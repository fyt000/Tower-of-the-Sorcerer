#pragma once
#include "raylib.h"
#include <utility>

namespace tsw::detail {
// A borrowed raylib handle is cheap to copy; its owner must never be copied.
// Keep these owners inside the lifetime of the window/graphics context.
template <class T, auto Unload, auto Valid> class RaylibResource {
  public:
    RaylibResource() = default;

    explicit RaylibResource(T value) noexcept : value_(value) {}

    ~RaylibResource() { reset(); }

    RaylibResource(const RaylibResource&) = delete;
    RaylibResource& operator=(const RaylibResource&) = delete;

    RaylibResource(RaylibResource&& other) noexcept : value_(std::exchange(other.value_, {})) {}

    RaylibResource& operator=(RaylibResource&& other) noexcept {
        if (this != &other) {
            reset();
            value_ = std::exchange(other.value_, {});
        }
        return *this;
    }

    T get() const noexcept { return value_; }

    T release() noexcept { return std::exchange(value_, {}); }

    T* address() noexcept { return &value_; }

    void reset(T value = {}) noexcept {
        if (Valid(value_))
            Unload(value_);
        value_ = value;
    }

  private:
    T value_{};
};

inline bool owns_image(Image image) {
    return image.data != nullptr;
}

inline bool owns_texture(Texture2D texture) {
    return texture.id != 0;
}

inline bool owns_render_texture(RenderTexture2D texture) {
    return texture.id != 0;
}

inline bool owns_shader(Shader shader) {
    return shader.id != 0;
}

inline bool owns_font(Font font) {
    return font.texture.id && font.texture.id != GetFontDefault().texture.id;
}

using UniqueImage = RaylibResource<Image, UnloadImage, owns_image>;
using UniqueTexture = RaylibResource<Texture2D, UnloadTexture, owns_texture>;
using UniqueRenderTexture = RaylibResource<RenderTexture2D, UnloadRenderTexture, owns_render_texture>;
using UniqueShader = RaylibResource<Shader, UnloadShader, owns_shader>;
using UniqueFont = RaylibResource<Font, UnloadFont, owns_font>;
} // namespace tsw::detail
