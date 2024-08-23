#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;

int x1s , y1s ;
int a = 100 ; int b = 50 ;
void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  ,  -300 , 300 , -1 , 1 );
}


void draw4point(int xc , int yc , int x , int y){
	glBegin(GL_POINTS) ;
		glVertex2i(xc+x,yc+y) ;
		glVertex2i(xc-x,yc+y) ;
		glVertex2i(xc+x,yc-y) ;
		glVertex2i(xc-x,yc-y) ;
	glEnd();
}

void ElipBresenham(int xc , int yc , int a , int b) {
	int x,y,a2,b2,x0,y0,p,consts ;
	a2 = pow(a , 2) ; b2= pow(b,2);
	x0=a2/sqrt(a2+b2) ; y0 = b2/sqrt(a2 + b2) ;
	
	//Nhánh 1
	p = b2-a2*b+a2/4 ;
	x=0;y=b;
	while(x <= x0){
		draw4point(xc , yc , x , y);
		if(p < 0){

			consts = (2*x+3)*b2 ;
			p+=consts ;
		}
		else {

			consts = (2*x+3)*b2-2*a2*(y-1) ;
			p+=consts ;
			y--;
		}
		x++;
	}
	// Nhánh 2
	x=a; y=0; p= a2 - b2*a + b2/4;
	while (y<=y0){
		draw4point(xc , yc , x, y) ;
		if (p<0 ){
			consts = a2*(2*y+3) ; 
			p+=consts;	
		} 
		else{
			consts = a2*(2*y+3) - 2* b2 * (x-1) ; 
			p+=consts;
			x--;

		}
		y++;

	}
	 
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0f , 0.0f , 0.0f);
	
	ElipBresenham(x1s,y1s,a,b);	
	

	glFlush();
}


void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout << "x=" << x << "y=" << y << endl ;
		xtest = x-300;
		ytest = 300 - y  ;
		
			x1s = xtest ;
			y1s = ytest ;
			
		

		
		glutPostRedisplay();
	}
}

void PhimNhan(unsigned char k, int x, int y){
	printf("k= %d",k);
	
	switch (k) { 
		
		case 61: {
			a+=5;
			glutPostRedisplay();
			break;
		}
		case 45: {
			a-=5;
			glutPostRedisplay();
			break;
		}
		case 93: {
			b+=5 ;
			glutPostRedisplay();
			break;
		}
		case 111: {
			b-=5 ;
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
	glutInitWindowSize(600 , 600) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Elip") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutKeyboardFunc(PhimNhan);
	glutMainLoop();
} 
