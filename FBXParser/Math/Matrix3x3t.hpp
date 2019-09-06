//
//  Matrix3x3t.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef Matrix3x3t_hpp
#define Matrix3x3t_hpp

#include <stdio.h>

template <typename T> class Matrix4x4t;

template <typename T>
class Matrix3x3t
{
public:
    Matrix3x3t():
    a1(static_cast<T>(1.0f)), a2(), a3(),
    b1(), b2(static_cast<T>(1.0f)), b3(),
    c1(), c2(), c3(static_cast<T>(1.0f))
    {
        
    }
    
    // ----------------------------------------------------------------------------------------
   Matrix3x3t(T _a1, T _a2, T _a3,
                              T _b1, T _b2, T _b3,
                              T _c1, T _c2, T _c3):
    a1(_a1), a2(_a2), a3(_a3),
    b1(_b1), b2(_b2), b3(_b3),
    c1(_c1), c2(_c2), c3(_c3)
    {
        
    }
public:
    inline Matrix3x3t(const Matrix4x4t<T>& pMatrix)
    {
        a1 = pMatrix.a1; a2 = pMatrix.a2; a3 = pMatrix.a3;
        b1 = pMatrix.b1; b2 = pMatrix.b2; b3 = pMatrix.b3;
        c1 = pMatrix.c1; c2 = pMatrix.c2; c3 = pMatrix.c3;
    }

    
public:
    T a1, a2, a3;
    T b1, b2, b3;
    T c1, c2, c3;
    
};

typedef Matrix3x3t<float> Matrix3x3;

#endif /* Matrix3x3t_hpp */
