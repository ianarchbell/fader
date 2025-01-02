/*
 * BlinkAgent.h
 *
 * Active agent to run as task and blink and LED on the given GPIO pad
 *
 *  Created on: 15 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINK_H_
#define BLINK_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "Task.hpp"


class Blink: public Task {
public:
	/***
	 * Constructor
	 */
	Blink(const char * taskName, uint32_t delay = 1000, uint32_t stackSize = 1024, uint8_t priority = TaskPrio_Low) : Task(taskName, stackSize, priority){
		m_delay = delay;
	};
	/***
	 * Destructor
	 */
	virtual ~Blink();


protected:

	/***
	 * Run loop for the agent.
	 */
	void run (void *data);

	uint32_t m_delay;

};


#endif /* BLINK_H_ */
