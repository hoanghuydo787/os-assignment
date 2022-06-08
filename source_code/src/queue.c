#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */
	//check if queue is full
	if (q->size < MAX_QUEUE_SIZE)
	{
		q->proc[q->size] = proc;
		q->size++;
	}
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if(empty(q)) return NULL;
	uint32_t priMax = q->proc[0]->priority;
	int ind = 0;
	for(int i = 1; i < q->size; i++){
		if(q->proc[i]->priority > priMax){
			priMax = q->proc[i]->priority;
			ind = i;
		}
	}
	pcb_t res = q->proc[ind];
	for(int i = ind; i < q->size; i++){
		if(i == q->size - 1){
			q->proc[i] = NULL;
			break;
		}
		q->proc[i] = q->proc[i+1];
	}
	q->size--;
	return res;
	//return NULL;
}

