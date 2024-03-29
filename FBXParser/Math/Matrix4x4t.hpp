//
//  Matrix4x4t.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef Matrix4x4t_hpp
#define Matrix4x4t_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

#ifdef __cplusplus


template <typename T> class Quaterniont;
template <typename T> class Matrix3x3t;
template <typename T> class Vector3Dt;

template<typename T>
class Matrix4x4t
{
public:
    Matrix4x4t():
    a1(1.0f), a2(), a3(), a4(),
    b1(), b2(1.0f), b3(), b4(),
    c1(), c2(), c3(1.0f), c4(),
    d1(), d2(), d3(), d4(1.0f)
    {
        
    }
    
    Matrix4x4t(T _a1, T _a2, T _a3, T _a4,
                              T _b1, T _b2, T _b3, T _b4,
                              T _c1, T _c2, T _c3, T _c4,
                              T _d1, T _d2, T _d3, T _d4):
    a1(_a1), a2(_a2), a3(_a3), a4(_a4),
    b1(_b1), b2(_b2), b3(_b3), b4(_b4),
    c1(_c1), c2(_c2), c3(_c3), c4(_c4),
    d1(_d1), d2(_d2), d3(_d3), d4(_d4)
    {
        
    }
    
    Matrix4x4t (const Matrix3x3t<T>& m)
    {
        a1 = m.a1; a2 = m.a2; a3 = m.a3; a4 = static_cast<T>(0.0);
        b1 = m.b1; b2 = m.b2; b3 = m.b3; b4 = static_cast<T>(0.0);
        c1 = m.c1; c2 = m.c2; c3 = m.c3; c4 = static_cast<T>(0.0);
        d1 = static_cast<T>(0.0); d2 = static_cast<T>(0.0); d3 = static_cast<T>(0.0); d4 = static_cast<T>(1.0);
    }
    
    // matrix multiplication.
    inline Matrix4x4t<T>& operator *= (const Matrix4x4t<T>& m)
    {
        *this = Matrix4x4t<T>(
                              m.a1 * a1 + m.b1 * a2 + m.c1 * a3 + m.d1 * a4,
                              m.a2 * a1 + m.b2 * a2 + m.c2 * a3 + m.d2 * a4,
                              m.a3 * a1 + m.b3 * a2 + m.c3 * a3 + m.d3 * a4,
                              m.a4 * a1 + m.b4 * a2 + m.c4 * a3 + m.d4 * a4,
                              m.a1 * b1 + m.b1 * b2 + m.c1 * b3 + m.d1 * b4,
                              m.a2 * b1 + m.b2 * b2 + m.c2 * b3 + m.d2 * b4,
                              m.a3 * b1 + m.b3 * b2 + m.c3 * b3 + m.d3 * b4,
                              m.a4 * b1 + m.b4 * b2 + m.c4 * b3 + m.d4 * b4,
                              m.a1 * c1 + m.b1 * c2 + m.c1 * c3 + m.d1 * c4,
                              m.a2 * c1 + m.b2 * c2 + m.c2 * c3 + m.d2 * c4,
                              m.a3 * c1 + m.b3 * c2 + m.c3 * c3 + m.d3 * c4,
                              m.a4 * c1 + m.b4 * c2 + m.c4 * c3 + m.d4 * c4,
                              m.a1 * d1 + m.b1 * d2 + m.c1 * d3 + m.d1 * d4,
                              m.a2 * d1 + m.b2 * d2 + m.c2 * d3 + m.d2 * d4,
                              m.a3 * d1 + m.b3 * d2 + m.c3 * d3 + m.d3 * d4,
                              m.a4 * d1 + m.b4 * d2 + m.c4 * d3 + m.d4 * d4);
        return *this;
    }
    
    inline Matrix4x4t<T> operator* (const Matrix4x4t<T>& m) const
    {
        Matrix4x4t<T> temp( *this);
        temp *= m;
        return temp;
    }
    
    inline T* operator[] (unsigned int index)
    {
        return &this->a1 + index * 4;
//        if(index > 3)
//        {
//            return NULL;
//        }
//
//        switch (index) {
//            case 0:
//                return &this->a1;
//                break;
//
//            default:
//                break;
//        }
    }
    
    inline const T* operator[] (unsigned int index) const
    {
       return  &this->a1 + index * 4;
    }
    
    
    inline T Determinant() const
    {
        return a1*b2*c3*d4 - a1*b2*c4*d3 + a1*b3*c4*d2 - a1*b3*c2*d4
        + a1*b4*c2*d3 - a1*b4*c3*d2 - a2*b3*c4*d1 + a2*b3*c1*d4
        - a2*b4*c1*d3 + a2*b4*c3*d1 - a2*b1*c3*d4 + a2*b1*c4*d3
        + a3*b4*c1*d2 - a3*b4*c2*d1 + a3*b1*c2*d4 - a3*b1*c4*d2
        + a3*b2*c4*d1 - a3*b2*c1*d4 - a4*b1*c2*d3 + a4*b1*c3*d2
        - a4*b2*c3*d1 + a4*b2*c1*d3 - a4*b3*c1*d2 + a4*b3*c2*d1;
    }
    
