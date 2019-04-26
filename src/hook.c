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

    log_writef("mouid: %d, mnid: %d, name: %s\n\n", info.name);

    if (strcmp(info.name, MODULE_NAME) != 0) {
        log_writef("Incorrect module gotten! Expected: \"%s\", but got \"%s\"!\n", MODULE_NAME, info.name);
        return SCE_KERNEL_START_FAILED;
    }

    if (injectStrings(info) != CODE_SUCCESS_INJECT_STR) {
        ret = SCE_KERNEL_START_FAILED;
    }

    return ret;
}

int unhook() {
    int ret = SCE_KERNEL_STOP_SUCCESS;

    if (releaseStringInjections() != CODE_SUCCESS_RELEASE_INJECT_STR) {
        ret = SCE_KERNEL_STOP_SUCCESS;
    }

    return ret;
}
