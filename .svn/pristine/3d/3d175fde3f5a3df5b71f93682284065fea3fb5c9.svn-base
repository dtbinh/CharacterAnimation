#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Mat4.h>
#include <CAViewer.h>



CAViewer viewer;


//! A appeller juste avant la boucle principale (Main Loop)
void GLInit(GLsizei Width, GLsizei Height)
{
	viewer.init();
}

//! Quand la fenetre est 'resizée'
void GLResize(GLsizei Width, GLsizei Height);


//! The main drawing function
void GLUpdate(void)
{
	viewer.updateGL();
}

//! Quand une touche est pressée
void keyPressed(unsigned char key, int x, int y)
{
	viewer.keyPressed(key,x,y);
}

//! The function called whenever a normal key is pressed
void specialKeyPressed(int key, int x, int y)
{
	viewer.specialKeyPressed(key,x,y);
}

void processMouse(int button, int state, int x, int y)
{
	viewer.processMouse(button,state,x,y);
}

void processMouseActiveMotion(int x, int y)
{
	//    printf("processMouseActiveMotion\n");
	//camMove( cam, x, y);
	viewer.processActiveMotion(x,y);
	GLUpdate();
}

void processMousePassiveMotion(int x, int y)
{
	//printf("processMousePassiveMotion\n");
	GLUpdate();
}

void GLAnimate()
{
	viewer.animate();
}

//! Quand la fenetre est 'resizée'
GLvoid GLResize(GLsizei Width, GLsizei Height)
{
	if (Height==0) Height=1;

	glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f,(GLfloat)Width/(GLfloat)Height,1.f,10000.0f);

	glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char **argv)
{
	int window;		// glut windows

	// Initialize GLUT
	glutInit(&argc, argv);

	/* Select type of Display mode:	 Double buffer	 RGBA color	 Depth buffer	 Alpha blending */
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
	//glutInitDisplayMode(GLUT_RGB);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// demande une fenetre de 640 x 480 à la position 0,0
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	// Creer une fenetre
	window = glutCreateWindow("CHARA");

	// La fonction d'affichage est GLDraw
	glutDisplayFunc(&GLUpdate);

	// Plein écran
	//glutFullScreen();

	// Quand il n'y a aucun évenement, on affiche quand même la scène
	//glutIdleFunc(&GLUpdate);

	// Quand la fenetre change de taille
	glutReshapeFunc(&GLResize);

	// quand une touche est pressee
	glutKeyboardFunc(&keyPressed);

	// quand une touche speciale est pressee
	glutSpecialFunc(&specialKeyPressed);

	// mouse
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMousePassiveMotion);
	//    glutEntryFunc(processMouseEntry);


	// Notre init:
	GLInit(640, 480);

	// La boucle principale
	glutMainLoop();

	return 0;
}
