#include "util.hpp"

enum CompSize : int {
    CS_NONE = 0,
    CS_UINT8 = sizeof(GLubyte),
    CS_SINT8 = sizeof(GLbyte),
    CS_UINT16 = sizeof(GLushort),
    CS_SINT16 = sizeof(GLshort),
    CS_UINT32 = sizeof(GLuint),
    CS_SINT32 = sizeof(GLint),
    CS_FLOAT32 = sizeof(GLfloat),
};

struct TextureFormatDescriptor {
    GLuint components;
    CompSize compSize;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
};

static const TextureFormatDescriptor formats[] = {
    { .components = 0, .compSize = CS_NONE, .internalFormat = GL_NONE, .format = GL_NONE, .type = GL_NONE },
    { .components = 1, .compSize = CS_UINT8, .internalFormat = GL_R8, .format = GL_RED, .type = GL_UNSIGNED_BYTE },
    { .components = 1, .compSize = CS_SINT8, .internalFormat = GL_R8_SNORM, .format = GL_RED, .type = GL_BYTE },
    { .components = 1, .compSize = CS_UINT8, .internalFormat = GL_R8UI, .format = GL_RED_INTEGER, .type = GL_UNSIGNED_BYTE },
    { .components = 1, .compSize = CS_SINT8, .internalFormat = GL_R8I, .format = GL_RED_INTEGER, .type = GL_BYTE },
    { .components = 1, .compSize = CS_UINT16, .internalFormat = GL_R16F, .format = GL_RED, .type = GL_HALF_FLOAT },
    { .components = 1, .compSize = CS_UINT16, .internalFormat = GL_R16UI, .format = GL_RED_INTEGER, .type = GL_UNSIGNED_SHORT },
    { .components = 1, .compSize = CS_SINT16, .internalFormat = GL_R16I, .format = GL_RED_INTEGER, .type = GL_SHORT },
    { .components = 2, .compSize = CS_UINT8, .internalFormat = GL_RG8, .format = GL_RG, .type = GL_UNSIGNED_BYTE },
    { .components = 2, .compSize = CS_SINT8, .internalFormat = GL_RG8_SNORM, .format = GL_RG, .type = GL_BYTE },
    { .components = 2, .compSize = CS_UINT8, .internalFormat = GL_RG8UI, .format = GL_RG_INTEGER, .type = GL_UNSIGNED_BYTE },
    { .components = 2, .compSize = CS_SINT8, .internalFormat = GL_RG8I, .format = GL_RG_INTEGER, .type = GL_BYTE },
    { .components = 1, .compSize = CS_FLOAT32, .internalFormat = GL_R32F, .format = GL_RED, .type = GL_FLOAT },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_R32UI, .format = GL_RED_INTEGER, .type = GL_UNSIGNED_INT },
    { .components = 1, .compSize = CS_SINT32, .internalFormat = GL_R32I, .format = GL_RED_INTEGER, .type = GL_INT },
    { .components = 2, .compSize = CS_UINT16, .internalFormat = GL_RG16F, .format = GL_RG, .type = GL_HALF_FLOAT },
    { .components = 2, .compSize = CS_UINT16, .internalFormat = GL_RG16UI, .format = GL_RG_INTEGER, .type = GL_UNSIGNED_SHORT },
    { .components = 2, .compSize = CS_SINT16, .internalFormat = GL_RG16I, .format = GL_RG_INTEGER, .type = GL_SHORT },
    { .components = 4, .compSize = CS_UINT8, .internalFormat = GL_RGBA8, .format = GL_RGBA, .type = GL_UNSIGNED_BYTE },
    { .components = 4, .compSize = CS_SINT8, .internalFormat = GL_RGBA8_SNORM, .format = GL_RGBA, .type = GL_BYTE },
    { .components = 4, .compSize = CS_UINT8, .internalFormat = GL_RGBA8UI, .format = GL_RGBA_INTEGER, .type = GL_UNSIGNED_BYTE },
    { .components = 4, .compSize = CS_SINT8, .internalFormat = GL_RGBA8I, .format = GL_RGBA_INTEGER, .type = GL_BYTE },
    { .components = 2, .compSize = CS_FLOAT32, .internalFormat = GL_RG32F, .format = GL_RG, .type = GL_FLOAT },
    { .components = 2, .compSize = CS_UINT32, .internalFormat = GL_RG32UI, .format = GL_RG_INTEGER, .type = GL_UNSIGNED_INT },
    { .components = 2, .compSize = CS_SINT32, .internalFormat = GL_RG32I, .format = GL_RG_INTEGER, .type = GL_INT },
    { .components = 4, .compSize = CS_UINT16, .internalFormat = GL_RGBA16F, .format = GL_RGBA, .type = GL_HALF_FLOAT },
    { .components = 4, .compSize = CS_UINT16, .internalFormat = GL_RGBA16UI, .format = GL_RGBA_INTEGER, .type = GL_UNSIGNED_SHORT },
    { .components = 4, .compSize = CS_SINT16, .internalFormat = GL_RGBA16I, .format = GL_RGBA_INTEGER, .type = GL_SHORT },
    { .components = 4, .compSize = CS_FLOAT32, .internalFormat = GL_RGBA32F, .format = GL_RGBA, .type = GL_FLOAT },
    { .components = 4, .compSize = CS_SINT32, .internalFormat = GL_RGBA32I, .format = GL_RGBA_INTEGER, .type = GL_INT },
    { .components = 4, .compSize = CS_UINT32, .internalFormat = GL_RGBA32UI, .format = GL_RGBA_INTEGER, .type = GL_UNSIGNED_INT },
    { .components = 4, .compSize = CS_UINT8, .internalFormat = GL_SRGB8_ALPHA8, .format = GL_RGBA, .type = GL_UNSIGNED_BYTE },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_RGB9_E5, .format = GL_RGB, .type = GL_UNSIGNED_INT_5_9_9_9_REV },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_RGB10_A2UI, .format = GL_RGBA_INTEGER, .type = GL_UNSIGNED_INT_2_10_10_10_REV },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_RGB10_A2, .format = GL_RGBA, .type = GL_UNSIGNED_INT_2_10_10_10_REV },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_R11F_G11F_B10F, .format = GL_RGB, .type = GL_UNSIGNED_INT_10F_11F_11F_REV },
    { .components = 1, .compSize = CS_UINT16, .internalFormat = GL_DEPTH_COMPONENT16, .format = GL_DEPTH_COMPONENT, .type = GL_UNSIGNED_SHORT },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_DEPTH_COMPONENT24, .format = GL_DEPTH_COMPONENT, .type = GL_UNSIGNED_INT },
    { .components = 1, .compSize = CS_UINT32, .internalFormat = GL_DEPTH24_STENCIL8, .format = GL_DEPTH_STENCIL, .type = GL_UNSIGNED_INT },
    { .components = 1, .compSize = CS_FLOAT32, .internalFormat = GL_DEPTH_COMPONENT32F, .format = GL_DEPTH_COMPONENT, .type = GL_FLOAT },
};

