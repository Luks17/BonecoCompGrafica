
#include "modelo.h"

double anguloMovimento[9];
double movimentoEixoX[9];
double movimentoEixoY[9];
double movimentoEixoZ[9];

// quando o frameCaminhadaAtual chega a 0, keyFrameCaminhadaAtual é incrementado
// até ele chegar em 7, onde ele volta para 0
int frameCaminhadaAtual = QUADROS_ENTRE_KEYFRAMES, keyFrameCaminhadaAtual = 0;

// quando alguem anda, ele realiza um leve deslocamento vertical de cima para
// baixo com cada passo, isso é calculado nesta função
double movimentacaoVertical(double angulo_coxa_esq, double angulo_panturr_esq,
                            double angulo_coxa_dir, double angulo_panturr_dir) {

  double movimentacao_coxa, movimentacao_panturrilha, mov_perna_esquerda,
      mov_perna_direita, mov_coxa_rad, mov_panturrilha_rad;

  // converte angulos para radianos
  // calcula movimentacao vertical da perna ESQUERDA
  mov_coxa_rad = (PI * angulo_coxa_esq) / 180.0;
  mov_panturrilha_rad = (PI * angulo_panturr_esq - angulo_coxa_esq) / 180.0;

  movimentacao_coxa =
      (UP_LEG_HEIGHT + 2 * UP_LEG_JOINT_SIZE) * cos(mov_coxa_rad);
  movimentacao_panturrilha =
      (LO_LEG_HEIGHT + 2 * (LO_LEG_JOINT_SIZE + FOOT_JOINT_SIZE) +
       FOOT_HEIGHT) *
      cos(mov_panturrilha_rad);
  mov_perna_esquerda =
      LEG_HEIGHT - (movimentacao_coxa + movimentacao_panturrilha);

  // converte angulos para radianos
  // calcula movimentacao vertical da perna DIREITA
  mov_coxa_rad = (PI * angulo_coxa_dir) / 180.0;
  mov_panturrilha_rad = (PI * angulo_panturr_dir - angulo_coxa_dir) / 180.0;

  movimentacao_coxa =
      (UP_LEG_HEIGHT + 2 * UP_LEG_JOINT_SIZE) * cos(mov_coxa_rad);
  movimentacao_panturrilha =
      (LO_LEG_HEIGHT + 2 * (LO_LEG_JOINT_SIZE + FOOT_JOINT_SIZE) +
       FOOT_HEIGHT) *
      cos(mov_panturrilha_rad);
  mov_perna_direita =
      LEG_HEIGHT - (movimentacao_coxa + movimentacao_panturrilha);

  // compara a movimentação vertical de ambas as pernas, a que tiver menor
  // deslocamento é a perna que está tocando o chão, logo é retornada
  return (mov_perna_esquerda <= mov_perna_direita) ? (-mov_perna_esquerda)
                                                   : (-mov_perna_direita);
}

void animacaoCaminhada() {
  // as variaveis de diferenca são definidas em cada frame baseado no livro
  // de animação "Moving Pictures" (menos as animacoes dos bracos, elas foram
  // feitas pelo Lucas mesmo). No total são 8, por isso o número de keyFrames é
  // 8 também (switch case de 0 a 7);
  // as variaveis de soma (que estao na funcao calculaAnimacaoCaminhada) são
  // calculadas pegando as variaveis de diferenca e dividindo pelo total de
  // quadros entre keyFrame, com isso é possível ter movimentos intermediários
  // entre keyframes
  float diferencaCoxaEsq, diferencaCoxaDir, diferencaPanturrEsq,
      diferencaPanturrDir, diferencaBracoEsq, diferencaBracoDir;

  switch (keyFrameCaminhadaAtual) {
  case 0:
    diferencaCoxaEsq = 15;
    diferencaCoxaDir = 5;
    diferencaPanturrEsq = 15;
    diferencaPanturrDir = 5;

    diferencaBracoEsq = 4;
    diferencaBracoDir = -4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 1:
    diferencaCoxaEsq = 20;
    diferencaCoxaDir = -65;
    diferencaPanturrEsq = -15;
    diferencaPanturrDir = 85;

    diferencaBracoEsq = 4;
    diferencaBracoDir = -4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 2:
    diferencaCoxaEsq = 5;
    diferencaCoxaDir = -25;
    diferencaPanturrEsq = 10;
    diferencaPanturrDir = -40;

    diferencaBracoEsq = -4;
    diferencaBracoDir = 4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 3:
    diferencaCoxaEsq = 20;
    diferencaCoxaDir = 25;
    diferencaPanturrEsq = -10;
    diferencaPanturrDir = -50;

    diferencaBracoEsq = -4;
    diferencaBracoDir = 4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 4:
    diferencaCoxaEsq = 5;
    diferencaCoxaDir = 15;
    diferencaPanturrEsq = 5;
    diferencaPanturrDir = 15;

    diferencaBracoEsq = -4;
    diferencaBracoDir = 4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 5:
    diferencaCoxaEsq = -65;
    diferencaCoxaDir = 20;
    diferencaPanturrEsq = 85;
    diferencaPanturrDir = -15;

    diferencaBracoEsq = -4;
    diferencaBracoDir = 4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 6:
    diferencaCoxaEsq = -25;
    diferencaCoxaDir = 5;
    diferencaPanturrEsq = -40;
    diferencaPanturrDir = 10;

    diferencaBracoEsq = 4;
    diferencaBracoDir = -4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  case 7:
    diferencaCoxaEsq = 25;
    diferencaCoxaDir = 20;
    diferencaPanturrEsq = -50;
    diferencaPanturrDir = -10;

    diferencaBracoEsq = 4;
    diferencaBracoDir = -4;

    calculaAnimacaoCaminhada(diferencaCoxaEsq, diferencaCoxaDir,
                             diferencaPanturrEsq, diferencaPanturrDir,
                             diferencaBracoEsq, diferencaBracoDir);
    break;
  }

  glutPostRedisplay();
}

