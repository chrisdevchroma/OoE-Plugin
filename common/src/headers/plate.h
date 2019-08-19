//
// Created by Master on 6/4/19.
//

#ifndef OOE_PLUGIN_PLATE_H
#define OOE_PLUGIN_PLATE_H

#endif //OOE_PLUGIN_PLATE_H

#if defined(NONPDRM)
#include <psp2kern/types.h>
#else
#include <psp2/types.h>
#endif

int plate_sceIoMkdir(const char *dir, SceMode mode);
SceUID plate_sceIoOpen(const char *file, int flags, SceMode mode);
int plate_sceIoWrite(SceUID fd, const void *data, SceSize size);
int plate_sceIoClose(SceUID fd);
int plate_sceIoRead(SceUID fd, void *data, SceSize size);

SceOff plate_sceIoLseek(SceUID fd, SceOff offset, int whence);
SceOff plate_sceIoLseekPtr(SceUID fd, SceOff *offset, int whence);
