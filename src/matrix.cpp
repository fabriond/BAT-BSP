#include <string>
#include <iostream>
#include <math.h>
#include "../include/matrix.h"
#include "../include/random_engine.h"

#define PI 3.14159265358979323846

Matrix::Matrix(int numRows, int numCols, bool isRandom, std::pair<int, int> randomLimits): 
    numRows(numRows), 
    numCols(numCols)
{
    for(int i = 0; i < numRows; ++i){
        std::vector<int> colValues;
        for(int j = 0; j < numCols; ++j){
            if(isRandom) colValues.push_back(uniformRandom(randomLimits.first, randomLimits.second));
            else colValues.push_back(0);
        }
        values.push_back(colValues);
    }
}

Matrix Matrix::transpose(){
    Matrix aux(numCols, numRows);
    
    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numCols; ++j){
            aux.setValue(j, i, getValue(i, j));
        }
    }

    return aux;
}

Matrix Matrix::forEach(std::function<int(int)> function){
    Matrix output(numRows, numCols);
    
    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numCols; ++j){
            output.setValue(i, j, function.operator()(getValue(i, j)));
        }
    }

    return output;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    os.precision(6);
    for(int i = 0; i < matrix.numRows; ++i){
        for(int j = 0; j < matrix.numCols; ++j){
            os << std::fixed << matrix.getValue(i, j) << " ";
        }
        os << std::endl;
    }
    
    return os;
}

Matrix operator+(const Matrix& m1, const Matrix& m2){
    
    /*  Returns the elementwise sum of two matrices.
        Inputs: 
            m1: a vector
            m2: a vector
        Output: a vector, sum of the matrices m1 and m2.
    */
    
    Matrix sum(m1.numRows, m1.numCols);
    
    if(m1.numCols != m2.numCols || m1.numRows != m2.numRows){
        throw std::runtime_error("Error in matrix addition, sizes don't match");
    }

    for(int i = 0; i < m1.numRows; ++i){
        for(int j = 0; j < m1.numCols; ++j){
            int v = m1.getValue(i, j) + m2.getValue(i, j);
            sum.setValue(i, j, v);
        }
    }
    
    return sum;
}

Matrix operator-(const Matrix& m1, const Matrix& m2){
    
    /*  Returns the difference between two matrices.
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 - m2, difference between two matrices m1 and m2.
    */
    
    Matrix diff(m1.numRows, m1.numCols);
    
    if(m1.numCols != m2.numCols || m1.numRows != m2.numRows){
        throw std::runtime_error("Error in matrix subtraction, sizes don't match");
    }

    for(int i = 0; i < m1.numRows; ++i){
        for(int j = 0; j < m1.numCols; ++j){
            int v = m1.getValue(i, j) - m2.getValue(i, j);
            diff.setValue(i, j, v);
        }
    }
    
    return diff;
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
    
    /*  Returns the product of two matrices (elementwise multiplication).
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 * m2, product of two matrices m1 and m2
    */
    
    Matrix mult(m1.numRows, m1.numCols);
    
    if(m1.numCols != m2.numCols || m1.numRows != m2.numRows){
        throw std::runtime_error("Error in matrix multiplication, sizes don't match");
    }

    for(int i = 0; i < m1.numRows; ++i){
        for(int j = 0; j < m1.numCols; ++j){
            int v = m1.getValue(i, j) * m2.getValue(i, j);
            mult.setValue(i, j, v);
        }
    }
    
    return mult;
}

