#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* maxHeap;
int* minHeap;
int maxSize;
int minSize;

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void maxHeapify(int* heap, int i, int n)
{
	int left = 2*i + 1;
	int right = 2*i + 2;
	int largest = i;

	if(left < n && heap[left] >= heap[largest])
		largest = left;

	if(right < n && heap[right] >= heap[largest])
		largest = right;

	if(largest != i)
	{
		swap(&heap[i], &heap[largest]);
		maxHeapify(heap, largest, n);
	}

}

void minHeapify(int* heap, int i, int n)
{
	int left = 2*i + 1;
	int right = 2*i + 2;
	int smallest = i;

	if(left < n && heap[left] < heap[smallest])
		smallest = left;

	if(right < n && heap[right] < heap[smallest])
		smallest = right;

	if(smallest != i)
	{
		swap(&heap[i], &heap[smallest]);
		minHeapify(heap, smallest, n);
	}
}

void insertMaxHeap(int value)
{
    int i;

	maxHeap[maxSize] = value;
	i = maxSize++;

	while(i != 0 && maxHeap[(i-1)/2] < maxHeap[i])
	{
		swap(&maxHeap[(i-1)/2], &maxHeap[i]);
		i = (i-1)/2;
	}

}

void insertMinHeap(int value)
{
	int i;

	minHeap[minSize++] = value;
	i = minSize-1;

	while(i > 0 && minHeap[(i-1)/2] > minHeap[i])
	{
		swap(&minHeap[(i-1)/2], &minHeap[i]);
		i = (i-1)/2;
	}

}


int extractMax()
{
    int max = maxHeap[0], i;

    maxHeap[0] = maxHeap[maxSize-1];
    maxSize--;
    maxHeapify(maxHeap, 0, maxSize);
    return max;
}

int extractMin()
{
	int min = minHeap[0], i;

   	minHeap[0] = minHeap[minSize-1];
    	--minSize;
	minHeapify(minHeap, 0, minSize);

    	return min;
}

double getMedian()
{
	if(maxSize != minSize)
	{
		if(maxSize > minSize)
            		return (double)(maxHeap[0]);
        	return (double)(minHeap[0]);
	}
	else
	{
        	return ((double)(minHeap[0] + maxHeap[0])/2.0);
	}
}

void balanceHeaps()
{
	if(maxSize - minSize > 1)
	{
		insertMinHeap(extractMax());
	}
	else if(minSize - maxSize > 1)
	{
		insertMaxHeap(extractMin());
	}

}

int main()
{
	int n, i, value;
	double median=0.0;

	scanf("%d", &n);

	maxHeap = (int*)malloc(((n/2)+1)*sizeof(int));
	minHeap = (int*)malloc(((n/2)+1)*sizeof(int));

	maxSize = 0;
	minSize = 0;

	scanf("%d", &value);

	median = (double)value;
    	insertMinHeap(value);
    	printf("%0.1f\n", median);

	for(i=1; i<n; i++)
	{
            	scanf("%d", &value);

		if(value > median)
			insertMinHeap(value);
		else
			insertMaxHeap(value);

            	if(maxSize - minSize >= 2 || minSize - maxSize >= 2)
                	balanceHeaps();

		median = getMedian();
		printf("%0.1f\n", median);

	}

	return 0;
}
