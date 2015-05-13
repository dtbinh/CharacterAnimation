

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Mat4.h>
#include "Viewer.h"

using namespace chara;
using namespace std;

// Code ASCII
#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77



void draw_axes(const float L)
{
	glLineWidth(5);
	glBegin( GL_LINES );

	glColor3f( 1.f, 0.f, 0.f);
	glVertex3f( 0.f, 0.f, 0.f);
	glVertex3f( L, 0.f, 0.f);

	glColor3f( 0.f, 1.f, 0.f);
	glVertex3f( 0.f, 0.f, 0.f);
	glVertex3f( 0.f, L, 0.f);

	glColor3f( 0.f, 0.f, 1.f);
	glVertex3f( 0.f, 0.f, 0.f);
	glVertex3f( 0.f, 0.f, L);

	glEnd();
}


void draw_grid(const float L=10.f)
{
	int i;
	glLineWidth(1);
	glColor3f( 1.f, 1.f, 1.f);

	glPushMatrix();
	glTranslatef( -10*L/2, 0, -10*L/2);
	glScalef(L,L,L);

	glBegin( GL_LINES );

	for (i=0;i<=10;++i)
	{
		glVertex3f( i, 0, 0);
		glVertex3f( i, 0, 10);
	}

	for (i=0;i<=10;++i)
	{
		glVertex3f( 0, 0, i);
		glVertex3f( 10, 0, i);
	}

	glEnd();
	glPopMatrix();
}



void draw_cube()
{
	static float pt[8][3] = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1}, {0,1,0}, {1,1,0}, {1,1,1}, {0,1,1} };
	static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {1,5,6,2}, {0,4,7,3}, {3,2,6,7}, {0,4,5,1} };
	static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
	static float uv[4][2] = { {0,0}, {1,0}, {1,1}, {0,1} };
	int i,j;

	glPushMatrix();
	glTranslatef(-0.5,-0.5,-0.5);
	glBegin(GL_QUADS);
	for (i=0;i<6;i++)
	{
		glNormal3f( n[ i ][0], n[ i ][1], n[ i ][2] );
		for (j=0;j<4;j++)
		{
			glTexCoord2f( uv[j][0], uv[j][1] );
			glVertex3f( pt[ f[i][j] ][0], pt[ f[i][j] ][1], pt[ f[i][j] ][2] );
		}
	}
	glEnd();
	glPopMatrix();
}





Viewer::~Viewer()
{
}


void Viewer::help()
{
	printf("\n\nCamera :\n");
	printf("   Fleches+pageup+pagedown : bouge la camera\n");
	printf("   Ctrl+Fleches ou souris+bouton gauche: tourne la camera\n");
	printf("   Shift+Fleches: bouge le cube servant de target pour la cinématique inverse\n");
	printf("   Souris+bouton droit : avance/recule la camera\n");
	printf("   i : reinitialise la camera\n");
	printf("Lumiere : \n");
	printf("    alt+fleches ou pageup,pagedown : bouge la mumière\n");
	printf("Touches : \n");
	printf("   a : dessine les axes\n");
	printf("   b : active blend(transparence)\n");
	printf("   f : camera Fly or Trackball\n");
	printf("   l : active la lumiere\n");
	printf("   z : animation\n");
	printf("   w : wireframe\n");
	printf("-------------------------------------------------\n\n");
}

void Viewer::init()
{
	//printf("repertoire courant=");
	//system("pwd");

	glShadeModel(GL_SMOOTH);

	LightPosition[0] = 100.0f;
	LightPosition[1] = 300.0f;
	LightPosition[2] = 100.0f;
	LightPosition[3] = 1.0f;

	const float ambiant=0.02;
	const float diffus=0.98;
	const float spec=0.5;
	GLfloat LightAmbient[]  = { ambiant,ambiant,ambiant,1.f};
	GLfloat LightDiffuse[]  = {diffus,diffus,diffus, 1.0f};
	GLfloat LightSpecular[]  = { spec, spec, spec, 1.0f};
	const GLfloat light_ambient[4]	= {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat light_diffuse[4]	= {.9f, .9f, .9f, 1.0f};
	const GLfloat light_specular[4] = {0.f, 0.f, 0.f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT,	light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR,	light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,	light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,	LightPosition);

	glEnable(GL_LIGHT0 );
	glDisable(GL_LIGHT1 );
	glDisable(GL_LIGHT2 );
	glDisable(GL_LIGHT3 );
	glDisable(GL_LIGHT4 );
	glDisable(GL_LIGHT5 );
	glDisable(GL_LIGHT6 );
	glDisable(GL_LIGHT7 );
	glEnable( GL_NORMALIZE );
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.6f, 0.8f, 0.9f, 1.0f);	// The Background Color
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Indique à GL de calculer la couleur suivant la formule
	// couleur_du_buffer = alpha * couleur_polygone + (1-alpha)*couleur_du_buffer_de_fond
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	// Indique à GL d'eliminer les fragments du polygones qui sont transparents
	// (On ne garde que les pixel dont alpha>0.01, )
	glAlphaFunc(GL_GREATER, 0.01f);
	glDisable(GL_ALPHA_TEST) ;

	if (bLight) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable( GL_COLOR_MATERIAL );
	//glDisable( GL_COLOR_MATERIAL );


	glLineWidth(4);

	help();
}



