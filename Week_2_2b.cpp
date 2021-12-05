#include <stdio.h>
#include <stdlib.h>


int main()
{

    struct name_age
    {
        char naam[20];
        int leeftijd;
    };

    struct name_age *pointer = (struct name_age*)malloc(sizeof(struct name_age));
    int check = 1;
    int counter = 1;
    struct name_age *newpointer;

    while (1)
    {
        newpointer = pointer;
        newpointer += (counter-1);

        printf("Name: ");
        scanf("%s", newpointer->naam);

        
        printf("Age: ");
        scanf("%d", &newpointer->leeftijd);


        printf("Type 1 if you want to add a element: ");
        scanf("%d", &check);
        if (check != 1)
        {
            break;
        }
        printf("\n");

        struct name_age *pp = pointer;
        for (int i = 0; i < counter; i++)
        {
            printf("%s\n", pp->naam);
            printf("%d\n", pp->leeftijd);
            pp++;
        }

        counter++;

        pointer = (struct name_age*)realloc(pointer, counter * sizeof(struct name_age));
        if (pointer == NULL)
        {
            perror("error");
            exit(-1);
        }
    }





    free(pointer);
    return 0;

}