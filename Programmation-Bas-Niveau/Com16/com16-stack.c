/*
  Un compilateur pour expressions arithmétiques
  Cible : machine à pile

  M Billaud, novembre 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <setjmp.h>

#define UNUSED(x) (void)(x)

enum TokenType {
  LEFTPAR     = 0x0001,
  RIGHTPAR    = 0x0002,
  PLUS        = 0x0004,
  MINUS       = 0x0008,
  TIMES       = 0x0010,
  DIV         = 0x0020,

  VARIABLE    = 0x0100,
  NUMBER      = 0x0200,

  ENDOFLINE   = 0x1000,
  ILLEGAL     = 0xF000,
};

struct Scanner {
  char *line;
  int position;
  enum TokenType type;
  char symbol[20];
  int number;
  jmp_buf on_error;
};

void compiler_bug(char message[], int line)
{
  printf("*** COMPILER INTERNAL ERROR ***\nline %d : %s\n", line, message);
  exit (EXIT_FAILURE);
}

/*
  Les 3 fonctions ci-dessous affichent les instructions générées pour une
  expression / un terme / un facteur (ETF) lu à partir de la position actuelle
  du scanner.
  Elles supposent que le scanner est déjà positionné sur le premier
  token de l'ETF
  Après exécution, le scanner est positionné sur le premier token qui
  suit l'ETF
*/

static void compile_expr  (struct Scanner *s);
static void compile_term  (struct Scanner *s);
static void compile_factor(struct Scanner *s);

// --------------------------------------------------------
// analyse lexicale à la mano
//

void getToken(struct Scanner *s)
{
  char c;
  while (isspace(c = s->line[s->position])) {
    s->position++;
  }
  s->type =
    (c == '\0') ? ENDOFLINE :
    (c == '\n') ? ENDOFLINE :
    (c == '#') ? ENDOFLINE :
    (c == '(') ? LEFTPAR :
    (c == ')') ? RIGHTPAR :
    (c == '+') ? PLUS :
    (c == '-') ? MINUS :
    (c == '*') ? TIMES :
    (c == '/') ? DIV :
    isdigit(c) ? NUMBER :
    isalpha(c) ? VARIABLE :
    (c == ')') ? RIGHTPAR :
    ILLEGAL;
  switch (s->type) {
  case NUMBER:
    s->number = 0;
    do {
      s->number *= 10;
      s->number += s->line[s->position++] - '0';
    } while isdigit
    (s->line[s->position]);
    break;
  case VARIABLE:
  {
    int i = 0;
    do {
      s->symbol[i++] = s->line[s->position++];
    } while isalnum
    (s->line[s->position]);
    s->symbol[i] = '\0';
  }
  break;
  case ENDOFLINE:
    if (c == '#') {
      do {
        c = s->line[s->position++];
      } while ( ! iscntrl(c) );
    }
    break;
  case ILLEGAL:
    printf("** caractere illegal rencontré (%d) **\n", c);
    longjmp(s->on_error, 1);	// traitement d'erreur
    break;
  default:
    s->position++;
    break;
  }
}

// ---------------------------------------------------------
// analyse syntaxique et génération
// par descente récursive
//

// Facteur = ( Expr ) | nombre | variable | - Terme

void compile_factor(struct Scanner *s)
{
  switch (s->type) {
  case LEFTPAR:
    getToken(s);
    compile_expr(s);
    if (s->type != RIGHTPAR) {
      printf("** erreur parentheses fermante attendue **\n");
      printf("** rencontre = %04x\n", s->type);
      longjmp(s->on_error, 1);	// traitement d'erreur
    }
    getToken(s);
    break;
  case NUMBER:
    printf("pushint(=%d) ", s->number);
    getToken(s);
    break;
  case MINUS:
    getToken(s);
    if (s->type == NUMBER) {
      printf("pushint(=-%d) ", s->number);
      getToken(s);
    } else {
      compile_term(s);
      printf("opp ");
    }
    break;
  case VARIABLE:
    printf("pushvar(%s) ", s->symbol);
    getToken(s);
    break;
  default:
    printf("** erreur dans terme : "
           "(,-,variable ou nombre attendus\n");
    printf("** rencontre = %04x\n", s->type);
    longjmp(s->on_error, 1);	// traitement d'erreur

  }
}

// --------

// Terme = Facteur {  {*|/} Facteur }*

void compile_term(struct Scanner *s)
{
  compile_factor(s);
  while (s->type & (TIMES | DIV)) {
    enum TokenType t = s->type;
    getToken(s);
    compile_factor(s);
    switch (t) {
    case TIMES:
      printf("mult ");
      break;
    case DIV:
      printf("div ");
      break;
    default:
      compiler_bug("compile_term default case ",__LINE__);
      break;
    }
  }
}

// ------------

// Expr = Terme {  {+|-} Terme }*
void compile_expr(struct Scanner *s)
{
  // printf("<e... ");
  compile_term(s);
  while (s->type & (PLUS | MINUS)) {
    enum TokenType t = s->type;
    getToken(s);
    compile_term(s);
    switch (t) {
    case PLUS:
      printf("plus ");
      break;
    case MINUS:
      printf("minus ");
      break;
    default:
      compiler_bug("compile_expr default case ",__LINE__);
      break;
    }
  }
}

// -------------------------------------------------

void test_compile_line(char line[])
{
  printf("--- compilation de '%s'\n", line);
  struct Scanner s = {.line = line,.position = 0 };
  if (! setjmp(s.on_error)) {
    getToken(&s);
    compile_expr(&s);
    printf("\n\n");
  } else {
    printf("*** erreur pendant la compilation.\n");
  }
}

void test_token(char line[])
{
  printf("--- analyse de '%s'\n", line);
  struct Scanner s = {.line = line,.position = 0 };
  do {
    getToken(&s);
  } while (s.type != ENDOFLINE);
  printf("---\n");
}

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);
  /*
     test_token("A");
     test_token("1");

     test_token("(A)");
     test_token("A+B");
     test_token("2+1");
   */
  test_compile_line("A");
  test_compile_line("1");
  test_compile_line("(A)");
  test_compile_line("A+B");
  test_compile_line(" B*B - 4*A*C ");
  test_compile_line(" (A  + 1) / (B + 2)");
  test_compile_line(" A + 1 # + B");

  return EXIT_SUCCESS;
}
