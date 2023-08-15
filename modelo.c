
#include "modelo.h"

double anguloMovimento[9];
double movimentoEixoX[9];
double movimentoEixoY[9];
double movimentoEixoZ[9];

void quadril() {
  glPushMatrix();

  glScalef(BASE_WIDTH, BASE_HEIGHT, TORSO);
  glColor3f(0.0, 1.0, 1.0);
  glTranslatef(0.0, 0.0, 0.0);
  glutWireCube(1.0);

  glPopMatrix();
}

void coxa(enum lados lado) {
  glPushMatrix();

  glScalef(UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glTranslatef(0.0, -UP_LEG_HEIGHT * 0.75, 0.0);

  glPushMatrix();

  glScalef(UP_LEG_WIDTH, UP_LEG_HEIGHT, UP_LEG_WIDTH);

  if (((gesticulacaoAtual == GEST_PERNA_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_PERNA_DIR && lado == 1)) &&
      estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(0.5, 0.5, 0.5);

  glutWireCube(1.0);

  glPopMatrix();
}

void panturrilha(enum lados lado) {
  glPushMatrix();

  // desenha joelho
  glScalef(LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glTranslatef(0.0, -LO_LEG_HEIGHT * 0.75, 0.0);

  glPushMatrix();

  glScalef(LO_LEG_WIDTH, LO_LEG_HEIGHT, LO_LEG_WIDTH);

  if (((gesticulacaoAtual == GEST_PERNA_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_PERNA_DIR && lado == 1) ||
       (gesticulacaoAtual == GEST_PANTURRILHA_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_PANTURRILHA_DIR && lado == 1)) &&
      estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(1.0, 0.0, 1.0);

  glutWireCube(1.0);

  glPopMatrix();
}

void pe(enum lados lado) {
  glPushMatrix();

  // desenha tornozelo
  glScalef(FOOT_JOINT_SIZE, FOOT_JOINT_SIZE, FOOT_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glPushMatrix();

  glTranslatef(0.0, -FOOT_HEIGHT * 0.75, FOOT_WIDTH * 0.5);

  glPushMatrix();

  glScalef(FOOT_WIDTH, FOOT_HEIGHT, FOOT);

  if (((gesticulacaoAtual == GEST_PERNA_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_PERNA_DIR && lado == 1) ||
       (gesticulacaoAtual == GEST_PANTURRILHA_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_PANTURRILHA_DIR && lado == 1)) &&
      estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(0.5, 0.0, 1.0);

  glutWireCube(1.0);

  glPopMatrix();
  glPopMatrix();
};

void perna(enum lados lado) {
  glPushMatrix();

  if (estado == CAMINHADA)
    glRotatef(keyWalkFrames[lado][3], 1.0, 0.0, 0.0);

  if (estado == GESTICULACAO) {
    glRotatef(anguloMovimento[GEST_PERNA_ESQ + lado],
              movimentoEixoX[GEST_PERNA_ESQ + lado],
              movimentoEixoY[GEST_PERNA_ESQ + lado],
              movimentoEixoZ[GEST_PERNA_ESQ + lado]);
  }

  coxa(lado);
  glTranslatef(0.0, -UP_LEG_HEIGHT * 0.75, 0.0);

  if (estado == CAMINHADA)
    glRotatef(keyWalkFrames[lado][4], 1.0, 0.0, 0.0);

  if (estado == GESTICULACAO) {
    glRotatef(anguloMovimento[GEST_PANTURRILHA_ESQ + lado],
              movimentoEixoX[GEST_PANTURRILHA_ESQ + lado],
              movimentoEixoY[GEST_PANTURRILHA_ESQ + lado],
              movimentoEixoZ[GEST_PANTURRILHA_ESQ + lado]);
  }

  panturrilha(lado);
  glTranslatef(0.0, -LO_LEG_HEIGHT * 0.625, 0.0);

  if (estado == CAMINHADA)
    glRotatef(keyWalkFrames[lado][5], 1.0, 0.0, 0.0);
  pe(lado);

  glPopMatrix();
}

void pernas() {
  glPushMatrix();

  // desce a altura para as pernas
  glTranslatef(0.0, -(BASE_HEIGHT), 0.0);

  // perna direita
  glPushMatrix();
  glTranslatef(TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna(DIREITA);
  glPopMatrix();

  // perna esquerda
  glPushMatrix();
  glTranslatef(-TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna(ESQUERDA);
  glPopMatrix();

  glPopMatrix();
}

void torso() {
  glPushMatrix();

  glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.0, BASE_HEIGHT / 2.0 + TORSO_HEIGHT / 2.0, 0.0);
  glScalef(TORSO_WIDTH, TORSO_HEIGHT, TORSO);

  glutWireCube(1.0);

  glPopMatrix();
}

void antebraco(enum lados lado) {
  glPushMatrix();

  glTranslatef(0.0, -LO_ARM_JOINT_SIZE * 4, 0.0);

  glPushMatrix();

  glColor3f(0.0, 1.0, 0.0);
  glScalef(LO_ARM_JOINT_SIZE, LO_ARM_JOINT_SIZE, LO_ARM_JOINT_SIZE);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  if (((gesticulacaoAtual == GEST_BRACO_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_BRACO_DIR && lado == 1) ||
       (gesticulacaoAtual == GEST_ANTEBRACO_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_ANTEBRACO_DIR && lado == 1)) &&
      estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(0.5, 0.1, 0.3);

  glTranslatef(0.0, -LO_ARM_JOINT_SIZE - LO_ARM_HEIGHT / 2, 0.0);

  glScalef(LO_ARM_WIDTH, LO_ARM_HEIGHT, LO_ARM_WIDTH);
  glutWireCube(1.0);

  glPopMatrix();
}

void bracoSuperior(enum lados lado) {
  glPushMatrix();

  glTranslatef(0.0, -UP_ARM_JOINT_SIZE * 2, 0.0);

  glPushMatrix();

  glColor3f(0.0, 1.0, 0.0);
  glScalef(UP_ARM_JOINT_SIZE, UP_ARM_JOINT_SIZE, UP_ARM_JOINT_SIZE);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  if (((gesticulacaoAtual == GEST_BRACO_ESQ && lado == 0) ||
       (gesticulacaoAtual == GEST_BRACO_DIR && lado == 1)) &&
      estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(0.5, 0.1, 0.3);

  glTranslatef(0.0, -UP_ARM_JOINT_SIZE - UP_ARM_HEIGHT / 2, 0.0);

  glScalef(UP_ARM_WIDTH, UP_ARM_HEIGHT, UP_ARM_WIDTH);
  glutWireCube(1.0);

  glPopMatrix();
}

void braco(enum lados lado) {
  glPushMatrix();

  if (estado == CAMINHADA)
    glRotatef(keyWalkFrames[lado][2], 1.0, 0.0, 0.0);

  if (estado == GESTICULACAO) {
    glRotatef(anguloMovimento[GEST_BRACO_ESQ + lado],
              movimentoEixoX[GEST_BRACO_ESQ + lado],
              movimentoEixoY[GEST_BRACO_ESQ + lado],
              movimentoEixoZ[GEST_BRACO_ESQ + lado]);
  }

  bracoSuperior(lado);

  if (estado == GESTICULACAO) {
    glRotatef(anguloMovimento[GEST_ANTEBRACO_ESQ + lado],
              movimentoEixoX[GEST_ANTEBRACO_ESQ + lado],
              movimentoEixoY[GEST_ANTEBRACO_ESQ + lado],
              movimentoEixoZ[GEST_ANTEBRACO_ESQ + lado]);
  }

  glTranslatef(0.0, -UP_ARM_HEIGHT * 0.875 - LO_ARM_JOINT_SIZE * 2, 0.0);
  antebraco(lado);

  glPopMatrix();
}

void bracos() {
  glPushMatrix();

  glTranslatef(TORSO_WIDTH * 0.66,
               UP_ARM_HEIGHT * 0.875 + LO_ARM_JOINT_SIZE * 2 + LO_ARM_HEIGHT,
               0.0);
  braco(DIREITA);

  glPopMatrix();

  glPushMatrix();

  glTranslatef(TORSO_WIDTH * (-0.66),
               UP_ARM_HEIGHT * 0.875 + LO_ARM_JOINT_SIZE * 2 + LO_ARM_HEIGHT,
               0.0);
  braco(ESQUERDA);

  glPopMatrix();
}

void cabeca() {
  glPushMatrix();

  glColor3f(0.0, 1.0, 0.0);
  glTranslatef(0.0, BASE_HEIGHT / 2.0 + TORSO_HEIGHT + HEAD_JOINT_SIZE, 0.0);

  glScalef(HEAD_JOINT_SIZE, HEAD_JOINT_SIZE, HEAD_JOINT_SIZE);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glPushMatrix();

  if (estado == GESTICULACAO) {
    glRotatef(anguloMovimento[GEST_CABECA], movimentoEixoX[GEST_CABECA],
              movimentoEixoY[GEST_CABECA], movimentoEixoZ[GEST_CABECA]);
  }

  if (gesticulacaoAtual == GEST_CABECA && estado == GESTICULACAO)
    glColor3f(0.0, 2.0, 0.0);
  else
    glColor3f(0.5, 0.0, 1.0);

  glTranslatef(0.0, TORSO_HEIGHT + HEAD_JOINT_SIZE + HEAD_HEIGHT, 0.0);
  glScalef(HEAD_WIDTH, HEAD_HEIGHT, HEAD_WIDTH);

  glutWireCube(1.0);

  glPopMatrix();
}
