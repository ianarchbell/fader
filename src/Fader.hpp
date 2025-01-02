/*
 * Fader.hpp
 *
 */

#ifndef FADER_H_
#define FADER_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "Task.hpp"


class Fader: public Task {
public:
	/***
	 * Constructor
	 */
	Fader(const char * taskName, uint32_t ledPin = 16, uint32_t delay = 500, uint32_t stackSize = 1024, uint8_t priority = TaskPrio_Low) : Task(taskName, stackSize, priority){
		m_ledPin = ledPin;
		m_delay = delay;
	};

	/***
	 * Destructor
	 */
	virtual ~Fader();


protected:

	/***
	 * Run loop for the agent.
	 */
	void run (void *data);

	void fade(int target_duty_cycle, int fade_speed_ms);
	void set_pwm_pin(uint freq, uint duty_c); 

	uint32_t m_ledPin;
	uint32_t m_duty_cycle = 0;
    uint32_t m_slice_num;
	uint32_t m_delay;

};


#endif /* BLINK_H_ */
