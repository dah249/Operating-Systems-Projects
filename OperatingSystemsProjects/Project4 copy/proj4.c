#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define MAX_REF_STR_LEN 20
#define MAX_PAGE 5

int findLRU(int time[], int n){
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i){
        if(time[i] < minimum){
            minimum = time[i];
            pos = i;
        }
    }    
    return pos;
}

int predict(int reference[], int pg, int frame[], int nf, int pos){
    int i, j, flag = 0, farthest = pos, idx;
    for(i=0; i<nf; i++){
        for(j=pos; j<pg; j++){
            if(frame[i] == reference[j]){
                if(j>farthest){
                    farthest = j;
                    idx = i;
                    flag = 1;
                }
                break;
            }
        }
        if(j == pg)
            return i;
    }
    if(flag)
        return idx;
    return 0;
}

void print_frames(int frames[], int n_frames){
    for(int i = 0; i < n_frames; i++){
        if(frames[i] == -1){
            printf("-- ");
        } else {
            printf("%2d ", frames[i]);
        }
    }
    printf("\n");
}

void page_replacement(int reference[], int frames[], int n_frames, int n_references, char * algorithm){
    int i, j, flag1, flag2, counter = 0, faults = 0, hits = 0, time[n_frames];
    for(i = 0; i < n_frames; ++i){
        frames[i] = -1;
    }
    for(i = 0; i < n_references; ++i){
        flag1 = flag2 = 0;
        for(j = 0; j < n_frames; ++j){
            if(frames[j] == reference[i]){
                   counter++;
                   time[j] = counter;
                   flag1 = flag2 = 1;
                   hits++;
                   break;
               }
        }
        if(flag1 == 0){
            for(j = 0; j < n_frames; ++j){
                if(frames[j] == -1){
                    counter++;
                    faults++;
                    frames[j] = reference[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }    
        }
        if(flag2 == 0){
            int pos;
            if(strcmp(algorithm, "Optimal") == 0){
                pos = predict(reference, n_references, frames, n_frames, i+1);
            } else if(strcmp(algorithm, "LRU") == 0){
                pos = findLRU(time, n_frames);
            }
            counter++;
            faults++;
            frames[pos] = reference[i];
            time[pos] = counter;
        }
        printf("\nFor reference %d -> ", reference[i]);
        print_frames(frames, n_frames);
    }
    printf("\nTotal Page Faults in %s: %d\n", algorithm, faults);
    printf("Total Page Hits in %s: %d\n", algorithm, hits);
}

int main(){
    srand(time(0));
    int reference_string[MAX_REF_STR_LEN];
    printf("Reference String: ");
    for(int i = 0; i < MAX_REF_STR_LEN; i++){
        reference_string[i] = (rand() % MAX_PAGE) + 1;
        printf("%d ", reference_string[i]);
    }
    printf("\n");
    int n_frames;
    printf("Enter the number of frames: ");
    scanf("%d", &n_frames);
    int frames[n_frames];
    printf("\nLRU Algorithm\n");
    page_replacement(reference_string, frames, n_frames, MAX_REF_STR_LEN, "LRU");
    printf("\nOptimal Page Replacement Algorithm\n");
    page_replacement(reference_string, frames, n_frames, MAX_REF_STR_LEN, "Optimal");
    return 0;
}
