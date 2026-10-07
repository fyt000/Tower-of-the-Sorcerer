#include "assets.hpp"
#include "embedded_media.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_BMP
#define STBI_NO_STDIO
#define STBI_MALLOC(size) MemAlloc(static_cast<unsigned>(size))
#define STBI_REALLOC(pointer, size) MemRealloc(pointer, static_cast<unsigned>(size))
#define STBI_FREE(pointer) MemFree(pointer)
#include "stb_image.h"

namespace tsw {
namespace {
std::string lower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return char(std::tolower(c)); });
    return text;
}

std::filesystem::path resolve(const std::filesystem::path& root, const std::filesystem::path& relative) {
    auto path = root;
    for (const auto& part : relative) {
        const auto direct = path / part;
        if (std::filesystem::exists(direct)) {
            path = direct;
            continue;
        }
        if (!std::filesystem::is_directory(path))
            return direct;
        const auto name = lower(part.string());
        auto matched = direct;
        for (const auto& entry : std::filesystem::directory_iterator(path))
            if (lower(entry.path().filename().string()) == name) {
                matched = entry.path();
                break;
            }
        path = matched;
    }
    return path;
}

std::vector<unsigned char> read(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Missing game asset: " + path.string());
    const auto size = std::filesystem::file_size(path);
    if (!size || size > 64 * 1024 * 1024)
        throw std::runtime_error("Invalid game asset size: " + path.string());
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size));
    file.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!file)
        throw std::runtime_error("Unable to read game asset: " + path.string());
    return bytes;
}
} // namespace

bool Assets::exists(const std::filesystem::path& root) {
    return std::filesystem::is_regular_file(resolve(root, "Data3/Chtable.oz")) ||
           std::filesystem::is_regular_file(resolve(root, "original-atlas.png"));
}

Assets::Assets(const std::filesystem::path& root, const std::filesystem::path& executable)
    : root_(std::filesystem::absolute(root)), executable_(executable),
      original_(std::filesystem::is_regular_file(resolve(root, "Data3/Chtable.oz"))) {
    if (!exists(root_))
        throw std::runtime_error("Game assets not found in " + root_.string());
}

std::filesystem::path Assets::select(const std::filesystem::path& executable_directory,
                                     const std::filesystem::path& requested,
                                     const std::filesystem::path& development_original,
                                     const std::filesystem::path& development_extracted) {
    if (!requested.empty()) {
        if (!exists(requested))
            throw std::runtime_error("Game assets not found in --assets directory: " + requested.string());
        return requested;
    }
    for (const auto& path :
         {executable_directory, executable_directory / "assets", development_original, development_extracted})
        if (!path.empty() && exists(path))
            return path;
    throw std::runtime_error("Place the executable beside Data3, Data2, Midi and Wav, or pass --assets DIR");
}

Image Assets::image(std::string_view name) const {
    std::filesystem::path relative;
    const char* format = original_ ? ".bmp" : ".png";
    if (!original_)
        relative = std::string(name) + ".png";
    else if (name == "original-atlas")
        relative = "Data3/Chtable.oz";
    else if (name == "original-background-atlas")
        relative = "Data3/Chtableb.oz";
    else if (name.starts_with("data3-"))
        relative = std::filesystem::path("Data3") / (std::string(name.substr(6)) + ".bmp");
    else if (name.starts_with("data2-"))
        relative = std::filesystem::path("Data2") / (std::string(name.substr(6)) + ".bmp");
    const bool story = name == "data-exe-ending-story", card = name == "data-exe-ending-card";
    std::vector<unsigned char> bytes;
    if ((story || card) && (original_ || !std::filesystem::is_regular_file(resolve(root_, relative)))) {
        bytes =
            read_embedded_media(executable_, story ? EmbeddedMedia::EndingStory : EmbeddedMedia::EndingCard);
        format = ".bmp";
    } else {
        if (relative.empty())
            throw std::runtime_error("Unknown original image: " + std::string(name));
        bytes = read(resolve(root_, relative));
    }
    Image image{};
    if (std::string_view(format) == ".bmp") {
        int channels{};
        image.data =
            stbi_load_from_memory(bytes.data(), int(bytes.size()), &image.width, &image.height, &channels, 4);
        image.mipmaps = 1;
        image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    } else
        image = LoadImageFromMemory(format, bytes.data(), int(bytes.size()));
    if (!IsImageValid(image))
        throw std::runtime_error("Unable to decode game image: " + std::string(name));
    return image;
}

std::vector<unsigned char> Assets::midi(std::string_view name) const {
    return read(
        resolve(root_, std::filesystem::path(original_ ? "Midi" : "midi") / (std::string(name) + ".mid")));
}

std::vector<unsigned char> Assets::wave(std::string_view name) const {
    return read(
        resolve(root_, std::filesystem::path(original_ ? "Wav" : "wav") / (std::string(name) + ".wav")));
}

std::vector<unsigned char> Assets::soundfont() const {
    const auto external = executable_.parent_path() / "music.sf2";
    if (std::filesystem::is_regular_file(external))
        return read(external);
    return read_embedded_media(executable_, EmbeddedMedia::Soundfont);
}
} // namespace tsw
