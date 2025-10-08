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

// Vector.h

*/

#ifndef VECTOR_H
#define VECTOR_H

#include <abstract.hpp>

// VectorGeneric (however many dimensions thy heart desireth)
template <int N, typename T>
class Vector {
public:
    T data[N];

    Vector();
    Vector(const T d[]);

    T& operator[] (size_t index); // Array-style access, mutable

    const T& operator[] (size_t index) const;  // Array-style access, constant (for const vectors)
};

// Vector2D
template<typename T>
class Vector<2, T> {
public:
    T x, y;

    Vector() : x(T()), y(T()) {}
    Vector(T x, T y) : x(x), y(y) {}

    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;
};

// Vector3D
template<typename T>
class Vector<3, T> {
public:
    T x, y, z;

    Vector(): x(T()), y(T()), z(T()) {}
    Vector(T x, T y, T z) : x(x), y(y), z(z) {};

    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;
};

// Vector4D
// OOoh, 4th dimension shenanigans
template<typename T>
class Vector<4, T> {
public:
    T x, y, z, w;

    Vector(): x(T()), y(T()), z(T()), w(T()) {}
    Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;
};


////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
///////////////////////////////////////////////////////////////////////////////

//Basic operations

template<int N, typename T>
Vector<N, T> operator +(const Vector<N, T>& left, const Vector<N, T>& right);

template <int N, typename T>
Vector<N, T> operator -(const Vector<N, T>& left, const Vector<N, T>& right);

// Vector multiplied by scalar
template <int N, typename T>
Vector<N, T> operator *(T lhs, const Vector<N, T>& rhs);

template <int N, typename T>
Vector<N, T> operator *(const Vector<N, T>& lhs, T rhs);

template <int N, typename T>
Vector<N, T> operator/(const Vector<N, T>& lhs, const T& rhs);

// output the vector values, for debugging purposes
template <int N, typename T>
std::ostream& operator <<(std::ostream& out, Vector<N, T>& vector);

// Dot product of two vectors
template <int N, typename T>
T dot(const Vector<N, T>& left, const Vector<N, T>& right);

// Cross product of two Vector3T vectors
template <typename T>
Vector<3, T> cross(Vector<3, T> left, Vector<3, T> right);



////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

// Constructor implementations

template <int N, typename T>
Vector<N, T>::Vector() {
    for (int i = 0; i < N; i++) {
        data[i] = T();
    }
}


/* 
template <typename T>
Vector<2, T>::Vector() : x(T()), y(T()) {}

template <typename T>
Vector<3, T>::Vector() : x(T()), y(T()), z(T()) {}

template <typename T>
Vector<4, T>::Vector() : x(T()), y(T()), z(T()), w(T()) {}


template <typename T>
Vector<2, T>::Vector(T X, T Y) {
    x = X;
    y = Y;
}

template <typename T>
Vector<3, T>::Vector(T X, T Y, T Z) {
    x = X;
    y = Y;
    z = Z;
}

template <typename T>
Vector<4, T>::Vector(T X, T Y, T Z, T W) {
    x = X;
    y = Y;
    z = Z;
    w = W;
} */

// Vector from C-style array definition

template <int N, typename T>
Vector<N, T>::Vector(const T d[]) {
    for (int i = 0; i < N; i++) {
        data[i] = d[i]; // Copy each element from array
    }
}

// For array-style access

template <int N, typename T>
T& Vector<N, T>::operator[](size_t index) {
    assert(index < N);  // ← CORRECT
    return data[index];
}

template <int N, typename T>
const T& Vector<N, T>::operator[](size_t index) const {
    assert(index < N);
    return data[index];
}

// Array-style access hack for Vector2, 3 and 4.

template <typename T>
T& Vector<2, T>::operator[](size_t index) {
    assert(index >= 0 && index < 2);
    return index == 0 ? x : y;
}

template <typename T>
const T& Vector<2, T>::operator[](size_t index) const {
    assert(index >= 0 && index < 2);
    return index == 0 ? x : y;
}

template <typename T>
T& Vector<3, T>::operator[](size_t index) {
    assert(index >= 0 && index < 3);
    if (index == 0) return x;
    else if (index == 1) return y;
    else return z;
}

template <typename T>
const T& Vector<3, T>::operator[](size_t index) const {
    assert(index >= 0 && index < 3);
    if (index == 0) return x;
    else if (index == 1) return y;
    else return z;
}

template <typename T>
T& Vector<4, T>::operator[](size_t index) {
    assert(index >= 0 && index < 4);
    if (index == 0) return x;
    else if (index == 1) return y;
    else if (index == 2) return z;
    else return w;
}

template <typename T>
const T& Vector<4, T>::operator[](size_t index) const {
    assert(index >= 0 && index < 4);
    if (index == 0) return x;
    else if (index == 1) return y;
    else if (index == 2) return z;
    else return w;
}

// Definition of the vector operations

template<int N, typename T>
Vector<N, T> operator +(const Vector<N, T>& left, const Vector<N, T>& right) {
    Vector<N, T> tmp;
    for (int i = 0; i < N; i++) tmp[i] = left[i] + right[i];
    return tmp;
}

template <int N, typename T>
Vector<N, T> operator -(const Vector<N, T>& left, const Vector<N, T>& right) {
    Vector<N, T> tmp;
    for (int i = 0; i < N; i++) tmp[i] = left[i] - right[i];
    return tmp;
}

template<int N, typename T>
Vector<N, T> operator *(const Vector<N, T>& lhs, T rhs) {
    Vector<N, T> tmp;
    for (int i = 0; i < N; i++) tmp[i] = lhs[i] * rhs;
    return tmp;
}

template<int N, typename T>
Vector<N, T> operator *(T lhs, const Vector<N, T>& rhs) {
    Vector<N, T> tmp;
    for (int i = 0; i < N; i++) tmp[i] = lhs * rhs[i];
    return tmp;
}

template <int N, typename T>
Vector<N, T> operator /(const Vector<N, T>& lhs, const T& rhs) {
    Vector<N, T> tmp;
    for (int i = 0; i < N; i++) tmp[i] = lhs[i]/rhs;
    return tmp;
}

template <int N, typename T>
std::ostream& operator <<(std::ostream& out, Vector<N, T>& vector) {
    out << "(" << vector[0];
    for (int i = 1; i < N; i++) {
        out << ", " << vector[i];
    }
    out << ")";
    return out;
}


// @todo learn what the fuct is a dot product
template <int N, typename T>
T dot(const Vector<N, T>& left, const Vector<N, T>& right) {
    T res = left[0] * right[0];
    for (int i = 1; i < N; i++) res += left[i] * right[i];
    return res;
}

template <typename T>
Vector<3, T> cross(Vector<3, T> left, Vector<3, T> right) {
    return Vector<3, T>(
        left[1] * right[2] - right[1] * left[2],
        right[0] * left[2] - left[0] * right[2],
        left[0] * right[1] - right[0] * left[1]
    );
}

template <typename T>
Vector<3, T> normalize(const Vector<3, T>& vec) {
    return Vector<3, T>(vec/std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
}

template <typename T>
T norm(const Vector<3, T>& vec) {
    return std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

typedef Vector<2, int> Vector2i;
typedef Vector<2, float> Vector2f;
typedef Vector<3, int> Vector3i;
typedef Vector<3, float> Vector3f;
typedef Vector<4, int> Vector4i;
typedef Vector<4, float> Vector4f;

#endif      // VECTOR_H