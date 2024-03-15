#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_ORDER 1
#define COMMAND_KITCHEN 2
#define COMMAND_BAR 3
#define COMMAND_STATS 4
#define COMMAND_EXIT 0
#define MAX_LEN_STRING 256
#define QUEUE_SIZE 10

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

void input_command();
int get_command();
void input_order(Queue *queue_kitchen, Queue *queue_bar);
void input_name_add_price(char *name, int *price);
void free_buffer();
Queue *init_queue();
void insert(Queue *queue, Order new_order);
int is_impty(Queue *queue);
Order remove_order(Queue *queue);
void print_order(Queue *queue);

int main() {
    input_command();
    return EXIT_SUCCESS;
}

void input_command() {
    int total_kitchen = 0;
    int count_kitchen = 0;
    int total_bar = 0;
    int count_bar = 0;
    Queue *queue_kitchen = init_queue();
    Queue *queue_bar = init_queue();
    int command = -1;
    Order tmp;
    while (command) {
        command = get_command();
        free_buffer();
        switch (command) {
            case COMMAND_ORDER:
                input_order(queue_kitchen, queue_bar);
                break;
            case COMMAND_KITCHEN:
                print_order(queue_kitchen);
                tmp = remove_order(queue_kitchen);
                count_kitchen++;
                total_kitchen += tmp.price;
                break;
            case COMMAND_BAR:
                print_order(queue_bar);
                tmp = remove_order(queue_bar);
                count_bar++;
                total_bar += tmp.price;
                break;
            case COMMAND_STATS:
                printf("COMMAND_STATS");
                break;
            case COMMAND_EXIT:
                break;
            default:
                printf("UNKNOWN COMMAND");
        }
    }
}

int get_command() {
    int result = -1;
    char input[MAX_LEN_STRING];
    scanf("%255s", input);
    if (!strcmp(input, "ORDER")) result = COMMAND_ORDER;
    if (!strcmp(input, "KITCHEN")) result = COMMAND_KITCHEN;
    if (!strcmp(input, "BAR")) result = COMMAND_BAR;
    if (!strcmp(input, "STATS")) result = COMMAND_STATS;
    if (!strcmp(input, "EXIT")) result = COMMAND_EXIT;

    return result;
}

/* Функция ввода заказа */
void input_order(Queue *queue_kitchen, Queue *queue_bar) {
    char name[MAX_LEN_STRING];
    int price = 0;
    input_name_add_price(name, &price);
    Order new_order;
    new_order.room = COMMAND_KITCHEN;
    strcpy(new_order.name, name);
    new_order.price = price;
    insert(queue_kitchen, new_order);
    free_buffer();
    input_name_add_price(name, &price);
    new_order.room = COMMAND_BAR;
    strcpy(new_order.name, name);
    new_order.price = price;
    insert(queue_bar, new_order);
}

void input_name_add_price(char *name, int *price) {
    scanf("%255[^\n]", name);
    scanf("%d", price);
}

/* Функция очистки буфера от лишних символов */
void free_buffer() {
    int c;
    while ((c = getchar()) != '\n') {
        ;
    }
}

/* Функция инициализации стека */
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

/* Проверка на пустуй очередь */
int is_impty(Queue *queue) { return (queue->last < queue->first) ? 1 : 0; }

/* Удаление заказа */
Order remove_order(Queue *queue) {
    if (is_impty(queue) == 1) {
        printf("Queue is empty");
    }
    Order first_order = queue->orders[queue->first];
    for (int i = queue->first; i < queue->last; i++) {
        queue->orders[i] = queue->orders[i + 1];
    }
    queue->last--;

    return first_order;
}

/* Печать первого заказа */
void print_order(Queue *queue) {
    if (is_impty(queue) == 1) {
        printf("NO ORDERS");
    } else {
        // if (queue->orders[queue->first].room == COMMAND_KITCHEN) printf("KITCHEN ");
        // if (queue->orders[queue->first].room == COMMAND_BAR) printf("BAR ");
        printf("%s\n", queue->orders[queue->first].name);
    }
}
