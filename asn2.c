
#include <stdlib.h>
#include <assert.h>
#include "asn2.h"

int main()
{
	FILE* inputFile = fopen("allprocesses.txt", "r");//establishes input file
	int numInputs = 0;
	PCB* data;
	data = (PCB*) malloc( sizeof(PCB) * 600);// creates an array of size 600 PBC's in the heap
	assert(data != NULL);
	int inputedPri;

	for (int i = 0; i < 600 && (fetchPCB(&(data[i]), inputFile)); i++) {// loops over 600 iterations if needed
		numInputs = i;// increments numinputs with i
	}

	data = (PCB*) realloc(data, sizeof(PCB) * numInputs);// reallocates to make size of data array just what it needs to be
	assert(data != NULL);

	for (int i = 0; i < numInputs; i++) {// loops thru and displays all PBC's
		displayPCBtable(&(data[i]));
		printf("\n");
	}

	printf("Please enter a priority: ");
	scanf("%d", &inputedPri);// gets priority to search for and display

	searchDisplay(inputedPri, data, numInputs);

	free(data);// deallocates memory used to store the PCB's

	getchar();
	return 0;
}

int fetchPCB(PCB* pcb, FILE* input) //reads line from input file and fills a PCB
{
	//loop thru delimiter is value -16, after 8 values collected, done -- This should be rewritten to parse line by line.
	int values[8];
	int currentVal = 0, currentIndex = 0, inputVal = fgetc(input) - 48;
	if (inputVal == -49)
		return 0;
	while (inputVal != -49) {
		if (inputVal >= 0) {
			currentVal *= 10;
			currentVal += inputVal;
			values[currentIndex] = currentVal;
			inputVal = fgetc(input) - 48;
		}
		else if (inputVal == -35) {
			fgetc(input);// advance the point of reading doc to the -38 val
			break;
		}
		else if (inputVal == -16) {
			currentIndex++;
			currentVal = 0;
			inputVal = fgetc(input) - 48;
			continue;
		}
	}
	fillPCB(pcb, values); // popultes the PCB data structure given the array and reference, found in "asn2.h"
	return 1;
}

void searchDisplay(int priority, PCB* pcbs, int elements) //finds and displays all PCB's w/ a given priority
{
	int numMatches = 0;
	for (int i = 0; i < elements; i++) {
		if (pcbs[i].priority == priority) {
			displayPCBtable(&pcbs[i]);
			numMatches++;
			printf("\n");
		}
	}
	printf("%d processes with priority %d\n", numMatches, priority);
}

void displayPCBtable(PCB* pcb) //displays a PCB in a more table-like format
{
	printf("ID:\t%d\tUsr:\t%d\tArr:\t%d\tpri:\t%d\tRemain:\t%d\tMem:\t%d\tCPU:\t%d", 
		pcb->processId, pcb->userId, pcb->arrivalTime, pcb->priority, 
		pcb->expectedTimeRemaining, pcb->expectedMemoryNeed, pcb->expectedPctCPU);
}
void displayPCB(PCB* pcb) //displays a PCB like so: ID:  3 Usr:  3 Arr:   0 pri:  1 Remain:  1 Mem:   17 CPU: 10
{
	printf("ID:\t%d Usr:\t%d Arr:\t%d pri:\t%d Remain:\t%d Mem:\t%d CPU:\t%d", 
		pcb->processId, pcb->userId, pcb->arrivalTime, pcb->priority, 
		pcb->expectedTimeRemaining, pcb->expectedMemoryNeed, pcb->expectedPctCPU);
}
void displayPCBspace(PCB* pcb)// displays a PCB using only spaces
{
	printf("ID: %d Usr: %d Arr: %d pri: %d Remain: %d Mem: %d CPU: %d", 
		pcb->processId, pcb->userId, pcb->arrivalTime, pcb->priority, 
		pcb->expectedTimeRemaining, pcb->expectedMemoryNeed, pcb->expectedPctCPU);
}