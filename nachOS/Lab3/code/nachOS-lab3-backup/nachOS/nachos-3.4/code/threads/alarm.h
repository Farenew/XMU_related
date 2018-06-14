// alarm.h
// 
// using alarm to achieve time just, we could put a thread to sleep 
// or wake it up at some certain point.
//
// contain two functions: 
// 1. alarm::Pause(int timePeriod), to sleep for a timePeriod
// 2. alarm::Wake(int dummy), used as IRQ inside timer object, to 
//    wake up those thread that have slept enough.
// 
// By ForenewHan at 2018.6.13

#ifndef ALARM_H
#define ALARM_H

#include "timer.h"
#include "synch.h"
#include "list.h"
#include "system.h"

class Alarm{
public:
	Alarm();
	~Alarm();

	void Pause(int timePeriod);

	// Wake function as VoidFunctionPtr to pass into timer
	// make it as friend function, it is actually declared in system.h
	// since we want to use variable interrupt.
	static void Wake(int dummy);

  private:
  	Timer *timer;


  	static int waitingNum;
  	static int waitingTime;
  	static Lock* lock;
  	static List* waitQueue;
};



#endif

