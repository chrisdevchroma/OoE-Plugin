cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

project(OoE-Plugin)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -nostdlib -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -g")

add_executable(${PROJECT_NAME}
        src/headers/constants.h
        src/headers/hook.h
        src/headers/codes.h
        src/headers/log.h
        src/headers/bin.h

        src/main.c
        src/hook.c
        src/log.c
        src/hook_strings.c
        src/bin.c
)

target_link_libraries(${PROJECT_NAME}
#        c
        k
        gcc

        SceIofilemgr_stub
        SceLibKernel_stub
        SceSysmem_stub
        SceLibc_stub

        taihen_stub

        kuio_stub
)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME} CONFIG exports.yml UNSAFE)
