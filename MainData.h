#include <iostream>
#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include <math.h>
#include "SDL2/SDL_ttf.h"
#include <cstdlib>
#include <stdlib.h>
#define RAND_MAX 60000                               // The Maximum Possible Amount of Generated Visual_Entity
#define STANDARD_FORMAT 32, 0, 0, 0, 0               // Standard Pixel Encoding of every sdl_surface     || true color, including 8 bit alpha channel

// Important class

namespace engine
{
    static int fps = 24;
    static float actual_fps;
}

namespace utility
{
    std::string Concantenate_Char_and_String(std::string str, char character)
    {
        str.push_back(character);
        return str;
    }
}

namespace time
{
    static unsigned int starting_tick;
    static unsigned int finishing_tick;
    static int Actual_Starting_Tick;
    static int Actual_Finishing_Tick;
}


namespace reaction_spreadsheet
{
    class error_log
    {
    public:
        std::string judul;
        std::vector<std::string> data;
        error_log(std::string title = "Log")
        {
            judul = title;
        }
    };

    static error_log internal_error_log("Error pada tingkat interaksi kode antar kode");


    static error_log warning_log("Interaksi Signifikan Antar Elemen");


}

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
    class Sprite
    {
    private:
        long int id;
        bool Alpha_Blending = true;                          // not mutually exclusive
        bool Chromatic_Isolationism = false;
        SDL_Color Chroma_Key;

        SDL_Texture* Main_Texture  = NULL;
        SDL_Rect Cropping_Frame = {0, 0, 0, 0};
        int Final_X_Axis_Scale = 1;
        int Final_Y_Axis_Scale = 1;
        int PosX;                             // Point Based Location
        int PosY;
        SDL_Renderer* Main_Renderer = NULL;
        SDL_Rect Final_Frame = {0, 0, 0, 0};
        SDL_Surface Pixel_Cache;


    public:


        bool isActive = false;

        static std::vector<int> daftar_id;      // Global Variable
        Sprite(int &ID_Container)                   // For the time being, failed construction doesnt mean cancelled construction
        {

            int possible_id;
            bool isUnique = true;

            while(true)
            {
                possible_id = rand();                   // Generate rng for possible id
                for(int n : daftar_id)
                {
                    if(n == possible_id){isUnique = false; break;}   // if the generated rng isnt an unique id, break the search and start all over again
                }
                if(isUnique){break;}   // if the generated rng is an unique integer, stop the process and proceed to the next step
            }
            daftar_id.push_back(possible_id);
            id = possible_id;
            ID_Container = possible_id;    // pass back the value to a reference variable, to be used by superroutine
        }

        short Load_Texture(SDL_Surface* Surface)
        {
            if(Main_Renderer != NULL && Surface != NULL){Main_Texture = SDL_CreateTextureFromSurface(Main_Renderer, Surface); Pixel_Cache = *Surface; return 1;}  // Success
            else if(Main_Renderer == NULL && Surface != NULL){return 2;}           // No Renderer attached
            else if(Main_Renderer == NULL && Surface == NULL){return 3;}           // invalid surface pointer and no renderer detected
            else if(Main_Renderer != NULL && Surface == NULL){return 4;}           // invalid surface pointer
            else{return 5;}                                                        // unknown error
        }

        short Attach_Renderer(SDL_Renderer* Renderer)
        {
            if(Renderer != NULL){Main_Renderer = Renderer; return 1;}   // Valid Proccess
            else if(Renderer == NULL){return 2;}                        // Invalid pointer passed
            else{return 3;}                                             // Unknown error
        }

        short Crop(SDL_Rect* Frame, int x = 0, int y = 0, int w = 0, int h = 0)
        {
            if(Frame != NULL){Cropping_Frame = *Frame; return 1;}   // Uses prefabricated sdl_rect
            else if(Frame == NULL){Cropping_Frame.x = x;
                                   Cropping_Frame.y = y;
                                   Cropping_Frame.w = w;            // Manual specification
                                   Cropping_Frame.h = h;
                                   return 2;}
            else{return 3;}                                         // unknown error
        }

        short Scale(int x = 1, int y = 1)
        {
            Final_X_Axis_Scale = x;
            Final_Y_Axis_Scale = y;
            return 1;
        }

        short AlphasizeKeyColor(SDL_Color* KeyColor, int r = 0, int g = 0, int b = 0)
        {
            if(Main_Texture != NULL)
            {
                SDL_Color Color;
                short procedure;
                if(KeyColor != NULL){Color = *KeyColor; procedure = 1;}
                else if(KeyColor == NULL){Color.r = r; Color.g = g; Color.b = b; procedure = 2;}
                else{return 3;}                   // Unknown error, break subroutine

                SDL_SetColorKey(&Pixel_Cache, SDL_TRUE, SDL_MapRGB(Pixel_Cache.format, Color.r, Color.g, Color.b));      // Create a surface with transparent specified color
                SDL_UpdateTexture(Main_Texture, NULL, Pixel_Cache.pixels, Pixel_Cache.pitch);                           // Update the texture based on that surface

                return procedure;
            }
            else if(Main_Texture == NULL){return 4;}
            else{return 5;}
        }

        short Render()
        {
            if((Main_Renderer != NULL) && (Main_Texture != NULL))
            {
                int CenterX = Cropping_Frame.x + (1/2) * (Cropping_Frame.w);
                int CenterY = Cropping_Frame.y + (1/2) * (Cropping_Frame.h);

                int OffsetX = PosX - CenterX;
                int OffsetY = PosY - CenterY;

                Final_Frame = Cropping_Frame;
                Final_Frame.x += OffsetX;
                Final_Frame.y += OffsetY;

                if(Alpha_Blending){SDL_SetTextureBlendMode(Main_Texture, SDL_BLENDMODE_BLEND);}
                else{SDL_SetTextureBlendMode(Main_Texture, SDL_BLENDMODE_NONE);}

                SDL_RenderCopy(Main_Renderer, Main_Texture, &Cropping_Frame, &Final_Frame);

                return 1;
            }
            else if(Main_Renderer == NULL)
            {
                if(Main_Texture != NULL){return 2;}                           // Valid Texture but non valid renderer
                else if(Main_Texture == NULL){return 3;}                      // both invalid
                else{}
            }
            else if(Main_Renderer != NULL)
            {
                if(Main_Texture == NULL){return 4;}                            // Valid Renderer but invalid texture
                else{}
            }
            else{return 5;}                                                     // Unknown Error
        }

        short Position(int x = 1, int y = 1)
        {
            PosX = x;
            PosY = y;
            return 1;
        }

        short BlendMode(bool alpha = true)
        {
            Alpha_Blending = alpha;
            return 1;
        }

        short setChromaKeyMode(bool flag = true)
        {
            Chromatic_Isolationism = flag;
            return 1;
        }

        short setChromaColor(SDL_Color* Color, int r = 0, int g = 0, int b = 0)
        {
            if(Color != NULL){Chroma_Key = *Color; return 1;}
            else if(Color == NULL){Chroma_Key.r = r;
                                   Chroma_Key.g = g;
                                   Chroma_Key.b = b;
                                   return 2;}
            else{return 3;}
        }

        bool ConfirmId(long int id_number)
        {
            if(id_number == id)
            {
                return true;
            }
            else{return false;}
        }



    };
    std::vector<int> Visual::Sprite::daftar_id;

    SDL_Surface* Load_Image(std::string nama_file)
    {
        const char* abc = nama_file.c_str();
        return SDL_LoadBMP(abc);
    }

    static surface_map_container GLOBAL_SURFACE_CACHE;
    static std::vector<Sprite*> GLOBAL_SPRITE_POINTER_CACHE;

    Sprite* Search_Sprite(int id_number)
    {
        bool isFound = false;
        for(Sprite* x : GLOBAL_SPRITE_POINTER_CACHE)
        {
            if(x->ConfirmId(id_number))
            {
                isFound = true;
                std::cout << "Found" << std::endl;
                return x;
                break;
            }
            else{}
        }
        if(!isFound)
        {
            std::cout << "Not Found" << std::endl;
            return NULL;
        }
    }

    void Scale_Rect(int multiplier, SDL_Rect &shape)
    {
        shape.h *= multiplier;
        shape.w *= multiplier;
    }

    static SDL_Surface SOLE_PIXEL;
    static SDL_Rect PIXEL_CROPPER;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    static SDL_Window* WINDOW = NULL;
    static SDL_Surface* LAYAR = NULL;
}

