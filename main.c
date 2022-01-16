#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NewTodoFlag "-n"
#define ShowTodosFlag "-a"
#define TodosFileName "todos.txt"

void writeTodo(char *text);
void printAllTodos(void);
int getTodosCount(void);

struct todo {
  int id;
  int done;
  char *text;
};

int main(int argc, char** argv) {
  if (argc > 1) {
    if (strcmp(argv[1], NewTodoFlag) == 0) {
      if (argv[2] != NULL) {
        writeTodo(argv[2]);
      }
    } else if (strcmp(argv[1], ShowTodosFlag) == 0) {
      printAllTodos();
    }
  } else {
    puts("Flags:");
    printf("Show all todos: %s\n", ShowTodosFlag);
    printf("Create new todo: %s \"new todo text\"\n", NewTodoFlag);
  }
}

int completeTodo(int todoId) {
  // remove todo and decrement id
}

void writeTodo(char *text) {
  FILE *fp = fopen(TodosFileName, "a+");
  if (!fp) {
    puts("Can't open todos file");
    return;
  } 

  int len = strlen(text);
  if (len < 1) {
    return;
  }
  int currentTodoCount = getTodosCount();

  /*
  char idText[20];
  sprintf(idText, "%d", currentTodoCount);
  for (int i = 0; i < strlen(idText); i++) {
    putc(idText[i], fp);
  }
  putc(' ', fp);
  */
  for (int i = 0; i < len; i++) {
    putc(text[i], fp);
  }
  putc('\n', fp);
  fclose(fp);
}

void printAllTodos() {
  FILE *fp = fopen(TodosFileName, "r");
  if (!fp) {
    puts("Failed to find todos file. Try creating a todo");
    return;
  }
  int c;
  int lineCount = 0;
  putc('0', stdout);
  putc(' ', stdout);
  while((c = getc(fp)) != EOF) {
    if (c == '\n') {
      if (lineCount > 0) {
        lineCount += 1;
        putc('\n', stdout);
        char idText[20];
        sprintf(idText, "%d", lineCount);
        for (int i = 0; i < strlen(idText); i++) {
          putc(idText[i], stdout);
        }
        putc(' ', stdout);
      }
    } else {
      putc(c, stdout);
    }
  }
  fclose(fp);
}

int getTodosCount() {
  int count = 0;
  FILE *fp = fopen(TodosFileName, "r");
  if (!fp) {
    puts("Can't open file");
    return count;
  }
  int c;
  while((c = getc(fp)) != EOF) {
    if (c == '\n') {
      count += 1;
    }
  }
  fclose(fp);
  return count;
}




