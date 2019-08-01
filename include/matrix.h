#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <utility>
#include <functional>

class Matrix{
public:
    Matrix(int numRows, int numCols, bool isRandom = false, std::pair<int, int> randomLimits = {0, 1});
    Matrix(int numRows, int numCols, std::vector<int> vals);
    Matrix transpose();
    Matrix forEach(std::function<int(int)> function);
    std::vector<int> toVector();
    void placeHexagon(int xCenter, int yCenter, int radius);
    void placeCircle(int xCenter, int yCenter, int radius);
    void setValue(int r, int c, int v){values.at(r).at(c) = v;}
    int getValue(int r, int c) const {return values.at(r).at(c);}
    int getNumRows(){return numRows;}
    int getNumCols(){return numCols;}
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend Matrix dot(const Matrix& m1, const Matrix& m2);

private:
    int numRows, numCols;
    std::vector<std::vector<int> > values;

    void drawBresenhamLine(int x1, int y1, int x2, int y2, int value);
};

#endif