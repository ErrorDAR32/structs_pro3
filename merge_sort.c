#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void insert(void *array, int start, int end, int (*compare)(void *, void *), int data_size) {
    int i = start;
    void* temp = malloc(data_size);
    while (i < (end-1) && compare(array + i * data_size, array + (i + 1) * data_size) > 0) {
        memcpy(temp, array + i * data_size, data_size);
        memcpy(array + i * data_size, array + (i + 1) * data_size, data_size);
        memcpy(array + (i + 1) * data_size, temp, data_size);
        i++;
    }
}


void merge(void *arr, int start, int mid, int end, int (*compare)(void *, void *), int data_size) {
    int l, w, r;

    l = start;
    w = mid;
    r = mid;

    void *tmp = malloc(data_size);
    while (l < r) {
        if (r>=end) {
            r=w;
        }
        if (l==w) {
            w = r;
        }
        if (w==r) {
            if (compare(arr+l*data_size, arr+r*data_size) < 0) {
                l++;
                continue;
            }

            //swap(l, r);
            memcpy(tmp, arr+l*data_size, data_size); 
            memcpy(arr+l*data_size, arr+r*data_size, data_size);
            memcpy(arr+r*data_size, tmp, data_size);
            r++;
            l++;
            continue;
        }

        if (compare(arr+l*data_size, arr+r*data_size) < 0) {
            //l<r
            if (compare(arr+l*data_size, arr+w*data_size) < 0) {
                //l<w && l<r
                // do nothing
                l++;
                continue;
            } else {
                //w<l<r
                //swap(l, w);
                memcpy(tmp, arr+l*data_size, data_size);
                memcpy(arr+l*data_size, arr+w*data_size, data_size);
                memcpy(arr+w*data_size, tmp, data_size);
                l++;
                insert(arr, w, r, compare, data_size); 
                continue;
            }
        } else {
            //r<l
            if (compare(arr+r*data_size, arr+w*data_size) < 0) {
                //r<w && r<l
                //swap(l, r);
                memcpy(tmp, arr+l*data_size, data_size);
                memcpy(arr+l*data_size, arr+r*data_size, data_size);
                memcpy(arr+r*data_size, tmp, data_size);
                l++;
                insert(arr, r, end, compare, data_size);
                continue;
            } else {
                //w<r<l
                //swap(l, w);
                memcpy(tmp, arr+l*data_size, data_size);
                memcpy(arr+l*data_size, arr+w*data_size, data_size);
                memcpy(arr+w*data_size, tmp, data_size);
                l++;
                insert(arr, w, r, compare, data_size);
                continue;
            }
        }
    }
}


void merge_sort(void *arr, int size, int (*compare)(void *, void *), int data_size) {
    typedef struct range {int first; int end; bool to_merge; } range;
    
    int stack_capacity = 20;
    int stack_size = 0;
    range *stack = malloc(sizeof(range) * 40);

    stack[0] = (range){0, size};
    stack_size = 1;

    while (stack_size > 0) {
        range *r = &stack[stack_size-1];
        stack_size--;
        int mid = (r->first + r->end)/2;

        if (r->to_merge) {
            merge(arr, r->first, mid, r->end, compare, data_size);
            continue;
        } else {
            if ((r->end - r->first) > 1) {
                stack[stack_size].to_merge = true;
                stack_size++;
                


                stack[stack_size] = (range){mid, r->end, false};
                stack_size++;
                stack[stack_size] = (range){r->first, mid, false};
                stack_size++;

                if (stack_size > stack_capacity) {
                    return;
                }
            } else {
                stack_size++;
                r->to_merge = true;
            }
        }        
    }
}


int compare_ints(void *a, void *b) {
    int *x = a;
    int *y = b;
    if (*x < *y) {
        return -1;
    } else if (*x > *y) {
        return 1;
    } else {
        return 0;
    }
}

void test() {
    int arr[] = {1,5,2,9,7,3,6,4,8,0};
    merge_sort(arr, 10, compare_ints, sizeof(int));
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}