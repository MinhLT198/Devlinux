#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Activity_log.h>

//static HistoryNode_t *tail = NULL;
static HistoryNode_t *head = NULL;
static HistoryNode_t *current = NULL;

/**
 * @brief Logs a new activity entry.
 * 
 * @param entry The activity entry to log.
 * @return void
 * @note ...
*/
void history_log_activity(const char* entry)
{
    HistoryNode_t *new_entry = (HistoryNode_t *)malloc(sizeof(HistoryNode_t));
    if (new_entry == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(new_entry->log_entry, entry, sizeof(new_entry->log_entry) - 1);
    new_entry->log_entry[sizeof(new_entry->log_entry) - 1] = '\0';
    new_entry->next = head;
    new_entry->prev = NULL;

    if (head == NULL) {
        head = new_entry;
    } else {
        head->prev = new_entry;
        head = new_entry;
    }
}
/**
 * @brief Navigates through the activity log.
 * 
 * @param void
 * @return void
 * @note ...
*/
void history_navigate(void)
{
    if (head == NULL) {
        printf("No activity log entries.\n");
        return;
    }

    if (current == NULL) {
        current = head;
    }

    char command;
    
    while (1) {
        printf("Enter 'n' for next, 'p' for previous, 'q' to quit: ");
        printf("Current Entry: %s\n", current->log_entry);
        printf("Command: ");
        command = getchar();
        while (getchar() != '\n'); // Clear input buffer
        switch (command) {
            case 'n':
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("No next entry.\n");
                }
                break;
            case 'p':
                if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    printf("No previous entry.\n");
                }
                break;
            case 'q':
                printf("Exiting navigation.\n");
                return;
            default:
                printf("Invalid command.\n");
        }
    }
}
/**
 * @brief Frees all memory allocated for the activity log.
 * 
 * @param void
 * @return void
 * @note ...
*/
void free_activity_log(void)
{
    current = head;
    while (current != NULL) {
        HistoryNode_t *temp = current;
        current = current->next;
        free(temp);
    }
}