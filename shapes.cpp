#include "shapes.h"
#include "matrix.h"

#include <cmath>
#include <cstdlib>

void drawLine(Matrix& m,
    int x1, int y1,
    int x2, int y2,
    char symbol)
{
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        m.setPixel(x1, y1, symbol);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void drawEllipse(Matrix& m,
    int cx, int cy,
    int rx, int ry,
    char symbol)
{
    const double step = 0.01;

    for (double angle = 0.0; angle < 2.0 * 3.14; angle += step) {
        int x = cx + static_cast<int>(rx * std::cos(angle));
        int y = cy + static_cast<int>(ry * std::sin(angle));
        m.setPixel(x, y, symbol);
    }
}

void drawRotatedRectangle(Matrix& m,
    int x, int y,
    int width, int height,
    double angleDeg,
    char symbol)
{
    double angleRad = angleDeg * 3.14 / 180.0;

    double cx = x + width / 2.0;
    double cy = y + height / 2.0;

    for (int i = -width / 2; i <= width / 2; ++i) {
        for (int j = -height / 2; j <= height / 2; ++j) {

            // Формулы поворота точки
            int xr = static_cast<int>(
                cx + i * std::cos(angleRad) - j * std::sin(angleRad)
                );
            int yr = static_cast<int>(
                cy + i * std::sin(angleRad) + j * std::cos(angleRad)
                );

            m.setPixel(xr, yr, symbol);
        }
    }
}
