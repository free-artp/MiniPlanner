/*
  MiniPlanner.h - Simple library for Arduino.
  Handles sceduling of the user functions
  Copyleft (c) 2012 Peter Artamonov.
  Mailto: Peter.Artamonov at gmail.com

  This library is totally free software; you can do anything with it.
*/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef MINI_PLANNER_h

#define MINI_PLANNER_h
#define MINI_PLANNER_V 100

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

//-------------------------- Planner desc.
#define MAX_PROCS 10

#define FLAG_PERIODIC 0
#define FLAG_ONCE 1

class Proc {
  public:
    unsigned long at;
    long period;
    int flags;
    void (*proc)();
};

class Planner {
  public:
    Planner();
    void cycle();
    void schedule(long time, int flags, void (*proc)() );
    void debug();
    void unschedule( void (*proc)() );
  protected:
    Proc _procs[MAX_PROCS];
};

#endif	// MINI_PLANNER_H
