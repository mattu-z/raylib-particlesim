#include <raylib.h>


typedef struct{
    Vector2 position;
    Vector2 velocity;

    float radius;
    float reboundFactor;

    Texture2D texture;
}Ball;

#define MAX_BALLS 100
Ball balls[MAX_BALLS];
int ballCount= 1;

void UpdateBall(Ball *ballptr, int screenWidth, int screenHeight){

            ballptr->position.x+= ballptr->velocity.x;
            ballptr->position.y+= ballptr->velocity.y;

            //Right Wall
            if(ballptr->position.x >= screenWidth - ballptr->radius){
                ballptr->position.x = screenWidth - ballptr->radius;
                ballptr->velocity.x *= -ballptr->reboundFactor;}

            //Left Wall
            if(ballptr->position.x <= ballptr->radius){
            ballptr->position.x = ballptr->radius;
            ballptr->velocity.x *= -ballptr->reboundFactor;}

            //Bottom
            if(ballptr->position.y >= screenHeight - ballptr->radius){
            ballptr->position.y = screenHeight - ballptr->radius;
            ballptr->velocity.y *= -ballptr->reboundFactor;}

            //Top
            if(ballptr->position.y <= ballptr->radius){
            ballptr->position.y = ballptr->radius;
            ballptr->velocity.y *= -ballptr->reboundFactor;}
}


void DrawBall(Ball *ballptr){
    Rectangle source= {0, 0, (float)ballptr->texture.width, (float)ballptr->texture.height};
    Rectangle destination= {ballptr->position.x, ballptr->position.y, ballptr->radius * 2, ballptr->radius * 2};
    Vector2 originBall= {ballptr-> radius, ballptr-> radius};
    DrawTexturePro(ballptr->texture, source, destination, originBall, 0.0f, WHITE);
}

void SpawnBall(Ball balls[], int *ballCount, Texture2D texture){
    if(*ballCount >= MAX_BALLS){
            return;}
    Ball *ballptr= &balls[*ballCount];
    ballptr->position= GetMousePosition(); //Mouse Position
    ballptr->velocity= (Vector2){GetRandomValue(-5, 5), GetRandomValue(-5,5)};

    //trial
    if(ballptr->velocity.x== 0 && ballptr->velocity.y== 0){
            ballptr->velocity= (Vector2){0,2};}
    ballptr->radius= 40;
    ballptr->reboundFactor= 0.8f;

    ballptr->texture= texture;
    (*ballCount)++;
}

int main(void){

    const int screenWidth= 1280;
    const int screenHeight= 720;

    InitWindow(screenWidth, screenHeight, "Bouncing Ball");
    SetTargetFPS(60);

    Texture2D ballTexture= LoadTexture("assets/head.png");

    Ball balls[MAX_BALLS];
    int ballCount= 0;

    //first ball
    SpawnBall(balls, &ballCount, ballTexture);

    while(!WindowShouldClose()){

            //button spawn
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    SpawnBall(balls, &ballCount, ballTexture);}

            //update
            for(int i= 0; i< ballCount; i++){
                    UpdateBall(&balls[i], screenWidth, screenHeight);}

            //drawing
            BeginDrawing();
            ClearBackground(BLACK);

            for(int i= 0; i< ballCount; i++){
                    DrawBall(&balls[i]);}
            EndDrawing();
    }

    UnloadTexture(ballTexture);
    CloseWindow();
    return 0;
}








