//
// Created by arx on 19/07/2024.
//

#ifndef RENDERER3D_H
#define RENDERER3D_H
#include <SDL.h>
#include <vector>
#include <chrono>
#include <cmath>

namespace renderer {

    struct Point2D { float x, y;};
    struct Point3D { float x, y, z;};
    struct Edge { int from, to;};

    class Renderer3D {
    public:
        Renderer3D(SDL_Window * _window, SDL_Renderer * _renderer, const std::vector<Point3D>& _points,
            const std::vector<Edge>& _edges);
        void render();
    private:
        Point3D rotateX(Point3D point);
        Point3D rotateY(Point3D point);
        Point2D projection(Point3D point);

        float rotation = 0.0f;
        float FOV = 10.0f;
        float dt = 0.0f;

        int WindowSizeX;
        int WindowSizeY;
        SDL_Renderer * renderer;

        std::vector<Point3D> points;
        std::vector<Edge> edges;
    };

} // renderer

#endif //RENDERER3D_H
