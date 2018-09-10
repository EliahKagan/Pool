#ifndef HAVE_POOL_LISTNODE_IDENTITY_H_
#define HAVE_POOL_LISTNODE_IDENTITY_H_

template<typename T>
struct Identity {
    using type = T;
};

template<typename T>
using IdentityType = typename Identity<T>::type;

#endif // ! HAVE_POOL_LISTNODE_IDENTITY_H_
