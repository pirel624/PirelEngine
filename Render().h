#ifndef Data
#include "Data.h"
#endif // MainData

Render()
{


    SDL_FillRect(Visual::LAYAR, NULL, SDL_MapRGBA(Visual::LAYAR->format, 100, 35, 0, 0));    // Cleaning the main rendering buffer (this engine use double buffering)

    // Process each visual_entity
    for(Visual::Visual_Entity* Renderer : Visual::GLOBAL_VISUAL_ENTITY_POINTER_CACHE)
	{
	    std::cout << Renderer->Debug_give_id() << std::endl;
        Renderer->doTask(NULL);
        std::cout << SDL_GetError() << std::endl;
	}

	SDL_UpdateWindowSurface(Visual::WINDOW);
    SDL_ClearError();
}
