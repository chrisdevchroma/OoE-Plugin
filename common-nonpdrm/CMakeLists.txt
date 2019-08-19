cmake_minimum_required(VERSION 2.8)

project(${CMAKE_PROJECT_NAME}-common-nonpdrm C)

cmake_policy(SET CMP0015 NEW)

include_directories(${PROJECT_NAME}
        src/headers
)

set(SOURCES
        src/plate.c
        src/map.c
)

set(TARGET_DEPENDENCIES
        k
        gcc
        SceIofilemgr_stub
)

#link_directories(${PROJECT_NAME}-nonpdrm ${CMAKE_BINARY_DIR}/nonpdrm-io/${CMAKE_PROJECT_NAME}-nonpdrm-io_stubs)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DNONPDRM)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-common)

set(TARGET_DEPENDENCIES_NONPDRM
        SceDebugForDriver_stub
        SceIofilemgrForDriver_stub
        SceThreadmgrForDriver_stub
        SceSysmemForDriver_stub
        ${CMAKE_PROJECT_NAME}-common
)

target_link_libraries(${PROJECT_NAME} ${TARGET_DEPENDENCIES} ${TARGET_DEPENDENCIES_U} ${TARGET_DEPENDENCIES_NONPDRM})
