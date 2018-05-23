
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GLut/gutil.h>
#include <GLut/glut.h>
#include <Opengl/gl.h>

#include "/Users/valentinmedina/Downloads/glm.h"
#include "/Users/valentinmedina/Downloads/glm.c"

GLMmodel* model;

int alto=200,ancho=200;
int altoM=1024,anchoM=1024;//dim imagen
GLfloat angle = 0;
GLfloat angle2 = 0;
int moving, startx, starty;
int ferrari=0;




unsigned char * textura;
unsigned char * textura2;
unsigned char * textura3;
unsigned char * textura4;
unsigned char * textura5;
unsigned char * textura6;
unsigned char * imagenTexturaM;

void dibujaModelo(){
    
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(model);
    glmScale(model, 4.90);
    
    glmDraw(model,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}


int leerImagen(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/base.data","r");
    textura=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
}

int leerImagen2(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/pared1.data","r");
    textura2=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura2,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
    
}

int leerImagen3(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/pared2.data","r");
    textura3=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura3,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
    
}

int leerImagen4(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/pared3.data","r");
    textura4=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura4,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
    
}


int leerImagen5(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/pared4.data","r");
    textura5=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura5,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
    
}

int leerImagen6(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Desktop/ImagenesBruto/tapa.data","r");
    textura6=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura6,ancho*alto*3,1,imagen);
    fclose(imagen);
    return 1;
    
}



int leerImagenM(){
    FILE *imagen;
    imagen=fopen("/Users/valentinmedina/Documents/proyecto3D/bowling pin/Hongo.data","r");
    imagenTexturaM=(unsigned char*)malloc(anchoM*altoM*3);
    if(imagen==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTexturaM,anchoM*altoM*3,1,imagen);
    fclose(imagen);
    return 1;
}

void aplicaTexturaM(void)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoM, altoM, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTexturaM);
}


void usarTextura(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);
}

void usarTextura2(void){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura2);
    
}

void usarTextura3(void){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura3);
    
}

void usarTextura4(void){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura4);
    
}
void usarTextura5(void){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura5);
    
}

void usarTextura6(void){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura6);
    
}

// cubemap variables
int d1=20;
int d2=40;
static GLint verticesPiso[4][3] = {
    { -d1, 0,  -d1 },
    {  d1, 0,  -d1 },
    {  d1, 0, d1 },
    { -d1, 0, d1 },
};
static GLint pared1Vertices[4][3] = {
    { -d1,d2, d1},
    { -d1,0,  d1},
    {  d1,0,  d1},
    {  d1,d2, d1},
};
static GLint pared2Vertices[4][3] = {
    { d1,d2, d1},
    { d1,0,  d1},
    { d1,0, -d1},
    { d1,d2,-d1},
};
static GLint pared3Vertices[4][3] = {
    
    {  d1,d2,-d1 },
    { d1,0,-d1 },
    { -d1,0,-d1 },
    {  -d1,d2,-d1},
};
/*static GLint pared4Vertices[4][3] = {
 { -d1,d2,-d1},
 { -d1,0,-d1 },
 {  -d1,0,d1 },
 {  -d1,d2,d1},
 };*/
static GLint techoVertices[4][3] = {
    { d1,d2,-d1},
    { -d1,d2,-d1 },
    {  -d1,d2,d1 },
    {  d1,d2,d1},
    
    
};

void dibujaBase(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(verticesPiso[0]);
    glTexCoord2f(0.0, 1);
    glVertex3iv(verticesPiso[1]);
    glTexCoord2f(1, 1);
    glVertex3iv(verticesPiso[2]);
    glTexCoord2f(1, 0.0);
    glVertex3iv(verticesPiso[3]);
    glEnd();
}

void dibujaPared1c(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(pared1Vertices[0]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(pared1Vertices[1]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(pared1Vertices[2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(pared1Vertices[3]);
    glEnd();
}

void dibujaPared2c(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(pared2Vertices[0]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(pared2Vertices[1]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(pared2Vertices[2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(pared2Vertices[3]);
    glEnd();
}

void dibujaPared3c(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(pared3Vertices[0]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(pared3Vertices[1]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(pared3Vertices[2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(pared3Vertices[3]);
    glEnd();
}

/*void dibujaPared4c(void) {
 glBegin(GL_QUADS);
 glTexCoord2f(0.0, 0.0);
 glVertex3iv(pared4Vertices[0]);
 glTexCoord2f(0.0, 1.0);
 glVertex3iv(pared4Vertices[1]);
 glTexCoord2f(1.0, 1.0);
 glVertex3iv(pared4Vertices[2]);
 glTexCoord2f(1.0, 0.0);
 glVertex3iv(pared4Vertices[3]);
 glEnd();
 }*/

void dibujaTapac(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(techoVertices[0]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(techoVertices[1]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(techoVertices[2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(techoVertices[3]);
    glEnd();
}
//////////////////////////////////////////////////

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0); //move mouse
    glRotatef(angle, 0.0, 1.0, 0.0);
    //Hongo 1
    glPushMatrix();
    glTranslatef(-40, -5, 0);
    glRotatef(90, 0, 1, 0);
    aplicaTexturaM();
    dibujaModelo();
    glPopMatrix();
    //Hongo2
    glPushMatrix();
    glTranslatef(-40, -5, 10);
    glRotatef(90, 0, 1, 0);
    aplicaTexturaM();
    dibujaModelo();
    glPopMatrix();
    
    glPushMatrix();
    
    glPushMatrix();
    glTranslatef(0,-10, 0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    usarTextura();
    dibujaBase();//Base
    usarTextura2();
    dibujaPared1c();
    usarTextura3();
    dibujaPared2c();
    usarTextura4();
    dibujaPared3c();
    usarTextura5();
    //dibujaPared4c();
    usarTextura6();
    dibujaTapac();//tapa
    glPopMatrix();
    
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

void mover(int x, int y) {
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1, 1,200);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0,10.0,  /* camara en (0,20,60) */
              0,0,0,          /* mira a (x,y,z) */
              0, 1, 0);/* altura en Y (0,1,0) o en x Y (1,0,0)*/
    
    
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_TEXTURE_2D);
    
    glClearColor(0.4, 0.7, 0.99, 1);
    
    float pos[4]={1,1,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(0, 0, -2);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    
    glutInitWindowSize(640,640);
    
    glutCreateWindow("Tarea Entorno");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mover);
    
    
    //gluPerspective(40,1,1,60); //16/10=1.6   5/4=1.25
    //glMatrixMode(GL_MODELVIEW);
    
    
    
    
    init();
    
    
    
    model = glmReadOBJ("/Users/valentinmedina/Documents/proyecto3D/bowling pin/Hongo.obj");
    glmReadMTL(model,"Hongo.mtl");
    
    leerImagen();
    leerImagen2();
    leerImagen3();
    leerImagen4();
    leerImagen5();
    leerImagen6();
    leerImagenM();
    glutMainLoop();
    return 0;
}


