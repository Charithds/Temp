#include "stdafx.h"
#include <cstdio>
#include <cstring>
#include <math.h>
#include <stack>
#include "token.hpp"
#include "stack.hpp"
#include "funcs.hpp"

// added by charith
// -------------------------------------------------------------------------------------
float calculate(Token *postFix, int &psiz)
{
	std::stack<float> operandStack;
	int i;

	// push operands into the stack
	// if an operator is found pop out the last two operands and do the calculation

	for (i = 0; i<psiz; i++) {

		switch (postFix[i].type) {
			case OPERATOR:
			{
				// if its an operator pop the last two elements. do the op. push it back
				float operand_1, operand_2;
				
				if (operandStack.empty()) {
					throw "Empty expression!";
				}
				
				operand_1 = operandStack.top();
				operandStack.pop();
				
				float result = 0;
				char currentOperator[OP_SIZE];
				strcpy_s(currentOperator, postFix[i].value.cval);
				
				if (!strcmp(currentOperator, "sqrt"))
				{
					result = sqrtf(operand_1);
				}
				else
				{
					if (operandStack.empty())
					{
						throw "Not enough operands!";
					}
					
					operand_2 = operandStack.top();
					operandStack.pop();
					
					// operator is "+"
					if (!strcmp(currentOperator, "+"))
					{
						result = operand_2 + operand_1;
					}
					else if (!strcmp(currentOperator, "-"))
					{
						result = operand_2 - operand_1;
					}
					else if (!strcmp(currentOperator, "*"))
					{
						result = operand_2 * operand_1;
					}
					else if (!strcmp(currentOperator, "/"))
					{
						result = operand_2 / operand_1;
					}
				}

				operandStack.push(result);
				break;
			}
			case VALUE:
				// if its a value push it
				operandStack.push(postFix[i].value.fval);
				break;
		}
	}
	if (operandStack.size() > 1)
	{
		throw "Not enough operators!";
	}
	if (operandStack.empty()) {
		throw "Empty expression!";
	}
	return operandStack.top();
}
// -------------------------------------------------------------------------------------

int main()
{
  int i, j;
  int count;
  FILE *fp;
  Token inFix[MAX_EXPRESSION_SIZE], postFix[MAX_EXPRESSION_SIZE];
  int esiz, psiz;

  printf("Input expression\n");
  
  fp = stdin;
  readExpression(fp, inFix, &esiz);

  convertToPostFix(inFix, postFix, esiz, &psiz);
   
  try
  {
	  float finalValue = calculate(postFix, psiz);
	  printf("value: %1.1f", finalValue);
  }
  catch (const char* msg)
  {
	  printf(msg);
  }
  
  char endString[256];
  gets_s(endString);
  return 0;
}
