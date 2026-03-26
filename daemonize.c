#include <unistd.h>
#include <stdlib.h>
void daemonize() {
    pid_t pid = fork();
    
    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        exit(0);
    }

    if (setsid() < 0) {
        exit(1);
    }

    pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
