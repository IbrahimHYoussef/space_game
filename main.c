# include <inttypes.h>
# include <stdio.h>
# include <stdbool.h>
# include <raylib.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define RESOUCE_PATH "assets"

# define BACKGROUND 3

void DisplaySystemMessage(char *message) {

    if (strlen(message) > 50) {
        return;
    }
    char messagef[50];
    // try xmessage
    sprintf(messagef, "xmessage -center '%s'", message);
    int result =  system(messagef);
    if (result == 0 ){
        return;
    }
}

// tiled renderer
typedef struct TiledRenderer{
    float backgroundSize;
    Texture2D texture;
}TiledRenderer;

void TiledRenderer_render(TiledRenderer* tiledRenderer,Camera2D* camera){

	Vector2 origin = {0.0f,0.0f};
	Rectangle src = {0,0,tiledRenderer->backgroundSize,tiledRenderer->backgroundSize};

    Vector2 viewRect = camera->target;
    for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			float posX = x + viewRect.x / tiledRenderer->backgroundSize;
			float posY = y + viewRect.y / tiledRenderer->backgroundSize;
			Rectangle source = {posX,posY,tiledRenderer->texture.width,tiledRenderer->texture.height};
            DrawTexturePro(tiledRenderer->texture,source,source,origin,0.0f,WHITE);
		}
	}
    DrawTexturePro(tiledRenderer->texture,src,src,origin,0.0f,WHITE);
}

TiledRenderer tiledRenderer [BACKGROUND] ={
    {.backgroundSize = 10000},
    {.backgroundSize = 10000},
    {.backgroundSize = 10000},
};


// Game data
typedef struct GameData {
    Vector2 playersPosition;
}GameData;

GameData gameData = {
    .playersPosition={100,100}
};

// Game Options
typedef struct GameOption{
    Vector2 ScreenSize;
}GameOption;

GameOption gameOption ={
    .ScreenSize={0,0}
};

// textures
Texture2D spaceShip;
Texture2D background[BACKGROUND];

// camera
Camera2D camera = {0};

bool init_game(){
    spaceShip = LoadTexture(RESOUCE_PATH"/spaceShip/ships/green.png");
    if (spaceShip.id <=0){
        return false;
    }

    background[0] = LoadTexture(RESOUCE_PATH"/background1.png");
    if (background[0].id <=0){
        return false;
    }
    tiledRenderer[0].texture = background[0];


    background[1] = LoadTexture(RESOUCE_PATH"/background2.png");
    if (background[1].id <=0){
        return false;
    }
    tiledRenderer[1].texture = background[1];

    background[2] = LoadTexture(RESOUCE_PATH"/background3.png");
    if (background[2].id <=0){
        return false;
    }
    tiledRenderer[2].texture = background[2];

    TraceLog(LOG_INFO,"Background size width:%d height:%d",background[0].width,background[0].height);
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
    // move Left
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        move.x--;
    }
    if (move.x != 0 || move.y!=0){
        move = normalize(move);
        move.x *=  deltaTime * 1000;
        move.y *=  deltaTime * 1000;
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
    camera.zoom = 0.5f;
}

bool clear_game(){
    return false ;
}

int main (){
    TraceLog(LOG_INFO, "Hello Space Game");
    InitWindow(gameOption.ScreenSize.x,gameOption.ScreenSize.y , "First Raylib window");
    SetTargetFPS(60);
    TraceLog(LOG_INFO, "Resouce Path |%s|", RESOUCE_PATH);
    bool game_started = init_game();
    if (game_started == false){
        DisplaySystemMessage("Failed to load assets");
        TraceLog(LOG_FATAL, "Failed Init the Game");
        return 1;
    }
    float time;
    #ifdef SHOWFRAME
    float fps;
    char fpsC[9];
    #endif
    attachCameraToPlayer(gameData.playersPosition, 900, 600);
    while(!WindowShouldClose()){
        time = GetFrameTime();

        moveShip(time);

        # pragma region drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
            // DrawTexture(backgroud,0,0,WHITE);
            for (int i = 0;i<BACKGROUND;i++){
                TiledRenderer_render(&tiledRenderer[i],&camera);
            }
            DrawTexture(spaceShip, gameData.playersPosition.x, gameData.playersPosition.y,WHITE);
            #ifdef SHOW_FRAME
            fps = GetFPS();
            sprintf(fpsC,"%.2f",fps);
            DrawText(fpsC,10, 10, 50, WHITE);
            #endif
        EndDrawing();
        # pragma endregion
    }
    CloseWindow();
    return 0;
}
