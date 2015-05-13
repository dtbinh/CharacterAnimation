#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Vec3.h"
#define _USE_MATH_DEFINES
#include <math.h>

enum Camera_FlyTrackball { CAMERA_FLY=0, CAMERA_TRACKBALL=1 };
enum DIR { FRONT, BACK, LEFT, RIGHT, UP, DOWN };
enum CAMERA_MODE { CAMERA_STOP, CAMERA_ROTATION, CAMERA_TRANSLATION };

//! A camera is defined by a position and 2 angles of rotations (defining the orientation)
class Camera
{
public:
	Camera(const Camera_FlyTrackball ft=CAMERA_TRACKBALL)
	{
		pos.x = 0;
		pos.y = 20;
		pos.z = 100;
		rotUp = 0;
		rotLeft = 0;
		mode = 0;
		flyOrTrackball = ft;
	}

	inline float rad(const float a)
	{
		return a*2.0f*M_PI/360.f;
	}


	inline void computeDirFront( math::Vec3f& dir)
	{
		if (flyOrTrackball==CAMERA_FLY)
		{
			float a = rad(rotUp);
			float b = rad(rotLeft);
			int signz=(pos.z>0)?1:-1;
			int signy=(pos.y>0)?1:-1;
			dir.set( sin(b), -signz*signy*sin(a)*cos(b), -cos(a)*cos(b));
		}
		else
		{
			dir.set( -pos.x, -pos.y, -pos.z);
			dir.normalize();
		}
	}

	inline void setFlyTrackballMode(const Camera_FlyTrackball m)
	{
		pos.x = 0;
		pos.y = 2;
		pos.z = 10;
		rotUp = 0;
		rotLeft = 0;
		mode = 0;
		flyOrTrackball = m;
	}

	inline void setGL()
	{
		glMatrixMode( GL_MODELVIEW);

		if (flyOrTrackball==CAMERA_FLY)
		{
			glRotatef( rotUp, 1.0f, 0, 0);
			glRotatef( rotLeft, 0, 1.0f, 0);
			glTranslatef( -pos.x, -pos.y, -pos.z);
		}
		else
		{
			glTranslatef( -pos.x, -pos.y, -pos.z);
			glRotatef( rotUp, 1.0f, 0, 0);
			glRotatef( rotLeft, 0, 1.0f, 0);
		}
	}

	inline void turnUpDown(const float stepR=2.f)
	{
		rotUp += stepR;
	}
	inline void turnLeftRight(const float stepR=2.f)
	{
		rotLeft += stepR;
	}


	inline void translate(const DIR where, const float c=10.f)
	{
		math::Vec3f dir, up, right;

		computeDirFront( dir);
		if (dir.y>=1.f)
			up.set(1, 0, 0);
		else
			up.set(0, 1, 0);
		right = dir^up;

		math::Vec3f tr(0,0,0);
		switch (where)
		{
		case UP:
			tr = c*up;
			break;

		case DOWN:
			tr = -c*up;
			break;

		case FRONT:
			tr = c*dir;
			break;

		case BACK:
			tr= -c*dir;
			break;

		case LEFT:
			tr=-c*right;
			break;

		case RIGHT:
			tr=c*right;
			break;
		}
		pos += tr;
	}


	inline void startMove( const CAMERA_MODE _mode, const int x, const int y)
	{
		mode = _mode;
		mx = x;
		my = y;
	}

	inline void move( const int x, const int y)
	{
		if (mode==CAMERA_TRANSLATION)
		{
			if (y>my) translate( BACK);
			else translate( FRONT);
		}
		else if (mode==CAMERA_ROTATION)
		{
		    const float c=0.2f;
			//        if (abs(y-my)>3)
			turnUpDown( c*(y-my));
			//        if (abs(x-mx)>3)
			turnLeftRight( c*(x-mx));
		}
		mx = x;
		my = y;
	}

	Camera_FlyTrackball getFlyOrTrackball() const	{ return flyOrTrackball; }

protected:
	math::Vec3f pos;
    float rotLeft;
    float rotUp;
    int mode;       // 0=neutral, 1=rotation mode, 2=translation mode
    Camera_FlyTrackball flyOrTrackball;
    int mx,my;      // mouse position
};




#endif // CAMERA_H_INCLUDED
