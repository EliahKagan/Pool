/* Actions useful with both array_foreach* and list_foreach* functions. */

#ifndef HAVE_POOL_ACTIONS_H_
#define HAVE_POOL_ACTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

void print_element(int x, void *sepp);
void print_alt_nonfirst_element(int x);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_ACTIONS_H_ */
