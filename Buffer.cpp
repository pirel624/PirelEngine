#include <iostream>
#include "SDL2/SDL.h"
#include <vector>
#include <string>

// Important class


/*namespace reaction_spreadsheet
{
    class error_log
    {
    public:
        std::string judul;
        std::vector<std::string> data;
    };

    static error_log internal_error_log;
    internal_error_log.judul = "Error pada tingkat interaksi kode antar kode";

    static error_log warning_log;
    warning_log.judul = "Interaksi Signifikan Antar Elemen";

}*/

namespace Visual
{
    struct peta
    {
        long int id;
        SDL_Surface* gambar;
    };

    class surface_map_container
    {
    private:



    public:

        std::vector<peta> wadah;

        surface_map_container(){};

        void add(long int number, SDL_Surface* gambar)
        {
            bool isSameIdExist = false;

            for(const peta isi : wadah)            // Mengecek kesaam id
            {
                if(isi.id == number)
                {
                    isSameIdExist = true;
                    break;
                }
                else
                {

                }
            }

            if(isSameIdExist)
            {
    //            reaction_spreadsheet::internal_error_log.data.push_back("surface_map_container::void add():: there already exist the same id");
            }

            else
            {
                peta blah;
                blah.id = number;
                blah.gambar = gambar;
                wadah.push_back(blah);
            }

        }
    };


    class Visual_Entity
    {
    private:

        long int id;
        std::vector<long int> daftar_id;

        SDL_Surface* Source_Surface = NULL;               // Main Data Pool
        SDL_Rect* Cropper_Rectangle = NULL;
        SDL_Surface * Destination_Surface = NULL;
        SDL_Rect * Destination_Dimension = NULL;

        bool isActive = false;




    public:

        Visual_Entity(long int ID)
        {
            bool isUnique = false;
            for(long int x: daftar_id)
            {
                if(ID == x)
                {
                    isUnique = false;
                    break;
                }

                else if(ID != x)
                {
                    isUnique = true;
                }
                else{}
            }

            if(isUnique)
            {
                id = ID;
                daftar_id.push_back(ID);
            }
            else{}
        }

        void Low_source(SDL_Surface* gambar_asal)
        {
            Source_Surface = gambar_asal;
        }

        void Low_crop(float titik_asal_x, float titik_asal_y, float panjang_x, float panjang_y)
        {
            Cropper_Rectangle = new SDL_Rect;
            Cropper_Rectangle->x = titik_asal_x;
            Cropper_Rectangle->y = titik_asal_y;
            Cropper_Rectangle->w = panjang_x;
            Cropper_Rectangle->h = panjang_y;
        }

        void Low_anchor(SDL_Surface* tujuan)
        {
            Destination_Surface = tujuan;
        }

        void Low_dimense(float titik_asal_x, float titik_asal_y, float panjang_x, float panjang_y)
        {
            Destination_Dimension = new SDL_Rect;
            Destination_Dimension->x = titik_asal_x;
            Destination_Dimension->y = titik_asal_y;
            Destination_Dimension->w = panjang_x;
            Destination_Dimension->h = panjang_y;
        }

        void activate()
        {
            isActive = true;
        }

        void deactivate()
        {
            isActive = false;
        }

        void Attach(SDL_Surface* gambar_asal)
        {
            Low_source(gambar_asal);
        }

        void Anchor(SDL_Surface* tujuan)
        {
            Low_anchor(tujuan);
        }

        void Crop(SDL_Rect* Cropper)
        {
            if(Cropper != NULL)
            {
                Low_crop(Cropper->x, Cropper->y, Cropper->w, Cropper->h);
            }
            else
            {
                Cropper_Rectangle = NULL;
            }
        }

        void Dimense(SDL_Rect* Dimensor)
        {
            if(Dimensor != NULL)
            {
                Low_crop(Dimensor->x, Dimensor->y, Dimensor->w, Dimensor->h);
            }
            else
            {
                Destination_Dimension = NULL;
            }
        }

        void Blit()
        {
            if(isActive)
            {
                SDL_BlitSurface(Source_Surface, Cropper_Rectangle, Destination_Surface, Destination_Dimension);
            }
            else if(!isActive)
            {
                //reaction_spreadsheet::warning_log.data.push_back("Trying to blits inactive visual entities" + id);
            }
            else
            {

            }
        }



    };

    SDL_Surface* Load_Image(std::string nama_file)
    {
        const char* abc = nama_file.c_str();
        return SDL_LoadBMP(abc);
    }


    static surface_map_container GLOBAL_SURFACE_CACHE;
    static std::vector<Visual_Entity*> GLOBAL_VISUAL_ENTITY_POINTER_CACHE;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    static SDL_Window* WINDOW = NULL;
    static SDL_Surface* LAYAR = NULL;
}




void Initialize_Engine();
void Initialize_Content();
void Handle_Event();
void Process();
void Render();

int main(int argc, char* args[])
{
    // Engine Initialization

    SDL_Window* window = NULL;
    SDL_Surface* LAYAR = NULL;



    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Its fucking broken asshole !" << std::endl;
    }
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)    // If there is no fucking window
    {
        std::cout << "No Window !!!, I repeat, No Fucking window" << std::endl;
    }else
    {
        LAYAR = SDL_GetWindowSurface(window);              // mengakses buffer rendering pada window
    }

// At this point, all sdl related object is active.

    // Program Initialization

    SDL_Surface* gambar = Visual::Load_Image("Test_Image_1.bmp");
    Visual::Visual_Entity* sprite = new Visual::Visual_Entity(0);
    Visual::GLOBAL_VISUAL_ENTITY_POINTER_CACHE.push_back(sprite);
    Visual::GLOBAL_VISUAL_ENTITY_POINTER_CACHE[0]->Anchor(LAYAR);
    sprite->Attach(gambar);
    sprite->activate();



    while(true)
    {

        sprite->Blit();






        // Rendering Pipeline
        SDL_UpdateWindowSurface(window);
        SDL_Delay(2000);

    }











    while(true);




    return 0;


}











