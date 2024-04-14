#include "./company.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>





int main(){
    FILE* input = fopen("./EmployeeSampleData.txt","r");
    if (input == NULL){
        printf("ERROR WHILE OPENING SRC FILE");
    }

    FILE* out = fopen("./EmployeeDataReduced.bin","wb");
    if (out == NULL){
        printf("ERROR WHILE OPENING DST FILE");
    }

    int i = 0,j = 0;
    unsigned short nofline = 0;
    char ch;
    do{
        if((ch = getc(input)) == '\n'){nofline++;}
    }while (ch != EOF);

    fseek(input,0,SEEK_SET);
    char Line_buffer[nofline][MAX_LINE_SIZE];
    do{
        ch = getc(input);
        if(ch == EOF){break;}
        if(ch == '\n'){
            Line_buffer[i][j] = '\0';
            i++;
            j = 0;
        }else{
            Line_buffer[i][j] = ch;
            j++;
        }
    }while (ch != EOF && i < nofline && j < MAX_LINE_SIZE);

    nofline--;
    fwrite(&nofline,sizeof(nofline),1,out);
    nofline++;
    struct RowData datas[nofline-1];

    for(i = 1;i<nofline;i++){
        int a=0,b=0;
        char WB[14][MAX_LINE_SIZE];
        WB[13][0] = '\0';
        // build Word buffer of every line;
        for(j = 0;j<strlen(Line_buffer[i]);j++){
            if(Line_buffer[i][j] == '\"' || Line_buffer[i][j] == '$' ||  Line_buffer[i][j] == ','|| Line_buffer[i][j] == '%' ||(Line_buffer[i][j] == 'E' && Line_buffer[i][j+1] - '0' <= 9)){
                continue;
            }
            if(Line_buffer[i][j] == '\t'){
                WB[a][b] = '\0';
                a++;
                b = 0;
            }else{
                WB[a][b] = Line_buffer[i][j];
                b++;
            }
        }
        // continue to put data into the struct
        // EmpID
        // int empid = 
        sscanf(WB[0],"%d",&datas[i-1].EmpID);
        // FULL Name
        datas[i-1].NSz = strlen(WB[1]);
        strcpy(datas[i-1].Name,WB[1]);
        // Jobtitle
        // taking care of spl case "System Administrator"
        char temp[50];
        strcpy(temp,WB[2]);
        temp[strlen(temp)-1] = '\0';
        if(strcmp(temp,"System Administrator") == 0){
            strcpy(WB[2],temp); 
        }
        for(int jo = 0; jo < NUM_JOB_TITLES ; jo++){
            if(strcmp(WB[2],JobTitles[jo]) == 0){
                datas[i-1].job = jo;
            }            
        }
        //DEparment
        for(int jo = 0; jo < NUM_DEPARTMENTS; jo++){
            if(strcmp(WB[3],Departments[jo]) == 0){
                datas[i-1].dep = jo;
            }            
        }
        //Business 
        for(int jo = 0; jo < NUM_UNITS; jo++){
            if(strcmp(WB[4],BusinessUnits[jo]) == 0){
                datas[i-1].Bsunit = jo;
            }            
        }
        //age
        datas[i-1].age = atoi(WB[7]);
        //
        int year,mnt,day;
        sscanf(WB[8],"%d/%d/%d",&mnt,&day,&year); 
        //year
        datas[i-1].year = (short int)year;
        //month
        datas[i-1].mnt = (unsigned char)mnt;
        //day
        datas[i-1].day = (unsigned char)day;
        //salary
        datas[i-1].salary = atoi(WB[9]);
        //country
        for(int jo = 0; jo < NUM_COUNTRIES; jo++){
            if(strcmp(WB[11],Countries[jo]) == 0){
                datas[i-1].cnt = jo;
            }            
        }
        //city
        for(int jo = 0; jo < NUM_CITIES; jo++){
            if(strcmp(WB[12],Cities[jo]) == 0){
                datas[i-1].cty = jo;
            }            
        }
        // exit day
        if(strlen(WB[13]) == 0){
            datas[i-1].extYr = 0;
            datas[i-1].extDa = 0;
            datas[i-1].extMn = 0;
        }else{
            sscanf(WB[13],"%d/%d/%d",&mnt,&day,&year); 
            datas[i-1].extYr = year;
            datas[i-1].extDa = mnt;
            datas[i-1].extMn = day;
        }
    }
    fwrite(datas,sizeof(struct RowData),nofline-1,out);
    fclose(input);
    fclose(out);
}


    // for (int i = 0; i < 10; i++){
    //     printf("%d - %s - %s - %s - %s - %d - %d/%d/%d - %d - %s - %s - %d\n",
    //     datas[i].EmpID,datas[i].Name,JobTitles[datas[i].job],
    //     Departments[datas[i].dep],BusinessUnits[datas[i].Bsunit],
    //     datas[i].age,datas[i].mnt,datas[i].day,datas[i].year,datas[i].salary,
    //     Countries[datas[i].cnt],Cities[datas[i].cty],datas[i].extYr);
    // }