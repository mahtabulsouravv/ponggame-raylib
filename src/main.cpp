#include <iostream>
#include <raylib.h>
using namespace std;

/*

STEPS TO DEVELOP

1. Create A Blank Screen & Game Loop
2. Draw The Paddles And The Ball
3. Move The Ball Around
4. Check For A Collision With All Edges
5. Move The Players Paddle
6. Move The CPU Paddle With AI
7. Check For A Collision With The Paddle
8. Add Scoring

*/

/* 4.BALL CLASS */
class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    /* BALL DRAWING */
    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    /* MOVING BALL / UPDATE */
    void Update()
    {
        x += speed_x;
        y += speed_y;
    }


};

/* BALL INSTANCE */
Ball ball;

int main()
{
    /* 1DEFINE SCREEN SIZE AS CONSTANT */
    const int screen_width = 1280;
    const int screen_height = 800;

    /* 1INITILIZE THE GAME WINDOW */
    InitWindow(screen_width, screen_height, "Pong Game By MahtabulShourav");
    SetTargetFPS(60);

    /* INITILIZE BALL OBJECT */
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    /* 1GAME LOOP */
    while (WindowShouldClose() == false)
    {
        /* BLANK CANVAS */
        BeginDrawing();

        /* UPDATING */
        ball.Update();


        ClearBackground(BLACK);
        /* 2.3DRAWING LINE */
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        /* 2.1DRAWING BALL */
        ball.Draw();
        // DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);

        /* 2.2DRAWING PADDLE(RECTANGLE) GEOMETRY APPLIED */
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, WHITE);

        /* END CANVAS DRAWING */
        EndDrawing();
    }

    /* 1DESTROY WINDOW */
    CloseWindow();
    return 0;
}