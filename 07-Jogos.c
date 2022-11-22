int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* espera, Uint32* ms) {
	int event = SDL_WaitEventTimeout(evt, *espera);
	if (event){
		*espera -= (SDL_GetTicks() - *ms);
		if(*espera <= 0) {
			*espera = 0;
		}
		return event;
	}else{
		return event;
	}
}
/*
int espera = 500;
Uint32 ms = SDL_GetTicks();
int isevt = AUX_WaitEventTimeoutCount(&evt, &espera , &ms);
*/
