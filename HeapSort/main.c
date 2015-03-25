#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct
{
    int r[MAX];
    int length;
}seqList;

typedef seqList heapType;

void heapAdjust(heapType *heap, int s, int m)
{
    int rc = heap->r[s];
    int j = 0;
    //从完全二叉树的第一个非叶子节点开始向前逐个调整成大顶堆
    for(j = 2 * s; j <= m; j *= 2)
    {
        if(j < m && heap->r[j] < heap->r[j + 1])
            j++;
        if(rc >= heap->r[j])
            break;
        heap->r[s] = heap->r[j];
        s = j;
    }
    heap->r[s] = rc;
}
//升序排
void heapSort(heapType *heap)
{
    int i = 0;
    int temp;
    for(i = (heap->length) / 2; i > 0; i--)
        heapAdjust(heap, i, heap->length);
    for(i = heap->length; i > 1; i--)
    {
         //把堆顶元素与当前完全二叉树的最后一个元素交换
         temp = heap->r[1];
         heap->r[1] = heap->r[i];
         heap->r[i] = temp;
         //重新调整成大顶堆
         heapAdjust(heap, 1, i - 1);
    }
}

int main()
{
    heapType *heap = (heapType*)malloc(sizeof(heapType));
    heap->length = 0;
    FILE *in, *out;
    int j = 1;
    if(!(in = fopen("input.txt", "r"))) exit(1);
    while(!feof(in))
    {
        fscanf(in, "%d", &(heap->r[j++])); //C语言从文件中把用空格分隔的整数读到数组中
        heap->length++;
    }
    heapSort(heap);
    if(!(out = fopen("output.txt","w"))) exit(1);
    for(j = 1; j <= heap->length; j++)
        fprintf(out, "%d ", heap->r[j]);
    fclose(in);
    fclose(out);
    free(heap);
    heap = NULL;
    return 0;
}
