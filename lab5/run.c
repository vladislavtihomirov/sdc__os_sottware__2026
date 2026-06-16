#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t running = 1;
static volatile sig_atomic_t printStatus = 0;
static volatile sig_atomic_t iteration = 0;

void handle_sigint(int signum) {
    (void)signum;
    running = 0;
}

void handle_sigusr1(int signum) {
    (void)signum;
    printStatus = 1;
}

void print_usage(const char *programName) {
    printf("Usage: %s <mode>\n", programName);
    printf("Modes:\n");
    printf("  tree          Create two child processes and wait for them\n");
    printf("  exec          Fork and run ps through execvp\n");
    printf("  zombie        Create a temporary zombie process\n");
    printf("  zombie-fixed  Create child and clean it with waitpid\n");
    printf("  server        Handle SIGUSR1 and SIGINT gracefully\n");
}

pid_t checked_fork(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    return pid;
}

void print_child_status(int childNumber, pid_t pid, int status) {
    if (WIFEXITED(status)) {
        printf("[Parent] Child %d (PID=%d) exited with code %d\n",
               childNumber,
               pid,
               WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("[Parent] Child %d (PID=%d) killed by signal %d\n",
               childNumber,
               pid,
               WTERMSIG(status));
    }
}

int run_tree_demo(void) {
    int status;

    printf("[Parent] PID=%d started\n", getpid());
    fflush(stdout);

    pid_t child1 = checked_fork();

    if (child1 == 0) {
        printf("[Child 1] PID=%d PPID=%d started\n", getpid(), getppid());
        fflush(stdout);
        sleep(5);
        _exit(1);
    }

    pid_t child2 = checked_fork();

    if (child2 == 0) {
        printf("[Child 2] PID=%d PPID=%d started\n", getpid(), getppid());
        fflush(stdout);
        sleep(5);
        _exit(2);
    }

    if (waitpid(child1, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    print_child_status(1, child1, status);

    if (waitpid(child2, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    print_child_status(2, child2, status);

    printf("[Parent] All children finished.\n");
    return 0;
}

int run_exec_demo(void) {
    int status;
    pid_t child = checked_fork();

    if (child == 0) {
        char *args[] = {"ps", "-o", "pid,ppid,stat,comm", NULL};

        execvp(args[0], args);
        perror("execvp");
        _exit(127);
    }

    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    print_child_status(1, child, status);
    return 0;
}

int run_zombie_demo(void) {
    pid_t child = checked_fork();

    if (child == 0) {
        _exit(0);
    }

    printf("[Parent] PID=%d created child PID=%d and will not wait for 15 seconds.\n",
           getpid(),
           child);
    printf("Run in another terminal: ps -o pid,ppid,stat,comm | grep Z\n");
    sleep(15);

    return 0;
}

int run_zombie_fixed_demo(void) {
    int status;
    pid_t child = checked_fork();

    if (child == 0) {
        _exit(0);
    }

    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    print_child_status(1, child, status);
    printf("[Parent] Child was collected, so no zombie remains.\n");

    return 0;
}

int setup_signal_handlers(void) {
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    action.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction SIGINT");
        return 1;
    }

    action.sa_handler = handle_sigusr1;
    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigaction SIGUSR1");
        return 1;
    }

    return 0;
}

int run_server_demo(void) {
    if (setup_signal_handlers() != 0) {
        return 1;
    }

    printf("[Server] PID=%d started. SIGUSR1 shows status, Ctrl+C stops.\n", getpid());

    while (running) {
        iteration++;
        printf("[Server] Iteration %d...\n", (int)iteration);

        if (printStatus) {
            printf("[SIGUSR1] Current iteration: %d\n", (int)iteration);
            printStatus = 0;
        }

        sleep(1);
    }

    printf("Shutdown after %d iterations. Goodbye!\n", (int)iteration);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "tree") == 0) {
        return run_tree_demo();
    }

    if (strcmp(argv[1], "exec") == 0) {
        return run_exec_demo();
    }

    if (strcmp(argv[1], "zombie") == 0) {
        return run_zombie_demo();
    }

    if (strcmp(argv[1], "zombie-fixed") == 0) {
        return run_zombie_fixed_demo();
    }

    if (strcmp(argv[1], "server") == 0) {
        return run_server_demo();
    }

    print_usage(argv[0]);
    return 1;
}
