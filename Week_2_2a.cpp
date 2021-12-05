#include <stdio.h>
char tk(FILE *fille);


int main()
{
    FILE *fille;
    fille = fopen("text.txt","r");
    if (fille == NULL)
    {
        printf("Could not open file.");
        return 0;
    }
    tk(fille);

    fclose(fille);
    return 0;
}

char tk(FILE *fille)
{
    char check;
    int counter = 0;
    FILE *neww;
    neww = fopen("new.txt", "w");

    while ((check = fgetc(fille)) != EOF)
    {
        counter++;

        check = check + 1;
        fputc(check, neww);

    }
    fclose(neww);
    printf("There are %d characters in this file." , counter);

}