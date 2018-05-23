
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
GLMmodel* model1;

int alto=256,ancho=256;
int altoM=1024,anchoM=1024;//dim imagen
GLfloat angle = 0;
GLfloat angle2 = 0;
int moving, startx, starty, ferrari=0, ferrari1=0;

unsigned char * textura;
unsigned char * textura2;
unsigned char * textura3;
unsigned char * textura4;
unsigned char * textura5;
unsigned char * textura6;
unsigned char * imagenTexturaM;
unsigned char * imagenTexturaM1;

int leerImagen(){
    FILE *imagen;
    imagen=fopen("/Users/ivan/Desktop/L1.data","r");
    textura=(unsigned char*)malloc(ancho*alto*3);
    if(imagen==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura,ancho*alto*3,1,imagen);
    fclose(imagen);

    FILE *imagen1;
    imagen1=fopen("//Users/ivan/Desktop/L2.data","r");
    textura2=(unsigned char*)malloc(ancho*alto*3);
    if(imagen1==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura2,ancho*alto*3,1,imagen1);
    fclose(imagen1);
    
    FILE *imagen2;
    imagen2=fopen("/Users/ivan/Desktop/L3.data","r");
    textura3=(unsigned char*)malloc(ancho*alto*3);
    if(imagen2==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura3,ancho*alto*3,1,imagen2);
    fclose(imagen2);
 
    FILE *imagen3;
    imagen3=fopen("/Users/ivan/Desktop/L4.data","r");
    textura4=(unsigned char*)malloc(ancho*alto*3);
    if(imagen3==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura4,ancho*alto*3,1,imagen3);
    fclose(imagen3);
  
    FILE *imagen4;
    imagen4=fopen("/Users/ivan/Desktop/Tapa.data","r");
    textura5=(unsigned char*)malloc(ancho*alto*3);
    if(imagen4==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura5,ancho*alto*3,1,imagen4);
    fclose(imagen4);

    FILE *imagen5;
    imagen5=fopen("/Users/ivan/Desktop/Suelo.data","r");
    textura6=(unsigned char*)malloc(ancho*alto*3);
    if(imagen5==NULL){
        printf("Error: No imagen");
        return 0;
    }
    fread(textura6,ancho*alto*3,1,imagen5);
    fclose(imagen5);

    FILE *imagen6;
    imagen6=fopen("/Users/ivan/Desktop/boliche.data","r");
    imagenTexturaM=(unsigned char*)malloc(anchoM*altoM*3);
    if(imagen6==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTexturaM,anchoM*altoM*3,1,imagen6);
    fclose(imagen6);
    
    FILE *imagen7;
    imagen7=fopen("/Users/ivan/Desktop/toastmap.data","r");
    imagenTexturaM1=(unsigned char*)malloc(anchoM*altoM*3);
    if(imagen7==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTexturaM1,anchoM*altoM*3,1,imagen7);
    fclose(imagen7);
    return 1;
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

void aplicaTexturaM(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoM, altoM, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTexturaM);
}

void aplicaTexturaM1(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoM, altoM, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTexturaM1);
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

/*static GLint pared3Vertices[4][3] = {
    
    {  d1,d2,-d1 },
    { d1,0,-d1 },
    { -d1,0,-d1 },
    {  -d1,d2,-d1},
};*/

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

/*void dibujaPared3c(void) {
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
}*/

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

void dibujaTapac(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(techoVertices[1]);
    glTexCoord2f(0.0, 1.0);
    glVertex3iv(techoVertices[2]);
    glTexCoord2f(1.0, 1.0);
    glVertex3iv(techoVertices[3]);
    glTexCoord2f(1.0, 0.0);
    glVertex3iv(techoVertices[0]);
    glEnd();
}

void dibujaBase(void) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3iv(verticesPiso[3]);
    glTexCoord2f(0.0, 1);
    glVertex3iv(verticesPiso[0]);
    glTexCoord2f(1, 1);
    glVertex3iv(verticesPiso[1]);
    glTexCoord2f(1, 0.0);
    glVertex3iv(verticesPiso[2]);
    glEnd();
}

void iluminacion (int encendido){
    if(encendido==1) {
        const GLfloat pos[4]={10, 10, 10};//poner afuera
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        
    }else{
        glDisable(GL_LIGHTING);}
}

void aplicarMaterial(int encendido) {
    iluminacion(1);
    if(encendido==1) {
        GLfloat mat_green_ambient[] = { 0.0,0.0,0.0,1.0};
        GLfloat mat_green_diffuse[] = { 0.5,0.0,0.0,1.0};
        GLfloat mat_specular[] = { 0.7,0.6,0.6,1.0};
        GLfloat mat_emission[] = { 0.0,0.0,0.0,0};
        
        GLfloat mat_shininess[] = {32};
        
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_green_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_green_diffuse);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
}

/*void transparencia (int encendido) {
    if(encendido==1) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
    }else{
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST); }
}*/

void dibujaModelo(){
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(model);
    glmScale(model, 8.0);
    
    glmDraw(model,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}

void dibujaModelo1(){
    if (ferrari1==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(model1);
    glmScale(model1, 4.0);
    
    glmDraw(model1,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glPushMatrix();
        glRotatef(angle2, 1.0, 0.0, 0.0); //move mouse
        glRotatef(angle, 0.0, 1.0, 0.0);
    
        //bola
        glPushMatrix();
            glTranslatef(0, -6, -25);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM1();
            dibujaModelo1();
        glPopMatrix();
    
        //bolo1
        glPushMatrix();
            glTranslatef(8, -7, 10);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        //bolo2
        glPushMatrix();
            glTranslatef(0, -7, 10);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        //bolo3
        glPushMatrix();
            glTranslatef(-8, -7, 10);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        //bolo4
        glPushMatrix();
            glTranslatef(3.5, -7, 2);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        //bolo5
        glPushMatrix();
            glTranslatef(-3.5, -7, 2);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        //bolo6
        glPushMatrix();
            glTranslatef(0.4, -7, -6);
            glRotatef(90, 0, 1, 0);
            aplicaTexturaM();
            dibujaModelo();
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(0,-10, 0);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            usarTextura();
            dibujaPared4c();
    
            usarTextura2();
            dibujaPared1c();
    
            usarTextura3();
            dibujaPared2c();
    
            //usarTextura4();
            //dibujaPared3c();
    
            usarTextura5();
            dibujaTapac();
    
            usarTextura6();
            dibujaBase();//Base
        glPopMatrix();
    
        glPushMatrix();
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            aplicarMaterial(1);
            glTranslatef(0, -6, -15);
            glRotatef(90, 0, 1, 0);
            glutSolidCube(5);
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
    gluLookAt(0.0, 10,-40.0,  /* camara en (0,20,60) */
              0,10,0,          /* mira a (x,y,z) */
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
    glutInitWindowPosition(200, 200);
    
    glutCreateWindow("Tarea Entorno");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mover);
    
    //gluPerspective(40,1,1,60); //16/10=1.6   5/4=1.25
    //glMatrixMode(GL_MODELVIEW);
    
    init();
    
    model = glmReadOBJ("/Users/ivan/Downloads/Archivo/bowling pin/bowling_pin_000.obj");
    glmReadMTL(model,"bowling_pin_000.mtl");

    model1 = glmReadOBJ("/Users/ivan/Downloads/Archivo/Bowling ball/tinker.obj");
    glmReadMTL(model1,"obj.mtl");

    leerImagen();
    glutMainLoop();
    return 0;
}
