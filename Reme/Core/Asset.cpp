#include <Reme/Core/Asset.h>

namespace Reme {

u32 AssetManager::s_uid_count = 1;
std::unordered_map<u32, WeakPtr<Asset>> AssetManager::s_asset_map;

u32 AssetManager::next_uid()
{
    return s_uid_count++;
}

} // namespace Reme
