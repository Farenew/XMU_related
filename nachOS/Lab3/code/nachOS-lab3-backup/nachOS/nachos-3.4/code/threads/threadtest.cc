#include "copyright.h"
#include "system.h"
#include "EventBarrier.h"
#include "alarm.h"

// testnum is set in main.cc
int testnum = 1;

void AlarmTest(int arg){
    extern Alarm* alarm;
    printf("----this is AlarmTest with ID %d\n",arg);
    printf("----AlarmTest pause for 50 time\n");
    alarm->Pause(200);
    currentThread->Yield();
}

void loopFunction(int arg){
    printf("----this is LoopFunction with ID %d\n\n",arg);
    currentThread->Yield();
    int time = 1000;
    while(time > 0){
        time = time - 50;
        printf("thread exchange\n");
        currentThread->Yield();
    }

}


void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    //Alarm alm;
    // create two thread, to make result cleaner.
    Thread *t1 = new Thread("Thread 1");
    Thread *t2 = new Thread("Thread 2");
    //Thread *t3 = new Thread("signal thread 3");

    t1->Fork(AlarmTest, 1);
    t2->Fork(loopFunction, 2);
    //t3->Fork(eventWake, 3);

    loopFunction(0);
}

//----------------------------------------------------------------------
// ThreadTest
//  Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
    ThreadTest1();
    break;

    default:
    printf("No test specified.\n");
    break;
    }
}