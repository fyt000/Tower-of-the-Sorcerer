#include "presentation.hpp"
#include "fairy_dialogue.hpp"
#include "rlgl.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifdef __ANDROID__
#include <EGL/egl.h>
#include <android/configuration.h>
#include <android_native_app_glue.h>
extern "C" android_app* GetAndroidApp();
#endif
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>

namespace tsw {
#ifdef __ANDROID__
namespace {
int32_t (*android_input_handler)(android_app*, AInputEvent*){};
bool android_pointer_cancelled{};

int32_t track_android_pointer(android_app* app, AInputEvent* event) {
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        const auto action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
        if (action == AMOTION_EVENT_ACTION_DOWN)
            android_pointer_cancelled = false;
        else if (action == AMOTION_EVENT_ACTION_CANCEL)
            android_pointer_cancelled = true;
    }
    return android_input_handler ? android_input_handler(app, event) : 0;
}
} // namespace
#endif

bool touch_device() {
#ifdef __ANDROID__
    return true;
#elif defined(__EMSCRIPTEN__)
    return EM_ASM_INT({ return !!Module['tswTouchDevice']; });
#else
    return false;
#endif
}

std::optional<TouchButton> TouchRepeat::update(TouchContext current, std::optional<TouchButton> hovered,
                                               bool down, bool pressed, float seconds, bool ready) {
    if (context != current) {
        active.reset();
        blocked = down;
        context = current;
    }
    if (!down) {
        active.reset();
        repeat = {};
        blocked = false;
        return {};
    }
    if (context == TouchContext::Hidden || blocked)
        return {};
    if (pressed && hovered) {
        active = hovered;
        repeat = {};
    }
    if (!active)
        return {};
    if (!hovered) {
        active.reset();
        blocked = true;
        return {};
    }
    const bool changed = active != hovered;
    active = hovered;
    if (*active == TouchButton::Confirm)
        return pressed ? active : std::nullopt; // Confirm never repeats or fires on a slide.
    if (repeat.update(pressed || changed, true, seconds, true, ready)) {
        return active;
    }
    return {};
}

CanvasViewport window_viewport() {
    CanvasViewport view;
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    auto* window = glfwGetCurrentContext();
    glfwGetWindowSize(window, &view.window_width, &view.window_height);
    glfwGetFramebufferSize(window, &view.framebuffer_width, &view.framebuffer_height);
#elif defined(__ANDROID__)
    // raylib reports its requested virtual size on Android; the EGL surface owns the real pixels.
    EGLint width = GetRenderWidth(), height = GetRenderHeight();
    eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_WIDTH, &width);
    eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_HEIGHT, &height);
    view.window_width = view.framebuffer_width = width;
    view.window_height = view.framebuffer_height = height;
    const int density = AConfiguration_getDensity(GetAndroidApp()->config);
    if (density > 0 && density < ACONFIGURATION_DENSITY_ANY)
        view.touch_scale = density / 160.f;
#else
    view.window_width = GetScreenWidth();
    view.window_height = GetScreenHeight();
    view.framebuffer_width = GetRenderWidth();
    view.framebuffer_height = GetRenderHeight();
    view.touch_scale = EM_ASM_DOUBLE(
        { return Module['canvas'].width / Math.max(1, Module['canvas'].getBoundingClientRect().width); });
#endif
    view.window_width = std::max(1, view.window_width);
    view.window_height = std::max(1, view.window_height);
    float scale = std::min(view.window_width / float(CanvasWidth), view.window_height / float(CanvasHeight));
    float left = 0, right = float(view.window_width);
    if (touch_device() && view.window_width > view.window_height) {
        // Keep both the map and the right HUD clear of the thumb controls.
        right -= (3 * 48 + 2 * 4 + 16 + 8) * view.touch_scale;
#ifdef __EMSCRIPTEN__
        left = EM_ASM_DOUBLE({ return Module['tswGameLeftInset'] || 0; }) * view.touch_scale;
#endif
        scale = std::min(scale, std::max(.1f, (right - left) / CanvasWidth));
    }
    view.area = {std::clamp((view.window_width - CanvasWidth * scale) / 2, left,
                            std::max(left, right - CanvasWidth * scale)),
                 (view.window_height - CanvasHeight * scale) / 2, CanvasWidth * scale, CanvasHeight * scale};
#ifdef __EMSCRIPTEN__
    // The game texture and its final destination must share a physical pixel grid.
    // A fractional destination introduces a second resampling pass over small glyphs.
    view.area = {std::round(view.area.x), std::round(view.area.y), std::round(view.area.width),
                 std::round(view.area.height)};
    // Expose the actual letterboxing to the browser host, including compact phone layouts.
    EM_ASM(
        { Module['tswCanvasViewport'] = ({x : $0, y : $1, width : $2, height : $3}); },
        view.area.x / view.touch_scale, view.area.y / view.touch_scale, view.area.width / view.touch_scale,
        view.area.height / view.touch_scale);
#endif
    return view;
}

std::array<Rectangle, 6> touch_buttons(const CanvasViewport& view) {
    const float unit = view.touch_scale, size = 48 * unit, step = 52 * unit;
    const float x = view.window_width - 16 * unit - (2 * step + size);
    const float y = view.window_height - 16 * unit - (2 * step + size);
    return {{{x + step, y, size, size},
             {x, y + step, size, size},
             {x + step, y + step, size, size},
             {x + 2 * step, y + step, size, size},
             {x + step, y + 2 * step, size, size},
             {x + 2 * step, y, size, size}}};
}

std::optional<int> mouse_destination(const Game& game, const DesktopUi& ui, Vector2 mouse) {
    if ((!ui.mouse_walking && !ui.blink_mode) || ui.modal() || ui.replay_active || ui.flight >= 0 ||
        ui.ending_wait || game.busy() || mouse.x < BoardX || mouse.y < BoardY ||
        mouse.x >= BoardX + BoardPixels || mouse.y >= BoardY + BoardPixels)
        return {};
    return cell(int((mouse.x - BoardX) / TileSize), int((mouse.y - BoardY) / TileSize));
}

