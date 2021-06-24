#include <stdio.h>
#include <stdlib.h>

void sift(int *numbers, int root, int bottom)
{
  int maxChild, done = 0;
  while((root * 2 + 1 <= bottom) && (!done))
  {
    if(root * 2 + 2 <= bottom)
    {
        if(numbers[root * 2 + 2] > numbers[root * 2 + 1])
            maxChild = root * 2 + 2;
        else
            maxChild = root * 2 + 1;
    }
    else
        maxChild = root * 2 + 1;
    if(numbers[root] < numbers[maxChild])
    {
      int temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void psort(int *numbers, int array_size) 
{
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2); i >= 0; i--)
    sift(numbers, i, array_size - 1);
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    sift(numbers, 0, i - 1);
  }
}

int main()
{
    int arr_len;
    scanf("%d",&arr_len);
    int *arr = (int*)malloc(sizeof(int) * arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        scanf("%d",&arr[i]);
    }
    psort(arr, arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        printf("%d", arr[i]);
        if(i<arr_len-1)
        printf(" ");
    }
    free(arr);
    printf("\n");
}

