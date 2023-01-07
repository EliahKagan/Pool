// A function object that uses RAII to print an enclosed, delimited sequence of
// items, one per call - implementation file.
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

#include <exception>

namespace ek {
    BadRaiiPrinterCall::BadRaiiPrinterCall()
        : std::logic_error{
                "call to moved-from (and not reassigned) RaiiPrinter"}
    {
    }

    BadRaiiPrinterCall::~BadRaiiPrinterCall() = default;

    RaiiPrinter::RaiiPrinter(std::ostream& out,
                             const std::string_view separator,
                             const std::string_view prefix,
                             const std::string_view suffix) noexcept
        : suffix_{suffix},
          separator_{separator},
          real_separator_ {},
          outp_{&out},
          suppressed_{false},
          uncaught_exceptions_{std::uncaught_exceptions()}
    {
        out << prefix;
    }

    RaiiPrinter::RaiiPrinter(RaiiPrinter&& other) noexcept
        : suffix_{other.suffix_},
          separator_{other.separator_},
          real_separator_{other.real_separator_},
          outp_{other.outp_},
          suppressed_{other.suppressed_},
          uncaught_exceptions_{other.uncaught_exceptions_}
    {
        other.suppressed_ = true;
    }

    RaiiPrinter& RaiiPrinter::operator=(RaiiPrinter&& other) noexcept
    {
        // Unlike copying, code that tries to move an object into itself is
        // wrong and deserves whatever it gets. But performance isn't critical
        // here, so an RaiiPrinter is merciful.
        if (this == &other) return *this;

        close();

        suffix_ = other.suffix_;
        separator_ = other.separator_;
        real_separator_ = other.real_separator_;
        outp_ = other.outp_;
        suppressed_ = other.suppressed_;
        uncaught_exceptions_ = other.uncaught_exceptions_;

        other.suppressed_ = true;

        return *this;
    }

    void RaiiPrinter::close() noexcept
    {
        // If we already printed a closer or were moved from, don't print again.
        if (suppressed_) return;

        suppressed_ = true;

        // We can do a fairly good job of not attempting to print a closer when
        // an exception was thrown, by printing only if there are no more
        // uncaught exceptions than when we were created.
        if (std::uncaught_exceptions() > uncaught_exceptions_) return;

        try {
            // Attempt to print a closer.
            *outp_ << suffix_;
        }
        catch (const std::ios_base::failure&) {
            // Counting uncaught exceptions is imperfect, in part because we may
            // have been passed around. So we silently swallow the most common
            // exception that may be thrown to signal failed stream insertion.
            // Other exception types might be thrown, e.g., stringstreams could
            // run out of memory, but it is less clear that user could would
            // not be better off crashing with std::terminate if that happened.
        }
    }
}
