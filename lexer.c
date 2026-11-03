#include<stdio.h>
#include<ctype.h>
#include<string.h>

char keywords[10][10] = {"int","float","if","else","return"};

int iskeyword(char token[]){
    for(int j = 0; j < 10; j++){
        if(strcmp(token, keywords[j]) == 0){
            return 1;
        }
        return 0;
    }
}

int main(){
    char token[10], ch;
    int i;
    FILE *fp = fopen("input.c","r");

    while((ch = fgetc(fp)) != EOF){
        if(isspace(ch)){
            continue;
        }

        if(isalnum(ch) || ch == '_'){
            i = 0;
            token[i++] = ch;
            while((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == "_")){
                token[i++] = ch;
            }
            token[i] = '\0';
            if(iskeyword(token)){
                printf("%s : Keyword\n", token);
            }else{
                printf("%s : Identifier\n", token);
            }
        }else if(isdigit(ch)){
            i = 0;
            token[i++] = ch;
            while((ch = fgetc(fp)) != EOF && isdigit(ch)){
                token[i++] = ch;
            }
            token[i] = '\0';
            if(ch != EOF){
                ungetc(ch, fp);
            }
            printf("%s : Constant\n",token);
        }else if(strchr("+-*/%<>=!^&|", ch)){
            printf("%c : Operator\n",ch);
        }else if(strchr(";:{}[]()#.", ch)){
            printf("%c : Special symbol\n",ch);
        }else{
            printf("%c : Unknown symbol\n",ch);
        }
    }
}