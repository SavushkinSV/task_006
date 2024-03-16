#include "queue.h"

#include "cafe.h"

/* Функция инициализации очереди */
Queue *init_queue() {
    Queue *pointer_queue = malloc(sizeof(Queue));
    pointer_queue->first = 1;
    pointer_queue->last = 0;

    return pointer_queue;
}

/* Функция добавления в очередь */
void insert(Queue *queue, Order new_order) {
    if (queue->last < QUEUE_SIZE - 1) {
        queue->last++;
        queue->orders[queue->last] = new_order;
    } else {
        printf("Queue is full");
    }
}

/* Проверка на пустую очередь */
int is_impty(Queue *queue) { return (queue->last < queue->first) ? 1 : 0; }

/* Удаление заказа из очереди*/
Order remove_order(Queue *queue) {
    Order first_order = {.room = 0};
    if (!is_impty(queue)) {
        first_order = queue->orders[queue->first];
        for (int i = queue->first; i < queue->last; i++) {
            queue->orders[i] = queue->orders[i + 1];
        }
        queue->last--;
    } else {
        // printf("Queue is empty");
    }

    return first_order;
}

/* Печать первого заказа */
void print_order(Queue *queue) {
    if (is_impty(queue) == 1) {
        printf("NO ORDERS\n");
    } else {
        printf("%s\n", queue->orders[queue->first].name);
    }
}