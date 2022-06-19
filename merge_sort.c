//merge sort implementation
//parametric comparisons
//generic
//in place merge
//stable?


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void swap(void* a, void* b, void* temp, int data_size) {
        memcpy(temp, a, data_size);
        memcpy(a, b, data_size);
        memcpy(b, temp, data_size);
}


void insert(void *array, int start, int end, int (*compare)(void *, void *), int data_size) {
    int i = start;
    void* temp = malloc(data_size);
    while (i < (end-1) && compare(array + i * data_size, array + (i + 1) * data_size) > 0) {
        swap(array+i*data_size, array+(i+1)*data_size, temp, data_size);
        i++;
    }
}


void merge(void *arr, int start, int mid, int end, int (*compare)(void *, void *), int data_size) {
    int l, r;
    l = start;
    r = mid;

    void *tmp = malloc(data_size);

    while (l < r && r < end) {
        if (compare(arr+r*data_size, arr+l*data_size) < 0) {
            //r<l
            swap(arr+l*data_size, arr+r*data_size, tmp, data_size);

            insert(arr, r, end, compare, data_size);
        }
        l++;
    }
}


void merge_sort(void *arr, int size, int (*compare)(void *, void *), int data_size) {
    typedef struct range {int first; int end; bool to_merge; } range;
    
    //todo: make stack dynamic
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
    int arr[] = {1,5,2,9,7,3,6,4,8,0,1,2,3,43,4,5,7,8,2,9,23,7,3,6,8,9,3,57,2,78,9,2,7,3};
    int size = sizeof(arr)/sizeof(int);

    merge_sort(arr, size, compare_ints, sizeof(int));
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//void main() {
//    test();
//}