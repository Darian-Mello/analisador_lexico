#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool gravouNomeArquivo = false, limpouArquivo = false;
char strNomeArquivo[100];
char retorno[100];

void gravaResultados() {
   int i, num;
   FILE *arquivo;
   
   if (!limpouArquivo) {
      arquivo = fopen("resultados.txt", "w");
      if (arquivo == NULL) {
         printf("Erro ao abrir arquivo\n");
         return;
      } else {
         fprintf(arquivo, " ");
         limpouArquivo = true;
      }
   }
   
   arquivo = fopen("resultados.txt", "a");
   if (arquivo == NULL) {
      printf("Erro ao abrir arquivo\n");
      return;
   }
   if (!gravouNomeArquivo) {
      fprintf(arquivo, "\n\nVerificando %s:\n\n", strNomeArquivo);
      gravouNomeArquivo = true;
   }
   fprintf(arquivo, "%s", retorno);

   printf("%s", retorno);
   memset(retorno, 0, sizeof(retorno));
    
   fclose(arquivo);
}

// Varificacao se e comentario
bool abriuComentario (char ch) {
   if (ch == '{') {
      return true;
   }
   return false;
}

bool fechouComentario (char ch) {
   if (ch == '}') {
      return true;
   }
   return false;
}

// Varificacao se e palavra reservada
bool palavraReservada (char *str) {
   if (!strcmp(str, "if") || !strcmp(str, "then") || !strcmp(str, "else") || !strcmp(str, "end") || !strcmp(str, "repeat") || !strcmp(str, "until") || !strcmp(str, "read") || !strcmp(str, "write")) {
      return true;
   }
   return false;
}

// Varificacao se e identificador
bool identificador (char *str) {
   int i, len = strlen(str);
   if (len == 0) {
      return false;
   }
   for (i = 0; i < len; i++) {
      if (str[i] != 'A' && str[i] != 'B' && str[i] != 'C' && str[i] != 'D' && str[i] != 'E' && str[i] != 'F' && str[i] != 'G' && str[i] != 'H' && str[i] != 'I' && str[i] != 'J' && str[i] != 'K' && str[i] != 'L' && str[i] != 'M' && str[i] != 'N' && str[i] != 'O' && str[i] != 'P' && str[i] != 'Q' && str[i] != 'R' && str[i] != 'S' && str[i] != 'T' && str[i] != 'U' && str[i] != 'V' && str[i] != 'W' && str[i] != 'X' && str[i] != 'Y' && str[i] != 'Z'
       && str[i] != 'a' && str[i] != 'b' && str[i] != 'c' && str[i] != 'd' && str[i] != 'e' && str[i] != 'f' && str[i] != 'g' && str[i] != 'h' && str[i] != 'i' && str[i] != 'j' && str[i] != 'k' && str[i] != 'l' && str[i] != 'm' && str[i] != 'n' && str[i] != 'o' && str[i] != 'p' && str[i] != 'q' && str[i] != 'r' && str[i] != 's' && str[i] != 't' && str[i] != 'u' && str[i] != 'v' && str[i] != 'w' && str[i] != 'x' && str[i] != 'y' && str[i] != 'z') {
         return false;
      }
   }
   return true;
}

// Varificacao se e constante numerica
bool constanteNumerica(char *str) {
   int i, len = strlen(str);
   if (len == 0) {
      return false;
   }
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9') {
         return false;
      }
   }
   return true;
}

// Varificacao se e constante alfanumerica
bool constanteAlfanumerica (char ch) {
   if (ch == '"') {
      return true;
   }
   return false;
}

// Varificacao se e simbolo individual
bool simboloIndividual (char ch) {
   if (ch == '+' || ch == '-' || ch == '*' ||
       ch == '/' || ch == '<' || ch == '=' ||
       ch == ';' || ch == '(' || ch == ')') {
      return true;
   }
   return false;
}

bool simboloAtribuicao (char *str) {
   if (!strcmp(str, ":=")) {
      return true;
   }
   return false;
}

// Varificacao se e delimitador
bool delimitador (char ch) {
   if (ch == ' ' || ch == '\t' || ch == '\n') {
      return true;
   }
   return false;
}

void mostraDelimitador (char ch, int linha) {
   if (ch == ' ') {
      sprintf(retorno,"linha: %d - classe: delimitador - cadeia: espaco\n", linha);
      gravaResultados();
   } else if (ch == '\t') {
      sprintf(retorno,"linha: %d - classe: delimitador - cadeia: tabulacao\n", linha);
      gravaResultados();
   } else if (ch == '\n') {
      sprintf(retorno,"linha: %d - classe: delimitador - cadeia: quebra de linha\n", linha);
      gravaResultados();
   }
}

// Varificacao se e simbolo adicional
bool simboloAdicional (char ch) {
   if (ch == '>') {
      return true;
   }
   return false;
}

