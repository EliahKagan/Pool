#include <cstdio>
#include <cstdlib>

#include "check.h"
#include "util.h"

namespace {
    auto s_failure_expected = false;
}

extern "C" {
    static void on_exit(void)
    {

    }
}

int main()
{
    check(3, "test 1", 11, 22, 33, 11, 22, 33); // should match

    s_failure_expected = true;
    check(3, "test 1", 11, 22, 33, 11, 22, 34); // should not match

    std::quick_exit(EXIT_FAILURE);
}
