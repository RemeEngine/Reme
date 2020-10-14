#include <Reme/Impl/OpenGL/OpenGL_Texture.h>

#include <glad/glad.h>

namespace Reme {

bool isPowerOf2(u32 x)
{
    return (x & (x - 1)) == 0;
}

OpenGL_Texture::OpenGL_Texture(u32 width, u32 height)
    : m_width(width)
    , m_height(height)
{
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGL_Texture::OpenGL_Texture(const RefPtr<Image>& img)
    : m_width(img->width())
    , m_height(img->height())
{
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img->pixels_data()[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    generate_mipmap();
}

OpenGL_Texture::~OpenGL_Texture()
{
    glDeleteTextures(1, &m_texture_id);
}

void OpenGL_Texture::generate_mipmap() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    if (isPowerOf2(m_width) && isPowerOf2(m_width)) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void OpenGL_Texture::set_data(const Color* data, u32 x, u32 y, u32 width, u32 height)
{
    if (width == 0)
        width = m_width;
    if (height == 0)
        height = m_height;

    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void OpenGL_Texture::bind(u32 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

} // namespace Reme
