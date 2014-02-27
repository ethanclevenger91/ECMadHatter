/*
Assignment Five - 3D Intro
Author: Ethan Clevenger (building on code from Tim Urness)
Proposed points: 10/10
*/

#include <stdlib.h>
#if defined(__APPLE__)
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

#include<iostream>
#include<vector>
#include<math.h>
#include "stdafx.h"
#include "glm.h"

using namespace std;

#define WIDTH 600
#define HEIGHT 600
#define TRUE 1
#define FALSE 0

int shape =0;
int projection = 0;

int right_button_down = FALSE;
int left_button_down = FALSE;
int shift_button_down = FALSE;
double z_distance = 10;

GLMmodel *bunny_ptr;

//Using these to make a house later
GLfloat vertices[] = {4,4,4, 4,4,-4, 0,8,-4, 0,8,4};
GLfloat leftSide[] = {-4,4,4, -4,4,-4, 0,8,-4, 0,8,4};
GLfloat leftWall[] = {-4,4,4, -4,4,-4, -4,-4,-4, -4,-4,4};
GLfloat rightWall[] = {4,4,4, 4,4,-4, 4,-4,-4, 4,-4,4};
GLfloat theFloor[] = {-4,-4,-4, 4,-4,-4, 4,-4,4, -4,-4,4};

int previous_mouseX;
int previous_mouseY;
int theta = 1;
bool goRight = true;
double view_rotX, view_rotY, light_moveX = 1.0, light_moveY = 1.0;
double zoom = 20.0;

GLfloat red_color[] = {1.0, 0.0, 0.0, 1.0};
GLfloat green_color[] = {0.0, 1.0, 0.0, 1.0};
GLfloat white_color[] = {1.0, 1.0, 1.0, 1.0};
GLfloat shininess[] = {50.0};
GLfloat black_color[] = {0.0, 0.0, 0.0, 0.0};
GLfloat skin_color[] = {.851, .855, .612, 1};
GLfloat skinShininess[] = {100};

GLfloat goldAmbient[] = {.24725, .1995, .0745, 1.0};
GLfloat goldDiffuse[] = {.75164, .60648, .22648, 1.0};
GLfloat goldSpecular[] = {.628281, .555802, .366065, 1.0};
GLfloat goldExponent[] = {51.2};

GLfloat jadeAmbient[] = {.135, .2225, .1575, .95};
GLfloat jadeDiffuse[] = {.54, .89, .63, .95};
GLfloat jadeSpecular[] = {.316228, .316228, .316228, .95};
GLfloat jadeExponent[] = {12.8};

GLfloat light_position[] = {light_moveX, light_moveY, 1.0, 0.0};

//function prototypes
void display();
void reshape(int w, int h);
void init(void);
void mouse_moved(int x, int y);
void mouse(int button, int state, int x, int y);
void key(unsigned char key, int x, int y);

//timer updates the angle at which tea is being poured
void timer(int extra) {
	if(goRight == true)
	{
		theta += 1;
	}
	else
	{
		theta -= 1;
	}
	if(theta < -35)
	{
		goRight = true;
	}
	else if(theta > 0)
	{
		goRight = false;
	}
	glutTimerFunc(extra, timer,extra);
	glutPostRedisplay();
}

