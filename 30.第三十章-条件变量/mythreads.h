#ifndef __MYTHREADS_h__
#define __MYTHREADS_h__

#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>

void *Malloc(size_t size) {
    void *p = malloc(size);
    assert(p != NULL);
    return p;
}

double Time_GetSeconds() {
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

void work(int seconds) {
    double t0 = Time_GetSeconds();
    while ((Time_GetSeconds() - t0) < (double)seconds)
	;
}

void Mutex_init(pthread_mutex_t *m) {
    assert(pthread_mutex_init(m, NULL) == 0);
}

void Mutex_lock(pthread_mutex_t *m) {
    int rc = pthread_mutex_lock(m);
    assert(rc == 0);
}

void Mutex_unlock(pthread_mutex_t *m) {
    int rc = pthread_mutex_unlock(m);
    assert(rc == 0);
}

void Cond_init(pthread_cond_t *c) {
    assert(pthread_cond_init(c, NULL) == 0);
}

void Cond_wait(pthread_cond_t *c, pthread_mutex_t *m) {
    int rc = pthread_cond_wait(c, m);
    assert(rc == 0);
}

void Cond_signal(pthread_cond_t *c) {
    int rc = pthread_cond_signal(c);
    assert(rc == 0);
}


void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, 	
		    void *(*start_routine)(void*), void *arg) {
    int rc = pthread_create(thread, attr, start_routine, arg);
    assert(rc == 0);
}

void Pthread_join(pthread_t thread, void **value_ptr) {
    int rc = pthread_join(thread, value_ptr);
    assert(rc == 0);
}


#endif // __MYTHREADS_h__
