#ifndef POOL_POOL_H_
#define POOL_POOL_H_

#include <deque>
#include <utility>

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

#endif // ! POOL_POOL_H_
