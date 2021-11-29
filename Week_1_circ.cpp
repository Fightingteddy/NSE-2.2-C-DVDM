#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

void circ(float *dia);

int main()
{
    float dia;
    float *num;
    printf("Geef de diameter van de cirkel: ");
    scanf("%f", &dia);
    num = &dia;
    circ(num);
    printf("%f\n", dia);
    return 0;
}

void circ(float *dia)
{
    *dia = *dia * M_PI;
}