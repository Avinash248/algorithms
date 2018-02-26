#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int i, ans, n, d, j, k, size=200;
    int *A, *count = (int*)calloc(201, sizeof(int));
    double median;

    scanf("%d%d", &n, &d);

    A = (int*)malloc(n*sizeof(int));

    for(i=0; i<n; i++)
        scanf("%d", &A[i]);

    for(i=0; i<d; i++)
        ++count[A[i]];

    for(i=1; i<size; i++)
        count[i] += count[i-1];

    i = d;
    ans = 0;

    while(i < n)
    {
        for(j=0; j<size; j++)
        {
            if(count[j] >= d/2)
                break;
        }

        if(count[j] == d/2)
        {
            median = j+1;

            if(d%2 == 0)
            {
                median += j;
                median /= 2.0;
            }
        }
        else
        {
            median = j;

            if(d%2 == 0)
            {
                if(count[j-1] + 1 == count[j])
                {
                    median += j-1;
                }
                else
                {
                    median += j;
                }

                median /= 2;
            }

        }

        if(A[i] >= 2*median)
            ans++;

        for(j=A[i-d]; j<size; j++)
            --count[j];

        for(j=A[i]; j<size; j++)
            ++count[j];

        i++;

    }

    printf("%d\n", ans);
}
