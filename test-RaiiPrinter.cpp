#include "RaiiPrinter.h"

#include <iostream>
#include <string>
#include <string_view>

namespace {
    using namespace std::literals;

    void test()
    {
        char bar[] {"bar"};

        ek::RaiiPrinter print {std::cout, ", ", "((", "))\n"};
        print("foo");
        print(42);
        print(bar);
        print("baz"s);
        print("quux"sv);
    }
}

int main()
{
    std::cout << "Starting the test...\n";
    test();
    std::cout << "...test done.\n";
}
