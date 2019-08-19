cmake_minimum_required(VERSION 2.8)

project(${CMAKE_PROJECT_NAME}-common-user C)

cmake_policy(SET CMP0015 NEW)

include_directories(${PROJECT_NAME}
        src/headers
)

set(SOURCES
        src/plate.c
        src/log.c
        src/map.c
)

set(TARGET_DEPENDENCIES
        k
        gcc
        SceIofilemgr_stub
        SceKernelThreadMgr_stub
        SceLibKernel_stub
        SceLibc_stub
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DUSER)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-common)

target_link_libraries(${PROJECT_NAME} ${TARGET_DEPENDENCIES} ${CMAKE_PROJECT_NAME}-common)
