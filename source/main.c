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
#include "rock.h"

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
    oamInit(&oamMain,SpriteMapping_1D_128,false);
    u16 *gfxMain = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

    memcpy(gfxMain, clangTiles, clangTilesLen);
    memcpy(SPRITE_PALETTE, clangPal, clangPalLen);

    int p_x = 128 - 32;
    int p_y = 125;

    oamSet(&oamMain, 0, p_x, p_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxMain, -1, false, false, false, false, false);


    memcpy(gfxMain, rockTiles, rockTilesLen);
    memcpy(SPRITE_PALETTE, rockPal, rockPalLen);

    int b_x = 128 + 32;
    int b_y = 150;

    oamSet(&oamMain, 1, b_x, b_y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, gfxMain, -1, false, false, false, false, false);





    consoleDemoInit();

    printf("PAD:Scroll background");


   


  


    while(1){
        swiWaitForVBlank();
        oamSetXY(&oamMain, 0, p_x, p_y);
        oamSetXY(&oamMain, 1, b_x, b_y);
      
       

        oamUpdate(&oamMain);

        scanKeys();

        u16 keys_held = keysHeld();

        // キーを押したら移動
     
        if (keys_held & KEY_LEFT) p_x--;
       
        if (keys_held & KEY_RIGHT) p_x++;

     
        if (keys_held & KEY_UP) b_y++;
       
        if (keys_held & KEY_DOWN) b_y--;
       
    }
    return 0;


}