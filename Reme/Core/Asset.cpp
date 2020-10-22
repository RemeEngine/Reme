#include <Reme/Core/Asset.h>

namespace Reme {

AssetUID AssetManager::s_uid_count = 1;
std::unordered_map<AssetUID, WeakPtr<Asset>> AssetManager::s_asset_map;

AssetUID AssetManager::next_uid()
{
    return s_uid_count++;
}

} // namespace Reme
