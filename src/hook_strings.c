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

SceUID injectRefs[52];

int sanityCheck() {
    //Check if injections were actually injected
    for (int i = 0; i < (sizeof(injectRefs) / sizeof(SceUID)); ++i) {
        SceUID patchRef = injectRefs[i];
        if (patchRef < 0) {
            log_writef("Patch ref is invalid?! Ref index: %d\n", i);
            return CODE_FAILED_INJECT_STR;
        }
    }
    return CODE_SUCCESS_INJECT_STR;
}

int injectStrings(tai_module_info_t info) {
    //TODO FIXME Text needs to be externally stored. Doing it this way bloats the plugin executable

    injectRefs[0] = injectString(info.modid, 0x0071D7BF, "Story Mode");//ストーリーモード
    injectRefs[1] = injectString(info.modid, 0x0071D7DB, "Free Match Mode");//フリー対戦モード
    injectRefs[2] = injectString(info.modid, 0x0071D7F7, "CAD Customization");//カスタマイズモード
    injectRefs[3] = injectString(info.modid, 0x0071D813, "Memories");//メモリーズ

    injectRefs[4] = injectString(info.modid, 0x0071D86B, "Continue");//コンティニュー
    injectRefs[5] = injectString(info.modid, 0x0071D883, "New game");//スタート

    injectRefs[6] = injectString(info.modid, 0x0071E12F, "Cursor");//カーソル移動
    injectRefs[7] = injectString(info.modid, 0x0071E19F, "Select character");//キャラ選択
    injectRefs[8] = injectString(info.modid, 0x0071D6FB, "Accept");//決定
    injectRefs[9] = injectString(info.modid, 0x00709247, "Back");//戻る
    injectRefs[10] = injectString(info.modid, 0x0071E143, "History Log");//バックログ
    injectRefs[11] = injectString(info.modid, 0x0071DA13, "Fast-Forward");//メッセージ早送り

    injectRefs[12] = injectString(info.modid, 0x00719C17, "First High School: Course 1");//第一高校制服 一科生
    injectRefs[13] = injectString(info.modid, 0x00719C37, "First High School: Course 2");//第一高校制服 二科生
    injectRefs[13] = injectString(info.modid, 0x00719C57, "Second High School");//第二高校制服
    injectRefs[13] = injectString(info.modid, 0x00719C6B, "Third High School");//第三高校制服
    injectRefs[13] = injectString(info.modid, 0x00719C7F, "Fourth High School");//第四高校制服
    injectRefs[13] = injectString(info.modid, 0x00719C93, "Fifth High School");//第五高校制服
    injectRefs[13] = injectString(info.modid, 0x00719CA7, "Sixth High School");//第六高校制服
    injectRefs[13] = injectString(info.modid, 0x00719CBB, "Seventh High School");//第七高校制服
    injectRefs[13] = injectString(info.modid, 0x00719CCF, "Eighth High School");//第八高校制服
    injectRefs[13] = injectString(info.modid, 0x00719CE3, "Ninth High School");//第九高校制服

    injectRefs[14] = injectString(info.modid, 0x0071D903, "Controls");//アクション設定
    injectRefs[15] = injectString(info.modid, 0x0071D91B, "Settings");//ゲーム設定
    injectRefs[16] = injectString(info.modid, 0x0071D77B, "Help");//ヘルプ

    injectRefs[17] = injectString(info.modid, 0x007179F7, "One Core left!");//コア残り１つ！

    injectRefs[18] = injectString(info.modid, 0x0071708F, "Leo");//レオ
    injectRefs[19] = injectString(info.modid, 0x0071799F, "Destroyed a core");//がコアを破壊しました

    injectRefs[20] = injectString(info.modid, 0x0071DA83, "BGM Volume");//BGM音量
    injectRefs[21] = injectString(info.modid, 0x0071F793, "Change the volume of the BGM");//ＢＧＭを再生する音量を変更することができます

    injectRefs[22] = injectString(info.modid, 0x0071DFCB, "Pause");//中断
    injectRefs[24] = injectString(info.modid, 0x00716F93, "Cannot pause during your first time playing");//初回プレイの為、中断出来ません

    injectRefs[25] = injectString(info.modid, 0x0071DA8F, "SE Volume");//SE音量
    injectRefs[26] = injectString(info.modid, 0x0071F7D7, "Change the volume of the SE");//ＳＥを再生する音量を変更することができます

    injectRefs[27] = injectString(info.modid, 0x0071D4EF, "Loading save data...");//セーブデータをロード中です...
    injectRefs[28] = injectString(info.modid, 0x0071D51F, "Creating save data...");//セーブデータを作成しています...
    injectRefs[29] = injectString(info.modid, 0x0071D54B, "Checking for DLC....");//ダウンロードコンテンツを確認中です...

    injectRefs[30] = injectString(info.modid, 0x0071E71F, "Begin a new game");//最初からストーリーを始めます
    injectRefs[31] = injectString(info.modid, 0x0071E74B, "Continue story mode");//前回の続きからストーリーを再開します

    injectRefs[32] = injectString(info.modid, 0x0071DA9B, "Message Speed");//メッセージスピード
    injectRefs[33] = injectString(info.modid, 0x0071DAB7, "Narrator Voice");//ガイドボイス選択
    injectRefs[34] = injectString(info.modid, 0x0071DC5B, "Default");//デフォルト

    injectRefs[35] = injectString(info.modid, 0x0071D20B, "Psion Flag Start");//Psyon Flag Start

    injectRefs[36] = injectString(info.modid, 0x0071E33F, "Psion Bullet");//サイオン・フラッグ
    injectRefs[37] = injectString(info.modid, 0x00717B33, "Loopcast");//ループキャスト

    injectRefs[38] = injectString(info.modid, 0x00716EE7, "Pause");//中断します
    injectRefs[39] = injectString(info.modid, 0x00716EF7, "Continue");//中断をやめます

    injectRefs[40] = injectString(info.modid, 0x0071D833, "Settings");//セッティングモード

    injectRefs[41] = injectString(info.modid, 0x0071D823, "Options");//オプション
    injectRefs[42] = injectString(info.modid, 0x0071D713, "Cancel");//キャンセル

    injectRefs[43] = injectString(info.modid, 0x0071D7BF, "Story mode");//ストーリーモード

    injectRefs[44] = injectString(info.modid, 0x0071D74F, "Gameplay Help");//操作ヘルプ
    injectRefs[45] = injectString(info.modid, 0x0071D75F, "Close gameplay Help");//操作ヘルプを閉じる

    injectRefs[46] = injectString(info.modid, 0x0071E16F, "Skip scene");//シーンスキップ？
    injectRefs[47] = injectString(info.modid, 0x00716713, "Do you want to skip this scene?");//このイベントをスキップしますか？

    injectRefs[48] = injectString(info.modid, 0x0071E56F, "Story Mode: Advances the main story");//オリジナルストーリーを進めることができるモードです
    injectRefs[49] = injectString(info.modid, 0x0071E5BB, "Match Mode: Any character and rule may be chosen");//キャラクターや対戦ルールを自由に選んで遊ぶことができるモードです
    injectRefs[50] = injectString(info.modid, 0x0071E61F, "CAD Customization Mode: Allows for CADs to be tuned and spells to be set");//アクション中に使用する魔法を、自由にカスタマイズできるモードです。ＣＡＤに魔法をセットしたり、チューニングを行うことができます
    //
    injectRefs[51] = injectString(info.modid, 0x0071E6DF, "Settings Mode");//各種設定を変更することができるモードです

    if (sanityCheck() != CODE_SUCCESS_INJECT_STR) return CODE_FAILED_INJECT_STR;
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
        if (sanityCheck() != CODE_SUCCESS_INJECT_STR) {
            return CODE_FAILED_INJECT_STR;
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
    SceUID injectRef = taiInjectData(modid, 0x000000, actual_address, text, strlen(text) + 1);//Add 1 to remove the trailing line
    if (injectRef > -1) {
        log_writef("Injected text \"%s\" into address 0x%06x (actual address: 0x%06x)\nRef: %d\n\n", text, address, actual_address, injectRef);
    } else {
        log_writef("Failed to inject word \"%s\" into address 0x%06x! (actual address 0x%06x)\n", text, address, actual_address);
        return -1;
    }
    return injectRef;
}
