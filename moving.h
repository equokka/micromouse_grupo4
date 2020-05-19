#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define COLUMNS 67
#define ROWS 32

// Cria estruturas termios para armazenar os parametros e informações do terminal
struct termios oldtc;
struct termios newtc;

void clearscreen()
{ system("clear"); }

// Esta função faz uso das ANSI escape sequences, sequências de bytes que ao
// serem impressas, são interpretadas pelo terminal como comandos e não como
// caratéres.

// Esta função coloca o terminal no modo cbreak ou rare, no qual o terminal
// interpreta um carater de cada vez, mas continua a reconhecer combinações de
// teclas de controlo, como Ctrl-C.
void cbreak()
{
  // Obtẽm os parâmetros/atributos associados ao terminal e coloca-os na struct
  // termios oldtc
  tcgetattr(STDIN_FILENO, &oldtc);

  // Atribui o valor de oldtc a newtc.
  newtc = oldtc;

  // Modifica a flag c_lflag que controla o modo do terminal, e efetua um
  // bitwise-and com o bitwise-not do bitwise-or das constantes ICANON e ECHO,
  // efetivamente definindo o modo não-canónico e a não-ecoação dos carateres
  // introduzidos. Com o modo canónico desativado, a input do utilizador é dada
  // caratér a carater, sem necessidade de delimitadores como newline, entre
  // outras coisas. Com ECHO desativado, os carateres introduzidos não são
  // ecoados, ou escritos, no ecrã.
  newtc.c_lflag &= ~(ICANON | ECHO);

  // Define os atributos do terminal tal como definidos em newtc, ou seja,
  // desativa o modo canónico e o eco
  tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
}

void nocbreak()
{
  // Repõe os atributos do terminal para aqueles obtidos no início do programa e
  // guardados em oldtc.
  tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
  fflush(stdout);
}

int *up(int **maze, int *pos)
{
  pos[1]++;

  if (maze[pos[1] - 1][pos[0] - 1] != 1)
  { printf("\033[1A"); }
  else
  { pos[1]--; }

  return pos;
}

int *down(int **maze, int *pos)
{
  pos[1]--;

  if (maze[pos[1] - 1][pos[0] - 1] != 1)
  { printf("\033[1B"); }
  else
  { pos[1]++; }

  return pos;
}

int *right(int **maze, int *pos)
{
  pos[0]++;

  if (maze[pos[1] - 1][pos[0] - 1] != 1)
  { printf("\033[1C"); }
  else
  { pos[0]--; }

  return pos;
}

int *left(int **maze, int *pos)
{
  pos[0]--;

  if (maze[pos[1] - 1][pos[0] - 1] != 1)
  { printf("\033[1D"); }
  else
  { pos[0]++; }

  return pos;
}

int mapa(int **maze)
{
  int *pos;
  char tecla;
  pos = malloc(sizeof(int*) * 2);

  // Calcula a posição do S (pisição inicial)
  for(int i = ROWS; i >= 0; i--)
  {
    for(int j = 0; j < COLUMNS; j++)
    {
      if (maze[i][j] == 2)
      {
        pos[0] = i + 2;
        pos[1] = j;
      }
    }
  }

  // Coloca o cursor na posição do S
  printf("\033[%d;%dH", ROWS + 2 - pos[1], pos[0]);

  do
  {
    // Receber tecla premida pelo utilizador
    tecla = getchar();
    char m = tecla;

    switch (m)
    {
      case 'w':
      case 'W':
        pos = up(maze, pos);
        break;
      case 'd':
      case 'D':
        pos = right(maze, pos);
        break;
      case 's':
      case 'S':
        pos = down(maze, pos);
        break;
      case 'a':
      case 'A':
        pos = left(maze, pos);
        break;
    }

    // Se chegar à posição do G o jogo acaba
    if (maze[pos[1] - 1][pos[0] - 1] == 3)
    { printf("\033[34;0HYOU WIN!"); }

    // Fazer isto atẽ o utilizador premir a tecla q
  } while (tecla != 'q' && tecla != 'Q');
}
