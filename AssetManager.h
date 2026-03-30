#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>

class AssetManager {
public:
    // Konstruktor przyjmuje renderer, bo potrzebujemy go do tworzenia tekstur
    AssetManager(SDL_Renderer* renderer);

    // Destruktor, który automatycznie posprz¹ta ca³¹ pamiêæ przy wy³¹czaniu gry
    ~AssetManager();

    // G³ówna funkcja: podajemy œcie¿kê, a ona zwraca teksturê (³aduj¹c j¹ tylko w razie potrzeby)
    SDL_Texture* GetTexture(const std::string& filePath);

    // Rêczne czyszczenie pamiêci (np. przy zmianie poziomu)
    void Clear();

private:
    SDL_Renderer* renderer;
    // Nasz "s³ownik" przechowuj¹cy za³adowane ju¿ grafiki
    std::unordered_map<std::string, SDL_Texture*> textures;
};
