#include <stdio.h>

int main() {
    int frames, pages[50], n, frame[10], i, j, k, avail, count = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nPage\tFrames\t\tPage Fault\n");

    j = 0;
    for(i = 0; i < n; i++) {
        avail = 0;

        for(k = 0; k < frames; k++) {
            if(frame[k] == pages[i]) {
                avail = 1;
                break;
            }
        }

        if(avail == 0) {
            frame[j] = pages[i];
            j = (j + 1) % frames;
            count++;

            printf("%d\t", pages[i]);
            for(k = 0; k < frames; k++) {
                if(frame[k] != -1)
                    printf("%d ", frame[k]);
                else
                    printf("- ");
            }
            printf("\tYes\n");
        } else {
            printf("%d\t", pages[i]);
            for(k = 0; k < frames; k++) {
                if(frame[k] != -1)
                    printf("%d ", frame[k]);
                else
                    printf("- ");
            }
            printf("\tNo\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", count);
    return 0;
}
