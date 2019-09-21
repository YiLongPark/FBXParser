//
//  Quaterniont.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef Quaterniont_hpp
#define Quaterniont_hpp

#include <stdio.h>
#include <cmath>

#ifdef __cplusplus

template <typename T> class Matrix3x3t;

template <typename T>
class Quaterniont
{
public:
    Quaterniont():w(1.0), x(), y(), z(){}
    
    Quaterniont(T pw, T px, T py, T pz): w(pw), x(px), y(py), z(pz){}
    
public:
    inline Quaterniont( const Matrix3x3t<T> &pRotMatrix)
    {
        T t = pRotMatrix.a1 + pRotMatrix.b2 + pRotMatrix.c3;
        
        // large enough
        if( t > static_cast<T>(0))
        {
            T s = std::sqrt(1 + t) * static_cast<T>(2.0);
            x = (pRotMatrix.c2 - pRotMatrix.b3) / s;
            y = (pRotMatrix.a3 - pRotMatrix.c1) / s;
            z = (pRotMatrix.b1 - pRotMatrix.a2) / s;
            w = static_cast<T>(0.25) * s;
        } // else we have to check several cases
        else if( pRotMatrix.a1 > pRotMatrix.b2 && pRotMatrix.a1 > pRotMatrix.c3 )
        {
            // Column 0:
            T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.a1 - pRotMatrix.b2 - pRotMatrix.c3) * static_cast<T>(2.0);
            x = static_cast<T>(0.25) * s;
            y = (pRotMatrix.b1 + pRotMatrix.a2) / s;
            z = (pRotMatrix.a3 + pRotMatrix.c1) / s;
            w = (pRotMatrix.c2 - pRotMatrix.b3) / s;
        }
        else if( pRotMatrix.b2 > pRotMatrix.c3)
        {
            // Column 1:
            T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.b2 - pRotMatrix.a1 - pRotMatrix.c3) * static_cast<T>(2.0);
            x = (pRotMatrix.b1 + pRotMatrix.a2) / s;
            y = static_cast<T>(0.25) * s;
            z = (pRotMatrix.c2 + pRotMatrix.b3) / s;
            w = (pRotMatrix.a3 - pRotMatrix.c1) / s;
        } else
        {
            // Column 2:
            T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.c3 - pRotMatrix.a1 - pRotMatrix.b2) * static_cast<T>(2.0);
            x = (pRotMatrix.a3 + pRotMatrix.c1) / s;
            y = (pRotMatrix.c2 + pRotMatrix.b3) / s;
            z = static_cast<T>(0.25) * s;
            w = (pRotMatrix.b1 - pRotMatrix.a2) / s;
        }
    }
    
    
    inline Matrix3x3t<T> GetMatrix() const
    {
        Matrix3x3t<T> resMatrix;
        resMatrix.a1 = static_cast<T>(1.0) - static_cast<T>(2.0) * (y * y + z * z);
        resMatrix.a2 = static_cast<T>(2.0) * (x * y - z * w);
        resMatrix.a3 = static_cast<T>(2.0) * (x * z + y * w);
        resMatrix.b1 = static_cast<T>(2.0) * (x * y + z * w);
        resMatrix.b2 = static_cast<T>(1.0) - static_cast<T>(2.0) * (x * x + z * z);
        resMatrix.b3 = static_cast<T>(2.0) * (y * z - x * w);
        resMatrix.c1 = static_cast<T>(2.0) * (x * z - y * w);
        resMatrix.c2 = static_cast<T>(2.0) * (y * z + x * w);
        resMatrix.c3 = static_cast<T>(1.0) - static_cast<T>(2.0) * (x * x + y * y);
        
        return resMatrix;
    }
    
public:
    T w, x, y, z;
    
};

typedef Quaterniont<float> Quaternion;

#endif 
#endif /* Quaterniont_hpp */
