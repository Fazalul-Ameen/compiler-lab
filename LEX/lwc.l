%{
    #include<stdio.h>
    int line=0, words = 0, character = 0;
%}
%%
[ \t]   {words++;}
[ \t\n]+ {words++; line++;}
[a-zA-Z] {character++;}
%%

int main(){
    printf("Enter the string : ");
    yylex();

    printf("Lines : %d\nWords : %d\nCharacters : %d\n",line, words, character);
    return 0;
}

int yywrap(){
    return 1;
}