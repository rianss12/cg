#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
} BMPImage;

#define MAX_NO_TEXTURES 1
GLuint texture_id[MAX_NO_TEXTURES];
char* filenameArray[MAX_NO_TEXTURES] = {"metal.bmp"};

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
   BMPImage textura;
    glGenTextures(MAX_NO_TEXTURES, texture_id);

    for (int i = 0; i < MAX_NO_TEXTURES; i++)
    {
        getBitmapImageData(filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

/* **********************************************************************
  void initTexture(void)
        Define a textura a ser usada

 ********************************************************************** */
void initTexture (void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    CarregaTexturas();
}

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);


    GLfloat light1_pos[] = {4.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {-1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0f);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);


    GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade


    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 2.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1.0, 2.0, 8.0);
    glViewport(0, 0, 500, 500);

    lightning();
}

void cubo(GLfloat red, GLfloat green, GLfloat blue) {
   glBegin(GL_POLYGON);
    glNormal3f(-0.25, 0.25, 0.25);
    glColor3f(red, green, blue);
    glVertex3f(-0.25, 0.25, 0.25);
    glNormal3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
   glBegin(GL_POLYGON);
    glNormal3f(-0.25, 0.25, 0.25);
    glColor3f(red, green, blue);
    glVertex3f(-0.25, 0.25, 0.25);
    glNormal3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
   glBegin(GL_POLYGON);
    glNormal3f(-0.25, 0.25, 0.25);
    glColor3f(red, green, blue);
    glVertex3f(-0.25, 0.25, 0.25);
    glNormal3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
   glBegin(GL_POLYGON);
    glNormal3f(-0.25, 0.25, 0.25);
    glColor3f(red, green, blue);
    glVertex3f(-0.25, 0.25, 0.25);
    glNormal3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
   glBegin(GL_POLYGON);
    glNormal3f(-0.25, 0.25, 0.25);
    glColor3f(red, green, blue);
    glVertex3f(-0.25, 0.25, 0.25);
    glNormal3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glNormal3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
}

void robo(){
  glMatrixMode(GL_MODELVIEW);
  //Cabeça
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glPushMatrix();
    glTranslatef(0.0, 0.95, 0.0);
    glScalef(0.5, 0.5, 0.5);
    cubo(1.0, 1.0, 0.0); // Amarelo
    glPopMatrix();
  //Corpo
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(1.0, 1.0, 0.5);
    cubo(1.0, 0.0, 0.0); // Vermelho
    glPopMatrix();
  //Perna esquerda
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  glPushMatrix();
  glTranslatef(-0.125,-0.125,0.0);
  glScalef(0.25,1.25,0.25);
  cubo(1.0, 0.0, 0.0);
  glPopMatrix();
  //Perna direita
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  glPushMatrix();
  glTranslatef(0.125,-0.125,0.0);
  glScalef(0.25,1.25,0.25);
  cubo(1.0, 0.0, 0.0);
  glPopMatrix();
  //Braço esquerdo
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  glPushMatrix();
  glTranslatef(-0.35,0.45,0.0);
  glScalef(0.25,1.25,0.25);
  cubo(1.0, 0.0, 0.0);
  glPopMatrix();
  //Braço Direito
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  glPushMatrix();
  glTranslatef(0.35,0.45,0.0);
  glScalef(0.25,1.25,0.25);
  cubo(1.0, 0.0, 0.0);
  glPopMatrix();
}

void displayFunc() {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glPushMatrix();
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    robo();
    glPopMatrix();

    glFlush();                  //força o desenho das primitivas
}

void rotacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angleX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angleX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angleY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angleY+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Textura");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(rotacoes);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}
