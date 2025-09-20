#include <stdio.h>
#include <setjmp.h>
#include <time.h>
#include <string.h>
#include "memory_lab.h"

jmp_buf buf; 

int main() {
    
    char mode;
    printf("-------------------------------------------\n");
    printf("--        Memory Lab Debug with GDB      --\n");
    printf("-------------------------------------------\n");
    printf("Key debug mode: 's' -> | Stack Overflow |  \n");
    printf("                'm' -> |   Memory Leak  |  \n");
    printf("                'o' -> |  Out Of Memory |  \n");
    printf("                'q' -> |      Quit      |  \n");
    printf("-------------------------------------------\n");
    setjmp(buf); // Luu lai trang thai hien tai
    printf("Choose mode: ");
    char line[100];
    if (fgets(line, sizeof(line), stdin) != NULL) {
        // Loại bỏ '\n' nếu có
        line[strcspn(line, "\n")] = 0;

        // Nếu độ dài > 1 → lỗi
        if (strlen(line) != 1) {
            log_message(WARN, "Invalid mode selected\n");
            longjmp(buf, 1); // Tro ve trang thai da luu 
        }
        mode = line[0];
    }
    switch (mode) {
        case 's':
            log_message(INFO, "Stack Overflow mode selected.");
            stack_overflow(); // lệnh để kiểm tra stack overflow " gdb ./build/main "  sau đó " run " và " backtrace "(bt)
            break;
        case 'm':
            log_message(INFO, "Memory Leak mode selected.\n");
            memory_leak(); // lệnh để kiểm tra memory leak " valgrind --leak-check=full ./build/main "
            break;
        case 'o':
            log_message(INFO, "Out Of Memory mode selected.\n");
            out_of_memory(); 
            break;
        case 'q':
            printf("Quitting program.\n");
            break;
        default:
            log_message(WARN, "Invalid mode selected\n");
            longjmp(buf, 1); // Tro ve trang thai da luu 
            break;;
    }
    printf("Program finished.\n");
    return 0;
}