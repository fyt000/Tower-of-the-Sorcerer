#include "presentation.hpp"
#include "rlgl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <format>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>

namespace tsw {
CanvasViewport window_viewport() {
    CanvasViewport view;
    auto* window = glfwGetCurrentContext();
    glfwGetWindowSize(window, &view.window_width, &view.window_height);
    glfwGetFramebufferSize(window, &view.framebuffer_width, &view.framebuffer_height);
    view.window_width = std::max(1, view.window_width);
    view.window_height = std::max(1, view.window_height);
    const float scale =
        std::min(view.window_width / float(CanvasWidth), view.window_height / float(CanvasHeight));
    view.area = {(view.window_width - CanvasWidth * scale) / 2,
                 (view.window_height - CanvasHeight * scale) / 2, CanvasWidth * scale, CanvasHeight * scale};
    return view;
}

namespace {
constexpr int SideWidth = 156, FrameWidth = 488, RightX = SideWidth + FrameWidth;
constexpr int DoorFrames = 16, TransformationFrames = 32, FirstHeroWalkingColor = 185;
constexpr int HeroSecondStepOffset = 2, HeroIdleOffset = 4;
constexpr Color Ink{246, 241, 230, 255}, Gold{247, 209, 138, 255}, Muted{199, 195, 197, 255};
constexpr Color Panel{57, 54, 63, 255}, Border{168, 145, 118, 255}, Bar{57, 56, 64, 255};
constexpr Rectangle Content{0, MenuHeight, CanvasWidth, ContentHeight};
constexpr Rectangle MapArea{BoardX, BoardY, BoardPixels, BoardPixels};
constexpr Rectangle EndingArea{80, MenuHeight + 50, 640, 400};

Rectangle sprite(int tile) {
    return {float((tile - 1) % 11 * TileSize), float((tile - 1) / 11 * TileSize), TileSize, TileSize};
}

bool clicked(Rectangle rect, Vector2 mouse) {
    return CheckCollisionPointRec(mouse, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

struct Typography {
    struct Typeface {
        std::vector<unsigned char> bytes;
        mutable std::unordered_map<int, Font> sizes;

        void load(const std::filesystem::path& path) {
            if (!std::filesystem::exists(path))
                return;
            int count{};
            if (auto* data = LoadFileData(path.string().c_str(), &count)) {
                bytes.assign(data, data + count);
                UnloadFileData(data);
            }
        }

        ~Typeface() {
            for (const auto& [size, font] : sizes)
                if (font.texture.id != GetFontDefault().texture.id)
                    UnloadFont(font);
        }

        Font at(int size, float scale) const {
            if (bytes.empty())
                return GetFontDefault();
            const int pixels = std::max(1, int(std::round(size * scale)));
            auto& font = sizes[size];
            if (!font.texture.id || font.baseSize != pixels) {
                if (font.texture.id && font.texture.id != GetFontDefault().texture.id)
                    UnloadFont(font);
                font = LoadFontFromMemory(".ttf", bytes.data(), int(bytes.size()), pixels, nullptr, 0);
                // Glyph alpha already contains antialiasing. Native pixel sampling avoids a second blur.
                SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
            }
            return font;
        }
    };

    Typeface body, numbers;
    Vector2 scale{1, 1};

    Typography() {
        // Use installed Windows fonts when available; no fonts or Windows APIs are bundled.
        if (const char* windows = std::getenv("WINDIR")) {
            const auto directory = std::filesystem::path(windows) / "Fonts";
            body.load(directory / "seguisb.ttf");
            numbers.load(directory / "segoeuib.ttf");
        }
    }

    Font font(int size, bool bold = false) const { return (bold ? numbers : body).at(size, scale.y); }

    float font_size(Font face, int size) const {
        return face.texture.id == GetFontDefault().texture.id ? float(size) : face.baseSize / scale.y;
    }

    Vector2 position(float x, float y) const {
        return {std::round(x * scale.x) / scale.x, std::round(y * scale.y) / scale.y};
    }

    void clip(Rectangle rect) const {
        const int x = int(std::floor(rect.x * scale.x)), y = int(std::floor(rect.y * scale.y));
        BeginScissorMode(x, y, int(std::ceil((rect.x + rect.width) * scale.x)) - x,
                         int(std::ceil((rect.y + rect.height) * scale.y)) - y);
    }

    int width(const std::string& value, int size, bool bold = false) const {
        const auto face = font(size, bold);
        return int(std::ceil(MeasureTextEx(face, value.c_str(), font_size(face, size), 0).x));
    }

    void draw(const std::string& value, int x, int y, int size, Color color = Ink) const {
        const auto face = font(size);
        std::istringstream lines(value);
        std::string line;
        while (std::getline(lines, line)) {
            DrawTextEx(face, line.c_str(), position(float(x), float(y)), font_size(face, size), 0, color);
            y += std::max(22, size + 2);
        }
    }

    std::string wrap(const std::string& text, int limit, int size) const {
        std::istringstream paragraphs(text);
        std::string paragraph, result;
        while (std::getline(paragraphs, paragraph)) {
            std::istringstream words(paragraph);
            std::string word, line;
            while (words >> word) {
                const std::string test = line.empty() ? word : line + " " + word;
                if (!line.empty() && width(test, size) > limit) {
                    result += line + '\n';
                    line = word;
                } else
                    line = test;
            }
            result += line + '\n';
        }
        return result;
    }

    void fit(const std::string& text, Rectangle rect, int size, Color color = Ink, bool right = false,
             bool bold = false) const {
        while (size > 10 && width(text, size, bold) > rect.width - 6)
            --size;
        clip(rect);
        const int measured = width(text, size, bold);
        const auto face = font(size, bold);
        DrawTextEx(face, text.c_str(),
                   position(rect.x + (right ? rect.width - measured - 3 : (rect.width - measured) / 2),
                            rect.y + (rect.height - size) / 2),
                   font_size(face, size), 0, color);
        EndScissorMode();
    }

    bool button(Rectangle rect, const std::string& label, Vector2 mouse, bool enabled = true) const {
        const bool hover = enabled && CheckCollisionPointRec(mouse, rect);
        DrawRectangleRec(rect, hover ? Color{89, 78, 75, 255} : Panel);
        DrawRectangleLinesEx(rect, 1, enabled ? Border : Color{99, 93, 94, 255});
        fit(label, rect, 18, enabled ? Ink : Color{145, 140, 143, 255});
        return enabled && clicked(rect, mouse);
    }

    void modal(Rectangle rect, const std::string& title) const {
        DrawRectangleRec(MapArea, Color{0, 0, 0, 130});
        DrawRectangle(int(rect.x + 4), int(rect.y + 5), int(rect.width), int(rect.height),
                      Color{0, 0, 0, 170});
        DrawRectangleRec(rect, Panel);
        DrawRectangleLinesEx(rect, 2, Border);
        draw(title, int(rect.x + 18), int(rect.y + 16), 21, Gold);
        DrawLine(int(rect.x + 18), int(rect.y + 45), int(rect.x + rect.width - 18), int(rect.y + 45), Border);
    }
};

bool passive(Item item) {
    return item == Item::Cross || item == Item::DragonSlayer || item == Item::LuckyGold;
}

constexpr std::array<const char*, 15> ItemDescriptions{
    "Inspect enemy statistics and predicted battle damage for this floor. The battle panel keeps the last "
    "defeated enemy.",
    "Read the clues recorded from old men and merchants. Scroll through long passages with the mouse wheel.",
    "Travel between visited floors. Use Up and Down to preview a floor, then Enter to travel.",
    "Works automatically in ordinary battles against Zombies and Zombie Knights.",
    "Restores life equal to ten times your attack plus five times your defense. Consumed when used.",
    "Lowers ordinary walls directly above, below, left and right of you. Consumed when used.",
    "Destroys eligible monsters directly above, below, left and right of you. Consumed when used.",
    "Warps to the opposite position on this floor when that position is a road. Each attempt uses one "
    "charge.",
    "Ascends one floor at the same map position if it is a road. Consumed on successful travel.",
    "Descends one floor at the same map position if it is a road. Consumed on successful travel.",
    "Works automatically in ordinary battles against the Dragon.",
    "Turns adjacent lava into road. The crystal can be used repeatedly.",
    "Opens every yellow door on the current floor. Consumed when used.",
    "Removes ordinary walls across the current floor. Consumed when used.",
    "Works automatically, increasing gold awarded by battle victories."};

constexpr const char* DissolveShader = R"(#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;
uniform sampler2D texture0;
uniform sampler2D maskAtlas;
uniform vec2 maskOrigin;
void main() {
    vec2 pixel = floor(fract(fragTexCoord * vec2(20.0, 12.5)) * 40.0);
    vec2 uv = maskOrigin + (pixel + vec2(0.5)) / vec2(440.0, 800.0);
    vec4 color = texture(texture0, fragTexCoord) * fragColor;
    color.a *= 1.0 - texture(maskAtlas, uv).r;
    finalColor = color;
})";
} // namespace

struct Presentation::Art {
    Typography text;
    Image atlas_image{}, background_image{};
    Texture2D atlas{};
    std::unordered_map<int, Texture2D> masked, icons;
    std::unordered_map<std::string, Texture2D> scenes;

