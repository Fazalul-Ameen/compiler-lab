%{
    #include<stdio.h>
    int vow=0, con=0;
%}
%%
[AEIOUaeiou]    { vow++; }
[a-zA-Z]    { con++; }
. | \n  ;
%%

int main(){
    printf("Enter the string : ");
    yylex();
    printf("No. of vowels : %d\n", vow);
    printf("No. of consonants : %d\n", con);
    return 0;
}

int yywrap(){
    return 1;
}