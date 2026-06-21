#include <stdio.h>
#define EXIT_SUCCESS 0

/* Declare a buffer for user input of size 2048*/
static char input[2048];

int main(int argc, char *argv[]) {
  /* Print Version and Exit Information*/
  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl + C to Exit\n");

  /*Begin RELP*/
  while (1) {
    // Output prompt
    fputs("lispy>", stdout);

    // Read a line of user input of maximum size 2048
    fgets(input, 2048, stdin);

    // Echo input back to user
    printf("No you're a %s", input);
  }

  return EXIT_SUCCESS;
}
