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
    heap->length = 0;
    FILE *in, *out;
    int j = 1;
    if(!(in = fopen("input.txt", "r"))) exit(1);
    while(!feof(in))
    {
        fscanf(in, "%d", &(heap->r[j++])); //C���Դ��ļ��а��ÿո�ָ�����������������
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
