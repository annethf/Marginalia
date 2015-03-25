#include <stdio.h>
#include <stdlib.h>

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
    //����ȫ�������ĵ�һ����Ҷ�ӽڵ㿪ʼ��ǰ��������ɴ󶥶�
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
//������
void heapSort(heapType *heap)
{
    int i = 0;
    int temp;
    for(i = (heap->length) / 2; i > 0; i--)
        heapAdjust(heap, i, heap->length);
    for(i = heap->length; i > 1; i--)
    {
         //�ѶѶ�Ԫ���뵱ǰ��ȫ�����������һ��Ԫ�ؽ���
         temp = heap->r[1];
         heap->r[1] = heap->r[i];
         heap->r[i] = temp;
         //���µ����ɴ󶥶�
         heapAdjust(heap, 1, i - 1);
    }
}

int main()
{
    heapType *heap = (heapType*)malloc(sizeof(heapType));
    heap->r[1] = 49;
    heap->r[2] = 38;
    heap->r[3] = 65;
    heap->r[4] = 97;
    heap->r[5] = 76;
    heap->r[6] = 13;
    heap->r[7] = 27;
    heap->r[8] = 50;
    heap->length = 8;
    heapSort(heap);
    int i = 0;
    for(i = 1; i <= heap->length; i++)
        printf("%d ", heap->r[i]);
    printf("\n");
    free(heap);
    heap = NULL;
    return 0;
}
