#pragma once
#include <SDL.h>
#include <SDL_image.h> // NOWE: Nag³ówek dla obrazków
#include <string>
#include <sol/sol.hpp>

class Player {
public:
    // NOWE: Przekazujemy renderer i œcie¿kê do obrazka
    Player(SDL_Texture* texture, float startX, float startY, sol::state* lua);
    ~Player(); // NOWE: Destruktor, aby usun¹æ teksturê z pamiêci!

    void Update(float deltaTime, const Uint8* keyboardState);
    void Render(SDL_Renderer* renderer);

private:
    sol::state* lua;
    float x, y;
    float speed;
    int size;
    SDL_Texture* texture; // NOWE: WskaŸnik na nasz¹ grafikê
};
