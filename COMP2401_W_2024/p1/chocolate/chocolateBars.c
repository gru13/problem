#include<stdio.h>
#include<string.h>
#include<stdlib.h>

                        

int main(){
    // init the variable
    // parallel array concept is used to store the details in order
    float prices[] = {0.87, 0.88, 0.50, 1.29, 0.98};
    int quantity[] = {24, 36, 48, 24, 36};
    char* chocolate[] = {"Oh Henry", "Coffee Crisp", "Aero", "Smarties", "Crunchie"};
    int Ordered[5];
    float Total = 0,Hst=0.13;
    // showing the menu
    for(int i = 0;i < 5;i++){
        printf("%d. %-15s %0.2f each\n",i+1, chocolate[i], prices[i]);
    }
    // getting order 
    printf("\n");
    for(int i = 0; i < 5;i++){
        printf("How many boxes of %s bars would you like (%d per box)? ", chocolate[i], quantity[i]);
        scanf("%d",&Ordered[i]);
    }
    printf("\n");
    //printing the values
    for (int i = 0; i < 5; i++){
        printf("%3d boxes of %-12s (%2d x $%0.2f per box) = $ %9.2f \n", Ordered[i],chocolate[i], quantity[i], prices[i],Ordered[i]*quantity[i]*prices[i]);
        Total += Ordered[i]*quantity[i]*prices[i];
    }
    Hst *= Total;
    printf("------------------------------------------------------------\n");
    printf("%-47s= $ %9.2f\n","Sub Total",Total);
    printf("%-47s= $ %9.2f\n","HST",Hst);
    printf("============================================================\n");
    printf("%-47s= $ %9.2f\n","Amount Due",Total+Hst);
    
    return 0;
}