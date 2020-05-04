#include <stdio.h>
#include <ctype.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define STRING
#define FLOAT
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define Str_LIT
#define Float_LIT

/* main driver */
int main(void) {
/* Open the input data file and process its contents */
 if ((in_fp = fopen("front.in", "r")) == NULL)
 printf("ERROR - cannot open front.in \n");
 else {
 getChar();
 do {
 lex();
 } while (nextToken != EOF);
 }
 return 0;
}

/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
 if (lexLen <= 98) {
 lexeme[lexLen++] = nextChar;
 lexeme[lexLen] = '\0';
 }
 else
 printf("Error - lexeme is too long \n");
}
/*input and determine its character class */
void getChar(void) {
if ((nextChar = getc(in_fp)) != EOF) {
  if (isalpha(nextChar))
    charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
      else
      charClass = UNKNOWN;
}
    else
charClass = EOF;
}
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
 while (isspace(nextChar))
 getChar();
} expressions */
int lex(void) {
 lexLen = 0;
 getNonBlank();
 switch (charClass) {
/* Identifiers */
 case LETTER:
 addChar();
 getChar();
 while (charClass == LETTER || charClass == DIGIT) {
 addChar();
 getChar();
 }
 nextToken = IDENT;
 break;
/* Integer literals */
 case DIGIT:
 addChar();
 getChar();
 while (charClass == DIGIT) {
 addChar();
 getChar();
 }
 nextToken = INT_LIT;
 break;
 /* String literals */
  case STRING:
  addChar();
  getChar();
  while (charClass == STRING) {
  addChar();
  getChar();
  }
  nextToken = STR_LIT;
  break;
  /* FLOAT literals */
   case FLOAT:
   addChar();
   getChar();
   while (charClass == FLOAT) {
   addChar();
   getChar();
   }
   nextToken = Float_LIT;
   break;
/* Parentheses and operators */
 case UNKNOWN:
 lookup(nextChar);getChar();
 break;
/* EOF */
 case EOF:
 nextToken = EOF;
 lexeme[0] = 'E';
 lexeme[1] = 'O';
 lexeme[2] = 'F';
 lexeme[3] = '\0';
 break;
 } /* End of switch */
 printf("Next token is: %d, Next lexeme is %s\n",
 nextToken, lexeme);
 return nextToken;
} /* End of function lex */
