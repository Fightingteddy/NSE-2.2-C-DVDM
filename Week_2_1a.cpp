#include <stdio.h>

int maxArrays(float *xptr, float *yptr, float *zptr);
int num;
int ctr;

int main()
{
    float x[4];
    float y[4];
    float z[4];
    
    float *xptr;
    float *yptr;
    float *zptr;

    xptr = &x[0];
    yptr = &y[0];
    zptr = &z[0];

    x[0] = 0.7; x[1] = 3.3; x[2] = 0.5; x[3] = 10.3;
    y[0] = 4.1; y[1] = 1.5; y[2] = 0.5; y[3] = 2.3;
    printf("Array 1 and 2:\n");

    for (num = 0; num < 4; num++)
    {
        printf("%g %g\n", x[num], y[num]);
    }
    printf("\nArray 3:\n");
    maxArrays(xptr, yptr, zptr);
    
    for (num = 0; num < 4; num++)
    {
        printf("%g\n", z[num]);
    }
    
    return 0;
}

int maxArrays(float *xptr, float *yptr, float *zptr)
{
    for (ctr = 0; ctr < 4; ctr++)
    {
        if (xptr[ctr] > yptr[ctr])
        {
            zptr[ctr] = xptr[ctr];
        }
        else
        {
            zptr[ctr] = yptr[ctr];
        }
    }
}