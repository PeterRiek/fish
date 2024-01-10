#include "GameObject.h"
#include <SDL2/SDL_image.h>

GameObject::GameObject(SDL_Renderer *renderer, const char *imagePath, int x, int y, int width, int height) : renderer(renderer)
{
    SDL_Surface *surface = IMG_Load(imagePath);
    if (!surface)
    {
        fprintf(stderr, "Error: Unable to load image %s! SDL_image Error: %s\n", imagePath, IMG_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        fprintf(stderr, "Error: Unable to create texture from %s! SDL Error: %s\n", imagePath, SDL_GetError());
        return;
    }

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}
GameObject::~GameObject()
{
    SDL_DestroyTexture(texture);
}

void GameObject::update()
{
    rect.x += 1;
}

void GameObject::render()
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}