    explicit Art(const Assets& assets) {
        atlas_image = assets.image("original-atlas");
        background_image = assets.image("original-background-atlas");
        if (atlas_image.width != 440 || atlas_image.height != 800 || background_image.width != 440 ||
            background_image.height != 600)
            throw std::runtime_error("Original color and mask atlases have unexpected dimensions.");
        atlas = LoadTextureFromImage(atlas_image);
        for (const auto name : SceneImageNames) {
            auto image = assets.image(name);
            auto texture = LoadTextureFromImage(image);
            UnloadImage(image);
            if (!IsTextureValid(texture))
                throw std::runtime_error("Unable to upload original scene artwork: " + std::string(name));
            scenes.emplace(std::string(name), texture);
        }
    }

    ~Art() {
        for (auto [key, texture] : masked)
            UnloadTexture(texture);
        for (auto [key, texture] : icons)
            UnloadTexture(texture);
        for (auto& [key, texture] : scenes)
            UnloadTexture(texture);
        UnloadTexture(atlas);
        UnloadImage(atlas_image);
        UnloadImage(background_image);
    }

    void tile(int value, int x, int y) const {
        if (value > 0 && value <= 220)
            DrawTextureRec(atlas, sprite(value), {float(x), float(y)}, WHITE);
        else
            DrawRectangle(x, y, TileSize, TileSize, BLACK);
    }

    void part(int value, Rectangle source, int x, int y) const {
        if (source.width <= 0 || source.height <= 0)
            return;
        const auto origin = sprite(value);
        source.x += origin.x;
        source.y += origin.y;
        DrawTextureRec(atlas, source, {float(x), float(y)}, WHITE);
    }

    Texture2D transparent(int color, int mask, bool background = false) {
        auto& textures = background ? icons : masked;
        const int key = color * 256 + mask;
        if (auto found = textures.find(key); found != textures.end())
            return found->second;
        Image colored = ImageFromImage(atlas_image, sprite(color));
        Image alpha = ImageFromImage(background ? background_image : atlas_image, sprite(mask));
        ImageColorInvert(&alpha);
        ImageAlphaMask(&colored, alpha);
        Texture2D texture = LoadTextureFromImage(colored);
        UnloadImage(colored);
        UnloadImage(alpha);
        textures.emplace(key, texture);
        return texture;
    }

    void icon(int value, Rectangle target, Color tint = WHITE) {
        DrawTexturePro(transparent(value, value, true), {0, 0, TileSize, TileSize}, target, {0, 0}, 0, tint);
    }

