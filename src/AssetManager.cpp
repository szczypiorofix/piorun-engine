#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager(SDL_Renderer* renderer) : renderer(renderer) {}

AssetManager::~AssetManager() {
    Clear(); // Automatyczne sprz¹tanie przy usuwaniu obiektu
}

SDL_Texture* AssetManager::GetTexture(const std::string& filePath) {
    // 1. Sprawdzamy, czy tekstura jest ju¿ w naszym s³owniku
    auto it = textures.find(filePath);
    if (it != textures.end()) {
        // ZnaleŸliœmy j¹! Zwracamy istniej¹c¹ z pamiêci
        return it->second;
    }

    // 2. Jeœli kod dotar³ tutaj, to znaczy, ¿e tej tekstury jeszcze nie ma. £adujemy j¹ z dysku.
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, filePath.c_str());
    if (newTexture == nullptr) {
        std::cerr << "Blad ladowania tekstury: " << filePath << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // 3. Zapisujemy now¹ teksturê do s³ownika na przysz³oœæ
    textures[filePath] = newTexture;

    // 4. Zwracamy now¹ teksturê
    return newTexture;
}

void AssetManager::Clear() {
    // Przechodzimy przez wszystkie za³adowane tekstury i niszczymy je
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear(); // Opró¿niamy s³ownik
}
