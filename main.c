#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>

void myInit(int*, char**);
void mouseManager(int, int, int, int);
void displayFunc(void);
float **prodmat(float **m1, float **m2, int p, int q, int r);
void  makeMatrix(float **, float **);

GLint xc, yc, radius;
int i=0;
float **A, **c, **points, u, x, y;
int drawCurve=0, next=-3;

void displayFunc(void){
    float u;
    int j, k;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    for(j=1; j<=i; j++)
        glVertex2i((int)points[j][1], (int)points[j][2]);
    
    if(drawCurve){
        glColor3f(1.0f,0.0f,0.0f); // set the drawing color to red(Bezier)
        for(j=0; j<= next; j+=3){
            if((j+4)<=i){ //    makeMatrix(c, points+i-4);
                makeMatrix(c, points+j);
                
                for(u=0.001; u<1; u+=0.001){
                    x=c[1][1] + c[2][1]*u + c[3][1]*u*u + c[4][1]*u*u*u;
                    y=c[1][2] + c[2][2]*u + c[3][2]*u*u + c[4][2]*u*u*u;
                    
                    glVertex2i((int)(x+0.5),(int)(y+0.5));
                }
            }
        }
    }
    
    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    int i;
    
    myInit(&argc, argv);
    
    c=(float **) malloc(5*sizeof(float *));
    for(i=1; i<=4; i++)
        c[i]=(float *) malloc(5*sizeof(float));
    points=(float **) malloc(100*sizeof(float *));
    for(i=1; i<=99; i++)
        points[i]=(float *) malloc(3*sizeof(float));
    
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseManager);
    
    glutMainLoop();               //infinite loop
}

void myInit(int *argc, char **argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(100, 150);
    glutCreateWindow(argv[0]);
    
    glClearColor(1.0,1.0,1.0,0.0);  // Set clear color to white
    glColor3f(1.0f,0.0f,0.0f);      // set the drawing color to red
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);   // virtual camera
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,640.0);
}

void mouseManager(int button, int state, int x, int y){
    y = 640 - y;
    
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                if(drawCurve){
                    drawCurve=0;
                    next=-3;
                    i=0;
                }
                i++;
                points[i][1]=x;
                points[i][2]=y;
            }
            break;
            /*
             case GLUT_MIDDLE_BUTTON:
             if(state==GLUT_DOWN)
             eyeZ-=0.4;
             break;
             */
        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN){
                drawCurve=1;
                next+=3;
            }
            break;
        defaut:
            ;
    }
    displayFunc();
}


float **prodmat(float **m1, float **m2, int p, int q, int r)
{
    int i, j, k;
    float **res;
    
    res=(float **) malloc((p+1)*sizeof(float *));
    
    for(i=1; i<=p; i++){
        res[i]=(float *) malloc((r+1)*sizeof(float));
        for(j=1; j<=r; j++)
        {
            res[i][j]=0.0;
            for(k=1; k<=q; k++)
                res[i][j]=res[i][j] + (m1[i][k]*m2[k][j]);
        }
    }
    return(res);
}

void makeMatrix(float **c, float **points){
    
    c[1][1]=points[1][1];
    c[1][2]=points[1][2];
    
    c[2][1]=3*(points[2][1]-points[1][1]);
    c[2][2]=3*(points[2][2]-points[1][2]);
    
    c[3][1]= 3*points[1][1]-6*points[2][1]+3*points[3][1];
    c[3][2]= 3*points[1][2]-6*points[2][2]+3*points[3][2];
    
    c[4][1]= -points[1][1]+3*points[2][1]-3*points[3][1]+points[4][1];
    c[4][2]= -points[1][2]+3*points[2][2]-3*points[3][2]+points[4][2];
    
    c[3][1]= 3*points[1][1]-6*points[2][1]+3*points[3][1];
    c[3][2]= 3*points[1][2]-6*points[2][2]+3*points[3][2];
    
}









