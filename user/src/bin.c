//
// Created by Master on 4/26/19.
//

#include <string.h>

#include <stdlib.h>
#include <taipool.h>

#if defined(USER)
#include <psp2/io/fcntl.h>
#include <psp2/kernel/sysmem.h>
#elif defined(NONPDRM)
#include <psp2kern/io/fcntl.h>
#include <psp2kern/kernel/sysmem.h>
#endif

#include "headers/bin.h"
#include "../../common/src/headers/constants.h"
#include "../../common/src/headers/log.h"
#include "../../common/src/headers/file.h"
#include "../../common/src/headers/plate.h"

SceUID openBinTranslateIoStream() {
    SceUID translationBinRef = plate_sceIoOpen(FILE_TRANSLATION_BIN_PATH, SCE_O_RDONLY, 0777);
    if (translationBinRef < 0) {
#if defined(_DEBUG)
#if defined(USER)
        log_writef("Failed to read file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
#elif defined(NONPDRM)
        //TODO
#endif
#endif
        return -1;
    } else {
#if defined(_DEBUG)
#if defined(USER)
        log_writef("Reading file \"%s\"\n", FILE_TRANSLATION_BIN_PATH);
#elif defined(NONPDRM)
        //TODO
#endif
#endif
    }
    return translationBinRef;
}

int closeBinTranslateIoStream(SceUID fd) {
    if (plate_sceIoClose(fd) < 0) {
#if defined(_DEBUG)
#if defined(USER)
        log_writef("Failed to close file \"%s\"!\n\n", FILE_TRANSLATION_BIN_PATH);
#elif defined(NONPDRM)
#endif
#endif
        return -1;
    }
#if defined(_DEBUG)
#if defined(USER)
    log_writef("Closed stream for file \"%s\"\n\n", FILE_TRANSLATION_BIN_PATH);
#elif defined(NONPDRM)
    //TODO
#endif
#endif
    return 0;
}

int checkHeader(SceUID fUID) {
    plate_sceIoLseek(fUID, 0x00, SCE_SEEK_SET);
    const int len = BIN_TRANSLATE_HEADER_LEN * sizeof(char);
    char* header = malloc(len + 1);
    header[plate_sceIoRead(fUID, header, len)] = 0;

#if defined(_DEBUG)
#if defined(USER)
    log_writef("Read file header as: \"%s\"\n", header);
#elif defined(NONPDRM)
    //TODO
#endif
#endif

    int cmp = (int)strncmp(BIN_TRANSLATE_HEADER, header, BIN_TRANSLATE_HEADER_LEN);
    if (cmp == 0) {
        log_write("Header is valid\n\n");
        return 0;
    } else {
#if defined(_DEBUG)
#if defined(USER)
        log_writef("Header is invalid!\nExpected: %s, Given: %s, Compare: %d\n\n", BIN_TRANSLATE_HEADER, header, cmp);
#elif defined(NONPDRM)
        //TODO
#endif
#endif
        return -1;
    }
}
