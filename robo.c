
#include "modelo.c"

// variaveis de perspectiva
// inicializados em init()
GLfloat fov, aspecto;

// variaveis da camera
// posições da camera no espaço
float posicaoX = 0.0, posicaoY = 0.0, posicaoZ = 1.2;

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Trabalho de Comp Grafica");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  init();

  glutMainLoop();

  return 1;
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  fov = 130;
  aspecto = 1;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  quadril();
  pernas();

  glutSwapBuffers();
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
  gluPerspective(fov, aspecto, 0.1, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(posicaoX, posicaoY, posicaoZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
