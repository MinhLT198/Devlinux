#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#define MAX_TASKS 100

typedef struct TaskNode {
    char task_description[MAX_TASKS];
    struct TaskNode* next;
} TaskNode_t;

void queue_add_task(const char* description);
TaskNode_t* queue_get_next_task(void);
void print_task_queue(void);
void free_task_queue(void);

#endif // __TASK_QUEUE_H__