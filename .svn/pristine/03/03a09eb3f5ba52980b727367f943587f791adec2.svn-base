
#include <Viewer.h>

#include <BVH.h>
#include <Vec3.h>

#ifndef _CAVIEWER_H
#define _CAVIEWER_H

class CAViewer : public Viewer
{
public:
	CAViewer() : Viewer(), isPhysics(false), m_bvh(NULL), m_bvhFrame(0)
	{}

	virtual ~CAViewer ();
	virtual void draw();
	virtual void help();
	virtual void init();
	virtual void animate();
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);

protected :

	bool isPhysics;

	//! mocap data
	chara::BVH*			m_bvh;
	//! mocap frame number (when mocap is used)
	int m_bvhFrame;

    //! target point for the IK
    math::Vec3f m_target;

	/// skeleton (build from the mocap-BVH data m_bvh)
	//CASkeleton*	m_skel;



};

#endif
