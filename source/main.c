// source/main.c
#include <nds.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "bg0.h"
#include "nds/arm9/background.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/sprite.h"
#include "nds/arm9/video.h"
#include "nds/input.h"
#include "nds/interrupts.h"
#include "nds/ndstypes.h"
#include "clang.h"
int main(int argc, char **argv)
{
    videoSetMode(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    
    int bg=bgInitHidden(0, BgType_Text8bpp, BgSize_B8_256x256, 0, 1);

    memcpy(bgGetGfxPtr(bg), bg0Tiles, bg0TilesLen);
    memcpy(bgGetMapPtr(bg),bg0Map,bg0MapLen);

    memcpy(BG_PALETTE, bg0Pal, bg0PalLen);

    bgShow(bg);


    vramSetBankB(VRAM_B_MAIN_SPRITE);
    oamInit(&oamMain,SpriteMapping_1D_32,false);
    u16 *gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);

    memcpy(gfxMain, clangTiles, clangTilesLen);
    memcpy(SPRITE_PALETTE, clangPal, clangPalLen);

    int x0 = 100;
    int y0 = 100;

    int x1 = 120;
    int y1 = 0;

    oamSet(&oamMain, 0, x0, y0, 0, 0, SpriteSize_32x32, SpriteColorFormat_16Color, gfxMain, 0, true, false, false, false, false);
    oamSet(&oamMain, 1, x1, y1, 0, 0, SpriteSize_32x32, SpriteColorFormat_16Color, gfxMain, 0, true, false, false, false, false);

    consoleDemoInit();

    printf("PAD:Scroll background");

    while(1){
        swiWaitForVBlank();

         oamSetXY(&oamMain, 0, x0, y0);
         oamSetXY(&oamMain, 1, x1, y1);
        // 回転・拡大縮小
        
        oamUpdate(&oamMain);

        scanKeys();

        u16 keys_held = keysHeld();

        // キーを押したら移動
        if(abs(x0-x1)<10 && abs(y0-y1)<10){
            printf("\x1b[10;10HGAME OVER!");
            printf("\x1b[12;5HPress A to Restart");
        }else{
             if (keys_held & KEY_LEFT) {
            x0--;
        }
        if (keys_held & KEY_RIGHT) {
            x0++;
        }
        if (keys_held & KEY_UP) {
            y0--;
        }
        if (keys_held & KEY_DOWN) {
            y0++;
        }

        y1 += 1;

        if (y1 > 192) {
            y1 = -32;
        }
        }
    }
    return 0;
}
    


