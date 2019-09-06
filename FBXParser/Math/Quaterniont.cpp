//
//  Quaterniont.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/5.
//  Copyright © 2019 Park. All rights reserved.
//

#include "Quaterniont.hpp"

//template<typename T>
//Quaterniont<T>::Quaterniont():w(1.0), x(), y(), z()
//{
//    
//}
//
//// ----------------------------------------------------------------------------------------
//template<typename T>
//Quaterniont<T>::Quaterniont(T pw, T px, T py, T pz): w(pw), x(px), y(py), z(pz)
//{
//    
//}
//
//// ----------------------------------------------------------------------------------------
//// Constructs a quaternion from a rotation matrix
//template<typename T>
//inline Quaterniont<T>::Quaterniont( const Matrix3x3t<T> &pRotMatrix)
//{
//    T t = pRotMatrix.a1 + pRotMatrix.b2 + pRotMatrix.c3;
//    
//    // large enough
//    if( t > static_cast<T>(0))
//    {
//        T s = std::sqrt(1 + t) * static_cast<T>(2.0);
//        x = (pRotMatrix.c2 - pRotMatrix.b3) / s;
//        y = (pRotMatrix.a3 - pRotMatrix.c1) / s;
//        z = (pRotMatrix.b1 - pRotMatrix.a2) / s;
//        w = static_cast<T>(0.25) * s;
//    } // else we have to check several cases
//    else if( pRotMatrix.a1 > pRotMatrix.b2 && pRotMatrix.a1 > pRotMatrix.c3 )
//    {
//        // Column 0:
//        T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.a1 - pRotMatrix.b2 - pRotMatrix.c3) * static_cast<T>(2.0);
//        x = static_cast<T>(0.25) * s;
//        y = (pRotMatrix.b1 + pRotMatrix.a2) / s;
//        z = (pRotMatrix.a3 + pRotMatrix.c1) / s;
//        w = (pRotMatrix.c2 - pRotMatrix.b3) / s;
//    }
//    else if( pRotMatrix.b2 > pRotMatrix.c3)
//    {
//        // Column 1:
//        T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.b2 - pRotMatrix.a1 - pRotMatrix.c3) * static_cast<T>(2.0);
//        x = (pRotMatrix.b1 + pRotMatrix.a2) / s;
//        y = static_cast<T>(0.25) * s;
//        z = (pRotMatrix.c2 + pRotMatrix.b3) / s;
//        w = (pRotMatrix.a3 - pRotMatrix.c1) / s;
//    } else
//    {
//        // Column 2:
//        T s = std::sqrt( static_cast<T>(1.0) + pRotMatrix.c3 - pRotMatrix.a1 - pRotMatrix.b2) * static_cast<T>(2.0);
//        x = (pRotMatrix.a3 + pRotMatrix.c1) / s;
//        y = (pRotMatrix.c2 + pRotMatrix.b3) / s;
//        z = static_cast<T>(0.25) * s;
//        w = (pRotMatrix.b1 - pRotMatrix.a2) / s;
//    }
//}
