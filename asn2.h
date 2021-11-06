
#include <stdio.h>


struct processState {
	// not used in this program
	char* state;// stores a string like 'NEW'
};
typedef struct processState State;

struct processblock {
	int processId;
	int userId;          
	int arrivalTime;   // time units in simulation, not actual time
	int priority;          // base priority
	int expectedTimeRemaining;
	int expectedMemoryNeed;
	int expectedPctCPU;     // to get an idea of whether CPU bound or IO bound
	int realTime;

	State processState; // Not input - initially NEW
	int currentPriority;   // can be increased or lowered based on what has happened with the process - not input - initially same as base priority
	int timeWaitingSoFar;   // Not input - initially zero	
	int timeProcessingLastRun; // Not input - initially zero
	int timeProcessingSoFar; // Not input - initially zero
	struct processblock* nextPtr;
};
typedef struct processblock PCB;


// FUNCTIONS
int fetchPCB(PCB* pcb, FILE* input); //reads line from input file and fills a PCB
void searchDisplay(int priority, PCB* pcbs, int elements); //finds and displays all PCB's w/ a given priority
void displayPCB(PCB* pcb); //displays a PCB like so: ID:  3 Usr:  3 Arr:   0 pri:  1 Remain:  1 Mem:   17 CPU: 10
void displayPCBtable(PCB* pcb);//displays a PCB in a more table-like format
void displayPCBspace(PCB* pcb);//displays a PCB using only spaces

void fillPCB(PCB* pcb, int values[]) {// populates PCB allocated memory given an array
	pcb->processId = values[0];
	pcb->userId = values[1];
	pcb->arrivalTime = values[2];
	pcb->priority = values[3];
	pcb->expectedTimeRemaining = values[4];
	pcb->expectedMemoryNeed = values[5];
	pcb->expectedPctCPU = values[6];
	pcb->realTime = values[7];
	State newState;
	newState.state = "NEW";
	pcb->processState = newState; // Not input - initially NEW
	pcb->currentPriority = pcb->priority;   // can be increased or lowered based on what has happened with the process - not input - initially same as base priority
	pcb->timeWaitingSoFar = 0;   // Not input - initially zero	
	pcb->timeProcessingLastRun = 0; // Not input - initially zero
	pcb->timeProcessingSoFar = 0; // Not input - initially zero
	pcb->nextPtr = NULL;
}

