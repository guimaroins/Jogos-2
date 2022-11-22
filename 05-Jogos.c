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
    struct retangulo {
        SDL_Rect r;
        int corR;
        int corG;
        int corB;
    };
    struct retangulo retangulos[10];
    
    while (event) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        
        for(int i = 0; i < qtd;i++){
            SDL_SetRenderDrawColor(ren, retangulos[i].corR,retangulos[i].corG,retangulos[i].corB,0x00);
            SDL_RenderFillRect(ren, &retangulos[i].r);
        }

        SDL_RenderPresent(ren);
        
        SDL_WaitEvent(&evt);
        switch (evt.type) {
            case SDL_KEYDOWN:
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
            break;
            case SDL_WINDOWEVENT:
                switch(evt.window.event){
                case SDL_WINDOWEVENT_CLOSE:
                event = SDL_FALSE;
                break;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
            switch(evt.button.button){
                case SDL_BUTTON_LEFT:
                    if(qtd < 10){
                        SDL_GetMouseState(&x,&y);
                        struct retangulo ret;
                        SDL_Rect r = {x, y , 10 + rand() % 100,10 + rand() % 100 };
                        ret.r = r;
                        ret.corR = rand() % 255;
                        ret.corG = rand() % 255;
                        ret.corB = rand() % 255;
                        retangulos[qtd] = ret;
                        qtd++;                    
                    }
            }
            break;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
