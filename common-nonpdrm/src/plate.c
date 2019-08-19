//
// Created by Master on 6/4/19.
//

#include <psp2kern/types.h>
#if defined(KERNEL)
#include <vitasdkkern.h>
#endif

#include "headers/myio.h"

int plate_sceIoMkdir(const char *dir, SceMode mode) {
#if defined(KERNEL)
    return ksceIoMkdir(dir, mode);
#else
    return myIoMkdir(dir, mode);
#endif
}

SceUID plate_sceIoOpen(const char *file, int flags, SceMode mode) {
#if defined(KERNEL)
    return ksceIoOpen(file, flags, mode);
#else
    return myIoOpen(file, flags, mode);
#endif
}

int plate_sceIoWrite(SceUID fd, const void *data, SceSize size) {
#if defined(KERNEL)
    return ksceIoWrite(fd, data, size);
#else
    return myIoWrite(fd, data, size);
#endif
}

int plate_sceIoClose(SceUID fd) {
#if defined(KERNEL)
    return ksceIoClose(fd);
#else
    return myIoClose(fd);
#endif
}

int plate_sceIoRead(SceUID fd, void *data, SceSize size) {
#if defined(KERNEL)
    return ksceIoRead(fd, data, size);
#else
    return myIoRead(fd, data, size);
#endif
}

SceOff plate_sceIoLseekPtr(SceUID fd, SceOff *offset, int whence) {
#if defined(KERNEL)
    //NOOP
    return -1;
#else
    return myIoLseekPtr(fd, whence, offset);
#endif
}

SceOff plate_sceIoLseek(SceUID fd, SceOff offset, int whence) {
#if defined(KERNEL)
    return ksceIoLseek(fd, offset, whence);
#else
    return plate_sceIoLseekPtr(fd, &offset, whence);
#endif
}
