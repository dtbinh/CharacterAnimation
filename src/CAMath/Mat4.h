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

#ifndef ____MAT4_H__
#define ____MAT4_H__


#include <iostream>
#include <vector>
#include <math.h>
#include <Vec.h>
#include <assert.h>

namespace math {

	template< typename T > class Vec2;
	template< typename T > class Vec3;
	template< typename T > class Vec4;

	/*! \brief   A generic matrix 4x4 class. */
	template< typename T >
	class Mat4
	{

	protected:

		union
		{
			T vv[4][4];   //!< The data of the matrix as a matrix. It is 'v''v' (and not 'w')
			T v[16];      //!< The data of the matrix as an array
		};

	public:

		/*! \brief The default constructor.
		*
		*  Initialize the matrix as an identity matrix. */
		Mat4(const bool initId=true);

		/*! \brief The copy constructor. */
		Mat4( const Mat4& m );

		/*! \brief The data constructor.
		*  \param a An array of size 16. */
		Mat4( const T* t );

		/*! \brief Constructor: translation matrix
		*  \param a the translation vector. */
		Mat4( const Vec3<T>& t );

		/*! \brief Constructor: scale matrix
		*  \param a the scale vector. */
		Mat4( const T& sx, const T& sy, const T& sz );

		enum AXE { AXE_X, AXE_Y, AXE_Z};

		/*! \brief The rotation constructor
		*  \param a the angle
		*	\param b the axe */
		Mat4( const T& angle, const AXE& axe );


		/*! \brief The destructor. */
		~Mat4();

		/*! \brief Accessor to a matrix line.
		*  \param i The line index (0 <= i< 4).
		*  \return A pointer to the first element of a line. */
		inline T* 						operator[]( int i );

		/*! \brief See above. */
		inline const T* 				operator[]( int i ) const;

		/*! \brief Accessor to the data (as an array).
		*  \return A pointer to the first element of the data (as an array).
		*
		*  Usefull to directly use the matrix with the OpenGL functions.
		*/
		operator 						T*();

		/*! \brief See above. */
		operator const 					T*() const;

		/*! \brief See the matrix as an array of 16 values
		\return the ith value of the matrix */
		inline const T&					operator()( int i ) const;

		/*! \brief See the matrix as an array of 16 values
		\return the ith value of the matrix */
		inline T&						operator()( int i );

		/*! \brief matrix x matrix */
		template< typename A, typename B >
		friend inline Mat4< A > 		operator*( const Mat4< A >& a, const Mat4< B >& b);

		/*! \brief matrix + matrix */
		template< typename A, typename B >
		friend inline Mat4< A > 		operator+( const Mat4< A >& a, const Mat4< B >& b);

		/*! \brief +=: matrix + matrix */
		inline Mat4< T >& operator+=( const Mat4< T >& a );

		inline Mat4< T >&				operator*=( const Mat4< T >& s );
		inline Mat4< T >&				operator*=( const T& s );

		/*! \brief multiply the matrix by the vector p */
		inline const Vec3< T >			operator*( const Vec3< T >& p ) const;

		/*! \brief multiply the matrix by the vector p */
		inline const Vec4< T >			operator*( const Vec4< T >& p ) const;

		/*! \brief To know if it is an identity matrix. */
		inline bool 					isIdentity() const;

		/*! \brief Transform the matrix which become an identity matrix. */
		inline Mat4< T >& 						setIdentity();
		/*! \brief set a X rotation matrix */
		inline Mat4< T >&						setRotationX( const T& fAngle );
		/*! \brief set a Y rotation matrix */
		inline Mat4< T >&						setRotationY( const T& fAngle );
		/*! \brief set a Z rotation matrix */
		inline Mat4< T >&						setRotationZ( const T& fAngle );
		/*! \brief set a scale matrix */
		inline Mat4< T >&						setScale(const T& sx, const T& sy, const T& sz );
		/*! \brief set a translation matrix */
		inline Mat4< T >&						setTranslationNoRotation(const Vec3<T>& transl );


