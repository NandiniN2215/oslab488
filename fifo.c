#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k, pos = 0;
    int pageFaults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frames[pos] = pages[i];
            pos = (pos + 1) % f;
            pageFaults++;
        }

        printf("\nFrames: ");
        for(k = 0; k < f; k++)
            printf("%d ", frames[k]);
    }

    printf("\n\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
