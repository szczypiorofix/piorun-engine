cmake_minimum_required(VERSION 3.15)
project(PiorunEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# --- KONFIGURACJA SDL2 ---
message(STATUS "Pobieranie biblioteki SDL2...")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.0
)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Disable static SDL build" FORCE)
FetchContent_MakeAvailable(SDL2)

# --- KONFIGURACJA SDL_image (NOWE) ---
message(STATUS "Pobieranie biblioteki SDL2_image...")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2 # Wersja kompatybilna z SDL2
)

# --- KONFIGURACJA LUA (U¿ywamy portu z gotowym CMakeLists) ---
message(STATUS "Pobieranie jezyka Lua...")
FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/TheLartians/Lua.git
    # GIT_TAG v5.4.4
)
FetchContent_MakeAvailable(lua)

# --- KONFIGURACJA SOL2 (Most miêdzy C++ a Lua) ---
message(STATUS "Pobieranie Sol2...")
FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG v3.3.1
)
FetchContent_MakeAvailable(sol2)

# Wymuszamy u¿ycie wbudowanych bibliotek (np. libpng) dla u³atwienia
set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored dependencies" FORCE)
FetchContent_MakeAvailable(SDL2_image)

message(STATUS "Pobieranie oficjalnego kodu Lua...")
FetchContent_Declare(
    lua_sources
    URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
)
FetchContent_MakeAvailable(lua_sources)

# Zbieramy wszystkie pliki .c z serca jêzyka Lua
file(GLOB LUA_SRC "${lua_sources_SOURCE_DIR}/src/*.c")
# Wyrzucamy pliki wykonywalne (które maj¹ w³asne main()), bo zepsu³yby nasz¹ grê
list(REMOVE_ITEM LUA_SRC "${lua_sources_SOURCE_DIR}/src/lua.c" "${lua_sources_SOURCE_DIR}/src/luac.c")

# Tworzymy absolutnie pewn¹, nasz¹ w³asn¹ bibliotekê o nazwie 'lua'
add_library(lua STATIC ${LUA_SRC})
target_include_directories(lua PUBLIC "${lua_sources_SOURCE_DIR}/src")

# --- KONFIGURACJA NASZEJ GRY ---
add_executable(${PROJECT_NAME} src/main.cpp src/Player.cpp src/AssetManager.cpp)

# Podpinamy now¹ bibliotekê (NOWE)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image lua sol2)

# --- AUTOMATYCZNE KOPIOWANIE DLL ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Kopiowanie DLL z SDL_image (NOWE)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2_image::SDL2_image>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
