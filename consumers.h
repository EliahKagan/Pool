/*
  Element consumers, to pass to the "foreach" functions.

  Copyright (c) 2018 Eliah Kagan

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
  REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
  INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
  LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
  OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
  PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef HAVE_POOL_CONSUMERS_H_
#define HAVE_POOL_CONSUMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Increases *accp by x. */
void increase_acc(int x, void *accp);

/* Decreases *accp by x. */
void decrease_acc(int x, void *accp);

/* Increases a shared variable by x. */
void increase_s_acc(int x);

/* Decreases a shared variable by x. */
void decrease_s_acc(int x);

/* Not a consumer, but provided to zero out the shared variable to 0. */
void reset_s_acc(void);

/* Not a consumer, but provided to inspect the value of the shared variable. */
int read_s_acc(void);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_CONSUMERS_H_ */
