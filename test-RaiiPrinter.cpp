#include "RaiiPrinter.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace {
    using namespace std::literals;

    void simple_test()
    {
        char bar[] {"bar"};

        ek::RaiiPrinter print {std::cout, ", ", "((", "))\n"};
        print("foo");
        print(42);

        ek::RaiiPrinter print2 {std::move(print)};
        print2(bar);
        print2("baz"s);

        ek::RaiiPrinter print3 {std::move(print)};
        print3 = std::move(print2);
        print3("quux"sv);
    }

    void run_simple_test()
    {
        std::cout << "Starting the SIMPLE test...\n";
        simple_test();
        std::cout << "...SIMPLE test done.\n\n";
    }

    void exceptions_test()
    {
        char bar[] {"bar"};

        try {
            ek::RaiiPrinter print {std::cout, ", ", "((", "))\n"};
            print("foo");
            print(42);
            print(bar);
            print("baz"s);
            throw std::runtime_error{"meaningless exception for testing"};
            //print("quux"sv);
        }
        catch (const std::runtime_error& e) {
            std::cout << "Got exception: " << e.what() << '\n';
        }
    }

    void run_exceptions_test()
    {
        std::cout << "Starting the EXCEPTIONS test...\n";
        exceptions_test();
        std::cout << "...EXCEPTIONS test done.\n\n";
    }
}

int main()
{
    run_simple_test();
    run_exceptions_test();
}