namespace {
constexpr int SideWidth = 156, FrameWidth = 488, RightX = SideWidth + FrameWidth;

constexpr bool is_orb(Item item) {
    return item == Item::HeroOrb || item == Item::WisdomOrb || item == Item::FlightOrb;
}

bool use_item_directly(Item item, const DesktopUi& ui) {
    return is_orb(item) || (ui.item_use_mode == ItemUseMode::OneClick && !item_definition(item).passive);
}

constexpr std::array<const char*, 3> ItemUseLabels{"Item use: Confirm", "Item use: Description + confirm",
                                                   "Item use: One-click"};

constexpr int DoorFrames = 16, TransformationFrames = 32, FirstHeroWalkingColor = 185;
constexpr int HeroSecondStepOffset = 2, HeroIdleOffset = 4;
constexpr Color Ink{246, 241, 230, 255}, Gold{247, 209, 138, 255}, Muted{199, 195, 197, 255};
constexpr Color Panel{57, 54, 63, 255}, Border{168, 145, 118, 255}, Bar{57, 56, 64, 255};
constexpr Rectangle Content{0, MenuHeight, CanvasWidth, ContentHeight};
constexpr Rectangle MapArea{BoardX, BoardY, BoardPixels, BoardPixels};
constexpr Rectangle EndingArea{80, MenuHeight + 50, 640, 400};

bool touch_button_enabled(TouchButton button, TouchContext context, bool busy) {
    if (context == TouchContext::Walk)
        return button != TouchButton::Confirm && button != TouchButton::Cancel && !busy;
    return context == TouchContext::Flight && button != TouchButton::Left && button != TouchButton::Right;
}

TouchContext touch_context(const Game& game, const DesktopUi& ui) {
    if (!ui.touch_enabled() || ui.modal() || ui.replay_active || ui.ending_wait ||
        (game.visual.raster_mode >= RasterMode::OpeningDissolve &&
         game.visual.raster_mode <= RasterMode::Title))
        return TouchContext::Hidden;
    if (game.dialogue)
        return game.dialogue->shop ? TouchContext::Shop : TouchContext::Dialogue;
    return ui.flight >= 0 ? TouchContext::Flight : TouchContext::Walk;
}

Rectangle sprite(int tile) {
    return {float((tile - 1) % 11 * TileSize), float((tile - 1) / 11 * TileSize), TileSize, TileSize};
}

bool clicked(Rectangle rect, Vector2 mouse) {
    return CheckCollisionPointRec(mouse, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

enum class TextAlignment { Center, Right };

struct TextOptions {
    TextAlignment alignment = TextAlignment::Center;
    bool bold{};
    bool translate = true;
};

struct Typography {
    struct Typeface {
        std::vector<unsigned char> bytes;
        mutable std::unordered_map<int, detail::UniqueFont> sizes;
        std::vector<int> codepoints;

        void load(const std::filesystem::path& path) {
            if (!std::filesystem::exists(path))
                return;
            std::ifstream input(path, std::ios::binary);
            if (input) {
                bytes.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
                // raylib initializes stb_truetype at byte zero. Windows CJK fonts
                // are collections; move the first face's directory to byte zero,
                // retaining its absolute table offsets and the original table data.
                if (bytes.size() >= 16 && std::equal(bytes.begin(), bytes.begin() + 4, "ttcf")) {
                    const auto be32 = [&](std::size_t at) {
                        return (std::uint32_t(bytes[at]) << 24) | (std::uint32_t(bytes[at + 1]) << 16) |
                               (std::uint32_t(bytes[at + 2]) << 8) | bytes[at + 3];
                    };
                    const auto offset = std::size_t(be32(12));
                    if (offset + 12 > bytes.size())
                        throw std::runtime_error("Invalid CJK font collection");
                    const auto tables = (int(bytes[offset + 4]) << 8) | bytes[offset + 5];
                    const auto size = std::size_t(12 + 16 * tables);
                    if (offset + size > bytes.size())
                        throw std::runtime_error("Invalid CJK font directory");
                    const std::vector<unsigned char> directory(bytes.begin() + offset,
                                                               bytes.begin() + offset + size);
                    std::ranges::copy(directory, bytes.begin());
                }
            }
        }

        Font at(int size, float scale) const {
            if (bytes.empty())
                return GetFontDefault();
            // Below nine physical pixels, outline-font strokes become nearly
            // transparent even before compositing on a small, low-density screen.
            const int pixels = std::max(9, int(std::round(size * scale)));
            auto& font = sizes[size];
            if (!font.get().texture.id || font.get().baseSize != pixels) {
                font.reset(
                    LoadFontFromMemory(".ttf", bytes.data(), int(bytes.size()), pixels,
                                       codepoints.empty() ? nullptr : const_cast<int*>(codepoints.data()),
                                       int(codepoints.size())));
                // Glyph alpha already contains antialiasing. Native pixel sampling avoids a second blur.
                SetTextureFilter(font.get().texture, TEXTURE_FILTER_POINT);
            }
            return font.get();
        }
    };

    Typeface body, numbers, japanese, chinese, labels;
    Language language = Language::English;
    Vector2 scale{1, 1};

    Typography() {
        body.load("assets/fonts/body.ttf");
        numbers.load("assets/fonts/body.ttf");
        japanese.load("assets/fonts/cjk.ttf");
        chinese.load("assets/fonts/cjk.ttf");
        labels.load("assets/fonts/labels.otf");
#ifdef __EMSCRIPTEN__
        // The startup subset also contains ASCII. Rasterize English at its actual
        // display size instead of shrinking raylib's built-in bitmap glyphs.
        if (body.bytes.empty())
            body.load("assets/fonts/labels.otf");
        if (numbers.bytes.empty())
            numbers.load("assets/fonts/labels.otf");
#endif
#ifdef __ANDROID__
        if (body.bytes.empty())
            body.load("/system/fonts/Roboto-Regular.ttf");
        if (numbers.bytes.empty())
            numbers.load("/system/fonts/Roboto-Bold.ttf");
        if (japanese.bytes.empty())
            japanese.load("/system/fonts/NotoSansCJK-Regular.ttc");
        if (chinese.bytes.empty())
            chinese.load("/system/fonts/NotoSansCJK-Regular.ttc");
#endif
        // Use installed Windows fonts when available; no fonts or Windows APIs are bundled.
        if (const char* windows = std::getenv("WINDIR")) {
            const auto directory = std::filesystem::path(windows) / "Fonts";
            body.load(directory / "seguisb.ttf");
            numbers.load(directory / "segoeuib.ttf");
            japanese.load(directory / "YuGothR.ttc");
            if (japanese.bytes.empty())
                japanese.load(directory / "msgothic.ttc");
            chinese.load(directory / "msyh.ttc");
        }
        // An optional user-supplied CJK face also supports portable builds.
        if (const char* path = std::getenv("TSW_CJK_FONT")) {
            japanese.load(path);
            chinese.load(path);
        }
        japanese.codepoints = chinese.codepoints = localization_codepoints();
        for (const auto item : Languages) {
            int count{};
            auto* points = LoadCodepoints(std::string(language_label(item)).c_str(), &count);
            for (int i = 0; i < count; ++i)
                if (std::ranges::find(labels.codepoints, points[i]) == labels.codepoints.end())
                    labels.codepoints.push_back(points[i]);
            UnloadCodepoints(points);
        }
    }

    void select_language(Language selected) {
        language = selected;
#ifdef __EMSCRIPTEN__
        const int ready = EM_ASM_INT(
            { return Module['tswFonts']['ensure'](UTF8ToString($0)); }, language_id(selected).data());
        // Keep every scene readable while a language font is in flight or awaiting retry.
        if (ready != 1) {
            language = Language::English;
            return;
        }
        if (selected == Language::Japanese && japanese.bytes.empty())
            japanese.load("/fonts/ja.otf");
        else if ((selected == Language::ChineseFromJapanese || selected == Language::ChineseFromEnglish) &&
                 chinese.bytes.empty())
            chinese.load("/fonts/zh.otf");
#endif
    }

    Font font(int size, bool bold = false, std::string_view value = {}) const {
        if (!labels.bytes.empty() &&
            std::ranges::any_of(Languages, [&](Language item) { return value == language_label(item); }))
            return labels.at(size, scale.y);
        const bool unicode = std::ranges::any_of(value, [](unsigned char c) { return c >= 128; });
        if (unicode) {
            const bool chinese_label = value == language_label(Language::ChineseFromJapanese) ||
                                       value == language_label(Language::ChineseFromEnglish);
            const auto& face = (language == Language::Japanese && !chinese_label) ? japanese : chinese;
            if (!face.bytes.empty())
                return face.at(size, scale.y);
        }
        // Some Android images provide Roboto-Regular without a separate bold face.
        // Keep both weights in the loaded family when either face is unavailable.
        const auto& preferred = bold ? numbers : body;
        const auto& fallback = bold ? body : numbers;
        return (preferred.bytes.empty() ? fallback : preferred).at(size, scale.y);
    }

    float font_size(Font face, int size) const {
        return face.texture.id == GetFontDefault().texture.id ? float(size) : face.baseSize / scale.y;
    }

    float spacing(Font face, int size) const {
        // The built-in bitmap face needs a gap between glyphs at each scaled size.
        return face.texture.id == GetFontDefault().texture.id ? std::max(1.f, size / 10.f) : 0.f;
    }

    Vector2 position(float x, float y) const {
        return {std::round(x * scale.x) / scale.x, std::round(y * scale.y) / scale.y};
    }

    void outline(Rectangle rect, float thickness, Color color) const {
        const auto top = position(rect.x, rect.y);
        const auto bottom = position(rect.x + rect.width, rect.y + rect.height);
        const float width = bottom.x - top.x, height = bottom.y - top.y;
        const float dx = std::max(1.f, std::round(thickness * scale.x)) / scale.x;
        const float dy = std::max(1.f, std::round(thickness * scale.y)) / scale.y;
        DrawRectangleRec({top.x, top.y, width, dy}, color);
        DrawRectangleRec({top.x, bottom.y - dy, width, dy}, color);
        DrawRectangleRec({top.x, top.y, dx, height}, color);
        DrawRectangleRec({bottom.x - dx, top.y, dx, height}, color);
    }

    void clip(Rectangle rect) const {
        const int x = int(std::floor(rect.x * scale.x)), y = int(std::floor(rect.y * scale.y));
        BeginScissorMode(x, y, int(std::ceil((rect.x + rect.width) * scale.x)) - x,
                         int(std::ceil((rect.y + rect.height) * scale.y)) - y);
    }

    int width(const std::string& value, int size, bool bold = false) const {
        const auto face = font(size, bold, value);
        return int(
            std::ceil(MeasureTextEx(face, value.c_str(), font_size(face, size), spacing(face, size)).x));
    }

    void draw(const std::string& value, int x, int y, int size, Color color = Ink,
              bool translate = true) const {
        const auto text = translate ? localized_text(language, value) : value;
        const auto face = font(size, false, text);
        std::istringstream lines(text);
        std::string line;
        while (std::getline(lines, line)) {
            DrawTextEx(face, line.c_str(), position(float(x), float(y)), font_size(face, size),
                       spacing(face, size), color);
            y += std::max(22, size + 2);
        }
    }

    std::string wrap(const std::string& text, int limit, int size, bool translate = true) const {
        return wrap_localized_text(
            translate ? localized_text(language, text) : text, float(limit),
            [&](std::string_view line) { return float(width(std::string(line), size)); });
    }

    void fit(const std::string& value, Rectangle rect, int size, Color color = Ink,
             TextOptions options = {}) const {
        const auto text = options.translate ? localized_text(language, value) : value;
        while (size > 10 && width(text, size, options.bold) > rect.width - 6)
            --size;
        clip(rect);
        const int measured = width(text, size, options.bold);
        const auto face = font(size, options.bold, text);
        DrawTextEx(
            face, text.c_str(),
            position(rect.x + (options.alignment == TextAlignment::Right ? rect.width - measured - 3
                                                                         : (rect.width - measured) / 2),
                     rect.y + (rect.height - font_size(face, size)) / 2),
            font_size(face, size), spacing(face, size), color);
        EndScissorMode();
    }

    void badge(const std::string& value, Rectangle rect, int size, Color color) const {
        if (value == "∞") {
            // Keep the blocked-defense symbol legible even with a fallback font.
            const auto point = [&](int segment) {
                const float angle = segment * 2 * PI / 32;
                return Vector2{rect.x + rect.width / 2 + 7 * std::sin(angle),
                               rect.y + rect.height / 2 + 3 * std::sin(angle * 2)};
            };
            for (int pass = 0; pass < 2; ++pass)
                for (int segment = 0; segment < 32; ++segment)
                    DrawLineEx(point(segment), point(segment + 1), pass ? 1.5f : 3.f,
                               pass ? color : Color{16, 15, 22, 255});
            return;
        }
        while (size > 9 && width(value, size, true) > rect.width - 2)
            --size;
        const auto face = font(size, true, value);
        const float x = rect.x + (rect.width - width(value, size, true)) / 2;
        const float y = rect.y + (rect.height - size) / 2;
        clip(rect);
        for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}})
            DrawTextEx(face, value.c_str(), position(x + dx, y + dy), font_size(face, size),
                       spacing(face, size), Color{16, 15, 22, 255});
        DrawTextEx(face, value.c_str(), position(x, y), font_size(face, size), spacing(face, size), color);
        EndScissorMode();
    }

    bool button(Rectangle rect, const std::string& label, Vector2 mouse, bool enabled = true) const {
        const bool hover = enabled && CheckCollisionPointRec(mouse, rect);
        DrawRectangleRec(rect, hover ? Color{89, 78, 75, 255} : Panel);
        fit(label, rect, 18, enabled ? Ink : Color{145, 140, 143, 255});
        outline(rect, 1, enabled ? Border : Color{99, 93, 94, 255});
        return enabled && clicked(rect, mouse);
    }

    void modal(Rectangle rect, const std::string& title) const {
        DrawRectangleRec(MapArea, Color{0, 0, 0, 130});
        DrawRectangle(int(rect.x + 4), int(rect.y + 5), int(rect.width), int(rect.height),
                      Color{0, 0, 0, 170});
        DrawRectangleRec(rect, Panel);
        outline(rect, 2, Border);
        draw(title, int(rect.x + 18), int(rect.y + 16), 21, Gold);
        DrawLine(int(rect.x + 18), int(rect.y + 45), int(rect.x + rect.width - 18), int(rect.y + 45), Border);
    }

    void tooltip(Rectangle anchor, const std::string& text) const {
        const auto wrapped = wrap(text, 300, 16);
        const float height = 20 + 22 * float(std::ranges::count(wrapped, '\n'));
        const float x = std::clamp(anchor.x + anchor.width - 324, 8.f, CanvasWidth - 332.f);
        const float y = anchor.y + anchor.height + 6 + height < CanvasHeight - 8
                            ? anchor.y + anchor.height + 6
                            : anchor.y - height - 6;
        const Rectangle rect{x, y, 324, height};
        DrawRectangleRec(rect, Color{38, 35, 43, 255});
        outline(rect, 1, Gold);
        draw(wrapped, int(x + 12), int(y + 10), 16, Ink, false);
    }
};

constexpr const char* DissolveShader =
#if defined(__ANDROID__) || defined(__EMSCRIPTEN__)
    R"(#version 100
precision mediump float;
varying vec2 fragTexCoord;
varying vec4 fragColor;
#define texture texture2D
#define finalColor gl_FragColor
)"
#else
    R"(#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;
)"
#endif
    R"(
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
    detail::UniqueImage atlas_image, background_image;
    detail::UniqueTexture atlas;
    std::unordered_map<int, detail::UniqueTexture> masked, icons;
    std::unordered_map<std::string, detail::UniqueTexture> scenes;

    explicit Art(const Assets& assets) {
        atlas_image.reset(assets.image("original-atlas"));
        background_image.reset(assets.image("original-background-atlas"));
        if (atlas_image.get().width != 440 || atlas_image.get().height != 800 ||
            background_image.get().width != 440 || background_image.get().height != 600)
            throw std::runtime_error("Original color and mask atlases have unexpected dimensions.");
        atlas.reset(LoadTextureFromImage(atlas_image.get()));
        if (!IsTextureValid(atlas.get()))
            throw std::runtime_error("Unable to upload original atlas");
        for (const auto name : SceneImageNames) {
            detail::UniqueImage image(assets.image(name));
            detail::UniqueTexture texture(LoadTextureFromImage(image.get()));
            if (!IsTextureValid(texture.get()))
                throw std::runtime_error("Unable to upload original scene artwork: " + std::string(name));
            scenes.emplace(std::string(name), std::move(texture));
        }
    }

    void tile(int value, int x, int y) const {
        if (value > 0 && value <= 220)
            DrawTextureRec(atlas.get(), sprite(value), {float(x), float(y)}, WHITE);
        else
            DrawRectangle(x, y, TileSize, TileSize, BLACK);
    }

    void part(int value, Rectangle source, int x, int y) const {
        if (source.width <= 0 || source.height <= 0)
            return;
        const auto origin = sprite(value);
        source.x += origin.x;
        source.y += origin.y;
        DrawTextureRec(atlas.get(), source, {float(x), float(y)}, WHITE);
    }

    Texture2D transparent(int color, int mask, bool background = false) {
        auto& textures = background ? icons : masked;
        const int key = color * 256 + mask;
        if (auto found = textures.find(key); found != textures.end())
            return found->second.get();
        detail::UniqueImage colored(ImageFromImage(atlas_image.get(), sprite(color)));
        detail::UniqueImage alpha(
            ImageFromImage(background ? background_image.get() : atlas_image.get(), sprite(mask)));
        ImageColorInvert(alpha.address());
        ImageAlphaMask(colored.address(), alpha.get());
        detail::UniqueTexture texture(LoadTextureFromImage(colored.get()));
        const auto borrowed = texture.get();
        textures.emplace(key, std::move(texture));
        return borrowed;
    }

    void icon(int value, Rectangle target, Color tint = WHITE) {
        DrawTexturePro(transparent(value, value, true), {0, 0, TileSize, TileSize}, target, {0, 0}, 0, tint);
    }

    bool collection_button(Rectangle rect, bool except_potions, Vector2 mouse, bool enabled) {
        const bool hover = enabled && CheckCollisionPointRec(mouse, rect);
        const Color tint = enabled ? WHITE : Color{112, 112, 112, 255};
        const Color light{183, 182, 187, 255}, shadow{38, 35, 43, 255};
        DrawRectangleRec(rect, hover ? Color{115, 112, 121, 255} : Color{87, 85, 93, 255});
        DrawRectangleRec({rect.x, rect.y, rect.width, 1}, light);
        DrawRectangleRec({rect.x, rect.y, 1, rect.height}, light);
        DrawRectangleRec({rect.x, rect.y + rect.height - 1, rect.width, 1}, shadow);
        DrawRectangleRec({rect.x + rect.width - 1, rect.y, 1, rect.height}, shadow);
        // Use the original atlas at whole-pixel coordinates, like the inventory itself.
        icon(YellowKey, {rect.x + 2, rect.y + 2, 23, 23}, tint);
        icon(RedGem, {rect.x + 23, rect.y + 3, 15, 19}, tint);
        icon(RedPotion, {rect.x + 22, rect.y + 21, 17, 18}, tint);
        constexpr std::array<std::string_view, 7> arrow{"  #  ", "  #  ", "#####", " ### ",
                                                        "  #  ", "#   #", "#####"};
        for (int y = 0; y < int(arrow.size()); ++y)
            for (int x = 0; x < int(arrow[y].size()); ++x)
                if (arrow[y][x] == '#')
                    DrawRectangle(int(rect.x) + 6 + x * 2, int(rect.y) + 23 + y * 2, 2, 2,
                                  enabled ? Ink : Muted);
        if (except_potions) {
            // A stepped slash stays crisp on the same pixel grid as the flask.
            for (int i = 0; i < 12; ++i)
                DrawRectangle(int(rect.x) + 24 + i, int(rect.y) + 35 - i, 4, 4, shadow);
            for (int i = 0; i < 12; ++i)
                DrawRectangle(int(rect.x) + 25 + i, int(rect.y) + 36 - i, 2, 2, enabled ? Ink : Muted);
        }
        if (hover) {
            text.outline({rect.x - 1, rect.y - 1, rect.width + 2, rect.height + 2}, 1, Gold);
#ifndef __ANDROID__
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
#endif
        }
        return enabled && clicked(rect, mouse);
    }

    void scene(const std::string& name, Rectangle target) const {
        const auto found = scenes.find(name);
        if (found == scenes.end())
            throw std::runtime_error("Missing scene: " + name);
        const auto texture = found->second.get();
        DrawTexturePro(texture, {0, 0, float(texture.width), float(texture.height)}, target, {0, 0}, 0,
                       WHITE);
    }
};

