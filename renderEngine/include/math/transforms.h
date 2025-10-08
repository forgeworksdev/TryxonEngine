#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <abstract.hpp>

#include "matrix.h"
#include "vector.h"

/* namespace Transform {
    Matrix4f translate(Vector3f translateVector);
    Matrix4f scale(Vector3f scalingFactors);
    Matrix4f rotate(Vector3f angles);
    Matrix4f lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
    Matrix4f viewportMatrix(int x, int y, int w, int h);
}
*/

namespace Transforms {

// Translation
template<typename T>
Matrix<4, 4, T> translate(T x, T y, T z);

template<typename T>
Matrix<4, 4, T> translate(const Vector<3, T>& translation);

// Scale
template<typename T>
Matrix<4, 4, T> scale(const Vector<3, T>& scale);

template<typename T>
Matrix<4, 4, T> scale(T uniformScaleFactor);

// Rotation
template<typename T>
Matrix<4, 4, T> rotate(const Vector<3, T>& angle);

// Camera
template<typename T>
Matrix<4, 4, T> lookAt(const Vector<3, T>& eye, const Vector<3, T>& target, const Vector<3, T>& up);

// Projection
template<typename T>
Matrix<4, 4, T> perspective(T fov, T aspect, T near, T far);

template<typename T>
Matrix<4, 4, T> orthographic(T left, T right, T bottom, T top, T near, T far);

// Transformation composition
template<typename T>
Matrix<4, 4, T> transform(const Vector<3, T>& position, const Vector<3, T>& rotation, const Vector<3, T>& scale);


/* template<typename T>
Vector<3, T> extractPosition(const Matrix<4, 4, T>& transform);

template<typename T>
Vector<3, T> extractScale(const Matrix<4, 4, T>& transform); */

} // namespace Transform

#endif      // TRANSFORMS_H