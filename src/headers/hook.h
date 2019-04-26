//
// Created by Master on 4/10/19.
//

#ifndef OOE_PLUGIN_HOOKS_H
#define OOE_PLUGIN_HOOKS_H

#endif //OOE_PLUGIN_HOOKS_H

#include <taihen.h>

int hook();
int unhook();

int injectStrings(tai_module_info_t info);
int releaseStringInjections();

SceUID injectString(SceUID modid, int address, const char* text);