Presentation::Presentation(const Assets& assets) : art_(std::make_unique<Art>(assets)) {
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    // GLFW cursor events already use the window units consumed by window_viewport().
    // Raylib's HiDPI startup scale would shrink them again before canvas_point().
    SetMouseScale(1, 1);
#endif
#ifdef __ANDROID__
    // raylib exposes cancellation as a release; retain the distinction for conversation taps.
    auto* app = GetAndroidApp();
    if (app->onInputEvent != track_android_pointer) {
        android_input_handler = app->onInputEvent;
        app->onInputEvent = track_android_pointer;
        android_pointer_cancelled = false;
    }
#endif
    resize_canvas(window_viewport());
    scene_cache_.reset(LoadRenderTexture(CanvasWidth, ContentHeight));
    SetTextureFilter(scene_cache_.get().texture, TEXTURE_FILTER_POINT);
    dissolve_.reset(LoadShaderFromMemory(nullptr, DissolveShader));
    dissolve_mask_location_ = GetShaderLocation(dissolve_.get(), "maskOrigin");
    if (!IsRenderTextureValid(canvas_.get()) || !IsRenderTextureValid(scene_cache_.get()) ||
        dissolve_mask_location_ < 0)
        throw std::runtime_error("Could not create the game canvas or scene compositor.");
    BeginTextureMode(canvas_.get());
    ClearBackground(BLACK);
    EndTextureMode();
}

void Presentation::resize_canvas(const CanvasViewport& view) {
    const int width =
        std::max(1, int(std::round(view.area.width * view.framebuffer_width / view.window_width)));
    const int height =
        std::max(1, int(std::round(view.area.height * view.framebuffer_height / view.window_height)));
    if (canvas_.get().texture.width == width && canvas_.get().texture.height == height)
        return;
    detail::UniqueRenderTexture resized(LoadRenderTexture(width, height));
    if (!IsRenderTextureValid(resized.get()))
        throw std::runtime_error("Could not resize the game canvas");
    SetTextureFilter(resized.get().texture, TEXTURE_FILTER_POINT);
    BeginTextureMode(resized.get());
    ClearBackground(BLACK);
    if (canvas_.get().id)
        DrawTexturePro(canvas_.get().texture,
                       {0, 0, float(canvas_.get().texture.width), -float(canvas_.get().texture.height)},
                       {0, 0, float(width), float(height)}, {0, 0}, 0, WHITE);
    EndTextureMode();
    canvas_ = std::move(resized);
    art_->text.scale = {width / float(CanvasWidth), height / float(CanvasHeight)};
}

Presentation::~Presentation() = default;

void Presentation::reset() {
    touch_ = {};
    touch_context_ = TouchContext::Hidden;
    dialogue_dragging_ = false;
    hide_panels_ = cache_requested_ = cache_valid_ = false;
    previous_raster_ = RasterMode::Inactive;
    walking_remaining_ = 0;
    animation_seconds_ = 0;
    collected_.clear();
    collection_age_ = 0;
}

void Presentation::moved(const Hero& before, const Hero& after, bool manual) {
    if (before.floor == after.floor && before.x == after.x && before.y == after.y)
        return;
    // Teleports and floor changes must never slide across intervening tiles.
    if (before.floor != after.floor || abs(before.x - after.x) + abs(before.y - after.y) != 1) {
        walking_remaining_ = 0;
        return;
    }
    const float remaining = walking_remaining_ / WalkAnimationSeconds;
    const bool continuing =
        walking_floor_ == before.floor && walking_x_ == before.x && walking_y_ == before.y;
    walking_offset_ = {float(before.x - after.x) + (continuing ? walking_offset_.x * remaining : 0.f),
                       float(before.y - after.y) + (continuing ? walking_offset_.y * remaining : 0.f)};
    walking_floor_ = after.floor;
    walking_x_ = after.x;
    walking_y_ = after.y;
    manual_walking_ = manual;
    walking_remaining_ = WalkAnimationSeconds;
}

void Presentation::collected(int floor, const std::vector<CollectedItem>& items) {
    collection_floor_ = floor;
    collected_ = items;
    collection_age_ = 0;
}

void Presentation::advance(float seconds, float real_seconds) {
    const float walk_seconds = manual_walking_ && real_seconds >= 0 ? real_seconds : seconds;
    walking_remaining_ = std::max(0.f, walking_remaining_ - walk_seconds);
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
    const int width = canvas_.get().texture.width;
    const int height = std::max(1, int(std::round(ContentHeight * art_->text.scale.y)));
    if (scene_cache_.get().texture.width != width || scene_cache_.get().texture.height != height) {
        detail::UniqueRenderTexture resized(LoadRenderTexture(width, height));
        if (!IsRenderTextureValid(resized.get()))
            throw std::runtime_error("Could not resize the scene cache");
        scene_cache_ = std::move(resized);
        SetTextureFilter(scene_cache_.get().texture, TEXTURE_FILTER_POINT);
    }
    BeginTextureMode(scene_cache_.get());
    ClearBackground(BLACK);
    // Render textures are vertically inverted; preserve the content below the menu.
    DrawTexturePro(canvas_.get().texture,
                   {0, StatusHeight * art_->text.scale.y, float(width), -ContentHeight * art_->text.scale.y},
                   {0, 0, float(width), float(height)}, {0, 0}, 0, WHITE);
    EndTextureMode();
    cache_requested_ = false;
    cache_valid_ = true;
}

void Presentation::draw_door(const Game& game, int x, int y) {
    const auto& visual = game.visual;
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
        art_->tile(Lava + int(animation_seconds_ * 2) % 2 * game.animation_offset(Lava), x, y);
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
        value += animation * game.animation_offset(value);
        art_->tile(value, x, y);
        if (!active)
            continue;
        const auto& layer = v.layers[index];
        if (layer.underlying >= 0) {
            art_->tile(layer.underlying, x, y);
            DrawTexture(art_->transparent(layer.color, layer.mask), x, y, WHITE);
        }
        if (v.door_cell == index)
            draw_door(game, x, y);
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
        const bool sliding =
            !source_board && walking_floor_ == floor && walking_x_ == hero_x && walking_y_ == hero_y;
        const float remaining = sliding ? walking_remaining_ / WalkAnimationSeconds : 0.f;
        DrawTexture(art_->transparent(pose, pose + 1),
                    BoardX + int(std::round((hero_x + walking_offset_.x * remaining) * TileSize)),
                    BoardY + int(std::round((hero_y + walking_offset_.y * remaining) * TileSize)), WHITE);
    }
    if (active && v.raster_mode == RasterMode::VampireTransformation)
        draw_transformation(game, animation);
    if (active && floor == collection_floor_ && !v.hide_hero && !v.dead &&
        v.raster_mode == RasterMode::Inactive) {
        for (std::size_t i = 0; i < collected_.size(); ++i) {
            const float delay = .16f * float(i) / float(collected_.size());
            const float progress = std::clamp((collection_age_ - delay) / .46f, 0.f, 1.f);
            if (progress >= 1)
                continue;
            const auto& item = collected_[i];
            const float ease = 1 - (1 - progress) * (1 - progress);
            const float x =
                float(item.position % BoardWidth) + (game.hero.x - float(item.position % BoardWidth)) * ease;
            const float y =
                float(item.position / BoardWidth) + (game.hero.y - float(item.position / BoardWidth)) * ease;
            const float size = TileSize * (1 - .45f * progress);
            const float arc = std::sin(progress * PI) * 24;
            art_->icon(item.tile,
                       {BoardX + x * TileSize + (TileSize - size) / 2,
                        BoardY + y * TileSize + (TileSize - size) / 2 - arc, size, size},
                       Fade(WHITE, 1 - .3f * progress));
        }
    }
}

void Presentation::draw_realtime_orb(const Game& game, const DesktopUi& ui) {
    if (!ui.realtime_hero_orb || !game.inventory(Item::HeroOrb) || ui.modal() || ui.flight >= 0 ||
        game.busy() || game.visual.raster_mode != RasterMode::Inactive)
        return;
    for (int index = 0; index < CellCount; ++index) {
        const auto info = orb_tile_info(game, game.hero.floor, index, ui.hero_orb_actual_damage);
        if (!info)
            continue;
        const float x = float(BoardX + index % BoardWidth * TileSize);
        const float y = float(BoardY + index / BoardWidth * TileSize);
        const auto& forecast = info->forecast;
        const Color cost_color = !forecast.penetrates              ? Color{212, 171, 255, 255}
                                 : forecast.damage >= game.hero.hp ? Color{255, 118, 118, 255}
                                 : forecast.damage                 ? Color{255, 222, 148, 255}
                                                                   : Color{139, 245, 174, 255};
        const auto cost = !forecast.penetrates ? "∞"
                          : forecast.damage    ? "-" + compact_orb_number(forecast.damage)
                                               : "0";
        art_->text.badge(cost, {x + 1, y, 38, 12}, 12, cost_color);
        art_->text.badge(compact_orb_number(info->attack), {x, y + 18, 20, 10}, 10,
                         Color{255, 174, 133, 255});
        art_->text.badge(compact_orb_number(info->defense), {x + 20, y + 18, 20, 10}, 10,
                         Color{142, 210, 255, 255});
        art_->text.badge("+" + compact_orb_number(info->gold), {x + 1, y + 28, 38, 12}, 10, Gold);
    }
}

