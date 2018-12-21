#ifndef HAVE_POOL_FUNCTION_TYPES_H_
#define HAVE_POOL_FUNCTION_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*BinaryOp)(int, int);

typedef void (*Consumer)(int);
typedef void (*ConsumerEx)(int, void*);
typedef void (*Mutator)(int*);
typedef void (*MutatorEx)(int*, void*);

#ifdef __cplusplus
}
#endif

#endif /* ! HAVE_POOL_FUNCTION_TYPES_H_ */
