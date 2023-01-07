// Meta-tests: tests of the ad-hoc testing infrastructure.
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

#include <cstdio>
#include <cstdlib>

#include "check.h"
#include "util.h"

namespace {
    auto s_failure_expected = false;

    [[noreturn]] void close_stdout_and_quit(const int status)
    {
        std::fclose(stdout); // flushes buffer, ensuring output is displayed
        std::_Exit(status);
    }
}

extern "C" {
    [[noreturn]] static void on_exit_cleanup(void)
    {
        close_stdout_and_quit(s_failure_expected ? EXIT_SUCCESS
                                                 : EXIT_FAILURE);
    }
}

int main()
{
    xatexit(on_exit_cleanup);

    check(3, "meta-test-can-pass", 11, 22, 33, 11, 22, 33); // should match

    s_failure_expected = true;
    check(3, "meta-test-can-fail", 11, 22, 33, 11, 22, 34); // should not match

    close_stdout_and_quit(EXIT_FAILURE);
}
