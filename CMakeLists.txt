cmake_minimum_required(VERSION 3.0.0)
project(Pool VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/permissive-)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        add_compile_options(
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-compat-bind-to-temporary-copy
            -Wno-padded
        )
    endif()
else()
    add_compile_options(-pedantic-errors)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        add_compile_options(
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-compat-bind-to-temporary-copy
            -Wno-padded
        )
    else()
        add_compile_options(
            -Wall
            -Wextra
        )
    endif()
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

#if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Weverything -Wno-c++98-compat -Wno-c++98-compat-bind-to-temporary-copy -Wno-padded")
#endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
