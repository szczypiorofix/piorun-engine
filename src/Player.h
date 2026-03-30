#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sol/sol.hpp>

class Player {
public:
    Player(SDL_Texture* texture, float startX, float startY, sol::state* lua);
    ~Player();

    void Update(float deltaTime, const Uint8* keyboardState);
    void Render(SDL_Renderer* renderer);

private:
    sol::state* lua;
    float x, y;
    float speed;
    int size;
    SDL_Texture* texture;
};
