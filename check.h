/*
  Test helpers.

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

#ifndef HAVE_POOL_CHECK_H_
#define HAVE_POOL_CHECK_H_

#ifdef __cplusplus
extern "C" {
#endif

struct fold_results { int min, max, sum, product; };

void check_folds(const struct fold_results *resp,
                 int min, int max, int sum, int product);

void check(int count, const char *label, ...);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_CHECK_H_ */
