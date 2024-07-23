//
// Created by arx on 19/07/2024.
//

#include "Renderer3D.h"


namespace renderer {
    Renderer3D::Renderer3D(SDL_Window * _window, SDL_Renderer * _renderer, const std::vector<Point3D> & _points, const std::vector<Edge> & _edges) {
        SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
        renderer = _renderer;
        points = _points;
        edges = _edges;
    }

    void Renderer3D::render() {
        auto time1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration(0);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        rotation += 1 * dt;

        for (auto &[from, to]: edges) {
            const Point3D rotatedStartPoint = rotateX(rotateY(points[from]));
            const Point3D rotatedEndPoint = rotateX(rotateY(points[to]));
            Point2D start = projection(rotatedStartPoint);
            Point2D end = projection(rotatedEndPoint);

            SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
        }
        SDL_RenderPresent(renderer);

        auto time2 = std::chrono::high_resolution_clock::now();
        duration = time2 - time1;
        dt = duration.count();
        time1 = time2;
    }

    Point3D Renderer3D::rotateX(Point3D point) {
        Point3D ret;
        ret.x = point.x;
        ret.y = cos(rotation) * point.y - sin(rotation) * point.z;
        ret.z = sin(rotation) * point.y + cos(rotation) * point.z;
        return ret;
    }

    Point3D Renderer3D::rotateY(Point3D point) {
        Point3D ret;
        ret.x = cos(rotation) * point.x - sin(rotation) * point.z;
        ret.y = point.y;
        ret.z = sin(rotation) * point.x + cos(rotation) * point.z;
        return ret;
    }

    Point2D Renderer3D::projection(Point3D point) {
        return Point2D{
            WindowSizeX/2 + (FOV * point.x)/(FOV + point.z) * 100,
            WindowSizeY/2 + (FOV * point.y)/(FOV + point.z) * 100
        };
    }

} // renderer