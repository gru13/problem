#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<math.h>
#include<limits.h>

int randomInt(int max){
  return(rand() % max);
}

int randomCordinator(){
    float cor = (float)(randomInt(60000) - 30000);
    cor /= 1000;
    return cor;
}

int min(float* arr, int len){
    float minVal = INT_MAX;
    int index = -1;
    for (int i = 0; i < len; i++){
        if(arr[i] < minVal){
            minVal = arr[i];
            index = i;
        }
    }
    return index;
    
}

int main(){
    // init the random seed
    srand(time(NULL));
    
    int nof_Driver,nof_Package;
    
    // getting input for no of driver with validation
    scanf("%d", &nof_Driver);
    if(nof_Driver<2 || nof_Driver > 200){
        return 1;
    }
    
    
    // getting input for no of Packages with validation
    scanf("%d", &nof_Package);
    if(nof_Package<10 || nof_Package > 50000){
        return 1;
    }

    float Dx[nof_Driver], Dy[nof_Driver];// parallel array save the cordinate of the driver
    float Px[nof_Package], Py[nof_Package];// parallel array save the cordinate of package
    int Result[nof_Package];
    float Distance[nof_Driver];
    float x,y;

    // creating cordinate for drivers
    for(int i =0;i<nof_Driver;i++){
        do{
            x = randomCordinator();
            y = randomCordinator();
        }while(x*x + y*y >= 30.0*30.0);
        Dx[i] = x;
        Dy[i] = y;
    }

    //  creating cordinate for Package
    for(int i =0 ;i<nof_Package;i++){
        do{
            x = randomCordinator();
            y = randomCordinator();
        }while(x*x + y*y >= 30.0*30.0);
        Px[i] = x;
        Py[i] = y;
    }

    for(int i = 0;i<nof_Package;i++){
        for (int j = 0; j < nof_Driver; j++){
            Distance[j] = sqrt(pow((Px[i]-Dx[j]),2)+pow((Py[i]-Dy[j]),2));
        }
        Result[i] = min(Distance, nof_Driver);

    }

    // results
    printf("%d %d\n",nof_Driver,nof_Package);
    for (int i = 0; i < nof_Package; i++){
        printf("%.2f %.2f %d ",Px[i],Py[i],Result[i]);
    }
    

}