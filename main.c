
#include "camera.h"
#include "modelo.h"

// Alunos: Eduardo Gimenes, Isadora Menezes e Lucas Ortiz

// Teclas para movimentar a câmera: A, S, D, W
// Teclas para movimentar os membros selecionados: J, K, L, I

// variaveis de perspectiva
// inicializados em init()
GLfloat fov, aspecto;

enum estadoAtual estado;
_Bool animacaoEstaPausada = false;

// variaveis da camera
// posições da camera no espaço
// LIMITE esta definido em movimento.h
float posicaoX = 0.0, posicaoY = 0.0, posicaoZ = LIMITE;

// inicialização de variaveis declaradas com extern em modelo.h
double deslocamentoVertical = 0.0;
double keyWalkFrames[2][6];
double anguloCoxaEsq = 30.0, anguloPanturrEsq = 0.0, anguloCoxaDir = -30.0,
       anguloPanturrDir = 0.0;

enum gesticulacoes gesticulacaoAtual;
double anguloMovimento[9];
double movimentoEixoX[9];
double movimentoEixoY[9];
double movimentoEixoZ[9];

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
  keyWalkFrames[0][2] = 0;
  keyWalkFrames[1][2] = 0;
  deslocamentoVertical = movimentacaoVertical(anguloCoxaEsq, anguloPanturrEsq,
                                              anguloCoxaDir, anguloPanturrDir);

  estadoInicial();
  zerarMovimento();
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
  if (!animacaoEstaPausada) {

    switch (estado) {
    case CAMINHADA:
      animacaoCaminhada();
      break;
    default:
      break;
    }
    glutPostRedisplay();
  }

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
  if (estado == GESTICULACAO) {
    switch (key) {
    case 'i':
      gesticulacao(FRENTE);
      break;
    case 'j':
      gesticulacao(LADO_ESQUERDO);
      break;
    case 'l':
      gesticulacao(LADO_DIREITO);
      break;
    case 'k':
      gesticulacao(TRAS);
      break;
    }
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
  int subMenu = glutCreateMenu(menuSecundario);
  glutAddMenuEntry("Perna esquerda", 0);
  glutAddMenuEntry("Perna direita", 1);
  glutAddMenuEntry("Braço esquerdo", 2);
  glutAddMenuEntry("Braço direito", 3);
  glutAddMenuEntry("Cabeça", 4);
  glutAddMenuEntry("Antebraço esquerdo", 5);
  glutAddMenuEntry("Antebraço direito", 6);
  glutAddMenuEntry("Panturrilha esquerda", 7);
  glutAddMenuEntry("Panturrilha direita", 8);

  int menu = glutCreateMenu(menuPrincipal);
  glutAddMenuEntry("Caminhada", 0);
  glutAddMenuEntry("Pausar", 1);
  glutAddMenuEntry("Voltar a posição inicial", 2);
  glutAddSubMenu("Gesticulação", subMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
};

void estadoInicial() {
  estado = NENHUM;
  gesticulacaoAtual = GEST_NULL;

  // retorna camera a posicao inicial
  posicaoX = posicaoY = 0;
  posicaoZ = LIMITE;
  coordenadaEstaAumentando[0] = coordenadaEstaAumentando[1] =
      coordenadaEstaAumentando[2] = true;
}

void zerarMovimento() {
  for (int i = 0; i < 9; i++) {
    anguloMovimento[i] = 0.0;
    movimentoEixoX[i] = 0.0;
    movimentoEixoY[i] = 0.0;
    movimentoEixoZ[i] = 0.0;
  }
}

void menuPrincipal(int option) {
  animacaoEstaPausada = false;

  switch (option) {
  case 0:
    printf("Opção 'Caminhada' selecionada\n");
    estado = CAMINHADA;
    break;
  case 1:
    printf("Opção 'Pausar' selecionada\n");
    animacaoEstaPausada = true;
    break;
  case 2:
    printf("Opção 'Voltar a posição inicial' selecionada\n");
    zerarMovimento();
    estadoInicial();
    break;
  }

  glutPostRedisplay();
}

void menuSecundario(int option) {
  estado = GESTICULACAO;

  switch (option) {
  case 0:
    printf("Opção 'Perna esquerda' selecionada\n");
    gesticulacaoAtual = GEST_PERNA_ESQ;
    break;
  case 1:
    printf("Opção 'Perna direita' selecionada\n");
    gesticulacaoAtual = GEST_PERNA_DIR;
    break;
  case 2:
    printf("Opção 'Braço esquerdo' selecionada\n");
    gesticulacaoAtual = GEST_BRACO_ESQ;
    break;
  case 3:
    printf("Opção 'Braço direito' selecionada\n");
    gesticulacaoAtual = GEST_BRACO_DIR;
    break;
  case 4:
    printf("Opção 'Cabeça' selecionada\n");
    gesticulacaoAtual = GEST_CABECA;
    break;
  case 5:
    printf("Opção 'Antebraço esquerdo' selecionada\n");
    gesticulacaoAtual = GEST_ANTEBRACO_ESQ;
    break;
  case 6:
    printf("Opção 'Antebraço direito' selecionada\n");
    gesticulacaoAtual = GEST_ANTEBRACO_DIR;
    break;
  case 7:
    printf("Opção 'Panturrilha esquerda' selecionada\n");
    gesticulacaoAtual = GEST_PANTURRILHA_ESQ;
    break;
  case 8:
    printf("Opção 'Panturrilha direita' selecionada\n");
    gesticulacaoAtual = GEST_PANTURRILHA_DIR;
    break;
  }

  glutPostRedisplay();
}
