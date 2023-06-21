#include <SDL2/SDL.h>
#include <iostream>
#include <numeric>
#include <complex>


int is_in_set(std::complex<double> c)
{
    std::complex<double> j(0.28, 0.008);
    std::complex<double> z(0, 0);
    for (int i = 0; i < 300; i++)
    {
        z = std::pow(z, 2) + c;
        //c = std::pow(c, 2) + j;
        if (std::norm(z) > 10)
        {
            return i;
        } 
    }
    return 0;
}

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
    //SDL_RenderSetScale(renderer, 1.2, 1.2);

    for (double x = 0.0; x < 1.0; x += 0.0005)
    {
        for (double y = 0.0; y < 1.0; y += 0.0005)
        {
            double point_x = std::lerp(-2.0, 2.0, x);
            double point_y = std::lerp(-2.0, 2.0, y);
            int iters = is_in_set(std::complex<double>(point_x, point_y));
            if (iters == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
            else 
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    cos(0.016 * iters + 4) * 255,
                    cos(0.013 * iters + 2) * 255,
                    cos(0.01 * iters + 1) * 255,
                    155);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
        }
    } 

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
}