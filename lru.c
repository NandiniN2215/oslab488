#include <stdio.h>

int main() {
    int pages[50], frames[10], time[10];
    int n, f, i, j, k;
    int pageFaults = 0, count = 0;
    int found, least, pos;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if(!found) {
            least = time[0];
            pos = 0;

            for(j = 1; j < f; j++) {
                if(time[j] < least) {
                    least = time[j];
                    pos = j;
                }
            }

            count++;
            frames[pos] = pages[i];
            time[pos] = count;
            pageFaults++;
        }

        printf("\nFrames: ");
        for(k = 0; k < f; k++)
            printf("%d ", frames[k]);
    }

    printf("\n\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
