cmake_minimum_required(VERSION 2.8)

project(${CMAKE_PROJECT_NAME}-user C)

cmake_policy(SET CMP0015 NEW)

set(
        SOURCES

        src/main.c
        src/hook.c
        src/hook_strings.c
        src/hook_func_impt.c

        src/bin.c
)

set(INCLUDE_DIR src/headers)

set(TARGET_LINK_LIBRARIES

        k
        gcc

        SceIofilemgr_stub
        SceLibc_stub
        SceLibKernel_stub
        SceKernelThreadMgr_stub

        taihen_stub

        ${CMAKE_PROJECT_NAME}-common
)

#-------------------------------------------------------------------------
#-                             USER  SECTION                             -
#-------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${PROJECT_NAME} ${INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-common)

set(TARGET_LINK_LIBRARIES_USER
        ${CMAKE_PROJECT_NAME}-common-user
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DUSER)
target_link_libraries(${PROJECT_NAME}
        ${TARGET_LINK_LIBRARIES}
        ${TARGET_LINK_LIBRARIES_USER}
)

# Uncomment either one if using that specific version
#add_definitions(-DMAI)
#add_definitions(-DVITAMIN)

# Uncomment if no offset should be used for addresses/offsets in translation.bin
#add_definitions(-DNO_ADD_OFFSET)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME} CONFIG exports.yml UNSAFE)


#-------------------------------------------------------------------------
#-                            NONPDRM SECTION                            -
#-------------------------------------------------------------------------

# link_directories needs to be called before add_executable
link_directories(${PROJECT_NAME}-nonpdrm "${CMAKE_BINARY_DIR}/nonpdrm/${CMAKE_PROJECT_NAME}-nonpdrm_stubs")

add_executable(${PROJECT_NAME}-nonpdrm ${SOURCES})
include_directories(${PROJECT_NAME}-nonpdrm ${INCLUDE_DIR})

add_dependencies(${PROJECT_NAME}-nonpdrm ${CMAKE_PROJECT_NAME}-common ${CMAKE_PROJECT_NAME}-common-nonpdrm ${CMAKE_PROJECT_NAME}-nonpdrm)

set(TARGET_LINK_LIBRARIES_NONPDRM
        ${CMAKE_PROJECT_NAME}-common-nonpdrm
        ${CMAKE_PROJECT_NAME}-nonpdrm_stub
)

target_compile_definitions(${PROJECT_NAME}-nonpdrm PRIVATE -DNONPDRM)
target_link_libraries(${PROJECT_NAME}-nonpdrm
        ${TARGET_LINK_LIBRARIES}
        ${TARGET_LINK_LIBRARIES_NONPDRM}
)

vita_create_self(${PROJECT_NAME}-nonpdrm.suprx ${PROJECT_NAME}-nonpdrm CONFIG exports.yml UNSAFE)