void Presentation::draw_scene(const Game& game) {
    const auto mode = game.visual.raster_mode;
    const int frame = game.visual.raster_frame;
    if (mode == RasterMode::Title) {
        art_->scene(game.hero.cycle_factor_minus_one ? "data3-title05r" : "data3-title05",
                    {SideWidth, MenuHeight, FrameWidth, ContentHeight});
    } else if (mode == RasterMode::OpeningDissolve || mode == RasterMode::EndingDissolve) {
        if (cache_valid_)
            DrawTexturePro(
                scene_cache_.get().texture,
                {0, 0, float(scene_cache_.get().texture.width), -float(scene_cache_.get().texture.height)},
                Content, {0, 0}, 0, WHITE);
        const auto mask = sprite(std::clamp(frame - 66 + 1, DissolveFirstMask, DissolveLastMask));
        const Vector2 origin{mask.x / art_->atlas.get().width, mask.y / art_->atlas.get().height};
        SetShaderValue(dissolve_.get(), dissolve_mask_location_, &origin, SHADER_UNIFORM_VEC2);
        BeginShaderMode(dissolve_.get());
        SetShaderValueTexture(dissolve_.get(), GetShaderLocation(dissolve_.get(), "maskAtlas"),
                              art_->atlas.get());
        art_->scene(mode == RasterMode::OpeningDissolve ? "data3-open1" : "data3-open0", Content);
        EndShaderMode();
    } else if (mode == RasterMode::OpeningStory) {
        art_->scene("data3-open1", Content);
        art_->text.clip({0, MenuHeight, CanvasWidth, float(std::clamp(frame, 0, ContentHeight))});
        if (art_->text.language == Language::English)
            art_->scene("data3-open2", Content);
        else {
            const auto opening =
                wrap_localized_text(localized_opening(art_->text.language), 650, [&](std::string_view line) {
                    return float(art_->text.width(std::string(line), 32));
                });
            const int lines = int(std::ranges::count(opening, '\n'));
            float y = Content.y + (Content.height - lines * 44) / 2;
            std::istringstream paragraphs(opening);
            for (std::string line; std::getline(paragraphs, line); y += 44)
                art_->text.fit(line, {75, y, 650, 44}, 32, WHITE, {.translate = false});
        }
        EndScissorMode();
    } else if (mode == RasterMode::EndingImages) {
        if (frame == 1)
            art_->scene("data3-open0", Content);
        else {
            const int image = std::clamp(frame + 3, 5, 20);
            art_->scene(std::format("data2-end{:02}", image), Content);
        }
    } else if (mode == RasterMode::EndingShrink) {
        DrawRectangleRec(Content, BLACK);
        if (frame < 400) {
            const float inset_y = std::clamp(frame / 2.f, 0.f, 200.f), inset_x = inset_y * 640 / 400;
            art_->scene("data2-end20", {EndingArea.x + inset_x, EndingArea.y + inset_y,
                                        EndingArea.width - 2 * inset_x, EndingArea.height - 2 * inset_y});
        } else
            art_->scene("data2-end26", Content);
    } else if (mode == RasterMode::EndingStory) {
        art_->scene("data2-end26", Content);
        art_->text.clip({EndingArea.x, EndingArea.y, EndingArea.width, float(std::clamp(frame, 0, 400))});
        if (art_->text.language == Language::English)
            art_->scene("data-exe-ending-story", EndingArea);
        else {
            DrawRectangleRec(EndingArea, WHITE);
            const auto story =
                wrap_localized_text(localized_ending(art_->text.language), 610, [&](std::string_view line) {
                    return float(art_->text.width(std::string(line), 24));
                });
            const int lines = int(std::ranges::count(story, '\n'));
            float y = EndingArea.y + std::max(8.f, (EndingArea.height - lines * 28) / 2);
            std::istringstream paragraphs(story);
            for (std::string line; std::getline(paragraphs, line); y += 28)
                art_->text.fit(line, {EndingArea.x + 15, y, 610, 28}, 24, BLACK, {.translate = false});
        }
        EndScissorMode();
    } else if (mode == RasterMode::EndingCard || mode == RasterMode::ClosingCard) {
        art_->scene("data-exe-ending-card", Content);
    }
}

float command_interval(const Game& game) {
    // Presentation pacing only; the command stack and gameplay order stay unchanged.
    switch (game.visual.raster_mode) {
    case RasterMode::OpeningDissolve:
    case RasterMode::EndingDissolve:
        return .05f;
    case RasterMode::OpeningStory:
        return .015f;
    case RasterMode::EndingShrink:
        return .05f;
    case RasterMode::EndingStory:
        return .03f;
    case RasterMode::EndingImages:
        return .225f;
    case RasterMode::EndingCard:
    case RasterMode::ClosingCard:
        return .3f;
    case RasterMode::Title:
        return .06f;
    default:
        return game.visual.battle ? .06f : .016f;
    }
}

bool CommandPlayback::advance(Game& game, float seconds, const DesktopUi& ui,
                              const std::function<bool(const Command&)>& observe) {
    accumulator_ += seconds;
    int paced = 0;
    for (int commands = 0; commands < 1024 && paced < 64; ++commands) {
        if (!game.visual.battle && !finishing_battle_)
            strike_pending_ = battle_preview_shown_ = false;
        const bool fast_battle =
            ui.skip_attack_animation && ((battle_preview_shown_ && game.visual.battle) || finishing_battle_);
        const bool fast_stairs = ui.skip_staircase_animation && game.visual.stair_source_floor >= 0;
        if (fast_battle)
            game.skip_battle_rounds();
        const float beat = fast_battle || fast_stairs ? 0.f : command_interval(game);
        if (accumulator_ < beat)
            break;
        Command command;
        if (!game.run_one(&command)) {
            reset();
            return true;
        }
        accumulator_ -= beat;
        paced += beat > 0;
        if (command.op == Op::HeroStrike || command.op == Op::EnemyStrike)
            strike_pending_ = true;
        else if (command.op == Op::Wait && strike_pending_) {
            strike_pending_ = false;
            battle_preview_shown_ = true;
        }
        if (fast_battle && command.op == Op::Callback && command.a == int(Callback::BattleEnd))
            finishing_battle_ = true;
        if (command.op == Op::Callback && command.a == int(Callback::CheckGuards) && command.b == 5)
            finishing_battle_ = strike_pending_ = battle_preview_shown_ = false;
        if (observe && !observe(command)) {
            accumulator_ = 0;
            break;
        }
    }
    return false;
}

UiAction Presentation::draw_panels(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto& h = game.hero;
    art_->text.fit(std::format("Tower {}", ui.flight >= 0 ? ui.flight : h.floor),
                   {18, MenuHeight + 59, 124, 24}, 22, Ink, {.bold = true});
    for (int i = 0; i < 4; ++i)
        art_->text.fit(std::to_string(std::array<int, 4>{h.hp, h.attack, h.defense, h.gold}[i]),
                       {50, float(MenuHeight + 101 + i * 29), 92, 22}, 21, i == 3 ? Gold : Ink,
                       {.alignment = TextAlignment::Right, .bold = true});
    art_->text.draw("ITEMS", 17, MenuHeight + 219, 14, Panel);
    if (art_->text.button({102, MenuHeight + 215, 40, 19}, "[I]", mouse,
                          !game.busy() && ui.flight < 0 && !ui.modal()))
        ui.inventory = true;
    UiAction action;
    int owned = 0;
    for (int i = 0; i < ItemCount; ++i) {
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
            art_->text.fit(label, {rect.x + 18, rect.y + 24, 23, 15}, 12, Gold,
                           {.alignment = TextAlignment::Right});
        }
        if (hover && !game.busy() && clicked(rect, mouse)) {
            if (use_item_directly(item, ui))
                action = {Action::UseItem, i};
            else
                ui.selected_item = i;
        }
        ++owned;
    }
    constexpr std::array<const char*, 6> EquipmentNames{"None", "Iron", "Silver", "Knight", "Holy", "Sacred"};
    for (int i = 0; i < 2; ++i) {
        const int equipment =
            std::clamp(std::to_underlying(i == 0 ? h.sword : h.shield), 0, EquipmentTierCount);
        if (art_->text.language != Language::English) {
            const Rectangle label{RightX + 12, float(MenuHeight + 59 + i * 60), 82, 22};
            DrawRectangleRec(label, Panel);
            art_->text.fit(i == 0 ? "Weapon" : "Shield", label, 17, Gold);
        }
        art_->text.fit(EquipmentNames[equipment], {RightX + 12, float(MenuHeight + 80 + i * 60), 82, 23}, 19);
        if (equipment)
            art_->icon((i == 0 ? IronSword : IronShield) + equipment - 1,
                       {RightX + 100, float(MenuHeight + 60 + i * 60), 40, 40});
    }
    for (int i = 0; i < 3; ++i) {
        const int count = std::array<int, 3>{h.yellow_keys, h.blue_keys, h.red_keys}[i];
        art_->icon(std::array<int, 3>{YellowKey, BlueKey, RedKey}[i],
                   {RightX + 17, float(MenuHeight + 181 + i * 26), 25, 25});
        art_->text.fit(std::to_string(count), {RightX + 52, float(MenuHeight + 183 + i * 26), 80, 23}, 20,
                       Ink, {.alignment = TextAlignment::Right});
    }
    if (ui.flight >= 0) {
        DrawRectangle(RightX + 12, MenuHeight + 278, 128, 162, Color{102, 102, 102, 255});
        if (ui.touch_enabled()) {
            DrawRectangle(RightX + 7, 306, 144, 214, Panel);
            art_->text.fit("ORB OF FLIGHT", {RightX + 9, 306, 140, 20}, 15, Gold);
            art_->text.fit(std::format("Floor {}", ui.flight), {RightX + 9, 327, 140, 20}, 18);
            if (art_->text.button({RightX + 9, 348, 140, 24}, "Cancel", mouse))
                action = {Action::CancelFlight};
            return action;
        }
        art_->text.fit("ORB OF FLIGHT", {RightX + 12, MenuHeight + 282, 128, 22}, 15, Gold);
        art_->text.fit(std::format("Floor {}", ui.flight), {RightX + 12, MenuHeight + 311, 128, 24}, 19);
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
                                          : std::format("Damage {}", enemy->damage),
                       {RightX + 58, MenuHeight + 305, 80, 22}, 17);
        art_->text.fit(std::string(Game::monster_name(enemy->monster_index)),
                       {RightX + 12, MenuHeight + 338, 128, 22}, 18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(std::to_string(std::array<int, 3>{monster.hp, monster.attack, monster.defense}[i]),
                           {RightX + 52, float(MenuHeight + 366 + i * 24), 85, 22}, 20, Ink,
                           {.alignment = TextAlignment::Right});
    } else {
        art_->text.fit("Defeated enemies", {RightX + 12, MenuHeight + 284, 128, 24}, 16, Muted);
        art_->text.fit("appear here", {RightX + 12, MenuHeight + 308, 128, 24}, 16, Muted);
        art_->text.fit("The Name", {RightX + 12, MenuHeight + 338, 128, 22}, 18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(std::array<const char*, 3>{"Life", "Offense", "Defense"}[i],
                           {RightX + 52, float(MenuHeight + 366 + i * 24), 85, 22}, 18);
    }
    if (h.fairy_visits)
        art_->text.fit(std::format("Fairy rank {}", h.fairy_rank), {RightX + 12, MenuHeight + 453, 128, 20},
                       13, Panel);
    if (ui.item_collection) {
        const bool can_collect = !game.busy() && !ui.modal() && !ui.replay_active && !ui.ending_wait &&
                                 game.visual.raster_mode == RasterMode::Inactive && !collecting();
        constexpr Rectangle all{28, 480, 40, 40}, except{88, 480, 40, 40};
        DrawRectangle(22, 476, 112, 48, Panel);
        art_->text.outline({22, 476, 112, 48}, 1, Border);
        if (art_->collection_button(all, false, mouse, can_collect))
            action = {Action::CollectAll};
        if (art_->collection_button(except, true, mouse, can_collect))
            action = {Action::CollectExceptPotions};
        if (can_collect && CheckCollisionPointRec(mouse, all))
            art_->text.tooltip(
                all,
                localized_text(ui.language, "Zuck all") + "\n" +
                    localized_text(ui.language,
                                   "Collect safely reachable items on this floor. Doors, monsters, hidden "
                                   "events and hazards block collection. The hero stays in place."));
        if (can_collect && CheckCollisionPointRec(mouse, except))
            art_->text.tooltip(
                except, localized_text(ui.language, "Zuck all except potion") + "\n" +
                            localized_text(ui.language,
                                           "Collect safely reachable items, leaving red and blue potions "
                                           "untouched. Skipped potions also block collection beyond them."));
    }
    return action;
}

