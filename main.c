# include <stdbool.h>
# include <raylib.h>
# include <unistd.h>
# include <math.h>
# define RESOUCE_PATH "assets"

//

// Game data
typedef struct GameData {
    Vector2 playersPosition;
}GameData;

GameData gameData = {
    .playersPosition={100,100}

};


// textures
Texture2D spaceShip;

bool init_game(){
    spaceShip = LoadTexture(RESOUCE_PATH"/spaceShip/ships/green.png");
    
    return true;
}

Vector2 normalize(Vector2 vector){
    float length =  sqrtf(powf(vector.x,2) + powf(vector.y,2));
    vector.x = vector.x / length;
    vector.y = vector.y / length;
    return vector;
}

void moveShip(float deltaTime){
    Vector2 move = {.x=0,.y=0};
    // move up
    if (IsKeyDown(KEY_DOWN)){
        move.y++;
    }
    // move Down
    if (IsKeyDown(KEY_UP)){
        move.y--;
    }
    // move Right
    if (IsKeyDown(KEY_RIGHT)){
        move.x++;
    }
    if (IsKeyDown(KEY_LEFT)){
        move.x--;
    }
    if (move.x != 0 || move.y!=0){
        move = normalize(move);
        move.x *=  deltaTime * 200;
        move.y *=  deltaTime * 200;
        gameData.playersPosition.x += move.x;
        gameData.playersPosition.y += move.y;
    }
}


bool clear_game(){
    return false ;
}

int main (){
    TraceLog(LOG_INFO, "Hello Space Game");
    InitWindow(900,600 , "First Raylib window");
    TraceLog(LOG_INFO, "Resouce Path |%s|", RESOUCE_PATH);
    bool game_started = init_game();
    if (game_started == false){

        TraceLog(LOG_FATAL, "Failed Init the Game");
        // TODO add message box in here to show to the user
        return 0;
    }
    while(!WindowShouldClose()){
        float time = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        # pragma region movement

        moveShip(time);

        # pragma endregion

        DrawTexture(spaceShip, gameData.playersPosition.x, gameData.playersPosition.y,WHITE);
        DrawText("HELLO TO RAY LIB", 10, 20, 50, LIGHTGRAY);

        EndDrawing();
    }

    // sleep(10);
    return 0;
}
