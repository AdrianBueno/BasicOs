#include <Heap.h>
#include <stdlib.h>

// Implements the insertion operation in a binary heap. IMPORTANT: does not increment the number of elements
// Parameters are:
//    info: PID to be inserted
//    heap: the corresponding queue: user, system or sleeping
//    queueType: if sleeping queue, QUEUE_WAKEUP; if ready queue, QUEUE_PRIORITY; if arrival, QUEUE_ARRIVAL
//    numElem: number of current elements inside the queue
//    limit: maximum capacity of the queue
// Returns: 0, if everything went ok (when returning, the number of elements must be incremented)

int Heap_add(int info, int heap[], int queueType, int numElem, int limit) {
	if (numElem >= limit || info<0)
		return -1;
	heap[numElem]=info;
	Heap_cribaAscendente(numElem, heap, queueType);
	return 0;
}

// Implements the extraction operation (the element with the highest priority). IMPORTANT: does not decrement the number of elements
// Parameters are:
//    heap: the corresponding queue: user, system or sleeping
//    queueType: if sleeping queue, QUEUE_WAKEUP; if ready queue, QUEUE_PRIORITY; if arrival, QUEUE_ARRIVAL
//    numElem: number of current elements inside the queue
// Returns: the PID with the highest priority in the queue, if everything went ok (when returning, the number of elements must be incremented)

int Heap_poll(int heap[], int queueType, int numElem) {
	int info = heap[0];
	if (numElem==0)
		return -1; // There are no elements in the queue
	else {
		heap[0]=heap[numElem-1];
		Heap_cribaDescendente(0, heap, queueType, numElem);
	}
	return info;		
}

// Auxiliary function
void Heap_cribaAscendente(int p, int heap[], int queueType) {
	if (p > 0)  {// if not in the root
		int padre = abs(p - 1) / 2; // integer division
		if (Heap_compare(heap[p],heap[padre],queueType)>0) { // Is less than his father ...
			int aux = heap[padre]; 
			heap[padre] = heap[p];
			heap[p] = aux;
			Heap_cribaAscendente(padre, heap, queueType);
		} // if not less, swap
	}// if at the root, finish
}

// Auxiliary function
void Heap_cribaDescendente(int p, int heap[], int queueType, int numElem) {
	int izq = 2*p+1;
	int der = 2*p+2;
	int aux = heap[p];
	
	if (der < numElem) // it has 2 children
		if ((Heap_compare(heap[izq],heap[der], queueType)>0) && (Heap_compare(heap[p],heap[izq],queueType)<0)){ // Swap with the left one if it is less/greater
			heap[p] = heap[izq];
			heap[izq] = aux;
			Heap_cribaDescendente(izq, heap, queueType, numElem);
		} else {
			if (Heap_compare(heap[p],heap[der], queueType)<0) { // swap with the right one if it is greater
				heap[p] = heap[der];
				heap[der] = aux;
				Heap_cribaDescendente(der, heap, queueType, numElem);
			}
		}
	else if (izq<numElem) { // it only has left child
		if (Heap_compare(heap[p],heap[izq], queueType)<0){ // swap with the left one if it is greater
			heap[p] = heap[izq];
			heap[izq] = aux;
			Heap_cribaDescendente(izq, heap, queueType, numElem);
		} // If it is less than its unique left child, do not swap
	} // if it is a leaf node, finish
}

// Auxiliary function to make comparisons
int Heap_compare(int uno, int dos, int queueType) {
  if (queueType==QUEUE_PRIORITY)
    return Heap_compare_priority(uno, dos);
  else if (queueType==QUEUE_WAKEUP) 
    return Heap_compare_wakeup(uno, dos);
  else // QUEUE_ARRIVAL
	return Heap_compare_arrival(uno, dos);
  
}

// Auxiliary function to compare priorities
int Heap_compare_priority(int uno, int dos) {
  return processTable[dos].priority-processTable[uno].priority;
}

// Auxiliary function to compare wake up times
int Heap_compare_wakeup(int uno, int dos) {
  return processTable[dos].whenToWakeUp - processTable[uno].whenToWakeUp;
}

// Auxiliary function to compare arrival times
int Heap_compare_arrival(int uno, int dos) {
  return userProgramsList[dos]->arrivalTime - userProgramsList[uno]->arrivalTime;
}