UiAction Presentation::draw_dialogue(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto& dialogue = *game.dialogue;
    constexpr Rectangle rect{BoardX + 12, BoardY + 58, 416, 330};
    art_->text.modal(rect, dialogue.shop ? "An offer" : "Conversation");
    const bool fairy = is_fairy_continuation(dialogue.continuation);
    const auto content = fairy ? localized_fairy_dialogue(art_->text.language, game.hero.fairy_score,
                                                          game.hero.fairy_rank, game.hero.fairy_visits)
                               : dialogue.text;
    const auto text = art_->text.wrap(content, 376, 18, !fairy);
    const int lines = 1 + int(std::ranges::count(text, '\n'));
    constexpr int TextHeight = 188;
    const float max_scroll = std::max(0.f, float(lines * 22 - TextHeight));
    bool tapped = false;
    if (!dialogue.shop || mouse.y < rect.y + 274 || dialogue_dragging_) {
        if (dialogue_dragging_ && dialogue_text_ != dialogue.text)
            dialogue_dragging_ = false;
        if (pointer_pressed_ && CheckCollisionPointRec(mouse, rect)) {
            dialogue_dragging_ = true;
            dialogue_moved_ = false;
            dialogue_start_ = dialogue_last_ = mouse;
            dialogue_text_ = dialogue.text;
        }
        if (dialogue_dragging_) {
            const auto view = window_viewport();
            const float threshold = 10 * view.touch_scale * CanvasWidth / view.area.width;
            dialogue_moved_ = dialogue_moved_ || std::abs(mouse.x - dialogue_start_.x) > threshold ||
                              std::abs(mouse.y - dialogue_start_.y) > threshold;
            if (pointer_down_) {
                if (dialogue_moved_)
                    ui.dialogue_scroll -= mouse.y - dialogue_last_.y;
                dialogue_last_ = mouse;
            } else {
                tapped = !dialogue.shop && !pointer_cancelled_ && !dialogue_moved_ &&
                         CheckCollisionPointRec(mouse, rect);
                dialogue_dragging_ = false;
            }
        }
    } else
        dialogue_dragging_ = false;
    ui.dialogue_scroll = std::clamp(ui.dialogue_scroll, 0.f, max_scroll);
    art_->text.clip({rect.x + 20, rect.y + 62, 376, TextHeight});
    art_->text.draw(text, int(rect.x + 20), int(rect.y + 62 - ui.dialogue_scroll), 18, Ink, false);
    EndScissorMode();
    if (max_scroll > 0)
        art_->text.draw(ui.touch_enabled() ? "Drag to scroll" : "Mouse wheel to scroll", int(rect.x + 20),
                        int(rect.y + 252), 12, Muted);
    if (dialogue.shop) {
        for (int i = 0; i < 3; ++i)
            if (!dialogue.choices[i].empty() &&
                art_->text.button({rect.x + 20 + i * 128, rect.y + 274, 120, 28}, dialogue.choices[i], mouse))
                return {Action::Choose, i};
        if (art_->text.button({rect.x + 284, rect.y + 308, 112, 19}, "Cancel [Esc]", mouse))
            return {Action::Choose, -1};
    } else {
        if (ui.touch_enabled())
            art_->text.fit("Tap the conversation to continue", {rect.x + 20, rect.y + 282, 376, 30}, 16,
                           Gold);
        else if (art_->text.button({rect.x + 20, rect.y + 282, 376, 30}, "Continue  [Enter / Space]",
                                   mouse)) {
            dialogue_dragging_ = false;
            return {Action::Continue};
        }
        if (tapped)
            return {Action::Continue};
    }
    return {};
}

UiAction Presentation::draw_inventory(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{BoardX + 4, BoardY + 9, 432, 420};
    art_->text.modal(rect, "Inventory");
    std::optional<std::pair<Rectangle, Item>> hovered_item;
    for (int i = 0; i < ItemCount; ++i) {
        const auto item = static_cast<Item>(i);
        const int count = game.inventory(item);
        const Rectangle row{rect.x + 12 + i / 8 * 204, rect.y + 57 + i % 8 * 39, 198, 35};
        const bool hover = CheckCollisionPointRec(mouse, row);
        DrawRectangleRec(row, count && hover ? Color{88, 79, 76, 255} : Color{66, 62, 70, 255});
        art_->icon(HeroOrb + i, {row.x + 2, row.y + 2, 31, 31}, count ? WHITE : Color{170, 170, 170, 130});
        art_->text.fit(std::string(Game::item_name(item)), {row.x + 37, row.y + 2, 158, 20}, 17,
                       count ? Ink : Muted);
        art_->text.draw(count ? item_definition(item).passive ? "Passive" : "Use" : "Not found",
                        int(row.x + 37), int(row.y + 21), 13, count ? Gold : Muted);
        if (hover)
            hovered_item = {{row, item}};
        if (count && !game.busy() && clicked(row, mouse)) {
            ui.inventory = false;
            if (use_item_directly(item, ui))
                return {Action::UseItem, i};
            ui.selected_item = i;
            break;
        }
    }
    if (art_->text.button({rect.x + 12, rect.y + 378, 408, 28}, "Close  [I / Esc]", mouse))
        ui.inventory = false;
    if (ui.inventory && hovered_item && ui.item_use_mode == ItemUseMode::Describe)
        art_->text.tooltip(hovered_item->first,
                           localized_text(ui.language, item_definition(hovered_item->second).description));
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
        const auto found = std::ranges::find_if(
            enemies, [&](auto entry) { return Game::monster_for_tile(entry.first) == row; });
        if (found == enemies.end())
            enemies.emplace_back(tile, 1);
        else
            ++found->second;
    }
    const int last_row = std::max(0, int(enemies.size()) - VisibleRows);
    ui.enemy_first_row = std::clamp(ui.enemy_first_row, 0, last_row);
    art_->text.modal(rect, std::format("Orb of the Hero - floor {}", game.hero.floor));
    for (const auto& [label, x, width] :
         std::array<std::tuple<const char*, int, int>, 5>{{{"Enemy", 52, 156},
                                                           {"Life", 216, 76},
                                                           {"Offense", 300, 72},
                                                           {"Defense", 380, 68},
                                                           {"Damage", 464, 116}}})
        art_->text.fit(label, {rect.x + x, rect.y + 57, float(width), 24}, 17, Gold);
    const int scale = game.hero.cycle_factor_minus_one + 1;
    for (int visible = 0; visible < VisibleRows && ui.enemy_first_row + visible < std::ssize(enemies);
         ++visible) {
        const auto [tile, count] = enemies[ui.enemy_first_row + visible];
        const int row = Game::monster_for_tile(tile);
        const auto& monster = game.monsters[row];
        const float y = rect.y + 88 + visible * 40;
        DrawRectangle(int(rect.x + 16), int(y), int(rect.width - 32), 37,
                      visible % 2 ? Color{67, 63, 73, 255} : Color{77, 72, 80, 255});
        art_->icon(tile, {rect.x + 18, y + 3, 31, 31});
        art_->text.fit(count > 1 ? std::format("{} ({})", Game::monster_name(row), count)
                                 : std::string(Game::monster_name(row)),
                       {rect.x + 52, y + 4, 156, 29}, 18);
        for (int i = 0; i < 3; ++i)
            art_->text.fit(
                std::to_string(std::array<int, 3>{monster.hp, monster.attack, monster.defense}[i] * scale),
                {rect.x + 216 + i * 82, y + 4, 76, 29}, 18, Ink, {.bold = true});
        const auto forecast = ui.hero_orb_actual_damage ? game.forecast(tile) : game.orb_forecast(tile);
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
    draw_qol_status(ui, {rect.x + 452, rect.y + 12, 132, 28}, mouse);
}

void Presentation::draw_qol_status(const DesktopUi& ui, Rectangle rect, Vector2 mouse) {
    const int count = int(ui.mouse_walking) + int(ui.blink_mode) + int(ui.hero_orb_actual_damage) +
                      int(ui.realtime_hero_orb) + int(ui.item_collection) + int(ui.skip_attack_animation) +
                      int(ui.skip_staircase_animation) + int(ui.item_use_mode != ItemUseMode::Confirm);
    DrawRectangleRec(rect, Bar);
    art_->text.outline(rect, 1, count ? Gold : Border);
    art_->text.fit(count ? std::format("QOL: {} enabled", count) : "QOL: none", rect, 16,
                   count ? Gold : Muted);
    if (CheckCollisionPointRec(mouse, rect)) {
        std::string text =
            localized_text(art_->text.language, count ? "Enabled QOLs:" : "Enabled QOLs: none");
        if (ui.mouse_walking)
            text += "\n" + localized_text(art_->text.language, "Mouse walking");
        if (ui.blink_mode)
            text += "\n" + localized_text(art_->text.language, "Blink mode (experienced players only)");
        if (ui.hero_orb_actual_damage)
            text += "\n" + localized_text(art_->text.language, "Hero Orb actual damage");
        if (ui.realtime_hero_orb)
            text += "\n" + localized_text(art_->text.language, "Realtime Hero Orb");
        if (ui.item_collection)
            text += "\n" + localized_text(art_->text.language, "Item collection");
        if (ui.skip_attack_animation)
            text += "\n" + localized_text(art_->text.language, "Skip attack animation");
        if (ui.skip_staircase_animation)
            text += "\n" + localized_text(art_->text.language, "Skip staircase animation");
        if (ui.item_use_mode != ItemUseMode::Confirm)
            text += "\n" +
                    localized_text(art_->text.language, ItemUseLabels[std::to_underlying(ui.item_use_mode)]);
        text += "\n" + localized_text(art_->text.language,
                                      "Change QOLs in Settings. Defaults: off; item use: Confirm.");
        art_->text.tooltip(rect, text);
    }
}

UiAction Presentation::draw_item(const Game& game, DesktopUi& ui, Vector2 mouse) {
    const auto item = static_cast<Item>(ui.selected_item);
    const bool touch = ui.touch_enabled();
    const float button_height = touch ? 44.f : 29.f;
    const Rectangle rect{BoardX + 18, BoardY + 98, 404, touch ? 272.f : 250.f};
    art_->text.modal(rect, std::string(Game::item_name(item)));
    art_->icon(HeroOrb + ui.selected_item, {rect.x + 20, rect.y + 60, 40, 40});
    art_->text.draw(item_definition(item).passive ? "Passive item"
                                                  : std::format("Owned: {}", game.inventory(item)),
                    int(rect.x + 76), int(rect.y + 68), 18, Gold);
    const bool describe = item_definition(item).passive || ui.item_use_mode == ItemUseMode::Describe;
    const auto description = art_->text.wrap(
        describe ? std::string(item_definition(item).description) : "Use this item?", 364, 17);
    SetTextLineSpacing(22);
    art_->text.draw(description, int(rect.x + 20), int(rect.y + 112), 17, Ink, false);
    if (item_definition(item).passive) {
        if (art_->text.button({rect.x + 20, rect.y + 203, 364, button_height}, "Close  [Enter / Esc]", mouse))
            ui.selected_item = -1;
    } else {
        if (art_->text.button({rect.x + 20, rect.y + 203, 176, button_height}, touch ? "Use" : "Use  [Enter]",
                              mouse, !game.busy() && game.inventory(item) > 0))
            return {Action::UseItem, ui.selected_item};
        if (art_->text.button({rect.x + 208, rect.y + 203, 176, button_height},
                              touch ? "Cancel" : "Cancel  [Esc]", mouse))
            ui.selected_item = -1;
    }
    return {};
}

void Presentation::draw_help(DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{140, 48, 520, 460};
    art_->text.modal(rect, "Tower of the Sorcerer");
    const std::array<std::pair<const char*, const char*>, 13> controls{
        {{"Arrows / WASD", "Move"},
         {"Enter / Space", "Continue dialogue"},
         {"I", "Inventory"},
         {"Q / Shift+Q", "Quick save / restore"},
         {"K / L", "Save / load slots"},
         {"Shift+L", "Restore floor autosave"},
         {"Shift+F", "Fairy checkpoint"},
         {"Shift+N", "New game"},
         {"O", "Settings"},
         {"H", "Help"},
         {"M", "Music and effects"},
         {"R", "Rankings"},
         {"Esc", "Main menu"}}};
    for (int i = 0; i < std::ssize(controls); ++i) {
        art_->text.draw(controls[i].first, int(rect.x + 20), int(rect.y + 60 + i * 22), 17, Ink);
        art_->text.fit(controls[i].second, {rect.x + 190, rect.y + 58 + i * 22, 310, 22}, 17, Ink,
                       {.alignment = TextAlignment::Right});
    }
    art_->text.draw(
        art_->text.wrap(
            "Click map tiles to walk or interact.\nFloor autosaves are written after arrival events finish.",
            480, 16),
        int(rect.x + 20), int(rect.y + 354), 16, Muted, false);
    if (art_->text.button({rect.x + 20, rect.y + 418, 480, 29}, "Close  [Esc]", mouse))
        ui.help = false;
}

