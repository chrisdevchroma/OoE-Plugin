//
// Created by Master on 6/3/19.
//

#include <psp2/types.h>
#include <vitasdk.h>

int plate_sceIoMkdir(const char *dir, SceMode mode) {
    return sceIoMkdir(dir, mode);
}

SceUID plate_sceIoOpen(const char *file, int flags, SceMode mode) {
    return sceIoOpen(file, flags, mode);
}

int plate_sceIoWrite(SceUID fd, const void *data, SceSize size) {
    return sceIoWrite(fd, data, size);
}

int plate_sceIoClose(SceUID fd) {
    return sceIoClose(fd);
}

int plate_sceIoRead(SceUID fd, void *data, SceSize size) {
    return sceIoRead(fd, data, size);
}

SceOff plate_sceIoLseek(SceUID fd, SceOff offset, int whence) {
    return sceIoLseek(fd, offset, whence);
}

SceOff plate_sceIoLseekPtr(SceUID fd, SceOff *offset, int whence) {
    return NULL;//NOOP - User does not use ptr
}
