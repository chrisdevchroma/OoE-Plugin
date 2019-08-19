//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <taihen.h>
#include <stdlib.h>

#include "headers/hook.h"
#include "../../common/src/headers/log.h"
#include "../../common/src/headers/constants.h"
#include "../../common/src/headers/codes.h"

#include "../../common-user/src/headers/map.h"


int hook() {
    int ret = SCE_KERNEL_START_SUCCESS;

    tai_module_info_t* info = malloc(sizeof(tai_module_info_t));
    info->size = sizeof(*info);

    int moduleInfo = taiGetModuleInfo(TAI_MAIN_MODULE, info);
    if (moduleInfo < 0) {
#if defined(_DEBUG)
        log_write("Failed to invoke function getModuleInfo!\n");
#endif
        return SCE_KERNEL_START_FAILED;
    }

#if defined(_DEBUG)
#if defined(USER)
    log_writef("mouid: 0x%08X, mnid: 0x%08X, name: \"%s\"\n\n\n", info->modid, info->module_nid, info->name);
#elif defined(NONPDRM)
    //TODO
#endif
#endif

    if (strcmp(info->name, TARGET_MODULE_NAME) != 0) {
#if defined(_DEBUG)
#if defined(USER)
        log_writef("Incorrect module gotten! Expected: \"%s\", but got \"%s\"!\n", TARGET_MODULE_NAME, info->name);
#elif defined(NONPDRM)
        //TODO
#endif
#endif
        return SCE_KERNEL_START_FAILED;
    }

    mapInit();

    if (injectStrings(*info) != CODE_USER_SUCCESS_INJECT_STR) ret = SCE_KERNEL_START_FAILED;
    if (hookFunctionImports(*info) != CODE_USER_SUCCESS_HOOK_FUNCTION_IMPORTS) ret = SCE_KERNEL_START_FAILED;

    return ret;
}

int unhook() {
    int ret = SCE_KERNEL_STOP_SUCCESS;
    if (releaseStringInjections() != CODE_USER_SUCCESS_RELEASE_INJECT_STR) ret = SCE_KERNEL_STOP_FAIL;
    if (releaseFunctionImports() != CODE_USER_SUCCESS_RELEASE_HOOK_FUNCTION_IMPORTS) ret = SCE_KERNEL_STOP_FAIL;
    return ret;
}
