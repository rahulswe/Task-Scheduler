/*
* File Name: priority_queue.h
* Description: Header file of a priority queue implementation using heap max with struct elements
* Author: Rahul Singh
*/

#include <stdint.h>

#define MAX_QUEUE_SIZE (10U)

typedef struct {
    uint8_t task_id;
    uint8_t priority;
} pq_item_t;

/* priority queue instance structure */
typedef struct {
    pq_item_t items[MAX_QUEUE_SIZE];
    uint32_t size;
} priority_queue_t;

/* function to enqueue data to the priority queue */
void pq_enqueue(priority_queue_t *pq, pq_item_t data);
/* function to dequeue data from the priority queue */
pq_item_t pq_dequeue(priority_queue_t *pq);
/* function to peek data in the priority queue */
pq_item_t pq_peek(priority_queue_t *pq);
