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
#define PORT 8080

int main(int argc, char* argv[])
{
  int **maze; //vem do reading.h
  int socketfd;
  int ret;
  int facing = 0;
  char buff[255];
  char status[255];
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
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

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

  // Set map & gamemode to what we got from the server.
  int gamemode = ((int) buff[0]) - 48;

  char bufmap[255];
  bufmap[0] = '\0';
  for (int i = 1; i < strlen(buff); i++) {
    strncat(bufmap, &buff[i], 1);
  }

  maze = read_map(bufmap);

  // Inicia o movimento do cursor utilizando a matriz
  int *pos = map_setup(maze);
  set_cursor(pos);

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

    // Quit on Q
    if (key == 'q' && strcmp(buff, "OK") == 0)
    { quitting = true; }

    // Quit on error reply.
    if (strcmp(buff, "ERROR") == 0)
    {
      quitting = true;
      error = true;
    }

    // Regular gamemode
    if (gamemode == 1)
    {
      // Check if the server approves.
      if (strcmp(buff, "OK") == 0)
      {
        // Move on WASD
        switch(key) {
          case 'w': up(maze,    pos); break;
          case 's': down(maze,  pos); break;
          case 'd': right(maze, pos); break;
          case 'a': left(maze,  pos); break;
        }
      }
    }

    // Three-key gamemode
    else if (gamemode == 2)
    {
      // Forward
      if (key == 'w')
      {
        if (strcmp(buff, "OK") == 0)
        {
          if      (facing == 0) { up(maze,    pos); }
          else if (facing == 1) { right(maze, pos); }
          else if (facing == 2) { down(maze,  pos); }
          else if (facing == 3) { left(maze,  pos); }
        }
      }
      // Turning
      else if (key == 'd' || key == 'a')
      {
        // If we're turning, we're expecting a message like this:
        // <0,1,2,3>OK
        // where the number is for updating the facing variable.
        status[0] = '\0';
        for (int i = 1; i < strlen(buff); i++) {
          strncat(status, &buff[i], 1);
        }

        if (strcmp(status, "OK") == 0)
        { facing = ((int) buff[0]) - 48; }
      }
    }

    // If we get to G (goal), end the game.
    // TODO: handle winning better than this
    if (maze[pos[1] - 1][pos[0] - 1] == 3)
    { printf("\033[34;0H YOU WIN!"); }

    // Fazer isto atẽ o utilizador premir a key q
  } while (quitting == false);

  // Por o terminal de volta no modo cooked
  nocbreak();

  clearscreen();

  return (error ? 1 : 0);
}
