#pragma once

#include <Reme/Core/Core.h>
#include <unordered_map>

namespace Reme {

class Asset;

class AssetManager {
public:
    static u32 next_uid();

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

    static RefPtr<Asset> get_asset(u32 uid)
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
    static RefPtr<T> get(u32 uid)
    {
        auto result = get_asset(uid);
        if (result == nullptr)
            return nullptr;

        return std::dynamic_pointer_cast<T>(result);
    }

private:
    friend Asset;

    static u32 s_uid_count;
    static std::unordered_map<u32, WeakPtr<Asset>> s_asset_map;
};

class Asset : public RefCounted<Asset> {
public:
    virtual ~Asset() {};
    ALWAYS_INLINE u32 uid() const { return m_uid; }
    virtual const char* class_name() const = 0;

protected:
    friend AssetManager;

    Asset()
        : m_uid(AssetManager::next_uid())
    {
    }

private:
    u32 m_uid { 0 };
};

template<typename T, typename... Args>
ALWAYS_INLINE constexpr RefPtr<T> make_asset(Args&&... args)
{
    return AssetManager::adopt_asset<T>(*new T(std::forward<Args>(args)...));
}

} // namespace Reme
