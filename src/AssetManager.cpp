#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager(SDL_Renderer* renderer) : renderer(renderer) {}

AssetManager::~AssetManager() {
    Clear();
}

SDL_Texture* AssetManager::GetTexture(const std::string& filePath) {
    auto it = textures.find(filePath);
    if (it != textures.end()) {
        return it->second;
    }

    SDL_Texture* newTexture = IMG_LoadTexture(renderer, filePath.c_str());
    if (newTexture == nullptr) {
        std::cerr << "Texture loading error: " << filePath << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }

    textures[filePath] = newTexture;

    return newTexture;
}

void AssetManager::Clear() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}
