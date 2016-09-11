#ifndef SORT_H_
#define SORT_H_



//Ñ¡ÔñÅÅĞò(ÉıĞòÅÅÁĞ)
void selectionSort(int *array, int len);

//²åÈëÅÅĞòËã·¨(½µĞòÅÅÁĞ)
void insertionSort(int *array, int len);

//Ã°ÅİÅÅĞò
void bubbleSort(int *array, int len);

//Ï£¶ûÅÅĞò
void shellSort(int *array, int len);

//¿ìËÙÅÅĞò
void quickSort(int s[], int l, int r);

//¹é²¢ÅÅĞò
void mergeSort(int a[], int first, int last, int temp[]);

#endif //SORT_H_