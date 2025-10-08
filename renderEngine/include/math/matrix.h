// theforge.nekoweb.org

//         :XXXXo;'                .;lXXXXl         
//         cNX....                  ....KNo         
//         ,do                          ld;         
//         ...    .cccccc:  ;cccccc.    ...         
//                ,NNxx0N0  kNKxxNN:                
//                'KK. cKk  xKo  KK;                
//                .::  .:;  ,:'  ::.                
//              ,::::  .::::::'  ::::;              
//                                                  
//              cxc  ',. .xx. .,,  :xo              
//         .'.  ,:,  ...  ::.  ..  ':;  .'.         
//         ,xd                          lx;         
//         cNX''..                  ..''KNo         
//         :KKKKl;'                .;cKKKKc      

// ForgeWorks

// In engineering I trust.

/*

Matrix.h

*/

#ifndef MATRIX_H
#define MATRIX_H

#include <abstract.hpp>
#include "vector.h"

// Generic MxN Matrix
template <int ROWS, int COLS, typename T>
class Matrix {
public:
    T data[ROWS][COLS];

    Matrix();
    Matrix(const T d[ROWS][COLS]);

    T* operator[](size_t row); // Row access, mutable
    const T* operator[](size_t row) const; // Row access, constant
};

// Common specializations for better performance and usability

// 2x2 Matrix
template<typename T>
class Matrix<2, 2, T> {
public:
    // Column-major storage (common in graphics)
    T m00, m10; // Column 0
    T m01, m11; // Column 1

    Matrix();
    Matrix(T _00, T _01,
           T _10, T _11);
    
    T* operator[](size_t row);
    const T* operator[](size_t row) const;
};

// 3x3 Matrix
template<typename T>
class Matrix<3, 3, T> {
public:
    T m00, m10, m20; // Column 0
    T m01, m11, m21; // Column 1  
    T m02, m12, m22; // Column 2

    Matrix();
    Matrix(T _00, T _01, T _02,
           T _10, T _11, T _12,
           T _20, T _21, T _22);
    
    T* operator[](size_t row);
    const T* operator[](size_t row) const;
};

// 4x4 Matrix (most common in 3D graphics)
template<typename T>
class Matrix<4, 4, T> {
public:
    T m00, m10, m20, m30; // Column 0
    T m01, m11, m21, m31; // Column 1
    T m02, m12, m22, m32; // Column 2
    T m03, m13, m23, m33; // Column 3

    Matrix();
    Matrix(T _00, T _01, T _02, T _03,
           T _10, T _11, T _12, T _13, 
           T _20, T _21, T _22, T _23,
           T _30, T _31, T _32, T _33);
    
    T* operator[](size_t row);
    const T* operator[](size_t row) const;
};

////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

// Matrix operations
template <int R, int C, typename T>
Matrix<R, C, T> operator+(const Matrix<R, C, T>& left, const Matrix<R, C, T>& right);

template <int R, int C, typename T>
Matrix<R, C, T> operator-(const Matrix<R, C, T>& left, const Matrix<R, C, T>& right);

// Matrix-scalar multiplication
template <int R, int C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, C, T>& mat, T scalar);

template <int R, int C, typename T>
Matrix<R, C, T> operator*(T scalar, const Matrix<R, C, T>& mat);

// Matrix-matrix multiplication
template <int M, int N, int P, typename T>
Matrix<M, P, T> operator*(const Matrix<M, N, T>& left, const Matrix<N, P, T>& right);

// Matrix-vector multiplication
template <int R, int C, typename T>
Vector<C, T> operator*(const Matrix<R, C, T>& mat, const Vector<C, T>& vec);

template <int R, int C, typename T>
Vector<R, T> operator*(const Vector<R, T>& vec, const Matrix<R, C, T>& mat);

// Output for debugging
template <int R, int C, typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<R, C, T>& mat);

// Common matrix operations
template <int R, int C, typename T>
Matrix<C, R, T> transpose(const Matrix<R, C, T>& mat);

template <typename T>
T determinant(const Matrix<2, 2, T>& mat);

template <typename T>
T determinant(const Matrix<3, 3, T>& mat);

template <typename T>
T determinant(const Matrix<4, 4, T>& mat);

/* template <typename T>
Matrix<2, 2, T> inverse(const Matrix<2, 2, T>& mat);

template <typename T>
Matrix<3, 3, T> inverse(const Matrix<3, 3, T>& mat);

template <typename T>
Matrix<4, 4, T> inverse(const Matrix<4, 4, T>& mat); */

