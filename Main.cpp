#include "MainData.h"

#include "InitializeEngine().h"
#include "InitializeContent().h"
#include "HandleEvent().h"
#include "Process().h"
#include "Render().h"



int main(int argc, char* args[])
{
	InitializeEngine();
	/*InitializeContent();

	while(true)
	{
	    time::Actual_Starting_Tick = SDL_GetTicks();
	    if((time::finishing_tick - time::starting_tick) < floor(1000 / engine::fps)){SDL_Delay(round(1000 / engine::fps) - (time::finishing_tick - time::starting_tick));}
	    time::starting_tick = SDL_GetTicks();
        HandleEvent();
        Process();
        Render();
        time::finishing_tick = SDL_GetTicks();
        time::Actual_Finishing_Tick = SDL_GetTicks();
        engine::actual_fps = 1 / (time::Actual_Finishing_Tick - time::Actual_Starting_Tick) ;
	}*/

    SDL_Surface* asu = SDL_CreateRGBSurface(NULL, 1000, 1000, 32, 0, 0, 0, 0);      // does window surface not accept alphqa blending ?
    SDL_Surface* memek = SDL_CreateRGBSurface(NULL, 1000, 1000, 32, 0, 0, 0, 0);
    std::cout << "111" << std::endl;
    SDL_FillRect(asu, NULL, SDL_MapRGBA(asu->format, 23, 43, 72, 65));
    SDL_FillRect(memek, NULL, SDL_MapRGBA(memek->format, 12, 87, 65, 255));
    SDL_FillRect(Visual::LAYAR, NULL,  SDL_MapRGBA(Visual::LAYAR->format, 19, 87, 90, SDL_ALPHA_TRANSPARENT));
    std::cout << "222" << std::endl;
    SDL_SetSurfaceBlendMode(asu, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(memek, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(Visual::LAYAR, SDL_BLENDMODE_BLEND);
    std::cout << "333" << std::endl;
    SDL_BlitSurface(memek, NULL, asu, NULL);
    SDL_BlitSurface(asu, NULL, Visual::LAYAR, NULL);
    SDL_UpdateWindowSurface(Visual::WINDOW);
    std::cout << "fuck you !!" << std::endl;
    SDL_Delay(1000);



	return 0;
}






// unsigned int is kinda janky, even more if you add float