UiAction Presentation::draw_menu(const Game& game, DesktopUi& ui, Vector2 mouse) {
    if (ui.menu == Menu::About) {
        constexpr Rectangle rect{190, 136, 420, 288};
        art_->text.modal(rect, "About");
        art_->text.fit("Tower of the Sorcerer", {rect.x + 20, rect.y + 58, 380, 32}, 24, Ink, {.bold = true});
        art_->text.fit("Magic Tower for Windows", {rect.x + 20, rect.y + 91, 380, 24}, 17, Muted);
        DrawLine(int(rect.x + 22), int(rect.y + 128), int(rect.x + rect.width - 22), int(rect.y + 128),
                 Border);
        art_->text.fit("Windows game (1998-2000)", {rect.x + 20, rect.y + 138, 380, 22}, 16, Muted);
        art_->text.fit("Oz & Kenichi", {rect.x + 20, rect.y + 161, 380, 29}, 22, Gold,
                       {.bold = true, .translate = false});
        art_->text.fit("Copyright (1996)", {rect.x + 20, rect.y + 194, 380, 22}, 16, Muted);
        art_->text.fit("N.W", {rect.x + 20, rect.y + 217, 380, 25}, 20, Gold,
                       {.bold = true, .translate = false});
        if (art_->text.button({rect.x + 126, rect.y + 253, 168, 26}, "OK [Enter / Esc]", mouse))
            ui.menu = Menu::None;
    } else if (ui.menu == Menu::Game) {
        constexpr Rectangle rect{6, MenuHeight, 252, 372};
        DrawRectangleRec(rect, Panel);
        art_->text.outline(rect, 1, Border);
        const std::array<const char*, 11> labels{"New game [Shift+N]",
                                                 "Save slots [K]",
                                                 "Load slots [L]",
                                                 "Quick save [Q]",
                                                 "Quick restore [Shift+Q]",
                                                 "Fairy checkpoint [Shift+F]",
                                                 "Floor autosave [Shift+L]",
                                                 "Rankings [R]",
                                                 "Play replay",
                                                 "Main menu [Esc]",
                                                 "Close"};
        const std::array<Action, 10> actions{
            Action::NewGame,     Action::OpenSaveSlots,   Action::OpenLoadSlots, Action::Save,
            Action::Load,        Action::FairyCheckpoint, Action::LoadAutosave,  Action::OpenRankings,
            Action::OpenReplays, Action::MainMenu};
        for (int i = 0; i < std::ssize(labels); ++i)
            if (art_->text.button({rect.x + 6, rect.y + 6 + i * 33, rect.width - 12, 27}, labels[i], mouse,
                                  ((i != 1 && i != 3) || !game.busy()) &&
                                      (i < 1 || i > 6 || ui.file_controls_enabled()) &&
                                      (i != 7 || !game.busy()))) {
                ui.menu = Menu::None;
                return i < std::ssize(actions) ? UiAction{actions[i]} : UiAction{};
            }
    } else if (ui.menu == Menu::Options) {
        constexpr Rectangle rect{50, 34, 700, 484};
        art_->text.modal(rect, "Settings");
        constexpr std::array<const char*, 5> tabs{"Game", "QOL", "Controls", "Replay", "Language"};
        for (int i = 0; i < std::ssize(tabs); ++i) {
            const Rectangle tab{rect.x + 18 + i * 134, rect.y + 56, 128, 48};
            if (art_->text.button(tab, tabs[i], mouse))
                ui.settings_tab = static_cast<SettingsTab>(i);
            if (int(ui.settings_tab) == i)
                art_->text.outline(tab, 2, Gold);
        }
        const float left = rect.x + 18;
        if (ui.settings_tab == SettingsTab::Game) {
            art_->text.draw("Sound", int(left), 150, 19, Gold);
            if (art_->text.button({left, 174, 664, 48},
                                  ui.muted ? "Enable music and effects [M]" : "Mute music and effects [M]",
                                  mouse))
                return {Action::Mute};
            art_->text.draw("Animation and automatic walking speed", int(left), 236, 17, Muted);
            const int current = int(std::round(ui.animation_speed * 10));
            art_->text.fit(std::format("{:.1f}x", ui.animation_speed), {left + 560, 232, 104, 28}, 21, Gold);
            if (art_->text.button({left, 276, 48, 48}, "-", mouse, current > MinAnimationSpeed))
                return {Action::Speed, current - 1};
            if (art_->text.button({left + 616, 276, 48, 48}, "+", mouse, current < MaxAnimationSpeed))
                return {Action::Speed, current + 1};
            constexpr Rectangle slider{128, 276, 544, 48};
            constexpr float start = slider.x + 12, width = slider.width - 24;
            if (pointer_pressed_ && CheckCollisionPointRec(mouse, slider) && !pointer_cancelled_)
                speed_dragging_ = true;
            int selected = current;
            if (speed_dragging_ && pointer_down_ && !pointer_cancelled_)
                selected =
                    int(std::round(MinAnimationSpeed + std::clamp((mouse.x - start) / width, 0.f, 1.f) *
                                                           (MaxAnimationSpeed - MinAnimationSpeed)));
            const float thumb =
                start + width * (selected - MinAnimationSpeed) / (MaxAnimationSpeed - MinAnimationSpeed);
            DrawRectangleRec({start, slider.y + 21, width, 6}, Bar);
            DrawRectangleRec({start, slider.y + 21, thumb - start, 6}, Gold);
            art_->text.outline({start, slider.y + 21, width, 6}, 1, Border);
            DrawRectangleRec({thumb - 12, slider.y + 7, 24, 34},
                             speed_dragging_ || CheckCollisionPointRec(mouse, slider) ? Gold : Ink);
            art_->text.outline({thumb - 12, slider.y + 7, 24, 34}, 1, Border);
            art_->text.fit("1x", {slider.x, 330, 48, 24}, 16, Muted);
            art_->text.fit("10x", {slider.x + slider.width - 48, 330, 48, 24}, 16, Muted);
            art_->text.draw("Click or drag to adjust. Default: 1x.", int(left), 372, 17, Muted);
            if (selected != current)
                return {Action::Speed, selected};
        } else if (ui.settings_tab == SettingsTab::Qol) {
            art_->text.draw("Quality of life", int(left), 158, 19, Gold);
            const Rectangle qol{left, 192, 328, 48}, realtime{left + 336, 192, 328, 48};
            if (art_->text.button(qol,
                                  ui.hero_orb_actual_damage ? "Hero Orb actual damage: on"
                                                            : "Hero Orb actual damage: off",
                                  mouse))
                return {Action::HeroOrbActualDamage};
            if (art_->text.button(realtime,
                                  ui.realtime_hero_orb ? "Realtime Hero Orb: on" : "Realtime Hero Orb: off",
                                  mouse))
                return {Action::RealtimeHeroOrb};
            const Rectangle collection{left, 252, 328, 48};
            if (art_->text.button(collection,
                                  ui.item_collection ? "Item collection: on" : "Item collection: off", mouse))
                return {Action::ItemCollection};
            const Rectangle attack{left + 336, 252, 328, 48}, stairs{left, 312, 328, 48};
            if (art_->text.button(attack,
                                  ui.skip_attack_animation ? "Skip attack animation: on"
                                                           : "Skip attack animation: off",
                                  mouse))
                return {Action::SkipAttackAnimation};
            if (art_->text.button(stairs,
                                  ui.skip_staircase_animation ? "Skip staircase animation: on"
                                                              : "Skip staircase animation: off",
                                  mouse))
                return {Action::SkipStaircaseAnimation};
            const Rectangle walking{left + 336, 312, 328, 48};
            if (art_->text.button(walking, ui.mouse_walking ? "Mouse walking: on" : "Mouse walking: off",
                                  mouse))
                return {Action::MouseWalking};
            const Rectangle blink{left, 372, 328, 48}, item_use{left + 336, 372, 328, 48};
            if (art_->text.button(blink, ui.blink_mode ? "Blink mode: on" : "Blink mode: off", mouse))
                return {Action::BlinkMode};
            if (art_->text.button(item_use, ItemUseLabels[std::to_underlying(ui.item_use_mode)], mouse))
                return {Action::CycleItemUse};
            art_->text.draw("Blink: experienced players only. Default item use: Confirm.", int(left), 430, 17,
                            Muted);
            if (CheckCollisionPointRec(mouse, item_use))
                art_->text.tooltip(item_use, "Confirm asks before use. Description + confirm explains the "
                                             "item. One-click use activates immediately.");
            if (CheckCollisionPointRec(mouse, attack))
                art_->text.tooltip(
                    attack,
                    "Show the first strike, then resolve the rest of combat instantly. Default: off.");
            if (CheckCollisionPointRec(mouse, stairs))
                art_->text.tooltip(
                    stairs,
                    "Arrive on the destination floor immediately, without the spiral wipe. Default: off.");
            if (CheckCollisionPointRec(mouse, collection))
                art_->text.tooltip(collection,
                                   "Show the two collection buttons beneath the inventory. Default: off.");
            if (CheckCollisionPointRec(mouse, qol))
                art_->text.tooltip(qol, ui.hero_orb_actual_damage
                                            ? "Hero Orb actual damage: on\nShows combat damage with Cross "
                                              "and Dragon Slayer bonuses. Battle rules are unchanged."
                                            : "Hero Orb actual damage: off\nEnable this to show combat "
                                              "damage with Cross and Dragon Slayer bonuses. Default: off.");
            if (CheckCollisionPointRec(mouse, realtime))
                art_->text.tooltip(realtime,
                                   "Requires Hero Orb. Top: HP cost. Left: ATK. Right: DEF. Bottom: gold. "
                                   "∞ means defense cannot be penetrated. Hover a monster for exact "
                                   "values. Uses the Hero Orb damage setting. Default: off.");
            if (CheckCollisionPointRec(mouse, walking))
                art_->text.tooltip(walking, "Click floor to walk or an event to interact. Hidden events stop "
                                            "the walk. Default: off.");
            if (CheckCollisionPointRec(mouse, blink))
                art_->text.tooltip(
                    blink, "Blink across event-free floor, or beside the clicked event to interact once. "
                           "Otherwise walk normally. Does not cross doors, monsters or hidden tunnels. "
                           "Overrides mouse walking.");
        } else if (ui.settings_tab == SettingsTab::Controls) {
            art_->text.draw("Controls", int(left), 158, 19, Gold);
            if (art_->text.button({left, 192, 664, 48},
                                  ui.touch_enabled() ? "Touch controls: on" : "Touch controls: off", mouse))
                return {Action::TouchControls};
            art_->text.draw("Show the directional pad. Default: automatic.", int(left), 252, 17, Muted);
        } else if (ui.settings_tab == SettingsTab::Replay) {
            art_->text.draw("Recording", int(left), 158, 19, Gold);
            if (art_->text.button({left, 192, 664, 48},
                                  ui.recording_enabled ? "Record new games: on" : "Record new games: off",
                                  mouse))
                return {Action::Recording};
            art_->text.draw("New games, recorded loads and replay takeover.", int(left), 252, 17, Muted);
            art_->text.draw("Replay and animation speed", int(left), 304, 17, Muted);
            for (int i = 0; i < std::ssize(ReplaySpeeds); ++i)
                if (art_->text.button(
                        {left + i * 96, 336, 88, 48},
                        std::format("{}x{}", ReplaySpeeds[i], ui.replay_speed_index == i ? " *" : ""), mouse))
                    return {Action::ReplaySpeed, i};
        } else {
            for (int i = 0; i < std::ssize(Languages); ++i) {
                const Rectangle choice{rect.x + 140, rect.y + 124 + i * 56, 420, 48};
                if (art_->text.button(choice, std::string(language_label(Languages[i])), mouse))
                    return {Action::Language, i};
                if (ui.language == Languages[i])
                    art_->text.outline(choice, 2, Gold);
            }
        }
        if (art_->text.button({rect.x + 490, rect.y + 426, 192, 48}, "Done [Esc]", mouse))
            ui.menu = Menu::None;
    }
    return {};
}

UiAction Presentation::draw_rankings(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{110, 42, 580, 470};
    art_->text.modal(rect, "Fairy rankings");
    constexpr std::array<int, RankingCategoryCount> Floors{10, 20, 25, 40, 49};
    for (int category = 1; category <= RankingCategoryCount; ++category)
        if (art_->text.button(
                {rect.x + 18 + (category - 1) * 110, rect.y + 56, 103, 28},
                std::format("{}F{}", Floors[category - 1], category == ui.ranking_category ? " *" : ""),
                mouse))
            return {Action::RankingCategory, category};
    constexpr std::array<float, 6> Columns{128, 166, 318, 390, 484, 560};
    constexpr std::array<float, 6> Widths{32, 144, 64, 86, 68, 100};
    constexpr std::array<const char*, 6> Headers{"Rank", "Name", "Score", "HP", "ATK", "DEF"};
    for (int column = 0; column < std::ssize(Headers); ++column)
        art_->text.fit(Headers[column], {Columns[column], 135, Widths[column], 22}, 16, Gold);
    const auto& table = game.rankings.at(ui.ranking_category - 1);
    for (int row = 0; row < RankingEntryCount; ++row) {
        const auto& entry = table[row];
        const std::array<std::string, 6> cells{std::to_string(row + 1),      entry.name,
                                               std::to_string(entry.score),  std::to_string(entry.hp),
                                               std::to_string(entry.attack), std::to_string(entry.defense)};
        for (int column = 0; column < std::ssize(cells); ++column)
            art_->text.fit(cells[column], {Columns[column], 159.f + row * 22, Widths[column], 22}, 16, Ink,
                           {.translate = column != 1});
    }
    const bool submission =
        ui.ranking_entry && ui.ranking_entry_category == ui.ranking_category && ui.ranking_position > 0;
    if (ui.ranking_reset_confirmation)
        art_->text.draw("Reset this category? Click Confirm reset to replace its scores.", 128, 399, 16,
                        Gold);
    else if (submission) {
        art_->text.draw(std::format("New entry: rank {}. Enter your name.", ui.ranking_position), 128, 387,
                        16, Gold);
        const Rectangle input{128, 415, 430, 30};
        DrawRectangleRec(input, Bar);
        art_->text.outline(input, 1, Gold);
        art_->text.draw(ui.ranking_name + "_", 136, 420, 18, Ink, false);
    }
    if (art_->text.button({128, 464, 178, 30},
                          ui.ranking_reset_confirmation ? "Confirm reset" : "Reset category", mouse,
                          !ui.replay_active))
        return {Action::ResetRankings};
    if (art_->text.button({316, 464, 156, 30}, "Submit [Enter]", mouse,
                          submission && !ui.ranking_name.empty() && !ui.ranking_reset_confirmation &&
                              !ui.replay_active))
        return {Action::SubmitRanking};
    if (art_->text.button({482, 464, 190, 30}, "Done [Esc]", mouse))
        ui.close_overlays();
    return {};
}

