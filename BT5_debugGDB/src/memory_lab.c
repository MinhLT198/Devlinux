#include <stdio.h>
#include <time.h>
#include "memory_lab.h"

const char* LoglevelStrings[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

/**
 *  @brief Hàm ghi log mức độ và thông điệp cụ thể kèm theo thời gian hiện tại
 *  @param level Mức độ log
 *  @param message Thông điệp log
 *  @return void
 *  @note ...
 */
void log_message(Loglevel level, const char* message){
    time_t now;
    time(&now);
    struct tm *t = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t); 
    printf("[%s] [%s]: %s\n", time_str, LoglevelStrings[level], message);
}

/**
 * @brief Hàm đệ quy
 * @param n Độ sâu hiện tại của đệ quy
 * @return void
 * @note Gọi đệ quy không có điều kiện
 */
void recursize(int n){
    printf("Recursion depth: %d\n", n);
    recursize(n+1);
}

/**
 * @brief Hàm stack overflow
 * @param void
 * @return void
 * @note Gọi hàm đệ quy không có điều kiện dừng
 */
void stack_overflow() {
    // Gọi đệ quy không có điều kiện dừng để kiểm tra stack overflow  
    recursize(1);
    printf("End of stack_overflow function.\n");
}

/**
 * @brief Hàm tạo memory leak
 * @param void
 * @return void
 * @note Cấp phát bộ nhớ liên tục mà không giải phóng
 */
void memory_leak() {
    for (int i = 0; i < 5; i++)
    {
        // Cấp phát bộ nhớ mà không giải phóng
        void* leak = (void*)malloc((1024 * 1024) * sizeof(void)); // Cấp phát 1MB
        if (leak == NULL) {
            log_message(ERROR, "Memory allocation failed!");
            break;
        }
        log_message(INFO, "Allocated 1MB of memory.");
        sleep(1); // Tạm dừng để quan sát
    }
}

/**
 * @brief Hàm tạo out of memory
 * @param void
 * @return void
 * @note Cấp phát bộ nhớ liên tục cho đến khi hệ thống không còn đủ bộ
 */
void out_of_memory() {
    while(1)
    {
        // Cấp phát bộ nhớ mà không giải phóng
        void* leak = (void*)malloc((1024 * 1024 * 1024) * sizeof(void)); // Cấp phát 1GB
        if (leak == NULL) {
            log_message(ERROR, "Memory allocation failed!");
            break;
        }
        log_message(INFO, "Allocated 1GB of memory.");
    }
}
