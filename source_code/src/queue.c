#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */	
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if(!q) return NULL;
	uint32_t priMax = q[0]->priority;
	int ind = 0;
	for(int i = 1; i < q->size; i++){
		if(q[i]->priority > priMax){
			priMax = q[i]->priority;
			ind = i;
		}
	}
	pcb_t res = q[ind];
	free(q[ind]);
	q[ind] = NULL;
	return res;
	//return NULL;
}

