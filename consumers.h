#ifndef HAVE_POOL_CONSUMERS_H_
#define HAVE_POOL_CONSUMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Increases *accp by x. */
void increase_acc( int x, void *accp);

/* Decreases *accp by x. */
void decrease_acc( int x, void *accp);

/* Increases a shared variable by x. */
void increase_s_acc(int x);

/* Decreases a shared variable by x. */
void decrease_s_acc(int x);

/* Not a consumer, but provided to zero out the shared variable to 0. */
void reset_s_acc(void);

/* Not a consumer, but provided to inspect the value of the shared variable. */
int read_s_acc(void);

#ifdef __cplusplus
}
#endif

#endif /* ! HAVE_POOL_CONSUMERS_H_ */
