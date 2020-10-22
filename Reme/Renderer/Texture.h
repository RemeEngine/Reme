#pragma once

#include <Reme/Core/Asset.h>
#include <Reme/Renderer/Color.h>
#include <Reme/Renderer/Image.h>

#include <string>

namespace Reme {
class Texture : public NoncopyableAsset {
public:
    static RefPtr<Texture> DEFAULT;
    static RefPtr<Texture> WHITE;

    static RefPtr<Texture> create(u32 width, u32 height);
    static RefPtr<Texture> create(const RefPtr<Image>& image);
    static RefPtr<Texture> create(const std::string& path);

    static void initialize();

public:
    virtual u32 width() const = 0;
    virtual u32 height() const = 0;
    virtual u32 internal_id() const = 0;

    virtual void generate_mipmap() const = 0;
    virtual void set_data(const Color* data, u32 x = 0, u32 y = 0, u32 width = 0, u32 height = 0) = 0;

    virtual void bind(u32 slot = 0) = 0;

    virtual const char* class_name() const override { return "Texture"; }
};
} // namespace Reme
