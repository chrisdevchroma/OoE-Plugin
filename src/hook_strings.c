//
// Created by Master on 4/10/19.
//

#include <vitasdk.h>
#include <stdio.h>
#include <taihen.h>

#include "headers/constants.h"
#include "headers/hook.h"
#include "headers/codes.h"
#include "headers/log.h"

SceUID injectRefs[13];

int injectStrings(tai_module_info_t info) {
    //TODO
//    injectRefs[0] = injectString(info.modid, "Main Menu", 0x0071D7A7);//メインメニュー
    injectRefs[0] = injectString(info.modid, 0x0071D7BF, "Story Mode");//ストーリーモード
//    injectRefs[1] = injectString(info.modid, "Select an item to play", 0x0071E51F);
//    injectRefs[2] = injectString(info.modid, "It is a mode that can advance the original story", 0x0071E56F);
//    injectRefs[3] = injectString(info.modid, "Cursor", 0x0071E12F);//カーソル移動

//    injectRefs[0] = injectString(info.modid, 0x0071D6FB, "Select");//決定

    injectRefs[1] = injectString(info.modid, 0x0071D77B, "Help");//ヘルプ
//    injectRefs[7] = injectString(info.modid, "Normal", 0x0071DC3B);//ノーマル
//    injectRefs[8] = injectString(info.modid, "Reverse", 0x0071DC4B);//リバース
//    injectRefs[9] = injectString(info.modid, "Auto target", 0x0071DBCF);//オートロックオン

    injectRefs[2] = injectString(info.modid, 0x0071DA83, "BGM Volume");//BGM音量
    injectRefs[3] = injectString(info.modid, 0x0071F793, "Change the volume of the BGM");//ＢＧＭを再生する音量を変更することができます
//    injectRefs[14] = injectString(info.modid, "TODO", 0x0071EA3F);//この画面で、対戦時のルールを設定することができます

    injectRefs[4] = injectString(info.modid, 0x0071DA8F, "SE Volume");//SE音量
    injectRefs[5] = injectString(info.modid, 0x0071F7D7, "Change the volume of the SE");//ＳＥを再生する音量を変更することができます

    injectRefs[6] = injectString(info.modid, 0x0071D4EF, "Loading save data...");//セーブデータをロード中です...
    injectRefs[7] = injectString(info.modid, 0x0071D51F, "Creating save data...");//セーブデータを作成しています...
    injectRefs[8] = injectString(info.modid, 0x0071D54B, "Checking for DLC....");//ダウンロードコンテンツを確認中です...

    injectRefs[8] = injectString(info.modid, 0x0071E71F, "Begin a new game");//最初からストーリーを始めます
    injectRefs[9] = injectString(info.modid, 0x0071E74B, "Continue story-mode");//前回の続きからストーリーを再開します

    injectRefs[10] = injectString(info.modid, 0x0071DA9B, "Message Speed");//メッセージスピード
    injectRefs[11] = injectString(info.modid, 0x0071DAB7, "Narrator Voice");//ガイドボイス選択
    injectRefs[12] = injectString(info.modid, 0x0071DC5B, "Default");//デフォルト

    //Check if injections were actually injected
    for (int i = 0; i < (sizeof(injectRefs) / sizeof(SceUID)); ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid! Ref index: %d\n", i);
            return CODE_FAILED_INJECT_STR;
        }
    }

    return CODE_SUCCESS_INJECT_STR;
}

int releaseStringInjections() {
    int flag = 0;
    for(int i = 0; i < (sizeof(injectRefs) / sizeof(SceUID)); ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?! Hook index: %d\n", i);
            flag++;
            continue;
        }

        if (taiInjectRelease(patchRef) == 0) {
            log_writef("Released inject. Hook index: %d\n", i);
        } else {
            log_writef("Failed to release inject! Hook index: %d\n", i);
            flag++;
        }
    }

    if (flag > 0) {
        log_writef("Failed to unhook multiple hooks for strings! Flag: %d\n", flag);
        return CODE_FAILED_RELEASE_INJECT_STR;
    }

    return CODE_SUCCESS_RELEASE_INJECT_STR;
}

SceUID injectString(SceUID modid, int address, const char* text) {
    int actual_address = address - 0xFEB;//Addresses that were decompiled were given incorrect offsets - Subtract offset to fix this
    SceUID injectRef = taiInjectData(modid, 0x000000, actual_address, text, strlen(text)+1);
    if (injectRef > -1) {
        log_writef("Injected text \"%s\" into address 0x%08x (actual address: 0x%08x)\nRef: %d\n\n", text, address, actual_address, injectRef);
    } else {
        log_writef("Failed to inject word \"%s\" into address 0x%08x! (actual address 0x%08x)\n", text, address, actual_address);
        return -1;
    }
    return injectRef;
}