void validaToken (char palavra[], int linha) {
   int tamPalavra = strlen(palavra);
   if (tamPalavra == 1) {
      if (simboloIndividual(palavra[0])) {
         sprintf(retorno, "linha: %d - classe: simbolo individual - cadeia: %s\n", linha, palavra);
      } else if (simboloAdicional(palavra[0])) {
         sprintf(retorno, "linha: %d - classe: simbolo adicional - cadeia: %s\n", linha, palavra);
      } else if (identificador(palavra)) {
         sprintf(retorno, "linha: %d - classe: simbolo adicional - cadeia: %s\n", linha, palavra);
      } else if (constanteNumerica(palavra)) {
         sprintf(retorno, "linha: %d - classe: constante numerica - cadeia: %s\n", linha, palavra);
      } else {
         sprintf(retorno, "linha: %d - classe: nao identificado - cadeia: %s\n", linha, palavra);
      }
      gravaResultados();
   } else {
      if (palavraReservada(palavra)) {
         sprintf(retorno, "linha: %d - classe: palavra reservada - cadeia: %s\n", linha, palavra);
      } else if (identificador(palavra)) {
         sprintf(retorno, "linha: %d - classe: identificador - cadeia: %s\n", linha, palavra);
      } else if (constanteNumerica(palavra)) {
         sprintf(retorno, "linha: %d - classe: constante numerica - cadeia: %s\n", linha, palavra);
      } else if (simboloAtribuicao(palavra)) {
         sprintf(retorno, "linha: %d - classe: simbolo de atribuicao - cadeia: %s\n", linha, palavra);
      } else if (palavra[strlen(palavra)-1] == ';') {
         char aux[2];
         aux[0] = palavra[strlen(palavra)-1];
         palavra[strlen(palavra)-1] = '\0';
         validaToken(palavra, linha);
         validaToken(aux, linha);
      } else {
         sprintf(retorno, "linha: %d - classe: nao identificado - cadeia: %s\n", linha, palavra);
      }
      gravaResultados();
   }
}

void verificaArquivo (FILE *arquivo) {
   char c;
   int linha = 1;
   bool comentario = false, alfanumerica = false;
   char palavra[100];
   char palavraComentario[100];
   int tamPalavra = 0, tamPalavraComentario = 0;
   int contPalavras = 0;

   while ((c = fgetc(arquivo)) != EOF) {
      if (abriuComentario(c)) {
         comentario = true;
      } else if (fechouComentario(c)) {
         comentario = false;
         palavraComentario[tamPalavraComentario] = c;
         sprintf(retorno, "linha: %d - classe: comentario - cadeia: %s\n", linha, palavraComentario);
         tamPalavraComentario = 0;
         memset(palavraComentario, 0, sizeof(palavraComentario));
         gravaResultados();
         continue;
      }

      if (!comentario) {
         if (constanteAlfanumerica(c)) {
            if (alfanumerica) {
               palavra[tamPalavra] = c;
               sprintf(retorno, "linha: %d - classe: constante alfanumerica - cadeia: %s\n", linha, palavra);
               alfanumerica = false;
               tamPalavra = 0;
               memset(palavra, 0, sizeof(palavra));
               mostraDelimitador(c, linha);
               continue;
            } else {
               alfanumerica = true;
            }
         }           
         if (delimitador(c) && !alfanumerica) {
            if (tamPalavra > 0) {
               palavra[tamPalavra] = '\0';
               validaToken(palavra, linha);
               tamPalavra = 0;
               memset(palavra, 0, sizeof(palavra));
               mostraDelimitador(c, linha);
            } else {
               mostraDelimitador(c, linha);
            }
         } else {
            palavra[tamPalavra] = c;
            tamPalavra = tamPalavra + 1;
         }
      } else {
         palavraComentario[tamPalavraComentario] = c;
         tamPalavraComentario++;
      }
      
      if (c == '\n') {
         linha = linha + 1;
      }
   }
   if (tamPalavra > 0) {
      palavra[tamPalavra] = '\0';
      validaToken(palavra, linha);
      mostraDelimitador(c, linha);
   }
}

int main () {
   FILE *tinyOk, *tinyErr;
   char *texto;
   int tamanho;

   tinyOk = fopen("tiny_ok.txt", "r");
   tinyErr = fopen("tiny_err.txt", "r");

   if (tinyOk == NULL || tinyErr == NULL) {
      printf("Erro ao abrir os arquivos!");
   } else {
      sprintf(strNomeArquivo,"tinyOk");
      printf("\n\nVerificando tinyOk:\n\n");
      verificaArquivo(tinyOk);
      gravouNomeArquivo = false;
      memset(strNomeArquivo, 0, sizeof(strNomeArquivo));
      sprintf(strNomeArquivo,"tinyErr");
      printf("\n\nVerificando tinyErr: \n\n");
      verificaArquivo(tinyErr);
   }
   
   fclose(tinyOk);
   fclose(tinyErr);
   return 0;
}