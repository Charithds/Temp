int isNumeral(char ch);
int isRightBrace(char ch);
int isLeftBrace(char ch);
int isSpace(char ch);
int endOfLine(char ch);
void readExpression(FILE *fp, Token *expression, int *esizp);
void convertToPostFix(Token *inFix, Token *postFix, int insiz, int *psizp);
void readOperator(FILE *fp, char *op);
int isValidOperator(char *op);
int precedence(char *op);





