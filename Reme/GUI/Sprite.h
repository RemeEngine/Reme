#pragma once

#include <Reme/GUI/Node.h>
#include <Reme/Renderer/Texture.h>

namespace Reme::GUI {

class Sprite : public Node {
public:
    static RefPtr<Sprite> create(const std::string& path_to_image)
    {
        return Asset::make<Sprite>(Texture::create(path_to_image));
    }

    static RefPtr<Sprite> create(const RefPtr<Texture>& texture)
    {
        return Asset::make<Sprite>(texture);
    }

    Sprite(const RefPtr<Texture>& texture)
        : m_texture(texture)
    {
        set_size({ texture->width(), texture->height() });
    }

    virtual void render() override;

    inline virtual const char* class_name() const override { return "GUI::Sprite"; }

private:
    RefPtr<Texture> m_texture;
};

} // namespace Reme::GUI
