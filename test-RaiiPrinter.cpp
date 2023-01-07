// A function object that uses RAII to print an enclosed, delimited sequence of
// items, one per call - tests.
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
