cmake_minimum_required(VERSION 2.8)

project(${CMAKE_PROJECT_NAME}-nonpdrm C)

cmake_policy(SET CMP0015 NEW)

include_directories(${PROJECT_NAME} src/headers)
link_directories(${PROJECT_NAME}-nonpdrm "${CMAKE_BINARY_DIR}/nonpdrm-io/${CMAKE_PROJECT_NAME}-nonpdrm-io_stubs")

add_executable(${PROJECT_NAME}
        src/main.c
        src/myio.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DNONPDRM -DKERNEL)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}-common ${CMAKE_PROJECT_NAME}-common-nonpdrm)

target_link_libraries(${PROJECT_NAME}
        k
        gcc

        SceIofilemgrForDriver_stub
        SceSysrootForKernel_stub
        SceModulemgrForDriver_stub
        SceSysmemForDriver_stub
        SceThreadmgrForDriver_stub

        taihenForKernel_stub

        ${CMAKE_PROJECT_NAME}-common
        ${CMAKE_PROJECT_NAME}-common-nonpdrm
)

vita_create_self(${PROJECT_NAME}.skprx ${PROJECT_NAME} CONFIG exports.yml UNSAFE)
vita_create_stubs(${PROJECT_NAME}_stubs ${PROJECT_NAME} exports.yml KERNEL)
