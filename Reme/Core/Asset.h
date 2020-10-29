#pragma once

#include <Reme/Core/Core.h>
#include <unordered_map>

namespace Reme {

using AssetUID = u32;

class Asset;

class AssetManager {
public:
    static AssetUID next_uid();
    static RefPtr<Asset> get_asset(AssetUID uid);

    template<typename T>
    static RefPtr<T> get(AssetUID uid)
    {
        auto result = get_asset(uid);
        if (result == nullptr)
            return nullptr;

        return std::static_pointer_cast<T>(result);
    }

private:
    friend Asset;

    static void add(const Asset*);
    static void remove(AssetUID uid);
};

class Asset : public RefCounted<Asset> {
public:    
    template<typename T, typename... Args>
    ALWAYS_INLINE static RefPtr<T> make(Args&&... args)
    {
        RefPtr<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);        
        AssetManager::add(ptr.get());

#ifdef REME_TRACE_ASSET_LIFETIME
        CORE_LOG_TRACE("Created ({}) {}", ptr->uid(), ptr->class_name());
#endif

        return ptr;
    }

    virtual ~Asset()
    {
        AssetManager::remove(uid());
    };

    ALWAYS_INLINE AssetUID uid() const { return m_uid; }
    virtual const char* class_name() const = 0;

protected:
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

} // namespace Reme
