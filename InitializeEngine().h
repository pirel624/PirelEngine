#ifndef Data
#include "Data.h"
#endif // MainData

void InitializeEngine()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Its fucking broken asshole !" << std::endl;
    }
    TTF_Init();
    Visual::WINDOW = SDL_CreateWindow("PIREL_ENGINE_v.0.17", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Visual::SCREEN_WIDTH, Visual::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(Visual::WINDOW == NULL)    // If there is no fucking window
    {
        std::cout << "No Window !!!, I repeat, No Fucking window" << std::endl;
    }else
    {
        Visual::LAYAR = SDL_GetWindowSurface(Visual::WINDOW);              // mengakses buffer rendering pada window
    }


    // Initializing Text Engine
	{
        if(Text::Init("Font1.ttf"))
        {
            std::cout << "Text engine initialization successful" << std::endl;
            SDL_Delay(1000);
        }
	}

}
