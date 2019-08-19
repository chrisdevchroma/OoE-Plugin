cmake_minimum_required(VERSION 2.8)

project(${CMAKE_PROJECT_NAME}-common C)

cmake_policy(SET CMP0015 NEW)

include_directories(${PROJECT_NAME}
        src/headers
)

set(SOURCES
        src/log.c
        src/rbtree.c
)

set(TARGET_DEPENDENCIES
        k
        gcc
        SceIofilemgr_stub
        SceLibKernel_stub
        SceLibc_stub
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(${PROJECT_NAME} ${TARGET_DEPENDENCIES})
