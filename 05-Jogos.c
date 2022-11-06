#include <SDL2/SDL.h>
#include <math.h>
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1-4-1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    SDL_bool event = SDL_TRUE;
    int qtd = 0;
    int x,y;
    int corR[10], corB[10], corG[10];
    SDL_Rect retangulos[10];

    
    while (event) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        for(int i = 0; i < qtd;i++){
            SDL_SetRenderDrawColor(ren, corR[i],corG[i],corB[i],0x00);
            SDL_RenderFillRect(ren, &retangulos[i]);
        }
        SDL_RenderPresent(ren);
        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    if(r.y == 0){
                        break;
                    }
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    if(r.y == 490){
                        break;
                    }
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    if(r.x == 0){
                        break;
                    }
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    if(r.x == 490){
                        break;
                    }
                    r.x += 5;
                    break;
            }
        }
        if (evt.type == SDL_WINDOWEVENT) {
            switch(evt.window.event){
            case SDL_WINDOWEVENT_CLOSE:
            event = SDL_FALSE;
            break;
            }
        }
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            switch(evt.button.button){
                case SDL_BUTTON_LEFT:
                    if(qtd < 10){
                        SDL_GetMouseState(&x,&y);
                        SDL_Rect retangulo = {x, y , 10 + rand() % 100,10 + rand() % 100 };
                        corR[qtd] = rand() % 255;
                        corG[qtd] = rand() % 255;
                        corB[qtd] = rand() % 255;
                        retangulos[qtd] = retangulo;
                        qtd = qtd + 1;

                    }
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}