// Common matrix creations
template<typename T>
Matrix<4, 4, T> identity4x4();


// Now on transforms
/* template<typename T>
Matrix<4, 4, T> translation(T x, T y, T z);

template<typename T>
Matrix<4, 4, T> rotationX(T angle);

template<typename T>
Matrix<4, 4, T> rotationY(T angle);

template<typename T>
Matrix<4, 4, T> rotationZ(T angle);

template<typename T>
Matrix<4, 4, T> scale(T x, T y, T z); */

////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

// Generic Matrix Constructors
template <int R, int C, typename T>
Matrix<R, C, T>::Matrix() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            data[i][j] = T();
        }
    }
}

template <int R, int C, typename T>
Matrix<R, C, T>::Matrix(const T d[R][C]) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            data[i][j] = d[i][j];
        }
    }
}

// Specialized Matrix Constructors
template <typename T>
Matrix<2, 2, T>::Matrix() : m00(T()), m10(T()), m01(T()), m11(T()) {}

template <typename T>
Matrix<2, 2, T>::Matrix(T _00, T _01, T _10, T _11) 
    : m00(_00), m10(_10), m01(_01), m11(_11) {}

template <typename T>
Matrix<3, 3, T>::Matrix() : m00(T()), m10(T()), m20(T()), 
                            m01(T()), m11(T()), m21(T()),
                            m02(T()), m12(T()), m22(T()) {}

template <typename T>
Matrix<3, 3, T>::Matrix(T _00, T _01, T _02,
                       T _10, T _11, T _12,
                       T _20, T _21, T _22)
    : m00(_00), m10(_10), m20(_20),
      m01(_01), m11(_11), m21(_21), 
      m02(_02), m12(_12), m22(_22) {}

template <typename T>
Matrix<4, 4, T>::Matrix() : m00(T()), m10(T()), m20(T()), m30(T()),
                            m01(T()), m11(T()), m21(T()), m31(T()),
                            m02(T()), m12(T()), m22(T()), m32(T()),
                            m03(T()), m13(T()), m23(T()), m33(T()) {}

template <typename T>
Matrix<4, 4, T>::Matrix(T _00, T _01, T _02, T _03,
                       T _10, T _11, T _12, T _13,
                       T _20, T _21, T _22, T _23,
                       T _30, T _31, T _32, T _33)
    : m00(_00), m10(_10), m20(_20), m30(_30),
      m01(_01), m11(_11), m21(_21), m31(_31),
      m02(_02), m12(_12), m22(_22), m32(_32),
      m03(_03), m13(_13), m23(_23), m33(_33) {}

// Array-style access
template <int R, int C, typename T>
T* Matrix<R, C, T>::operator[](size_t row) {
    assert(row >= 0 && row < R);
    return data[row];
}

template <int R, int C, typename T>
const T* Matrix<R, C, T>::operator[](size_t row) const {
    assert(row >= 0 && row < R);
    return data[row];
}

// Specialized array access
template <typename T>
T* Matrix<2, 2, T>::operator[](size_t row) {
    assert(row >= 0 && row < 2);
    static T row0[2] = {m00, m01};
    static T row1[2] = {m10, m11};
    return row == 0 ? row0 : row1;
}

template <typename T>
const T* Matrix<2, 2, T>::operator[](size_t row) const {
    assert(row >= 0 && row < 2);
    static T row0[2] = {m00, m01};
    static T row1[2] = {m10, m11};
    return row == 0 ? row0 : row1;
}

template <typename T>
T* Matrix<3, 3, T>::operator[](size_t row) {
    assert(row >= 0 && row < 3);
    static T row0[3] = {m00, m01, m02};
    static T row1[3] = {m10, m11, m12};
    static T row2[3] = {m20, m21, m22};
    if (row == 0) return row0;
    else if (row == 1) return row1;
    else return row2;
}

template <typename T>
const T* Matrix<3, 3, T>::operator[](size_t row) const {
    assert(row >= 0 && row < 3);
    static T row0[3] = {m00, m01, m02};
    static T row1[3] = {m10, m11, m12};
    static T row2[3] = {m20, m21, m22};
    if (row == 0) return row0;
    else if (row == 1) return row1;
    else return row2;
}

