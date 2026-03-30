cmake_minimum_required(VERSION 3.15)
project(PiorunEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

message(STATUS "Downloading SDL2...")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.0
)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Disable static SDL build" FORCE)
FetchContent_MakeAvailable(SDL2)

message(STATUS "Downloading SDL2_image...")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
)

message(STATUS "Downloading Lua...")
FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/TheLartians/Lua.git
)
FetchContent_MakeAvailable(lua)

message(STATUS "Downloading Sol2...")
FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG v3.3.1
)
FetchContent_MakeAvailable(sol2)

set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored dependencies" FORCE)
FetchContent_MakeAvailable(SDL2_image)

message(STATUS "Downloading Lua language...")
FetchContent_Declare(
    lua_sources
    URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
)
FetchContent_MakeAvailable(lua_sources)

file(GLOB LUA_SRC "${lua_sources_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM LUA_SRC "${lua_sources_SOURCE_DIR}/src/lua.c" "${lua_sources_SOURCE_DIR}/src/luac.c")

add_library(lua STATIC ${LUA_SRC})
target_include_directories(lua PUBLIC "${lua_sources_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME} src/main.cpp src/Player.cpp src/AssetManager.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image lua sol2)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2_image::SDL2_image>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
