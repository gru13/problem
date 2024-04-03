#include "./company.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct line{
    char Emp_id[6];
    char Name[];
};


int main(){
    FILE* input = fopen("./EmployeeSampleData.txt","r");
    char Line_buffer[1001][MAX_LINE_SIZE];
    int i = 0,j = 0;
    char ch;
    do{
        ch = getc(input);
        if(ch == EOF){
            break;
        }
        if(ch = '\n'){
            Line_buffer[i][j] = '\0';
            i++;
            j = 0; 
        }else{
            Line_buffer[i][j] = ch;
            j++;
        }
        // putchar(Line_buffer[i][j]);
    }while (ch != EOF && i < 1001 && j < MAX_LINE_SIZE);
    printf("%s",Line_buffer[0]);

}