void display(void) {
	/*clear all pixels*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	/*set color to white*/
	glColor3f(1.0,1.0,1.0);
	
	
	glPushMatrix();
	{
		/*code to allow 3D navigation*/
		gluLookAt(0,0,z_distance,0,0,0,0,1,0);
		glRotated(view_rotX,1,0,0);
		glRotated(view_rotY,0,1,0);

		glMaterialfv(GL_FRONT, GL_AMBIENT, red_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red_color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white_color);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

		glPushMatrix();
		{
			glPushMatrix();
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDiffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpecular);
				glMaterialfv(GL_FRONT, GL_SHININESS, jadeExponent);
				glTranslated(5, -5, 0);
				glmDraw(bunny_ptr, GLM_SMOOTH | GLM_MATERIAL);
				glPopMatrix();
			}
			glPopMatrix();
		}
		/*The Mad Hatter*/
		glMaterialfv(GL_FRONT, GL_AMBIENT, skin_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, skin_color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, skin_color);
		glMaterialfv(GL_FRONT, GL_SHININESS, skinShininess);
		glTranslated(-3.5, 4.3, 0);
		glRotated(10, 1, 1, 1);
		glPushMatrix();
		{
			glScaled(1, 1.2, 1);
			glutSolidSphere(1.5, 30, 30);
			glPopMatrix();
		}
		glPushMatrix();
		{
			glTranslated(0, -3.5, 0);
			glutSolidCube(4.5);
			glPushMatrix();
			{
				glTranslated(-1, -4.5, .2);
				glRotated(-10, 0, 0, 1);
				glScaled(.5, 1.4, .7);
				glutSolidCube(3);
				glPopMatrix();
			}
			glPushMatrix();
			{
				glTranslated(1, -4.5, .2);
				glRotated(10, 0, 0, 1);
				glScaled(.5, 1.4, .7);
				glutSolidCube(3);
				glPopMatrix();
			}
			glPushMatrix();
			{
				glTranslated(4, 1, .2);
				glRotated(15, 0, 0, 1);
				glScaled(1.4, .3, .8);
				glutSolidCube(3);
				glPopMatrix();
			}
			glPushMatrix();
			{
				glTranslated(-4, 0, .2);
				glRotated(25, 0, 0, 1);
				glScaled(1.4, .3, .8);
				glutSolidCube(3);
				glPopMatrix();
			}
			glPushMatrix();
			{
				glTranslated(7.4, 1, 0);
				glRotated(theta, 0, 0, 1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
				glMaterialfv(GL_FRONT, GL_SHININESS, goldExponent);
				glutSolidTeapot(1.3);
				glPopMatrix();
			}
			glPushMatrix();
				glTranslated(0, 5.05, 0);
				glMaterialfv(GL_FRONT, GL_AMBIENT, green_color);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, green_color);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white_color);
				glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
				glPushMatrix();
				{
					glRotated(90, 1, 0, 0);
					glutSolidTorus(1, 2, 2, 30);
					glPopMatrix();
				}
				glTranslated(0,1.5,0);
				glScaled(1, 1.5, 1);
				glutSolidCube(2);
				glPopMatrix();
			glPopMatrix();
		}
		glPopMatrix();
	}	
	glutSwapBuffers();
}


void reshape(int w, int h) {
	/*prevents user from reshaping window*/
	glutReshapeWindow(WIDTH, HEIGHT);                 
}


void init(void) {
	/*set clearing (background) color*/
	glClearColor(0.0, 0.0, 0.0, 0.0);

	
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambient_light[] = {0.0, 0.0, 0.0, 1.0};

	/*set up lighting parameters*/
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    
	/*enable lighting and depth*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	/*initialize viewing values*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (projection == 0) {
		glOrtho(-10, 10, -10, 10, 2, 100);
	}
	else {
		glFrustum(-1,1,-1,1,1,30);
		//gluPerspective(60.0, 1.0, 1.5, 30);
		
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0,0,zoom,0,0,0,0,1,0);
}


void mouse(int button, int state, int x, int y) {
	//left mouse down rotation
	//right mouse down for zoom
	
	int mod = glutGetModifiers();

	//keep track of where user pressed down
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		previous_mouseX = x;
		previous_mouseY = y;
		left_button_down = TRUE;
	} 
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		previous_mouseX = x;
		previous_mouseY = y;
		right_button_down = TRUE;
	}      
    
	else {
		left_button_down = FALSE;
		right_button_down = FALSE;
	}
	
	
	glutPostRedisplay();
}

void mouse_moved(int x, int y) {
	
	double thetaY, thetaX, distZ;
	double lightX, lightY;
	//left mouse effects rotation
	if (left_button_down == TRUE) {
		thetaY = 360.0 * (x-previous_mouseX)/WIDTH;
		thetaX = 360.0 * (y-previous_mouseY)/HEIGHT; 
		view_rotX += thetaX;
		view_rotY += thetaY;
		previous_mouseX = x;
		previous_mouseY = y;
	}	
    
	//right mouse zoom
	else if (right_button_down) {
		distZ = 10.0*(y-previous_mouseY)/HEIGHT;
		previous_mouseX = x;
		previous_mouseY = y;
		z_distance += distZ;
	}
	glutPostRedisplay();
    
}


void key(unsigned char key, int x, int y) {
	/* 
	 press escape or q to quit
	 press 'o' for orthographic
     'p' for perspective
	 */
	 
	switch(key) {
		case 'q':
		case 27:
			exit(0);
			break;
		case 'o' :
			projection = 0;
			init();
			break;
		case 'p' :
			projection = 1;
			init();
			break;
		default:
			return;            
	}     
    
    glutPostRedisplay();
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Drake CS 147");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_moved);
	glutKeyboardFunc(key);
	glutTimerFunc(0, timer, 12);
	if (!bunny_ptr)
	{
		bunny_ptr = glmReadOBJ("bunny.obj");
		if (!bunny_ptr) exit(0);
		glmUnitize(bunny_ptr);
		glmFacetNormals(bunny_ptr);
		glmVertexNormals(bunny_ptr, 90.0);
	}
	glutMainLoop();
}