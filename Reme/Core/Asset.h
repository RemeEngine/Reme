#pragma once

#include <Reme/Core/Core.h>
#include <unordered_map>

namespace Reme {

using AssetUID = u32;

class Asset;

class AssetManager {
public:
    static AssetUID next_uid();

    template<typename T>
    static RefPtr<T> adopt_asset(T& asset)
    {
        auto ptr = RefPtr<T>(&asset, [](T* ptr) {
#ifdef REME_TRACE_ASSET_LIFETIME
            CORE_LOG_TRACE("Removed ({}) {}", ptr->uid(), ptr->class_name());
#endif
            delete ptr;
        });

        s_asset_map[ptr->uid()] = ptr->weak_from_this();

#ifdef REME_TRACE_ASSET_LIFETIME
        CORE_LOG_TRACE("Created ({}) {}", ptr->uid(), ptr->class_name());
#endif

        return ptr;
    }

    static RefPtr<Asset> get_asset(AssetUID uid)
    {
        auto it = s_asset_map.find(uid);
        if (it == s_asset_map.end())
            return nullptr;

        auto asset = it->second;
        if (asset.expired()) {
            s_asset_map.erase(it);
            return nullptr;
        }

        return asset.lock();
    }

    template<typename T>
    static RefPtr<T> get(AssetUID uid)
    {
        auto result = get_asset(uid);
        if (result == nullptr)
            return nullptr;

        return std::dynamic_pointer_cast<T>(result);
    }

private:
    friend Asset;

    static AssetUID s_uid_count;
    static std::unordered_map<AssetUID, WeakPtr<Asset>> s_asset_map;
};

class Asset : public RefCounted<Asset> {
public:
    virtual ~Asset()
    {
        if (!AssetManager::get_asset(uid()))
            CORE_LOG_WARN("An asset (uid={}) was create and remove without using 'make_asset'");
    };

    ALWAYS_INLINE AssetUID uid() const { return m_uid; }
    virtual const char* class_name() const = 0;

protected:
    friend AssetManager;

    Asset()
        : m_uid(AssetManager::next_uid())
    {
    }

private:
    AssetUID m_uid { 0 };
};

class NoncopyableAsset : public Asset {
    MAKE_NONCOPYABLE(NoncopyableAsset);

public:
    virtual ~NoncopyableAsset() {};

protected:
    NoncopyableAsset() {};
};

template<typename T, typename... Args>
ALWAYS_INLINE constexpr RefPtr<T> make_asset(Args&&... args)
{
    return AssetManager::adopt_asset<T>(*new T(std::forward<Args>(args)...));
}

} // namespace Reme
