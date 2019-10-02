#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 func0:
    "Monster %s attack to %s with %d damage.\n"
    attack:  lives -= 8 or +4
    defend: "%s has stopped the attack.\n"
  func1:
    "Monster %s defends with %d of defense.\n"
    attack: lives -= 4 or +8
    defend: "%s defends too.\n"
  func2:
    "%s roar to %s.\n"
    attack: "%s hit a critical to %s.\n", lives += 10
    defend: "%s defends.\n"

  When we defend, it doesn't change the lives count.
  The target is to set lives < 0 to get the chunks freed but not the process
  exiting.
  We start with 16 lives.
*/

int main(int argc, char* argv[]) {
    const char* players[] = {
        "fataku", "hds", "beford", "emyei", "g05u", "SELF"};

    if (argc < 2) {
      printf("Usage: %s <timestamp>\n", argv[0]);
      return 1;
    }
    int token = atoi(argv[1]);
    token >>= 8;
    srand(token);

    const int static_proba = 4;
    int lives = 16;
    int player_target = 0;
    int func_target = 0;    
    char values[1024];
    size_t index = 0;
    memset(values, 0, sizeof(values));

    while (lives != 0) {
      player_target = (rand() % 6);
      func_target = (rand() % 3);    
      printf("lives: %d ; player = %s ; func = %d\n", 
          lives, players[player_target], func_target);

      switch (func_target) {
        case 0:
          if (static_proba < rand() % 10) {
            if (lives > 0 && lives != 8) {
              printf("attack\n");
              values[index++] = '3';
              lives -= 8;
            } else {
              printf("defend\n");
              values[index++] = '4';
            }
          } else {
            if (lives < 0) {
              printf("attack\n");
              values[index++] = '3';
              lives += 4;
            } else {
              printf("defend\n");
              values[index++] = '4';
            }
          }
          break;

        case 1: {
          int n = rand();
          unsigned int n2 = (unsigned int)(n >> 0x1f) >> 0x1d;
          n = (n + n2 & 7) - n2;
          if (n < static_proba) {
            if (lives < 0) {
              printf("attack\n");
              values[index++] = '3';
              lives += 8;
            } else {
              printf("defend\n");
              values[index++] = '4';
            }
          } else {
            if (lives > 0 && lives != 4) {
              printf("attack\n");
              values[index++] = '3';
              lives -= 4;
            } else {
              printf("defend\n");
              values[index++] = '4';
            }
          }
          break;
        }

        case 2: 
          if (lives <= -10) {
            printf("attack\n");
            values[index++] = '3';
            lives += 10;
          } else {
            printf("defend\n");
            values[index++] = '4';
          }
          break;
      }
    }

    printf("\n0\nBBBBBBBBBBBBBBB\n");
    for (int i = 0; i < index; i++) {
      printf("%c\n", values[i]);
    }

    return 0;
}