#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846
using namespace std ;

struct Point  {
	int x,y;
	int z ;
	Point *next ;
};
int size = 0 ; 
int goc = 0 ;
int diemxoay = 1 ;
struct Point* top = NULL;

Point* point_rotate = NULL ;


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
	size++ ;
}

void pop(int *x , int *y , int *z) {
	if(top != NULL){
		struct Point *point ;
		point = top;
		top = top->next ;
		*x = point->x ; *y=point->y; *z = point->z ;
	
		delete(point) ;			
		size-- ;
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
	float size = 5.0f ;
	glPointSize(size);
	if(point_rotate != NULL){
		glBegin(GL_POINTS);
			glColor3f(0.0,0.0,0.0);
		
			glVertex3i(point_rotate->x , point_rotate->y,point_rotate->z);
		glEnd();
		glFlush();
	}
}


void mouse(int button , int state , int x , int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		x = x - 300 ;
		y = 300 - y ;
		push(x , y) ;	
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		int x , y , z ;
		pop(&x , &y , &z) ;
		cout << x << "-" << y << "-" << z << endl ;
	}
	glutPostRedisplay();
}

Point* swapPointRotate(int index){
	
	Point *point = top ;
	if(index <= size){
		index = size - index ;
		while(index > 0){
			point = point->next ;
			index-- ;
		}
	}
	
	return point ;
	
}
void xoay() {
	float rad = goc * M_PI / 180 ;
	cout << "goc= " << goc << endl ;
	cout << "rad= " << rad << endl << "========" << endl ;
	if(point_rotate == NULL){
		point_rotate = top ;
	}
	else {
		point_rotate = swapPointRotate(diemxoay) ;
		
	}
	
	int tx = point_rotate->x , ty = point_rotate->y;
	int x , y  ;
	Point* p = top ;
	
	while (p != NULL) {
		if(p->x != point_rotate->x || p->y != point_rotate->y){
			x = p->x ; y = p->y ;
			p->x = x*cos(rad) - y*sin(rad) + (1-cos(rad))*tx + ty*sin(rad)   ; //(x-tx)*cos(rad) - (y-ty)*sin(rad) + tx
			p->y = x*sin(rad) + y*cos(rad) + (1-cos(rad))*ty - tx*sin(rad)  ; //(x-tx)*sin(rad) + (y-ty)*cos(rad) + ty
			p->z = 1 ;
		}
		p = p->next ;
	}
	delete(p) ;
	
}

void buttonrotate(int key , int x , int y) {
	
	switch(key) {
		
		case GLUT_KEY_LEFT: {
			goc+=1;
			if(goc > 360 ) goc = 0 ;
			xoay() ;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT: {
			goc-=1 ;
			if(goc < 0 ) goc = 360 ;
			xoay() ;
			glutPostRedisplay();
				
			break;
		}
	}
}

void PhimNhanChonGocXoay(unsigned char k, int x, int y){
	printf("k= %d",k);
	
	switch (k) { 
		case 49 :	diemxoay=1;glutPostRedisplay(); 
					break; 
		case 50 :	diemxoay = 2 ;glutPostRedisplay();
					break; 
		case 51 :	diemxoay = 3 ;glutPostRedisplay();
					break; 
		case 52 :	diemxoay = 4 ;glutPostRedisplay();
					break; 
		case 53 :	diemxoay = 5 ;glutPostRedisplay();
					break; 
		case 54 :	diemxoay = 6 ;glutPostRedisplay();
					break; 
		case 55 :	diemxoay = 7 ; glutPostRedisplay();
					break; 
		case 56 :	diemxoay = 8 ; glutPostRedisplay();
					break; 
		case 57 :	diemxoay = 9  ;glutPostRedisplay();
					break; 
		
		default: 
					break; 
	}
 }

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600 , 600) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Phep xoay") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutSpecialFunc(buttonrotate) ;
	glutKeyboardFunc(PhimNhanChonGocXoay);
	glutMainLoop();
} 
