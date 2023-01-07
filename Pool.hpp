// A trivial expanding object pool.
// Does not contract or reuse unreachable objects.
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

#ifndef HAVE_POOL_POOL_HPP_
#define HAVE_POOL_POOL_HPP_

#include <deque>
#include <utility>

namespace ek {
    template<typename T>
    class Pool {
    public:
        template<typename... Args>
        T* operator()(Args&&... args)
        {
            return &objects_.emplace_back(std::forward<Args>(args)...);
        }

    private:
        std::deque<T> objects_;
    };
}

#endif // ! HAVE_POOL_POOL_HPP_
