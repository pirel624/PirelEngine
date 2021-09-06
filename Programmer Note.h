To Do list

Refactor the fucking code


!!!! unitialized sdl surface

managing surface blending

format all pixel encoding to accomodate 32 bits depth

Implement hardware rendering

SDL_Surface* Source_Surface = NULL;               // Main Data Pool
        SDL_Surface buffer_surface;
        SDL_Rect* Cropper_Rectangle = NULL;
        SDL_Surface * Destination_Surface = NULL;
        SDL_Rect * Destination_Dimension = NULL;











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
            buffer_surface = *Source_Surface;
            //SDL_BlitSurface(Source_Surface, Cropper_Rectangle, Destination_Surface, Destination_Dimension);
            if(isActive)
            {
                if(Chromatic_Isolationism)
                {
                    SDL_SetColorKey(&buffer_surface, SDL_TRUE, SDL_MapRGBA(buffer_surface.format, Chroma_Key.r, Chroma_Key.g, Chroma_Key.b, Chroma_Key.a));            // set a certain key color to invisible
                }
                else{}
                if(Alpha_Blending)
                {
                    SDL_SetSurfaceBlendMode(&buffer_surface, SDL_BLENDMODE_BLEND);        // Activate alpha blending for the destination surface
                    SDL_SetSurfaceBlendMode(Destination_Surface, SDL_BLENDMODE_BLEND);
                    SDL_BlitSurface(&buffer_surface, Cropper_Rectangle, Destination_Surface, Destination_Dimension);
                    std::cout << id << "   " << "Alpha Blending Activated" << std::endl;
                }
                else
                {
                    SDL_BlitSurface(&buffer_surface, Cropper_Rectangle, Destination_Surface, Destination_Dimension);
                }

            }
            else if(!isActive)
            {
                //reaction_spreadsheet::warning_log.data.push_back("Trying to blits inactive visual entities" + id);
            }
            else
            {

            }
        }

        void SetKeyColor(int r = 255, int g = 255, int b = 255)
        {
            Chroma_Key.r = r;
            Chroma_Key.g = g;
            Chroma_Key.b = b;
        }
        void setAlphaBlend(bool flag = true)
        {
            Alpha_Blending = true;
        }
        void setChromaKey(bool flag = true)
        {
            Chromatic_Isolationism = flag;
        }

        bool ConfirmId(long int id_number)
        {
            if(id_number == id)
            {
                return true;
            }
            else{return false;}
        }

        void doTask(void* ptr)
        {
            Blit();
        }

        long int Debug_give_id()
        {}




std::cout << "Constructor Entry Point Passed" << std::endl;
            std::cout << &daftar_id << std::endl;
            bool isUnique = false;
            if(daftar_id.size() <= 0)
            {
                std::cout << "Container Empty" << std::endl;
                isUnique = true;
            }
            else
            {
                std::cout << "Container Inhabited" << std::endl;
                for(long int x : daftar_id)
                {
                    std::cout << "Second Constructor Entry Point Passed" << std::endl;
                    if(ID == x)
                    {
                        isUnique = false;
                        std::cout << "notUnique" << std::endl;
                        break;
                    }
                    else if(ID != x)
                    {
                        std::cout << "Unique" << std::endl;
                        isUnique = true;
                    }
                    else{}
                }
            }
            if(isUnique)
            {
                id = ID;
                daftar_id.push_back(ID);
            }
            else{reaction_spreadsheet::warning_log.data.push_back("Id ini (" + std::to_string(id) + ") sudah dipakai [Konstruksi Visual_Entity]");}
