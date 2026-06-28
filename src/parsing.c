#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/history.h>
#include <editline/readline.h>
#endif

int main(int argc, char **argv) {

  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expression = mpc_new("expression");
  mpc_parser_t *Lispy = mpc_new("lispy");
  mpc_parser_t *AB = mpc_new("AB");

  mpca_lang(MPCA_LANG_DEFAULT, "                       \
                number: /-?[0-9]+/;                                     \
                operator: '+' | '-' | '*' | '/';                        \
                expression: <number> | '(' <operator> <expression>+ ')';\
                lispy: /^/ <operator> <expression>+ /$/;                \
                AB: /^[ab]+$/;                                          \
",
            Number, Operator, Expression, Lispy, AB);

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    char *input = readline("lispy> ");
    add_history(input);

    if (strcmp(input, "exit") == 0) {
      printf("goodbye!\n");
      exit(0);
    } else if (strcmp(input, "clear") == 0) {
      // TODO: implement clear console output
    }

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(5, Number, Operator, Expression, Lispy, AB);
  return 0;
}
