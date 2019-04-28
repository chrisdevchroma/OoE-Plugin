//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <stdio.h>
#include <taihen.h>
#include <stdlib.h>

#include "headers/constants.h"
#include "headers/hook.h"
#include "headers/codes.h"
#include "headers/log.h"
#include "headers/bin.h"

static int* injectRefLen;
static SceUID* injectRefs;

int sanityCheck() {
    //Check if injections were actually injected
    for (int i = 0; i < *injectRefLen; ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?! Ref index: %d\n", i);
            return CODE_FAILED_INJECT_STR;
        }
    }
    return CODE_SUCCESS_INJECT_STR;
}

int injectStrings(tai_module_info_t info) {
    SceUID translationBinFd = openBinTranslateIoStream();

    if (translationBinFd < 0) {
        log_writef("Failed to read file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
        return CODE_FAILED_INJECT_STR;
    }

    if (checkHeader(translationBinFd) == -1) {
        log_writef("Failed to check header for file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
        return CODE_FAILED_INJECT_STR;
    }

    SceOff seek;

    int length = sceIoLseek(translationBinFd, 0x00, SCE_SEEK_END);
    log_writef("Length: 0x%04X\n", length);

    seek = sceIoLseek(translationBinFd, BIN_TRANSLATE_HEADER_LEN, SCE_SEEK_SET);

    int* entries = malloc(sizeof(uint32_t));
    sceIoRead(translationBinFd, entries, sizeof(uint32_t));
    log_writef("Found 0x%02X entries\n\n", *entries);

    injectRefLen = malloc(sizeof(int));
    injectRefLen = entries;
    injectRefs = malloc(sizeof(SceUID) * *entries);
    memset(injectRefs, 0, sizeof(SceUID) * *entries);

    seek = sceIoLseek(translationBinFd, seek + sizeof(uint32_t), SCE_SEEK_SET);
    for(int i = 0; i < *entries; ++i) {
        uint32_t* entry_index = malloc(sizeof(uint32_t));
        uint32_t* address_offset = malloc(sizeof(uint32_t));
        uint16_t* text_len = malloc(sizeof(uint16_t));

        //Entry index
        sceIoRead(translationBinFd, entry_index, sizeof(uint32_t));
        seek = sceIoLseek(translationBinFd, seek + sizeof(uint32_t), SCE_SEEK_SET);

        //Address offset
        sceIoRead(translationBinFd, address_offset, sizeof(uint32_t));
        seek = sceIoLseek(translationBinFd, seek + sizeof(uint32_t), SCE_SEEK_SET);

        //Text Length
        sceIoRead(translationBinFd, text_len, sizeof(uint16_t));
        seek = sceIoLseek(translationBinFd, seek + sizeof(uint16_t), SCE_SEEK_SET);

        log_writef("Index: %d, Entry Index: 0x%02X, Address Offset: 0x%08X, Text Length: 0x%02X\n", i, *entry_index, *address_offset, *text_len);

        int alloc_len = (*text_len + 0) * sizeof(char);
        char *text = malloc(alloc_len + 1);
        text[sceIoRead(translationBinFd, text, alloc_len)] = 0;

        log_writef("Text: \"%s\"\n", text);

        int offset = seek + (*text_len * sizeof(char));
        log_writef("New Seek: %d\n\n", offset);
        seek = sceIoLseek(translationBinFd, offset, SCE_SEEK_SET);

        injectRefs[i] = injectString(info.modid, *address_offset, text);
    }

    closeBinTranslateIoStream(translationBinFd);

    if (sanityCheck() != CODE_SUCCESS_INJECT_STR) return CODE_FAILED_INJECT_STR;
    return CODE_SUCCESS_INJECT_STR;
}

int releaseStringInjections() {
    int flag = 0;
    for(int i = 0; i < *injectRefLen; ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?! Hook index: %d\n", i);
            flag++;
            continue;
        }
        if (sanityCheck() != CODE_SUCCESS_INJECT_STR) {
            return CODE_FAILED_INJECT_STR;
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

SceUID injectString(SceUID modid, int address, const char* text) {
    int actual_address = address - 0xFEB;//Addresses that were decompiled were given incorrect offsets - Subtract offset to fix this
    SceUID injectRef = taiInjectData(modid, 0x000000, actual_address, text, strlen(text) + 1);//Add 1 to include null-terminator character
    if (injectRef > -1) {
        log_writef("Injected text \"%s\" into address 0x%08X (actual address: 0x%08X)\nInjection Ref: %d\n\n", text, address, actual_address, injectRef);
    } else {
        log_writef("Failed to inject word \"%s\" into address 0x%08X! (actual address 0x%08X)\n", text, address, actual_address);
        return -1;
    }
    return injectRef;
}