namespace audio
{
    class Audio_Engine
    {

    };
}

namespace Text
{
    // Semi Accessible Data Container   ( FSM State )
    std::string TEXT_BUFFER;
    SDL_Surface* Text_Panel_Pointer;
    TTF_Font* Font1_Pointer;
    SDL_Rect* TextBox_Dimension_Pointer = new SDL_Rect();
    SDL_Rect* TextBox_Cropping_Pointer =  new SDL_Rect();
    std::string ACTIVE_FONT_NAME;
    SDL_Color Warna_Tulisan = {255, 255, 255};
    SDL_Color Warna_Latar = {28, 78, 90};
    static int TEXT_ENGINE_VISUAL_ENTITY_ID;

    // State Modifier Subroutine   ( FSM State Modifier )
    int Change_Color(int r, int g, int b)
    {
        Warna_Tulisan.r = r;
        Warna_Tulisan.g = g;
        Warna_Tulisan.b = b;
        return 1;
    }

    int Init(std::string Font_Name)
    {
        Font1_Pointer = TTF_OpenFont(Font_Name.c_str(), 30);  // Setting up the font data;
        ACTIVE_FONT_NAME = Font_Name;                         // Recording the name of the used font for future use
        Text_Panel_Pointer = SDL_CreateRGBSurface(NULL, 1000, 1000, 32, 0, 0, 0, 0);
        Visual::GLOBAL_SPRITE_POINTER_CACHE.push_back(new Visual::Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID));
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->Anchor(Visual::LAYAR);
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->Source_Surface = Text_Panel_Pointer;
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->Destination_Dimension = TextBox_Dimension_Pointer;
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->Cropper_Rectangle = TextBox_Cropping_Pointer;
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->activate();
        Visual::Search_Sprite(TEXT_ENGINE_VISUAL_ENTITY_ID)->setAlphaBlend(true);
        TextBox_Dimension_Pointer->h = 10000;
        TextBox_Dimension_Pointer->w = 10000;
        TextBox_Dimension_Pointer->x = 0;
        TextBox_Dimension_Pointer->y = 0;               // GAME_ENGINE_CONSTANT
        TextBox_Cropping_Pointer->h = 10000;
        TextBox_Cropping_Pointer->w = 10000;
        TextBox_Cropping_Pointer->x = 0;
        TextBox_Cropping_Pointer->y = 0;
        return 1;

    }
    int Change_Position(int x = 0, int y = 0)
    {
        TextBox_Dimension_Pointer->x = x;
        TextBox_Dimension_Pointer->y = y;
        return 1;
    }
    int Change_Size(int n = 10)
    {
        Font1_Pointer = TTF_OpenFont(ACTIVE_FONT_NAME.c_str(), n);
        return 1;
    }
    int write(std::string string_data, bool isNewLine = true)
    {
        if(isNewLine)
        {
            TEXT_BUFFER += '\n' + string_data;
            return 1;
        }
        else
        {
            TEXT_BUFFER += string_data;
        }
    }
    int clean_string()
    {
        TEXT_BUFFER.clear();
        return 1;
    }

    int clean_panel()
    {
        SDL_FillRect(Text_Panel_Pointer, NULL, SDL_MapRGBA(Text_Panel_Pointer->format, Warna_Latar.r, Warna_Latar.g, Warna_Latar.b, 90));
    }

    // FSM Execution Procedure

    int print(int x = 0, int y = 0)
    {
        SDL_Surface *low_buffer;
        std::string low_string_buffer;
        int low_panel_width;
        int low_panel_height;
        SDL_Rect Frame = {0, 0, 0, 0};
        SDL_Surface* Main_Frame = SDL_CreateRGBSurface(NULL, 1000, 1000, STANDARD_FORMAT);

        for(char t : TEXT_BUFFER)
        {
            if(t == '\n')                            // If line break character is met, stop writing the line, then render the line into the main panel
            {
                low_buffer = TTF_RenderText_Blended(Font1_Pointer, low_string_buffer.c_str(), Warna_Tulisan);     // Aqquire single line panel

                SDL_SetColorKey(low_buffer, SDL_TRUE, SDL_MapRGB(low_buffer->format, 0, 0, 0));

                TTF_SizeText(Font1_Pointer, low_string_buffer.c_str(), &low_panel_width, &low_panel_height);    // Aqquire the panel dimension

                Frame.w = low_panel_width;
                Frame.h = low_panel_height;                                                                     // Set the bliiting dimension// Set the bliiting dimension

                SDL_BlitSurface(low_buffer, NULL, Main_Frame, &Frame);                                  // Crop the single line panel and merge it into the main panel

                Frame.y += low_panel_height;                                                                    // offset the blitting frame

                low_string_buffer.clear();                                                                      // clean the writing line
                delete low_buffer;                                                                              // the buffer panel is dynamically allocated in the heap part of the memory, so i need to manually delete to prevent memory overloading
            }
            else{low_string_buffer += t;}             // no line break character is met, so continue writing
        }

        low_buffer = TTF_RenderText_Blended(Font1_Pointer, low_string_buffer.c_str(), Warna_Tulisan);

        SDL_SetColorKey(low_buffer, SDL_TRUE, SDL_MapRGB(low_buffer->format, 0, 0, 0));

        TTF_SizeText(Font1_Pointer, low_string_buffer.c_str(), &low_panel_width, &low_panel_height);

        Frame.w = low_panel_width;
        Frame.h = low_panel_height;

        SDL_BlitSurface(low_buffer, NULL, Main_Frame, &Frame);

        Frame.y += low_panel_height;

        low_string_buffer.clear();
        delete low_buffer;                                                                               // the buffer panel is dynamically allocated in the heap part of the memory, so i need to manually delete to prevent memory overloading

        Frame.x = x;
        Frame.y = y;
        Frame.w = 1000;
        Frame.h = 1000;
        SDL_SetColorKey(Main_Frame, SDL_TRUE, SDL_MapRGB(Main_Frame->format, 0, 0, 0));
        SDL_BlitSurface(Main_Frame, NULL, Text_Panel_Pointer, &Frame);
        return 1;
    }

    int direct_write(std::string kalimat, int x, int y, int fsize = 10)
    {
        clean_string();
        write(kalimat, true);
        Change_Size(fsize);
        print(x, y);
        clean_string();
    }
}

#define MainData Included
