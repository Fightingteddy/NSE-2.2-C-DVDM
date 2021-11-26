#include<stdio.h>
 
int main() {
 
   int radius;
   float PI = 3.141592654;
   float dia = 0;

   printf("\nRadius van de cirkel: ");
   scanf("%d", &radius);
 
   dia = 2 * PI * radius;
   printf("\nDiameter is : %f ", dia);
 
   return (0);
}