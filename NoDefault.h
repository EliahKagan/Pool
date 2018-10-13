#ifndef HAVE_POOL_NODEFAULT_H_
#define HAVE_POOL_NODEFAULT_H_

#include <cstddef>
#include <iterator>
#include <ostream>
#include <string_view>

namespace ek {
    template<typename T>
    class NoDefault {
    public:
        explicit NoDefault(const T& item) : item_{item} { }
        explicit NoDefault(T&& item) noexcept : item_{std::move(item)} { }

        operator const T&() const & noexcept { return item_; }
        operator T&() & noexcept { return item_; }
        operator const T&&() const && noexcept { return std::move(item_); }
        operator T&&() && noexcept { return std::move(item_); }

    private:
        T item_;
    };

    // This is needed to print a NoDefault<T> when the std::operator<< overload
    // that would match a T is an instance of a template, as in that situation
    // the implicit conversion from NoDefault lvalue to T reference does not
    // happen (because template argument deduction requires an exact match).
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const NoDefault<T>& nod)
    {
        return out << static_cast<const T&>(nod);
    }
}

namespace ek::literals {
    inline NoDefault<std::string_view> operator""_nsv(const char* const start,
                                                      const std::size_t count)
    {
        return NoDefault{std::string_view{start, count}};
    }
}

#endif // ! HAVE_POOL_NODEFAULT_H_
