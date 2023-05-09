// File: treasure_hunt.cpp
// Author: Chia Chi Lin
//
// DATE 04/30/2023
// g++ -o treasure_hunt treasure_hunt.cpp
// ./treasure_hunt
// valgrind ./treasure_hunt

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using std::string;

const int max_board = 10;
const int num_Rows = 10;
const int num_Cols = 10;

const int bronze_l = 5;
const int bronze = 11;
const int silver_l = 4;
const int silver = 12;
const int gold_l = 3;
const int gold = 13;
const int rubies_l = 2;
const int rubies = 14;
const int vibranium_l = 1;
const int vibranium = 15;

// I need to modify the numbers in this 2d-array, so I won't add const to it.
int *arr2d = new int[num_Rows * num_Cols];
int *arr2d_ai = new int[num_Rows * num_Cols];

bool checkPlacement(int *ptr_arr, int row, int col, int length, char row_or_col) {

  int real_row = row - 1;
  int real_col = col - 1;
  // if we want to put gold in 1,1 and length is 8
  // if we worte if row add length can not bigger than 8,
  // the code will return false, but in fact, this is feasible,
  // so row + length must be less than or equal to 9

  if (row > num_Rows || col > num_Cols) {
    return false;
  } else if (length > num_Rows) {
    return false;
  }

  if (row_or_col == 'r') {
    if (real_row + length > num_Rows) {
      return false;
    }

    for (int i = real_row; i < real_row + length; i++) {

      int offset = (i * num_Rows) + col - 1;
      if (ptr_arr[offset] != 0) {
        return false;
      }
    }

  } else if (row_or_col == 'c') {
    if (real_col + length > num_Cols) {
      return false;
    }

    for (int i = col; i < col + length; i++) {

      int offset = (real_row * num_Rows) + i - 1;
      if (ptr_arr[offset] != 0) {
        return false;
      }
    }
  }

  return true;
}

void setByOffset2(int *ptr_arr, int row, int col, int length, int number,
                  char row_or_col) {

  bool seeP = checkPlacement(ptr_arr, row, col, length, row_or_col);

  // i do not like checkPlacement(ptr_arr, row, col, length, row_or_col);
  if (!checkPlacement(ptr_arr, row, col, length, row_or_col)) {
    printf("error\n\n");
    return;
  }

  // int offset = (row * num_Rows) + col - 1;
  int real_row = row - 1;

  if (row_or_col == 'r') {

    for (int i = real_row; i < real_row + length; i++) {
      int offset = (i * num_Rows) + col - 1;
      ptr_arr[offset] = number;
    }
  } else if (row_or_col == 'c') {

    for (int i = col; i < col + length; i++) {
      int offset = (real_row * num_Rows) + i - 1;
      ptr_arr[offset] = number;
    }
  }
}

void print_2dArray(int *ptr_arr) {

  for (int row = 0; row < num_Rows; row++) {
    for (int col = 0; col < num_Cols; col++) {

      printf("%d ", ptr_arr[(row * num_Cols) + col]);
    }
    printf("\n");
  }
  printf("\n");
}

void show(int *ptr_arr, int row, int col) {

  for (int x = 0; x < row; x++) {
    for (int y = 0; y < col; y++) {

      // This integer is used to keep track of my current position in this fake
      // 2d-array, and make my code more readable.
      int count = (x * 8) + y;

      if (ptr_arr[count] == 0 || ptr_arr[count] > 0) {
        printf("- ");
      } else if (ptr_arr[count] == -1) {
        printf("X ");
      } else if (ptr_arr[count] < 0) {
        printf("@ ");
      }
    }
    printf("\n");
  }
}

void dig(int *ptr_arr, int row, int col) {

  for (int x = 0; x < row; x++) {
    for (int y = 0; y < col; y++) {

      int count = (x * num_Rows) + y;

      if (ptr_arr[count] == 0) {
        ptr_arr[count] = -1;
        printf("%d ", ptr_arr[count]);
      } else if (ptr_arr[count] > 0) {
        ptr_arr[count] = ptr_arr[count] * -1;
        printf("%d ", ptr_arr[count]);
      } else {
        printf("%d ", ptr_arr[count]);
      }
    }
    printf("\n");
  }
}

void user_put(string chest_type, int chest_l, int chest_n) {
  int r = 0;
  int c = 0;
  int reNum;
  char rorc;
  char just;
  bool seevalid = false;

  printf("Now we are going to place the %s chest.\n", chest_type.c_str());
  while (!seevalid) {
    printf("Please enter two numbers of row and col\n");
    reNum = scanf(" %d, %d", &r, &c);
    
    //reNum = getchar();
    
    printf("Please enter a character to decide if you want to place it in "
           "columns or rows.\n");
    printf("enter r or c\n");

    do {
      just = scanf(" %c", &rorc);
      if (rorc != 'r' && rorc != 'c') {
        printf("try again! enter a character\n");
        
        //just = getchar();
        
      }
    } while (rorc != 'r' && rorc != 'c');

    seevalid = checkPlacement(arr2d, r, c, chest_l, rorc);

    if (!seevalid) {
      printf("Try again!\n");
    }
  }

  setByOffset2(arr2d, r, c, chest_l, chest_n, rorc);

  print_2dArray(arr2d);
  printf("\n");
}

