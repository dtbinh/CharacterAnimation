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

#ifndef ___MATH_VEC2_H__
#define ___MATH_VEC2_H__


#include <math.h>
#include <iostream>

namespace math {

	/*! \brief A 2D generic vector. */
    template<class T>
    class Vec2
    {
        public:

            union
            {
                struct { T x, y; };
                T v[2];
            };

            /*
             * Constructors, destructor and accessors
             */

            /*! \brief Default constructor */
			Vec2(const T &_x=0, const T &_y=0) : x(_x), y(_y) {}

			/*! */
			Vec2( const T* v ) : x( v[0] ), y( v[1] ) {}

            /*! \brief Copy constructor */
            Vec2(const Vec2<T> &v) : x(v.x), y(v.y) {}


            template <class C>
            explicit Vec2(const C &c) : x(c[0]), y(c[1]) {}

            /*! \brief Destructor */
            ~Vec2() {}

			/*! Accesors */
			inline T &operator[](const int &i) { return v[i]; }
			inline T &operator[](const unsigned int &i) { return v[i]; }
			inline const T &operator[](const int &i) const { return v[i]; }
			inline const T &operator[](const unsigned int &i) const { return v[i]; }
            inline void set(const T &_x, const T &_y) { x=_x; y=_y; }
            operator const T*() const { return v; }
            operator T*() { return v; }

            /*
             * Affectation operator
             */
            inline Vec2 operator=(const Vec2 &a) { x = a.x; y = a.y; return *this; }
            inline Vec2 operator+=(const Vec2 &a) { x += a.x; y += a.y; return *this; }
            inline Vec2 operator-=(const Vec2 &a) { x -= a.x; y -= a.y; return *this; }

            inline Vec2 operator*=(const T &s) { x *= s; y *= s; return *this; }
            inline Vec2 operator/=(const T &s) { x /= s; y /= s; return *this; }

            /*
             * Binary operation with an other vector
             */
            friend inline Vec2 operator+(const Vec2 &a, const Vec2 &b) { return Vec2<T>( a.x+b.x, a.y+b.y ); }
            friend inline Vec2 operator-(const Vec2 &a, const Vec2 &b) { return Vec2<T>( a.x-b.x, a.y-b.y ); }

            /*
             * Unary operation with one vector
             */
            friend inline Vec2 operator-(const Vec2 &a) { return Vec2<T>( -a.x, -a.y ); }

            /*
             * Binary operation with a scalar
             */
            friend inline Vec2 operator+(const Vec2 &a, const T & s) { return Vec2<T>( a.x+s, a.y+s ); }
            friend inline Vec2 operator-(const Vec2 &a, const T & s) { return Vec2<T>( a.x-s, a.y-s ); }
            friend inline Vec2 operator*(const Vec2 &a, const T & s) { return Vec2<T>( a.x*s, a.y*s ); }
            friend inline Vec2 operator/(const Vec2 &a, const T & s) { return Vec2<T>( a.x/s, a.y/s ); }

            friend inline Vec2 operator+(const T &s, const Vec2 &a ) { return Vec2<T>( a.x+s, a.y+s ); }
            friend inline Vec2 operator*(const T &s, const Vec2 &a ) { return Vec2<T>( a.x*s, a.y*s ); }

            /*
             * Boolean operator
             */
            friend inline bool operator!=(const Vec2 &a, const Vec2 &b) { return !(a==b); }
            friend inline bool operator==(const Vec2 &a, const Vec2 &b) { return (a-b).norm() < 1.0E-10f; }

            /*
             * Dot product
             */
            friend inline T dotProduct(const Vec2 &a, const Vec2 &b) { return a.x*b.x + a.y*b.y; }
            friend inline T operator*(const Vec2 &a, const Vec2 &b) { return dotProduct(a,b); }







            /*! Norm of the vector */
            inline float norm() const {return sqrt(static_cast< float >( x*x + y*y ) );}
            inline T squaredNorm() const {return (x*x + y*y);}

            /*! Normalize the vector */
            inline Vec2 &normalize() { *this/=norm(); return *this; }
            inline Vec2 &unit() const { return Vec2(*this).normalize(); }

            /*! I/O operator */
            friend std::istream &operator >>(std::istream &stream, Vec2 &v) { return stream >> v.x >> v.y; }
            friend std::ostream &operator <<(std::ostream &stream, const Vec2<T> &v) { return stream << v.x << " " << v.y; }
    };

	typedef Vec2< double       > Vec2d ;
	typedef Vec2< float        > Vec2f ;
	typedef Vec2< int          > Vec2i ;
	typedef Vec2< unsigned int > Vec2ui ;

} // namespace Sami


#endif // ___MATH_VEC2_H__
