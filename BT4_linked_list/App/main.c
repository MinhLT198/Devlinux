#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <string.h>
#include <Task_Queue.h>
#include <Activity_log.h>
#include <stdbool.h>

int main() {
    char command[100];
    int a=1;
    while (1) {
        printf("\nEnter command (add <decription>, run, list, history, quit): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // bỏ newline

        if (strncmp(command, "add ", 4) == 0) {
            queue_add_task(command + 4);
        } else if (strcmp(command, "run") == 0) {
            TaskNode_t* task = queue_get_next_task();
            if (task) {
                printf("Execution: %s\n", task->task_description);
                history_log_activity(task->task_description);
                free(task);
            } else {
                printf("No tasks in the queue.\n");
            }
        } else if (strcmp(command, "list") == 0) {
            print_task_queue();
        } else if (strcmp(command, "history") == 0) {
            history_navigate();
        } else if (strcmp(command, "quit") == 0) {
            free_task_queue();
            free_activity_log();
            printf("Exiting...\n");
            break;
        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}