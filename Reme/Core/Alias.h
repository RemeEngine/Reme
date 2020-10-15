#pragma once

#include <memory>

// Types
#include <cstdint>
#include <stddef.h>

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

static_assert(sizeof(i8) == 1);
static_assert(sizeof(u8) == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(i64) == 8);
static_assert(sizeof(u64) == 8);

using FlatPtr = intptr_t;

constexpr u32 KB = 1024;
constexpr u32 MB = KB * KB;
constexpr u32 GB = KB * KB * KB;

namespace std {
using nullptr_t = decltype(nullptr);
}

// Helper macro
#define BIT(x) (1 << x)
#define NO_DISCARD [[no_discard]]
#define MAYBE_UNUSED [[maybe_unused]]
#define ALWAYS_INLINE [[gnu::always_inline]]
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define MAKE_NONCOPYABLE(c) \
private:                    \
    c(const c&) = delete;   \
    c& operator=(const c&) = delete

#define MAKE_NONMOVABLE(c) \
private:                   \
    c(c&&) = delete;       \
    c& operator=(c&&) = delete

// Alias smart pointer
namespace Reme {
template<typename T>
using OwnPtr = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr OwnPtr<T> make_own(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using RefPtr = std::shared_ptr<T>;

template<typename T>
using RefCounted = std::enable_shared_from_this<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

class Asset;

template<typename T, typename... Args>
constexpr RefPtr<T> make(Args&&... args)
{
    static_assert(!std::is_base_of_v<Asset, T>, "We must use 'make_asset' instead of 'make' to create this");
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Reme
