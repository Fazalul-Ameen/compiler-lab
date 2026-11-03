%{
    #include<stdio.h>
%}

%%
"abc"   { printf("ABC"); }
.   { printf("%s",yytext); }
%%

int main(){
    printf("Enter the string : ");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}