cmake_minimum_required(VERSION 3.0.0)
project(Pool VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # cl and clang-cl accept /W4 (but -Weverything will override in clang-cl).
    string(REGEX REPLACE /W[123] /W4 CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

    # cl and clang-cl accept /permissive- for stricter conformance.
    add_compile_options(/permissive-)
else()
    # gcc/g++ and clang/clang++ require comparably strict conformance to
    # /permissive- unless -fpermissive is passed. But they accept -pedantic
    # for even more conformance warnings, and -pedantic-errors for errors.
    add_compile_options(-pedantic-errors)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # Clang accepts -Weverything with both clang/clang++ and clang-cl.
    # We will keep all but a few of the warnings that -Weverything enables.
    add_compile_options(
        -Weverything
        -Wno-c++98-compat
        -Wno-c++98-compat-bind-to-temporary-copy
        -Wno-padded
    )
elseif(MSVC)
    # cl but not clang-cl accepts /Za to reject Microsoft extensions.
    add_compile_options(/Za)

    # cl but not clang-cl accepts /analyze for static analysis (default rules).
    add_compile_options(/analyze)
else()
    # Enable most warnings.
    add_compile_options(-Wall -Wextra)
endif()

add_executable(pooltest
    main.cpp
    array.c array.h
    check.c check.h
    ListNode.cpp ListNode.hpp
    ListNode-test.cpp ListNode-test.hpp
    NoDefault.cpp NoDefault.hpp
    P.cpp P.hpp
    Pool.cpp Pool.hpp
    predicates.c predicates.h
    RaiiPrinter.cpp RaiiPrinter.hpp
    TreeNode.cpp TreeNode.hpp
    TreeNode-test.cpp TreeNode-test.hpp
    util.hpp
)

add_executable(test-RaiiPrinter
    test-RaiiPrinter.cpp
    RaiiPrinter.cpp RaiiPrinter.hpp
)

add_executable(test-cfuncs
    test-cfuncs.c
    array.c array.h
    check.c check.h
    predicates.c predicates.h
)

add_test(test-RaiiPrinter test-RaiiPrinter)
add_test(test-cfuncs test-cfuncs)
add_test(test pooltest) # runs the whole program as a test

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
