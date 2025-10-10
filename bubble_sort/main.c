#include<stdio.h>

int arr[4] = {2,4,3,1};
int arr1[4] = {6,7,5,8};
int arr2[4] = {11,12,10,9};

void swap_index(int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void swap_pointers(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int array[], int size)
{
    printf("array:%d\n", array);
    int* ptr = array;
    for(int i=0; i<size-1; i++){
        for (int j = 0; j < size-1-i; j++)
        {
            if(*ptr>*(ptr+1)){
                swap_pointers(ptr, ptr+1);
            }
            ptr++;
        }
        ptr = array;
    }
    printf("\n");
    for(int i=0; i<size; i++){
        printf("%d ", *ptr++);
    }
}

int main(){

    printf("arr:%d\n", arr);
    printf("&arr[0]:%d\n", &arr[0]);
    bubble_sort(arr,4);
    bubble_sort(arr1,4);
    bubble_sort(arr2,4);

    return 0;
}