void ai_put(int chest_l, int chest_n) {

  bool seevalid = false;
  char rorc;
  int rorc2;
  int r;
  int c;

  while (!seevalid) {
    r = 1 + (rand() % (max_board));
    c = 1 + (rand() % (max_board));
    rorc2 = 1 + rand() % (2);

    // note: later //
    // printf("r: %d c: %d rorc2: %d\n",r, c, rorc2);

    if (rorc2 == 1) {
      rorc = 'r';
    } else if (rorc2 == 2) {
      rorc = 'c';
    }
    seevalid = checkPlacement(arr2d_ai, r, c, chest_l, rorc);
  }

  setByOffset2(arr2d_ai, r, c, chest_l, chest_n, rorc);
}

void print_ai() {
  for (int x = 0; x < num_Rows; x++) {
    for (int y = 0; y < num_Cols; y++) {
      int count = (x * num_Rows) + y;

      if (arr2d_ai[count] > -1) {
        printf("- ");
      } else if (arr2d_ai[count] == -1) {
        printf("X ");
      } else if (arr2d_ai[count] < -1) {
        printf("@ ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void print_user() {

  // note the first is 0, 0. the last is 9*10+9
  for (int x = 0; x < num_Rows; x++) {
    for (int y = 0; y < num_Cols; y++) {

      int val = *(arr2d + x * num_Rows + y);

      if (val == 0) {
        printf("- ");
      } else if (val == -1) {
        printf("X ");
      } else if (val > 10 && val < 17) {
        printf("%c ", 'a' + val - 11);
      } else if (val < 0 && val > -16) {
        printf("%c ", 'A' + (val * -1) - 11);
      } else {
        printf("%d", val);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void dig2(int *ptr_arr, int row, int col) {

  int real_row = row - 1;

  int count = (real_row * num_Rows) + col - 1;

  if (ptr_arr[count] == 0) {
    ptr_arr[count] = -1;

  } else if (ptr_arr[count] > 0) {
    ptr_arr[count] = ptr_arr[count] * -1;
  }
}

// Check the AI's grid to confirm that each number is smaller than 0
// indicating that no treasure chest remains undiscovered.
int user_win() {

  for (int x = 0; x < num_Rows; x++) {
    for (int y = 0; y < num_Cols; y++) {

      int count = (x * num_Rows) + y;

      if (arr2d_ai[count] > 0) {
        return 0;
      }
    }
  }

  return 344;
}

// Check the player's grid to confirm that each number is smaller than 0
// indicating that no treasure chest remains undiscovered.
int ai_win() {

  for (int x = 0; x < num_Rows; x++) {
    for (int y = 0; y < num_Cols; y++) {

      int count = (x * num_Rows) + y;

      if (arr2d[count] > 0) {
        return 0;
      }
    }
  }

  return 1;
}

bool ai_wnat_win(int r, int c) {

  int count = (r * num_Rows) + c - 1;
  if (arr2d[count] < 0) {
    return false;
  }
  return true;
}

char play() {

  int r;
  int c;
  int back;

  int ai_r;
  int ai_c;

  int user_w = 0;
  int ai_w = 0;

  while (user_w == 0 && ai_w == 0) {
    printf("Please enter two numbers of row and col\n");
    back = scanf(" %d, %d", &r, &c);
    dig2(arr2d_ai, r, c);

    do {
      ai_c = 1 + (rand() % (max_board));
      ai_r = 1 + (rand() % (max_board));
    } while (!ai_wnat_win(r, c));

    dig2(arr2d, ai_r, ai_c);

    print_user();
    print_ai();

    user_w = user_win();
    ai_w = ai_win();
  }

  if (user_w == 344) {
    return 'u';
  } else if (ai_w == 1) {
    return 'a';
  }

  return 'n';
}

int main(int argc, char **argv) {

  srand(time(NULL));

  printf("\n\n");
  print_2dArray(arr2d);
  printf("\n\n");

  user_put("bronze", bronze_l, bronze);
  user_put("silver", silver_l, silver);
  user_put("gold", gold_l, gold);
  user_put("rubies", rubies_l, rubies);
  user_put("vibranium", vibranium_l, vibranium);

  ai_put(bronze_l, bronze);
  ai_put(silver_l, silver);
  ai_put(gold_l, gold);
  ai_put(rubies_l, rubies);
  ai_put(vibranium_l, vibranium);

  print_2dArray(arr2d_ai);
  print_user();
  print_ai();

  char win = 'n';
  printf("The game is starting.\n");
  printf("please enter the coordinates to search for the enemy's chest\n");

  win = play();

  if (win == 'u') {
    printf("Player win!");
  } else if (win == 'a') {
    printf("AI win!");
  }

  // last_things
  // say bye bye the this world arr2d. I will not miss you
  delete[] arr2d;
  delete[] arr2d_ai;
}