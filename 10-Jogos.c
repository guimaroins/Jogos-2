#include <SDL2/SDL.h>

struct ret {
    SDL_Rect r;
    SDL_Point origPos;
    SDL_bool dragOrigin;
    SDL_bool didDrag;
};

int main (int argc, char* args[])
{
    /* INICIALIZACAO */

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("2.0",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    /* EXECUÇÃO */

    SDL_bool event = SDL_TRUE;
    struct ret retangulo;
    SDL_Rect cubo = { 275,275, 50,50 };
    SDL_Point  mouse;
    retangulo.r = cubo;
    retangulo.didDrag = SDL_FALSE;
    retangulo.dragOrigin = SDL_FALSE;
    
    while (event) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &retangulo.r);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        SDL_WaitEvent(&evt);
        switch(evt.type){
        case(SDL_WINDOWEVENT):
            switch(evt.window.event){
            case SDL_WINDOWEVENT_CLOSE:
            event = SDL_FALSE;
            break;
            }
        break;
        case(SDL_MOUSEBUTTONDOWN):
            SDL_GetMouseState(&mouse.x, &mouse.y);
            if(SDL_PointInRect (&mouse, &retangulo.r)){
                retangulo.origPos.x = retangulo.r.x;
                retangulo.origPos.y = retangulo.r.y;
                retangulo.dragOrigin = SDL_TRUE;
                retangulo.didDrag = SDL_FALSE;
            };
            break;
        case(SDL_MOUSEMOTION):
            SDL_GetMouseState(&mouse.x, &mouse.y);
            if(retangulo.dragOrigin){
                retangulo.r.x = mouse.x;
                retangulo.r.y = mouse.y;
                retangulo.didDrag = SDL_TRUE;
                SDL_Log("Dragging...");
            }
            break;
        case(SDL_MOUSEBUTTONUP):
            retangulo.dragOrigin = SDL_FALSE;
            if(retangulo.didDrag){
                SDL_Log("Dropped!");
            }else {
                SDL_Log("Clicked!");
            }
            break;
        case(SDL_KEYDOWN):
            switch(evt.key.keysym.sym){
                case(SDLK_ESCAPE):
                    retangulo.dragOrigin = SDL_FALSE;
                    retangulo.r.x =  retangulo.origPos.x;
                    retangulo.r.y = retangulo.origPos.y;
                    SDL_Log("Cancelled!");
                    break;
            }
            break;
        }
}
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

