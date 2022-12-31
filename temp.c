#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    srand(time(0));
    int a = RAND_MAX/2;
    int b = rand();
    printf("%d %d",a,b);
    printf(" %d",b<a);
    return 0;
}