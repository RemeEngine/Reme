#include <Reme/Renderer/Image.h>

#include <stb/stb_image.h>
#include <stdlib.h>

namespace Reme {
Image::Image(u32 width, u32 height)
    : m_width(width)
    , m_height(height)
{
    m_pixels = new Color[m_width * m_height];
}

Image::Image(const std::string& path)
{
    int width, height, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data == nullptr) {
        CORE_LOG_ERROR("Failed to load image \"{}\"", path);
        CORE_LOG_INFO("Reason: {}", stbi_failure_reason());
        return;
    }

    CORE_LOG_TRACE("Image loaded an {}x{} image with {} color channels \"{}\"", width, height, channels, path);

    m_width = width;
    m_height = height;
    m_pixels = new Color[m_width * m_height];
    if (channels == 4) {
        memcpy(m_pixels, data, m_width * m_height * sizeof(Color));
        return;
    }

    u32 mod = channels;
    if (channels == 2) { // Grayscale with alpha
        mod = 1;
        for (u32 i = 0; i < m_width * m_height; i++)
            m_pixels[i].a = data[i * channels + 1];
    }

    for (u32 i = 0; i < m_width * m_height; i++) {
        m_pixels[i].r = data[i * channels + (0 % mod)];
        m_pixels[i].g = data[i * channels + (1 % mod)];
        m_pixels[i].b = data[i * channels + (2 % mod)];
    }
}

Image::~Image()
{
    delete[] m_pixels;
}

void Image::set_pixels_data(const Color* pixels)
{
    memcpy(&m_pixels[0], pixels, m_width * m_height);
}

void Image::copy(
    const RefPtr<Image>& source,
    u32 dX, u32 dY,
    u32 sX, u32 sY, u32 sW, u32 sH,
    bool applyAlpha)
{
    if (sW > source->width())
        sW = source->width();
    if (sH > source->height())
        sH = source->height();

    int width = sW;
    int height = sH;
    if (dX + width > m_width)
        width = m_width - dX;
    if (dY + height > m_height)
        height = m_height - dY;

    if (width <= 0 || height <= 0)
        return;

    int pitch = width;
    int rows = height;
    int srcStride = source->width();
    int dstStride = m_width;
    const Color* srcPixels = &source->pixels_data()[sX + sY * source->width()];
    Color* dstPixels = &m_pixels[dX + dY * m_width];

    // Copy the pixels
    if (applyAlpha) {
        // Interpolation using alpha values, pixel by pixel (slower)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < width; ++j) {
                // Get a direct pointer to the components of the current pixel
                const Color& src = *(srcPixels + j);
                Color& dst = *(dstPixels + j);

                // Interpolate RGBA components using the alpha value of the source pixel
                uint8_t alpha = src.a;
                dst.r = (src.r * alpha + dst.r * (255 - alpha)) / 255;
                dst.g = (src.g * alpha + dst.g * (255 - alpha)) / 255;
                dst.b = (src.b * alpha + dst.b * (255 - alpha)) / 255;
                dst.a = alpha + dst.a * (255 - alpha) / 255;
            }

            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    } else {
        // Optimized copy ignoring alpha values, row by row (faster)
        for (int i = 0; i < rows; ++i) {
            std::memcpy(dstPixels, srcPixels, pitch * sizeof(Color));
            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    }
}

} // namespace Reme
