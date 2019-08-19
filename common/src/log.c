//
// Created by Master on 6/3/19.
//

#include <string.h>

#include <fcntl.h>

#if defined(NONPDRM)
#include <vitasdkkern.h>
#else
#include <vitasdk.h>
#endif

#include "headers/log.h"
#include "headers/plate.h"
#include "headers/file.h"

/**
 * https://github.com/CelesteBlue-dev/PSVita-StorageMgr/blob/master/kernel/main.c#L1221
 */
void log_write(const char *buffer) {
    int mkdir = plate_sceIoMkdir(OOE_FOLDER_PATH, 0777);
    if (mkdir == -1) {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Failed to make directory \"%s\"!\n",
                OOE_FOLDER_PATH
        );
        return;
    }

    SceUID fd = plate_sceIoOpen(LOG_FILE_PATH, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, 0777);
    if (fd < 0) {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Failed to open log file \"%s\"!",
                LOG_FILE_PATH
        );
        return;
    }

    int len = plate_sceIoWrite(fd, buffer, strlen(buffer));
    if (len > -1) {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Wrote %d bytes",
                len
        );
    } else {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Failed to write bytes?"
        );
    }

    int closeRet = plate_sceIoClose(fd);
    if (closeRet < 0) {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Failed to close log file!"
        );
    } else {
#if defined(NONPDRM)
        ksceDebugPrintf(
#else
        sceClibPrintf(
#endif
                "Closed log file"
        );
    }
}
