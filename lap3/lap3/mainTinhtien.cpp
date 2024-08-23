#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;

struct Point  {
	int x,y;
	int z ; 
	Point *next ;
};

struct Point* top = NULL;


void push(int x, int y) {
	struct Point* point ;
	point=(Point *) calloc(1,sizeof(Point));
	point->x=x ; point->y = y ; point->z = 1 ; point->next = NULL ;
	if(top == NULL){
		top = point ;
		
	}
	else {
		point->next = top;
		top = point ;
	}
}

void pop(int *x , int *y , int *z) {
	if(top != NULL){
		struct Point *point ;
		point = top;
		top = top->next ;
		*x = point->x ; *y=point->y; *z = point->z ;
		
		delete(point) ;			
	}

}

void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  , -300 , 300 , -1 , 1 );
}

void draw() {
	
	glBegin(GL_POLYGON) ;
		Point* p = top ;
		while (p != NULL) {
			glVertex3i(p->x , p->y , p->z) ;
			p = p->next ;
		}
		delete(p) ;
	glEnd();
	glFlush();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0f , 0.0f , 0.0f);
	
	draw();
}


void mouse(int button , int state , int x , int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		x = x - 300 ;
		y = 300 - y ;
		push(x , y) ;	
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		int x , y , z;
		pop(&x , &y , &z) ;
		cout << x << "-" << y << "-" << z << endl ;
	}
	glutPostRedisplay();
}

void tinhtien(int tx , int ty) {
	Point* p = top ;
	while (p != NULL) {
		p->x = p->x + tx ;
		p->y = p->y + ty ;
		p->z = 1 ;
		p = p->next ;
	}
	delete(p) ;
}

void keyboard(int key , int x , int y) {
	switch(key) {
		case GLUT_KEY_UP: {
			tinhtien(0,5) ;
			break;
		}
		case GLUT_KEY_DOWN: {
			tinhtien(0,-5) ;
			break;
		}
		case GLUT_KEY_LEFT: {
			tinhtien(-5,0) ;
			break;
		}
		case GLUT_KEY_RIGHT: {
			tinhtien(5,0) ;
			break;
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600 , 600) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Duong thang") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutSpecialFunc(keyboard) ;
	glutMainLoop();
} 
