#pragma once

#include <Reme/Core/Core.h>
#include <unordered_map>

namespace Reme {

class Asset;

class AssetManager {
public:
    static RefPtr<Asset> get_asset(u32 uid)
    {
        auto it = s_asset_map.find(uid);
        if (it == s_asset_map.end())
            return nullptr;

        return s_asset_map.at(uid).lock();
    }

    template<typename T>
    static RefPtr<T> get(u32 uid)
    {
        auto result = get_asset(uid);
        if (result == nullptr)
            return nullptr;

        return std::dynamic_pointer_cast<T>(result);
    }

    static u32 next_uid();

private:
    friend Asset;
    static void put_asset(Asset&);

    static u32 s_uid_count;
    static std::unordered_map<u32, WeakPtr<Asset>> s_asset_map;
};

class Asset : public RefCounted<Asset> {
public:
    Asset()
        : m_uid(AssetManager::next_uid())
    {
        AssetManager::put_asset(*this);
    }

    virtual ~Asset() {};

    u32 uid() const { return m_uid; }

private:
    u32 m_uid { 0 };
};

} // namespace Reme
