#include "Renderer3D.h"
#include "Pyramid.h"
#include <iostream>
#include <vector>
#include <SDL.h>

std::vector<Point3D> points{
    Point3D{ 0, 1, 0 },    // Top point
    Point3D{ -1, -1, 1 },  // Front left bottom
    Point3D{ 1, -1, 1 },   // Front right bottom
    Point3D{ 1, -1, -1 },  // Back right bottom
    Point3D{ -1, -1, -1 }  // Back left bottom
};

std::vector<Edge> edges{
    Edge{ 0, 1 },  // Top to front left
    Edge{ 0, 2 },  // Top to front right
    Edge{ 0, 3 },  // Top to back right
    Edge{ 0, 4 },  // Top to back left
    Edge{ 1, 2 },  // Front left to front right
    Edge{ 2, 3 },  // Front right to back right
    Edge{ 3, 4 },  // Back right to back left
    Edge{ 4, 1 }   // Back left to front left
};

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    Renderer3D render3D(window, renderer, points, edges);

    while (running)
    {
        if (SDL_QuitRequested()) { running = false; break; }

        render3D.render();
    }

    return 0;
}

