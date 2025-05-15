#include <stdio.h>

int main() {
    int n, frames, i, j, k, faults = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame_arr[frames];
    int time[frames]; // To track the usage time
    for(i = 0; i < frames; i++) {
        frame_arr[i] = -1;
        time[i] = 0;
    }

    int counter = 0;
    for(i = 0; i < n; i++) {
        int flag = 0;
        for(j = 0; j < frames; j++) {
            if(frame_arr[j] == pages[i]) {
                flag = 1;
                counter++;
                time[j] = counter; // Update the usage time
                break;
            }
        }

        if(flag == 0) { // Page fault
            faults++;
            int min_time = time[0], min_pos = 0;
            for(k = 1; k < frames; k++) {
                if(time[k] < min_time) {
                    min_time = time[k];
                    min_pos = k;
                }
            }
            frame_arr[min_pos] = pages[i]; // Replace the least recently used
            counter++;
            time[min_pos] = counter; // Update the usage time for the new page
        }

        printf("Frames after accessing %d: ", pages[i]);
        for(j = 0; j < frames; j++) {
            if(frame_arr[j] == -1)
                printf("- ");
            else
                printf("%d ", frame_arr[j]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", faults);
    int Hits = n-faults;
    printf("Total page Hits: %d\n",Hits);
    return 0;
}
