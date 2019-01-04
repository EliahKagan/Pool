#include <cstdio>
#include <cstdlib>

#include "check.h"
#include "util.h"

namespace {
    auto s_failure_expected = false;

    [[noreturn]] void close_stdout_and_quit(const int status)
    {
        std::fclose(stdout);
        std::_Exit(status);
    }
}

extern "C" {
    [[noreturn]] static void on_exit(void)
    {
        close_stdout_and_quit(s_failure_expected ? EXIT_SUCCESS
                                                 : EXIT_FAILURE);
    }
}

int main()
{
    xatexit(on_exit);

    check(3, "test 1", 11, 22, 33, 11, 22, 33); // should match

    s_failure_expected = true;
    check(3, "test 1", 11, 22, 33, 11, 22, 34); // should not match

    close_stdout_and_quit(EXIT_FAILURE);
}
