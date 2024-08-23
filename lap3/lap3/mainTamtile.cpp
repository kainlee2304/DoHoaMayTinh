#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846
using namespace std ;
int wScreen = 600 , hScreen = 600 ;
struct Point  {
	double x,y;
	double z ;
	Point *next ;
};
double tx = 0 , ty = 0 , Sx = 1, Sy = 1 ; 

struct Point* top = NULL;

void push(double x, double y) {
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

void pop(double *x , double *y , double *z) {
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
	glOrtho(-wScreen/2 , wScreen/2  , -hScreen/2 , hScreen/2 , -1 , 1 );
}

void draw() {
	glColor3f(1.0f , 0.0f , 0.0f);
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
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	
	glColor3f(0.0 , 0.0 ,0.0 );
	float size = 5.0 ;
	glPointSize(size) ;
	glBegin(GL_POINTS);
		glVertex2i(tx , ty) ;
	glEnd();
	glFlush();
	
	
	drawTruc() ;
	draw();	
	
}

void Tam_Ti_Le(double tx , double ty , double Sx , double Sy){
	Point *p  = top ;
	double x , y , z;
	while(p != NULL){
		x = p->x ; y = p->y  ; z = p->z ;
		p->x = x*Sx + (1-Sx)*tx ; // (x-tx)*Sx + tx
		p->y = y*Sy + (1-Sy)*ty ; // (y-tx)*Sy + ty
		p->z = 1 ;
		p = p->next ;
	}
	
	delete(p) ;
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
		tx = x ;
		ty = y ;
	}
	glutPostRedisplay();
}



void button(int key , int x , int y) {
	
	switch(key) {
		case GLUT_KEY_UP: {
			Tam_Ti_Le(tx , ty , Sx , -Sy) ;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN: {
			Tam_Ti_Le(tx , ty , Sx , -Sy) ;			
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT: {
			Tam_Ti_Le(tx , ty , -Sx , Sy) ;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT: {
			Tam_Ti_Le(tx , ty , -Sx , Sy) ;
			glutPostRedisplay();
				
			break;
		}
	}
}

void PhimNhan(unsigned char k, int x, int y){
	printf("k= %d",k);
	
	switch (k) { 
		case 27: { // esc
			Sx = 1;
			Sy = 1 ;
			tx = 0;
			ty = 0 ;
			Tam_Ti_Le(tx , ty , Sx , Sy) ;
			glutPostRedisplay();
			
			break;
		}
		case 61: {
			Sx+=0.01;
			Sy+=0.01 ;
			Tam_Ti_Le(tx , ty , Sx , Sy) ;
			glutPostRedisplay();
			break;
		}
		case 45: {
			Sx-=0.01;
			Sy-=0.01 ;
			Tam_Ti_Le(tx , ty , Sx , Sy) ;
			glutPostRedisplay();
			break;
		}
		case 8:{
			double x , y , z;
			pop(&x , &y ,&z) ;
			Tam_Ti_Le(tx , ty , 1 , 1) ;
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
