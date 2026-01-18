#include "matrix.h"
#include <iostream>
#include <fstream>

Matrix::Matrix(int n, int m, char bg)
    : rows(n), cols(m), background(bg),
    data(n, std::vector<char>(m, bg)) {
}

void Matrix::clear() {
    for (auto& row : data)
        std::fill(row.begin(), row.end(), background);
}

void Matrix::setPixel(int x, int y, char c) {
    if (x >= 0 && x < cols && y >= 0 && y < rows)
        data[y][x] = c;
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (char c : row)
            std::cout << c;
        std::cout << '\n';
    }
}

bool Matrix::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;

    out << rows << " " << cols << "\n";
    for (const auto& row : data) {
        for (char c : row)
            out << c;
        out << "\n";
    }
    return true;
}

bool Matrix::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    in >> rows >> cols;
    in.ignore();

    data.assign(rows, std::vector<char>(cols, background));

    std::string line;
    for (int i = 0; i < rows; ++i) {
        if (!std::getline(in, line)) return false; 
        for (int j = 0; j < cols && j < static_cast<int>(line.size()); ++j) {
            data[i][j] = line[j];
        }
    }

    return true;
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }
