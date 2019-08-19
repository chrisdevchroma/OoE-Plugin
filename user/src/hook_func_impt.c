//
// Created by Master on 5/13/19.
//

#include "headers/hook.h"
#include "../../common/src/headers/codes.h"

int hookFunctionImports(tai_module_info_t info) {
    int ret = CODE_USER_SUCCESS_HOOK_FUNCTION_IMPORTS;
    return ret;
}

int releaseFunctionImports() {
    int ret = CODE_USER_SUCCESS_RELEASE_HOOK_FUNCTION_IMPORTS;
    return ret;
}
