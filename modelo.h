
#ifndef MODELO_H
#define MODELO_H

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// A altura do torso define as dimensões de todos os outros elementos
#define TORSO_HEIGHT 0.8
#define TORSO_WIDTH TORSO_HEIGHT * 0.75
#define TORSO TORSO_WIDTH / 3.0

#define FOOT_JOINT_SIZE HEAD_JOINT_SIZE
#define FOOT_HEIGHT FOOT_JOINT_SIZE * 2.0
#define FOOT_WIDTH LO_LEG_WIDTH
#define FOOT FOOT_WIDTH * 2.0
#define UP_ARM_HEIGHT TORSO_HEIGHT * 0.625
#define UP_ARM_WIDTH TORSO_WIDTH / 4.0
#define UP_ARM_JOINT_SIZE HEAD_JOINT_SIZE * 2.0
#define LO_ARM_HEIGHT TORSO_HEIGHT * 0.5
#define LO_ARM_WIDTH UP_ARM_WIDTH
#define LO_ARM_JOINT_SIZE UP_ARM_JOINT_SIZE * 0.75
#define HAND_HEIGHT LO_ARM_HEIGHT / 2.0
#define HAND_WIDTH LO_ARM_WIDTH
#define HAND LO_ARM_WIDTH / 2.0
#define HEAD_WIDTH HEAD_HEIGHT * 0.93
#define HEAD_HEIGHT TORSO_HEIGHT * 0.375
#define HEAD_JOINT_SIZE HEAD_HEIGHT / 6
#define BASE_WIDTH TORSO_WIDTH
#define BASE_HEIGHT TORSO_HEIGHT / 4.0
#define UP_LEG_HEIGHT LO_ARM_HEIGHT
#define UP_LEG_JOINT_SIZE UP_ARM_JOINT_SIZE
#define UP_LEG_WIDTH UP_LEG_JOINT_SIZE * 2.0
#define LO_LEG_HEIGHT UP_LEG_HEIGHT
#define LO_LEG_WIDTH UP_LEG_WIDTH
#define LO_LEG_JOINT_SIZE UP_LEG_JOINT_SIZE
#define LEG_HEIGHT                                                             \
  UP_LEG_HEIGHT + LO_LEG_HEIGHT + FOOT_HEIGHT +                                \
      2 * (FOOT_JOINT_SIZE + UP_LEG_JOINT_SIZE + LO_LEG_JOINT_SIZE)

#define PI 3.141592
#define QUADROS_ENTRE_KEYFRAMES 14

extern double deslocamentoVertical;
extern double keyWalkFrames[2][6];
extern double anguloCoxaEsq, anguloPanturrEsq, anguloCoxaDir, anguloPanturrDir;
extern int frameCaminhadaAtual, keyFrameCaminhadaAtual;

enum lados { ESQUERDA, DIREITA };
enum animacaoAtual { CAMINHADA, ACENANDO, NENHUM };

void init();
void display();
void reshape(int, int);
void kbd(unsigned char, int, int);
void timer(int);
void mouseHandler(int, int, int, int);
void criaMenu();
void menuPrincipal(int);

void quadril();
void perna(enum lados);
void panturrilha();
void pe();
void coxa();
void pernas();
void torso();
void braco();
void antebraco();
void bracos();
void cabeca();

double movimentacaoVertical(double, double, double, double);
void animacaoCaminhada();
void calculaAnimacaoCaminhada(float, float, float, float);

#endif
