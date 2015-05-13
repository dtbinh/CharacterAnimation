

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "CAViewer.h"
#include <BVH.h>
#include <BVHChannel.h>
#include <Mat4.h>
#include <Quaternion.h>

using namespace chara;
using namespace std;


void CAViewer::help()
{
	printf("Animation:\n");
	printf("   n: Next character pose\n");
	printf("   b: Back(Previous) character pose");
	printf("   shift+arrows: Move the target point");
	Viewer::help();
}


CAViewer::~CAViewer()
{
}



void CAViewer::init()
{
	Viewer::init();

	//std::string fn_front = "G:/alex/code/CharAnim_m2pro/data/OneArm.bvh";
	//std::string fn_front = "/home/pers/alexandre.meyer/code/CharAnim_m2pro/data/OneArm.bvh";
	std::string fn_front = "../data/OneArm.bvh";

	if (fn_front!="")
	{
		std::string current_file( fn_front );
		printf("%s\n", current_file.c_str());
		m_bvh = new BVH(current_file.c_str(), true );

		cout<<"BVH"<<endl;
		cout<<*m_bvh<<endl;
		cout<<"------------"<<endl;
	}
	else cout<<"No BVH\n";

    m_target.set( 10, 10, 0);

//    // TEST quaternion (ne sert à rien)
//    math::Quaternion q1( math::Vec3f(0,0,1),  0.08f);
//    math::Quaternion q2( math::Vec3f(0,0,1),  0.04f);
//    math::Quaternion qr;
//    qr = math::Quaternion::slerp( q1, q2, 0.5f);
//    math::Vec3f v;
//    float a;
//    qr.getAxisAngle(v,a);
//    cout<<"v="<<v<<"  angle="<<a<<endl;
//
//
//    math::QuaternionD qq1( math::Vec3d(0,0,1),  0.08);
//    math::QuaternionD qq2( math::Vec3d(0,0,1),  0.04);
//    math::QuaternionD qqr;
//    qqr = math::QuaternionD::slerp( qq1, qq2, 0.5);
//    math::Vec3d vv;
//    double aa;
//    qqr.getAxisAngle(vv,aa);
//    cout<<"vv="<<vv<<"  angleD="<<aa<<endl;

}



void CAViewer::draw()
{
	glPushMatrix();
	//if (m_skel) m_skel->render();

    glPushMatrix();
    glTranslatef( m_target.x, m_target.y, m_target.z);
    glColor3f( 1, 1, 0);
    draw_cube();
    glPopMatrix();

	glPopMatrix();
}



void CAViewer::keyPressed(unsigned char key, int x, int y)
{
	bool handled = false;
	if ((key=='n'))
	{
		++m_bvhFrame;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if ((key=='b'))
	{
		--m_bvhFrame;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if (key=='w')
	{
		bWireframe = !bWireframe;
		if (bWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		handled = true;
	}

	if (!handled)
	{
		Viewer::keyPressed(key,x,y);
	}
	updateGL();
}


void CAViewer::specialKeyPressed(int key, int x, int y)
{
	bool handled = false;

	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			m_target.y += 1;
			handled=true;
			break;
		case GLUT_KEY_DOWN:
			m_target.y -= 1;
			handled=true;
			break;
		case GLUT_KEY_LEFT:
			m_target.x -= 1;
			handled=true;
			break;
		case GLUT_KEY_RIGHT:
			m_target.x += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_UP:
			m_target.z += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_DOWN:
			m_target.z -= 1;
			handled=true;
			break;
		}
	}


	if (!handled)
	{
        Viewer::specialKeyPressed(key,x,y);
	}
	updateGL();
}



void CAViewer::animate()
{
	if (m_bvh)
	{
		++m_bvhFrame;
		if (m_bvhFrame>=m_bvh->getNumFrame()) m_bvhFrame=0;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
	}
}



