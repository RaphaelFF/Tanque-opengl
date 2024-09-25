#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cstdio>
#include <cmath>

const float WALL_MIN_X = -48.0f;
const float WALL_MAX_X = 48.0f;
const float WALL_MIN_Z = -48.0f;
const float WALL_MAX_Z = 48.0f;
const float MARGIN_ERROR = 0.5f;

float angleX = 0.0f;
float angleY = 0.0f;
float turretAngle = 0.0f;     
float cannonElevation = 0.0f; 
float tankX = 10.0f;          
float tankZ = 45.0f;           
float tankAngle = 85.0f;      
bool teclas[256];
bool isTankView = false;
GLuint textureTankBody, textureTurret, textureCannon, textureBackground, textureparede;

GLuint loadTexture(const char *filename)
{
    GLuint textureID;
    int width, height, channels;
    unsigned char *image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);

    if (!image)
    {
        printf("Erro ao carregar a imagem: %s\n", SOIL_last_result());
        return 0;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    return textureID;
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(130.0, 1.0, 1.0, 100.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    textureTankBody = loadTexture("C:/Users/Raphael França/Documents/Tanque-opengl/imag/militar1.jpeg");
    textureBackground = loadTexture("C:/Users/Raphael França/Documents/Tanque-opengl/imag/fundochao1.jpeg");
    textureparede = loadTexture("C:/Users/Raphael França/Documents/Tanque-opengl/imag/fundocena.jpeg");  
}
void drawCylinder(float base, float top, float height, int slices, int stacks)
{
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, base, top, height, slices, stacks);
    gluDisk(quad, 0, base, slices, 1);
    glTranslatef(0, 0, height);
    gluDisk(quad, 0, top, slices, 1);
    gluDeleteQuadric(quad);
}
void drawGround()
{
    glBindTexture(GL_TEXTURE_2D, textureBackground);
    glPushMatrix();
    glBegin(GL_QUADS);

    // Aplicar coordenadas de textura e desenhar o plano do chão
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, -0.75f, 50.0f); // Ponto inferior esquerdo
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -0.75f, 50.0f); // Ponto inferior direito
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, -0.75f, -50.0f); // Ponto superior direito
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, -0.75f, -50.0f); // Ponto superior esquerdo

    glEnd();
    glPopMatrix();
}
void drawSkybox()
{
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, textureparede);
    glColor3f(1.0f, 1.0f, 1.0f); // A cor não afeta a textura

    // Frente
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glEnd();

    // Traseira
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glEnd();

    // Lado Esquerdo
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glEnd();

    // Lado Direito
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glEnd();

    // Parte Superior
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glEnd();

    // Parte Inferior
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glEnd();

    glPopMatrix();
}
void soltarTecla(unsigned char tecla, int x, int y)
{
    teclas[tecla] = false; // Marca a tecla como liberada
}
void pressionarTecla(unsigned char tecla, int x, int y)
{
    teclas[tecla] = true; // Marca a tecla como pressionada
}
void movimentoTanque()
{
    float velocidade = 0.05;       // Velocidade de movimento do tanque
    float rotacaoVelocidade = 0.25; // Velocidade de rotação (valor ajustável)
    float radiano = tankAngle * M_PI / 180.0;
    float dx = velocidade * sin(radiano);
    float dz = velocidade * cos(radiano);

    // Movimenta para frente (W)
     if (teclas['w'])
    {
        if (tankX + dx < WALL_MIN_X) {
            tankX = WALL_MIN_X;
        } else if (tankX + dx > WALL_MAX_X) {
            tankX = WALL_MAX_X;
        } else {
            tankX += dx;
        }

        if (tankZ + dz < WALL_MIN_Z) {
            tankZ = WALL_MIN_Z;
        } else if (tankZ + dz > WALL_MAX_Z) {
            tankZ = WALL_MAX_Z;
        } else {
            tankZ += dz;
        }
    }
    // Movimenta para trás (S)
    if (teclas['s'])
    {
        if (tankX - dx < WALL_MIN_X) {
            tankX = WALL_MIN_X;
        } else if (tankX - dx > WALL_MAX_X) {
            tankX = WALL_MAX_X;
        } else {
            tankX -= dx;
        }

        if (tankZ - dz < WALL_MIN_Z) {
            tankZ = WALL_MIN_Z;
        } else if (tankZ - dz > WALL_MAX_Z) {
            tankZ = WALL_MAX_Z;
        } else {
            tankZ -= dz;
        }
    }
    // Rotaciona para a esquerda (A)
    if (teclas['a'])
    {
        tankAngle += rotacaoVelocidade;
    }
    // Rotaciona para a direita (D)
    if (teclas['d'])
    {
        tankAngle -= rotacaoVelocidade;
    }
    if (teclas['1'])
    {
        turretAngle -= rotacaoVelocidade;
    }
    if (teclas['2'])
    {
        turretAngle += rotacaoVelocidade;
    }
    if (teclas['3'])
    {
        cannonElevation += 0.1f;
        if (cannonElevation > 15.0f) // Limitar a elevação máxima do canhão
            cannonElevation = 15.0f;
    }
    if (teclas['4'])
    {
         cannonElevation -= 0.1f;
        if (cannonElevation < -15.0f) // Limitar a elevação mínima do canhão
            cannonElevation = -15.0f;
    }
    if (teclas['t']) {
        isTankView = true;
    } else if (teclas['y']) {
        isTankView = false;
    }
    glutPostRedisplay(); // Atualiza a tela
}
void corpoTanque(){
    glBindTexture(GL_TEXTURE_2D, textureTankBody);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glScalef(2.5f, 1.0f, 4.0f); // Alongando o cubo para formar o corpo
    glBegin(GL_QUADS);

    // Face frontal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Face traseira
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Face superior
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Face inferior
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Face direita
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Face esquerda
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glPopMatrix();
    glEnd();

    glPopMatrix();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float cameraDistance = 5.0f; // Distância da câmera
    float cameraHeight = 2.9f;   // Altura da câmera
    float cameraX = tankX - cameraDistance * sin(tankAngle * M_PI / 180.0f);
    float cameraZ = tankZ - cameraDistance * cos(tankAngle * M_PI / 180.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (isTankView) {
    // Visão em primeira pessoa (dentro do tanque)
    gluLookAt(tankX, 1.0f, tankZ ,  // Posição da câmera dentro do tanque
              tankX + sin(tankAngle * M_PI / 180.0f), 0.3f, tankZ + cos(tankAngle * M_PI / 180.0f),  // Foco na direção do tanque
              0.0f, 1.0f, 0.0f);                // Vetor "up" da câmera
    } else {
    // Visão em terceira pessoa (atras e acima do tanque)
        gluLookAt(cameraX, cameraHeight, cameraZ,    // Posição da câmera
                  tankX, 0.3f, tankZ,                // Ponto de referência da câmera (tanque)
                  0.0f, 1.0f, 0.0f);                // Vetor "up"
    }
    drawSkybox();
    drawGround();

    glPushMatrix();
    movimentoTanque();
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotação no eixo X
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotação no eixo Y
    // Movimenta o tanque para frente e para trás baseado no ângulo da direção
    glTranslatef(tankX, 0.3f, tankZ);
    glRotatef(tankAngle, 0.0f, 1.0f, 0.0f); // Rotaciona o tanque baseado no ângulo da direção

    if (!isTankView){
    // Corpo do tanque
    corpoTanque();

    // Torre do tanque 
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.0f);
    glRotatef(turretAngle, 0.0f, 1.0f, 0.0f); 
    glScalef(1.5f, 0.75f, 1.5f);
    glutSolidCube(1.0f);

    // Cano do tanque
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.5f);               
    glRotatef(cannonElevation, 1.0f, 0.0f, 0.0f); 
    drawCylinder(0.1f, 0.1f, 2.0f, 20, 5);
    glPopMatrix();


    // Cilindro lateral direito (frente)
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0f);      
    glTranslatef(1.35f, -0.5f, 1.8f); 
    glRotatef(90, 0.0f, 1.0f, 0.0f);  
    drawCylinder(0.26f, 0.15f, 0.05f, 20, 5);
    glPopMatrix();

    // Cilindro lateral direito (traseira)
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0);       
    glTranslatef(1.35f, -0.5f, -1.8f); 
    glRotatef(90, 0.0f, 1.0f, 0.0f);   
    drawCylinder(0.26f, 0.15f, 0.05f, 20, 5);
    glPopMatrix();

    // Esteira lateral direita
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0f);
    glTranslatef(1.35f, -0.5f, 0.0f);
    glScalef(0.2f, 0.5f, 3.7f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cilindro lateral esquerdo (frente)
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0f);       
    glTranslatef(-1.35f, -0.5f, 1.8f); 
    glRotatef(90, 0.0f, 1.0f, 0.0f);   
    drawCylinder(0.26f, 0.15f, 0.05f, 20, 5);
    glPopMatrix();

    // Cilindro lateral esquerdo (traseira)
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0f);        
    glTranslatef(-1.35f, -0.5f, -1.8f); 
    glRotatef(90, 0.0f, 1.0f, 0.0f);    
    drawCylinder(0.26f, 0.15f, 0.05f, 20, 5);
    glPopMatrix();

    // Esteira lateral esquerda
    glPushMatrix();
    glColor3f(0.75f, 1.0f, 0.0f);
    glTranslatef(-1.35f, -0.5f, 0.0f);
    glScalef(0.2f, 0.5f, 3.7f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Rodas (Círculos ao longo das esteiras)
    float wheel_positions[8][3] = {
        {1.26f, -0.75f, 1.5f},   
        {1.26f, -0.75f, 0.5f},
        {-1.46f, -0.75f, -0.5f},
        {-1.46f, -0.75f, 0.5f},  
        {1.26f, -0.75f, -0.5f}, 
        {1.26f, -0.75f, -1.5f}, 
        {-1.46f, -0.75f, 1.5f},
        {-1.46f, -0.75f, -1.5f}
    };
    for (int i = 0; i < 8; ++i)
    {
        glPushMatrix();
        glColor3f(0.0f, 0.4f, 0.0f); // Roda verde escuro
        glTranslatef(wheel_positions[i][0], wheel_positions[i][1], wheel_positions[i][2]);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.3f, 0.3f, 0.2f, 20, 5);
        glPopMatrix();
    }
  }
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tanque 3D");
    init();
    glutDisplayFunc(display);
    glutKeyboardUpFunc(soltarTecla);
    glutKeyboardFunc(pressionarTecla);
    glutMainLoop();

    return 0;
}