//
// Created by Master on 6/3/19.
//

#include <string.h>

#include <psp2kern/types.h>
#include <taihen.h>
#include <vitasdkkern.h>

#include "../../common/src/headers/constants.h"
#include "../../common/src/headers/file.h"
#include "../../common/src/headers/log.h"
#include "../../common-nonpdrm/src/headers/map.h"

static SceUID hook_ksceKernelStartPreloadedModules;
static SceUID hook_ksceModulemgrUnloadProcess;

static tai_hook_ref_t ksceKernelStartPreloadedModulesRef;
static tai_hook_ref_t ksceModulemgrUnloadProcessRef;

static int ksceKernelStartPreloadedModulesPatched(SceUID pid) {
    int ref = TAI_CONTINUE(int, ksceKernelStartPreloadedModulesRef, pid);

    char titleID[32];
    ksceKernelGetProcessTitleId(pid, titleID, sizeof(titleID) * sizeof(char));

    if (strncmp(titleID, TARGET_TITLE_ID, 9) == 0) {
#if defined(_DEBUG)
        log_write("Title \"");
        log_write(TARGET_TITLE_ID);
        log_write("\" is currently running.\nAttempting to start plugin...\n");
#endif
        ksceKernelLoadStartModuleForPid(pid, FILE_OOE_PLUGIN_USER_SUPRX_PATH, 0, NULL, 0, NULL, NULL);
    }

    return ref;
}

static void *ksceModulemgrUnloadProcessPatched() {
    return 0;
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize argc, void *argp) {

    mapInit();

    hook_ksceKernelStartPreloadedModules = taiHookFunctionExportForKernel(
            KERNEL_PID,
            &ksceKernelStartPreloadedModulesRef,
            "SceKernelModulemgr",
            0xC445FA63,
            0x432DCC7A,
            ksceKernelStartPreloadedModulesPatched
    );
    /*
    hook_ksceModulemgrUnloadProcess = taiHookFunctionImportForKernel(
            KERNEL_PID,
            &ksceModulemgrUnloadProcessRef,
            "SceProcessmgr",
            0xC445FA63,
            0x0E33258E,
            ksceModulemgrUnloadProcessPatched
    );
    */

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, void *argp) {
    if (hook_ksceKernelStartPreloadedModules != -1) taiHookReleaseForKernel(KERNEL_PID, hook_ksceKernelStartPreloadedModules);
    if (hook_ksceModulemgrUnloadProcess != -1) taiHookReleaseForKernel(KERNEL_PID, hook_ksceModulemgrUnloadProcess);

    return SCE_KERNEL_STOP_SUCCESS;
}
