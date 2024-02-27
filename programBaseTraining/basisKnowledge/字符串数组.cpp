#include<stdio.h>
#include<string.h>
#include<iostream> 
#include<stdlib.h>
int main()
{
    const char *c="dd";
    const char *num="a";
    char *A[2]={"asdf","asff"};
    char *b=(char*)malloc(sizeof(char)*30);
    char *d=(char*)malloc(sizeof(char)*30);   
    strcpy(b,num);
	strcat(b,c);
	printf("%s",b);
	strcpy(d,num);
	strcat(d,c);
	printf("%s",d);
	
}
//const char* proteinTransToRNA_kernel =
//"__kernel                                   \n"
//"void proteinTransToRNA_kernel(       \n"
//"                  __global int *repeat,       \n"
//"                  __global int *roll,       \n"
//"                  __global char **A,       \n"
//"                  __global char **R,       \n"
//"                  __global char **I,        \n"
//"                  __global char **T,        \n"
//"                  __global char **P,        \n"
//"                  __global char **H,        \n"
//"                  __global char **L,        \n"
//"                  __global char **Q,        
//"                  __global char **result);       
//"{                                         
//"    //Get the index of the work-item       
//"    int index = get_global_id(0);          
//"    char* num ="";          
//"    strcpy(result[index],num);        
//"    strcat(result[index],*R[(index%roll[0])/repeat[0]]); 
//"    strcat(result[index],*I[(index%roll[1])/repeat[1]]); 
//"    strcat(result[index],*T[(index%roll[2])/repeat[2]]); 
//"    strcat(result[index],*P[(index%roll[3])/repeat[3]]); 
//"    strcat(result[index],*R[(index%roll[4])/repeat[4]]); 
//"    strcat(result[index],*H[(index%roll[5])/repeat[5]]); 
//"    strcat(result[index],*L[(index%roll[6])/repeat[6]]); 
//"    strcat(result[index],*Q[(index%roll[7])/repeat[7]]); 
//"    strcat(result[index],*L[(index%roll[8])/repeat[8]]); 
//"    strcat(result[index],*A[(index%roll[9])/repeat[9]]); 
//"}                                          \n";
