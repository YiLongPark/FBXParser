//
//  Vector3D.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/8.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <stdio.h>
#include <cmath>

template <typename T>
class Vector3Dt
{
public:
    Vector3Dt(){}
    Vector3Dt(T _x, T _y, T _z): x(_x), y(_y), z(_z){}
    
    inline T SquareLength() const
    {
        return  x*x + y*y + z*z;
    }
    
    inline T Length() const
    {
        return std::sqrt(SquareLength());
    }
    
   inline T operator[](unsigned int i)
    {
        return *(&x + i);
    }
    
    inline Vector3Dt<T> operator /= (T f)
    {
        x /= f; y /= f; z /= f; return *this;
    }
    
    
    inline const Vector3Dt<T>& operator -= (const Vector3Dt<T>& o)
    {
        x -= o.x; y -= o.y; z -= o.z; return *this;
    }
    
    inline Vector3Dt<T> operator - (const Vector3Dt<T>& v)
    {
        return Vector3Dt<T>(-v.x, -v.y, -v.z);
    }
    
public:
    T  x, y ,z;
};

typedef Vector3Dt<float> Vector3D;

#endif /* Vector3D_hpp */
