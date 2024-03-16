
#include "cafe.h"

#include "queue.h"

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
        switch (command) {
            case COMMAND_ORDER:
                free_buffer();
                input_order(queue_kitchen, queue_bar);
                break;
            case COMMAND_KITCHEN:
                print_order(queue_kitchen);
                tmp = remove_order(queue_kitchen);
                if (tmp.room) {
                    count_kitchen++;
                    total_kitchen += tmp.price;
                }
                break;
            case COMMAND_BAR:
                print_order(queue_bar);
                tmp = remove_order(queue_bar);
                if (tmp.room) {
                    count_bar++;
                    total_bar += tmp.price;
                }
                break;
            case COMMAND_STATS:
                print_stats(count_kitchen, total_kitchen, count_bar, total_bar);
                break;
            case COMMAND_EXIT:
                break;
            default:
                printf("UNKNOWN COMMAND\n");
        }
    }
}

/* Функция получения команды */
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

/* Печать статистики */
void print_stats(int count_kitchen, int total_kitchen, int count_bar, int total_bar) {
    printf("KITCHEN %d %d\n", count_kitchen, total_kitchen);
    printf("BAR %d %d\n", count_bar, total_bar);
}
