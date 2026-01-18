#pragma once
#include <vector>
#include <string>

class Matrix {
private:
    int rows, cols;
    char background;
    std::vector<std::vector<char>> data;

public:
    Matrix(int n, int m, char bg);

    void clear();
    void setPixel(int x, int y, char c);
    void print() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    int getRows() const;
    int getCols() const;
};
