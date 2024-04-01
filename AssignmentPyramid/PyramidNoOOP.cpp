#include <iostream>
#include "PyramidNoOOp.h"
#include <vector>
#include <chrono>
#include <SDL.h>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

int WindowSizeX;
int WindowSizeY;
SDL_Renderer* renderer;
float DeltaTime = 0;
float FL = 5;

std::vector<Point3D> points2{
    Point3D{ 0, 1, 0 },    // Top point
    Point3D{ -1, -1, 1 },  // Front left bottom
    Point3D{ 1, -1, 1 },   // Front right bottom
    Point3D{ 1, -1, -1 },  // Back right bottom
    Point3D{ -1, -1, -1 }  // Back left bottom
};

std::vector<Edge> edges2{
    Edge{ 0, 1 },  // Top to front left
    Edge{ 0, 2 },  // Top to front right
    Edge{ 0, 3 },  // Top to back right
    Edge{ 0, 4 },  // Top to back left
    Edge{ 1, 2 },  // Front left to front right
    Edge{ 2, 3 },  // Front right to back right
    Edge{ 3, 4 },  // Back right to back left
    Edge{ 4, 1 }   // Back left to front left
};

Point2D projection2(Point3D point)
{
    return Point2D{ WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 100, WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 100 };
}

void render2(std::vector<Point3D> points, std::vector<Edge> edges)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    //rotation += 1 * DeltaTime;

    for (auto& edge : edges) {
        Point2D start = projection2(points[edge.start]);
        Point2D end = projection2(points[edge.end]);

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    SDL_Window* window;

    window = SDL_CreateWindow("Pyramid Renderer No OOP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);

    bool running = true;

    while (running)
    {
        if (SDL_QuitRequested()) { running = false; break; }

        render2(points2, edges2);
    }

    return 0;
}

