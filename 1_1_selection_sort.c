#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 101


void selection_sort(int);
void selection_sort_pointer(int);

void sort(int[], int);
void sort_pointer(int*, int);
void swap(int*, int*);
void showResult(int[], int);
void showResult_pointer(int*, int);
void binsearch(int[], int, int);
void binsearch_pointer(int*, int, int);

int* genList(int);

/*
Selection sort
for(i=0; i<n; i++){
  比較 list[i] 到 list[n-1], 將比較小的放在前面
}

Binary search
while(left <= right){
  middle = (left + right) / 2
  if(list[middle] == searchNum){
    return middle;
  }else if(list[middle] > searchNum){
    right = middle;
  }else{
    left = middle;
  }
}
*/
void main(void){
  int n;

  printf("please enter your list size : ");

  do{
    scanf("%d", &n);
  } while(n < 1 || n > MAX_SIZE);

  printf("your input number is %d\n", n);

  selection_sort(n);
  selection_sort_pointer(n);
}

void selection_sort(int n){
  int i;
  int list[MAX_SIZE];
  printf("\n---------start general selection sort ---------\n");
  //initailize
  for(i=0; i<n; i++){
    list[i] = rand()  % 1000;
  }
  int searchNum = list[0];
  sort(list, n);
  showResult(list, n);
  printf("\n---------end general selection sort ---------\n");
  printf("\n---------start general binsearch ---------\n");
  binsearch(list, searchNum, n);
  printf("\n---------end general binsearch ---------\n");
}

void selection_sort_pointer(int n){
  printf("\n---------start pointer selection sort ---------\n");
  int* newList = genList(n);
  int searchNum = *newList;
  sort_pointer(newList, n);
  showResult_pointer(newList, n);
  printf("\n---------end pointer selection sort ---------\n");
  printf("\n---------start pointer binsearch ---------\n");
  binsearch_pointer(newList, searchNum, n);
  printf("\n---------end pointer binsearch ---------\n");
}

//排序邏輯
void sort(int list[], int n){
    int i, j, min;
    for(i=0; i<n; i++){
      min = i;
      for(j=i+1; j<n; j++){
        if(list[min] > list[j]){
          min = j;
        }
      }
      swap(&list[i], &list[min]);
    }
}

//排序邏輯(pointer)
void sort_pointer(int* list, int n){
    int i, j, min;
    for(i=0; i<n; i++){
      min = i;
      for(j=i+1; j<n; j++){
        if(*(list + min) > *(list + j)){
          min = j;
        }
      }
      swap((list + i), (list + min));
    }
}

//調換邏輯
void swap(int* i, int* j){
  int temp = *i;
  *i = *j;
  *j = temp;
}

//顯示邏輯
void showResult(int list[], int n){
  int i;
  printf("%s\n", "the sorted list is : ");
  for(i=0; i<n; i++){
    printf("%d ", list[i]);
  }
}

//顯示邏輯(pointer)
void showResult_pointer(int* list, int n){
  int i;
  printf("%s\n", "the sorted list is : ");
  for(i=0; i<n; i++){
    printf("%d ", *(list + i));
  }
}

int* genList(int n){
  int* newList = malloc(sizeof(int) * n);
  int i;
  for(i=0; i<n; i++){
    int* arrayNode = newList + i;
    *arrayNode = rand()  % 1000;
  }

  return newList;
}

//Binary search
void binsearch(int list[], int chooseNum ,int n){
  int i, middle, left, right;
  right = n-1;
  left = 0;
  printf("\nyour search number is %d\n", chooseNum);
  while(left <= right){
    middle = (right + left) / 2;
    if(list[middle] == chooseNum){
      break;
    }else if(list[middle] >= chooseNum){
      right = middle;
    }else{
      left = middle;
    }
  }
  printf("\nyour search number location is %d\n", middle+1);
}

//Binary search(pointer)
void binsearch_pointer(int* list, int chooseNum ,int n){
  int i, middle, left, right;
  right = n-1;
  left = 0;
  printf("\nyour search number is %d\n", chooseNum);
  while(left <= right){
    middle = (right + left) / 2;
    if(*(list + middle) == chooseNum){
      break;
    }else if(*(list + middle) >= chooseNum){
      right = middle;
    }else{
      left = middle;
    }
  }
  printf("\nyour search number location is %d\n", middle+1 );
}
