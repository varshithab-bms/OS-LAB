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
    for(i = 0; i < frames; i++)
        frame_arr[i] = -1;

    for(i = 0; i < n; i++) {
        int flag = 0;
        for(j = 0; j < frames; j++) {
            if(frame_arr[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) { // Page fault
            faults++;
            int pos = -1;
            for(j = 0; j < frames; j++) {
                if(frame_arr[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1) { // Need to replace a page
                int farthest = i, replace_index = 0;
                for(j = 0; j < frames; j++) {
                    int found = 0;
                    for(k = i + 1; k < n; k++) {
                        if(frame_arr[j] == pages[k]) {
                            if(k > farthest) {
                                farthest = k;
                                replace_index = j;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        replace_index = j;
                        break;
                    }
                }
                pos = replace_index;
            }
            frame_arr[pos] = pages[i];
        }
        printf("Frames after accessing %d: ", pages[i]);
        for(j = 0; j < frames; j++) {
            if(frame_arr[j] == -1)
                printf("_ ");
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
