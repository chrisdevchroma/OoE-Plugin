//
// Created by Master on 4/24/19.
//

#include <vitasdk.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "headers/constants.h"
#include "headers/log.h"

void log_writef(const char *format, ...) {
    char buffer[BUF_MAX_LEN];

    va_list list;
    va_start(list, format);
    sceClibVsnprintf(buffer, sizeof(buffer), format, list);
    va_end(list);

    log_write(buffer);
}

/**
 * https://github.com/CelesteBlue-dev/PSVita-StorageMgr/blob/master/kernel/main.c#L1221
 */
void log_write(const char *buffer) {
    if (sceIoMkdir(OOE_FOLDER_PATH, 0777) == -1) {
        sceClibPrintf("Failed to make directory \"%s\"!", OOE_FOLDER_PATH);
        return;
    }

    SceUID fd = sceIoOpen(LOG_PATH, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, 0777);
    if (fd < 0) {
        return;
    }
    sceIoWrite(fd, buffer, strlen(buffer));
    sceIoClose(fd);
}
