#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 50

void generateThreeAddressCode(char *lhs,char *rhs){
    int opTop=-1,operTop=-1,tempCount=1;
    char temp[5],operSt[MAX][5],opSt[MAX],buffer[10];
    
    for(int i=0;rhs[i];i++){

        if(isspace(rhs[i])){
            continue;
        }
        
        if(isalnum(rhs[i])){

            int j=0;
            while(isalnum(rhs[i])||rhs[i] =='_'){
                buffer[j++]=rhs[i++];
            }
            buffer[j]='\0';
            strcpy(operSt[++operTop],buffer);
            i--;
        }
        else if(rhs[i]=='('){
            opSt[++opTop]=rhs[i];
        }
        else if(rhs[i]==')'){
            while(opSt[opTop]!='(' && opTop >=0){
                sprintf(temp,"t%d",tempCount++);
                printf("%s=%s %c %s \n",temp,operSt[operTop-1],opSt[opTop--],operSt[operTop]);
                strcpy(operSt[--operTop],temp);
            }
            opTop--;
        }
        else{
            while(opTop >=0 && strchr("*/",opSt[opTop]) ){
                sprintf(temp,"t%d",tempCount++);
                printf("%s=%s %c %s \n",temp,operSt[operTop-1],opSt[opTop--],operSt[operTop]);
                strcpy(operSt[--operTop],temp);
            }
            opSt[++opTop]=rhs[i];
        }
    }

    while(opTop >=0){
        sprintf(temp,"t%d",tempCount++);
        printf("%s=%s %c %s \n",temp,operSt[operTop-1],opSt[opTop--],operSt[operTop]);
        strcpy(operSt[--operTop],temp);
    }

    printf("%s = %s \n",lhs,operSt[operTop]);

}

int main(){
    printf("Enter the Expression:\n"); //Format Eg: a = a + b*c

    char expr[MAX];
    char lhs[5],rhs[MAX];

    fgets(expr,sizeof(expr),stdin);

    sscanf(expr,"%4[^=]=%[^\n]",lhs,rhs);

    printf("The Expression : %s \n Intermediate code (3-Address Code): \n",expr);
    generateThreeAddressCode(lhs,rhs);
    return 0;
}