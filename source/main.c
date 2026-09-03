// source/main.c
#include <nds.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char **argv)
{
    videoSetMode(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    int bg=bgInitHidden(0,BgType_Text8bpp,BgSize_B8_256x256,0,1);
    memcpy(bgGetGfxPtr(bg),bg0Tiles,bg0TilesLen);
    memcpy(bgGetMapPtr(bg),bg0Map,bg0MapLen);
    memcpy(BG_PALETTE,bg0Pal,bg0PalLen);

    bgShow(bg);

    vramSetBankB(VRAM_B_MAIN_SPRITE);
    oamInit(&oamMain,SpriteMapping_1D_128,false);

    u16 *gfxMain = oamAllocateGfx(&oamMain,SpriteSize_32x32,SpriteColorFormat_256Color);
    memcpy(gfxMain,clangTiles,clangTilesLen);
    memcpy(SPRITE_PALETTE,clangPal,clangPalLen);
 
    u16 *gfxheart = oamAllocateGfx(&oamMain,SpriteSize_32x32,SpriteColorFormat_256Color);
    memcpy(gfxheart,rockTiles,rockTilesLen);
    memcpy(SPRITE_PALETTE,rockPal,rockPalLen);

    int x0=112;
    int y0=150;

    int x1=rand() % 200;
    int y1=-30;

    int x2=rand() % 200;
    int y2=-60;

    int x3 =100;
    int y3 =100;

    int x4 = rand() % 224;
    int y4 =  -64;


    int speed1_y = 1 + (rand() % 3);
    int speed2_y = 2 + (rand() % 2);
   
    int speed4_y = 1 + (rand() % 2);
    
    
    
    int score=0;
    int hiScore=0;
    bool GameOver=false;

    oamSet(&oamMain, 0, x0, y0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxMain, -1, false, false, false, false, false);
    oamSet(&oamMain, 1, x1, y1, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxheart, -1, false, false, false, false, false);
    oamSet(&oamMain, 2, x2, y2, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxheart, -1, false, false, false, false, false);
    oamSet(&oamMain, 3, x3, y3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxheart, -1, false, false, false, false, false);
    oamSet(&oamMain, 4, x4, y4, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfxheart, -1, false, false, false, false, false);

    consoleDemoInit();
    printf("UpperTale\n");
    printf("プレイヤーは攻撃を避けてください\n");
    printf("Score    : %d\n", score);
    printf("Hi-Score : %d\n", hiScore);

    // スタートボタンを押したらゲームがスタートするようにした
    printf("Pless Start Key and Start");

    while (1) {
    swiWaitForVBlank();
    scanKeys();
    u16 keys_down = keysDown();
      if (keys_down & KEY_START) break;
    }

    consoleClear();

    while(1){
        swiWaitForVBlank();

        scanKeys();
        u16 keys_held = keysHeld();
        u16 keys_down = keysDown();

        if (!GameOver) {
            if ((keys_held & KEY_LEFT) && x0 > 0)    x0 -= 2;
            if ((keys_held & KEY_RIGHT) && x0 < 224) x0 += 2;
            if ((keys_held & KEY_UP) && y0 > 0)      y0 -= 2;
            if ((keys_held & KEY_DOWN) && y0 < 160)  y0 += 2;

            y1 += speed1_y;
            if (y1 > 192) {
                y1 = -32;
                x1 = rand() % 200;
                speed1_y = 1 + (rand() % 10);
            }

            y2 += speed2_y;
            if (y2 > 192) {
                y2 = -32;
                x2 = rand() % 200;
                speed2_y = 2 + (rand() % 10);
            }

            x3 += 4;
           
             y4 += speed4_y;
             x4 += 3;
              if (y4 > 192) {
                y4 = -32;
                x4 = rand() % 224;
                speed4_y = 2 + (rand() % 2);
            }


            score++;
            if(score > hiScore){
                hiScore = score;
            }

            printf("\x1b[5;13H%d", score);
            printf("\x1b[6;13H%d\n", hiScore);

            if ((abs(x0 - x1) < 20 && abs(y0 - y1) < 20) || 
                (abs(x0 - x2) < 20 && abs(y0 - y2) < 20) || (abs(x0 - x3) < 20 && abs(y0 - y3) < 20)||
                (abs(x0 - x4) < 20 && abs(y0 - y4) < 20)) {
                
                GameOver = true;
                
                printf("====================\n");
                printf("*** GAME OVER ***\n");
                printf("Press A to Retry!\n");
                printf("====================\n");
            }
        } else {
            if (keys_down & KEY_A) {
                x0 = 112;
                y0 = 150;

                x1 = rand() % 224;
                y1 = -32;

                x2 = rand() % 224;
                y2 = -64;
                x3 = -50;
                x4 = rand() % 224;
                y4 = -32;



                speed1_y = 1 + (rand() % 3);
                speed2_y = 2 + (rand() % 2);
              
                
                score = 0;
                GameOver = false;

                printf("UpperTale\n");
                printf("プライヤーは攻撃を避けてください\n");
                printf("Score    : %d\n", score);
                printf("Hi-Score : %d\n", hiScore);
            }
        }

        oamSetXY(&oamMain, 0, x0, y0);
        oamSetXY(&oamMain, 1, x1, y1);
        oamSetXY(&oamMain, 2, x2, y2);
        oamSetXY(&oamMain, 3, x3, y3);
        oamSetXY(&oamMain, 4, x4, y4);
        oamUpdate(&oamMain);
    }
    return 0;
}