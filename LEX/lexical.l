%{
#include<stdio.h>
#include<ctype.h>
%}

%%
"int"|"float"|"char"|"double"|"if"|"else"|"return"  { printf("%s : Keyword\n",yytext); }
[_a-zA-Z]+[0-9]*[a-zA-Z]*   { printf("%s : Identifier",yytext); }
"+"|"-"|"*"|"/"|"<"|">"|"<="|">="|"=="|"!=" { printf("%s : Operator\n",yytext); }
[0-9]+  { printf("%s : Constant\n",yytext); }
[ \t\n]+ {/*ignore whitespaces and tabs*/}
.   { printf("%s : symbols\n",yytext); }
%%

int main(){
yyin = fopen("input.c","r");
yylex();
return 0;
}

int yywrap(){
return 1;
}