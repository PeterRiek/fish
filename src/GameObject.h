#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject
{
public:
    GameObject(SDL_Renderer *renderer, const char *imagePath, int x, int y, int width, int height);
    ~GameObject();

    void update();
    void render();

private:
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
};