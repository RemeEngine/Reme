#pragma once

#include <Reme/Core/Alias.h>

namespace Reme {

template<typename T>
class Badge {
    MAKE_NONCOPYABLE(Badge)
    MAKE_NONMOVABLE(Badge)

private:
    Badge() {}
    friend class T;
};

} // namespace Reme