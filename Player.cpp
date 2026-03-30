#include "Player.h"
#include <iostream>

Player::Player(SDL_Texture* playerTexture, float startX, float startY) {
    x = startX;
    y = startY;
    speed = 300.0f;
    size = 64;
    texture = playerTexture; // Po prostu przypisujemy wskaŸnik
}

// NOWE: Kiedy gracz jest niszczony, zwalniamy pamiêæ karty graficznej
Player::~Player() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Player::Update(float deltaTime, const Uint8* keyboardState) {
    if (keyboardState[SDL_SCANCODE_UP])    y -= speed * deltaTime;
    if (keyboardState[SDL_SCANCODE_DOWN])  y += speed * deltaTime;
    if (keyboardState[SDL_SCANCODE_LEFT])  x -= speed * deltaTime;
    if (keyboardState[SDL_SCANCODE_RIGHT]) x += speed * deltaTime;
}

void Player::Render(SDL_Renderer* renderer) {
    if (texture != nullptr) {
        // Obliczamy docelowy prostok¹t
        SDL_Rect destRect = { static_cast<int>(x), static_cast<int>(y), size, size };

        // NOWE: Rysujemy teksturê zamiast kolorowego prostok¹ta!
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
}
