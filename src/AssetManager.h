#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>

class AssetManager {
public:
    AssetManager(SDL_Renderer* renderer);

    ~AssetManager();

    SDL_Texture* GetTexture(const std::string& filePath);

    void Clear();

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;
};
