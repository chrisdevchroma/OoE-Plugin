//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <stdio.h>
#include <taihen.h>

#include "headers/constants.h"
#include "headers/hook.h"
#include "headers/codes.h"
#include "headers/log.h"

static SceUID patchRefs[3];

int hookStrings(tai_module_info_t info) {
    patchRefs[0] = inject(info.modid, "Story Mode", 0x0071D7A7);
    patchRefs[1] = inject(info.modid, "Select an item to play", 0x0071E51F);
    patchRefs[2] = inject(info.modid, "It is a mode that can advance the original story", 0x0071E56F);
    return CODE_SUCCESS_HOOK_STR;
}

SceUID inject(SceUID modid, const char* text, int address) {
    SceUID injectRef = taiInjectData(modid, 0x000000, address, text, strlen(text));
    if (injectRef > -1) {
        log_writef("Injected text \"%s\" into address %d\n", text, address);
    } else {
        log_writef("Failed to inject world \"%s\" into address %d!\n", text, address);
        return -1;
    }
    return injectRef;
}

int unhookStrings() {
    for(int i = 0; i < sizeof(patchRefs); ++i) {
        SceUID patchRef = patchRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?!");
            continue;
        }

        if (taiInjectRelease(patchRef) == 0) {
            log_writef("Released inject");
        } else {
            log_writef("Failed to release inject!");
        }
    }
    return CODE_SUCCESS_UNHOOK_STR;
}
