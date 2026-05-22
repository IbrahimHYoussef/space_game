# include <stdio.h>
# include <stdbool.h>
# include <raylib.h>
# include <unistd.h>
# include <math.h>
# define RESOUCE_PATH "assets"

// tiled renderer
typedef struct TiledRenderer{
    float backgroundSize;
    Texture2D texture;
}TiledRenderer;




// Game data
typedef struct GameData {
    Vector2 playersPosition;
}GameData;

GameData gameData = {
    .playersPosition={100,100}
};


// textures
Texture2D spaceShip;
Texture2D backgroud;

// camera
Camera2D camera = {0};

bool init_game(){
    spaceShip = LoadTexture(RESOUCE_PATH"/spaceShip/ships/green.png");
    backgroud = LoadTexture(RESOUCE_PATH"/background1.png");
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
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        move.y++;
    }
    // move Down
    if (IsKeyDown(KEY_UP) ||IsKeyDown(KEY_W)){
        move.y--;
    }
    // move Right
    if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        move.x++;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        move.x--;
    }
    if (move.x != 0 || move.y!=0){
        move = normalize(move);
        move.x *=  deltaTime * 200;
        move.y *=  deltaTime * 200;
        gameData.playersPosition.x += move.x;
        gameData.playersPosition.y += move.y;
    }
    // update camera
    camera.target = gameData.playersPosition;
}

void attachCameraToPlayer(Vector2 vector,float sWidth,float sHight){
    camera.target = (Vector2){vector.x,vector.y};
    camera.offset = (Vector2){sWidth/2.0f,sHight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
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
    float time;
    #ifdef SHOWFRAME
    float fps;
    char fpsC[9];
    #endif
    attachCameraToPlayer(gameData.playersPosition, 900, 600);
    while(!WindowShouldClose()){
        time = GetFrameTime();

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawTexture(backgroud,0,0,WHITE);
        # pragma region movement
        moveShip(time);
        # pragma endregion

        DrawTexture(spaceShip, gameData.playersPosition.x, gameData.playersPosition.y,WHITE);
        #ifdef SHOW_FRAME
        fps = GetFPS();
        sprintf(fpsC,"%.2f",fps);
        DrawText(fpsC,10, 10, 50, WHITE);
        #endif
        EndDrawing();
    }
    return 0;
}
