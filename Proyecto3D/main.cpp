
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
GLMmodel* bola;
GLMmodel* flecha;

int alto=256,ancho=256;
int altoM=1024,anchoM=1024;//dim imagen
GLfloat angle = 0;
GLfloat angle2 = 0;
int moving, startx, starty, ferrari=0, band=1, bandTimer=1;
int rotarFlecha=-90, direccionBola=0;
float i=-65;
float planoPiso[4];
float posicionLuz[] = {10, 0, 0, 0};
enum {X, Y, Z, W};
enum {A, B, C, D};

unsigned char * textura;
unsigned char * textura2;
unsigned char * textura3;
unsigned char * textura4;
unsigned char * textura5;
unsigned char * textura6;
unsigned char * imagenTexturaM;
unsigned char * imagenTexturaBola;
unsigned char * imagenTexturaFlecha;


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
    imagen7=fopen("/Users/ivan/Desktop/bola.data","r");
    imagenTexturaBola=(unsigned char*)malloc(anchoM*altoM*3);
    if(imagen7==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTexturaBola,anchoM*altoM*3,1,imagen7);
    fclose(imagen7);
    
    FILE *imagen8;
    imagen8=fopen("/Users/ivan/Desktop/flecha.data","r");
    imagenTexturaFlecha=(unsigned char*)malloc(anchoM*altoM*3);
    if(imagen8==NULL){
        printf("Sin imagen");
        return 0;
    }
    fread(imagenTexturaFlecha,anchoM*altoM*3,1,imagen8);
    fclose(imagen8);
    
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

void aplicaTexturaBola(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoM, altoM, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTexturaBola);
}

void aplicaTexturaFlecha(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoM, altoM, 0, GL_RGB, GL_UNSIGNED_BYTE, imagenTexturaFlecha);
}

// cubemap variables
int d1=40;
int d2=80;

/*static GLint verticesPiso[4][3] = {
    { -d1, 0,  -d1 },
    {  d1, 0,  -d1 },
    {  d1, 0, d1 },
    { -d1, 0, d1 },
};*/

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

static GLfloat verticesPisoP[4][3] = {
    { -100.0, -10.0,  100.0 },
    {  100.0, -10.0,  100.0 },
    {  100.0, -10.0, -100.0 },
    { -100.0, -10.0, -100.0 },
};

char *texturaP[] = {
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    "o...............",
    
};

