#include <Reme/Core/Asset.h>
#include <atomic>
#include <mutex>

namespace Reme {

static std::atomic<AssetUID> s_uid_count { 1 };

static std::mutex s_asset_mutex;
static std::unordered_map<AssetUID, WeakPtr<Asset>> s_asset_map;

AssetUID AssetManager::next_uid()
{
    return s_uid_count++;
}

RefPtr<Asset> AssetManager::get_asset(AssetUID uid)
{
    std::scoped_lock lock(s_asset_mutex);

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

void AssetManager::add(const Asset* ptr)
{
    std::scoped_lock lock(s_asset_mutex);
    s_asset_map.emplace(ptr->uid(), const_cast<Asset*>(ptr)->weak_from_this());
}

void AssetManager::remove(AssetUID uid)
{
    const std::lock_guard<std::mutex> lock(s_asset_mutex);

    auto it = s_asset_map.find(uid);
    if (it == s_asset_map.end()) {
        CORE_LOG_ERROR("AssetManager: Tried to remove asset with unknown uid ({})", uid);
        return;
    }

#ifdef REME_TRACE_ASSET_LIFETIME
    CORE_LOG_TRACE("Removed ({})", uid);
#endif

    s_asset_map.erase(it);
}

} // namespace Reme
