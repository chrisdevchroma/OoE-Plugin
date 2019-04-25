//
// Created by Master on 4/9/19.
//

#include <psp2kern/kernel/modulemgr.h>

#include "headers/constants.h"
#include "headers/hook.h"
#include "headers/log.h"

void _start() __attribute__ ((weak, alias("module_start")));

int module_start(SceSize argc, void *argp) {
    log_writef("Starting %s...\n", ID);
    return hook();
}

int module_stop(SceSize argc, void *argp) {
    log_writef("Stopping %s...\n", ID);
    return unhook();
}
