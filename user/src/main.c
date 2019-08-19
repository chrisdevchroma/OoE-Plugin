//
// Created by Master on 4/9/19.
//

#include <vitasdk.h>

#include "headers/hook.h"
#include "../../common/src/headers/log.h"
#include "../../common/src/headers/constants.h"

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize argc, void *argp) {
#if defined(DEBUG)
#if defined(USER)
    log_writef("Starting %s...\n", ID);
#elif defined(NONPDRM)
    //TODO
    log_write("Starting");
#endif
#endif
    return hook();
}

int module_stop(SceSize argc, void *argp) {
#if defined(DEBUG)
#if defined(USER)
    log_writef("Stopping %s...\n", ID);
#elif defined(NONPDRM)
    //TODO
#endif
#endif
    return unhook();
}
