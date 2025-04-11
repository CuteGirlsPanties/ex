#pragma once

#include <glad/gles2.h>

enum TextureFormat : GLenum {
    TF_NONE,
    TF_R8_UNORM,
    TF_R8_SNORM,
    TF_R8_UINT,
    TF_R8_SINT,
    TF_R16_FLOAT,
    TF_R16_UINT,
    TF_R16_SINT,
    TF_RG8_UNORM,
    TF_RG8_SNORM,
    TF_RG8_UINT,
    TF_RG8_SINT,
    TF_R32_FLOAT,
    TF_R32_UINT,
    TF_R32_SINT,
    TF_RG16_FLOAT,
    TF_RG16_UINT,
    TF_RG16_SINT,
    TF_RGBA8_UNORM,
    TF_RGBA8_SNORM,
    TF_RGBA8_UINT,
    TF_RGBA8_SINT,
    TF_RG32_FLOAT,
    TF_RG32_UINT,
    TF_RG32_SINT,
    TF_RGBA16_FLOAT,
    TF_RGBA16_UINT,
    TF_RGBA16_SINT,
    TF_RGBA32_FLOAT,
    TF_RGBA32_SINT,
    TF_RGBA32_UINT,
    TF_RGBA8_UNORM_SRGB,
    TF_RGB9E5U_FLOAT,
    TF_RGB10A2_UINT,
    TF_RGB10A2_UNORM,
    TF_RG11B10U_FLOAT,
    TF_DEPTH16_UNORM,
    TF_DEPTH24PLUS,
    TF_DEPTH24PLUS_STENCIL8,
    TF_DEPTH32_FLOAT,
};

struct Framebuffer {
    GLsizei maxWidth;
    GLsizei maxHeight;
    TextureFormat format;

    GLuint framebuffer;
    GLuint texture;

    void init(void* initialPixels);
    void bind() const;
    void bindTexture(GLuint textureSlot) const;
    GLenum readPixels(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLint* format, GLint* type, long* bufferSize, void* pixels);
};

struct Texture {
    GLsizei width;
    GLsizei height;
    TextureFormat format;
    GLenum magFilter;
    GLenum minFilter;
    GLenum wrapS;
    GLenum wrapT;

    GLuint texture;

    void init(void* pixels);
    void bind(GLuint textureSlot) const;
    void write(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, void* pixels) const;
    void writeAll(void* pixels) const;
};
