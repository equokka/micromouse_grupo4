#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <moving.h>
#include <reading.h>

int main(int argc, char* argv[])
{
  int **maze;
  int socketfd;
  int ret;
  char buff[255];
  char key;
  bool quitting = false;
  bool error = false;
  struct sockaddr_in server;
  int len = sizeof(struct sockaddr_in);

  // Create socket
  socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketfd < 0)
  { printf("Socket error\n"); return 1; }

  // Wildcards
  server.sin_family = AF_INET;
  server.sin_port = htons(8000);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Limpar o ecrã
  clearscreen();

  // Colocar o terminal no modo cbreak ou rare
  cbreak();

  // Hail the server.
  snprintf(buff, sizeof(buff), "HELLO");
  ret = sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&server, sizeof(server));
  // Error handling
  if (ret < 0)
  {
    printf("Error sending message\n");
    quitting = true;
    error = true;
  }
  // Receive map from the server.
  ret = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&server, &len);
  // Error handling
  if (ret < 0)
  {
    printf("Error when receiving\n");
    quitting = true;
    error = true;
  }

  // Set map to what we got from the server.
  maze = read_map(buff);

  // Inicia o movimento do cursor utilizando a matriz
  int *pos = map_setup(maze);

  do
  {
    // Get keypress, put it in the message buffer.
    key = (char)getchar();
    buff[0] = key;
    buff[1] = 0;

    // Send the key to the server.
    ret = sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&server, sizeof(server));
    // Error handling
    if (ret < 0)
    {
      printf("Error sending message\n");
      quitting = true;
      error = true;
    }
    // Receive reply from the server.
    ret = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&server, &len);
    // Error handling
    if (ret < 0)
    {
      printf("Error when receiving\n");
      quitting = true;
      error = true;
    }

    // Check if the server approves.
    if (strcmp(buff, "OK") == 0)
    {
      // Quit on Q
      if (key == 'q')
      { quitting = true; }
      // Move on WASD
      else
      {
        switch(key) {
          case 'w': // "cima"
            up(maze, pos);
            break;
          case 's': // "baixo"
            down(maze, pos);
            break;
          case 'd': // "direita"
            right(maze, pos);
            break;
          case 'a': // "esquerda"
            left(maze, pos);
            break;
        }
      }
    }
    // Quit on error reply.
    else if (strcmp(buff, "ERROR") == 0)
    {
      quitting = true;
      error = true;
    }

    // If we get to G (goal), end the game.
    // TODO: handle winning better than this
    if (maze[pos[1] - 1][pos[0] - 1] == 3)
    { printf("\033[34;0HYOU WIN!"); }

    // Fazer isto atẽ o utilizador premir a key q
  } while (quitting == false);

  // Por o terminal de volta no modo cooked
  nocbreak();

  clearscreen();

  return (error ? 1 : 0);
}

