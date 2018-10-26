// A function object that uses RAII to print an enclosed, delimited sequence of
// items, one per call.

#ifndef HAVE_POOL_RAIIPRINTER_H_
#define HAVE_POOL_RAIIPRINTER_H_

#include <iostream>
#include <stdexcept>
#include <string_view>

namespace ek {
    class BadRaiiPrinterCall : public std::logic_error {
    public:
        BadRaiiPrinterCall();

        // The destructor is default out of line to avoid "weak vtables."
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

#endif // ! HAVE_POOL_RAIIPRINTER_H_
