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

#ifndef ___MATH_VEC3_H__
#define ___MATH_VEC3_H__


#include <math.h>
#include <iostream>

#include <Vec2.h>

namespace math {

	#ifndef _WIN32
	template< typename T > class Vec3;
	template< typename T > Vec3<T> getToroidalVector(const Vec3<T>& p1, const Vec3<T>& p2, const T& sizex=static_cast<T>(1.f), const T& sizey=static_cast<T>(1.f), const T& sizez=static_cast<T>(1.f));
	#endif

	/*! \brief A 3D generic vector. */
    template< typename T >
    class Vec3
    {
        public:

            union
			{
				struct { T x, y, z; };
				struct { T r, g, b; };
                T v[3];
            };

            /*
             * Constructors, destructor and accessors
             */

            /*! Default constructor. */
									Vec3				( const T&_x = 0, const T& _y = 0, const T& _z = 0 ) : x( _x ), y( _y ), z( _z ) {}

			/*! Constructor with an array of T. */
									Vec3				( const T* v ) : x( v[0] ), y( v[1] ), z( v[2] ) {}

            /*! Copy constructor. The third value is set to 0. */
									Vec3				( const Vec2< T >& v ) : x( v.x ), y( v.y ), z( 0 ) {}

            /*! Copy constructor. */
									Vec3				( const Vec3< T >& v ) : x( v.x ), y( v.y ), z( v.z ) {}

            /*! Constructor with any class providing the function : T operator[]( int i ). */
            template < class C >
            explicit				Vec3				( const C& c ) : x( (T)c[0] ), y( (T)c[1] ), z( (T)c[2] ) {}

            /*! Destructor */
            ~Vec3() {}

			/*! Accessors */
			inline void				set					( const T& _x, const T& _y, const T& _z ) { x = _x; y = _y; z = _z; }
			inline T&				operator[]			( const int& i ) { return v[i]; }
			inline T&				operator[]			( const unsigned int& i ) { return v[i]; }
			inline const T&			operator[]			( const int& i ) const { return v[i]; }
			inline const T&			operator[]			( const unsigned int& i ) const { return v[i]; }
            inline					operator const T*	() const { return v; }
            inline					operator T*			() { return v; }

            /*
             * Affectation operator
             */
            inline Vec3				operator=			( const Vec3& a) { x = a.x; y = a.y; z = a.z; return *this; }
            inline Vec3				operator+=			( const Vec3& a) { x += a.x; y += a.y; z += a.z; return *this; }
            inline Vec3				operator-=			( const Vec3& a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
            inline Vec3				operator*=			( const T& s ) { x *= s; y *= s; z *= s; return *this; }
            inline Vec3				operator/=			( const T& s ) { x /= s; y /= s; z /= s; return *this; }

            /*
             * Binary operation with an other vector
             */
            friend inline Vec3		operator+			( const Vec3& a, const Vec3& b ) { return Vec3< T >( a.x + b.x, a.y + b.y, a.z + b.z ); }
            friend inline Vec3		operator-			( const Vec3& a, const Vec3& b ) { return Vec3< T >( a.x - b.x, a.y - b.y, a.z - b.z ); }

            /*
             * Unary operation with one vector
             */
            friend inline Vec3		operator-			( const Vec3& a ) { return Vec3< T >( -a.x, -a.y, -a.z ); }

            /*
             * Binary operation with a scalar
             */
            friend inline Vec3		operator+			( const Vec3& a, const T& s) { return Vec3< T >( a.x + s, a.y + s, a.z + s ); }
            friend inline Vec3		operator-			( const Vec3& a, const T& s) { return Vec3< T >( a.x - s, a.y - s, a.z - s ); }
            friend inline Vec3		operator*			( const Vec3& a, const T& s) { return Vec3< T >( a.x * s, a.y * s, a.z * s ); }
            friend inline Vec3		operator/			( const Vec3& a, const T& s) { return Vec3< T >( a.x / s, a.y / s, a.z / s ); }

            friend inline Vec3		operator+			( const T& s, const Vec3& a ) { return Vec3< T >( a.x + s, a.y + s, a.z + s ); }
            friend inline Vec3		operator*			( const T& s, const Vec3& a ) { return Vec3< T >( a.x * s, a.y * s, a.z * s ); }

            /*
             * Boolean operator
             */
            friend inline bool		operator!=			( const Vec3& a, const Vec3& b) { return !( a == b ); }
            friend inline bool		operator==			( const Vec3& a, const Vec3& b) { return ( a - b ).squaredNorm() < 1.0E-10f; }

			template< typename TT >
			friend inline bool		operator<			( const Vec3< TT >& a, const Vec3< TT >& b );
            /*
             * Dot product
			 */
			friend inline T			dotProduct			( const Vec3& a, const Vec3& b) { return ( ( a.x * b.x ) + ( a.y * b.y ) + ( a.z * b.z ) ); }
			friend inline T			dot					( const Vec3& a, const Vec3& b) { return dotProduct( a, b ); }
            friend inline T			operator*			( const Vec3& a, const Vec3& b) { return dotProduct( a, b ); }

            /*
             * Cross product
             */
            friend inline Vec3		crossProduct		( const Vec3& a, const Vec3& b ) { return Vec3( ( a.y * b.z ) - ( a.z * b.y ), ( a.z * b.x ) - ( a.x * b.z ), ( a.x * b.y ) - ( a.y * b.x ) ); }
			friend inline Vec3		cross				( const Vec3& a, const Vec3& b ) { return crossProduct( a, b ); }
			friend inline Vec3		operator^			( const Vec3& a, const Vec3& b ) { return crossProduct( a, b ); }

            /*! Norm of the vector */
            inline T				norm				() const { return sqrt( ( x * x ) + ( y * y ) + ( z * z ) ); }
            inline T				squaredNorm			() const { return ( ( x * x ) + ( y * y ) + ( z * z ) ); }

            /*! Normalize the vector */
            inline Vec3&			normalize			() { T n = norm(); ( *this ) /= ( ( n != 0 )? n : 1 ); return *this; }
			inline Vec3&			unit				() const { return ( *this ).normalize(); }
			inline Vec3				getNormalized		() const { Vec3 v( *this ); return v.normalize(); }
			inline Vec3				getUnit				() const { return getNormalized(); }

			/*! Rotation */
			inline void				rotateX				( double fAngle ) { *this = getRotatedX( fAngle ); }
			inline void				rotateY				( double fAngle ) { *this = getRotatedY( fAngle ); }
			inline void				rotateZ				( double fAngle ) { *this = getRotatedZ( fAngle ); }
			inline Vec3				getRotatedX			( double fAngle ) const;
			inline Vec3				getRotatedY			( double fAngle ) const;
			inline Vec3				getRotatedZ			( double fAngle ) const;

            /*! I/O operator */
            friend std::istream&	operator >>			( std::istream& is, Vec3& v ) { return is >> v.x >> v.y >> v.z; }
            friend std::ostream&	operator <<			( std::ostream& os, const Vec3< T >& v ) { return os << v.x << " " << v.y << " " << v.z; }

			#ifdef _WIN32
			friend Vec3<T> getToroidalVector(const Vec3<T>& p1, const Vec3<T>& p2, const T& sizex, const T& sizey, const T& sizez);
			#else
			friend Vec3<T> getToroidalVector<>(const Vec3<T>& p1, const Vec3<T>& p2, const T& sizex, const T& sizey, const T& sizez);
			#endif
    };

