#ifndef MATRIXOPS_H
#define MATRIXOPS_H

#pragma once

double** addMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2);
double** subtractMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2);
double** multiplyMatrices(const double* const* a, const double* const* b, int r1, int c1, int r2, int c2);
double** transposeMatrix(const double* const* m, int r, int c);
double     detMatrix(const double* const* m, int r, int c);
double**   inverseMatrix(const double* const* m, int r, int c);


#endif // MATRIXOPS_H
