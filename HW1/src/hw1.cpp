#include "hw1.h"

namespace algebra
{
    Matrix zeros(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 0));
    }

    Matrix ones(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 1));
    }

    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (min > max) {
            throw std::logic_error("max must be bigger than min!");
        }
        std::uniform_real_distribution<double> u(min, max);
        std::default_random_engine e;
        Matrix matrix;
        for (unsigned i = 0; i < n; ++i) {
            std::vector<double> v;
            v.reserve(m);
            for (unsigned j = 0; j < m; ++j) {
                v.push_back(u(e));
            }
            matrix.push_back(v);
        }
        return matrix;
    }

    void show(const Matrix& matrix)
    {
        for (std::vector<double> v: matrix) {
            std::cout << '[';
            for (double d: v) {
                std::cout << std::setiosflags(std::ios::left) << std::setprecision(3) << std::setw(7) << d;
            }
            std::cout << ']' << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c)
    {
        if (matrix.empty()) {
            throw std::logic_error("The matrix to be multipied is empty!");
        }
        Matrix new_matrix;
        for (Matrix::const_iterator it = matrix.cbegin(); it < matrix.cend(); ++it) {
            std::vector<double> v;
            v.reserve((*it).size());
            for (std::vector<double>::const_iterator iit = (*it).cbegin(); iit < (*it).cend(); ++iit) {
                v.push_back(c * (*iit));
            }
            new_matrix.push_back(v);
        }
        return new_matrix;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() || matrix2.empty()) {
            Matrix empty_matrix;
            return empty_matrix;
        }
        // Specify the shape of the product matrix.
        // Since neither matrix1 nor matrix2 is empty, we can specify n through matrix1 and m through matrix2. 
        const unsigned n = matrix1.size(), m = matrix2[0].size(), k = matrix1[0].size();
        if (matrix1[0].size() != matrix2.size()) {
            throw std::logic_error("Shape of the two matrices don't match!");
        }
        Matrix new_matrix = zeros(n, m);
        for (unsigned i = 0; i < n; ++i) {
            for (unsigned l = 0; l < k; ++l) {
                double s = matrix1[i][l];
                for (unsigned j = 0; j < m; ++j) {
                    new_matrix[i][j] += s * matrix2[l][j];
                }
            }
        }
        return new_matrix;
    }

    Matrix sum(const Matrix& matrix, double c)
    {
        if (matrix.empty() || matrix[0].empty()) {
            Matrix emptyMatrix;
            return emptyMatrix;
        }

        Matrix newMatrix(matrix);
        for (Matrix::iterator it = newMatrix.begin(); it < newMatrix.end(); ++it) {
            for (std::vector<double>::iterator iit = (*it).begin(); iit < (*it).end(); ++iit) {
                *iit += c;
            }
        }
        return newMatrix;
   }

   Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
   {
        bool matrix1IsEmpty = matrix1.empty() || matrix1[0].empty();
        bool matrix2IsEmpty = matrix2.empty() || matrix2[0].empty();
        if (matrix1IsEmpty && matrix2IsEmpty) {
            // Both matrix1 and matrix2 are empty.
            Matrix emptyMatrix;
            return emptyMatrix;
        }
        else if (matrix1IsEmpty || matrix2IsEmpty) {
            throw std::logic_error("One of the 2 matrices is empty!");
        }

        const unsigned n1 = matrix1.size(), m1 = matrix1[0].size(), n2 = matrix2.size(), m2 = matrix2[0].size();
        if (n1 == n2 && m1 == m2) {
            Matrix newMatrix(matrix1);
            for (unsigned i = 0; i < n1; ++i) {
                for (unsigned j = 0; j < m1; ++j) {
                    newMatrix[i][j] += matrix2[i][j];
                }
            }
            return newMatrix;
        }
        else {
            throw std::logic_error("Sizes of the two matrices do not match!");
        }
    }

    Matrix transpose(const Matrix& matrix)
    {
        if (matrix.empty() || matrix[0].empty()) {
            Matrix emptyMatrix;
            return emptyMatrix;
        }

        const unsigned n = matrix.size(), m = matrix[0].size();
        Matrix newMatrix = zeros(m, n);
        for (unsigned i = 0; i < m; ++i) {
            for (unsigned j = 0; j < n; ++j) {
                newMatrix[i][j] = matrix[j][i];
            }
        }
        return newMatrix;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m)
    {
        if (matrix.empty() || matrix[0].empty()) {
            Matrix emptyMatrix;
            return emptyMatrix;
        } 

        const unsigned N = matrix.size(), M = matrix[0].size();
        if (n >= N || m >= M) {
            throw std::logic_error("Index out of range!");
        }

        Matrix newMatrix(matrix);
        unsigned i = 0;
        Matrix::iterator it = newMatrix.begin();
        it += n;
        newMatrix.erase(it);
        for (i = 0; i < N - 1; ++i) {
            std::vector<double>::iterator iit = newMatrix[i].begin();
            iit += m;
            newMatrix[i].erase(iit);
        }
        return newMatrix;
    }

    double determinant(const Matrix& matrix)
    {
        if (matrix.empty() || matrix[0].empty()) {
            return 1;
        }

        const unsigned n = matrix.size(), m = matrix[0].size();
        if (n != m) {
            throw std::logic_error("The matrix is not a square matrix!");
        }

        if (n == 1) {
            return matrix[0][0];
        }

        double det = 0;
        for (unsigned i = 0; i < n; ++i) {
            Matrix minorMatrix = minor(matrix, i, 0);
            if (i % 2 != 0) {
                det += (-1) * matrix[i][0] * determinant(minorMatrix);
            }
            else {
                det += matrix[i][0] * determinant(minorMatrix);
            }
        }
        return det;
    }

    Matrix inverse(const Matrix& matrix)
    {
        if (matrix.empty() || matrix[0].empty()) {
            Matrix emptyMatrix;
            return emptyMatrix;
        }
        
        const unsigned n = matrix.size(), m = matrix[0].size();
        if (n != m) {
            throw std::logic_error("Non-square matrix is not inversible!");
        }

        double det = determinant(matrix);
        if (det == 0) {
            throw std::logic_error("This matrix is not inversible!");
        }

        Matrix adjugateMatrix = zeros(n, n);
        for (unsigned i = 0; i < n; ++i) {
            for (unsigned j = 0; j < n; ++j) {
                if ((i + j) % 2 == 0) {
                    adjugateMatrix[j][i] = determinant(minor(matrix, i, j));
                }
                else {
                    adjugateMatrix[j][i] = (-1) * determinant(minor(matrix, i, j));
                }

            }
        }

        Matrix inverseMatrix = multiply(adjugateMatrix, 1 / det);
        return inverseMatrix;

    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
    {
        bool matrix1IsEmpty = matrix1.empty() || matrix1[0].empty();
        bool matrix2IsEmpty = matrix2.empty() || matrix2[0].empty();

        if (matrix1IsEmpty || matrix2IsEmpty) {
            throw std::logic_error("Cannot concatenate an empty matrix!");
        }

        const unsigned n1 = matrix1.size(), m1 = matrix1[0].size(), n2 = matrix2.size(), m2 = matrix2[0].size();
        Matrix newMatrix(matrix1);
        if (axis == 0) {
            if (m1 != m2) {
                throw std::logic_error("Shapes of the matrices do not match!");
            }

            newMatrix.insert(newMatrix.cend(), matrix2.cbegin(), matrix2.cend());
        }
        else if (axis == 1) {
            if (n1 != n2) {
                throw std::logic_error("Shapes of the matrices do not match!");
            }

            for (unsigned i = 0; i < n1; ++i) {
                newMatrix[i].insert(newMatrix[i].cend(), matrix2[i].cbegin(), matrix2[i].cend());
            }
        }

        return newMatrix;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2)
    {
        if (matrix.empty() || matrix[0].empty()) {
            throw std::logic_error("Empty matrix");
        }

        const unsigned n = matrix.size();
        if (r1 >= n || r2 >= n) {
            throw std::logic_error("Index out of range");
        }

        Matrix newMatrix(matrix);
        newMatrix[r1].swap(newMatrix[r2]);
        return newMatrix;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c)
    {
        if (matrix.empty() || matrix[0].empty()) {
            throw std::logic_error("Empty matrix");
        }

        const unsigned n = matrix.size(), m = matrix[0].size();
        if (r >= n) {
            throw std::logic_error("Index out of range!");
        }

        Matrix newMatrix(matrix);
        for (unsigned i = 0; i < m; ++i) {
            newMatrix[r][i] *= c;
        }

        return newMatrix;
         
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
    {
        if (matrix.empty() || matrix[0].empty()) {
            throw std::logic_error("Empty matrix");
        }

        const unsigned n = matrix.size(), m = matrix[0].size();
        if (r1 >= n || r2 >= n) {
            throw std::logic_error("Index out of range");
        }

        Matrix newMatrix(matrix);
        Matrix multipliedMatrix = ero_multiply(newMatrix, r1, c);
        for (unsigned i = 0; i < m; ++i) {
            newMatrix[r2][i] += multipliedMatrix[r1][i];
        }

        return newMatrix;
    }

    Matrix upper_triangular(const Matrix& matrix)
    {
        if (matrix.empty() || matrix[0].empty()) {
            Matrix emptyMatrix;
            return emptyMatrix;
        }

        const unsigned n = matrix.size(), m = matrix[0].size();
        if (n != m) {
            throw std::logic_error("Non-square matrix does not have upper triangular form!");
        }

        Matrix newMatrix(matrix);
        for (unsigned i = 0; i < m - 1; ++i) {
            double e = newMatrix[i][i];
            if (e == 0) {
                bool allZeroesColumn = true;
                for (unsigned k = i + 1; k < n; ++k) {
                    if (newMatrix[k][i] != 0) {
                        newMatrix = ero_swap(newMatrix, i, k);
                        e = newMatrix[i][i];
                        allZeroesColumn = false;
                        break;
                    }
                }
                if (allZeroesColumn) {
                    throw std::logic_error("One of the columns is all-zero!");
                }
                
            }
            for (unsigned j = i + 1; j < n; ++j) {
                double factor = (-1) * newMatrix[j][i] / e;
                newMatrix = ero_sum(newMatrix, i, factor, j);
            }
        }

        return newMatrix;
    }
}