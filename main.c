#include "sprites.h"
#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 420
#define MAX_ANGLE 170
int win_counter = 0;
int check_ForDirection(struct circle sprite)
{
    if (sprite.direction == 'u')
        return -sprite.angle;
    else
        return sprite.angle;
}
int betweenRandom(float low, float high)
{
    return ((float)rand() / high) * low;
}
void check_ballPosn(struct circle *sprite, PADDLE *paddle1)
{
    sprite->y += tan(sprite->angle);
    sprite->x += sprite->velocity;
    srand(time(NULL));
    if ((sprite->x <= paddle1->paddle.x + PLAYER_WIDTH && sprite->x >= paddle1->paddle.x) && (sprite->y >= paddle1->paddle.y && sprite->y <= paddle1->paddle.y + PLAYER_HEIGHT))
    {
        if (sprite->y <= paddle1->paddle.y + 10 || sprite->y > paddle1->paddle.y + 60)
        {
            sprite->angle = 80;
            sprite->angle = check_ForDirection(*sprite);
        }
        if ((sprite->y <= paddle1->paddle.y + 20 && sprite->y > paddle1->paddle.y + 10) || (sprite->y > paddle1->paddle.y + 50 && sprite->y < paddle1->paddle.y + 60))
        {
            sprite->angle = 73;
            sprite->angle = check_ForDirection(*sprite);
        }
        if ((sprite->y <= paddle1->paddle.y + 30 && sprite->y > paddle1->paddle.y + 10) || (sprite->y > paddle1->paddle.y + 40 && sprite->y < paddle1->paddle.y + 60))
        {
            sprite->angle = 60;
            sprite->angle = check_ForDirection(*sprite);
        }

        sprite->velocity *= -1;
        if (sprite->velocity < 12)
            sprite->velocity += 0.2;
    }
    if (sprite->y + sprite->r * 2 >= SCREEN_HEIGHT)
    {
        sprite->angle *= -1;
        sprite->direction = 'u';
    }
    if (sprite->y <= 0)
    {
        sprite->angle *= -1;
        sprite->direction = 'd';
    }
    if (sprite->x <= 0)
    {
        SDL_Delay(2000);
        sprite->x = SCREEN_WIDTH / 2;
        sprite->y = paddle1->paddle.y = SCREEN_HEIGHT / 2;
        sprite->angle = 1;
        sprite->velocity = -4;
    }
    if (sprite->x >= SCREEN_WIDTH)
    {
        SDL_Delay(2000);
        sprite->x = SCREEN_WIDTH / 2;
        sprite->y = paddle1->paddle.y = SCREEN_HEIGHT / 2;
        sprite->angle = 1;
        win_counter = 1;
        sprite->velocity = -4;
    }
}
void algorithm(struct circle *sprite, PADDLE *paddle1)
{
    if (sprite->y > paddle1->paddle.y + PLAYER_HEIGHT / 2)
    {
        paddle1->velocity = abs(paddle1->velocity);
    }
    else if (sprite->y < paddle1->paddle.y + PLAYER_HEIGHT / 2)
    {
        paddle1->velocity = -abs(paddle1->velocity);
    }
    if ((sprite->x <= paddle1->paddle.x + PLAYER_WIDTH && sprite->x >= paddle1->paddle.x) && (sprite->y >= paddle1->paddle.y && sprite->y <= paddle1->paddle.y + PLAYER_HEIGHT))
    {
        if (sprite->y <= paddle1->paddle.y + 10 || sprite->y > paddle1->paddle.y + 60)
        {
            sprite->angle = 80;
            sprite->angle = check_ForDirection(*sprite);
        }
        if ((sprite->y <= paddle1->paddle.y + 20 && sprite->y > paddle1->paddle.y + 10) || (sprite->y > paddle1->paddle.y + 50 && sprite->y < paddle1->paddle.y + 60))
        {
            sprite->angle = 73;
            sprite->angle = check_ForDirection(*sprite);
        }
        if ((sprite->y <= paddle1->paddle.y + 30 && sprite->y > paddle1->paddle.y + 10) || (sprite->y > paddle1->paddle.y + 40 && sprite->y < paddle1->paddle.y + 60))
        {
            sprite->angle = 60;
            sprite->angle = check_ForDirection(*sprite);
        }

        sprite->velocity *= -1;
        if (sprite->velocity > -12)
        {
            sprite->velocity -= 0.2;
        }
    }
}
int main(int argc, char **argv)
{
the_start:
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Surface *windowSurface = NULL;
    SDL_Surface *currentImage = NULL;
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Let's you render shapes

    PADDLE player1;
    PADDLE player2;

the_initialization:
    player1.velocity = 0;
    player2.velocity = 9;
    player1.paddle.x = 50;
    player1.paddle.y = player2.paddle.y = SCREEN_HEIGHT / 2 - PLAYER_HEIGHT;
    player2.paddle.x = 680 - 50;
    player1.paddle.h = player2.paddle.h = PLAYER_HEIGHT;
    player1.paddle.w = player2.paddle.w = PLAYER_WIDTH;
    player1.player_color.r = player1.player_color.g = player1.player_color.b = player1.player_color.a = 255;
    player2.player_color.r = player2.player_color.g = player2.player_color.b = player2.player_color.a = 255;

    struct circle pong_ball;
    pong_ball.r = 5;
    pong_ball.x = 680 / 2 - pong_ball.r;
    pong_ball.y = 420 / 2 - pong_ball.r;
    pong_ball.angle = 1;
    bool running = true;
    pong_ball.velocity = -4;
    while (running)
    {
        SDL_Delay(1000 / 60);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    player1.velocity = -3;
                    break;
                case SDLK_DOWN:

                    player1.velocity = 3;
                    break;

                case SDLK_RETURN:
                    pong_ball.velocity *= -1;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (player1.velocity < 0)
                        player1.velocity = 0;
                    break;
                case SDLK_DOWN:
                    if (player1.velocity > 0)
                        player1.velocity = 0;
                    break;
                case SDLK_ESCAPE:
                    SDL_DestroyWindow(window);
                    window = NULL;
                    SDL_FreeSurface(currentImage);
                    SDL_FreeSurface(windowSurface);
                    SDL_Quit();
                    return 0;
                    break;
                default:
                    break;
                }
                break;
            }
        }

        check_ballPosn(&pong_ball, &player1);
        algorithm(&pong_ball, &player2);
        SDL_UpdateWindowSurface(window);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, player1.player_color.r, player1.player_color.g, player1.player_color.b, player1.player_color.a);
        SDL_RenderFillRect(renderer, &player1.paddle);
        SDL_RenderDrawRect(renderer, &player1.paddle);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player2.paddle);
        SDL_RenderDrawRect(renderer, &player2.paddle);
        draw_circle(renderer, pong_ball.x, pong_ball.y, pong_ball.r, player1.player_color);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        player1.paddle.y += player1.velocity;
        player2.paddle.y += player2.velocity;
        if (win_counter == 1)
        {
            player1.player_color.r = 255;
            player1.player_color.g = 215;
            player1.player_color.b = 0;
            win_counter = 0;
        }
    }
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_FreeSurface(currentImage);
    SDL_FreeSurface(windowSurface);
    SDL_Quit();
    return 0;
}