#include <glob.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <stdio.h>
int find_keyboard_fd() {
    glob_t gl;
    
    // try by-id first (USB keyboards)
    if (glob("/dev/input/by-id/*event-kbd", 0, NULL, &gl) == 0 && gl.gl_pathc > 0) {
        int fd = open(gl.gl_pathv[0], O_RDONLY);
        globfree(&gl);
        if (fd >= 0) return fd;  // only return if open succeeded
    } else {
        globfree(&gl);
    }
    
    // fall back to by-path (PS/2, built-in laptop keyboards)
    if (glob("/dev/input/by-path/*event-kbd", 0, NULL, &gl) == 0 && gl.gl_pathc > 0) {
        int fd = open(gl.gl_pathv[0], O_RDONLY);
        globfree(&gl);
        if (fd >= 0) return fd;
    } else {
        globfree(&gl);
    }
    
    return -1;
}