void Viewer::updateGL()
{
	// Efface la couleur et le ZBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// Place la scène comme on veut
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam.setGL();

	glPushAttrib( GL_ENABLE_BIT);
	glPointSize(18);
	glColor3f(1,1,1);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	glVertex3f( LightPosition[0], LightPosition[1], LightPosition[2]  );
	glEnd();

	if (bAxe) draw_axes(10);
	if (bGrid) draw_grid(100);
	if (bAnimate) animate();

	glPopAttrib();

	draw();

	// since this is double buffered, swap the buffers to display what just got drawn.
	glutSwapBuffers();
}



void Viewer::keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case ESCAPE: // termine
		exit(1);
		break;

	case 'h':
	case 'H':
		help();
		break;

	case 'g':
	case 'G':
		bGrid = !bGrid;
		break;

	case 'a':
	case 'A':
		bAxe = !bAxe;
		break;

	case 'z':
	case 'Z':
		bAnimate = !bAnimate;
		break;

	case 'f':
	case 'F':
		if  (cam.getFlyOrTrackball()==CAMERA_TRACKBALL)
			cam.setFlyTrackballMode(CAMERA_FLY);
		else
			cam.setFlyTrackballMode(CAMERA_TRACKBALL);
		printf("Camera fly or trackball : %d\n", cam.getFlyOrTrackball());
		break;

	case 'I':
		LightPosition[0] = 5.0f;
		LightPosition[1] = 15.0f;
		LightPosition[2] = 5.0f;
		break;
	case 'i':
		cam = Camera();
		break;

	case 'w':
	case 'W':
		bWireframe = !bWireframe;
		if (bWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		printf("wireframe=%d\n", bWireframe);
		break;

	case 'b':
	case 'B': // switch the blending
		//~ printf("B/b pressed; blending is: %d\n", bBlend);
		bBlend = bBlend ? 0 : 1;              // switch the current value of blend, between 0 and 1.
		if (bBlend)
		{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST) ;
		}
		else
		{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
		}
		printf("Blending is now: %d\n", bBlend);
		break;

	case 'l':
	case 'L': // switch the lighting
		//~ printf("L/l pressed; lighting is: %d\n", bLight);
		bLight = bLight ? 0 : 1;              // switch the current value of light, between 0 and 1.
		if (bLight)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
		printf("Lighting is now: %d\n", bLight);
		break;

	default:
		printf ("Key %d pressed. No action there yet.\n", key);
		break;
	}
	updateGL();
}


void Viewer::specialKeyPressed(int key, int x, int y)
{
	const float stepR=2;
	const int stepL=1;

	if (glutGetModifiers()==GLUT_ACTIVE_CTRL)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			cam.turnUpDown( -stepR);
			break;

		case GLUT_KEY_DOWN:
			cam.turnUpDown( stepR);
			break;

		case GLUT_KEY_LEFT:
			cam.turnLeftRight( -stepR);
			break;

		case GLUT_KEY_RIGHT:
			cam.turnLeftRight( stepR);
			break;
		}
	}
	else
		if (glutGetModifiers()==GLUT_ACTIVE_ALT)
		{
			switch (key)
			{
			case GLUT_KEY_UP:
				LightPosition[0] += stepL;
				break;

			case GLUT_KEY_DOWN:
				LightPosition[0] -= stepL;
				break;

			case GLUT_KEY_LEFT:
				LightPosition[2] -= stepL;
				break;

			case GLUT_KEY_RIGHT:
				LightPosition[2] += stepL;
				break;

			case GLUT_KEY_PAGE_UP:
				LightPosition[1] += stepL;
				break;

			case GLUT_KEY_PAGE_DOWN:
				LightPosition[1] -= stepL;
				break;
			}
			printf("Light position= %f %f %f\n", LightPosition[0], LightPosition[1], LightPosition[2]);
		}
		else
		{
			switch (key)
			{
			case GLUT_KEY_PAGE_UP:
				cam.translate( UP);
				break;

			case GLUT_KEY_PAGE_DOWN:
				cam.translate( DOWN);
				break;
			case GLUT_KEY_UP:
				cam.translate( FRONT);
				break;

			case GLUT_KEY_DOWN:
				cam.translate( BACK);
				break;

			case GLUT_KEY_LEFT:
				cam.translate( LEFT);
				break;

			case GLUT_KEY_RIGHT:
				cam.translate( RIGHT);
				break;
			default:
				break;
			}
		}
		updateGL();
}



void Viewer::animate()
{
}


void Viewer::processMouse(int button, int state, int x, int y)
{
	int specialKey;
	specialKey = glutGetModifiers();

	cam.startMove( CAMERA_STOP, x, y);

	if ((state == GLUT_DOWN)) // && (specialKey == GLUT_ACTIVE_ALT))
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			cam.startMove( CAMERA_ROTATION, x, y);
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			cam.startMove( CAMERA_TRANSLATION, x, y);
		}
	}
	//updateGL();
}

void Viewer::processActiveMotion(int x, int y)
{
	cam.move( x, y);
	//updateGL();
}


void Viewer::draw()
{

}





