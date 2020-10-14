#pragma once

#include <Reme/Core/Alias.h>

namespace Reme {

template<typename T>
class Badge {
    friend T;
    Badge() {}

    Badge(const Badge&) = delete;
    Badge& operator=(const Badge&) = delete;

    Badge(Badge&&) = delete;
    Badge& operator=(Badge&&) = delete;
};

} // namespace Reme