    inline void Decompose(Vector3Dt<T>& pScaling, Quaterniont<T>& pRotation, Vector3Dt<T>& pPosition) const
    {
        const Matrix4x4t<T> &_this = *this;
        pPosition.x = _this[0][3];
        pPosition.y = _this[1][3];
        pPosition.z = _this[2][3];
        
        Vector3Dt<T> vRows[3] =
        {
            Vector3Dt<T>(_this[0][0], _this[1][0], _this[2][0]),
            Vector3Dt<T>(_this[0][1], _this[1][1], _this[2][1]),
            Vector3Dt<T>(_this[0][2], _this[1][2], _this[2][2])
        };

        pScaling.x = vRows[0].Length();
        pScaling.y = vRows[1].Length();
        pScaling.z = vRows[2].Length();
        
        if(Determinant() < 0)
        {
            pScaling.x = -pScaling.x;
            pScaling.y = -pScaling.y;
            pScaling.z = -pScaling.z;
        }
        
        if(pScaling.x)
        {
            vRows[0] /= pScaling.x;
        }
        if(pScaling.y)
        {
            vRows[1] /= pScaling.y;
        }
        if(pScaling.z)
        {
            vRows[2] /= pScaling.z;
        }
        
        // build a 3x3 rotation matrix
        Matrix3x3t<T> m(vRows[0].x,vRows[1].x,vRows[2].x,
                        vRows[0].y,vRows[1].y,vRows[2].y,
                        vRows[0].z,vRows[1].z,vRows[2].z);
   
        // and generate the rotation quaternion from it
        pRotation = Quaterniont<T>(m);
    }
    
    inline Matrix4x4t<T>& Transpose()
    {
        // (TReal&) don't remove, GCC complains cause of packed fields
        std::swap( (T&)b1, (T&)a2);
        std::swap( (T&)c1, (T&)a3);
        std::swap( (T&)c2, (T&)b3);
        std::swap( (T&)d1, (T&)a4);
        std::swap( (T&)d2, (T&)b4);
        std::swap( (T&)d3, (T&)c4);
        return *this;
    }
    

public:
    static Matrix4x4t &RotationX(T a, Matrix4x4t &out)
    {
        
        /*
         |  1  0       0       0 |
         M = |  0  cos(A) -sin(A)  0 |
         |  0  sin(A)  cos(A)  0 |
         |  0  0       0       1 |  */
        out = Matrix4x4t<T>();
        out.b2 = out.c3 = std::cos(a);
        out.b3 = -(out.c2 = std::sin(a));
        return out;
    }
    
    static Matrix4x4t &RotationY(T a, Matrix4x4t &out)
    {
        /*
         |  cos(A)  0   sin(A)  0 |
         M = |  0       1   0       0 |
         | -sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
         */
        out = Matrix4x4t<T>();
        out.a1 = out.c3 = std::cos(a);
        out.c1 = -(out.a3 = std::sin(a));
        return out;
    }
    
    static Matrix4x4t &RotationZ(T a, Matrix4x4t &out)
    {
        /*
         |  cos(A)  -sin(A)   0   0 |
         M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |   */
        out = Matrix4x4t<T>();
        out.a1 = out.b2 = std::cos(a);
        out.a2 = -(out.b1 = std::sin(a));
        return out;
    }
    
    static Matrix4x4t<T>& Translation(const Vector3Dt<T> &v, Matrix4x4t<T> &out)
    {
        out = Matrix4x4t<T>();
        out.a4 = v.x;
        out.b4 = v.y;
        out.c4 = v.z;
        
        return out;
    }
    
    static Matrix4x4t<T>& Scaling( const Vector3Dt<T>& v, Matrix4x4t<T>& out)
    {
        out = Matrix4x4t<T>();
        out.a1 = v.x;
        out.b2 = v.y;
        out.c3 = v.z;
        return out;
    }
    
public:
    
    T a1, a2, a3, a4;
    T b1, b2, b3, b4;
    T c1, c2, c3, c4;
    T d1, d2, d3, d4;
    
};

typedef Matrix4x4t<float> Matrix4x4;

//#else

//struct Matrix4x4
//{
//    float a1, a2, a3, a4;
//    float b1, b2, b3, b4;
//    float c1, c2, c3, c4;
//    float d1, d2, d3, d4;
//};

#endif

#endif /* Matrix4x4t_hpp */