    void scene(const std::string& name, Rectangle target) const {
        const auto found = scenes.find(name);
        if (found == scenes.end())
            throw std::runtime_error("Missing scene: " + name);
        const auto texture = found->second;
        DrawTexturePro(texture, {0, 0, float(texture.width), float(texture.height)}, target, {0, 0}, 0,
                       WHITE);
    }
};

Presentation::Presentation(const Assets& assets) : art_(std::make_unique<Art>(assets)) {
    resize_canvas(window_viewport());
    scene_cache_ = LoadRenderTexture(CanvasWidth, ContentHeight);
    SetTextureFilter(scene_cache_.texture, TEXTURE_FILTER_POINT);
    dissolve_ = LoadShaderFromMemory(nullptr, DissolveShader);
    dissolve_mask_location_ = GetShaderLocation(dissolve_, "maskOrigin");
    if (!IsRenderTextureValid(canvas_) || !IsRenderTextureValid(scene_cache_) || dissolve_mask_location_ < 0)
        throw std::runtime_error("Could not create the game canvas or scene compositor.");
    BeginTextureMode(canvas_);
    ClearBackground(BLACK);
    EndTextureMode();
}

void Presentation::resize_canvas(const CanvasViewport& view) {
    const int width =
        std::max(1, int(std::round(view.area.width * view.framebuffer_width / view.window_width)));
    const int height =
        std::max(1, int(std::round(view.area.height * view.framebuffer_height / view.window_height)));
    if (canvas_.texture.width == width && canvas_.texture.height == height)
        return;
    auto resized = LoadRenderTexture(width, height);
    if (!IsRenderTextureValid(resized))
        throw std::runtime_error("Could not resize the game canvas");
    SetTextureFilter(resized.texture, TEXTURE_FILTER_POINT);
    BeginTextureMode(resized);
    ClearBackground(BLACK);
    if (canvas_.id)
        DrawTexturePro(canvas_.texture, {0, 0, float(canvas_.texture.width), -float(canvas_.texture.height)},
                       {0, 0, float(width), float(height)}, {0, 0}, 0, WHITE);
    EndTextureMode();
    if (canvas_.id)
        UnloadRenderTexture(canvas_);
    canvas_ = resized;
    art_->text.scale = {width / float(CanvasWidth), height / float(CanvasHeight)};
}

Presentation::~Presentation() {
    UnloadShader(dissolve_);
    UnloadRenderTexture(scene_cache_);
    UnloadRenderTexture(canvas_);
}

void Presentation::reset() {
    hide_panels_ = cache_requested_ = cache_valid_ = false;
    previous_raster_ = -1;
    walking_remaining_ = 0;
    animation_seconds_ = 0;
}

void Presentation::moved(const Hero& before, const Hero& after) {
    if (before.floor == after.floor && (before.x != after.x || before.y != after.y))
        walking_remaining_ = WalkAnimationSeconds;
}

void Presentation::advance(float seconds) {
    walking_remaining_ = std::max(0.f, walking_remaining_ - seconds);
    animation_seconds_ += seconds;
}

void Presentation::command(const Command& command) {
    if (command.op != Op::Callback)
        return;
    switch (static_cast<Callback>(command.a)) {
    case Callback::HidePanels:
        hide_panels_ = true;
        break;
    case Callback::CacheScene:
        cache_requested_ = true;
        break;
    case Callback::Capture:
    case Callback::RestoreBoard:
    case Callback::Teleport:
    case Callback::NextCycle:
        reset();
        break;
    default:
        break;
    }
}

void Presentation::cache_scene() {
    const int width = canvas_.texture.width;
    const int height = std::max(1, int(std::round(ContentHeight * art_->text.scale.y)));
    if (scene_cache_.texture.width != width || scene_cache_.texture.height != height) {
        UnloadRenderTexture(scene_cache_);
        scene_cache_ = LoadRenderTexture(width, height);
        if (!IsRenderTextureValid(scene_cache_))
            throw std::runtime_error("Could not resize the scene cache");
        SetTextureFilter(scene_cache_.texture, TEXTURE_FILTER_POINT);
    }
    BeginTextureMode(scene_cache_);
    ClearBackground(BLACK);
    // Render textures are vertically inverted; preserve the content below the menu.
    DrawTexturePro(canvas_.texture,
                   {0, StatusHeight * art_->text.scale.y, float(width), -ContentHeight * art_->text.scale.y},
                   {0, 0, float(width), float(height)}, {0, 0}, 0, WHITE);
    EndTextureMode();
    cache_requested_ = false;
    cache_valid_ = true;
}

void Presentation::draw_door(const Visual& visual, int x, int y) {
    // 0x4770E0: 16 steps cover half a 40-pixel tile, then a complete tile for walls/lava.
    const int half = TileSize / 2, opened = std::clamp(visual.door_frame * half / DoorFrames, 0, half);
    const int remaining = half - opened, full = 2 * opened;
    const auto part = [&](int tile, int sx, int sy, int w, int h, int dx, int dy) {
        art_->part(tile, {float(sx), float(sy), float(w), float(h)}, x + dx, y + dy);
    };
    art_->tile(Road, x, y);
    switch (static_cast<DoorMotion>(visual.door_mode)) {
    case DoorMotion::Yellow:
    case DoorMotion::Blue:
    case DoorMotion::Red:
        part(visual.door_mode, opened, 0, remaining, TileSize, 0, 0);
        part(visual.door_mode, half, 0, remaining, TileSize, half + opened, 0);
        break;
    case DoorMotion::OpenGate:
        for (int row = 0; row < 2; ++row)
            for (int col = 0; col < 2; ++col)
                part(SealedGate, col ? half : opened, row ? half : opened, remaining, remaining,
                     col ? half + opened : 0, row ? half + opened : 0);
        break;
    case DoorMotion::CloseGate:
        for (int row = 0; row < 2; ++row)
            for (int col = 0; col < 2; ++col)
                part(SealedGate, col ? half : remaining, row ? half : remaining, opened, opened,
                     col ? TileSize - opened : 0, row ? TileSize - opened : 0);
        break;
    case DoorMotion::Prison:
        if (full < TileSize)
            DrawTextureRec(art_->transparent(PrisonGate, PrisonGate, true),
                           {0, float(full), TileSize, float(TileSize - full)}, {float(x), float(y)}, WHITE);
        break;
    case DoorMotion::LowerWall:
        part(Wall, 0, 0, TileSize, TileSize - full, 0, full);
        break;
    case DoorMotion::RaiseWall:
        part(Wall, 0, TileSize - full, TileSize, full, 0, 0);
        break;
    case DoorMotion::RoadFromRight:
    case DoorMotion::RoadFromLeft:
    case DoorMotion::RoadFromTop:
    case DoorMotion::RoadFromBottom: {
        art_->tile(Lava + int(animation_seconds_ * 2) % 2 * Game::animation_offset(Lava), x, y);
        const auto motion = static_cast<DoorMotion>(visual.door_mode);
        if (motion == DoorMotion::RoadFromRight)
            part(Road, TileSize - full, 0, full, TileSize, 0, 0);
        else if (motion == DoorMotion::RoadFromLeft)
            part(Road, 0, 0, full, TileSize, 0, 0);
        else if (motion == DoorMotion::RoadFromTop)
            part(Road, 0, 0, TileSize, full, 0, 0);
        else
            part(Road, 0, TileSize - full, TileSize, full, 0, TileSize - full);
        break;
    }
    }
}

void Presentation::draw_transformation(const Game& game, int animation) {
    // 0x47C978: nine bats converge on the center while the Vampire materializes.
    const int progress = game.visual.raster_frame * TileSize / TransformationFrames;
    for (int row = 4; row <= 6; ++row)
        for (int col = 4; col <= 6; ++col)
            art_->tile(Road, BoardX + col * TileSize, BoardY + row * TileSize);
    for (int row = -1; row <= 1; ++row)
        for (int col = -1; col <= 1; ++col)
            art_->icon(BigBat + animation,
                       {float(BoardX + 5 * TileSize + col * (TileSize - progress)),
                        float(BoardY + 5 * TileSize + row * (TileSize - progress)), TileSize, TileSize});
    DrawTexture(
        art_->transparent(Vampire + animation, std::clamp(DissolveFirstMask + game.visual.raster_frame / 2,
                                                          DissolveFirstMask, DissolveLastMask)),
        BoardX + 5 * TileSize, BoardY + 5 * TileSize, WHITE);
}

void Presentation::draw_board(const Game& game, int floor, bool animated) {
    const auto& v = game.visual;
    const int animation = animated ? int(animation_seconds_ * 2) % 2 : 0;
    const bool active = floor == game.hero.floor && animated;
    const bool source_board = active && v.stair_source_floor >= 0 && !v.stair_revealing;
    for (int index = 0; index < CellCount; ++index) {
        const int x = BoardX + index % BoardWidth * TileSize, y = BoardY + index / BoardWidth * TileSize;
        int value = source_board ? v.stair_source.tiles[index] : game.tile(floor, index);
        value += animation * Game::animation_offset(value);
        art_->tile(value, x, y);
        if (!active)
            continue;
        const auto& layer = v.layers[index];
        if (layer.underlying >= 0) {
            art_->tile(layer.underlying, x, y);
            DrawTexture(art_->transparent(layer.color, layer.mask), x, y, WHITE);
        }
        if (v.door_cell == index)
            draw_door(v, x, y);
        if (v.stair_source_floor >= 0 && v.stair_cover[index])
            art_->tile(StairCover, x, y);
    }
    const int hero_x = source_board ? v.stair_hero_x : game.hero.x;
    const int hero_y = source_board ? v.stair_hero_y : game.hero.y;
    const Direction facing = source_board ? v.stair_hero_facing : game.hero.facing;
    const int position = cell(hero_x, hero_y);
    if (active && !v.hide_hero && !v.dead && !v.stair_cover[position] && v.layers[position].underlying < 0) {
        // 0x443120 selects standing frames 189/197/205/213, not the two walking poses.
        const int phase = walking_remaining_ <= 0                         ? HeroIdleOffset
                          : walking_remaining_ > WalkAnimationSeconds / 2 ? 0
                                                                          : HeroSecondStepOffset;
        const int pose = FirstHeroWalkingColor + (int(facing) - 1) * FacingSpriteStride + phase;
        DrawTexture(art_->transparent(pose, pose + 1), BoardX + hero_x * TileSize, BoardY + hero_y * TileSize,
                    WHITE);
    }
    if (active && v.raster_mode == 10)
        draw_transformation(game, animation);
}

void Presentation::draw_scene(const Game& game) {
    const int mode = game.visual.raster_mode, frame = game.visual.raster_frame;
    if (mode == 9) {
        art_->scene(game.hero.cycle_factor_minus_one ? "data3-title05r" : "data3-title05",
                    {SideWidth, MenuHeight, FrameWidth, ContentHeight});
    } else if (mode == 0 || mode == 2) {
        if (cache_valid_)
            DrawTexturePro(scene_cache_.texture,
                           {0, 0, float(scene_cache_.texture.width), -float(scene_cache_.texture.height)},
                           Content, {0, 0}, 0, WHITE);
        const auto mask = sprite(std::clamp(frame - 66 + 1, DissolveFirstMask, DissolveLastMask));
        const Vector2 origin{mask.x / art_->atlas.width, mask.y / art_->atlas.height};
        SetShaderValue(dissolve_, dissolve_mask_location_, &origin, SHADER_UNIFORM_VEC2);
        BeginShaderMode(dissolve_);
        SetShaderValueTexture(dissolve_, GetShaderLocation(dissolve_, "maskAtlas"), art_->atlas);
        art_->scene(mode == 0 ? "data3-open1" : "data3-open0", Content);
        EndShaderMode();
    } else if (mode == 1) {
        art_->scene("data3-open1", Content);
        art_->text.clip({0, MenuHeight, CanvasWidth, float(std::clamp(frame, 0, ContentHeight))});
        art_->scene("data3-open2", Content);
        EndScissorMode();
    } else if (mode == 6) {
        if (frame == 1)
            art_->scene("data3-open0", Content);
        else {
            const int image = std::clamp(frame + 3, 5, 20);
            art_->scene("data2-end" + (image < 10 ? std::string("0") : std::string()) + std::to_string(image),
                        Content);
        }
    } else if (mode == 4) {
        DrawRectangleRec(Content, BLACK);
        if (frame < 400) {
            const float inset_y = std::clamp(frame / 2.f, 0.f, 200.f), inset_x = inset_y * 640 / 400;
            art_->scene("data2-end20", {EndingArea.x + inset_x, EndingArea.y + inset_y,
                                        EndingArea.width - 2 * inset_x, EndingArea.height - 2 * inset_y});
        } else
            art_->scene("data2-end26", Content);
    } else if (mode == 5) {
        art_->scene("data2-end26", Content);
        art_->text.clip({EndingArea.x, EndingArea.y, EndingArea.width, float(std::clamp(frame, 0, 400))});
        art_->scene("data-exe-ending-story", EndingArea);
        EndScissorMode();
    } else if (mode == 7 || mode == 8) {
        art_->scene("data-exe-ending-card", Content);
    }
}

float command_interval(const Game& game) {
    // Presentation pacing only; the command stack and gameplay order stay unchanged.
    switch (game.visual.raster_mode) {
    case 0:
    case 2:
        return .05f;
    case 1:
        return .015f;
    case 4:
        return .05f;
    case 5:
        return .03f;
    case 6:
        return .225f;
    case 7:
    case 8:
        return .3f;
    case 9:
        return .06f;
    default:
        return game.visual.battle ? .06f : .016f;
    }
}

UiAction Presentation::draw_panels(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto& h = game.hero;
    art_->text.fit("Tower " + std::to_string(ui.flight >= 0 ? ui.flight : h.floor),
                   {18, MenuHeight + 59, 124, 24}, 22, Ink, false, true);
    for (int i = 0; i < 4; ++i)
        art_->text.fit(std::to_string(std::array<int, 4>{h.hp, h.attack, h.defense, h.gold}[i]),
                       {50, float(MenuHeight + 101 + i * 29), 92, 22}, 21, i == 3 ? Gold : Ink, true, true);
    art_->text.draw("ITEMS", 17, MenuHeight + 219, 14, Panel);
    if (art_->text.button({102, MenuHeight + 215, 40, 19}, "[I]", mouse,
                          !game.busy() && ui.flight < 0 && !ui.modal()))
        ui.inventory = true;
    UiAction action;
    int owned = 0;
    for (int i = 0; i < 15; ++i) {
        const auto item = static_cast<Item>(i);
        const int count = game.inventory(item);
        if (count <= 0)
            continue;
        const Rectangle rect{16.f + owned % 3 * 42, MenuHeight + 238.f + owned / 3 * 40, 42, 40};
        const bool hover =
            !ui.modal() && !game.dialogue && ui.flight < 0 && CheckCollisionPointRec(mouse, rect);
        if (hover)
            DrawRectangleRec(rect, Color{89, 85, 94, 255});
        art_->icon(HeroOrb + i, {rect.x + 3, rect.y + 2, 36, 36});
        if (count > 1) {
            const auto label = std::to_string(count);
            DrawRectangle(int(rect.x + 18), int(rect.y + 24), 23, 15, Panel);
            art_->text.fit(label, {rect.x + 18, rect.y + 24, 23, 15}, 12, Gold, true);
        }
        if (hover && !game.busy() && clicked(rect, mouse))
            ui.selected_item = i;
        ++owned;
    }
    constexpr std::array<const char*, 6> EquipmentNames{"None", "Iron", "Silver", "Knight", "Holy", "Sacred"};
    for (int i = 0; i < 2; ++i) {
        const int equipment = std::clamp(i == 0 ? h.sword : h.shield, 0, 5);
        art_->text.fit(EquipmentNames[equipment], {RightX + 12, float(MenuHeight + 80 + i * 60), 82, 23}, 19);
        if (equipment)
            art_->icon((i == 0 ? IronSword : IronShield) + equipment - 1,
                       {RightX + 100, float(MenuHeight + 60 + i * 60), 40, 40});
    }
    for (int i = 0; i < 3; ++i) {
        const int count = std::array<int, 3>{h.yellow_keys, h.blue_keys, h.red_keys}[i];
        art_->icon(std::array<int, 3>{YellowKey, BlueKey, RedKey}[i],
                   {RightX + 17, float(MenuHeight + 181 + i * 26), 25, 25},
                   count ? WHITE : Color{190, 190, 190, 160});
        art_->text.fit(std::to_string(count), {RightX + 52, float(MenuHeight + 183 + i * 26), 80, 23}, 20,
                       Ink, true);
    }
    if (ui.flight >= 0) {
        DrawRectangle(RightX + 12, MenuHeight + 278, 128, 162, Color{102, 102, 102, 255});
        art_->text.fit("ORB OF FLIGHT", {RightX + 12, MenuHeight + 282, 128, 22}, 15, Gold);
        art_->text.fit("Floor " + std::to_string(ui.flight), {RightX + 12, MenuHeight + 311, 128, 24}, 19);
        if (art_->text.button({RightX + 12, MenuHeight + 340, 60, 25}, "Up", mouse))
            action = {Action::FlightUp};
        if (art_->text.button({RightX + 80, MenuHeight + 340, 60, 25}, "Down", mouse))
            action = {Action::FlightDown};
        if (art_->text.button({RightX + 12, MenuHeight + 374, 128, 28}, "Travel [Enter]", mouse))
            action = {Action::Travel};
        if (art_->text.button({RightX + 12, MenuHeight + 410, 128, 28}, "Cancel [Esc]", mouse))
            action = {Action::CancelFlight};
        return action;
    }
    const EnemyInfo* enemy = game.visual.battle          ? &game.visual.battle_enemy
                             : game.visual.last_defeated ? &*game.visual.last_defeated
                                                         : nullptr;
    if (enemy) {
        const auto& monster = enemy->stats;
        art_->icon(enemy->tile, {RightX + 14, MenuHeight + 284, 40, 40});
        art_->text.fit(game.visual.battle ? "Enemy life" : "Defeated",
                       {RightX + 58, MenuHeight + 281, 80, 22}, 16, Gold);
        art_->text.fit(game.visual.battle ? std::to_string(game.visual.enemy_hp)
                                          : "Damage " + std::to_string(enemy->damage),
                       {RightX + 58, MenuHeight + 305, 80, 22}, 17);
        art_->text.fit(std::string(Game::monster_name(enemy->row)), {RightX + 12, MenuHeight + 338, 128, 22},
                       18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(std::to_string(std::array<int, 3>{monster.hp, monster.attack, monster.defense}[i]),
                           {RightX + 52, float(MenuHeight + 366 + i * 24), 85, 22}, 20, Ink, true);
    } else {
        art_->text.fit("Defeated enemies", {RightX + 12, MenuHeight + 284, 128, 24}, 16, Muted);
        art_->text.fit("appear here", {RightX + 12, MenuHeight + 308, 128, 24}, 16, Muted);
        art_->text.fit("The Name", {RightX + 12, MenuHeight + 338, 128, 22}, 18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(std::array<const char*, 3>{"Life", "Offense", "Defense"}[i],
                           {RightX + 52, float(MenuHeight + 366 + i * 24), 85, 22}, 18);
    }
    if (h.fairy_visits)
        art_->text.fit("Fairy rank " + std::to_string(h.fairy_rank), {RightX + 12, MenuHeight + 453, 128, 20},
                       13, Panel);
    return action;
}

UiAction Presentation::draw_dialogue(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto& dialogue = *game.dialogue;
    constexpr Rectangle rect{BoardX + 12, BoardY + 58, 416, 330};
    art_->text.modal(rect, dialogue.shop ? "An offer" : "Conversation");
    const auto text = art_->text.wrap(dialogue.text, 376, 18);
    const int lines = int(std::count(text.begin(), text.end(), '\n'));
    constexpr int TextHeight = 188;
    ui.dialogue_scroll = std::clamp(ui.dialogue_scroll, 0.f, std::max(0.f, float(lines * 22 - TextHeight)));
    art_->text.clip({rect.x + 20, rect.y + 62, 376, TextHeight});
    art_->text.draw(text.c_str(), int(rect.x + 20), int(rect.y + 62 - ui.dialogue_scroll), 18, Ink);
    EndScissorMode();
    if (lines * 22 > TextHeight)
        art_->text.draw("Mouse wheel to scroll", int(rect.x + 20), int(rect.y + 252), 12, Muted);
    if (dialogue.shop) {
        for (int i = 0; i < 3; ++i)
            if (!dialogue.choices[i].empty() &&
                art_->text.button({rect.x + 20 + i * 128, rect.y + 274, 120, 28}, dialogue.choices[i], mouse))
                return {Action::Choose, i};
        if (art_->text.button({rect.x + 284, rect.y + 308, 112, 19}, "Cancel [Esc]", mouse))
            return {Action::Choose, -1};
    } else if (art_->text.button({rect.x + 20, rect.y + 282, 376, 30}, "Continue  [Enter / Space]", mouse))
        return {Action::Continue};
    return {};
}

UiAction Presentation::draw_inventory(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{BoardX + 4, BoardY + 9, 432, 420};
    art_->text.modal(rect, "Inventory");
    for (int i = 0; i < 15; ++i) {
        const auto item = static_cast<Item>(i);
        const int count = game.inventory(item);
        const Rectangle row{rect.x + 12 + i / 8 * 204, rect.y + 57 + i % 8 * 39, 198, 35};
        const bool hover = CheckCollisionPointRec(mouse, row);
        DrawRectangleRec(row, count && hover ? Color{88, 79, 76, 255} : Color{66, 62, 70, 255});
        art_->icon(HeroOrb + i, {row.x + 2, row.y + 2, 31, 31}, count ? WHITE : Color{170, 170, 170, 130});
        art_->text.draw(std::string(Game::item_name(item)).c_str(), int(row.x + 37), int(row.y + 2), 17,
                        count ? Ink : Muted);
        art_->text.draw(count ? passive(item) ? "Passive" : "Use / inspect" : "Not found", int(row.x + 37),
                        int(row.y + 21), 13, count ? Gold : Muted);
        if (count && clicked(row, mouse)) {
            ui.inventory = false;
            ui.selected_item = i;
            break;
        }
    }
    if (art_->text.button({rect.x + 12, rect.y + 378, 408, 28}, "Close  [I / Esc]", mouse))
        ui.inventory = false;
    return {};
}

void Presentation::draw_enemies(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{100, BoardY + 20, 600, 400};
    constexpr int VisibleRows = 6;
    std::vector<std::pair<int, int>> enemies; // One entry per shared monster row; tile and count.
    for (int tile : game.floors[game.hero.floor].tiles) {
        const int row = Game::monster_for_tile(tile);
        if (row < 0)
            continue;
        const auto found = std::find_if(enemies.begin(), enemies.end(), [&](auto entry) {
            return Game::monster_for_tile(entry.first) == row;
        });
        if (found == enemies.end())
            enemies.emplace_back(tile, 1);
        else
            ++found->second;
    }
    const int last_row = std::max(0, int(enemies.size()) - VisibleRows);
    ui.enemy_first_row = std::clamp(ui.enemy_first_row, 0, last_row);
    art_->text.modal(rect, "Orb of the Hero - floor " + std::to_string(game.hero.floor));
    for (const auto& [label, x, width] :
         std::array<std::tuple<const char*, int, int>, 5>{{{"Enemy", 52, 156},
                                                           {"Life", 216, 76},
                                                           {"Offense", 300, 72},
                                                           {"Defense", 380, 68},
                                                           {"Damage", 464, 116}}})
        art_->text.fit(label, {rect.x + x, rect.y + 57, float(width), 24}, 17, Gold);
    const int scale = game.hero.cycle_factor_minus_one + 1;
    for (int visible = 0; visible < VisibleRows && ui.enemy_first_row + visible < int(enemies.size());
         ++visible) {
        const auto [tile, count] = enemies[ui.enemy_first_row + visible];
        const int row = Game::monster_for_tile(tile);
        const auto& monster = game.monsters[row];
        const float y = rect.y + 88 + visible * 40;
        DrawRectangle(int(rect.x + 16), int(y), int(rect.width - 32), 37,
                      visible % 2 ? Color{67, 63, 73, 255} : Color{77, 72, 80, 255});
        art_->icon(tile, {rect.x + 18, y + 3, 31, 31});
        art_->text.fit(std::string(Game::monster_name(row)) +
                           (count > 1 ? " (" + std::to_string(count) + ")" : ""),
                       {rect.x + 52, y + 4, 156, 29}, 18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(
                std::to_string(std::array<int, 3>{monster.hp, monster.attack, monster.defense}[i] * scale),
                {rect.x + 216 + i * 82, y + 4, 76, 29}, 18, Ink, false, true);
        const auto forecast = game.forecast(tile);
        art_->text.fit(
            forecast.penetrates ? std::to_string(forecast.damage) : "Blocked", {rect.x + 464, y + 4, 116, 29},
            18, !forecast.penetrates || forecast.damage >= game.hero.hp ? Color{255, 161, 146, 255} : Ink);
    }
    if (enemies.empty())
        art_->text.fit("No enemies remain on this floor.", {rect.x + 16, rect.y + 140, 568, 40}, 20);
    if (art_->text.button({rect.x + 16, rect.y + 350, 130, 28}, "Previous", mouse, ui.enemy_first_row > 0))
        ui.enemy_first_row = std::max(0, ui.enemy_first_row - VisibleRows);
    if (art_->text.button({rect.x + 152, rect.y + 350, 130, 28}, "Next", mouse,
                          ui.enemy_first_row < last_row))
        ui.enemy_first_row = std::min(last_row, ui.enemy_first_row + VisibleRows);
    if (art_->text.button({rect.x + 312, rect.y + 350, 272, 28}, "Close [Enter / Esc]", mouse))
        ui.enemies = false;
    art_->text.fit("Scroll or use Up / Down to browse. The battle panel keeps the last victory.",
                   {rect.x + 16, rect.y + 382, 568, 18}, 14, Muted);
}

UiAction Presentation::draw_item(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto item = static_cast<Item>(ui.selected_item);
    constexpr Rectangle rect{BoardX + 18, BoardY + 98, 404, 250};
    art_->text.modal(rect, std::string(Game::item_name(item)));
    art_->icon(HeroOrb + ui.selected_item, {rect.x + 20, rect.y + 60, 40, 40});
    art_->text.draw(
        (passive(item) ? "Passive item" : "Owned: " + std::to_string(game.inventory(item))).c_str(),
        int(rect.x + 76), int(rect.y + 68), 18, Gold);
    const auto description = art_->text.wrap(ItemDescriptions[ui.selected_item], 364, 17);
    SetTextLineSpacing(22);
    art_->text.draw(description.c_str(), int(rect.x + 20), int(rect.y + 112), 17, Ink);
    if (passive(item)) {
        if (art_->text.button({rect.x + 20, rect.y + 203, 364, 29}, "Close  [Enter / Esc]", mouse))
            ui.selected_item = -1;
    } else {
        if (art_->text.button({rect.x + 20, rect.y + 203, 176, 29},
                              item == Item::HeroOrb ? "View enemies [Enter]" : "Use  [Enter]", mouse,
                              !game.busy() && game.inventory(item) > 0))
            return {Action::UseItem, ui.selected_item};
        if (art_->text.button({rect.x + 208, rect.y + 203, 176, 29}, "Cancel  [Esc]", mouse))
            ui.selected_item = -1;
    }
    return {};
}

void Presentation::draw_help(DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{BoardX + 12, BoardY + 14, 416, 410};
    art_->text.modal(rect, "Tower of the Sorcerer");
    const std::array<std::pair<const char*, const char*>, 8> controls{{{"Arrows / WASD", "Move"},
                                                                       {"Enter / Space", "Continue dialogue"},
                                                                       {"I", "Inventory"},
                                                                       {"F6 / F7", "Save / load slots"},
                                                                       {"F5 / F9", "Quick save / restore"},
                                                                       {"F8", "Fairy checkpoint"},
                                                                       {"F2", "New game"},
                                                                       {"M", "Music and effects"}}};
    for (int i = 0; i < int(controls.size()); ++i) {
        art_->text.draw(controls[i].first, int(rect.x + 20), int(rect.y + 60 + i * 24), 17, Ink);
        art_->text.draw(controls[i].second, int(rect.x + 170), int(rect.y + 60 + i * 24), 17, Ink);
    }
    art_->text.draw("Click an item to inspect or use it.\nHero Orb: view this floor's enemies.\nFlight: Up / "
                    "Down, Enter to travel, Esc to cancel.\nOptions: music and game speed.",
                    int(rect.x + 20), int(rect.y + 266), 17, Muted);
    if (art_->text.button({rect.x + 20, rect.y + 365, 376, 29}, "Close  [Esc]", mouse))
        ui.help = false;
}

UiAction Presentation::draw_menu(const Game& game, DesktopUi& ui, Vector2 mouse) {
    if (ui.menu == Menu::Game) {
        constexpr Rectangle rect{6, MenuHeight, 214, 306};
        DrawRectangleRec(rect, Panel);
        DrawRectangleLinesEx(rect, 1, Border);
        const std::array<const char*, 9> labels{
            "New game [F2]",   "Save slots [F6]",    "Load slots [F7]",
            "Quick save [F5]", "Quick restore [F9]", "Fairy checkpoint [F8]",
            "Play replay",     "Main menu [Esc]",    "Close"};
        const std::array<Action, 8> actions{
            Action::NewGame, Action::OpenSaveSlots,   Action::OpenLoadSlots, Action::Save,
            Action::Load,    Action::FairyCheckpoint, Action::OpenReplays,   Action::MainMenu};
        for (int i = 0; i < int(labels.size()); ++i)
            if (art_->text.button({rect.x + 6, rect.y + 6 + i * 33, rect.width - 12, 27}, labels[i], mouse,
                                  (i != 1 && i != 3) || !game.busy())) {
                ui.menu = Menu::None;
                return i < int(actions.size()) ? UiAction{actions[i]} : UiAction{};
            }
    } else if (ui.menu == Menu::Options) {
        constexpr Rectangle rect{182, 82, 436, 390};
        art_->text.modal(rect, "Settings");
        if (art_->text.button({rect.x + 18, rect.y + 60, 400, 34},
                              ui.muted ? "Enable music and effects [M]" : "Mute music and effects [M]",
                              mouse))
            return {Action::Mute};
        art_->text.draw("Walking and animation speed", int(rect.x + 18), int(rect.y + 112), 17, Muted);
        for (int i = 0; i < 3; ++i)
            if (art_->text.button({rect.x + 18 + i * 135, rect.y + 138, 130, 30},
                                  std::format("{}x{}", GameSpeeds[i], ui.speed_index == i ? " *" : ""),
                                  mouse))
                return {Action::Speed, i};
        art_->text.draw("Replay and animation speed", int(rect.x + 18), int(rect.y + 188), 17, Muted);
        for (int i = 0; i < int(ReplaySpeeds.size()); ++i)
            if (art_->text.button(
                    {rect.x + 18 + i * 57, rect.y + 214, 54, 30},
                    std::format("{}x{}", ReplaySpeeds[i], ui.replay_speed_index == i ? " *" : ""), mouse))
                return {Action::ReplaySpeed, i};
        if (art_->text.button({rect.x + 18, rect.y + 264, 400, 34},
                              ui.recording_enabled ? "Record new games: on" : "Record new games: off", mouse))
            return {Action::Recording};
        art_->text.draw("New games, recorded loads and replay takeover.", int(rect.x + 18), int(rect.y + 308),
                        15, Muted);
        if (art_->text.button({rect.x + 18, rect.y + 346, 400, 30}, "Done [Esc]", mouse))
            ui.menu = Menu::None;
    }
    return {};
}

UiAction Presentation::draw_save_slots(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{82, MenuHeight + 16, 636, 466};
    const bool saving = ui.save_picker == SavePicker::Save;
    art_->text.modal(rect, saving ? "Save game - eight slots" : "Load game - eight slots");
    if (!saving) {
        if (art_->text.button({rect.x + 344, rect.y + 14, 136, 28}, "Quick [F9]", mouse, ui.quick_available))
            return {Action::Load};
        if (art_->text.button({rect.x + 488, rect.y + 14, 130, 28}, "Fairy [F8]", mouse, ui.fairy_available))
            return {Action::FairyCheckpoint};
    }
    for (int i = 0; i < ManualSaveSlotCount; ++i) {
        const Rectangle card{rect.x + 18 + i % 2 * 306, rect.y + 64 + i / 2 * 84, 294, 76};
        const auto& info = ui.save_slots[i];
        const bool selected = ui.selected_slot == i + 1;
        const bool hover = CheckCollisionPointRec(mouse, card);
        DrawRectangleRec(card, selected ? Color{84, 69, 65, 255} : Color{45, 43, 51, 255});
        DrawRectangleLinesEx(card, selected ? 2.f : 1.f, selected || hover ? Gold : Border);
        art_->text.draw("Slot " + std::to_string(i + 1), int(card.x + 12), int(card.y + 7), 18, Gold);
        if (info.state == SaveSlotState::Ready) {
            const std::string mode = !info.backside     ? "Frontside"
                                     : info.later_cycle ? "Backside 3+"
                                                        : "Backside 2";
            art_->text.fit("Floor " + std::to_string(info.floor) + " / " + mode,
                           {card.x + 72, card.y + 5, card.width - 84, 23}, 16, Muted, true);
            art_->text.draw("HP " + std::to_string(info.hp), int(card.x + 12), int(card.y + 30), 16);
            art_->text.draw("ATK " + std::to_string(info.attack) + "    DEF " + std::to_string(info.defense),
                            int(card.x + 12), int(card.y + 51), 16);
        } else if (info.state == SaveSlotState::Empty)
            art_->text.draw("Empty", int(card.x + 12), int(card.y + 33), 17, Muted);
        else {
            art_->text.draw("Unreadable save", int(card.x + 12), int(card.y + 29), 17, Gold);
            art_->text.fit(info.error, {card.x + 12, card.y + 50, card.width - 24, 20}, 13, Muted);
        }
        if (clicked(card, mouse))
            ui.selected_slot = i + 1;
    }
    art_->text.draw("1-8 or arrows: select a slot. Enter: confirm. Esc: close.", int(rect.x + 18),
                    int(rect.y + 404), 16, Muted);
    const auto& selected = ui.save_slots[ui.selected_slot - 1];
    const std::string label =
        saving ? (selected.state == SaveSlotState::Empty ? "Save to slot " : "Replace slot ") : "Load slot ";
    if (art_->text.button({rect.x + 18, rect.y + 430, 294, 28},
                          label + std::to_string(ui.selected_slot) + " [Enter]", mouse,
                          saving ? !game.busy() : selected.state == SaveSlotState::Ready))
        return {saving ? Action::SaveSlot : Action::LoadSlot, ui.selected_slot};
    if (art_->text.button({rect.x + 324, rect.y + 430, 294, 28}, "Cancel [Esc]", mouse))
        ui.close_overlays();
    return {};
}

UiAction Presentation::draw_home(const DesktopUi& ui, Vector2 mouse) {
    art_->scene("data3-open0", {0, 0, CanvasWidth, CanvasHeight});
    const std::array<std::string, 5> labels{ui.replay_active ? "Continue replay" : "Continue game",
                                            "New game", "Load game", "Play replay", "Settings"};
    constexpr std::array<Action, 5> actions{Action::ResumeGame, Action::NewGame, Action::OpenLoadSlots,
                                            Action::OpenReplays, Action::OpenSettings};
    const int first = ui.game_started ? 0 : 1;
    constexpr int top = 48;
    for (int i = first; i < int(labels.size()); ++i) {
        const Rectangle row{118, float(top + (i - first) * 52), 244, 44};
        const bool selected = ui.home_selection == i;
        const bool hover = CheckCollisionPointRec(mouse, row);
        const int x = int(row.x + 26), y = int(row.y + 8);
        art_->text.draw(labels[i], x + 1, y + 2, 26, Color{0, 0, 0, 190});
        art_->text.draw(labels[i], x, y, 26, selected || hover ? Gold : Ink);
        if (selected)
            art_->text.draw(">", int(row.x), y, 26, Gold);
        if (clicked(row, mouse))
            return {actions[i]};
    }
    return {};
}

UiAction Presentation::draw_replays(DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{60, 54, 680, 440};
    constexpr int Rows = 5;
    art_->text.modal(rect, "Play a recording");
    art_->text.draw("Saved recordings  /  scroll or use Up and Down", int(rect.x + 18), int(rect.y + 59), 16,
                    Muted);
    const int count = int(ui.replay_files.size());
    if (CheckCollisionPointRec(mouse, {rect.x + 18, rect.y + 88, 644, 195}))
        ui.replay_first_row -= int(GetMouseWheelMove());
    ui.replay_first_row = std::clamp(ui.replay_first_row, 0, std::max(0, count - Rows));
    for (int row = 0; row < Rows && row + ui.replay_first_row < count; ++row) {
        const int index = row + ui.replay_first_row;
        const Rectangle button{rect.x + 18, rect.y + 92 + row * 39, 644, 32};
        const auto text = ui.replay_files[index].filename().u8string();
        if (art_->text.button(button, std::string(text.begin(), text.end()), mouse)) {
            ui.replay_selected = index;
            const auto path = ui.replay_files[index].u8string();
            ui.replay_path.assign(path.begin(), path.end());
            ui.replay_path_focus = false;
        }
        if (ui.replay_selected == index)
            DrawRectangleLinesEx(button, 2, Gold);
    }
    if (!count)
        art_->text.draw(
            "No recordings saved yet. Paste a file path below,\nor drop a .jsonl file on the window.",
            int(rect.x + 26), int(rect.y + 116), 19, Muted);
    art_->text.draw("Recording file  /  Ctrl+V to paste", int(rect.x + 18), int(rect.y + 292), 16, Muted);
    const Rectangle field{rect.x + 18, rect.y + 318, 644, 34};
    DrawRectangleRec(field, Color{31, 29, 36, 255});
    DrawRectangleLinesEx(field, 1, ui.replay_path_focus ? Gold : Border);
    if (clicked(field, mouse))
        ui.replay_path_focus = true;
    art_->text.clip(field);
    const int offset = std::max(0, art_->text.width(ui.replay_path, 16) - int(field.width) + 24);
    art_->text.draw(ui.replay_path, int(field.x + 8) - offset, int(field.y + 6), 16);
    EndScissorMode();
    if (art_->text.button({rect.x + 18, rect.y + 368, 314, 32}, "Play [Enter]", mouse,
                          !ui.replay_path.empty()))
        return {Action::PlayReplay};
    if (art_->text.button({rect.x + 348, rect.y + 368, 314, 32}, "Cancel [Esc]", mouse))
        ui.close_overlays();
    art_->text.fit(ui.notice.empty() ? "Recordings are read only. Take over to continue playing." : ui.notice,
                   {rect.x + 18, rect.y + 408, 644, 24}, 15, ui.notice.empty() ? Muted : Gold);
    return {};
}

UiAction Presentation::draw_replay_controls(const DesktopUi& ui, Vector2 mouse) {
    const bool ready = ui.replay_error.empty();
    const bool remaining = ui.replay_step < ui.replay_count || ui.replay_in_progress;
    if (art_->text.button({6, 3, 52, 22}, "Menu", mouse))
        return {Action::MainMenu};
    if (art_->text.button({64, 3, 78, 22}, "Previous", mouse, ui.replay_step > 0))
        return {Action::ReplayPrevious};
    if (art_->text.button({148, 3, 70, 22}, ui.replay_paused ? "Resume" : "Pause", mouse, ready && remaining))
        return {Action::ReplayPause};
    if (art_->text.button({224, 3, 52, 22}, "Next", mouse, ready && remaining))
        return {Action::ReplayNext};
    if (art_->text.button({282, 3, 70, 22}, "Restart", mouse))
        return {Action::ReplayRestart};
    if (art_->text.button({358, 3, 86, 22}, "Take over", mouse, ready))
        return {Action::ReplayTakeOver};
    if (art_->text.button({450, 3, 24, 22}, "-", mouse, ui.replay_speed_index > 0))
        return {Action::ReplaySpeed, ui.replay_speed_index - 1};
    art_->text.fit(std::format("{}x", ReplaySpeeds[ui.replay_speed_index]), {480, 3, 66, 22}, 17, Gold);
    if (art_->text.button({552, 3, 24, 22}, "+", mouse, ui.replay_speed_index + 1 < int(ReplaySpeeds.size())))
        return {Action::ReplaySpeed, ui.replay_speed_index + 1};
    if (art_->text.button({584, 3, 76, 22}, "Settings", mouse))
        return {Action::OpenSettings};
    art_->text.fit(std::format("{} / {}", ui.replay_step, ui.replay_count), {666, 3, 128, 22}, 16, Muted);
    return {};
}

UiAction Presentation::draw(const Game& game, DesktopUi& ui, Vector2 mouse) {
    resize_canvas(window_viewport());
    const int mode = game.visual.raster_mode;
    if (!ui.home) {
        if ((mode == 0 || mode == 2) && previous_raster_ != mode && !cache_valid_)
            cache_requested_ = true;
        if (cache_requested_)
            cache_scene();
        previous_raster_ = mode;
    }
    BeginTextureMode(canvas_);
    // Layout stays in original logical coordinates; rasterization uses the actual display pixels.
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, CanvasWidth, CanvasHeight, 0, 0, 1);
    rlMatrixMode(RL_MODELVIEW);
    ClearBackground(Bar);
    if (ui.home) {
        const bool overlay = ui.save_picker != SavePicker::None || ui.replay_picker || ui.menu != Menu::None;
        auto action = draw_home(ui, overlay ? Vector2{-1, -1} : mouse);
        if (ui.save_picker != SavePicker::None)
            action = draw_save_slots(game, ui, mouse);
        else if (ui.replay_picker)
            action = draw_replays(ui, mouse);
        else if (ui.menu != Menu::None)
            action = draw_menu(game, ui, mouse);
        if (!ui.notice.empty())
            art_->text.fit(ui.notice, {12, CanvasHeight - 36.f, CanvasWidth - 24.f, 30}, 17, Gold);
        EndTextureMode();
        return action;
    }
    art_->scene(game.hero.cycle_factor_minus_one ? "data3-leftr" : "data3-left",
                {0, MenuHeight, SideWidth, ContentHeight});
    art_->scene("data3-center", {SideWidth, MenuHeight, FrameWidth, ContentHeight});
    art_->scene(game.hero.cycle_factor_minus_one ? "data3-rightr" : "data3-right",
                {RightX, MenuHeight, SideWidth, ContentHeight});
    if (mode != 9)
        draw_board(game, ui.flight >= 0 ? ui.flight : game.hero.floor, ui.flight < 0);
    UiAction action;
    const auto game_mouse = ui.replay_active ? Vector2{-1, -1} : mouse;
    if (!hide_panels_)
        action = draw_panels(game, ui, game_mouse);
    if (mode == 9 || (mode >= 0 && mode <= 8))
        draw_scene(game);
    if (ui.save_picker != SavePicker::None)
        action = draw_save_slots(game, ui, mouse);
    else if (ui.replay_picker)
        action = draw_replays(ui, mouse);
    else if (game.dialogue && !ui.help && ui.menu == Menu::None) {
        ui.inventory = false;
        ui.selected_item = -1;
        action = draw_dialogue(game, ui, game_mouse);
    } else if (ui.selected_item >= 0)
        action = draw_item(game, ui, game_mouse);
    else if (ui.inventory)
        action = draw_inventory(game, ui, game_mouse);
    else if (ui.enemies)
        draw_enemies(game, ui, mouse);
    if (ui.help)
        draw_help(ui, mouse);

    DrawRectangle(0, 0, CanvasWidth, MenuHeight, Bar);
    DrawLine(0, MenuHeight - 1, CanvasWidth, MenuHeight - 1, Border);
    if (ui.replay_active) {
        const auto control = draw_replay_controls(ui, ui.modal() ? Vector2{-1, -1} : mouse);
        if (control.kind != Action::None)
            action = control;
    } else {
        if (art_->text.button({6, 3, 58, 22}, "Game", mouse)) {
            const bool opened = ui.menu == Menu::Game;
            ui.close_overlays();
            ui.menu = opened ? Menu::None : Menu::Game;
        }
        if (art_->text.button({70, 3, 78, 22}, "Options", mouse)) {
            const bool opened = ui.menu == Menu::Options;
            ui.close_overlays();
            ui.menu = opened ? Menu::None : Menu::Options;
        }
        if (art_->text.button({154, 3, 58, 22}, "Help", mouse)) {
            ui.close_overlays();
            ui.help = true;
        }
        const std::string label = (game.hero.cycle_factor_minus_one ? "Backside  /  " : "") +
                                  std::to_string(int(GameSpeeds[ui.speed_index])) + "x  /  " +
                                  (ui.muted ? "Music off" : "Music on") +
                                  (ui.recording_active ? "  /  Recording" : "");
        art_->text.fit(label, {440, 3, 350, 22}, 17, Muted, true);
    }
    if (ui.menu != Menu::None)
        action = draw_menu(game, ui, mouse);

    DrawRectangle(0, MenuHeight + ContentHeight, CanvasWidth, StatusHeight, Color{82, 80, 83, 255});
    DrawLine(0, MenuHeight + ContentHeight, CanvasWidth, MenuHeight + ContentHeight, Border);
    std::string status = ui.flight >= 0 ? "Previewing floor " + std::to_string(ui.flight) +
                                              ". Up / Down to choose; Enter to travel."
                                        : game.status;
    if (ui.ending_wait)
        status = "The End. Press Enter / Space to continue to the backside tower.";
    if (ui.replay_active) {
        const std::string state =
            ui.replay_paused
                ? (ui.replay_step == ui.replay_count && !ui.replay_in_progress ? "Finished" : "Paused")
                : "Playing";
        status = ui.replay_error.empty() ? state + "  /  " + ui.replay_name + "  /  " + game.status
                                         : ui.replay_error;
    }
    if (!ui.replay_active && !ui.modal() && !game.dialogue && ui.flight < 0) {
        int owned = 0;
        for (int i = 0; i < 15; ++i)
            if (game.inventory(static_cast<Item>(i)) > 0) {
                if (CheckCollisionPointRec(
                        mouse, {16.f + owned % 3 * 42, MenuHeight + 238.f + owned / 3 * 40, 42, 40}))
                    status = std::string(Game::item_name(static_cast<Item>(i))) + "  -  click to inspect";
                ++owned;
            }
    }
    art_->text.fit(
        status,
        {7, MenuHeight + ContentHeight + 3, ui.ending_wait ? 643.f : CanvasWidth - 14.f, StatusHeight - 6},
        17);
    if (ui.ending_wait && !ui.replay_active &&
        art_->text.button({658, MenuHeight + ContentHeight + 3, 135, StatusHeight - 6}, "Continue", mouse,
                          !ui.modal()))
        action = {Action::ContinueEnding};
    EndTextureMode();
    return action;
}

Vector2 Presentation::mouse_position() const {
    return window_viewport().canvas_point(GetMousePosition());
}

void Presentation::present() const {
    const auto view = window_viewport();
    BeginDrawing();
    // GLFW reports logical window and physical framebuffer sizes separately. Raylib
    // 5.5's resize/DPI callbacks can leave its projection and screenScale out of sync.
    rlViewport(0, 0, view.framebuffer_width, view.framebuffer_height);
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, view.window_width, view.window_height, 0, 0, 1);
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
    ClearBackground(BLACK);
    DrawTexturePro(canvas_.texture, {0, 0, float(canvas_.texture.width), -float(canvas_.texture.height)},
                   view.area, {0, 0}, 0, WHITE);
    EndDrawing();
}

Image Presentation::capture_window() const {
    const auto view = window_viewport();
    return {rlReadScreenPixels(view.framebuffer_width, view.framebuffer_height), view.framebuffer_width,
            view.framebuffer_height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
}

Image Presentation::capture_native_canvas() const {
    Image image = LoadImageFromTexture(canvas_.texture);
    ImageFlipVertical(&image);
    return image;
}

Image Presentation::capture_canvas() const {
    auto image = capture_native_canvas();
    if (image.width == CanvasWidth && image.height == CanvasHeight)
        return image;
    // Sample logical pixel centers. ImageResizeNN samples left edges, which shifts
    // sprite pixels when the native canvas has a fractional scale such as 1.5x.
    auto logical = GenImageColor(CanvasWidth, CanvasHeight, BLANK);
    const auto* source = static_cast<const Color*>(image.data);
    auto* destination = static_cast<Color*>(logical.data);
    for (int y = 0; y < CanvasHeight; ++y)
        for (int x = 0; x < CanvasWidth; ++x) {
            const int sx = (2 * x + 1) * image.width / (2 * CanvasWidth);
            const int sy = (2 * y + 1) * image.height / (2 * CanvasHeight);
            destination[y * CanvasWidth + x] = source[sy * image.width + sx];
        }
    UnloadImage(image);
    return logical;
}

bool Presentation::screenshot(const std::filesystem::path& path) const {
    Image capture = capture_canvas();
    const bool result = ExportImage(capture, path.string().c_str());
    UnloadImage(capture);
    return result;
}
} // namespace tsw
