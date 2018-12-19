// A trivial expanding object pool.
// Does not contract or reuse unreachable objects.

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
