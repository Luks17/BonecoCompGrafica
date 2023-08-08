
#include "camera.c"
#include "modelo.c"

// variaveis de perspectiva
// inicializados em init()
GLfloat fov, aspecto;

// variaveis da camera
// posições da camera no espaço
// LIMITE esta definido em movimento.h
float posicaoX = 0.0, posicaoY = 0.0, posicaoZ = LIMITE;

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Trabalho de Comp Grafica");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(kbd);
  glutMouseFunc(mouseHandler);

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
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(posicaoX, posicaoY, posicaoZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  quadril();
  pernas();
  torso();
  cabeca();
  bracos();

  glutSwapBuffers();
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
  glutAddMenuEntry("Corrida", 0);
  glutAddMenuEntry("Acenando", 1);
  glutAddMenuEntry("Voltar a posicao inicial", 2);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
};

void menuPrincipal(int option) {
  switch (option) {
  case 0:
    printf("Opção 'Corrida' selecionada\n");
    break;
  case 1:
    printf("Opção 'Acenando' selecionada\n");
    break;
  case 2:
    // TODO: desfazer transformacoes futuras aqui tb
    posicaoX = posicaoY = 0;
    posicaoZ = LIMITE;
    coordenadaEstaAumentando[0] = coordenadaEstaAumentando[1] =
        coordenadaEstaAumentando[2] = true;
    break;
  }

  glutPostRedisplay();
}