void texturaPiso() {
    GLubyte floorTexture[16][16][3];
    GLubyte *color;
    
    int x,y;
    // Crear RGB para textura
    color = (GLubyte*) floorTexture;
    
    for (x = 0; x < 16; x++) {
        for (y = 0; y < 16; y++) {
            if (texturaP[x][y] == 'x') {
                color[0] = 255;
                color[1] = 204;
                color[2] = 128;
            } else if (texturaP[x][y] == 'o') {
                color[0] = 1;
                color[1] = 1;
                color[2] = 1;
            }else {
                color[0] =255;
                color[1] =204;
                color[2] =128;
            }
            color += 3;
        }
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 16,16, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
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

void dibujaPiso() {
    glDisable(GL_LIGHTING);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(verticesPisoP[0]);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(verticesPisoP[1]);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(verticesPisoP[2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(verticesPisoP[3]);
    glEnd();
    
    glEnable(GL_LIGHTING);
}

/* Ecuación del plano dados 3 puntos. */
void ecPlano(GLfloat plano[4],GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]) {
    GLfloat vec0[3], vec1[3];
    /* Producto cruz entre 2 vectores. */
    vec0[X] = v1[X] - v0[X];
    vec0[Y] = v1[Y] - v0[Y];
    vec0[Z] = v1[Z] - v0[Z];
    
    vec1[X] = v2[X] - v0[X];
    vec1[Y] = v2[Y] - v0[Y];
    vec1[Z] = v2[Z] - v0[Z];
    
    /* Encontrar producto cruz para A, B, y C en la ec. del plano */
    plano[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
    plano[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
    plano[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
    
    plano[D] = -(plano[A] * v0[X] + plano[B] * v0[Y] + plano[C] * v0[Z]);
}


/*void dibujaBase(void) {
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
}*/

void timerFunc(int value) {
    if (bandTimer==1) {
        glutTimerFunc(50, timerFunc, 0);
        switch (band) {
            case 1:
                rotarFlecha-=1;
                if (rotarFlecha<-110) {
                    band=0;
                }
                break;
            case 0:
                rotarFlecha+=1;
                if (rotarFlecha>-70) {
                    band=1;
                }
                break;
        }
    } else {
        glutTimerFunc(50, timerFunc, 0);
        if (i<15) {
            i+=5;
        }
    }
    glutPostRedisplay();
}

void dibujaModelo(){
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(model);
    glmScale(model, 18.0);
    
    glmDraw(model,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}

void dibujaModeloBola(){
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(bola);
    glmScale(bola, 8.0);
    
    glmDraw(bola,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
}

void dibujaModeloFlecha(){
    if (ferrari==1)
        glRotatef(-90, 1.0, 0.0, 0.0);
    
    glmUnitize(flecha);
    glmScale(flecha, 8.0);
    
    glmDraw(flecha,GLUT_DOUBLE|GLM_SMOOTH | GLM_MATERIAL|GLM_TEXTURE);
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
    }
}

static void key(unsigned char c, int x, int y) {
    if (c == 27) {
        exit(0);
    }
    if (c == 'd') {
        bandTimer=0;
        if (rotarFlecha<-90) {
            direccionBola=65*cos(rotarFlecha);
        } else {
            direccionBola=-65*cos(rotarFlecha);
        }
        glutTimerFunc(0, timerFunc, 0);
    }
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1, 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 10,-100.0,  /* camara en (0,20,60) */
              0,10,0,          /* mira a (x,y,z) */
              0, 1, 0);/* altura en Y (0,1,0) o en x Y (1,0,0)*/
    
    glClearColor(0.4, 0.7, 0.99, 1);
    
    ecPlano(planoPiso, verticesPisoP[1], verticesPisoP[2], verticesPisoP[3]);//Plano para sombra
}

void display(void) {
    printf("\n\n\n\n\n\nse desplaza %d\n\n\n\n\n\n", direccionBola);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glutTimerFunc(50, timerFunc, 0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glRotatef(angle2, 1.0, 0.0, 0.0); //move mouse
        glRotatef(angle, 0.0, 1.0, 0.0);

            //bola
            glPushMatrix();
                glTranslatef((direccionBola/10), -2, i);
                //glRotatef(90, 0, 1, 0);
                aplicaTexturaBola();
                dibujaModeloBola();
            glPopMatrix();
    
            //flecha
            glPushMatrix();
                glTranslatef(0, -6, -30);
                glRotatef(rotarFlecha, 0, 1, 0);
                glScalef(3, 1, 1);
                aplicaTexturaFlecha();
                dibujaModeloFlecha();
            glPopMatrix();
    
            //bolo1
            glPushMatrix();
                glTranslatef(15, -2, 16);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo2
            glPushMatrix();
                glTranslatef(5, -2, 16);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo3
            glPushMatrix();
                glTranslatef(-5, -2, 16);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo4
            glPushMatrix();
                glTranslatef(-15, -2, 16);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo5
            glPushMatrix();
                glTranslatef(9, -2, 6);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo6
            glPushMatrix();
                glTranslatef(0, -2, 6);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo7
            glPushMatrix();
                glTranslatef(-9, -2, 6);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo8
            glPushMatrix();
                glTranslatef(5, -2, -4);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo9
            glPushMatrix();
                glTranslatef(-5, -2, -4);
                glRotatef(90, 0, 1, 0);
                aplicaTexturaM();
                dibujaModelo();
            glPopMatrix();
    
            //bolo10
            glPushMatrix();
                glTranslatef(0, -2, -14);
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
    
                /*usarTextura6();
                dibujaBase();//Base*/
            glPopMatrix();
    
            glPushMatrix();
                //glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
                //glEnable(GL_BLEND);
                //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(1.0, 1.0, 1.0, 0.6);
                usarTextura6();
                dibujaPiso();
            glPopMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    
    glutInitWindowSize(640,640);
    glutInitWindowPosition(200, 200);
    
    glutCreateWindow("Tarea Entorno");
    leerImagen();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mover);
    glutKeyboardFunc(key);
    
    init();
    
    model = glmReadOBJ("/Users/ivan/Downloads/bowling pin/bowling_pin_000.obj");
    glmReadMTL(model,"bowling_pin_000.mtl");

    bola = glmReadOBJ("/Users/ivan/Downloads/Bowling ball/ball.obj");
    glmReadMTL(bola,"ball.mtl");
    
    flecha = glmReadOBJ("/Users/ivan/Downloads/arrow-obj/arrow.obj");
    glmReadMTL(flecha,"arrow.mtl");
    
    glutMainLoop();
    
    return 0;
}
