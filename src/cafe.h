#ifndef CAFE_H
#define CAFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define COMMAND_EXIT 0
#define COMMAND_ORDER 1
#define COMMAND_KITCHEN 2
#define COMMAND_BAR 3
#define COMMAND_STATS 4

void input_command();
int get_command();
void input_order(Queue *queue_kitchen, Queue *queue_bar);
void input_name_add_price(char *name, int *price);
void free_buffer();
void print_stats(int count_kitchen, int total_kitchen, int count_bar, int total_bar);

#endif  // CAFE_H