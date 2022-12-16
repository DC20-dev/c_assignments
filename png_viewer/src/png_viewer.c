#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "png_decoder.h"

int main(int argc, char **argv)
{
    // exit if no image was passed
    if(argc <= 1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION ,"No image provided!");
        return -1;
    }

    // initialize graphic output

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("PNG VIEWER", SDL_WINDOWPOS_CENTERED,
     SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE);

    if(!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer){
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    // get to loop

    int running = 1;
    const int passed_images = argc - 1;
    int selected_image = 1;
    int image_changed = 1;
    int draw_texture = 0;
    SDL_Texture *texture;
    uint32_t image_len, width, height;

    while (running)
    {
        // input
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if(event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    selected_image = selected_image > 1 ? selected_image-1 : 1;
                    image_changed = 1;
                    break;
                case SDLK_RIGHT:
                    selected_image = selected_image < passed_images ? selected_image+1 : passed_images;
                    image_changed = 1;
                    break;
                default:
                    break;
                }
                SDL_Log("selected image: %d\n", selected_image);
            }
        }
        // update
        if(image_changed)
        {
            image_changed = 0;
            unsigned char* image;
            int exitcode = decode(argv[selected_image], &image, &image_len, &width, &height);
            if(exitcode == 0)
            {
                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
                // check on texture
                if(!texture)
                {
                    draw_texture = 0;
                    SDL_Log("Unable to create texture: %s", SDL_GetError());
                }
                SDL_UpdateTexture(texture, NULL, image, width * 4);
                SDL_SetTextureAlphaMod(texture, 255);
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                free(image);
                draw_texture = 1;
            }
            else
            {
                draw_texture = 0;
                SDL_Log("Error while decoding image");
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if(draw_texture)
        {
            SDL_Rect target_rect = {0, 0, width, height};
            SDL_RenderCopy(renderer, texture, NULL, &target_rect);
        }

        SDL_RenderPresent(renderer);
    }


    return 0;
}
