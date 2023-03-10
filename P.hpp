// Temporarily wraps a container by its iterators and makes it printable.
//
// Copyright (c) 2018 Eliah Kagan
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef HAVE_POOL_P_HPP_
#define HAVE_POOL_P_HPP_

#include <algorithm>
#include <iterator>
#include <ostream>
#include <string_view>
#include <type_traits>

namespace ek {
    namespace detail {
        template<typename C>
        constexpr auto my_cbegin(const C& c) noexcept
        {
            using std::cbegin;
            return cbegin(c);
        }

        template<typename C>
        constexpr auto my_cend(const C& c) noexcept
        {
            using std::cend;
            return cend(c);
        }

        template<typename C>
        using First = decltype(my_cbegin(std::declval<const C&>()));

        template<typename C>
        using Last = decltype(my_cend(std::declval<const C&>()));
    }

    template<typename C>
    class P;

    template<typename C>
    std::ostream& operator<<(std::ostream& out, P<C> printer);

    template<typename C>
    class P {
        static_assert(!std::is_reference_v<C>);

    public:
        explicit constexpr P(const C& c,
                             std::string_view prefix = "{",
                             std::string_view suffix = "}",
                             std::string_view separator = ", ") noexcept;

        P(const P&) = delete;
        P(P&&) = delete;
        P& operator=(const P&) = delete;
        P& operator=(P&&) = delete;
        ~P() = default;

    private:
        std::string_view prefix_;
        std::string_view suffix_;
        std::string_view separator_;
        detail::First<C> first_;
        detail::Last<C> last_;

        friend std::ostream& operator<< <C>(std::ostream&, P<C>);
    };

    template<typename C>
    constexpr P<C>::P(const C& c, std::string_view prefix,
                                  std::string_view suffix,
                                  std::string_view separator) noexcept
        : prefix_{prefix}, suffix_{suffix}, separator_{separator},
          first_{detail::my_cbegin(c)}, last_{detail::my_cend(c)}
    {
    }

    template<typename C>
    std::ostream& operator<<(std::ostream& out, const P<C> printer)
    {
        out << printer.prefix_;

        std::string_view sep {};
        std::for_each(printer.first_, printer.last_, [&](const auto& x) {
            out << sep << x;
            sep = printer.separator_;
        });

        return out << printer.suffix_;
    }
}

#endif // ! HAVE_POOL_P_HPP_
