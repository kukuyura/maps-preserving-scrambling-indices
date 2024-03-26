#pragma once

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <math.h>

class BoolMatrix {
public:
    BoolMatrix(int n) : n(n), a(n, std::vector<bool>(n, false)) {}

    BoolMatrix operator+(const BoolMatrix &other) const {
        assert(n == other.n);
        BoolMatrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result.a[i][j] = a[i][j] ^ other.a[i][j];
            }
        }
        return result;
    }

    BoolMatrix operator*(const BoolMatrix &other) const {
        assert(n == other.n);
        BoolMatrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    result.a[i][j] = result.a[i][j] || (a[i][k] && other.a[k][j]);
                }
            }
        }
        return result;
    }

    BoolMatrix pow(int n) const {
        BoolMatrix result(n);
        BoolMatrix base = *this;
        for (int i = 0; i < n; i++) {
            result.a[i][i] = true; // единичная матрица
        }
        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n /= 2;
        }
        return result;
    }

    bool is_scramble() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                bool ort = true;
                for (int k = 0; k < n; ++k) {
                    if (a[i][k] && a[j][k]) {
                        ort = false;
                        break;
                    }
                }
                if (ort) {
                    return false;
                }
            }
        }
        return true;
    }

    int scrambling_index(int bound = 0) const {
        const int th_bound = (n - 1) * (n - 1) + 1;

        bound = std::min(bound, th_bound);
        if (bound <= 0) {
            bound = th_bound;
        }

        BoolMatrix base = *this;
        BoolMatrix power = base;
        for (int i = 1; i <= bound; ++i) {
            if (power.is_scramble()) {
                return i;
            } 
            power = power * base;
        }
        return 0;
    }

    BoolMatrix apply_perm(const std::vector<int>& perm) const {
        assert(n * n == perm.size());
        BoolMatrix res(n);
        for (int i = 0; i < n * n; ++i) { 
            res.a[perm[i] / n][perm[i] % n] = a[i / n][i % n];
        }
        return res;
    }

    int number_of_edges() const {
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ret += (int)a[i][j];
            }
        }
        return ret;
    }

    void print() const {
        for (const auto &row : a) {
            for (bool val : row) {
                std::cout << static_cast<int>(val) << " ";
            }
            std::cout << "\n";
        }
    }

public:
    std::vector<std::vector<bool>> a;
    int n;
};

// Функция для генерации всех булевых матриц заданного размера
std::vector<BoolMatrix> generateAllBoolMatrices(int n) {
    int total_matrices = 1 << (n * n);
    std::vector<BoolMatrix> matrices;
    for (int i = 0; i < total_matrices; i++) {
        BoolMatrix matrix(n);
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                matrix.a[row][col] = (i >> (row * n + col)) & 1;
            }
        }
        matrices.push_back(matrix);
    }
    return matrices;
}