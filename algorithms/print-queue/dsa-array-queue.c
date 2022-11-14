/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Queue implementation using array in C
 * @date    12-10-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int QueueType;

typedef struct queue {
    int front;
    int rear;
    QueueType *arr;
} *queue;

queue new_queue();
bool queue_enqueue(queue qu, QueueType val);
QueueType queue_dequeue(queue qu);
QueueType queue_peek(queue qu);
bool queue_isempty(queue qu);
void queue_free(queue *head);

#define queue_error(e) {                     \
    fprintf(stderr, "queue error: %s\n", e); \
    abort();                                 \
}

#define queue_warn(e, retval) {              \
    fprintf(stderr, "queue warn: %s\n", e);  \
    return retval;                           \
}

// allocate a new queue
queue new_queue()
{
    queue qu = calloc(1, sizeof(struct queue));
    if (!qu) queue_error("null pointer");
    qu->front = -1;
    qu->rear = -1;
    qu->arr = NULL;
    return qu;
}

bool queue_enqueue(queue qu, QueueType val)
{
    if (!qu) queue_error("null pointer");
    qu->arr = realloc(qu->arr, (++(qu->rear) + 1) * sizeof(QueueType));
    if (!qu->arr) queue_error("null pointer");
    qu->arr[qu->rear] = val;
    if (qu->front == -1) ++qu->front;
    return true;
}

QueueType queue_dequeue(queue qu)
{
    if (!qu) queue_error("null pointer");
    if (qu->front < 0) queue_warn("underflow", 0);
    QueueType tmp = qu->arr[qu->front++];
    if (qu->front > qu->rear) {
        free(qu->arr);
        qu->arr = NULL;
        qu->front = qu->rear = -1;
    }
    return tmp;
}

QueueType queue_peek(queue qu)
{
    if (!qu) queue_error("null pointer");
    if (qu->front < 0) queue_warn("underflow", 0);
    return qu->arr[qu->front];
}

bool queue_isempty(queue qu)
{
    return qu->front < 0;
}

void queue_free(queue *qu)
{
    if (!qu || !*qu) queue_error("null pointer");
    free((*qu)->arr);
    free(*qu);
    *qu = NULL;
}

int main()
{
    queue qu = new_queue();
    int ch = 0;
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: enqueue to rear\n"
               "   2: peek front\n"
               "   3: dequeue front\n"
               "   4: is empty?\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // enqueue
            case 1: {
                int val;
                printf("enter val = ");
                scanf("%d", &val);
                queue_enqueue(qu, val);
                break;
            }
            // peek
            case 2: {
                printf("value at front = %d\n", queue_peek(qu));
                break;
            }
            // dequeue
            case 3: {
                printf("value on dequeue = %d\n", queue_dequeue(qu));
                break;
            }
            // is empty
            case 4: {
                if (queue_isempty(qu))
                    printf("queue is empty\n");
                else
                    printf("queue is not empty\n");
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(ch);
    queue_free(&qu);
    return 0;
}

/* OUTPUT:

run: dsa-array-queue.c

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 23

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 56

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 98

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 44

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 2

value at front = 23

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 23

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 56

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 98

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 44

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

queue warn: underflow
value on dequeue = 0

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 4

queue is empty

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 0

*/
