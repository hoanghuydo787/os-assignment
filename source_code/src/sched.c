
#include "queue.h"
#include "sched.h"
#include <pthread.h>

static struct queue_t ready_queue;
static struct queue_t run_queue;
static pthread_mutex_t queue_lock;

int queue_empty(void) {
	return (empty(&ready_queue) && empty(&run_queue));
}

void init_scheduler(void) {
	ready_queue.size = 0;
	run_queue.size = 0;
	pthread_mutex_init(&queue_lock, NULL);
}

struct pcb_t * get_proc(void) {
	struct pcb_t * proc = NULL;
	/*TODO: get a process from [ready_queue]. If ready queue
	 * is empty, push all processes in [run_queue] back to
	 * [ready_queue] and return the highest priority one.
	 * Remember to use lock to protect the queue.
	 * */
	if(!empty(&ready_queue)){
		pthread_mutex_lock(&queue_lock);
		proc = dequeue(&ready_queue);
		enqueue(&run_queue, proc);
		pthread_mutex_unlock(&queue_lock);
	}
	else{
		for(int i = 0; i < run_queue.size; i++){
			add_proc(run_queue.proc[i]);
		}
		pthread_mutex_lock(&queue_lock);
		proc = dequeue(&ready_queue);
		enqueue(&run_queue, proc);
		pthread_mutex_unlock(&queue_lock);
		for(int i = 0; i < run_queue.size; i++){
			pthread_mutex_lock(&queue_lock);
			proc = dequeue(&run_queue);
			pthread_mutex_unlock(&queue_lock);
		}
	}
	return proc;
}

void put_proc(struct pcb_t * proc) {
	pthread_mutex_lock(&queue_lock);
	enqueue(&run_queue, proc);
	pthread_mutex_unlock(&queue_lock);
}

void add_proc(struct pcb_t * proc) {
	pthread_mutex_lock(&queue_lock);
	enqueue(&ready_queue, proc);
	pthread_mutex_unlock(&queue_lock);	
}