void calculaAnimacaoCaminhada(float diffCoxaEsq, float diffCoxaDir,
                              float diffPanturrEsq, float diffPanturrDir,
                              float diffBracoEsq, float diffBracoDir) {
  float somaCoxaEsq, somaCoxaDir, somaPanturrEsq, somaPanturrDir, somaBracoEsq,
      somaBracoDir;

  somaBracoEsq = diffBracoEsq / QUADROS_ENTRE_KEYFRAMES;
  somaBracoDir = diffBracoDir / QUADROS_ENTRE_KEYFRAMES;

  somaCoxaEsq = diffCoxaEsq / QUADROS_ENTRE_KEYFRAMES;
  somaCoxaDir = diffCoxaDir / QUADROS_ENTRE_KEYFRAMES;
  somaPanturrEsq = diffPanturrEsq / QUADROS_ENTRE_KEYFRAMES;
  somaPanturrDir = diffPanturrDir / QUADROS_ENTRE_KEYFRAMES;

  keyWalkFrames[0][2] += somaBracoEsq;
  keyWalkFrames[1][2] += somaBracoDir;

  keyWalkFrames[0][3] += somaCoxaDir;
  keyWalkFrames[1][3] += somaCoxaEsq;
  keyWalkFrames[0][4] += somaPanturrDir;
  keyWalkFrames[1][4] += somaPanturrEsq;

  anguloCoxaEsq -= somaCoxaEsq;
  anguloPanturrEsq -= somaPanturrEsq;
  anguloCoxaDir -= somaCoxaDir;
  anguloPanturrDir -= somaPanturrDir;
  deslocamentoVertical = movimentacaoVertical(anguloCoxaEsq, anguloPanturrEsq,
                                              anguloCoxaDir, anguloPanturrDir);
  frameCaminhadaAtual--;
  if (frameCaminhadaAtual == 0) {
    keyFrameCaminhadaAtual = (keyFrameCaminhadaAtual + 1) % 8;
    frameCaminhadaAtual = QUADROS_ENTRE_KEYFRAMES;
  }
}

void gesticulacao(enum sentidoMovimento sentido) {
  switch (sentido) {
  case 0:
    if (gesticulacaoAtual == GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] <= -8.0)
      return;
    if (gesticulacaoAtual != GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] <= -100.0)
      return;
    if ((gesticulacaoAtual == GEST_ANTEBRACO_ESQ ||
         gesticulacaoAtual == GEST_ANTEBRACO_DIR) &&
        anguloMovimento[gesticulacaoAtual] <= -12.0)
      return;
    if ((gesticulacaoAtual == GEST_PANTURRILHA_ESQ ||
         gesticulacaoAtual == GEST_PANTURRILHA_DIR) &&
        anguloMovimento[gesticulacaoAtual] == 0)
      return;

    anguloMovimento[gesticulacaoAtual] += -0.5;
    movimentoEixoX[gesticulacaoAtual] = 1.0;
    movimentoEixoZ[gesticulacaoAtual] = 0.0;
    break;
  case 1:
    if (gesticulacaoAtual == GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] >= 8.0)
      return;
    if (gesticulacaoAtual != GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] >= 100.0)
      return;
    if ((gesticulacaoAtual == GEST_ANTEBRACO_ESQ ||
         gesticulacaoAtual == GEST_ANTEBRACO_DIR) &&
        anguloMovimento[gesticulacaoAtual] == 0)
      return;
    if ((gesticulacaoAtual == GEST_PANTURRILHA_ESQ ||
         gesticulacaoAtual == GEST_PANTURRILHA_DIR) &&
        anguloMovimento[gesticulacaoAtual] >= 90.0)
      return;

    anguloMovimento[gesticulacaoAtual] += 0.5;
    movimentoEixoX[gesticulacaoAtual] = 1.0;
    movimentoEixoZ[gesticulacaoAtual] = 0.0;
    break;
  case 2:
    if (gesticulacaoAtual == GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] <= -8.0)
      return;
    if (gesticulacaoAtual != GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] <= -100.0)
      return;
    if (gesticulacaoAtual == GEST_ANTEBRACO_ESQ ||
        gesticulacaoAtual == GEST_ANTEBRACO_DIR)
      return;
    if (gesticulacaoAtual == GEST_PANTURRILHA_ESQ ||
        gesticulacaoAtual == GEST_PANTURRILHA_DIR)
      return;

    anguloMovimento[gesticulacaoAtual] += -0.5;
    movimentoEixoX[gesticulacaoAtual] = 0.0;
    movimentoEixoZ[gesticulacaoAtual] = 1.0;
    break;
  case 3:
    if (gesticulacaoAtual == GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] >= 8.0)
      return;
    if (gesticulacaoAtual != GEST_CABECA &&
        anguloMovimento[gesticulacaoAtual] >= 100.0)
      return;
    if (gesticulacaoAtual == GEST_ANTEBRACO_ESQ ||
        gesticulacaoAtual == GEST_ANTEBRACO_DIR)
      return;
    if (gesticulacaoAtual == GEST_PANTURRILHA_ESQ ||
        gesticulacaoAtual == GEST_PANTURRILHA_DIR)
      return;

    anguloMovimento[gesticulacaoAtual] += 0.5;
    movimentoEixoX[gesticulacaoAtual] = 0.0;
    movimentoEixoZ[gesticulacaoAtual] = 1.0;
    break;
  }
}