Matrix dot(const Matrix& m1, const Matrix& m2){
    
    /*  Returns the product of two matrices: m1 x m2.
        Inputs:
            m1: vector, left matrix of size m1_rows x m1_columns
            m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix 
                must be equal to the number of the columns in the left one)
            m1_rows: int, number of rows in the left matrix m1
            m1_columns: int, number of columns in the left matrix m1
            m2_columns: int, number of columns in the right matrix m2
        Output: vector, m1 * m2, product of two matrices m1 and m2, a matrix of size m1_rows x m2_columns
    */
    
    Matrix output(m1.numRows, m2.numCols);
    
    if(m1.numCols != m2.numRows){
        throw std::runtime_error("Error in matrix dot multiplication, sizes don't match");
    }

    for(int row = 0; row < m1.numRows; ++row) {
        for(int col = 0; col < m2.numCols; ++col) {
            int v = 0;
            for( int k = 0; k < m1.numCols; ++k ) {
                v += m1.getValue(row, k) * m2.getValue(k, col);
            }
            output.setValue(row, col, v);
        }
    }
    
    return output;
}

Matrix::Matrix(int numRows, int numCols, std::vector<int> vals): 
    numRows(numRows), 
    numCols(numCols)
{
    for(int i = 0; i < numRows; ++i){
        std::vector<int> colValues;
        for(int j = 0; j < numCols; ++j){
            colValues.push_back(vals.at(j + i*numCols));
        }
        values.push_back(colValues);
    }
}

std::vector<int> Matrix::toVector(){
    std::vector<int> result;

    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numCols; ++j){
            result.push_back(getValue(i, j));
        }
    }

    return result;
}

void Matrix::placeHexagon(int xCenter, int yCenter, int radius){
    int xPrev = -1;
    int yPrev = -1;
    int xCurrent = -1;
    int yCurrent = -1;

    for(int i = 0; i <= radius; ++i){
        for(double theta = 0.0; theta < 2.0*PI - PI/3.0; theta += PI/3.0){
            xCurrent = xCenter + i*sin(theta);
            yCurrent = yCenter + i*cos(theta);    
            
            //setValue(xCenter + i*sin(theta), yCenter + i*cos(theta), 1);
            if(xPrev != -1 && yPrev != -1){
                drawBresenhamLine(xPrev, yPrev, xCurrent, yCurrent, 1);
            }

            xPrev = xCurrent;
            yPrev = yCurrent;
        }
    }
}

void Matrix::placeCircle(int xCenter, int yCenter, int radius){
    int xPrev = -1;
    int yPrev = -1;
    int xCurrent = -1;
    int yCurrent = -1;

    for(int i = 0; i <= radius; ++i){
        for(double theta = 0.0; theta < 2.0*PI - PI/1000.0; theta += PI/1000.0){
            try{
                setValue(xCenter + i*sin(theta), yCenter + i*cos(theta), 0);
            } catch(const std::exception& e){}
        }
    }
}

void Matrix::drawBresenhamLine(int x1, int y1, int x2, int y2, int value){
    bool swap = false;
    bool flip = false;
    if(abs(y2 - y1) > abs(x2 - x1)) {
        int aux = x1;
        x1 = y1;
        y1 = aux;
        aux = x2;
        x2 = y2;
        y2 = aux;
        swap = true;
    }
    if(x1 > x2) {
        int aux = x1;
        x1 = x2;
        x2 = aux;
        aux = y1;
        y1 = y2;
        y2 = aux;
    }
    if(y1 > y2) {
        y1 = -y1;
        y2 = -y2;
        flip = true;
    }
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = 2 * dy - dx;
    int incE = 2 * dy;
    int incNE = 2 * (dy - dx);
    int x = x1;
    int y = y1;
    try{
        if(swap) 
            if(flip) setValue(-y, x, value);
            else setValue(y, x, value);
        else 
            if(flip) setValue(x, -y, value);
            else setValue(x, y, value);
    } catch(const std::exception& e){
        //std::cout << "Damnit" << std::endl;
    }

    while(x < x2) {
        if(d <= 0) {
            //E
            d += incE;
            x++;
        } else {
            //NE
            d += incNE;
            x++;
            y++;
        }
        try{
            if(swap) 
                if(flip) setValue(-y, x, value);
                else setValue(y, x, value);
            else 
                if(flip) setValue(x, -y, value);
                else setValue(x, y, value);
        } catch(const std::exception& e){
            //std::cout << "Damnit" << std::endl;
        }
    }
}

