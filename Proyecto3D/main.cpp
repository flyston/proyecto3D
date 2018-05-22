//
//  main.cpp
//  Proyecto3D
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GLut/gutil.h>
#include <GLut/glut.h>
#include <Opengl/gl.h>

#include "/Users/ivan/Downloads/glm.h"
#include "/Users/ivan/Downloads/glm.c"

GLMmodel* model;

int alto=256, ancho=256, ferrari=0, ancho1=1024 ,alto1=1024;
GLfloat angle = 0;
GLfloat angle2 = 0;
int moving, startx, starty;

unsigned char * datos;
unsigned char * datos1;
unsigned char * datos2;
unsigned char * datos3;
unsigned char * datos4;
unsigned char * datos5;
unsigned char * imagenTextura;

int leerImagen(){
    
    FILE *imagenModelo;
    imagenModelo=fopen("/Users/ivan/Downloads/Archivo/bowling pin/bowling_pin_000.mtl","r");
    imagenTextura=(unsigned char*)malloc(ancho1*alto1*3);
    if(imagenModelo==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTextura,ancho1*alto1*3,1,imagenModelo);
    fclose(imagenModelo);
    
    FILE *imagen;
    imagen=fopen("/Users/ivan/Desktop/L1.data","r");
    datos=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos,ancho*alto*3,1,imagen);
    fclose(imagen);
    
    FILE *imagen1;
    imagen1=fopen("/Users/ivan/Desktop/L2.data","r");
    datos1=(unsigned char*)malloc(ancho*alto*3);
    if(imagen1==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos1,ancho*alto*3,1,imagen1);
    fclose(imagen1);
    
    FILE *imagen2;
    imagen2=fopen("/Users/ivan/Desktop/L3.data","r");
    datos2=(unsigned char*)malloc(ancho*alto*3);
    if(imagen2==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos2,ancho*alto*3,1,imagen2);
    fclose(imagen2);
    
    FILE *imagen3;
    imagen3=fopen("/Users/ivan/Desktop/L4.data","r");
    datos3=(unsigned char*)malloc(ancho*alto*3);
    if(imagen3==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos3,ancho*alto*3,1,imagen3);
    fclose(imagen3);
    
    FILE *imagen4;
    imagen4=fopen("/Users/ivan/Desktop/Suelo.data","r");
    datos4=(unsigned char*)malloc(ancho*alto*3);
    if(imagen4==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos4,ancho*alto*3,1,imagen4);
    fclose(imagen4);
    
    FILE *imagen5;
    imagen5=fopen("/Users/ivan/Desktop/Tapa.data","r");
    datos5=(unsigned char*)malloc(ancho*alto*3);
    if(imagen5==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(datos5,ancho*alto*3,1,imagen5);
    fclose(imagen5);
    
    return 1;
}

void aplicaTextura(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTextura);
}

void usarL1(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
}

void usarL2(void){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos1);
}

void usarL3(void){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos2);
}

void usarL4(void){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos3);
}

void usarSuelo(void){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos4);
}

void usarTapa(void){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos5);
    
}

void dibujaModelo() {
    
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(model);
    glmScale(model, 0.95);
    
    glmDraw(model,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}

// cubemap variables
int d1=10;
int d2=20;
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
static GLint pared4Vertices[4][3] = {
    { -d1,d2,-d1},
    { -d1,0,-d1 },
    {  -d1,0,d1 },
    {  -d1,d2,d1},
};
static GLint techoVertices[4][3] = {
    { d1,d2,-d1},
    { -d1,d2,-d1 },
    {  -d1,d2,d1 },
    {  d1,d2,d1},
};

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

void dibujaPared4c(void) {
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
}

void dibujaBase(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(verticesPiso[2]);
    glTexCoord2f(0.0, 1);
    glVertex3iv(verticesPiso[3]);
    glTexCoord2f(1, 1);
    glVertex3iv(verticesPiso[0]);
    glTexCoord2f(1, 0.0);
    glVertex3iv(verticesPiso[1]);
    glEnd();
}

void dibujaTapac(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(techoVertices[2]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(techoVertices[3]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(techoVertices[0]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(techoVertices[1]);
    glEnd();
}

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0); //move mouse
    glRotatef(angle, 0.0, 1.0, 0.0);
    
    dibujaModelo();
    
    glPushMatrix();
    glTranslatef(0,-10, 0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    usarSuelo();
    dibujaBase();
    usarL1();
    dibujaPared1c();
    usarL2();
    dibujaPared2c();
    usarL3();
    dibujaPared3c();
    usarL4();
    dibujaPared4c();
    usarTapa();
    dibujaTapac();
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
    glMatrixMode(GL_MODELVIEW);
    
    gluPerspective(60, 1, 1, 50);
    
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
    
    glutInitWindowSize(640,480);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    
    glutInitWindowSize(640,640);
    glutInitWindowPosition(200, 0);

    glutCreateWindow("Cubo Entorno");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mover);
    
    init();
    
    model = glmReadOBJ("/Users/ivan/Downloads/Archivo/bowling pin/bowling_pin_000.obj");
    glmReadMTL(model,"bowling_pin_000.mtl");
    
    gluPerspective(40.0,1.333,0.1,200.0); //16/10=1.6   5/4=1.25
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 60.0,  /* camara en (0,20,60) */
              0,0,0,          /* mira a (x,y,z) */
              0, 1, 0);      /* altura en Y (0,1,0) o en x Y (1,0,0) */
    
    leerImagen();
    aplicaTextura();
    glutMainLoop();
    return 0;
}


