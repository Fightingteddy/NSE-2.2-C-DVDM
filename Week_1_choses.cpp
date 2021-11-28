#include<stdio.h>
#include "hello.h"
int main()
{
    float num;
    printf("Kies uit: 1, 2 of 3: ");
    scanf("%f",&num);
    if(num == 1)
    {
        printf("Uw keuze is 1!\nNiet de juiste keus!");
    }
    else if(num == 2)
    {
        printf("Goede keuze, hier komt de 'hello world' functie: ");
        hello();
    }
    else if(num == 3)
    {
        printf("Uw keuze is 3\nNiet de juiste keus!");
    }
    else if(num <= 0)
    {
        exit(0);
    }
    else
    {
        printf("Kies een geldig nummer!");
    }
    return(0);
}

