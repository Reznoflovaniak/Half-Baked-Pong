#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 60
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <crtdbg.h>
#include <time.h>
int sector;
int loadSprites();
typedef struct PADDLE
{
    SDL_Rect paddle;
    int velocity;
    SDL_Color player_color;
} PADDLE;
SDL_Color white;
void draw_circle(SDL_Renderer *renderer, float x, float y, float radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            float dx = radius - w;
            float dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
struct circle
{
    int r;
    int x;
    int y;
    int angle;
    int velocity;
};