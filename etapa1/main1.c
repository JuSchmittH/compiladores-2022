int main(int argc, char **argv) {
  int tok;
  if (argc < 2) {
    fprintf(stderr, "Call: ./etapa1.out file_name\n");
    exit(1);
  }
  yyin = fopen(argv[1], "r");

  initMe();

  while(running) {
      tok = yylex();
      if(running == 0) break;
      switch(tok)
      {
          case TOKEN_ERROR: printf("Unexpected token %d\n", tok);
              break;
          default: printf("Encontrei %c\n", yytext[0]);
              break; 
      }

  }
  printf("Main done! File has %d lines\n", lineNumber);
  hashPrint();
  exit(0);
}
