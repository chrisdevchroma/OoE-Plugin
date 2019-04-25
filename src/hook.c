//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <taihen.h>
#include <stdio.h>

#include "headers/hook.h"
#include "headers/constants.h"
#include "headers/codes.h"
#include "headers/log.h"

int hook() {
    int ret = SCE_KERNEL_START_SUCCESS;

    tai_module_info_t info;
    info.size = sizeof(info);

    int moduleInfo = taiGetModuleInfo(TAI_MAIN_MODULE, &info);
    if (moduleInfo < 0) {
        log_write("Failed to invoke function getModuleInfo!\n");
        return SCE_KERNEL_START_FAILED;
    }

    log_writef("mouid: %d, mnid: %d, name: %s\n", info.name);

    const char *expected = "imhPSP2M";
    if (strcmp(info.name, expected) != 0) {
        log_writef("Incorrect module gotten! Expected: \"%s\", but got \"%s\"!\n", expected, info.name);
        return SCE_KERNEL_START_FAILED;
    }

    if (hookStrings(info) != CODE_SUCCESS_HOOK_STR) {
        ret = SCE_KERNEL_STOP_SUCCESS;
    }

    return ret;
}

int unhook() {
    int ret = SCE_KERNEL_STOP_SUCCESS;

    if (unhookStrings() != CODE_SUCCESS_UNHOOK_STR) {
        ret = SCE_KERNEL_STOP_SUCCESS;
    }

    return ret;
}
