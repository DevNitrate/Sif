#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>
#include <vector>
#include <sstream>
#include "Pixel.h"
#include "Img.h"

int main(int argc, char *argv[]) {
    /*if (argc != 2) {
        std::cout << "Wrong number of args. Command use: 'sif img.sif'";
        return 1;
    }*/
    
    Img img("g.sif");
    //Img img(argv[1]);

    Camera2D camera;

    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "Simple Image Format");
    SetTargetFPS(60);

    camera.offset = (Vector2){ img.width/2.0f-img.width/2, img.height/2.0f-img.height/2 };
    camera.rotation = 0.0f;
    camera.target = (Vector2){ 0.0f, 0.0f };

    if (img.width > img.height) {
        camera.zoom = (float)screenWidth / img.width;
    } else {
        camera.zoom = (float)screenHeight / img.height;
    }

    Image buffer = GenImageColor(img.width, img.height, RED);

    int count = 0;

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            Color col = img.data[count].getRGBA();
            ImageDrawPixel(&buffer, j, i, col);
            count++;
        }
    }

    Texture2D image = LoadTextureFromImage(buffer);
    
    while (WindowShouldClose() == false){
        BeginDrawing();
            ClearBackground(BLACK);

            camera.zoom += ((float)GetMouseWheelMove()*0.1f);

            if (camera.zoom > 3.0f) camera.zoom = 3.0f;
            else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) camera.target.x -= GetMouseDelta().x;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) camera.target.y -= GetMouseDelta().y;
        BeginMode2D(camera);

            DrawTexture(image, 0, 0, WHITE);

        EndMode2D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}