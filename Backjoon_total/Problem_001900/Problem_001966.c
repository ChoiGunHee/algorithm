/**
* 2021. 06. 08
* Creater : Gunhee Choi
* Problem Number : 1966
* Title : 프린터 큐

* Problem :
여러분도 알다시피 여러분의 프린터 기기는 여러분이 인쇄하고자 하는 문서를 인쇄 명령을 받은 ‘순서대로’, 즉 먼저 요청된 것을 먼저 인쇄한다. 여러 개의 문서가 쌓인다면 Queue 자료구조에 쌓여서 FIFO - First In First Out - 에 따라 인쇄가 되게 된다. 하지만 상근이는 새로운 프린터기 내부 소프트웨어를 개발하였는데, 이 프린터기는 다음과 같은 조건에 따라 인쇄를 하게 된다.

현재 Queue의 가장 앞에 있는 문서의 ‘중요도’를 확인한다.
나머지 문서들 중 현재 문서보다 중요도가 높은 문서가 하나라도 있다면, 이 문서를 인쇄하지 않고 Queue의 가장 뒤에 재배치 한다. 그렇지 않다면 바로 인쇄를 한다.
예를 들어 Queue에 4개의 문서(A B C D)가 있고, 중요도가 2 1 4 3 라면 C를 인쇄하고, 다음으로 D를 인쇄하고 A, B를 인쇄하게 된다.

여러분이 할 일은, 현재 Queue에 있는 문서의 수와 중요도가 주어졌을 때, 어떤 한 문서가 몇 번째로 인쇄되는지 알아내는 것이다. 예를 들어 위의 예에서 C문서는 1번째로, A문서는 3번째로 인쇄되게 된다.

* Input :
첫 줄에 테스트케이스의 수가 주어진다. 각 테스트케이스는 두 줄로 이루어져 있다.

테스트케이스의 첫 번째 줄에는 문서의 개수 N(1 ≤ N ≤ 100)과, 몇 번째로 인쇄되었는지 궁금한 문서가 현재 Queue에서 몇 번째에 놓여 있는지를 나타내는 정수 M(0 ≤ M < N)이 주어진다. 이때 맨 왼쪽은 0번째라고 하자. 두 번째 줄에는 N개 문서의 중요도가 차례대로 주어진다. 중요도는 1 이상 9 이하의 정수이고, 중요도가 같은 문서가 여러 개 있을 수도 있다.

	3
	1 0
	5
	4 2
	1 2 3 4
	6 0
	1 1 9 1 1 1

* Output :
각 테스트 케이스에 대해 문서가 몇 번째로 인쇄되는지 출력한다.

	1
	2
	5

**/

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 101
#define MAX_QUEUE_SIZE 200
#define MAX_STRING 100

typedef struct {
	int key;
	int index;
} element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
	int size;
} QueueType;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType * create() {
	return (HeapType * ) malloc(sizeof(HeapType));
}

void init(HeapType * h) {
	int i;
	h->heap_size = 0;
	for(i=0; i<MAX_ELEMENT; i++) {
		h->heap[i].key = 0;
		h->heap[i].index = 0;
	}
}

void insert_max_heap(HeapType * h, element item) {
	int i;
	i = ++(h->heap_size);

	while( (i != 1) && (item.key > h->heap[i/2].key) ) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType * h) {
	int parent, child;
	element item, temp;
	
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	
	while(child <= h->heap_size) {
		if( (child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		
		if(temp.key >= h->heap[child].key) break;
		
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	
	h->heap[parent] = temp;
	return item;
}


//Queue
void init_queue(QueueType * queue) {
	queue->rear = -1;
	queue->front = -1;
	queue->size = 0;
}

int is_full(QueueType * queue) {
	if(queue->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	
	return 0;
}

int is_empty(QueueType * queue) {
	if(queue->front == queue->rear)
		return 1;
	
	return 0;
}

int enqueue(QueueType * queue, element data) {
	if( is_full(queue) ) return -1;
	
	queue->size++;
	queue->data[++(queue->rear)].key = data.key;
	queue->data[++(queue->rear)].index = data.index;
	return 0;
}

element dequeue(QueueType * queue) {
	element data;
	
	if( is_empty(queue) ) {
		return data;
	}
	
	queue->size--;
	data.key = queue->data[++(queue->front)].key;
	data.index = queue->data[++(queue->front)].index;
	return data;
}

void print_queue(QueueType * queue) {
	int i;
	
	for(i=queue->front+1; i<queue->rear+1; i++) {
		printf("%d\n", queue->data[i].key);
	}
}

int get_size(QueueType * queue) {
	return queue->size;
}

int main(void) {
	int T;
	int N, M;
	int i, j;
	int temp;
	element t_e;
	element t_e2;
	element goal_e;
	int count;
	
	HeapType * heap;
	QueueType q;
	
	init(heap);
	init_queue(&q);
	
	scanf("%d", &T);
	
	for(i=0; i<T; i++) {
		scanf("%d %d", &N, &M);
		for(j=0; j<N; j++) {
			scanf("%d", &temp);
			t_e.key = temp;
			t_e.index = j;
			insert_max_heap(heap, t_e);
			
			enqueue(&q, t_e);
			
			if(j == M) {
				goal_e.key = temp;
				goal_e.index = j;
			}
		}
		
		count = 0;
		
		while( N != 0 ) {
			t_e = delete_max_heap(heap);
			
			while(1) {
				t_e2 = dequeue(&q);
				count++;
				if(t_e.key == t_e2.key && t_e.index == t_e2.index)
					break;
				
				enqueue(&q, t_e2);
			}
			
			
			N--;
		}
		
		printf("%d\n", count);
	}
	
	free(heap);
	
	return 0;
}