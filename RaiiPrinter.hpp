// A function object that uses RAII to print an enclosed, delimited sequence of
// items, one per call.
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

#ifndef HAVE_POOL_RAIIPRINTER_HPP_
#define HAVE_POOL_RAIIPRINTER_HPP_

#include <iostream>
#include <stdexcept>
#include <string_view>

namespace ek {
    class BadRaiiPrinterCall : public std::logic_error {
    public:
        BadRaiiPrinterCall();

        BadRaiiPrinterCall(const BadRaiiPrinterCall&) = default;
        BadRaiiPrinterCall& operator=(const BadRaiiPrinterCall&) = default;

        // The destructor is defaulted out-of-line to avoid "weak vtables."
        ~BadRaiiPrinterCall() override;
    };

    class RaiiPrinter {
    public:
        explicit RaiiPrinter(std::ostream& out = std::cout,
                             std::string_view separator = ", ",
                             std::string_view prefix = "(",
                             std::string_view suffix = ")\n") noexcept;

        RaiiPrinter(const RaiiPrinter&) = delete;
        RaiiPrinter(RaiiPrinter&& other) noexcept;
        RaiiPrinter& operator=(const RaiiPrinter&) = delete;
        RaiiPrinter& operator=(RaiiPrinter&& other) noexcept;
        ~RaiiPrinter();

        template<typename T>
        void operator()(const T& x);

    private:
        void close() noexcept;

        std::string_view suffix_;
        std::string_view separator_;
        std::string_view real_separator_;
        std::ostream* outp_;
        bool suppressed_;
        int uncaught_exceptions_;
    };

    template<typename T>
    void RaiiPrinter::operator()(const T& x)
    {
        if (suppressed_) throw BadRaiiPrinterCall{};
        *outp_ << real_separator_ << x;
        real_separator_ = separator_;
    }

    inline RaiiPrinter::~RaiiPrinter()
    {
        close();
    }
}

#endif // ! HAVE_POOL_RAIIPRINTER_HPP_
