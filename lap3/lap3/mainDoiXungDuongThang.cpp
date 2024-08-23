#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846
using namespace std ;
int wScreen = 600 , hScreen = 600 ;
float a =  -5, b = -80 ;
float rad = (atan(a)) ;
struct Point  {
	float x,y;
	float z ;
	Point *next ;
};
struct Point* top = NULL;
void push(float x, float y) {
	struct Point* point ;
	
	point=(Point *) calloc(1,sizeof(Point));
	point->x=x ; point->y = y ;  point->z = 1 ; point->next = NULL ;
	
	
	if(top == NULL){
		top = point ;
	}
	else {
		point->next = top;
		top = point ;
	}
}

void pop(float *x , float *y , float *z) {
	if(top != NULL){
		struct Point *point ;
		point = top;
		top = top->next ;
		*x = point->x ; *y=point->y; *z = point->z ;
	
		delete(point) ;			
	}

}

void doixung(float x , float y) {
	cout  << rad  << endl ;
	float cos2x = cos(2*rad) , sin2x = sin(2*rad) ; 
	float xs = x*cos2x + y*sin2x +(b/a)*(cos2x -1 ) ;
	float ys = x*sin2x - y*cos2x +(b/a)*(sin2x) ;

	glVertex3d(xs , ys , 1) ;
	
}	


void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-wScreen/2 , wScreen/2  , -hScreen/2 , hScreen/2 , -1 , 1 );
}
void createLine() {
	int x_max = (wScreen/2) -50 , x_min = -(wScreen/2) + 50 ; 
	int y_x_max = a*x_max + b , y_x_min = a*x_min + b ;
	
	glColor3f(1.0f , 0.0f , 0.0f);
	glBegin(GL_LINE_LOOP) ;
		glVertex2i(x_max , y_x_max);
		glVertex2i(x_min , y_x_min);
	glEnd();
	glFlush();
	
}
void draw() {
	glColor3f(1.0f , 0.0f , 0.0f);
	glBegin(GL_POLYGON) ;
		Point* p = top ;
		while (p != NULL) {
			glVertex3i(p->x , p->y , p->z) ;
			p = p->next ;
		}
	glEnd();
	
	glBegin(GL_POLYGON) ;
		p = top ;
		while (p != NULL) {
			doixung(p->x , p->y) ;
			p = p->next ;
		}
		delete(p) ;
	glEnd();
	
	glFlush();
}
void drawTruc(){
	glColor3f(0.0 , 1.0 , 1.0) ;
	glBegin(GL_LINE_LOOP);
		glVertex2i(-wScreen/2 , 0) ;
		glVertex2i(wScreen/2 , 0) ;
			
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, hScreen/2) ;
		glVertex2i(0 , -hScreen/2) ;
	glEnd();
	glFlush();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	createLine() ;
	drawTruc() ;
	draw();	
	
}




void mouse(int button , int state , int x , int y) {
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		x = x - 300 ;
		y = 300 - y ;
		push(x , y) ;	
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x = x - 300 ;
		y = 300 - y ;
		
	}
	glutPostRedisplay();
}



void button(int key , int x , int y) {
	
	switch(key) {
		case GLUT_KEY_UP: {
		
			break;
		}
		case GLUT_KEY_DOWN: {
			
			break;
		}
		case GLUT_KEY_LEFT: {
			
			break;
		}
		case GLUT_KEY_RIGHT: {
				
			break;
		}
	}
}

void PhimNhan(unsigned char k, int x, int y){
	printf("k= %d",k);
	
	switch (k) { 
		
		case 8:{
			float x , y , z;
			pop(&x , &y ,&z) ;
			
			cout << x << "-" <<y << "-" << z << endl ;
			glutPostRedisplay();
			break;
		}
		
		default: 
		break; 
	}
 }

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wScreen , hScreen) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Duong thang") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutSpecialFunc(button) ;
	glutKeyboardFunc(PhimNhan);
	glutMainLoop();
} 
