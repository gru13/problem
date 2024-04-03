#include "phoneNetwork.h"
void init_phoneNetwork(PhoneNetworkType* ph){
    ph->numCalls = 0;
    ph->numCustomers = 0; 
}

int registerCustomer(PhoneNetworkType *phn, char *name, char *phoneNumber, int minAllowed){
    if(phn->numCustomers < MAX_CUSTOMERS){
        phn->customers[phn->numCustomers].name=name;
        phn->customers[phn->numCustomers].number=phoneNumber;
        phn->customers[phn->numCustomers].numInCalls = 0;
        phn->customers[phn->numCustomers].numOutCalls = 0;
        phn->customers[phn->numCustomers].id = PhoneId + phn->numCustomers;
        phn->customers[phn->numCustomers].plan.minutesAllowed = minAllowed;
        phn->customers[phn->numCustomers].plan.minutesUsed = 0;
        phn->numCustomers++;
        return 1;
    }else{
        return 0;
    }
}

void displayCharges(PhoneNetworkType phn){
    printf(" %-6s %13s\t%-19s%-4s\n","ID","Phone Number","Name","Plan");
    printf("-----------------------------------------------\n");
    for(unsigned int i =0;i<phn.numCustomers;i++){
       if(phn.customers[i].plan.minutesAllowed == UNLIMITED){
            printf(" %-6d %13s\t%-19s%4s\n",phn.customers[i].id,phn.customers[i].number,phn.customers[i].name,"UN");    
       }else if(phn.customers[i].plan.minutesAllowed == PAY_PER_MINUTE){
            printf(" %-6d %13s\t%-19s%4s\n",phn.customers[i].id,phn.customers[i].number,phn.customers[i].name,"PPM");    
       }else{
            printf(" %-6d %13s\t%-19s%4d\n",phn.customers[i].id,phn.customers[i].number,phn.customers[i].name,phn.customers[i].plan.minutesAllowed);    
       }
    }
    printf("\n");
}


void resetMonth(PhoneNetworkType *phn){
    phn->numCalls = 0;
}

char recordCall(PhoneNetworkType *phn, char *made_from, char *made_to, time_t started, time_t ended){
    if(phn->numCalls >= MAX_CALLS){
        return 0;
    }
    int a_in = 0,b_in=0; // bool var to check if both number in the customer
    CustomerType *a,*b;
    for(int i =0 ;i < (int)phn->numCustomers;i++){
        if(phn->customers[i].number == made_from){
            a_in = 1;
            a = &phn->customers[i];
        }
        if(phn->customers[i].number == made_to){
            b_in = 1;
            b = &phn->customers[i];
        }
    }
    if(a_in == 0 && b_in == 0){
        return 0;
    }

    double time_used = difftime(ended, started); 
    a->numOutCalls++;
    b->numInCalls++;
    a->plan.minutesUsed += (int)time_used;
    if(b->plan.minutesAllowed == PAY_PER_MINUTE){
        b->plan.minutesUsed += (int)time_used;
    }
    phn->calls[phn->numCalls].startTime = started;
    phn->calls[phn->numCalls].endTime = ended;
    phn->calls[phn->numCalls].madeFrom = a;
    phn->calls[phn->numCalls].madeTo = b;
    phn->numCalls++;
    return 1;
}

void displayCallLog(PhoneNetworkType* phn){
    printf("\n");
    printf("Call From #     Call To #       Start Time:           End Time              Call Length\n");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < (int)phn->numCalls; i++){
        float h = difftime(phn->calls[i].endTime,phn->calls[i].startTime);
        h = (int)h/60 + (h - ((int)h/60)*60)/60.0;
        char s[100];
        strftime(s,sizeof(s),"%Y-%m-%d %H:%M:%S",localtime(&phn->calls[i].startTime));
        char e[100];
        strftime(e,sizeof(e),"%Y-%m-%d %H:%M:%S",localtime(&phn->calls[i].endTime));
        char d[13];
        sprintf(d,"%3.1f minutes",h);
        printf("%-15s %-15s %-20s %-20s %15s\n",phn->calls[i].madeFrom->number,phn->calls[i].madeTo->number,s,e,d);
    }
    printf("\n");
}
void displayCharges_Modified(PhoneNetworkType phn){
    printf("Phone Number     Name                Plan Out  In     Used     Over       Base      Extra        HST       Total\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for(unsigned int i =0;i<phn.numCustomers;i++){
        CustomerType t = phn.customers[i];
        int over;
        float base,extra,hst;
       if(t.plan.minutesAllowed == UNLIMITED){
            base = 34.99;
            hst = base*0.13;
            printf("%-15s  %-20s %3s %3d %3d %8d %8d %10.2f %10.2f %10.2f   $%8.2f\n",t.number,t.name,"UN",t.numOutCalls,t.numInCalls,t.plan.minutesUsed,0,base,0.0,hst,base+hst);
       }else if(t.plan.minutesAllowed == PAY_PER_MINUTE){
            over = t.plan.minutesUsed - 100;
            over = (over < 0)?0:over;
            base = 0.15*(t.plan.minutesUsed - over);
            extra = 0.35*over;
            hst = (base+extra)*0.13;
            printf("%-15s  %-20s %3s %3d %3d %8d %8d %10.2f %10.2f %10.2f   $%8.2f\n",t.number,t.name,"PPM",t.numOutCalls,t.numInCalls,t.plan.minutesUsed,over,base,extra,hst,(base+extra+hst));
       }else{
            over = t.plan.minutesUsed - t.plan.minutesAllowed;
            over = (over < 0)?0:over;
            base = 9.99;
            extra = over*0.15;
            hst = (base+extra)*0.13;
            printf("%-15s  %-20s %3d %3d %3d %8d %8d %10.2f %10.2f %10.2f   $%8.2f\n",t.number,t.name,t.plan.minutesAllowed,t.numOutCalls,t.numInCalls,t.plan.minutesUsed,over,base,extra,hst,(base+extra+hst));
       }
    }
}