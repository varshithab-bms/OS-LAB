#include<stdio.h>

int main(){
    int frames , pages;
    printf("enter the number of pages:");
    scanf("%d",&pages);
    printf("ente the number of frames:");
    scanf("%d",&frames);
    int f[frames];
    int p[pages];

    printf("enter the reference string:");
    for(int i=0;i<pages;i++){
        scanf("%d",&p[i]);
        }
    for(int j=0;j<frames;j++){
        f[j] = -1;
        }
    int count = 0;
    int k;
    printf("page\tframes\t\t\t fault\n");
    for(int i=0;i<pages;i++){
        int avail = 0;
        for(int j=0;j<frames;j++){
            if(f[j]==p[i]){
                avail = 1;
                break;
                }
            }
        if(avail == 0){
            count++;
            f[k] = p[i];
            k = (k+1)%frames;
            printf("%d\t",p[i]);
            for(int j=0;j<frames;j++){
                if(f[j]!=-1){
                    printf("%d\t",f[j]);
                    }
                else{
                    printf("-\t");
                    }
                }
            printf("\tYes\n");
        }
        else{
            printf("%d\t",p[i]);
            for(int j=0;j<frames;j++){
                if(f[j]!=-1){
                    printf("%d\t",f[j]);
                    }
                else{
                    printf("-\t");
                    }
                }
            printf("\tNo\n");
            }
        }
        printf("Faults:%d\n",count);
        printf("hits:%d\n",pages-count);
        float hits = pages - count;
        float faults = (float)count;
        float ratio = (hits/count);
        printf("ratio:%.2f\n",ratio);
        return 0;
        }
