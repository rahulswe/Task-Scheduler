/*
* File Name: priority_queue.c
* Description: Source file of a priority queue implementation using heap max with struct elements
* Author: Rahul Singh
*/

#include <stddef.h>
#include "priority_queue.h"

/////////////////////////////////////////////////////////
/* utility functions for heap */
/////////////////////////////////////////////////////////

/* function to swap the content of two variables */
void swap(pq_item_t *a, pq_item_t *b) {
    pq_item_t temp = *a;
    *a = *b;
    *b = temp;
}

/* function to heapfy down */
void pq_heapify_down(priority_queue_t *pq, uint32_t index) {
    if(pq == NULL) {
        return;
    }

    uint32_t p_idx = index; //parent node index
    uint32_t l_idx, r_idx, s_idx;//left child / right child / child with largest value index

    while(p_idx < pq->size) {
        l_idx = 2 * p_idx + 1;
        r_idx = 2 * p_idx + 2;
        s_idx = p_idx;
        
        /* find the child with largest value */
        if((l_idx < pq->size) && (pq->items[l_idx].priority > pq->items[s_idx].priority)) {
            s_idx = l_idx;
        }
        
        if((r_idx < pq->size) && (pq->items[r_idx].priority > pq->items[s_idx].priority)) {
            s_idx = r_idx;
        } 
        
        /* if largest is not the parent, swap and continue heapifying down */
        if(s_idx != p_idx) {
            swap(&(pq->items[s_idx]), &(pq->items[p_idx]));
            p_idx = s_idx;
        }
        else {
            /* if no swap occurred, heap property is maintained */
            return;
        }
    }
}

/* function to heapfy up */
void pq_heapify_up(priority_queue_t *pq, uint32_t index) {
    /* check the validity of the arguments */
    if(pq == NULL) {
        return;
    }
    
        
    /* ensure the condition of heap max is satisfied
    from index position to updwards till root */
    
    while(index > 0) {
        uint32_t p_idx = (index - 1)/2;
        if(pq->items[p_idx].priority < pq->items[index].priority) {
            swap(&(pq->items[p_idx]), &(pq->items[index]));
            index = p_idx;
        } else {
            return;
        }
    }
}

/////////////////////////////////////////////////////////

/* function to enqueue data to the priority queue */
void pq_enqueue(priority_queue_t *pq, pq_item_t data) {
    /* check the validity of the arguments */
    if(pq == NULL) {
        return;
    }
    
    /* check if pq is full and return if so */
    if(pq->size == MAX_QUEUE_SIZE) {
        return;
    }
    
    /* insert the data in the pq */
    pq->items[pq->size].task_id = data.task_id;
    pq->items[(pq->size)++].priority = data.priority;
    
    /* restore heap property */
    pq_heapify_up(pq, pq->size - 1);
    
    return;
}

/* function to dequeue data from the priority queue */
pq_item_t pq_dequeue(priority_queue_t *pq) {
    pq_item_t data = {0xFF, 0xFF};
    /* check the validity of the arguments */
    if(pq == NULL) {
        return data;
    }
    
    /* check if pq is empty and return if so */
    if(pq->size == 0) {
        return data;
    }
    
    /* get the data to be dequeued i.e. at the root */
    data = pq->items[0];
    
    /* restore the heap property */
    pq->items[0] = pq->items[--(pq->size)];
    pq_heapify_down(pq, 0);
    
    return data;
}

/* function to peek data in the priority queue */
pq_item_t pq_peek(priority_queue_t *pq) {
    pq_item_t data = {0xFF, 0xFF};
    /* check the validity of the arguments */
    if(pq == NULL) {
        return data;
    }
    
    /* check if pq is empty and return if so */
    if(pq->size == 0) {
        return data;
    }
    
    /* return the data at the root */
    data = pq->items[0];
    return data;
}
