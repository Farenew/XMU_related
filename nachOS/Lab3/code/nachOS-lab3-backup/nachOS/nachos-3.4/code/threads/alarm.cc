// alarm.cc
// implementation for alarm.h
// 
// By ForenewHan at 2018.6.13

#include "alarm.h"
#include "stats.h"
#include "thread.h"
#include "interrupt.h"


int Alarm::waitingTime = 0;
int Alarm::waitingNum = 0;
Lock* Alarm::lock = new Lock("alarm lock");
List* Alarm::waitQueue = new List;

Alarm::Alarm(){
	waitingTime = 0;
	waitingNum = 0;
	timer = new Timer(Wake, 0, 0);
}

Alarm::~Alarm(){
	delete timer;
	delete lock;
	delete waitQueue;
}


void Alarm::Pause(int timePeriod){
	waitingTime = timePeriod;

	if(waitingTime >= 0){
		waitingNum++;
		lock->Acquire();		// enforce mutual exclusive access to the list 
		waitQueue->Append((void *)currentThread);   // so go to sleep
	    lock->Release();

	    IntStatus oldLevel = interrupt->SetLevel(IntOff);   // disable interrupts
	    currentThread->Sleep();             // if we want to make thread sleep, we have to disable ints
	    (void) interrupt->SetLevel(oldLevel);   // re-enable interrupts
	}

	printf("Pause %d Finished\n", timePeriod);
}

void Alarm::Wake(int dummy){

	//printf("\n-----my waiting------\n");

	extern Interrupt *interrupt;			// interrupt status

    waitingTime -= TimerTicks;
    printf("\n----time goes by %d-----\n", TimerTicks);
    if(waitingTime >= 0){
        printf("----keep waiting-----\n");
    }
    else{
    	if(waitingNum>0){
    		Thread* threadtoRun = (Thread*)waitQueue->Remove();
        	scheduler->ReadyToRun(threadtoRun);
        	waitingTime = 0;
        	waitingNum--;
        	printf("-----sleeping thread is waken-------");
    	}
    }

    
}