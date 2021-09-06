#ifndef Data
#include "Data.h"
#endif // MainData


InitializeContent()
{
    // Initializing Random_1 Visual Entity
    {
        SDL_Surface* gambar = Visual::Load_Image("Test_Image_1.bmp");
        Visual::Visual_Entity* sprite = new Visual::Visual_Entity(id_cache::VE_Id.Random_1);
        Visual::GLOBAL_VISUAL_ENTITY_POINTER_CACHE.push_back(sprite);
        sprite->Anchor(Visual::LAYAR);
        sprite->Attach(gambar);
        sprite->activate();                       // set to be seen by the main renderer
        sprite->setChromaKey();
        sprite->SetKeyColor(255, 255, 255);
        sprite->setAlphaBlend(true);
        std::cout << "Random 1 Initialized" << std::endl;

        Text::Change_Size();
        Text::Change_Position(300, 300);
    }
    {

    }







}

