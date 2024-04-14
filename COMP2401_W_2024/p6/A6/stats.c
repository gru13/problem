#include "./company.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<locale.h>

void swap(int* xp, int* yp) { 
    if (xp == yp) // Check if the two addresses are same 
        return; 
    *xp = *xp + *yp; 
    *yp = *xp - *yp; 
    *xp = *xp - *yp; 
} 

int main(){
    FILE* input = fopen("./EmployeeDataReduced.bin","rb");
    setlocale(    LC_NUMERIC, "");
    if (input == NULL){
        printf("ERROR WHILE OPENING SRC FILE");
    }
    unsigned short len = 0;
    fread(&len,sizeof(len),1,input);
    struct RowData datas[len];
    fread(datas,sizeof(struct RowData),len,input);
    
    int minindex = -1,maxindex = -1,max_=datas[0].salary,min_=datas[0].salary,avg=0;
    int curEmp =0;
    for (int i = 0; i < len; i++){
        if(min_ > datas[i].salary){
            min_ = datas[i].salary;
            minindex = i; 
        }
        if(max_ < datas[i].salary){
            max_ = datas[i].salary;
            maxindex = i;
        }
        if (datas[i].extYr == (short int)0){
            avg += datas[i].salary;
            curEmp += 1;
        }
        
    }
    printf("Lowest Salary Employee\n");
    printf("  $%'d for %s (%s - %s,%s)\n",datas[minindex].salary, datas[minindex].Name,JobTitles[datas[minindex].job],Cities[datas[minindex].cty],Countries[datas[minindex].cnt]);
    printf("\nHighest Salary Employee\n");
    printf("  $%'d for %s (%s - %s,%s)\n",datas[maxindex].salary, datas[maxindex].Name,JobTitles[datas[maxindex].job],Cities[datas[maxindex].cty],Countries[datas[maxindex].cnt]);
    
    printf("\nAverage Salary of Current Employees = $%'d\n",avg/curEmp);
    
    printf("\n\nSystem Administrators From Seattle:\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < len; i++){
        if(datas[i].cty == SEATTLE && strcmp(JobTitles[datas[i].job],"System Administrator") == 0){
            printf("#E%05d - %s\n",datas[i].EmpID,datas[i].Name);
        }
    }

    printf("\n\nEmployees Hired in October of 2022:\n");
    printf("-----------------------------------\n");
    int OCT[len];
    int OCT_l = 0;
    for(int i =0;i<len;i++){
        if(datas[i].year == 2022 && datas[i].mnt == 10){
            OCT[OCT_l++] = i;
        }
    }
    // sorting
    for(int i =0;i<OCT_l;i++){
        for(int j = 0;j<OCT_l-i-1;j++){
            if(datas[OCT[j]].day > datas[OCT[j+1]].day){
                swap(&OCT[j],&OCT[j+1]);
        
            }
        }
    }
    for(int i =0 ;i<OCT_l;i++){
        printf("#E%05d - %-30s(2022-10-%02d)\n",
        datas[OCT[i]].EmpID,datas[OCT[i]].Name,datas[OCT[i]].day);
    }

    printf("\n\nIT Employees in China working in Research & Development:\n");
    int CRD_len = 0;
    int CRD[len];
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < len; i++){
    if(strcmp(Countries[datas[i].cnt],"China") == 0 && Departments[datas[i].dep] == "IT" && BusinessUnits[datas[i].Bsunit] == "Research & Development"){
            CRD[CRD_len] = i;
            CRD_len+=1; 
        }
    }
    // sort
    for(int i = 0; i < CRD_len-1; i++){
        for (int j = 0; j < CRD_len-i-1; j++)        {
            if(strcmp(datas[CRD[j]].Name,datas[CRD[j+1]].Name) > 0){
                int temp = CRD[j];
                CRD[j] = CRD[j+1];
                CRD[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < CRD_len; i++){
        printf("#E%05d - %s\n",datas[CRD[i]].EmpID,datas[CRD[i]].Name);
    }
    int totOlds = 0;
    printf("\n\nEmployees 65 or older:\n");
    printf("---------------------\n");
    for (int i = 0; i < len; i++){
        if(datas[i].age >= 65){
            printf("#E%05d - %-30s $%'6d\n",datas[i].EmpID,datas[i].Name,datas[i].salary);
            totOlds += datas[i].salary;
        }
    }
    printf("\n$%'d will be saved annually if those 65 or older exit the company\n",totOlds);
    fclose(input);

}
