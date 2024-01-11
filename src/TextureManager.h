#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager();

    // Load texture from file
    SDL_Texture* loadTexture(const std::string &filePath);

    // Clean up resources
    void clean();

private:
    SDL_Renderer *renderer;
    std::unordered_map<std::string, SDL_Texture*> textureMap;
};