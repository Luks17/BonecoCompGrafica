
#include "camera.c"
#include "modelo.c"
#include "modelo.h"

// variaveis de perspectiva
// inicializados em init()
GLfloat fov, aspecto;

enum animacaoAtual estado;

// variaveis da camera
// posições da camera no espaço
// LIMITE esta definido em movimento.h
float posicaoX = 0.0, posicaoY = 0.0, posicaoZ = LIMITE;

// inicialização de variaveis declaradas com extern em modelo.h
double deslocamentoVertical = 0.0;
double keyWalkFrames[2][6];
double anguloCoxaEsq = 30.0, anguloPanturrEsq = 0.0, anguloCoxaDir = -30.0,
       anguloPanturrDir = 0.0;

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Trabalho de Comp Grafica");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(kbd);
  glutMouseFunc(mouseHandler);
  glutTimerFunc(100, timer, 1);

  init();

  glutMainLoop();

  return 1;
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  fov = 65;
  aspecto = 1;

  keyWalkFrames[0][3] = anguloCoxaEsq;
  keyWalkFrames[1][3] = anguloCoxaDir;
  keyWalkFrames[0][4] = anguloPanturrEsq;
  keyWalkFrames[1][4] = anguloPanturrDir;
  deslocamentoVertical = movimentacaoVertical(anguloCoxaEsq, anguloPanturrEsq,
                                              anguloCoxaDir, anguloPanturrDir);

  estado = NENHUM;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(posicaoX, posicaoY, posicaoZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glPushMatrix();

  glTranslatef(0.0, deslocamentoVertical, 0.0);

  quadril();
  pernas();
  torso();
  cabeca();
  bracos();

  glPopMatrix();

  glutSwapBuffers();
}

void timer(int value) {
  switch (estado) {
  case CAMINHADA:
    animacaoCaminhada();
    break;
  case ACENANDO:
    break;
  case NENHUM:
    break;
  }

  glutPostRedisplay();
  glutTimerFunc(16, timer, 1);
}

void kbd(unsigned char key, int x, int y) {

  switch (key) {
  case 'w':
    ajustaCoordenada(&posicaoZ, coordz, true);
    ajustaCoordenada(&posicaoY, coordy, true);
    break;
  case 's':
    ajustaCoordenada(&posicaoZ, coordz, false);
    ajustaCoordenada(&posicaoY, coordy, false);
    break;
  case 'a':
    ajustaCoordenada(&posicaoZ, coordz, false);
    ajustaCoordenada(&posicaoX, coordx, false);
    break;
  case 'd':
    ajustaCoordenada(&posicaoZ, coordz, true);
    ajustaCoordenada(&posicaoX, coordx, true);
    break;
  }

  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  aspecto = (GLfloat)w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // fov = field of view
  // aspecto deve ser corrigido dependendo do w e h da janela,
  // znear é o corte mais próximo da camera e
  // zfar é o corte mais longe da camera
  // gluPerspective deve ser sempre modificado no GL_PROJECTION
  gluPerspective(fov, aspecto, 1.0, 40.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouseHandler(int btn, int state, int x, int y) {
  if (btn == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN)
      criaMenu();
  }

  glutPostRedisplay();
}

void criaMenu() {
  int menu = glutCreateMenu(menuPrincipal);
  glutAddMenuEntry("Caminhada", 0);
  glutAddMenuEntry("Acenando", 1);
  glutAddMenuEntry("Pausar", 2);
  glutAddMenuEntry("Voltar a posicao inicial", 3);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
};

void menuPrincipal(int option) {
  switch (option) {
  case 0:
    printf("Opção 'Caminhada' selecionada\n");
    estado = CAMINHADA;
    break;
  case 1:
    printf("Opção 'Acenando' selecionada\n");
    estado = ACENANDO;
    break;
  case 2:
    estado = NENHUM;
    break;
  case 3:
    estado = NENHUM;
    // TODO: desfazer transformacoes aqui

    // retorna camera a posicao inicial
    posicaoX = posicaoY = 0;
    posicaoZ = LIMITE;
    coordenadaEstaAumentando[0] = coordenadaEstaAumentando[1] =
        coordenadaEstaAumentando[2] = true;
    break;
  }

  glutPostRedisplay();
}
