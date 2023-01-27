#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#define N 25
#define M 80

void printer(int field[][M]);
void fieldinit(int field[][M]);
void read_from_file(int arr[][M], char name[]);
int allDie(int field[][M]);
int fieldIsStatic(int field[][M], int future[][M]);
void swap(int field[][M], int future[][M]);
int check(int field[][M], int future[][M]);
void reset_m(int arr[][M]);
int checkPoint(int arr[][M], int i, int j);
int changeSpeed(char key, int n);
int kbhit();

int main() {
  double n = 1;
    int field[N][M];
    int future[N][M];
    char key;
    reset_m(field);
    reset_m(future);
    fieldinit(field);
    while (1) {
      if (check(field, future)) {
        printer(field);
        break;
      }
      if (kbhit()) {
        key = getchar();
        if (key == '0' || key == 27) {
          break;
        }
        n = changeSpeed(key, n);
      }
      printer(field);
      usleep(1000000 / n);
    }
    printf("\nGAME OVER...\n");
  return 0;
}
void printer(int field[][M]) {
  printf("\e[H\e[2J\e[3J");
  for (int i = 0; i < M + 2; i++) {
    printf("\033[1;47m  \033[0m");
  }
  printf("\n");
  for (int i = 0; i < N; i++) {
    printf("\033[1;47m  \033[0m");
    for (int j = 0; j < M; j++) {
      if (field[i][j] == 0)
        printf("  ");
      if (field[i][j] == 1)
        printf("\033[1;46m  \033[0m");
    }
    printf("\033[1;47m  \033[0m");
    printf("\n");
  }
  for (int i = 0; i < M + 2; i++) {
    printf("\033[1;47m  \033[0m");
  }
  printf("\n");
}

void fieldinit(int field[][M]) {
  int c = 0;
  printf("Now choose file: ");
  while (1) {
    scanf("%d", &c);
    if (c > 10 || c < 1) {
      printf("No such file...Try again: ");
    } else {
      break;
    }
  }
  if (c == 1) {
    char name[] = "1.txt";
    read_from_file(field, name);
  } else if (c == 2) {
    char name[] = "2.txt";
    read_from_file(field, name);
  } else if (c == 3) {
    char name[] = "3.txt";
    read_from_file(field, name);
  } else if (c == 4) {
    char name[] = "4.txt";
    read_from_file(field, name);
  } else if (c == 5) {
    char name[] = "5.txt";
    read_from_file(field, name);
  } else if (c == 6) {
    char name[] = "6.txt";
    read_from_file(field, name);
  } else if (c == 7) {
    char name[] = "7.txt";
    read_from_file(field, name);
  } else if (c == 8) {
    char name[] = "8.txt";
    read_from_file(field, name);
  } else if (c == 9) {
    char name[] = "9.txt";
    read_from_file(field, name);
  } else if (c == 10) {
    char name[] = "10.txt";
    read_from_file(field, name);
  }
}

int changeSpeed(char key, int n) {
  if (key >= '1' && key <= '9') {
    switch (key) {
    case '1':
      n = 1;
      break;
    case '2':
      n = 2;
      break;
    case '3':
      n = 3;
      break;
    case '4':
      n = 4;
      break;
    case '5':
      n = 5;
      break;
    case '6':
      n = 6;
      break;
    case '7':
      n = 7;
      break;
    case '8':
      n = 8;
      break;
    case '9':
      n = 9;
      break;
    }
  }
  return n;
}

void read_from_file(int arr[][M], char name[]) {
  FILE *file = fopen(name, "r");
  int i = 0;
  int j = 0;
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      printf("\n");
      i++;
      j = 0;
    } else {
      if (c == '0') {
        arr[i][j] = 0;
      }
      if (c == '1') {
        arr[i][j] = 1;
      }
      j++;
    }
  }
}

int check(int field[][M], int future[][M]) {
  reset_m(future);
  int endGame = 0;
  int flag;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      flag = checkPoint(field, i, j);
      if (field[i][j] == 0 && flag == 3) {
        future[i][j] = 1;
      } else if (field[i][j] == 1 && (flag == 2 || flag == 3)) {
        future[i][j] = 1;
      }
    }
  }
  if (allDie(future) || fieldIsStatic(field, future)) {
    printf("Game over!\n");
    endGame = 1;
  }
  swap(field, future);
  return endGame;
}

int allDie(int field[][M]) {
  int counter = 0;
  int f = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      counter += field[i][j];
    }
  }
  if (counter == 0) {
    f = 1;
  }
  return f;
}
int fieldIsStatic(int field[][M], int future[][M]) {
  int f = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (field[i][j] != future[i][j]) {
        f = 0;
      }
    }
  }
  return f;
}

void swap(int field[][M], int future[][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      field[i][j] = future[i][j];
    }
  }
}

int checkPoint(int field[][M], int i, int j) {
  int flag = 0;
  flag += field[(i + 1) % N][j - 1 < 0 ? M - 1 : j - 1];
  flag += field[(i + 1) % N][j];
  flag += field[(i + 1) % N][(j + 1) % M];
  flag += field[i][j - 1 < 0 ? M - 1 : j - 1];
  flag += field[i][(j + 1) % M];
  flag += field[i - 1 < 0 ? N - 1 : i - 1][j - 1 < 0 ? M - 1 : j - 1];
  flag += field[i - 1 < 0 ? N - 1 : i - 1][j];
  flag += field[i - 1 < 0 ? N - 1 : i - 1][(j + 1) % M];
  return flag;
}

void reset_m(int arr[][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      arr[i][j] = 0;
    }
  }
}

int kbhit() {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
