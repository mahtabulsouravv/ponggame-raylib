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

/* COLOR */
Color Orange = Color{200, 130, 70, 255};  
Color Dark_Orange = Color{223, 151, 85, 1};    // Dark Orange
Color Light_Orange = Color{240, 175, 120, 255};  
Color BallColor = Color{47, 54, 69, 255};

/* SCORE */
int player_score = 0;
int cpu_score = 0;

/* BALL CLASS */
class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    /* BALL DRAWING */
    void Draw()
    {
        DrawCircle(x, y, radius, BallColor);
    }

    /* MOVING BALL / UPDATE */
    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }

        if (x + radius >= GetScreenWidth()) // CPU WINS
        {
            cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0)
        {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

/* PADDLE CLASS */
class Paddle
{
    /* ENCAPSULATION */
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }

        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    /* PADDLE DRAWING */
    void Draw()
    {
        DrawRectangleRounded(Rectangle{x,y, width, height}, 0.8, 0, WHITE);
    }

    /* MOVING PADDLE / UPDATE */
    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

/* APPLYING INHERITANCE */
class CPUPaddle : public Paddle
{
public:
    /* MOVING PADDLE / UPDATE BY APPLYING AI ALGORITHMS */
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }

        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

/* CLASS INSTANCE */
Ball ball;
Paddle player;
CPUPaddle cpu;

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

    /* INITILIZE PLAYER OBJECT */
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    /* INITILIZE CPU OBJECT */
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    /* 1GAME LOOP */
    while (WindowShouldClose() == false)
    {
        /* BLANK CANVAS */
        BeginDrawing();

        /* UPDATING */
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        /* CHECKING FOR COLLISIONS */
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        ClearBackground(Dark_Orange);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Orange);
        DrawCircle(screen_width/2, screen_height/2, 150, Light_Orange);
        /* 2.3DRAWING LINE */
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        /* 2.1DRAWING BALL */
        ball.Draw();
        cpu.Draw();
        // DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);

        /* 2.2DRAWING PADDLE(RECTANGLE) GEOMETRY APPLIED */
        // DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        // DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, WHITE);
        player.Draw();
        /* SCORE TEXT */
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        /* END CANVAS DRAWING */
        EndDrawing();
    }

    /* 1DESTROY WINDOW */
    CloseWindow();
    return 0;
}