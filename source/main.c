// source/main.c
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include "bg0.h"
#include "nds/arm9/background.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/video.h"
#include "nds/input.h"
#include "nds/interrupts.h"
#include "nds/ndstypes.h"

int main(int argc, char **argv)
{
    videoSetMode(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);

    int bg=bgInitHidden(0, BgType_Text8bpp, BgSize_B8_256x256, 0, 1);

    memcpy(bgGetGfxPtr(bg), bg0Tiles, bg0TilesLen);
    memcpy(bgGetMapPtr(bg),bg0Map,bg0MapLen);

    memcpy(BG_PALETTE, bg0Pal, bg0PalLen);

    bgShow(bg);

    consoleDemoInit();

    printf("PAD:Scroll background");

    int x=0,y=0;

    while(1){
        swiWaitForVBlank();
        bgSetScroll(bg, x, y);
        bgUpdate();
        scanKeys();

        u16 keys_held = keysHeld();

        if(keys_held & KEY_LEFT){
            x++;
        }
        if(keys_held & KEY_RIGHT){
            x--;
        }
        if(keys_held & KEY_UP){
            y++;
        }
        if(keys_held & KEY_DOWN){
            y--;
        }
    }
    return 0;


}