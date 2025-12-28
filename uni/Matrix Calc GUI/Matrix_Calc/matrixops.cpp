#include "matrixops.h"
#include <cmath>    // std::fabs

// ----------------- small helpers -----------------
static double** allocMatrix(int r, int c) {
    auto M = new double*[r];
    for (int i = 0; i < r; ++i) M[i] = new double[c]{};
    return M;
}
static void freeMatrix(double** M, int r) {
    if (!M) return;
    for (int i = 0; i < r; ++i) delete[] M[i];
    delete[] M;
}
static double** makeSubMatrix(const double* const* m, int r, int c, int rpos, int cpos) {
    // build (r-1) x (c-1) by skipping row rpos and col cpos
    auto sub = allocMatrix(r - 1, c - 1);
    int rr = 0;
    for (int i = 0; i < r; ++i) {
        if (i == rpos) continue;
        int cc = 0;
        for (int j = 0; j < c; ++j) {
            if (j == cpos) continue;
            sub[rr][cc++] = m[i][j];
        }
        ++rr;
    }
    return sub;
}

// ----------------- operations -----------------
double** addMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2) {
    if (r1 != r2 || c1 != c2) return nullptr;
    auto res = allocMatrix(r1, c1);
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}

double** subtractMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2) {
    if (r1 != r2 || c1 != c2) return nullptr;
    auto res = allocMatrix(r1, c1);
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j)
            res[i][j] = a[i][j] - b[i][j];
    return res;
}

double** multiplyMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2) {
    if (c1 != r2) return nullptr;
    auto res = allocMatrix(r1, c2);
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j)
            for (int k = 0; k < c1; ++k)    // use c1 (== r2)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}

double** transposeMatrix(const double* const* m, int r, int c) {
    auto res = allocMatrix(c, r);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            res[j][i] = m[i][j];
    return res;
}

double detMatrix(const double* const* m, int r, int c) {
    if (r != c) return 0.0;              // not square
    if (r == 1) return m[0][0];
    if (r == 2) return m[0][0]*m[1][1] - m[0][1]*m[1][0];

    double det = 0.0;
    for (int j = 0; j < c; ++j) {
        const double a0j = m[0][j];
        if (a0j == 0.0) continue;       // small speedup
        auto sub = makeSubMatrix(m, r, c, 0, j);
        double minor = detMatrix(sub, r - 1, c - 1);
        double sign  = (j % 2 == 0) ? +1.0 : -1.0;
        det += sign * a0j * minor;
        freeMatrix(sub, r - 1);
    }
    return det;
}

double** inverseMatrix(const double* const* m, int r, int c) {
    if (r != c) return nullptr;
    const double det = detMatrix(m, r, c);
    const double eps = 1e-12;           // tolerance for singularity
    if (std::fabs(det) < eps) return nullptr;

    // cofactor matrix
    auto cof = allocMatrix(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            auto sub = makeSubMatrix(m, r, c, i, j);
            double minor = detMatrix(sub, r - 1, c - 1);
            double sign  = ((i + j) % 2 == 0) ? +1.0 : -1.0;
            cof[i][j] = sign * minor;
            freeMatrix(sub, r - 1);
        }
    }
    // adjugate = transpose(cofactor)
    auto adj = transposeMatrix(cof, r, c);
    freeMatrix(cof, r);

    // inverse = (1/det) * adj
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            adj[i][j] /= det;

    return adj;
}
