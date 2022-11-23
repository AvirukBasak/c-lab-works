/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Circular queue implementation
 * @date    15-11-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int QueueType;

typedef struct queue {
    int front;
    int rear;
    size_t size;
    QueueType *arr;
} *queue;

queue new_queue(size_t size);
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
queue new_queue(size_t size)
{
    if (!size) queue_error("size 0");
    queue qu = calloc(1, sizeof(struct queue));
    if (!qu) queue_error("null pointer");
    qu->front = -1;
    qu->rear = -1;
    qu->size = size;
    qu->arr = calloc(size, sizeof(QueueType));
    if (!qu->arr) queue_error("null pointer");
    return qu;
}

bool queue_enqueue(queue qu, QueueType val)
{
    if (!qu) queue_error("null pointer");
    int rear = (qu->rear +1) % qu->size;
    if (rear == qu->front) queue_warn("overflow", false);
    qu->arr[qu->rear = rear] = val;
    if (qu->front == -1) ++qu->front;
    return true;
}

QueueType queue_dequeue(queue qu)
{
    if (!qu) queue_error("null pointer");
    if (qu->front < 0) queue_warn("underflow", 0);
    QueueType tmp = qu->arr[qu->front];
    if (qu->front == qu->rear)
        qu->front = qu->rear = -1;
    else
        qu->front = (qu->front +1) % qu->size;
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
    int size;
    printf("enter circular queue size: ");
    scanf("%d", &size);
    queue qu = new_queue(size);
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

enter circular queue size: 3

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 67

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 78

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 55

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 33
queue warn: overflow

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 2

value at front = 67

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 67

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 90

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 2

value at front = 78

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 78

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 1

enter val = 45

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 2

value at front = 55

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 55

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 90

choices:
   0: exit
   1: enqueue to rear
   2: peek front
   3: dequeue front
   4: is empty?
enter your choice: 3

value on dequeue = 45

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
enter your choice: 0

*/
