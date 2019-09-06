//
//  Matrix4x4t.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/5.
//  Copyright © 2019 Park. All rights reserved.
//

#include "Matrix4x4t.hpp"

//template<typename T>
//Matrix4x4t<T>::Matrix4x4t():
//    a1(1.0f), a2(), a3(), a4(),
//    b1(), b2(1.0f), b3(), b4(),
//    c1(), c2(), c3(1.0f), c4(),
//    d1(), d2(), d3(), d4(1.0f)
//{
//    
//}
//
//// ----------------------------------------------------------------------------------------
//template<typename T>
//Matrix4x4t<T>::Matrix4x4t(T _a1, T _a2, T _a3, T _a4,
//           T _b1, T _b2, T _b3, T _b4,
//           T _c1, T _c2, T _c3, T _c4,
//           T _d1, T _d2, T _d3, T _d4):
//    a1(_a1), a2(_a2), a3(_a3), a4(_a4),
//    b1(_b1), b2(_b2), b3(_b3), b4(_b4),
//    c1(_c1), c2(_c2), c3(_c3), c4(_c4),
//    d1(_d1), d2(_d2), d3(_d3), d4(_d4)
//{
//    
//}
//
//// ----------------------------------------------------------------------------------------
//template <typename T>
//inline Matrix4x4t<T>& Matrix4x4t<T>::RotationX(T a, Matrix4x4t<T>& out)
//{
//    /*
//     |  1  0       0       0 |
//     M = |  0  cos(A) -sin(A)  0 |
//     |  0  sin(A)  cos(A)  0 |
//     |  0  0       0       1 |  */
//    out = Matrix4x4t<T>();
//    out.b2 = out.c3 = std::cos(a);
//    out.b3 = -(out.c2 = std::sin(a));
//    return out;
//}
//
//// ----------------------------------------------------------------------------------------
//template <typename T>
//inline Matrix4x4t<T>& Matrix4x4t<T>::RotationY(T a, Matrix4x4t<T>& out)
//{
//    /*
//     |  cos(A)  0   sin(A)  0 |
//     M = |  0       1   0       0 |
//     | -sin(A)  0   cos(A)  0 |
//     |  0       0   0       1 |
//     */
//    out = Matrix4x4t<T>();
//    out.a1 = out.c3 = std::cos(a);
//    out.c1 = -(out.a3 = std::sin(a));
//    return out;
//}
//
//// ----------------------------------------------------------------------------------------
//template <typename T>
//inline Matrix4x4t<T>& Matrix4x4t<T>::RotationZ(T a, Matrix4x4t<T>& out)
//{
//    /*
//     |  cos(A)  -sin(A)   0   0 |
//     M = |  sin(A)   cos(A)   0   0 |
//     |  0        0        1   0 |
//     |  0        0        0   1 |   */
//    out = Matrix4x4t<T>();
//    out.a1 = out.b2 = std::cos(a);
//    out.a2 = -(out.b1 = std::sin(a));
//    return out;
//}

// ----------------------------------------------------------------------------------------
//template <typename T>
//inline Matrix4x4t<T>& Matrix4x4t<T>::operator *= (const Matrix4x4t<T>& m)
//{
//    *this = Matrix4x4t<T>(
//                                m.a1 * a1 + m.b1 * a2 + m.c1 * a3 + m.d1 * a4,
//                                m.a2 * a1 + m.b2 * a2 + m.c2 * a3 + m.d2 * a4,
//                                m.a3 * a1 + m.b3 * a2 + m.c3 * a3 + m.d3 * a4,
//                                m.a4 * a1 + m.b4 * a2 + m.c4 * a3 + m.d4 * a4,
//                                m.a1 * b1 + m.b1 * b2 + m.c1 * b3 + m.d1 * b4,
//                                m.a2 * b1 + m.b2 * b2 + m.c2 * b3 + m.d2 * b4,
//                                m.a3 * b1 + m.b3 * b2 + m.c3 * b3 + m.d3 * b4,
//                                m.a4 * b1 + m.b4 * b2 + m.c4 * b3 + m.d4 * b4,
//                                m.a1 * c1 + m.b1 * c2 + m.c1 * c3 + m.d1 * c4,
//                                m.a2 * c1 + m.b2 * c2 + m.c2 * c3 + m.d2 * c4,
//                                m.a3 * c1 + m.b3 * c2 + m.c3 * c3 + m.d3 * c4,
//                                m.a4 * c1 + m.b4 * c2 + m.c4 * c3 + m.d4 * c4,
//                                m.a1 * d1 + m.b1 * d2 + m.c1 * d3 + m.d1 * d4,
//                                m.a2 * d1 + m.b2 * d2 + m.c2 * d3 + m.d2 * d4,
//                                m.a3 * d1 + m.b3 * d2 + m.c3 * d3 + m.d3 * d4,
//                                m.a4 * d1 + m.b4 * d2 + m.c4 * d3 + m.d4 * d4);
//    return *this;
//}
//// ----------------------------------------------------------------------------------------
//template <typename TReal>
//inline Matrix4x4t<TReal> Matrix4x4t<TReal>::operator* (const Matrix4x4t<TReal>& m) const
//{
//    Matrix4x4t<TReal> temp( *this);
//    temp *= m;
//    return temp;
//}

