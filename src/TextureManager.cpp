#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer *renderer) : renderer(renderer) {}

TextureManager::~TextureManager()
{
    clean();
}

SDL_Texture *TextureManager::loadTexture(const std::string &filePath)
{
    // Check if the texture is already loaded
    if (textureMap.find(filePath) != textureMap.end())
        return textureMap[filePath];

    // Load the image
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    if (!surface)
        return nullptr;

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_FreeSurface(surface);
        return nullptr;
    }

    SDL_FreeSurface(surface);

    textureMap[filePath] = texture;
    return texture;
}

void TextureManager::clean()
{
    for (auto &entry : textureMap)
        SDL_DestroyTexture(entry.second);

    textureMap.clear();
}