		/*! \brief Transpose of the matrix. */
		inline Mat4< T >& 						transpose();

		/*! \brief Get the transpose of the matrix. */
		inline Mat4< T >						get_transpose() const;

		/*! \brief Get the inverse of the matrix. */
		inline Mat4< T >						get_inverse() const;

		/*! \brief inverse of the matrix. */
		inline Mat4< T >&						inverse();

		/*! \brief return the matrix combined with the translation */
		inline Mat4< T >						operator+( const Vec3< T >& vTranslation ) const;

		/*! \brief add the translation to the matrix */
		inline Mat4< T >&						operator+=( const Vec3< T >& vTranslation );
		inline Mat4< T >&						addTranslation( const Vec3< T >& vTranslation );

		/*! \brief return the matrix combined with the scale */
		//inline Mat4< T >						operator*( const T& scaleX, const T& scaleY, const T& scaleZ ) const;

		/*! \brief add the scale */
		inline Mat4< T >&						operator*=( const Vec3< T >& vScale );

		/*! \brief multiply the matrix by a X rotation matrix */
		inline Mat4< T >&						addRotationX( float fAngle );

		/*! \brief multiply the matrix by a X rotation matrix */
		inline Mat4< T >&						addRotationY( float fAngle );

		/*! \brief multiply the matrix by a X rotation matrix */
		inline Mat4< T >&						addRotationZ( float fAngle );

		/*! \brief multiply the matrix by a scale matrix */
		inline Mat4<T>&							addScale( const T& sx, const T& sy, const T& sz );

		inline Vec3< T >						getTranslation() const { return Vec3< T >( vv[0][3], vv[1][3], vv[2][3] ); }
		void	setTranslation(const T& x, const T& y, const T& z)  { vv[0][3]=x; vv[1][3]=y; vv[2][3]=z; }
		void	setTranslation(const Vec3< T >& t)  { vv[0][3]=t.x; vv[1][3]=t.y; vv[2][3]=t.z; }


		/*! \brief A comparator. */
		template< typename C >
		friend inline bool				operator!=( const Mat4< C >& a, const Mat4< C >& b );

		/*! \brief A comparator. */
		template< typename C >
		friend inline bool				operator==( const Mat4< C >& a, const Mat4< C >& b);

		/*! \brief Read a matrix from a std::istream. */
		template< typename C >
		friend std::istream&			operator>>( std::istream& stream, Mat4< C >& a );

		/*! \brief Write a matrix to a std::ostream. */
		template< typename C >
		friend std::ostream&			operator<<( std::ostream &stream, const Mat4< C >& a );

		//static const Mat4< T >			m_mIdentity;		//{ return Mat4< T >(); }

		static const T ZERO;
		static const T ONE;
		static bool isPrintOnLine;

	};

	//template< typename T > const Mat4< T > Mat4< T >::m_mIdentity;

	typedef Mat4< double > Mat4d;  //!< Matrix 4x4 of double
	typedef Mat4< float >  Mat4f;  //!< Matrix 4x4 of float
	typedef Mat4< int >    Mat4i;  //!< Matrix 4x4 of integer

	template<typename T>	const T Mat4<T>::ZERO = static_cast<T>(0);
	template<typename T>	const T Mat4<T>::ONE = static_cast<T>(1);
	template<typename T>	bool Mat4<T>::isPrintOnLine = false;


	template< typename T >
	Mat4< T >::Mat4( const Vec3<T>& trans )
	{
		setTranslationNoRotation(trans);
	}

