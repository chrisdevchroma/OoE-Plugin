//
// Created by Master on 4/26/19.
//

#include <psp2/io/fcntl.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/clib.h>
#include <stdlib.h>
#include <taipool.h>

#include "headers/bin.h"
#include "headers/constants.h"
#include "headers/codes.h"
#include "headers/log.h"

SceUID openBinTranslateIoStream() {
    SceUID translationBinRef = sceIoOpen(FILE_TRANSLATION_BIN_PATH, SCE_O_RDONLY, 0777);
    if (translationBinRef < 0) {
        log_writef("Failed to read file \"%s\"!\n", FILE_TRANSLATION_BIN_PATH);
        return -1;
    } else {
        log_writef("Reading file \"%s\"\n", FILE_TRANSLATION_BIN_PATH);
    }
    return translationBinRef;
}

int closeBinTranslateIoStream(SceUID fd) {
    if (sceIoClose(fd) < 0) {
        log_writef("Failed to close file \"%s\"!\n\n", FILE_TRANSLATION_BIN_PATH);
        return -1;
    }
    log_writef("Closed stream for file \"%s\"\n\n", FILE_TRANSLATION_BIN_PATH);
    return 0;
}

int checkHeader(SceUID fUID) {
    sceIoLseek(fUID, 0x00, SCE_SEEK_SET);
    const int len = BIN_TRANSLATE_HEADER_LEN * sizeof(char);
    char* header = malloc(len + 1);
    header[sceIoRead(fUID, header, len)] = 0;

    log_writef("Read file header as: \"%s\"\n", header);

    int cmp = (int)sceClibStrncmp(BIN_TRANSLATE_HEADER, header, BIN_TRANSLATE_HEADER_LEN);
    if (cmp == 0) {
        log_writef("Header is valid\n\n");
        return 0;
    } else {
        log_writef("Header is invalid!\nExpected: %s, Given: %s, Compare: %d\n\n", BIN_TRANSLATE_HEADER, header, cmp);
        return -1;
    }
}
