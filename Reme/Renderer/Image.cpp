#include <Reme/Renderer/Image.h>

#include <stb/stb_image.h>

namespace Reme {
Image::Image(u32 width, u32 height)
    : m_width(width)
    , m_height(height)
    , m_pixels(width * height)
{
}

Image::Image(const std::string& path)
{
    int width, height, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (data == nullptr) {
        CORE_LOG_ERROR("Failed to load image \"{}\"", path);
        return;
    }

    m_width = width;
    m_height = height;
    m_pixels.reserve(width * height);
    memcpy(m_pixels.data(), data, width * height * sizeof(Color));

    stbi_image_free(data);
    CORE_LOG_TRACE("Image loaded an {}x{} image \"{}\"", width, height, path);
}

Image::~Image()
{
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
