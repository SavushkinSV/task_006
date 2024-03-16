#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 10
#define MAX_LEN_STRING 256

typedef struct {
    int room;
    char name[MAX_LEN_STRING];
    int price;
} Order;

typedef struct {
    Order orders[QUEUE_SIZE];
    int first;
    int last;
} Queue;

Queue *init_queue();
void insert(Queue *queue, Order new_order);
int is_impty(Queue *queue);
Order remove_order(Queue *queue);
void print_order(Queue *queue);

#endif  // QUEUE_H