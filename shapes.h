#pragma once

class Matrix;

void drawLine(Matrix& m,
    int x1, int y1,
    int x2, int y2,
    char symbol);

void drawEllipse(Matrix& m,
    int cx, int cy,
    int rx, int ry,
    char symbol);

void drawRotatedRectangle(Matrix& m,
    int x, int y,
    int width, int height,
    double angleDeg,
    char symbol);
