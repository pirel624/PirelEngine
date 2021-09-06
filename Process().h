#ifndef Data
#include "Data.h"
#endif // MainData


void Process()
{

    Visual::Search_Visual_Entity(id_cache::VE_Id.Random_1)->Cropper_Rectangle = &buffer_variable::Cropper_Rectangle;  // This Line Contain fatal error
    std::cout << "After Cropping" << SDL_GetError() << std::endl;
    Visual::Search_Visual_Entity(id_cache::VE_Id.Random_1)->Destination_Dimension = &buffer_variable::Destination;
    std::cout << SDL_GetError() << std::endl;
    buffer_variable::Destination.x++;                 // Moving the skeleton frame that random_1 attached to
    buffer_variable::Destination.y++;
    buffer_variable::Cropper_Rectangle.w++;
    buffer_variable::Cropper_Rectangle.h++;

    Text::clean_string();
    Text::clean_panel();
    Text::write("Emprical Frame per Second : " + std::to_string(engine::actual_fps), false);
    Text::write("Theretical Frame per Second : " + std::to_string(engine::fps), true);
    Text::print(buffer_variable::Destination.x, buffer_variable::Destination.y);
    //Text::Change_Position();
    Text::clean_string();

}
