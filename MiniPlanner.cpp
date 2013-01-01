/*
  MiniPlanner.h - Simple library for Arduino.
  Handles sceduling of the user functions
  Copyleft (c) 2012 Peter Artamonov.
  Mailto: Peter.Artamonov at gmail.com

  This library is totally free software; you can do anything with it.
*/

#include "MiniPlanner.h"

//------------------------- Planner code

Planner::Planner() {
  for (int i=0; i<MAX_PROCS; i++) {
    _procs[i].at = 0;
    _procs[i].flags = 0;
  }
}

void Planner::cycle() {
  unsigned long now;
  now = millis();
  
  for ( int slot=0; slot < MAX_PROCS; slot++) {
    if ( (_procs[slot].at >0) && (_procs[slot].at <= now) ) {
      if (_procs[slot].flags & FLAG_ONCE) {
        _procs[slot].at = 0;
      } else {
        _procs[slot].at = now + _procs[slot].period;
      }
      (*_procs[slot].proc)();
    }
  }
}

void Planner::schedule( long time, int flags, void (*proc)() ) {
  int slot;
  unsigned long now = millis();
  
  for( slot=0; slot<MAX_PROCS; slot++) {
    if (_procs[slot].at == 0) {
      if (flags & FLAG_ONCE) {
        _procs[slot].period = 0;
      } else {
        _procs[slot].period = time;
      }
      _procs[slot].at = now + time;
      _procs[slot].flags = flags;
      _procs[slot].proc = proc;
      return;
    }
  }
}

void Planner::unschedule( void (*proc)() ) {
  for ( int slot=0; slot < MAX_PROCS; slot++) {
    if ( (_procs[slot].at >0) && _procs[slot].proc == proc) {
        _procs[slot].at = 0;
    }
  }
}

void Planner::debug() {
  unsigned long now;
  now = millis();
  Serial.print("Now:"); Serial.println(now);
  for (int slot =0; slot < MAX_PROCS; slot++) {
    if (_procs[slot].at > 0) {
      Serial.print("Slot:"); Serial.print(slot); Serial.print(" at:"); Serial.println(_procs[slot].at);
    }
  }
}