template <typename T>
T* Matrix<4, 4, T>::operator[](size_t row) {
    assert(row >= 0 && row < 4);
    static T row0[4] = {m00, m01, m02, m03};
    static T row1[4] = {m10, m11, m12, m13};
    static T row2[4] = {m20, m21, m22, m23};
    static T row3[4] = {m30, m31, m32, m33};
    if (row == 0) return row0;
    else if (row == 1) return row1;
    else if (row == 2) return row2;
    else return row3;
}

template <typename T>
const T* Matrix<4, 4, T>::operator[](size_t row) const {
    assert(row >= 0 && row < 4);
    static T row0[4] = {m00, m01, m02, m03};
    static T row1[4] = {m10, m11, m12, m13};
    static T row2[4] = {m20, m21, m22, m23};
    static T row3[4] = {m30, m31, m32, m33};
    if (row == 0) return row0;
    else if (row == 1) return row1;
    else if (row == 2) return row2;
    else return row3;
}

// Matrix operations implementation
template <int R, int C, typename T>
Matrix<R, C, T> operator+(const Matrix<R, C, T>& left, const Matrix<R, C, T>& right) {
    Matrix<R, C, T> result;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            result[i][j] = left[i][j] + right[i][j];
        }
    }
    return result;
}

template <int R, int C, typename T>
Matrix<R, C, T> operator-(const Matrix<R, C, T>& left, const Matrix<R, C, T>& right) {
    Matrix<R, C, T> result;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            result[i][j] = left[i][j] - right[i][j];
        }
    }
    return result;
}

template <int R, int C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, C, T>& mat, T scalar) {
    Matrix<R, C, T> result;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            result[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

template <int R, int C, typename T>
Matrix<R, C, T> operator*(T scalar, const Matrix<R, C, T>& mat) {
    return mat * scalar;
}

template <int M, int N, int P, typename T>
Matrix<M, P, T> operator*(const Matrix<M, N, T>& left, const Matrix<N, P, T>& right) {
    Matrix<M, P, T> result;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            result[i][j] = T();
            for (int k = 0; k < N; k++) {
                result[i][j] += left[i][k] * right[k][j];
            }
        }
    }
    return result;
}

/* template <int R, int C, typename T>
Vector<C, T> operator*(const Matrix<R, C, T>& mat, const Vector<C, T>& vec) {
    Vector<C, T> result;
    for (int i = 0; i < R; i++) {
        result[i] = T();
        for (int j = 0; j < C; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
    return result;
} */

template <int R, int C, typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<R, C, T>& mat) {
    for (int i = 0; i < R; i++) {
        out << "[ ";
        for (int j = 0; j < C; j++) {
            out << mat[i][j];
            if (j < C - 1) out << ", ";
        }
        out << " ]" << std::endl;
    }
    return out;
}

// Common matrix functions
template <int R, int C, typename T>
Matrix<C, R, T> transpose(const Matrix<R, C, T>& mat) {
    Matrix<C, R, T> result;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            result[j][i] = mat[i][j];
        }
    }
    return result;
}

// Identity matrix
template<typename T>
Matrix<4, 4, T> identity4x4() {
    return Matrix<4, 4, T>(
        1, 0, 0, 0,
        0, 1, 0, 0, 
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

// Now handled by transforms
/* 
// Translation matrix
template<typename T>
Matrix<4, 4, T> translation(T x, T y, T z) {
    return Matrix<4, 4, T>(
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

// Scale matrix
template<typename T>
Matrix<4, 4, T> scale(T x, T y, T z) {
    return Matrix<4, 4, T>(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

template<typename T>
Matrix<4, 4, T> rotationX(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return Matrix<4, 4, T>(
        1, 0,  0, 0,
        0, c, -s, 0,
        0, s,  c, 0,
        0, 0,  0, 1
    );
}

template<typename T>
Matrix<4, 4, T> rotationY(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return Matrix<4, 4, T>(
        c, 0, s, 0,
        0, 1, 0, 0,
       -s, 0, c, 0,
        0, 0, 0, 1
    );
}

template<typename T>
Matrix<4, 4, T> rotationZ(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return Matrix<4, 4, T>(
        c, -s, 0, 0,
        s,  c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1
    );
} */

// Typedefs for common use
typedef Matrix<2, 2, float> Matrix2f;
typedef Matrix<3, 3, float> Matrix3f;
typedef Matrix<4, 4, float> Matrix4f;
typedef Matrix<2, 2, int> Matrix2i;
typedef Matrix<3, 3, int> Matrix3i;
typedef Matrix<4, 4, int> Matrix4i;

#endif // MATRIX_H