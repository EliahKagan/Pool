#ifndef HAVE_POOL_MUTATORS_H_
#define HAVE_POOL_MUTATORS_H_

#ifdef __cplusplus
extern "C" {
#endif

void increment(int *elemp);
void increase_by(int *elemp, void *deltap);

#ifdef __cplusplus
}
#endif

#endif /* ! HAVE_POOL_MUTATORS_H_ */
