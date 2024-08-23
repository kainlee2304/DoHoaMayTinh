#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;

int x1s=0,x2s=0,y1s=0,y2s=50 ;
int index = 0 ;

void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  , -300 , 300 , -1 , 1 );
}

void draw8point(int xc , int yc , int x , int y){
	glBegin(GL_POINTS) ;
			glVertex2i(xc+x,yc+y) ;
			glVertex2i(xc+y,yc+x) ;
			glVertex2i(xc-x,yc+y) ;
			glVertex2i(xc-y,yc+x) ;
			glVertex2i(xc+x,yc-y) ;
			glVertex2i(xc+y,yc-x) ;
			glVertex2i(xc-x,yc-y) ;
			glVertex2i(xc-y,yc-x) ;
	
		glEnd();
}

void CycleMidPoint1(int xc , int yc , int r ){
	double x , y , p , const1 , const2 ;
	x = r ; y = 0 ; p = 5/4-r;  
	
	while (y <= x){
		
		draw8point(xc , yc , x , y) ;
		
		
			if(p < 0){
				const1 = 2*y+3 ;
				p+=const1 ;
			}
			else {
				const2 =  2*(y-x) + 5 ;
				p+=const2;
				x-- ;
			}
			y++ ;
		
	}
}
void CycleMidPoint2(int xc , int yc , int r ){
	double x , y , p , const1 , const2 ;
	x = 0 ; y = -r ; p = 5/4-r;  
	
	while (x <= -y){
		
		draw8point(xc , yc , x , y) ;
		
		
			if(p < 0){
				const1 = 2*x+3 ;
				p+=const1 ;
			}
			else {
				const2 =  2*(y+x) + 5 ;
				p+=const2;
				y++ ;
			}
			x++ ;
		
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0f , 0.0f , 0.0f);
	
	int r = sqrt(pow(x1s-x2s,2) + pow(y1s-y2s , 2)) ;
	
	CycleMidPoint1(x1s,y1s, r);
	
	glFlush();
}


void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout << "x=" << x << "y=" << y << endl ;
		xtest = x-300;
		ytest = 300 - y  ;
		
		if(index == 0){
			x1s = xtest ;
			y1s = ytest ;
			index = 1 ;
		}
		else {
			x2s = xtest ;
			y2s = ytest ;
			index = 0 ;
		}
		
		glutPostRedisplay();
	}
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
	glutMainLoop();
} 