UiAction Presentation::draw_save_slots(const Game& game, DesktopUi& ui, Vector2 mouse) {
    constexpr Rectangle rect{82, MenuHeight + 16, 636, 466};
    const bool saving = ui.save_picker == SavePicker::Save;
    art_->text.modal(rect, saving ? "Save game - eight slots" : "Load game - eight slots");
    if (!saving) {
        if (art_->text.button({rect.x + 344, rect.y + 14, 136, 28}, "Quick [Shift+Q]", mouse,
                              ui.quick_available))
            return {Action::Load};
        if (art_->text.button({rect.x + 488, rect.y + 14, 130, 28}, "Fairy [Shift+F]", mouse,
                              ui.fairy_available))
            return {Action::FairyCheckpoint};
    }
    for (int i = 0; i < ManualSaveSlotCount; ++i) {
        const Rectangle card{rect.x + 18 + i % 2 * 306, rect.y + 64 + i / 2 * 84, 294, 76};
        const auto& info = ui.save_slots[i];
        const bool selected = ui.selected_slot == i + 1;
        const bool hover = CheckCollisionPointRec(mouse, card);
        DrawRectangleRec(card, selected ? Color{84, 69, 65, 255} : Color{45, 43, 51, 255});
        art_->text.outline(card, selected ? 2.f : 1.f, selected || hover ? Gold : Border);
        art_->text.draw(std::format("Slot {}", i + 1), int(card.x + 12), int(card.y + 7), 18, Gold);
        if (info.state == SaveSlotState::Ready) {
            const std::string mode = !info.backside     ? "Frontside"
                                     : info.later_cycle ? "Backside 3+"
                                                        : "Backside 2";
            art_->text.fit(std::format("Floor {} / {}", info.floor, mode),
                           {card.x + 72, card.y + 5, card.width - 84, 23}, 16, Muted,
                           {.alignment = TextAlignment::Right});
            art_->text.draw(std::format("HP {}", info.hp), int(card.x + 12), int(card.y + 30), 16);
            art_->text.draw(std::format("ATK {}    DEF {}", info.attack, info.defense), int(card.x + 12),
                            int(card.y + 51), 16);
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
                          std::format("{}{} [Enter]", label, ui.selected_slot), mouse,
                          saving ? !game.busy() : selected.state == SaveSlotState::Ready))
        return {saving ? Action::SaveSlot : Action::LoadSlot, ui.selected_slot};
    const Rectangle autosave{rect.x + 324, rect.y + 430, 156, 28};
    if (!saving &&
        art_->text.button(autosave, "Floor autosave", mouse, ui.autosave_slot.state == SaveSlotState::Ready))
        return {Action::LoadAutosave};
    if (!saving && CheckCollisionPointRec(mouse, autosave)) {
        if (ui.autosave_slot.state == SaveSlotState::Ready)
            art_->text.tooltip(autosave, std::format("Floor {} / HP {} [Shift+L]", ui.autosave_slot.floor,
                                                     ui.autosave_slot.hp));
        else
            art_->text.tooltip(autosave, ui.autosave_slot.state == SaveSlotState::Invalid
                                             ? "Unreadable save"
                                             : "No floor autosave yet.");
    }
    if (art_->text.button({rect.x + (saving ? 324 : 488), rect.y + 430, saving ? 294.f : 130.f, 28},
                          "Cancel [Esc]", mouse))
        ui.close_overlays();
    return {};
}

UiAction Presentation::draw_home(const DesktopUi& ui, Vector2 mouse) {
    art_->scene("data3-open0", {0, 0, CanvasWidth, CanvasHeight});
    const std::array<std::string, 6> labels{ui.replay_active ? "Continue replay" : "Continue game",
                                            "New game",
                                            "Load game",
                                            "Play replay",
                                            "Settings",
                                            "About"};
    constexpr std::array<Action, 6> actions{Action::ResumeGame,  Action::NewGame,      Action::OpenLoadSlots,
                                            Action::OpenReplays, Action::OpenSettings, Action::OpenAbout};
    const int first = ui.game_started ? 0 : 1;
    constexpr int top = 48;
    for (int i = first; i < std::ssize(labels); ++i) {
        const Rectangle row{40, float(top + (i - first) * 52), 244, 44};
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
        if (clicked(button, mouse)) {
            ui.replay_selected = index;
            const auto path = ui.replay_files[index].u8string();
            ui.replay_path.assign(path.begin(), path.end());
            ui.replay_path_focus = false;
        }
        DrawRectangleRec(button, Panel);
        art_->text.fit(std::string(text.begin(), text.end()), button, 18, Ink, {.translate = false});
        if (ui.replay_selected == index)
            art_->text.outline(button, 2, Gold);
    }
    if (!count)
        art_->text.draw(
            "No recordings saved yet. Paste a file path below,\nor drop a .jsonl file on the window.",
            int(rect.x + 26), int(rect.y + 116), 19, Muted);
    art_->text.draw("Recording file  /  Ctrl+V to paste", int(rect.x + 18), int(rect.y + 292), 16, Muted);
    const Rectangle field{rect.x + 18, rect.y + 318, 644, 34};
    DrawRectangleRec(field, Color{31, 29, 36, 255});
    art_->text.outline(field, 1, ui.replay_path_focus ? Gold : Border);
    if (clicked(field, mouse))
        ui.replay_path_focus = true;
    art_->text.clip(field);
    const int offset = std::max(0, art_->text.width(ui.replay_path, 16) - int(field.width) + 24);
    art_->text.draw(ui.replay_path, int(field.x + 8) - offset, int(field.y + 6), 16, Ink, false);
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
    if (art_->text.button({552, 3, 24, 22}, "+", mouse, ui.replay_speed_index + 1 < std::ssize(ReplaySpeeds)))
        return {Action::ReplaySpeed, ui.replay_speed_index + 1};
    if (art_->text.button({584, 3, 76, 22}, "Settings", mouse))
        return {Action::OpenSettings};
    art_->text.fit(std::format("{} / {}", ui.replay_step, ui.replay_count), {666, 3, 128, 22}, 16, Muted);
    return {};
}

UiAction Presentation::draw_ending_summary(const EndingSummary& summary, DesktopUi& ui, Vector2 mouse) {
    const auto& hero = summary.hero;
    const auto achievements = ending_achievements(summary);
    ClearBackground(Color{29, 27, 35, 255});
    DrawRectangle(0, MenuHeight, CanvasWidth, 59, Panel);
    DrawLine(32, 86, 768, 86, Border);
    art_->text.draw("Tower cleared", 32, 43, 28, Gold);

    const int sword = std::clamp(std::to_underlying(hero.sword), 0, EquipmentTierCount),
              shield = std::clamp(std::to_underlying(hero.shield), 0, EquipmentTierCount);
    const std::array<std::tuple<const char*, int, int>, 8> stats{
        {{"HP", hero.hp, RedPotion},
         {"ATK", hero.attack, sword ? IronSword + sword - 1 : 0},
         {"Defense", hero.defense, shield ? IronShield + shield - 1 : 0},
         {"Gold", hero.gold, LuckyGold},
         {"Altar purchases", hero.altar_purchases, Altar},
         {"Yellow keys", hero.yellow_keys, YellowKey},
         {"Blue keys", hero.blue_keys, BlueKey},
         {"Red keys", hero.red_keys, RedKey}}};
    for (int i = 0; i < std::ssize(stats); ++i) {
        const auto [label, value, icon] = stats[i];
        const float x = 32.f + (i % 4) * 188, y = 98.f + (i / 4) * 64;
        DrawRectangleRec({x, y, 172, 60}, Panel);
        if (icon)
            art_->icon(icon, {x + 10, y + 21, 30, 30});
        art_->text.fit(label, {x + 4, y + 3, 164, 19}, 15, Muted);
        art_->text.fit(std::to_string(value), {x + 44, y + 23, 120, 29}, 23, Ink,
                       {.bold = true, .translate = false});
    }
    art_->text.draw("Achievements", 32, 239, 21, Gold);
    int shown = 0;
    for (const auto& entry : achievements) {
        if (entry.status != AchievementStatus::Earned)
            continue;
        const float x = 32.f + (shown % 2) * 376, y = 272.f + (shown / 2) * 80;
        ++shown;
        DrawRectangleRec({x, y, 360, 74}, Panel);
        art_->text.outline({x, y, 360, 74}, 1, Border);
        art_->icon(entry.icon, {x + 10, y + 13, 48, 48});
        if (entry.overlay) {
            DrawRectangleRec({x + 40, y + 43, 24, 24}, Color{29, 27, 35, 255});
            art_->icon(entry.overlay, {x + 42, y + 45, 20, 20});
            if (entry.overlay == DragonSlayer || entry.overlay == Bomb)
                DrawLineEx({x + 42, y + 65}, {x + 62, y + 45}, 2, Color{240, 124, 116, 255});
        }
        const auto name = localized_text(art_->text.language, entry.name);
        int size = 18;
        while (size > 12 && art_->text.width(name, size) > 276)
            --size;
        art_->text.draw(name, int(x + 72), int(y + 8), size, Ink, false);
        art_->text.clip({x + 72, y + 31, 276, 40});
        art_->text.draw(art_->text.wrap(std::string(entry.description), 276, 14), int(x + 72), int(y + 33),
                        14, Muted, false);
        EndScissorMode();
    }
    const bool next = art_->text.button({588, 514, 180, 29}, "Next cycle", mouse, !ui.replay_active);
    if (ui.replay_active) {
        const auto action = draw_replay_controls(ui, mouse);
        if (action.kind != Action::None)
            return action;
    }
    return next ? UiAction{Action::ContinueEnding} : UiAction{};
}

UiAction Presentation::draw_touch_controls(const Game& game, TouchContext context,
                                           std::optional<TouchButton> input) {
    touch_context_ = context;
    touch_busy_ = game.busy();
    if (!input || !touch_button_enabled(*input, context, touch_busy_))
        return {};
    if (*input == TouchButton::Cancel)
        return {Action::CancelFlight};
    if (*input == TouchButton::Confirm)
        return {Action::Travel};
    if (context == TouchContext::Flight)
        return {*input == TouchButton::Up ? Action::FlightUp : Action::FlightDown};
    constexpr std::array<Direction, 5> directions{Direction::Up, Direction::Left, Direction::Down,
                                                  Direction::Right, Direction::Down};
    return {Action::Move, int(directions[int(*input)])};
}

