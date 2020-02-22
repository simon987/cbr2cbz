cmake_minimum_required(VERSION 3.7)
project(cbr2cbz C)

set(CMAKE_C_STANDARD 11)
option(STATIC_BUILD "Static build" off)

add_executable(cbr2cbz main.c)

if (STATIC_BUILD)
    target_link_libraries(
            cbr2cbz
            -static
            archive
    )
else ()
    target_link_libraries(
            cbr2cbz
            archive
    )
endif ()

target_compile_options(
        cbr2cbz
        PRIVATE
)

