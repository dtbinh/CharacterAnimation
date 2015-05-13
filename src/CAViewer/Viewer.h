
#include <iostream>
#include <Camera.h>



#include <BVH.h>

#ifndef _VIEWER_H
#define _VIEWER_H

class Viewer
{
public:
	Viewer() : bLight(true), bAxe(true), bGrid(true), bBlend(false), bWireframe(false), bAnimate(false) {}
	virtual ~Viewer ();
	virtual void draw();
	virtual void init();
	virtual void animate();
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);
	virtual void processMouse(int button, int state, int x, int y);
	virtual void processActiveMotion(int x, int y);
	virtual void updateGL();
	virtual void help();

protected :

	Camera cam;
	bool bLight;           // lighting on/off
	bool bAxe;		// draw Axe X,Y,Z
	bool bGrid;		// draw Grid
	bool bBlend;
	bool bWireframe;
	bool bAnimate;
	GLfloat LightPosition[4];

};

void draw_cube();
void draw_axes(const float L=1.f);

#endif