	typedef Vec3< double       > Vec3d ;
	typedef Vec3< float        > Vec3f ;
	typedef Vec3< int          > Vec3i ;
	typedef Vec3< unsigned int > Vec3ui ;


	template< typename T >
	Vec3< T > getToroidalVector(	const Vec3<T>& p1,
									const Vec3<T>& p2,
									const T& sizex=static_cast<T>(1.f),
									const T& sizey=static_cast<T>(1.f),
									const T& sizez=static_cast<T>(1.f))
	{
		float dx = p2.x - p1.x;
		if (fabs(dx) > sizex / 2) {
			if (p2.x < sizex / 2) {
				dx = p2.x - (p1.x - sizex);
			} else {
				dx = p2.x - (p1.x + sizex);
			}
		}
		float dy = p2.y - p1.y;
		if (fabs(dy) > sizey / 2) {
			if (p2.y < sizey / 2) {
				dy = p2.y - (p1.y - sizey);
			} else {
				dy = p2.y - (p1.y + sizey);
			}
		}
		float dz = p2.z - p1.z;
		if (fabs(dz) > sizez / 2) {
			if (p2.y < sizez / 2) {
				dz = p2.z - (p1.z - sizez);
			} else {
				dz = p2.z - (p1.z + sizez);
			}
		}
		return Vec3f(dx, dy, dz);
	}

	template< typename T >
	Vec3<T> Vec3<T>::getRotatedX( double fAngle ) const
	{
		if( fAngle == 0.0 ) return *this;

		float fSinAngle = (float)sin( M_PI * fAngle / 180 );
		float fCosAngle = (float)cos( M_PI * fAngle / 180 );

		return Vec3<T>( v[0], v[1] * fCosAngle - v[2] * fSinAngle, v[1] * fSinAngle + v[2] * fCosAngle );
	}

	template<typename T>
	Vec3<T> Vec3<T>::getRotatedY(double fAngle) const
	{
		if( fAngle == 0.0 ) return *this;

		float fSinAngle =(float)sin( M_PI * fAngle / 180 );
		float fCosAngle =(float)cos( M_PI * fAngle / 180 );

		return Vec3<T>( v[0] * fCosAngle + v[2] * fSinAngle, v[1], -v[0] * fSinAngle + v[2] * fCosAngle );
	}

	template<typename T>
	Vec3<T> Vec3<T>::getRotatedZ( double fAngle ) const
	{
		if( fAngle == 0.0 ) return *this;

		float fSinAngle =(float)sin( M_PI * fAngle /180 );
		float fCosAngle =(float)cos( M_PI * fAngle /180 );

		return Vec3<T>( v[0] * fCosAngle - v[1] * fSinAngle, v[0] * fSinAngle + v[1] * fCosAngle , v[2] );
	}

	template< typename T >
	bool operator<( const Vec3< T >& a, const Vec3< T >& b )
	{
		//return ( a.squaredNorm() < b.squaredNorm() );
	/*	if ( a.v[0] != b.v[0] ) return a.v[0] < b.v[0];
		if ( a.v[1] != b.v[1] ) return a.v[1] < b.v[1];
		if ( a.v[2] != b.v[2] ) return a.v[2] < b.v[2];
		return false; */



		float fCompX = fabs( a.x - b.x );
		float fCompY = fabs( a.y - b.y );
		float fCompZ = fabs( a.z - b.z );

		if ( ( fCompX >= fCompY ) && ( fCompX >= fCompZ ) ) return a.x < b.x;
		if ( ( fCompY >= fCompX ) && ( fCompY >= fCompZ ) ) return a.y < b.y;
		if ( ( fCompZ >= fCompX ) && ( fCompZ >= fCompY ) ) return a.z < b.z;

		return false;
	}

} // namespace

#endif // ___MATH_VEC3_H__

