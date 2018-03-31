#include"stdafx.h"
#include <cstdio>
#include <cstring>
#include "token.hpp"
#include "stack.hpp"
#include "funcs.hpp"



void convertToPostFix(Token *inFix, Token *postFix, int insiz, int *psizp)
{
  stack s;
  int psiz;
  int i, done;
  Token *token;
  

  psiz = 0;

  for (i=0;i<insiz;i++) {

    switch(inFix[i].type) {
      
    case VALUE:
      postFix[psiz] . type = inFix[i].type;
      postFix[psiz++]. value.fval = inFix[i].value.fval;
      break;
      
    case LBRACE:
      s.Push(&inFix[i]);
      break;

    case RBRACE:

      token = s.Pop();

      while(token->type != LBRACE) {
	postFix[psiz] . type = token->type;
	strcpy_s(postFix[psiz++]. value.cval, token->value.cval);
	token = s.Pop();
      }

      break;

    case OPERATOR:
      done = 0;
      while (!s.isEmpty()  && !done) {

	token = s.Pop();
	
	if (token->type != LBRACE  && precedence(token->value.cval) >=
	    precedence(inFix[i].value.cval)) {

	  postFix[psiz] . type = token->type;
	  strcpy_s(postFix[psiz++]. value.cval, token->value.cval);
	}

	else 
	  {
	    s.Push(token);
	    done = 1;
	  }

      }
      s.Push(&inFix[i]);

      break;
    }
  }


  while (!s.isEmpty()) {
    token = s.Pop();
    postFix[psiz].type = token->type;
	strcpy_s(postFix[psiz++].value.cval, token->value.cval);
  }

  *psizp = psiz;
}
	  
      
      

  
  


void readExpression(FILE *fp, Token *expression, int *esizp)
{
  char ch;
  char expr[MAX_EXPRESSION_SIZE], op[100], *p;
  float f;
  int i;
  int esiz;

  ch = getc(fp);
  esiz = 0;
  while (!endOfLine(ch)) {

    if (isSpace(ch)){
    }
    else 

      if (isNumeral(ch)) {
	ungetc(ch, fp);
	fscanf_s(fp, "%f", &f);

	expression[esiz].type = VALUE;
	expression[esiz++].value.fval = f;


      } else

	if (isRightBrace(ch)) {
	  expression[esiz++].type = RBRACE;
	}

	else 
	  if (isLeftBrace(ch))
	    expression[esiz++].type = LBRACE;
	  else 
	    {
	      ungetc(ch, fp);
	      readOperator(fp, op);
	      expression[esiz].type = OPERATOR;
	      strcpy_s(expression[esiz++].value.cval, op);
	    }
    ch = getc(fp);
  }
  *esizp = esiz;
}

int isSpace(char ch)
{
  return (ch==' ');
}

int isLeftBrace(char ch)
{
  return (ch == '(');
}

int isRightBrace(char ch)
{
  return (ch == ')');
}

int isNumeral(char ch)
{
  return (ch >= '0' && ch <= '9');
}
  
void readOperator(FILE *fp, char *op)
{
  int i;
  int j = 0;
  char ch;

  j = 0;
  ch = getc(fp);
  while(!isRightBrace(ch) && !isLeftBrace(ch) && !isNumeral(ch)
	&& !endOfLine(ch)) {
    op[j++] = ch;

    op[j] = '\0';

    if (isValidOperator(op)) 
      break;

    ch = getc(fp);
  }
}

int isValidOperator(char *op)
{
  int i;

  for (i=0;i<NUM_OPS;i++) 
    if (!strcmp(op, OPS[i]))
      break;

  if (i<NUM_OPS)
    return 1;
  return 0;
}

int precedence(char *op)
{
  int i;

  if (!strcmp(op, "sqrt"))
    return 3;
  if (!strcmp(op, "*") || !strcmp(op, "/"))
    return 2;
  if (!strcmp(op, "+") || !strcmp(op, "-"))
    return 1;

  return -1;
}


    

int endOfLine(char ch)
{
  return (ch == '\n');
}


