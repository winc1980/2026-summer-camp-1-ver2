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

typedef struct {
    int x;
    int y;
}Splite;



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

    int x = 128 - 32;
    int y = 125;

    oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_16Color, gfxMain, 0, true, false, false, false, false);



    consoleDemoInit();

    printf("PAD:Scroll background");


   


  


    while(1){
        swiWaitForVBlank();
        oamSetXY(&oamMain, 0, x, y);
      
       

        oamUpdate(&oamMain);

        scanKeys();

        u16 keys_held = keysHeld();

        // キーを押したら移動
     
        if (keys_held & KEY_LEFT) x--;
       
        if (keys_held & KEY_RIGHT) x++;

     

       
    }
    return 0;


}