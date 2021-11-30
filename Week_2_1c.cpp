#include<stdio.h>
#include<string.h>


struct opleiding
{
    char naam[30];
    int instroomjaar;
    int name;
    int leeftijd;
};

int main()
{
    struct opleiding arr_opleiding[1];
    int i;


    for(i = 0; i < 1; i++ )
    {
        printf("\nGeeft jouw info: \n", i+1);

        printf("Naam: ");
        scanf("%s", &arr_opleiding[i].name);

        printf("Leeftijd: ");
        scanf("%f", &arr_opleiding[i].leeftijd);
        
        printf("Naam opleiding: ");
        scanf("%s", &arr_opleiding[i].naam);

        printf("Instroomjaar: ");
        scanf("%d", &arr_opleiding[i].instroomjaar);


    }

    printf("\n");

    printf("Naam student\tLeeftijd\tNaam opleiding\tInstroomjaar\n");

    for(i = 0; i < 1; i++ )
    {
        printf("%s\t\t%d\t\t%s\t\t%d\n",
        &arr_opleiding[i].name, &arr_opleiding[i].leeftijd, arr_opleiding[i].naam, arr_opleiding[i].instroomjaar);
    }
    return 0;
}