	template< typename T >
	Mat4< T >&	Mat4< T >::setTranslationNoRotation( const Vec3<T>& tr )
	{
		vv[0][0] = ONE;			vv[0][1] = ZERO;	vv[0][2] = ZERO;	vv[0][3] = tr.x;
		vv[1][0] = ZERO;		vv[1][1] = ONE;		vv[1][2] = ZERO;	vv[1][3] = tr.y;
		vv[2][0] = ZERO;		vv[2][1] = ZERO;	vv[2][2] = ONE;		vv[2][3] = tr.z;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;	vv[3][2] = ZERO;	vv[3][3] = ONE;
		return *this;
	}

	template< typename T >
	Mat4< T >::Mat4( const T& sx, const T& sy, const T& sz )
	{
		setScale( sx, sy, sz);
	}

	template<typename T>
	Mat4<T>& Mat4<T>::setScale( const T& sx, const T& sy, const T& sz )
	{
		vv[0][0] = sx;			vv[0][1] = ZERO;	vv[0][2] = ZERO;	vv[0][3] = ZERO;
		vv[1][0] = ZERO;		vv[1][1] = sy;		vv[1][2] = ZERO;	vv[1][3] = ZERO;
		vv[2][0] = ZERO;		vv[2][1] = ZERO;	vv[2][2] = sz;		vv[2][3] = ZERO;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;	vv[3][2] = ZERO;	vv[3][3] = ONE;
		return *this;
	}

	template< typename T >
	Mat4< T >::Mat4( const T& angle, const AXE& axe )
	{
		if (axe==AXE_X) setRotationX(angle);
		else if (axe==AXE_Y) setRotationY(angle);
		else setRotationZ(angle);
	}



	template< typename T >
	Mat4<T>&	Mat4< T >::setRotationX( const T& angle)
	{
		vv[0][0] = ONE;			vv[0][1] = ZERO;	vv[0][2] = ZERO;	vv[0][3] = ZERO;
		vv[1][0] = ZERO;		vv[1][1] = cos(angle);	vv[1][2] = -sin(angle);	vv[1][3] = ZERO;
		vv[2][0] = ZERO;		vv[2][1] = sin(angle);	vv[2][2] = cos(angle);	vv[2][3] = ZERO;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;	vv[3][2] = ZERO;	vv[3][3] = ONE;
		return *this;
	}

	template< typename T >
	Mat4<T>&	Mat4< T >::setRotationY( const T& angle)
	{
		vv[0][0] = cos(angle);	vv[0][1] = ZERO;	vv[0][2] = sin(angle);	vv[0][3] = ZERO;
		vv[1][0] = ZERO;		vv[1][1] = ONE;		vv[1][2] = ZERO;		vv[1][3] = ZERO;
		vv[2][0] = -sin(angle);	vv[2][1] = ZERO;	vv[2][2] = cos(angle);	vv[2][3] = ZERO;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;	vv[3][2] = ZERO;		vv[3][3] = ONE;
		return *this;
	}

