#include <math.h>
#include <time.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  
    glOrtho(0, 600, 0, 600, -1, 1);
}

struct LIST {
	int x , y ;
	struct LIST* next;
};

struct LIST* head = NULL;
struct LIST* last = NULL;

void push(int x , int y) {
	struct LIST* point ;
	point=(LIST *) calloc(1,sizeof(LIST));
	point->x = x ; point->y =y ; point->next = NULL ;
	if(head == NULL) {
		head = point ;
		last = point ;
	}
	else {
		last->next = point ;	
		last = point ;
	}
}
void pop(int *x , int *y) {
	struct LIST *point ;
	point = head;
	head = head->next ;
	*x = point->x ; *y=point->y;
	delete(point) ;	
}



void BoundaryFill(int x, int y, float* fillColor, float* bc){
	
	float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && 
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    	glBegin(GL_POINTS);
    		glVertex2i(x, y);
    	glEnd();
    	glFlush();
        
        push(x,y);
        
    }
}

void BoundaryFill_Stack(int x0, int y0, float* fillColor, float* bc){
	
	int x , y ;
	
	
	glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glBegin(GL_POINTS);
    	glVertex2i(x0, y0);
    glEnd();
    glFlush();
    
    
	push(x0 , y0) ;
	while(head != NULL){

		pop(&x , &y);
		BoundaryFill(x-1 , y , fillColor , bc);
		BoundaryFill(x+1 , y , fillColor , bc);
		BoundaryFill(x , y+1 , fillColor , bc);
		BoundaryFill(x , y-1 , fillColor , bc);
		
		
	}
}


void mouse(int btn, int state, int x, int y)
{
    y = 600 - y; 
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float bCol[] = {1, 0, 0};  // Boundary color (red)
        float color[] = {0, 1, 1};  // Fill color (cyan)
        BoundaryFill_Stack(x, y, color, bCol);
    }
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);  // Set drawing color to red
    glBegin(GL_LINE_LOOP);
      
        glVertex2i(300, 400);
        glVertex2i(500, 400);
        glVertex2i(600, 300);
        glVertex2i(205, 350);
		glVertex2i(200, 100);        
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}

