cmake_minimum_required(VERSION 3.14)

set(project_name "winpthreads")
project(${project_name} C CXX)

file(GLOB src
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/*.h
    ${CMAKE_CURRENT_LIST_DIR}/src/*.rc
)

if(MINGW)
    file(GLOB_RECURSE libgcc_src
        ${CMAKE_CURRENT_LIST_DIR}/src/libgcc/*.c
        ${CMAKE_CURRENT_LIST_DIR}/src/libgcc/*.S
    )

    add_library(fake-libgcc
        STATIC ${libgcc_src}
    )
endif()

add_library(${project_name}
    STATIC ${src}
)

target_include_directories(${project_name}
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(${project_name}
    PRIVATE "_CRT_SECURE_NO_WARNINGS"
    PRIVATE "_CRT_NONSTDC_NO_DEPRECATE"
    PRIVATE "IN_WINPTHREAD"
    PRIVATE "_WIN32_WINNT=0x0400"
    PRIVATE "_LIB"
    PRIVATE "_UNICODE"
    PRIVATE "UNICODE"
)

if(CMAKE_CXX_IS_CLANG_WIN)
    target_compile_definitions(${project_name}
        PUBLIC "_TIMESPEC_DEFINED"
    )

    target_compile_options(${project_name}
        PRIVATE "-flto"
        PRIVATE "-march=pentium-mmx"
        PRIVATE "-Wno-cast-calling-convention"
        PRIVATE "-Wno-ignored-pragmas"
    )
elseif(MINGW)
    target_link_libraries(${project_name}
        PRVIATE fake-libgcc
    )

    target_compile_options(${project_name}
        PRIVATE "-march=pentium-mmx"
    )

    target_link_options(${project_name}
        PRIVATE "-no-pthread"
    )
endif()