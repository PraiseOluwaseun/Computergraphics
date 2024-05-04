#include "Renderer3D.h"
#include "Pyramid.h"
#include <iostream>
#include <vector>
#include <SDL.h>

std::vector<Point3D> points{
    Point3D{ 0, 1, 0 },
    Point3D{ -1, -1, 1 },
    Point3D{ 1, -1, 1 },
    Point3D{ 1, -1, -1 },
    Point3D{ -1, -1, -1 }
};

std::vector<Edge> edges{
    Edge{ 0, 1 },
    Edge{ 0, 2 },
    Edge{ 0, 3 },
    Edge{ 0, 4 },
    Edge{ 1, 2 },
    Edge{ 2, 3 },
    Edge{ 3, 4 },
    Edge{ 4, 1 }
};

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    Renderer3D render3D(window, renderer, points, edges);

    double scale = 1.0;
    double scaleStep = 0.01;

    while (running)
    {
        if (SDL_QuitRequested()) { running = false; break; }

        scale += scaleStep;
        if (scale > 1.5) {
            scaleStep = -0.01;
        }
        if (scale < 0.5) {
            scaleStep = 0.01;
        }

        std::vector<Point3D> scaledPoints = points;
        for (auto& point : scaledPoints) {
            point.x *= scale;
            point.y *= scale;
            point.z *= scale;
        }

        render3D.setPoints(scaledPoints);
        render3D.render();
    }

    return 0;
}