	template< typename T >
	Mat4<T>&	Mat4< T >::setRotationZ( const T& angle)
	{
		vv[0][0] = cos(angle);	vv[0][1] = -sin(angle);	vv[0][2] = ZERO;	vv[0][3] = ZERO;
		vv[1][0] = sin(angle);	vv[1][1] = cos(angle);	vv[1][2] = ZERO;	vv[1][3] = ZERO;
		vv[2][0] = ZERO;		vv[2][1] = ZERO;		vv[2][2] = ONE;		vv[2][3] = ZERO;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;		vv[3][2] = ZERO;	vv[3][3] = ONE;
		return *this;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::Mat4(const bool initId)
	{
		if (initId) setIdentity();
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::Mat4( const Mat4< T >& a )
	{
		for ( unsigned int i = 0; i < 16 ; i++ ) v[i] = a.v[i];
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::Mat4( const T* a )
	{
		for ( unsigned int i = 0; i < 16 ; i++ )
			v[i] = a[i];
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::~Mat4()
	{

	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	T* Mat4< T >::operator[]( int i )
	{
		assert(i>=0);
		assert(i<16);
		return vv[i];
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	const T* Mat4< T >::operator[]( int i ) const
	{
		assert(i>=0);
		assert(i<4);
		return vv[i];
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::operator T*()
	{
		return ( T* )v;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >::operator const T*() const
	{
		return ( T* )v;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	const T& Mat4< T >::operator()( int i ) const
	{
		assert(i>=0);
		assert(i<16);
		return v[i];
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	T& Mat4< T >::operator()( int i )
	{
		assert(i>=0);
		assert(i<16);
		return v[i];
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T, typename C >
	Mat4< T > operator*( const Mat4< T >& a, const Mat4< C >& b )
	{
		Mat4< T > res;
		res[0][0]=a[0][0]*b[0][0]+a[0][1]*b[1][0]+a[0][2]*b[2][0]+a[0][3]*b[3][0];
		res[0][1]=a[0][0]*b[0][1]+a[0][1]*b[1][1]+a[0][2]*b[2][1]+a[0][3]*b[3][1];
		res[0][2]=a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2]*b[2][2]+a[0][3]*b[3][2];
		res[0][3]=a[0][0]*b[0][3]+a[0][1]*b[1][3]+a[0][2]*b[2][3]+a[0][3]*b[3][3];

		res[1][0]=a[1][0]*b[0][0]+a[1][1]*b[1][0]+a[1][2]*b[2][0]+a[1][3]*b[3][0];
		res[1][1]=a[1][0]*b[0][1]+a[1][1]*b[1][1]+a[1][2]*b[2][1]+a[1][3]*b[3][1];
		res[1][2]=a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2]*b[2][2]+a[1][3]*b[3][2];
		res[1][3]=a[1][0]*b[0][3]+a[1][1]*b[1][3]+a[1][2]*b[2][3]+a[1][3]*b[3][3];

		res[2][0]=a[2][0]*b[0][0]+a[2][1]*b[1][0]+a[2][2]*b[2][0]+a[2][3]*b[3][0];
		res[2][1]=a[2][0]*b[0][1]+a[2][1]*b[1][1]+a[2][2]*b[2][1]+a[2][3]*b[3][1];
		res[2][2]=a[2][0]*b[0][2]+a[2][1]*b[1][2]+a[2][2]*b[2][2]+a[2][3]*b[3][2];
		res[2][3]=a[2][0]*b[0][3]+a[2][1]*b[1][3]+a[2][2]*b[2][3]+a[2][3]*b[3][3];

		res[3][0]=a[3][0]*b[0][0]+a[3][1]*b[1][0]+a[3][2]*b[2][0]+a[3][3]*b[3][0];
		res[3][1]=a[3][0]*b[0][1]+a[3][1]*b[1][1]+a[3][2]*b[2][1]+a[3][3]*b[3][1];
		res[3][2]=a[3][0]*b[0][2]+a[3][1]*b[1][2]+a[3][2]*b[2][2]+a[3][3]*b[3][2];
		res[3][3]=a[3][0]*b[0][3]+a[3][1]*b[1][3]+a[3][2]*b[2][3]+a[3][3]*b[3][3];
		return res;
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T, typename C >
	Mat4< T > operator+( const Mat4< T >& a, const Mat4< C >& b )
	{
		Mat4< T > res;
		res[0][0]=a[0][0]+b[0][0];
		res[0][1]=a[0][1]+b[0][1];
		res[0][2]=a[0][2]+b[0][2];
		res[0][3]=a[0][3]+b[0][3];

		res[1][0]=a[1][0]+b[1][0];
		res[1][1]=a[1][1]+b[1][1];
		res[1][2]=a[1][2]+b[1][2];
		res[1][3]=a[1][3]+b[1][3];

		res[2][0]=a[2][0]+b[2][0];
		res[2][1]=a[2][1]+b[2][1];
		res[2][2]=a[2][2]+b[2][2];
		res[2][3]=a[2][3]+b[2][3];

		res[3][0]=a[3][0]+b[3][0];
		res[3][1]=a[3][1]+b[3][1];
		res[3][2]=a[3][2]+b[3][2];
		res[3][3]=a[3][3]+b[3][3];
		return res;
	}

	template< typename T >
	Mat4< T >& Mat4<T>::operator+=( const Mat4< T >& a )
	{
		vv[0][0]+=a[0][0];
		vv[0][1]+=a[0][1];
		vv[0][2]+=a[0][2];
		vv[0][3]+=a[0][3];

		vv[1][0]+=a[1][0];
		vv[1][1]+=a[1][1];
		vv[1][2]+=a[1][2];
		vv[1][3]+=a[1][3];

		vv[2][0]+=a[2][0];
		vv[2][1]+=a[2][1];
		vv[2][2]+=a[2][2];
		vv[2][3]+=a[2][3];

		vv[3][0]+=a[3][0];
		vv[3][1]+=a[3][1];
		vv[3][2]+=a[3][2];
		vv[3][3]+=a[3][3];
		return *this;
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >& Mat4< T >::operator*=( const Mat4< T >& s )
	{
		( *this ) = ( *this ) * s;
		return ( *this );
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >&	 Mat4< T >::operator*=( const T& s )
	{
		Mat4< T >& res(*this);
		res[0][0] *=s;
		res[0][1] *=s;
		res[0][2] *=s;
		res[0][3] *=s;

		res[1][0] *=s;
		res[1][1] *=s;
		res[1][2] *=s;
		res[1][3] *=s;

		res[2][0] *=s;
		res[2][1] *=s;
		res[2][2] *=s;
		res[2][3] *=s;

		res[3][0] *=s;
		res[3][1] *=s;
		res[3][2] *=s;
		res[3][3] *=s;
		return (*this);
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	const Vec4< T > Mat4< T >::operator*( const Vec4< T >& p ) const
	{
		return Vec4< T >(
			vv[0][0]*p[0] + vv[0][1]*p[1] + vv[0][2]*p[2] + vv[0][3]*p[3] ,
			vv[1][0]*p[0] + vv[1][1]*p[1] + vv[1][2]*p[2] + vv[1][3]*p[3] ,
			vv[2][0]*p[0] + vv[2][1]*p[1] + vv[2][2]*p[2] + vv[2][3]*p[3] ,
			vv[3][0]*p[0] + vv[3][1]*p[1] + vv[3][2]*p[2] + vv[3][3]*p[3] );
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T, typename C >
	const Vec4< T > operator*( const Vec4< T >& v, const Mat4< C >& m )
	{
		return Vec4< T >(
			m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2] + m[3][0]*v[3] ,
			m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2] + m[3][1]*v[3] ,
			m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2] + m[3][2]*v[3] ,
			m[0][3]*v[0] + m[1][3]*v[1] + m[2][3]*v[2] + m[3][3]*v[3] );
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	const Vec3< T > Mat4< T >::operator*( const Vec3< T >& p ) const
	{
		return Vec3< T >(
			vv[0][0]*p.x + vv[0][1]*p.y + vv[0][2]*p.z + vv[0][3],
			vv[1][0]*p.x + vv[1][1]*p.y + vv[1][2]*p.z + vv[1][3],
			vv[2][0]*p.x + vv[2][1]*p.y + vv[2][2]*p.z + vv[2][3]);
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T, typename C >
	const Vec3< T > operator*( const Vec3< T >& v, const Mat4< C >& m )
	{
		return Vec3< T >(
			m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2] + m[3][0] ,
			m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2] + m[3][1] ,
			m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2] + m[3][2] );
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	bool Mat4< T >::isIdentity() const
	{
		for ( unsigned int i = 0; i < 4; i++ )
			for ( unsigned int j = 0; j < 4; j++ )
				if ( ( ( i == j ) && ( vv[i][j] != 1 ) ) || ( ( i != j ) && ( vv[i][j] !=0 ) ) )
					return false;
		return true;
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >& Mat4< T >::setIdentity()
	{
		vv[0][0] = ONE;			vv[0][1] = ZERO;	vv[0][2] = ZERO;	vv[0][3] = ZERO;
		vv[1][0] = ZERO;		vv[1][1] = ONE;		vv[1][2] = ZERO;	vv[1][3] = ZERO;
		vv[2][0] = ZERO;		vv[2][1] = ZERO;	vv[2][2] = ONE;		vv[2][3] = ZERO;
		vv[3][0] = ZERO;		vv[3][1] = ZERO;	vv[3][2] = ZERO;	vv[3][3] = ONE;
		return ( *this );
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T > Mat4< T >::get_transpose() const
	{
		Mat4< T > mat;
		for ( unsigned int i = 0; i < 4 ; i++ )
			for ( unsigned int j = 0; j < 4 ; j++ )
				mat.vv[i][j] = vv[j][i];
		return mat;
	}

	template< typename T >
	Mat4< T >& Mat4< T >::transpose()
	{
		T tmp;
		for ( unsigned int i = 0; i < 4 ; i++ )
			for ( unsigned int j = i+1; j < 4 ; j++ )
			{
				tmp = vv[i][j];
				vv[i][j] = vv[j][i];
				vv[j][i] = tmp;
			}
			return *this;
	}

	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T >&  Mat4< T >::operator+=( const Vec3< T >& vTranslation )
	{
		vv[0][3] += vTranslation.x;
		vv[1][3] += vTranslation.y;
		vv[2][3] += vTranslation.z;
		return *this;
	}

	template< typename T >
	Mat4< T >&  Mat4< T >::addTranslation( const Vec3< T >& vTranslation )
	{
		vv[0][3] += vTranslation.x;
		vv[1][3] += vTranslation.y;
		vv[2][3] += vTranslation.z;
		return *this;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4<T>& Mat4< T >::addScale( const T& sx, const T& sy, const T& sz )
	{
		vv[0][0] *= sx;
		vv[1][1] *= sy;
		vv[2][2] *= sz;
		return *this;
	}

	//=============================================================================================
	// TODO
	//=============================================================================================
	template< typename T >
	Mat4< T >& Mat4< T >::addRotationX( float fAngle )
	{
		Mat4< T > mat(fAngle, AXE_X);
		return operator*=(mat);
	}

	//=============================================================================================
	template< typename T >
	Mat4< T >& Mat4< T >::addRotationY( float fAngle )
	{
		Mat4< T > mat(fAngle, AXE_Y);
		return operator*=(mat);
	}

	//=============================================================================================
	template< typename T >
	Mat4< T >& Mat4< T >::addRotationZ( float fAngle )
	{
		Mat4< T > mat(fAngle, AXE_Z);
		return operator*=(mat);
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	bool operator!=( const Mat4< T >& a, const Mat4< T >& b )
	{
		return !( a == b );
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	bool operator==( const Mat4< T >& a, const Mat4< T >& b )
	{
		for ( unsigned int i = 0; i < 4 ; i++ )
			for ( unsigned int j = 0; j < 4 ; j++ )
				if ( a[i][j] != b[i][j] ) return false;
		return true;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	std::istream& operator>>( std::istream& stream, Mat4< T >& a )
	{
		for( unsigned int i = 0; i < 16; i++ )
			stream >> a.v[i];
		return stream;
	}


	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	std::ostream& operator<<( std::ostream& stream, const Mat4< T >& a )
	{
		for( unsigned int i = 0; i < 16; i++ )
		{
			stream << a.v[i] << " ";
			if ((!Mat4<T>::isPrintOnLine) && ((i+1)%4==0)) stream<<std::endl;
		}
		return stream;
	}



	//=============================================================================================
	//
	//=============================================================================================
	template< typename T >
	Mat4< T > Mat4< T >::get_inverse() const
	{
		return Mat4<T>(*this).inverse();
	}

	template< typename T >
	Mat4< T >& Mat4< T >::inverse()
	{
		Mat4< T >& mat( *this );
		unsigned int i,j,k;
		// Locations of pivot elements
		unsigned int  *pvt_i, *pvt_j;

		T pvt_matal;                   // matalue of current pimatot element
		T hold;                        // Temporary storage
		T determ;                      // Determinant

		determ = 1.0;

		pvt_i = new unsigned int[4];
		pvt_j = new unsigned int[4];

		for (k = 0; k < 4; k++)
		{
			// Locate k'th pivot element
			pvt_matal = mat.vv[k][k];            // Initialize for search
			pvt_i[k] = k;
			pvt_j[k] = k;
			for (i = k; i < 4; i++)
				for (j = k; j < 4; j++)
					if (fabs(mat.vv[i][j]) > fabs(pvt_matal))
					{
						pvt_i[k] = i;
						pvt_j[k] = j;
						pvt_matal = mat.vv[i][j];
					}
					// Product of pivots, gives determinant when finished
					determ *= pvt_matal;
					if (determ == 0.0)
					{
						// matrix is singular (zero determinant).
						delete[] pvt_i;
						delete[] pvt_j;
						return mat.setIdentity();
					}

					// "Interchange" rows (with sign change stuff)
					i = pvt_i[k];
					if (i != k)                     // If rows are different
						for (j = 0; j < 4; j++)
						{
							hold = -mat.vv[k][j];
							mat.vv[k][j] = mat.vv[i][j];
							mat.vv[i][j] = hold;
						}

						// "Interchange" columns
						j = pvt_j[k];
						if (j != k)                     // If columns are different
							for (i = 0; i < 4; i++)
							{
								hold = -mat.vv[i][k];
								mat.vv[i][k] = mat.vv[i][j];
								mat.vv[i][j] = hold;
							}
							// Divide column by minus pivot matalue
							for (i = 0; i < 4; i++)
								if (i != k)                   // Don't touch the pivot entry
									mat.vv[i][k] /= ( -pvt_matal) ;  // (Tricky C syntax for division)

							// Reduce the matrix
							for (i = 0; i < 4; i++)
							{
								hold = mat.vv[i][k];
								for (j = 0; j < 4; j++)
									if ( i != k && j != k )   // Don't touch pivot.
										mat.vv[i][j] += hold * mat.vv[k][j];
							}

							// Divide row by pivot
							for (j = 0; j < 4; j++)
								if (j != k)                   // Don't touch the pivot!
									mat.vv[k][j] /= pvt_matal;

							// Replace pivot by reciprocal (at last we can touch it).
							mat.vv[k][k] = 1.0f/pvt_matal;
		}

		// That was most of the work, one final pass of row/column interchange
		// to finish
		for (k = 4-1; k > 0; k--)  // Don't need to work with 1 by 1
			// corner
		{
			i = pvt_j[k-1];		 // Rows to swap correspond to pivot COLUM4
			if (i != k-1)                     // If rows are different
				for (j = 0; j < 4; j++)
				{
					hold = mat.vv[k-1][j];
					mat.vv[k-1][j] = -mat.vv[i][j];
					mat.vv[i][j] = hold;
				}

				j = pvt_i[k-1];           // Columns to swap correspond to pimatot ROW
				if (j != k-1)                     // If columns are different
					for (i = 0; i < 4; i++)
					{
						hold = mat.vv[i][k-1];
						mat.vv[i][k-1] = -mat.vv[i][j];
						mat.vv[i][j] = hold;
					}
		}
		delete[] pvt_i;
		delete[] pvt_j;
		return mat;
	}

} // namespace

#endif // ___MATH_MAT4_H__

