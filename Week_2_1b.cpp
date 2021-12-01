#include <stdio.h>  
#include <string.h>  
   
int main()  
{  
    char str[100];
    int i,chars;
    chars= 0;
    printf("Voer een string is: \n");
    scanf("%d" ,&str);  
    gets(str);
      
    i=0;
    while(str[i] != '\0'){
        {
            chars++;
        }
         i++;
    }
    printf("Aantal karakters in de sting is:  %d",chars);

    return 0;
} 
