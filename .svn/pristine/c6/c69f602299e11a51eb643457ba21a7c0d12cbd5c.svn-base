/****************************************************************************
Copyright (C) 2010-2011 Alexandre Meyer

This file is part of Sami library.

Sami is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sami is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sami.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef ___MATH_VEC4_H__
#define ___MATH_VEC4_H__


#include <math.h>
#include <iostream>

#include <Vec2.h>
#include <Vec3.h>

namespace math {

	/*! \brief A 4D generic vector. */
    template<class T>
    class Vec4
    {
        public:

            union
            {
                struct { T x, y, z, w; };
                T v[4];
            };

            /*
             * Constructors, destructor and accessors
             */

            /*! Default constructor */
            Vec4(const T &_x=0, const T &_y=0, const T &_z=0, const T &_w=1) : x(_x), y(_y), z(_z), w(_w) {}

			/*! */
			Vec4( const T* v ) : x( v[0] ), y( v[1] ), z( v[2] ), w( v[3] ) {}

            /*! Copy constructor */
            Vec4(const Vec2<T> &v) : x(v.x), y(v.y), z(0), w(1) {}
            Vec4(const Vec3<T> &v) : x(v.x), y(v.y), z(v.z), w(1) {}

            template <class C>
            explicit Vec4(const C &c) : x(c[0]), y(c[1]), z(c[2]), w(c[3]) {}

            /*! Destructor */
            ~Vec4() {}

			/*! Accesors */
			inline T &operator[](const int &i) { return v[i]; }
			inline T &operator[](const unsigned int &i) { return v[i]; }
			inline const T &operator[](const int &i) const { return v[i]; }
			inline const T &operator[](const unsigned int &i) const { return v[i]; }
            inline void set(const T &_x, const T &_y, const T &_z, const T &_w) { x=_x; y=_y; z=_z; w=_w; }
            operator const T*() const { return v; }
            operator T*() { return v; }

            /*
             * Affectation operator
             */
            inline Vec4 operator=(const Vec4 &a) { x = a.x; y = a.y; z = a.z; w = a.w; return *this; }
            inline Vec4 operator+=(const Vec4 &a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }
            inline Vec4 operator-=(const Vec4 &a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }

            inline Vec4 operator*=(const T &s) { x *= s; y *= s; z *= s; w *= s; return *this; }
            inline Vec4 operator/=(const T &s) { x /= s; y /= s; z /= s; w /= s; return *this; }

            /*
             * Binary operation with an other vector
             */
            friend inline Vec4 operator+(const Vec4 &a, const Vec4 &b) { return Vec4<T>( a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w ); }
            friend inline Vec4 operator-(const Vec4 &a, const Vec4 &b) { return Vec4<T>( a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w ); }

            /*
             * Unary operation with one vector
             */
            friend inline Vec4 operator-(const Vec4 &a) { return Vec4<T>( -a.x, -a.y, -a.z, -a.w ); }

            /*
             * Binary operation with a scalar
             */
            friend inline Vec4 operator+(const Vec4 &a, const T & s) { return Vec4<T>( a.x+s, a.y+s, a.z+s, a.w+s ); }
            friend inline Vec4 operator-(const Vec4 &a, const T & s) { return Vec4<T>( a.x-s, a.y-s, a.z-s, a.w-s ); }
            friend inline Vec4 operator*(const Vec4 &a, const T & s) { return Vec4<T>( a.x*s, a.y*s, a.z*s, a.w*s ); }
            friend inline Vec4 operator/(const Vec4 &a, const T & s) { return Vec4<T>( a.x/s, a.y/s, a.z/s, a.w/s ); }

            friend inline Vec4 operator+(const T &s, const Vec4 &a ) { return Vec4<T>( a.x+s, a.y+s, a.z+s, a.w+s ); }
            friend inline Vec4 operator*(const T &s, const Vec4 &a ) { return Vec4<T>( a.x*s, a.y*s, a.z*s, a.w*s ); }

            /*
             * Boolean operator
             */
            friend inline bool operator!=(const Vec4 &a, const Vec4 &b) { return !(a==b); }
            friend inline bool operator==(const Vec4 &a, const Vec4 &b) { return (a-b).norm() < 1.0E-10f; }

            /*
             * Dot product
             */
            friend inline T dotProduct(const Vec4 &a, const Vec4 &b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
            friend inline T operator*(const Vec4 &a, const Vec4 &b) { return dotProduct(a,b); }







            /*! Norm of the vector */
            inline T norm() const {return sqrt(x*x + y*y + z*z + w*w);}
            inline T squaredNorm() const {return (x*x + y*y + z*z + w*w);}

            /*! Normalize the vector */
            inline Vec4 &normalize() { *this/=norm(); return *this; }
            inline Vec4 &unit() const { return Vec4(*this).normalize(); }

            /*! I/O operator */
            friend std::istream &operator >>(std::istream &stream, Vec4 &v) { return stream >> v.x >> v.y >> v.z >> v.w; }
            friend std::ostream &operator <<(std::ostream &stream, const Vec4<T> &v) { return stream << v.x << " " << v.y << " " << v.z << " " << v.w; }
    };

    typedef Vec4< double       > Vec4d ;
    typedef Vec4< float        > Vec4f ;
    typedef Vec4< int          > Vec4i ;
    typedef Vec4< unsigned int > Vec4ui ;

} // namespace Sami

#endif // __Sami_MATH_VEC4_H__

