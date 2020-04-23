#include <stdio.h>
#include <stdlib.h>

void main(){
    printf("Hello world!\n");
    int x=0;
    for (int i=0;i<20;i++){
        x=x+i;
    }
    printf("O resultado final de x: %d\n",x);
}
