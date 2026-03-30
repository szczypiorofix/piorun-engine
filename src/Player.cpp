#include "Player.h"
#include <iostream>

Player::Player(SDL_Texture* playerTexture, float startX, float startY, sol::state* luaState) {
    x = startX;
    y = startY;
    speed = 300.0f;
    size = 64;
    texture = playerTexture;
    lua = luaState;
}

Player::~Player() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Player::Update(float deltaTime, const Uint8* keyboardState) {
    float startSpeed = (*lua)["PlayerConfig"]["speed"];

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

    sol::tie(this->x, this->y) = (*lua)["update_player"](
        this->x, this->y, startSpeed, deltaTime,
        up, down, left, right,
        screenWidth, screenHeight
    );
}

void Player::Render(SDL_Renderer* renderer) {
    if (texture != nullptr) {
        SDL_Rect destRect = { static_cast<int>(x), static_cast<int>(y), size, size };

        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
}
