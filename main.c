#include <termios.h>
#include <signal.h>
#include <unistd.h>

/* unran code - ignoremyaccount 2025 */

struct termios astdout1;
struct termios astdin1; 

void rawncb(struct termios *astdout, struct termios *astdin, void (*cb)(char *, size_t)) {
  astdin->c_iflag &= ~(ECHO | ICANON);
}

/* restore and exit */
void restore_e(int a) {
  tcsetattr(STDOUT_FILENO, TSCANOW, &astdout1);
  tcsetattr(STDIN_FILENO, TSCANOW, &astdin1);
  _exit(0);
}

/* signal set - wide area - array init*/
void sigset_wide(void (*callback)(int)) {
  int arr[] = {
    SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS,
    SIGFPE, SIGKILL, SIGUSR1, SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM,
    SIGTERM, SIGCHLD, SIGCONT, SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU,
    SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF, SIGWINCH, SIGIO,
    SIGPWR, SIGSYS
  };
  int size = sizeof(arr)/sizeof(arr[0]);

  for (int i = 0; i < size; i++) {
    signal(arr[i], callback)
  }
}

int main() {
  tcgetattr(STDOUT_FILENO, &astdout1);
  tcgetattr(STDIN_FILENO, &astdin1);

  sigset_wide(restore_e);

  
  return 0;
}
