cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0054 NEW) # Don't expand unquoted variable names in if().
project(Pool VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    # cl and clang-cl accept /permissive- for stricter conformance.
    string(REGEX REPLACE /W[123] /W4 CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    add_compile_options(/permissive-)
else()
    # gcc/g++ and clang/clang++ require comparably strict conformance to
    # /permissive- unless -fpermissive is passed. But they accept -pedantic
    # for even more conformance warnings, and -pedantic-errors for errors.
    add_compile_options(-pedantic-errors)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # cl but not clang-cl accepts /Za to disable Microsoft extensions.
    add_compile_options(/Za)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # Clang accepts -Weverything with both clang/clang++ and clang-cl.
    # We will keep all but a few of the warnings that -Weverything enables.
    add_compile_options(
        -Weverything
        -Wno-c++98-compat
        -Wno-c++98-compat-bind-to-temporary-copy
        -Wno-padded
    )
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # GCC doesn't accept -Weverything, but we still want most GCC warnings.
    add_compile_options(-Wall -Wextra)
endif()

add_executable(pooltest
    main.cpp
    ListNode.cpp ListNode.h
    ListNode-test.cpp ListNode-test.h
    NoDefault.cpp NoDefault.h
    P.cpp P.h
    Pool.cpp Pool.h
    RaiiPrinter.cpp RaiiPrinter.h
    TreeNode.cpp TreeNode.h
    TreeNode-test.cpp TreeNode-test.h
    util.h
)

add_executable(test-RaiiPrinter
    test-RaiiPrinter.cpp
    RaiiPrinter.cpp RaiiPrinter.h
)

add_test(RaiiPrinter-test RaiiPrinter-test)
add_test(test pooltest) # runs the whole program as a test

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