void Framebuffer::init(void* initialPixels) {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &texture);
    const TextureFormatDescriptor* tfdesc = &formats[format];
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, tfdesc->internalFormat, maxWidth, maxHeight, 0, tfdesc->format, tfdesc->type, initialPixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void Framebuffer::bindTexture(GLuint textureSlot) const {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texture);
}

GLenum Framebuffer::readPixels(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLint* format, GLint* type, long* bufferSize, void* pixels) {
    glReadBuffer(GL_COLOR_ATTACHMENT0);

    if (pixels == nullptr) {
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, format);
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, type);

        int components = 0;

        switch (*format) {
        case GL_RED:
            components = 1;
            break;
        case GL_RG:
            components = 2;
            break;
        case GL_RGB:
            components = 3;
            break;
        case GL_RGBA:
            components = 4;
            break;
        case GL_RED_INTEGER:
            components = 1;
            break;
        case GL_RG_INTEGER:
            components = 2;
            break;
        case GL_RGB_INTEGER:
            components = 3;
            break;
        case GL_RGBA_INTEGER:
            components = 4;
            break;
        default:
            return GL_FALSE;
        }

        CompSize compSize = CS_NONE;

        switch (*type) {
        case GL_BYTE:
            compSize = CS_SINT8;
            break;
        case GL_SHORT:
            compSize = CS_SINT16;
            break;
        case GL_INT:
            compSize = CS_SINT32;
            break;
        case GL_UNSIGNED_BYTE:
            compSize = CS_UINT8;
            break;
        case GL_UNSIGNED_SHORT:
            compSize = CS_UINT16;
            break;
        case GL_UNSIGNED_INT:
            compSize = CS_UINT32;
            break;
        default:
            return GL_FALSE;
        }

        *bufferSize = components * compSize;
    } else {
        glReadPixels(xoffset, yoffset, width, height, *format, *type, pixels);
    }

    return GL_TRUE;
}

void Texture::init(void* pixels) {
    glGenTextures(1, &texture);
    const TextureFormatDescriptor* tfdesc = &formats[format];
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, tfdesc->internalFormat, width, height, 0, tfdesc->format, tfdesc->type, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

void Texture::bind(GLuint textureSlot) const {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::write(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, void* pixels) const {
    const TextureFormatDescriptor* tfdesc = &formats[format];
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, tfdesc->format, tfdesc->type, pixels);
}

void Texture::writeAll(void* pixels) const {
    const TextureFormatDescriptor* tfdesc = &formats[format];
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, tfdesc->format, tfdesc->type, pixels);
}
