#include <errno.h>
#undef errno
extern int errno;

void _exit(int code) {
    volatile x = 1/0;
}

int _close(int file) {
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

unsigned long _read(int fd, void *buf, unsigned long cnt) {
    return 0;
}

unsigned long _write(int fd, void *buf, unsigned long cnt) {
    return 0;
}

int _open(const char *file, int flags, int mode) {
    return -1;
}

void *_sbrk(void* incr) {
    return 0;
}

int _fstat(int fd, struct stat *pstat) {
    return 0;
}

int _kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}

int _isatty(int file) {
  return 1;
}

int _getpid(void) {
  return 1;
}
