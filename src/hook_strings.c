//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <taihen.h>
#include <stdlib.h>
#include <kuio.h>

#include "headers/constants.h"
#include "headers/hook.h"
#include "headers/codes.h"
#include "headers/log.h"
#include "headers/bin.h"

static uint32_t* injectRefLen;
static SceUID* injectRefs;

int sanityCheck() {
    if (!injectRefLen || !injectRefs) return CODE_FAILED_INJECT_STR;
    //Check if injections were actually injected
    for (uint32_t i = 0; i < *injectRefLen; ++i) {
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

    if (!translationBinFd) {
        log_writef("Failed to read file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
        return CODE_FAILED_INJECT_STR;
    }

    if (checkHeader(translationBinFd) == -1) {
        log_writef("Failed to check header for file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
        return CODE_FAILED_INJECT_STR;
    }

    uint seek_offset;

    seek_offset = BIN_TRANSLATE_HEADER_LEN;
    kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);//reset seek to after header

    uint32_t address_offset;
    kuIoRead(translationBinFd, &address_offset, sizeof(uint32_t));
    seek_offset += sizeof(uint32_t);
    kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);
    log_writef("Found address offset: 0x%02X\n", address_offset);

    uint32_t entries;
    kuIoRead(translationBinFd, &entries, sizeof(uint32_t));
    seek_offset += sizeof(uint32_t);
    kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);
    log_writef("Found 0x%02X entries\n\n", entries);

    injectRefLen = malloc(sizeof(uint32_t));
    injectRefLen = &entries;
    injectRefs = malloc(sizeof(SceUID) * entries);
    memset(injectRefs, 0, sizeof(SceUID) * entries);

    for(uint32_t i = 0; i < entries; ++i) {
        uint32_t entry_index;
        uint32_t address;
        uint16_t text_len;

        //Entry index
        kuIoRead(translationBinFd, &entry_index, sizeof(uint32_t));
        seek_offset += sizeof(uint32_t);
        kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);

        //Address offset
        kuIoRead(translationBinFd, &address, sizeof(uint32_t));
        seek_offset += sizeof(uint32_t);
        kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);

        //Text Length
        kuIoRead(translationBinFd, &text_len, sizeof(uint16_t));
        seek_offset += sizeof(uint16_t);
        kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);

        log_writef("Index: %d, Entry Index: 0x%02X, Address Offset: 0x%08X, Text Length: 0x%02X\n", i, entry_index, address, text_len);

        char* text = malloc((text_len * sizeof(char)) + 1);
        kuIoRead(translationBinFd, text, text_len);
        seek_offset += text_len;
        kuIoLseek(translationBinFd, seek_offset, SCE_SEEK_SET);
//        log_writef("Text: \"%s\"\n", text); //commented out because it degrades performance
//        log_writef("Next Offset: %d\n\n\n", seek_offset);

        injectRefs[i] = injectString(info.modid, address_offset, address, text, text_len);
    }

    closeBinTranslateIoStream(translationBinFd);

    if (sanityCheck() != CODE_SUCCESS_INJECT_STR) return CODE_FAILED_INJECT_STR;
    return CODE_SUCCESS_INJECT_STR;
}

int releaseStringInjections() {
    int flag = 0;
    for(uint32_t i = 0; i < *injectRefLen; ++i) {
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

SceUID injectString(SceUID modid, uint32_t address_offset, uint32_t address, const char* text, const uint16_t text_len) {
    uint32_t actual_address = address - address_offset;

    SceUID injectRef = taiInjectData(modid, 0x00000000, actual_address, text, text_len + 1);
    if (!injectRef) {
        log_writef("Failed to inject word \"%s\" into address 0x%08X! (actual address 0x%08X)\n", text, address, actual_address);
        return -1;
    } else {
        log_writef("Injected text \"%s\" into address 0x%08X (actual address: 0x%08X)\nInjection Ref: %d\n\n", text, address, actual_address, injectRef);
    }
    return injectRef;
}