void Presentation::paint_touch_controls(const CanvasViewport& view) const {
    if (touch_context_ != TouchContext::Walk && touch_context_ != TouchContext::Flight)
        return;
    const auto buttons = touch_buttons(view);
    const float unit = view.touch_scale;
    for (int i = 0; i < int(buttons.size()); ++i) {
        const auto button = static_cast<TouchButton>(i);
        const auto rect = buttons[i];
        if (touch_context_ == TouchContext::Walk &&
            (button == TouchButton::Confirm || button == TouchButton::Cancel))
            continue;
        if (touch_context_ == TouchContext::Flight &&
            (button == TouchButton::Left || button == TouchButton::Right))
            continue;
        const bool usable = touch_button_enabled(button, touch_context_, touch_busy_);
        const bool held = usable && touch_.active == button && !touch_.blocked;
        DrawRectangleRec(rect, held ? Color{113, 87, 55, 255} : Panel);
        DrawRectangleLinesEx(rect, unit, usable ? Border : Color{99, 93, 94, 255});
        const auto color = usable ? Ink : Color{120, 115, 117, 255};
        const Vector2 center{rect.x + rect.width / 2, rect.y + rect.height / 2};
        if (button == TouchButton::Confirm || button == TouchButton::Cancel) {
            if (button == TouchButton::Confirm) {
                DrawLineEx({center.x - 11 * unit, center.y}, {center.x - 3 * unit, center.y + 8 * unit},
                           3 * unit, color);
                DrawLineEx({center.x - 3 * unit, center.y + 8 * unit},
                           {center.x + 11 * unit, center.y - 9 * unit}, 3 * unit, color);
            } else {
                DrawLineEx({center.x - 9 * unit, center.y - 9 * unit},
                           {center.x + 9 * unit, center.y + 9 * unit}, 3 * unit, color);
                DrawLineEx({center.x + 9 * unit, center.y - 9 * unit},
                           {center.x - 9 * unit, center.y + 9 * unit}, 3 * unit, color);
            }
        } else {
            const auto direction = button == TouchButton::Up     ? Vector2{0, -1}
                                   : button == TouchButton::Down ? Vector2{0, 1}
                                   : button == TouchButton::Left ? Vector2{-1, 0}
                                                                 : Vector2{1, 0};
            const Vector2 tip{center.x + 10 * unit * direction.x, center.y + 10 * unit * direction.y};
            DrawLineEx({center.x - 9 * unit * direction.x, center.y - 9 * unit * direction.y}, tip, 3 * unit,
                       color);
            for (int side : {-1, 1})
                DrawLineEx(tip,
                           {center.x + unit * (2 * direction.x - side * 8 * direction.y),
                            center.y + unit * (2 * direction.y + side * 8 * direction.x)},
                           3 * unit, color);
        }
    }
}

UiAction Presentation::draw(const Game& game, DesktopUi& ui, Vector2 mouse, float real_seconds) {
    if (collecting()) {
        collection_age_ += std::max(0.f, real_seconds);
        if (collection_age_ >= .62f || collection_floor_ != game.hero.floor || ui.home || ui.replay_active)
            collected_.clear();
    }
    const auto context = touch_context(game, ui);
    touch_context_ = TouchContext::Hidden;
    const auto view = window_viewport();
    const auto buttons = touch_buttons(view);
    const Vector2 screen_mouse{view.area.x + mouse.x * view.area.width / CanvasWidth,
                               view.area.y + mouse.y * view.area.height / CanvasHeight};
    std::optional<TouchButton> hovered;
    for (int i = 0; i < int(buttons.size()); ++i)
        if (CheckCollisionPointRec(screen_mouse, buttons[i]))
            hovered = static_cast<TouchButton>(i);
    bool down = IsMouseButtonDown(MOUSE_BUTTON_LEFT), pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
#ifdef __EMSCRIPTEN__
    // Pointer capture in the shell also cancels holds on blur, page hiding and touch cancellation.
    down = EM_ASM_INT({ return !!Module['tswPointerDown']; });
    const int serial = EM_ASM_INT({ return Module['tswPointerSerial'] | 0; });
    pressed = serial != pointer_serial_;
    pointer_serial_ = serial;
    pointer_cancelled_ = EM_ASM_INT({ return !!Module['tswPointerCancelled']; });
#elif defined(__ANDROID__)
    down = down && IsWindowFocused();
    pointer_cancelled_ = !IsWindowFocused() || android_pointer_cancelled;
#endif
    pointer_down_ = down;
    pointer_pressed_ = pressed;
    if (!down || pointer_cancelled_ || ui.menu != Menu::Options || ui.settings_tab != SettingsTab::Game)
        speed_dragging_ = false;
    if (!game.dialogue || ui.menu != Menu::None || ui.help || ui.replay_active)
        dialogue_dragging_ = false;
    const auto touch_input = touch_.update(context, hovered, down, pressed, real_seconds,
                                           context != TouchContext::Walk || !game.busy());
    // Closing a panel must consume its click instead of selecting the floor underneath.
    const auto destination = mouse_destination(game, ui, mouse);
#ifndef __ANDROID__
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
#endif
    art_->text.select_language(ui.language);
    resize_canvas(view);
    const auto mode = game.visual.raster_mode;
    if (!ui.home) {
        if ((mode == RasterMode::OpeningDissolve || mode == RasterMode::EndingDissolve) &&
            previous_raster_ != mode && !cache_valid_)
            cache_requested_ = true;
        if (cache_requested_)
            cache_scene();
        previous_raster_ = mode;
    }
    BeginTextureMode(canvas_.get());
    // Layout stays in original logical coordinates; rasterization uses the actual display pixels.
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, CanvasWidth, CanvasHeight, 0, 0, 1);
    rlMatrixMode(RL_MODELVIEW);
    ClearBackground(Bar);
    if (!ui.home && ui.ending_wait && game.ending_summary && ui.menu == Menu::None) {
        const auto action = draw_ending_summary(*game.ending_summary, ui, mouse);
        EndTextureMode();
        return action;
    }
    if (ui.home) {
        const bool overlay =
            ui.save_picker != SavePicker::None || ui.replay_picker || ui.rankings || ui.menu != Menu::None;
        auto action = draw_home(ui, overlay ? Vector2{-1, -1} : mouse);
        if (ui.save_picker != SavePicker::None)
            action = draw_save_slots(game, ui, mouse);
        else if (ui.replay_picker)
            action = draw_replays(ui, mouse);
        else if (ui.rankings)
            action = draw_rankings(game, ui, mouse);
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
    if (mode != RasterMode::Title)
        draw_board(game, ui.flight >= 0 ? ui.flight : game.hero.floor, ui.flight < 0);
    draw_realtime_orb(game, ui);
    UiAction action;
    const auto game_mouse = ui.replay_active || ui.menu == Menu::About ? Vector2{-1, -1} : mouse;
    if (!hide_panels_)
        action = draw_panels(game, ui, game_mouse);
    if (mode == RasterMode::Title || (mode >= RasterMode::OpeningDissolve && mode <= RasterMode::ClosingCard))
        draw_scene(game);
    if (ui.save_picker != SavePicker::None)
        action = draw_save_slots(game, ui, mouse);
    else if (ui.replay_picker)
        action = draw_replays(ui, mouse);
    else if (ui.rankings)
        action = draw_rankings(game, ui, mouse);
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
        if (art_->text.button({218, 3, 62, 22}, "About", mouse)) {
            const bool opened = ui.menu == Menu::About;
            ui.close_overlays();
            ui.menu = opened ? Menu::None : Menu::About;
        }
        const auto label = std::format(
            "{}{}x  /  {}{}", game.hero.cycle_factor_minus_one ? "Backside  /  " : "", ui.animation_speed,
            ui.muted ? "Music off" : "Music on", ui.recording_active ? "  /  Recording" : "");
        art_->text.fit(label, {440, 3, 350, 22}, 17, Muted, {.alignment = TextAlignment::Right});
    }
    if (ui.menu != Menu::None)
        action = draw_menu(game, ui, mouse);

    DrawRectangle(0, MenuHeight + ContentHeight, CanvasWidth, StatusHeight, Color{82, 80, 83, 255});
    DrawLine(0, MenuHeight + ContentHeight, CanvasWidth, MenuHeight + ContentHeight, Border);
    std::string status =
        ui.flight >= 0 ? std::format("Previewing floor {}. Up / Down to choose; Enter to travel.", ui.flight)
                       : localized_status(art_->text.language, game);
    bool translate_status = ui.flight >= 0;
    if (ui.ending_wait) {
        status = "The End. Press Enter / Space to continue to the backside tower.";
        translate_status = true;
    }
    if (ui.replay_active) {
        const std::string state =
            ui.replay_paused
                ? (ui.replay_step == ui.replay_count && !ui.replay_in_progress ? "Finished" : "Paused")
                : "Playing";
        status = ui.replay_error.empty()
                     ? localized_text(art_->text.language, state) + "  /  " + ui.replay_name + "  /  " +
                           localized_status(art_->text.language, game)
                     : ui.replay_error;
    }
    if (!ui.replay_active && !ui.modal() && !game.dialogue && ui.flight < 0) {
        int owned = 0;
        for (int i = 0; i < ItemCount; ++i)
            if (game.inventory(static_cast<Item>(i)) > 0) {
                if (CheckCollisionPointRec(
                        mouse, {16.f + owned % 3 * 42, MenuHeight + 238.f + owned / 3 * 40, 42, 40})) {
                    const auto item = static_cast<Item>(i);
                    status = std::string(Game::item_name(item)) +
                             (use_item_directly(item, ui) ? "  -  click to use" : "  -  click to inspect");
                    translate_status = true;
                    if (ui.item_use_mode == ItemUseMode::Describe)
                        art_->text.tooltip(
                            {16.f + owned % 3 * 42, MenuHeight + 238.f + owned / 3 * 40, 42, 40},
                            localized_text(ui.language, item_definition(item).description));
                }
                ++owned;
            }
    }
    if (ui.realtime_hero_orb && !ui.modal() && !game.busy() && ui.flight < 0 &&
        CheckCollisionPointRec(mouse, MapArea) && mouse.x < BoardX + BoardPixels &&
        mouse.y < BoardY + BoardPixels) {
        const int index = cell(int((mouse.x - BoardX) / TileSize), int((mouse.y - BoardY) / TileSize));
        if (const auto info = orb_tile_info(game, game.hero.floor, index, ui.hero_orb_actual_damage)) {
            status = std::format("{} | HP {} | ATK {} | DEF {} | Gold {} | HP cost {}",
                                 Game::monster_name(info->monster_index), info->hp, info->attack,
                                 info->defense, info->gold,
                                 info->forecast.penetrates ? std::to_string(info->forecast.damage) : "∞");
            translate_status = true;
        }
    }
    art_->text.fit(
        status,
        {7, MenuHeight + ContentHeight + 3, ui.ending_wait ? 643.f : CanvasWidth - 14.f, StatusHeight - 6},
        17, Ink, {.translate = translate_status && !ui.replay_active});
    if (ui.ending_wait && !ui.replay_active &&
        art_->text.button({658, MenuHeight + ContentHeight + 3, 135, StatusHeight - 6}, "Continue", mouse,
                          !ui.modal()))
        action = {Action::ContinueEnding};
    if (!ui.replay_active)
        draw_qol_status(ui, {220, 3, 132, 22}, mouse);
    if (!hide_panels_ && context == touch_context(game, ui)) {
        const auto control = draw_touch_controls(game, context, touch_input);
        if (control.kind != Action::None && action.kind == Action::None)
            action = control;
    }
    if (destination && mouse_destination(game, ui, mouse)) {
        if (!mouse_path(game, *destination).empty()) {
            const Rectangle target{float(BoardX + *destination % BoardWidth * TileSize),
                                   float(BoardY + *destination / BoardWidth * TileSize), TileSize, TileSize};
            art_->text.outline(target, 1.f, Gold);
#ifndef __ANDROID__
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
#endif
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            action = {Action::WalkTo, *destination};
    }
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
    DrawTexturePro(canvas_.get().texture,
                   {0, 0, float(canvas_.get().texture.width), -float(canvas_.get().texture.height)},
                   view.area, {0, 0}, 0, WHITE);
    paint_touch_controls(view);
    EndDrawing();
}

Image Presentation::capture_window() const {
    const auto view = window_viewport();
    return {rlReadScreenPixels(view.framebuffer_width, view.framebuffer_height), view.framebuffer_width,
            view.framebuffer_height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
}

Image Presentation::capture_native_canvas() const {
    detail::UniqueImage image(LoadImageFromTexture(canvas_.get().texture));
    ImageFlipVertical(image.address());
    return image.release();
}

Image Presentation::capture_canvas() const {
    detail::UniqueImage image(capture_native_canvas());
    if (image.get().width == CanvasWidth && image.get().height == CanvasHeight)
        return image.release();
    // Sample logical pixel centers. ImageResizeNN samples left edges, which shifts
    // sprite pixels when the native canvas has a fractional scale such as 1.5x.
    detail::UniqueImage logical(GenImageColor(CanvasWidth, CanvasHeight, BLANK));
    const auto* source = static_cast<const Color*>(image.get().data);
    auto* destination = static_cast<Color*>(logical.get().data);
    for (int y = 0; y < CanvasHeight; ++y)
        for (int x = 0; x < CanvasWidth; ++x) {
            const int sx = (2 * x + 1) * image.get().width / (2 * CanvasWidth);
            const int sy = (2 * y + 1) * image.get().height / (2 * CanvasHeight);
            destination[y * CanvasWidth + x] = source[sy * image.get().width + sx];
        }
    return logical.release();
}

bool Presentation::screenshot(const std::filesystem::path& path) const {
    detail::UniqueImage capture(capture_canvas());
    return ExportImage(capture.get(), path.string().c_str());
}
} // namespace tsw
