#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject
{
public:
    GameObject(SDL_Renderer *renderer, const char *imagePath, int x, int y, int width, int height);
    ~GameObject();

    virtual void update();
    virtual void render();

protected:
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
};