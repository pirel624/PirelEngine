#ifndef MainData
#include "MainData.h"
#endif // MainData


namespace buffer_variable
{
    SDL_Rect Cropper_Rectangle = {10, 10, 10 , 10};
    SDL_Rect Destination = {10, 10, 10, 10};
}

namespace id_cache
{
    struct Visual_Entity_Id
    {
        int Text_Panel;
        int Random_1;                 // Volatile
        int Random_2;
    };
    static Visual_Entity_Id VE_Id;
}










#define AuxData Included
