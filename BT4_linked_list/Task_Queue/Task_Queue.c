#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Task_Queue.h>

static TaskNode_t *head = NULL;
static TaskNode_t *tail = NULL;

/**
 * @brief Adds a new task to the queue.
 * 
 * @param description Description of the task to be added.
 * @return void
 * @note ...
*/
void queue_add_task(const char* description)
{
    TaskNode_t *new_task = (TaskNode_t *)malloc(sizeof(TaskNode_t));
    if (new_task == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(new_task->task_description, description, sizeof(new_task->task_description) - 1);
    new_task->task_description[sizeof(new_task->task_description) - 1] = '\0';
    new_task->next = NULL;

    if (tail == NULL) {
        head = tail = new_task;
    } else {
        tail->next = new_task;
        tail = new_task;
    }
}
/**
 * @brief Retrieves and removes the next task from the queue.
 * 
 * @param void
 * @return TaskNode_t* Pointer to the next task node, or NULL if the queue is empty.
 * @note ... 
*/
TaskNode_t* queue_get_next_task(void)
{
    if (head == NULL) {
        return NULL;
    }
    TaskNode_t *next_task = head;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    }
    return next_task;
}
/**
 * @brief Prints all tasks in the queue.
 * 
 * @param void
 * @return void
 * @note ... 
*/
void print_task_queue(void)
{
    TaskNode_t *current = head;
    if (current == NULL) {
        printf("Task queue is empty.\n");
        return;
    }
    printf("Current Task Queue:\n");
    while (current != NULL) {
        printf("- %s\n", current->task_description);
        current = current->next;
    }
    //free(current);
}
/**
 * @brief Frees all tasks in the queue.
 * 
 * @param void
 * @return void
 * @note ... 
*/
void free_task_queue(void)
{
    TaskNode_t *current = head;
    while (current != NULL) {
        TaskNode_t *temp = current;
        current = current->next;
        free(temp);
    }
}
