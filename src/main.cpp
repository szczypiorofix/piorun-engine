#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "AssetManager.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);

    try {
        lua.script_file("config.lua");
    }
    catch (const sol::error& e) {
        std::cerr << "Lua script error: " << e.what() << std::endl;
        return 1;
    }

    float startSpeed = lua["PlayerConfig"]["speed"];
    std::string playerName = lua["PlayerConfig"]["name"];

    std::cout << "Starting as: " << playerName << " with speed: " << startSpeed << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 1;

    SDL_Window* window = SDL_CreateWindow("PiorunEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    AssetManager assetManager(renderer);

    SDL_Texture* playerTex = assetManager.GetTexture("player.png");

    Player player(playerTex, WINDOW_WIDTH / 2.0f - 32.0f, WINDOW_HEIGHT / 2.0f - 32.0f, &lua);

    Uint64 lastTime = SDL_GetTicks64();
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        Uint64 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
        }

        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
        player.Update(deltaTime, keyboardState);

        SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
        SDL_RenderClear(renderer);

        player.Render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}