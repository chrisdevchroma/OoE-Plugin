//
// Created by Master on 4/26/19.
//

#ifndef OOE_PLUGIN_BIN_PARSER_H
#define OOE_PLUGIN_BIN_PARSER_H

#endif //OOE_PLUGIN_BIN_PARSER_H

#define BIN_TRANSLATE_HEADER "TRANSLATE"
#define BIN_TRANSLATE_HEADER_LEN 0x09

SceUID openBinTranslateIoStream();
int closeBinTranslateIoStream(SceUID fd);

/**
 * @param fUID
 * @return 0 if successful. -1 if not
 */
int checkHeader(SceUID fUID);
