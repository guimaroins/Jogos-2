#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
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
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
    SDL_Rect t = { 50,150, 50,50 };
    SDL_RenderFillRect(ren, &t);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
    SDL_Rect u = { 400,150, 50,50 };
    SDL_RenderFillRect(ren, &u);
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0xFF,0x00);
    SDL_Rect v = { 50,300, 50,50 };
    SDL_RenderFillRect(ren, &v);
    SDL_SetRenderDrawColor(ren, 0xFF,0x00,0xFF,0x00);
    SDL_Rect w = { 400,300, 50,50 };
    SDL_RenderFillRect(ren, &w);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_Rect y = { 200,200, 100,100 };
    SDL_RenderFillRect(ren, &y);
    SDL_Rect a = { 50,100, 10,10 };
    SDL_RenderFillRect(ren, &a);
    SDL_Rect b = { 440,100, 10,10 };
    SDL_RenderFillRect(ren, &b);
    SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
    SDL_Rect c = { 50,380, 10,10 };
    SDL_RenderFillRect(ren, &c);
    SDL_Rect d = { 440,380, 10,10 };
    SDL_RenderFillRect(ren, &d);
    SDL_RenderPresent(ren);
    SDL_Delay(2000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
