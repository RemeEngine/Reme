#pragma once

#include <cxxabi.h>
#include <string>

namespace Reme {

inline std::string demangle(const std::string_view& name)
{
    int status = 0;
    auto* demangled_name = abi::__cxa_demangle(name.data(), nullptr, nullptr, &status);
    auto string = std::string(status == 0 ? demangled_name : name);
    if (status == 0)
        std::free(demangled_name);

    return string;
}

} // namespace Reme
