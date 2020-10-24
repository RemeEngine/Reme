#pragma once

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#include <string>

namespace Reme {

inline std::string demangle(const std::string& name)
{
#ifndef _MSC_VER
    int status = 0;
    auto* demangled_name = abi::__cxa_demangle(name.data(), nullptr, nullptr, &status);
    auto string = std::string(status == 0 ? demangled_name : name);
    if (status == 0)
        std::free(demangled_name);

    return string;
#else
    return name;
#endif
}

} // namespace Reme
