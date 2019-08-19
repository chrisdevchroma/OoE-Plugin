//
// Created by Master on 5/14/19.
//

#define OOE_FOLDER_PATH "ux0:data/OoE"
#define FILE_TRANSLATION_BIN_PATH (OOE_FOLDER_PATH "/translation.bin")

#if defined(NONPDRM)
#define LOG_FILE_PATH (OOE_FOLDER_PATH "/log_kernel.txt")
#define FILE_OOE_PLUGIN_USER_SUPRX_PATH (OOE_FOLDER_PATH "/OoE-Plugin-user-nonpdrm.suprx")
#elif defined(USER)
#define LOG_FILE_PATH (OOE_FOLDER_PATH "/log_user.txt")
#else
#define LOG_FILE_PATH (OOE_FOLDER_PATH "/log_undefined.txt")
#endif
