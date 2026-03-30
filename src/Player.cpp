#include "Player.h"
#include <iostream>

Player::Player(SDL_Texture* playerTexture, float startX, float startY, sol::state* lua) {
    x = startX;
    y = startY;
    speed = 300.0f;
    size = 64;
    texture = playerTexture; // Po prostu przypisujemy wskaŸnik
    this->lua = lua;
}

// NOWE: Kiedy gracz jest niszczony, zwalniamy pamiêæ karty graficznej
Player::~Player() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Player::Update(float deltaTime, const Uint8* keyboardState) {
    float startSpeed = this->lua["PlayerConfig"]["speed"];

    float screenWidth = 800.0f;
    float screenHeight = 600.0f;

    //if (keyboardState[SDL_SCANCODE_UP])    y -= speed * deltaTime;
    //if (keyboardState[SDL_SCANCODE_DOWN])  y += speed * deltaTime;
    //if (keyboardState[SDL_SCANCODE_LEFT])  x -= speed * deltaTime;
    //if (keyboardState[SDL_SCANCODE_RIGHT]) x += speed * deltaTime;

    bool up = keyboardState[SDL_SCANCODE_UP];
    bool down = keyboardState[SDL_SCANCODE_DOWN];
    bool left = keyboardState[SDL_SCANCODE_LEFT];
    bool right = keyboardState[SDL_SCANCODE_RIGHT];

    //sol::tie(this->x, this->y) = this->lua["update_player"](
    //    this->x, this->y, startSpeed, dt,
    //    up, down, left, right,
    //    screenWidth, screenHeight
    //);
}

void Player::Render(SDL_Renderer* renderer) {
    if (texture != nullptr) {
        // Obliczamy docelowy prostok¹t
        SDL_Rect destRect = { static_cast<int>(x), static_cast<int>(y), size, size };

        // NOWE: Rysujemy teksturê zamiast kolorowego prostok¹ta!
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
}
