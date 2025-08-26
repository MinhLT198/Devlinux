#ifndef __ACTIVITY_LOG_H__
#define __ACTIVITY_LOG_H__

#define MAX_LOG_ENTRY 50

typedef struct HistoryNode {
    char log_entry[MAX_LOG_ENTRY];
    struct HistoryNode *next;
    struct HistoryNode *prev;
}HistoryNode_t;

void history_log_activity(const char* entry);
void history_navigate(void);
void free_activity_log(void);

#endif // __ACTIVITY_LOG_H__