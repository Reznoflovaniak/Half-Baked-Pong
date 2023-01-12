#include "sprites.h"
#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 420
#define MAX_ANGLE 170

int betweenRandom(float low, float high)
{
    return ((float)rand() / high) * low;
}
void check_ballPosn(struct circle *sprite, PADDLE paddle1, PADDLE paddle2)
{
    /*  Position            Angle
        y to y + 10         5 to 30
        y + 11 to y + 20    30 to 60
        y + 21 to y + 30    60 to 90
        y + 31 to y + 40    90 to 120
        y + 41 to y + 50    120 to 150
        y + 51 to y + 60    150 to 180

        Use the pythagorean theorum to calculate the distance between the current position
        of the ball and the end of the screen so you know how much to increment the ball's position
        by.
    */

    sprite->y += tan(sprite->angle);
    sprite->x += sprite->velocity;
    srand(time(NULL));

    if (sprite->x == paddle1.paddle.x && (sprite->y <= paddle1.paddle.y + paddle1.paddle.h && sprite->y > paddle1.paddle.y))
    {

        if (sprite->y > paddle1.paddle.y && sprite->y < paddle1.paddle.y + paddle1.paddle.h / 7)
        {
            sprite->angle = abs(betweenRandom(tan(78), tan(79)));
            printf("part 1\n");
        }
        if (sprite->y > paddle1.paddle.y + paddle1.paddle.h / 7 && sprite->y <= paddle1.paddle.y + paddle1.paddle.h * (2 / 7))
        {
            sprite->angle = abs(betweenRandom(tan(71), tan(77)));
            printf("part 2\n");
        }
        else if (sprite->y > paddle1.paddle.y + paddle1.paddle.h * (2 / 7) && sprite->y <= paddle1.paddle.y + paddle1.paddle.h * (3 / 7))
        {
            sprite->angle = abs(betweenRandom(tan(60), tan(70)));
            printf("part 3\n");
        }
        else if (sprite->y > paddle1.paddle.y + paddle1.paddle.h * (3 / 7) && sprite->y <= paddle1.paddle.y + paddle1.paddle.h * (4 / 7))
        {
            if (sprite->angle < 0)
                sprite->angle = abs(betweenRandom(tan(0), tan(55)));
            if (sprite->angle > 0)
                sprite->angle = -abs(betweenRandom(tan(0), tan(55)));
            printf("Part 4\n");
        }
        else if (sprite->y > paddle1.paddle.y + paddle1.paddle.h * (4 / 7) && sprite->y <= paddle1.paddle.y + paddle1.paddle.h * (5 / 7))
        {
            sprite->angle = -abs(betweenRandom(tan(60), tan(70)));
            printf("part 5\n");
        }
        else if (sprite->y > paddle1.paddle.y + paddle1.paddle.h * (5 / 7) && sprite->y <= paddle1.paddle.y + paddle1.paddle.h * (6 / 7))
        {
            sprite->angle = -abs(betweenRandom(tan(71), tan(77)));
            printf("part 6\n");
        }
        else if (sprite->y > paddle1.paddle.y + paddle1.paddle.h * (6 / 7) && sprite->y <= paddle1.paddle.y + paddle1.paddle.h)
        {
            sprite->angle = -abs(betweenRandom(tan(78), tan(79)));
            printf("Final part\n");
        }
        sprite->velocity *= -1;
    }
    if (sprite->y < 0)
    {
        sprite->angle *= -1;
        sprite->y = 5;
    }
    if (sprite->y + sprite->r * 2 >= SCREEN_HEIGHT)
    {
        sprite->angle *= -1;
        sprite->y = SCREEN_HEIGHT - sprite->r * 2;
    }
    // printf("Paddle X: %d\t\tPaddle Y: %d\n\nBall X: %d\t\tBall Y: %d\n\nDirection: %d\n\n", paddle1.paddle.x, paddle1.paddle.y, sprite->x, sprite->y, *ball_direction);
}
int main(int argc, char **argv)
{
    system("cls");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Surface *windowSurface = NULL;
    SDL_Surface *currentImage = NULL;
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Let's you render shapes

    PADDLE player1;
    PADDLE player2;

    player1.velocity = 0;
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
    pong_ball.velocity = -3;
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
                    player1.velocity = -2;
                    break;
                case SDLK_DOWN:

                    player1.velocity = 2;
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
                default:
                    break;
                }
                break;
            }
        }

        check_ballPosn(&pong_ball, player1, player2);
        SDL_UpdateWindowSurface(window);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, player1.player_color.r, player1.player_color.g, player1.player_color.b, player1.player_color.a);
        SDL_RenderFillRect(renderer, &player1.paddle);
        SDL_RenderDrawRect(renderer, &player1.paddle);
        SDL_RenderFillRect(renderer, &player2.paddle);
        SDL_RenderDrawRect(renderer, &player2.paddle);
        draw_circle(renderer, pong_ball.x, pong_ball.y, pong_ball.r, player1.player_color);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        player1.paddle.y += player1.velocity;
    }
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_FreeSurface(currentImage);
    SDL_FreeSurface(windowSurface);
    SDL_Quit();
    return 0;
}