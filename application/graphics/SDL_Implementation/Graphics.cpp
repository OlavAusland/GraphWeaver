#include "Graphics.hpp"
#include "SDL3/SDL.h"

static GraphWeaver::Color active_color;

void GraphWeaver::SetColor(int r, int g, int b, int a = 1)
{
    active_color.r = r;
    active_color.g = g;
    active_color.b = b;
    active_color.a = a;
}

GraphWeaver::Color GraphWeaver::GetActiveColor()
{
    return active_color;
}

void* GraphWeaver::GetActiveRenderer()
{
    return SDL_GetRenderer(SDL_GL_GetCurrentWindow());
}

void GraphWeaver::DrawPoint(double x, double y)
{
    SDL_Renderer* renderer = (SDL_Renderer*)GetActiveRenderer();

    SDL_RenderPoint(renderer, x, y);
}

void GraphWeaver::DrawPoints(void* start, int points)
{
    SDL_Renderer* renderer = (SDL_Renderer*)GetActiveRenderer();
    SDL_SetRenderDrawColor(renderer, active_color.r, active_color.g, active_color.b, active_color.a);
    SDL_RenderPoints(renderer, (const SDL_FPoint*)start, points);
}

void GraphWeaver::DrawLines(void* start, int points)
{
    SDL_Renderer* renderer = (SDL_Renderer*)GetActiveRenderer();
    SDL_SetRenderDrawColor(renderer, active_color.r, active_color.g, active_color.b, active_color.a);
    SDL_RenderLines(renderer, (const SDL_FPoint*)start, points);
}

void GraphWeaver::DrawLine(const Vec3 start, const Vec3 end, const Color color)
{
    SDL_Renderer* renderer = (SDL_Renderer*)GetActiveRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
}

