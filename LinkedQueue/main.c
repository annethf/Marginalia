#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct queueNode
{
    char elem;
    struct queueNode *next;
};
typedef struct queueNode qNode;

qNode *initQueue(qNode *queue)
{
    if(!queue)
    {
        queue = (qNode*)malloc(sizeof(qNode));
        queue->elem = 0;
        queue->next = NULL;
    }
    return queue;
}

void destroyQueue(qNode *queue)
{
    qNode *p = queue;
    while(p->next)
    {
        queue = p->next;
        p->elem = 0;
        free(p);
        p = queue;
    }
    free(queue);
    queue = NULL;
}

void clearQueue(qNode *queue)
{
    qNode *p = queue;
    if(!p->next) return;
    while(p->next)
    {
        p = p->next;
        p->elem = 0;
    }
}

int queueEmpty(qNode *queue)
{
    if(!queue->next) return 1;
    else return 0;
}

int queueLength(qNode *queue)
{
    int length = 0;
    qNode *p = queue;
    while(p->next)
    {
        p = p->next;
        length++;
    }
    return length;
}

char getHead(qNode *queue, char e)
{
    if(!queue->next) return 0;
    e = queue->next->elem;
    return e;
}

void enQueue(qNode *queue, char e)
{
    qNode *p = queue;
    qNode *q = (qNode*)malloc(sizeof(qNode));
    q->elem = e;
    q->next = NULL;
    if(!p->next)
        p->next = q;
    else
    {
        while(p->next)
            p = p->next;
        p->next = q;
    }
}

int deQueue(qNode *queue, char e)
{
    qNode *p = queue;
    if(!p->next) return 0;
    qNode *q = p->next;
    e = q->elem;
    p->next = q->next;
    free(q);
    q = NULL;
    return 1;
}

void visit(char e)
{
    printf("%c ", e);
}

void queueTraverse(qNode *queue, void visit(char e))
{
    qNode *p = queue;
    while(p->next)
    {
        p = p->next;
        visit(p->elem);
    }
}

int main()
{
    qNode *queue = NULL;
    queue = initQueue(queue);
    printf("empty = %d\n", queueEmpty(queue));
    enQueue(queue, 'A');
    enQueue(queue, 'B');
    enQueue(queue, 'C');
    enQueue(queue, 'D');
    enQueue(queue, 'E');
    printf("empty = %d\n", queueEmpty(queue));
    char e = 0;
    deQueue(queue, e);
    printf("head = %c\n", getHead(queue, e));
    printf("length = %d\n", queueLength(queue));
    queueTraverse(queue, visit);
    clearQueue(queue);
    queueTraverse(queue, visit);
    destroyQueue(queue);
    return 0;
}
