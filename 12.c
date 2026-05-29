#include <stdio.h>

int main()
{
    int blockSize[10], processSize[10];
    int allocation[10];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of memory blocks:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int worstIndex = -1;

        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worstIndex == -1 || blockSize[j] > blockSize[worstIndex])
                    worstIndex = j;
            }
        }

        if(worstIndex != -1)
        {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    printf("\nWORST FIT Allocation\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
