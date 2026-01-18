#include <iostream>
#include <string>
#include <cstdlib>

#include "matrix.h"
#include "shapes.h"

void printUsage(const char* progName) {
    std::cout << "Usage:\n";
    std::cout << "  " << progName << " N M line x1 y1 x2 y2 [background] [symbol]\n";
    std::cout << "  " << progName << " N M ellipse cx cy rx ry [background] [symbol]\n";
    std::cout << "  " << progName << " N M rect x1 y1 x2 y2 [angle] [background] [symbol]\n";
    std::cout << "  " << progName << " load <filename>\n";
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string firstArg = argv[1];

    if (firstArg == "load") {
        if (argc < 3) {
            std::cerr << "Error: missing filename for loading.\n";
            printUsage(argv[0]);
            return 1;
        }

        std::string filename = argv[2];
        Matrix matrix(1, 1, '.'); 
        if (matrix.loadFromFile(filename)) {
            std::cout << "Matrix loaded from " << filename << ":\n";
            matrix.print();
        }
        else {
            std::cerr << "Failed to load matrix from " << filename << "\n";
            return 1;
        }

        return 0;
    }

    if (argc < 4) {
        printUsage(argv[0]);
        return 1;
    }

    int N = std::stoi(argv[1]);
    int M = std::stoi(argv[2]);
    std::string shape = argv[3];

    char background = '.';
    char symbol = '#';
    double angle = 0.0;

    if (shape == "rect" && argc >= 9 + 1) {
        if (argc >= 9) angle = std::stod(argv[8]);
        if (argc >= 10) background = argv[9][0];
        if (argc >= 11) symbol = argv[10][0];
    }
    else {
        if (argc >= 8) background = argv[7][0];
        if (argc >= 9) symbol = argv[8][0];
    }

    Matrix matrix(N, M, background);

    try {
        if (shape == "line") {
            if (argc < 8) { std::cerr << "Line requires 4 coordinates.\n"; printUsage(argv[0]); return 1; }
            int x1 = std::stoi(argv[4]);
            int y1 = std::stoi(argv[5]);
            int x2 = std::stoi(argv[6]);
            int y2 = std::stoi(argv[7]);
            drawLine(matrix, x1, y1, x2, y2, symbol);

        }
        else if (shape == "ellipse") {
            if (argc < 8) { std::cerr << "Ellipse requires 4 parameters.\n"; printUsage(argv[0]); return 1; }
            int cx = std::stoi(argv[4]);
            int cy = std::stoi(argv[5]);
            int rx = std::stoi(argv[6]);
            int ry = std::stoi(argv[7]);
            drawEllipse(matrix, cx, cy, rx, ry, symbol);

        }
        else if (shape == "rect") {
            if (argc < 8) { std::cerr << "Rectangle requires 4 coordinates.\n"; printUsage(argv[0]); return 1; }
            int x1 = std::stoi(argv[4]);
            int y1 = std::stoi(argv[5]);
            int x2 = std::stoi(argv[6]);
            int y2 = std::stoi(argv[7]);

            int cx = (x1 + x2) / 2;
            int cy = (y1 + y2) / 2;
            int width = std::abs(x2 - x1);
            int height = std::abs(y2 - y1);

            drawRotatedRectangle(matrix, cx, cy, width, height, angle, symbol);

        }
        else {
            std::cerr << "Unknown shape: " << shape << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: invalid arguments.\n";
        return 1;
    }

    matrix.print();
    if (matrix.saveToFile("matrix.txt"))
        std::cout << "Matrix saved to matrix.txt\n";
    else
        std::cerr << "Failed to save matrix to file.\n";

    return 0;
}
