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

static SceUID injectRefs[6];

int injectStrings(tai_module_info_t info) {
    //TODO
    injectRefs[0] = injectString(info.modid, "Story Mode", 0x0071D7A7);
    injectRefs[1] = injectString(info.modid, "Select an item to play", 0x0071E51F);
    injectRefs[2] = injectString(info.modid, "It is a mode that can advance the original story", 0x0071E56F);
    injectRefs[3] = injectString(info.modid, "Cursor", 0x0071E12F);//カーソル移動
    injectRefs[4] = injectString(info.modid, "Select", 0x0071D6FB);//決定
    injectRefs[5] = injectString(info.modid, "Help", 0x0071D77B);//ヘルプ

    //Check if injections were actually injected
    for (int i = 0; i < sizeof(injectRefs); ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid! Ref index: %d\n", i);
            return CODE_FAILED_INJECT_STR;
        }
    }

    return CODE_SUCCESS_INJECT_STR;
}

int releaseStringInjections() {
    int flag = 0;
    for(int i = 0; i < sizeof(injectRefs); ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?! Hook index: %d\n", i);
            flag++;
            continue;
        }

        if (taiInjectRelease(patchRef) == 0) {
            log_writef("Released inject. Hook index: %d\n", i);
        } else {
            log_writef("Failed to release inject! Hook index: %d\n", i);
            flag++;
        }
    }

    if (flag > 0) {
        log_writef("Failed to unhook multiple hooks for strings! Flag: %d\n", flag);
        return CODE_FAILED_RELEASE_INJECT_STR;
    }

    return CODE_SUCCESS_RELEASE_INJECT_STR;
}

SceUID injectString(SceUID modid, const char* text, int address) {
    SceUID injectRef = taiInjectData(modid, 0x000000, address, text, sizeof(text));
    if (injectRef > -1) {
        log_writef("Injected text \"%s\" into address %d\n", text, address);
    } else {
        log_writef("Failed to inject world \"%s\" into address %d!\n", text, address);
        return -1;
    }
    return injectRef;
}
