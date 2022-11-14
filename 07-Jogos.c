int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms, int delay){
    int aux = delay;
    int event = SDL_WaitEventTimeout(evt, delay);
    if (event){
    	delay -= (SDL_GetTicks() - *ms);
    	return event;
    }else{
    	delay = aux;
    	return event;
    }
}
// int delay = 500;
// Uint32 ms = SDL_GetTicks();
// int isevt = AUX_WaitEventTimeoutCount(&evt, &ms,delay);