#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "SDL2_gfxPrimitives.h"


int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.2.2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_Rect r = { 00,50, 500,10 };
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
    SDL_Rect s = { 00,400, 500,10 };
    SDL_RenderFillRect(ren, &s);
    

    int circle = filledCircleColor(ren, 150, 150, 50, 0xF0FF00FF);
    SDL_RenderPresent(ren);
   
    int elipse = filledEllipseColor(ren,350, 300, 10,70, 0xF000F0FF);
    SDL_RenderPresent(ren);
    
    int elipse2 = filledEllipseRGBA(ren,200, 300, 80,20, 0x00,0xFF,0x00,0xFF);
    SDL_RenderPresent(ren);
    
    int box = boxColor(ren,300,100, 350,200,0xFF0000FF);
    SDL_RenderPresent(ren);
    
    int trigon = filledTrigonRGBA(ren,200,200,300,200,300,300,0x00,0xF0,0xFF,0xFF);
    SDL_RenderPresent(ren);
    
    SDL_Delay(3000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
