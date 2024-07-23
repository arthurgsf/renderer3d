#include <iostream>
#include <SDL.h>
#include <vector>

#include "Renderer3D.h"
/* weak perspective projection */
// focal length pode ser interpretado como FOV ?
// cube
std::vector<renderer::Point3D> points {
    renderer::Point3D{-1.0f, -1.0f, -1.0f}, renderer::Point3D{-1.0f, -1.0f, 1.0f},
    renderer::Point3D{1.0f, -1.0f, -1.0f}, renderer::Point3D{-1.0f, 1.0f, -1.0f},
    renderer::Point3D{-1.0f, 1.0f, 1.0f}, renderer::Point3D{1.0f, -1.0f, 1.0f},
    renderer::Point3D{1.0f, 1.0f, -1.0f}, renderer::Point3D{1.0f, 1.0f, 1.0f}
};

std::vector<renderer::Edge> edges {
    renderer::Edge { 0, 1 }, renderer::Edge { 0, 2 }, renderer::Edge { 0, 3 },
    renderer::Edge { 2, 5 }, renderer::Edge { 3, 6 }, renderer::Edge { 3, 4 },
    renderer::Edge { 4, 7 }, renderer::Edge {6, 7 }, renderer::Edge {7, 5 },
    renderer::Edge {5, 1}, renderer::Edge {4, 1}, renderer::Edge{ 2, 6}
};
int main(int argc, char * argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 520, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    renderer::Renderer3D r3d(window, renderer, points, edges);

    while (true) {
        if(SDL_QuitRequested()) break;
        r3d.render();
    }
    // std::vector<SDL_Point>
    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_QUIT;
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
