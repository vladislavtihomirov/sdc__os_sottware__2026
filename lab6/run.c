#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

typedef struct {
    int thread_id;
    int iterations;
} WorkerArgs;

static long counter = 0;
static volatile long counter_volatile = 0;
static long counter_safe = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

static void print_usage(const char *program_name) {
    printf("Usage: %s <mode>\n", program_name);
    printf("Modes:\n");
    printf("  race       Increment shared counter without synchronization\n");
    printf("  volatile   Same as race, but counter is declared volatile\n");
    printf("  mutex      Increment shared counter protected by mutex\n");
    printf("  bench      Compare race, mutex, and batch timings\n");
}

static int checked_pthread_create(pthread_t *tid, void *(*func)(void *), void *arg) {
    int rc = pthread_create(tid, NULL, func, arg);

    if (rc != 0) {
        fprintf(stderr, "pthread_create: %s\n", strerror(rc));
        exit(1);
    }

    return 0;
}

static void checked_pthread_join(pthread_t tid) {
    int rc = pthread_join(tid, NULL);

    if (rc != 0) {
        fprintf(stderr, "pthread_join: %s\n", strerror(rc));
        exit(1);
    }
}

static void checked_mutex_lock(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_lock(mutex);

    if (rc != 0) {
        fprintf(stderr, "pthread_mutex_lock: %s\n", strerror(rc));
        exit(1);
    }
}

static void checked_mutex_unlock(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_unlock(mutex);

    if (rc != 0) {
        fprintf(stderr, "pthread_mutex_unlock: %s\n", strerror(rc));
        exit(1);
    }
}

static double timespec_to_ms(const struct timespec *start, const struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1000.0
         + (end->tv_nsec - start->tv_nsec) / 1e6;
}

static void run_threads(void *(*worker)(void *)) {
    pthread_t tids[NUM_THREADS];
    WorkerArgs args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;
        args[i].iterations = ITERATIONS;
        checked_pthread_create(&tids[i], worker, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        checked_pthread_join(tids[i]);
    }
}

static void *worker_race(void *arg) {
    WorkerArgs *a = (WorkerArgs *)arg;

    for (int i = 0; i < a->iterations; i++) {
        counter++;
    }

    printf("[Поток %d] Завершён\n", a->thread_id);
    return NULL;
}

static void *worker_race_volatile(void *arg) {
    WorkerArgs *a = (WorkerArgs *)arg;

    for (int i = 0; i < a->iterations; i++) {
        counter_volatile++;
    }

    printf("[Поток %d] Завершён\n", a->thread_id);
    return NULL;
}

static void *worker_race_quiet(void *arg) {
    WorkerArgs *a = (WorkerArgs *)arg;

    for (int i = 0; i < a->iterations; i++) {
        counter++;
    }

    return NULL;
}

static void *worker_safe(void *arg) {
    WorkerArgs *a = (WorkerArgs *)arg;

    for (int i = 0; i < a->iterations; i++) {
        checked_mutex_lock(&counter_mutex);
        counter_safe++;
        checked_mutex_unlock(&counter_mutex);
    }

    return NULL;
}

static void *worker_batch(void *arg) {
    WorkerArgs *a = (WorkerArgs *)arg;
    long local = 0;

    for (int i = 0; i < a->iterations; i++) {
        local++;
    }

    checked_mutex_lock(&counter_mutex);
    counter_safe += local;
    checked_mutex_unlock(&counter_mutex);

    return NULL;
}

static double run_experiment(void *(*worker)(void *)) {
    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    run_threads(worker);
    clock_gettime(CLOCK_MONOTONIC, &end);

    return timespec_to_ms(&start, &end);
}

static void print_counter_result(long expected, long actual) {
    printf("Ожидалось: %ld\n", expected);
    printf("Получено:  %ld\n", actual);

    if (actual == expected) {
        printf("Верно!\n");
    } else {
        printf("Потеряно:  %ld\n", expected - actual);
    }
}

static int run_race_demo(void) {
    long expected = (long)NUM_THREADS * ITERATIONS;

    counter = 0;
    run_threads(worker_race);
    print_counter_result(expected, counter);

    return 0;
}

static int run_volatile_demo(void) {
    long expected = (long)NUM_THREADS * ITERATIONS;

    counter_volatile = 0;
    run_threads(worker_race_volatile);
    print_counter_result(expected, counter_volatile);

    return 0;
}

static int run_mutex_demo(void) {
    long expected = (long)NUM_THREADS * ITERATIONS;

    counter_safe = 0;
    run_threads(worker_safe);
    print_counter_result(expected, counter_safe);

    return 0;
}

static int run_bench_demo(void) {
    long expected = (long)NUM_THREADS * ITERATIONS;

    printf("=== Без синхронизации (гонка) ===\n");
    counter = 0;
    double t_race = run_experiment(worker_race_quiet);
    printf("Получено: %ld (%s)\n", counter, counter == expected ? "верно" : "неверно");
    printf("Время: %.2f мс\n\n", t_race);

    printf("=== С mutex (lock на каждую итерацию) ===\n");
    counter_safe = 0;
    double t_mutex = run_experiment(worker_safe);
    printf("Получено: %ld (%s)\n", counter_safe, counter_safe == expected ? "верно" : "неверно");
    printf("Время: %.2f мс\n\n", t_mutex);

    printf("=== С mutex (батч: локальный счётчик) ===\n");
    counter_safe = 0;
    double t_batch = run_experiment(worker_batch);
    printf("Получено: %ld (%s)\n", counter_safe, counter_safe == expected ? "верно" : "неверно");
    printf("Время: %.2f мс\n\n", t_batch);

    if (t_race > 0.0) {
        printf("Замедление mutex vs гонка: %.1fx\n", t_mutex / t_race);
        printf("Замедление mutex vs батч:   %.1fx\n", t_mutex / t_batch);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "race") == 0) {
        return run_race_demo();
    }

    if (strcmp(argv[1], "volatile") == 0) {
        return run_volatile_demo();
    }

    if (strcmp(argv[1], "mutex") == 0) {
        int rc = run_mutex_demo();
        pthread_mutex_destroy(&counter_mutex);
        return rc;
    }

    if (strcmp(argv[1], "bench") == 0) {
        int rc = run_bench_demo();
        pthread_mutex_destroy(&counter_mutex);
        return rc;
    }

    print_usage(argv[0]);
    return 1;
}
