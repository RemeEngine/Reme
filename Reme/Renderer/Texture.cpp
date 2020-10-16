#include <Reme/Renderer/Texture.h>

#include <Reme/Core/Core.h>
#include <Reme/Impl/OpenGL/OpenGL_Texture.h>
#include <Reme/Renderer/RendererAPI.h>

namespace Reme {

RefPtr<Texture> Texture::DEFAULT;
RefPtr<Texture> Texture::WHITE;

void Texture::initialize()
{
    PROFILE_FUNCTION();

    Texture::DEFAULT = Texture::create(2, 2);
    Color rgbTextureData[] = { Color::RED, Color::GREEN, Color::BLUE, Color::WHITE };
    Texture::DEFAULT->set_data(rgbTextureData);
    // Texture::Default->GenerateMipmap();

    Texture::WHITE = Texture::create(1, 1);
    Texture::WHITE->set_data(&Color::WHITE);
    // Texture::White->GenerateMipmap();
}

RefPtr<Texture> Texture::create(u32 width, u32 height)
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return Texture::DEFAULT;
    case RendererAPI::OpenGL:
        return make_asset<OpenGL_Texture>(width, height);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return Texture::DEFAULT;
}

RefPtr<Texture> Texture::create(const RefPtr<Image>& image)
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return Texture::DEFAULT;
    case RendererAPI::OpenGL:
        return make_asset<OpenGL_Texture>(image);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return Texture::DEFAULT;
}

RefPtr<Texture> Texture::create(const std::string& path)
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return Texture::DEFAULT;
    case RendererAPI::OpenGL:
        return make_asset<OpenGL_Texture>(Image::create(path));
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return Texture::DEFAULT;
}

} // namespace Reme
