

#include "Fader.hpp"

#include "stdio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

/***
 * Constructor in hpp
 */


/***
 * Destructor
 */
Fader::~Fader() {
	stop();
}


// Fade the LED up or down over time
void Fader::fade(int target_duty_cycle, int fade_speed_ms) {
	int step = (target_duty_cycle > m_duty_cycle) ? 1 : -1;
	printf("Fading led pin %i\n", m_ledPin);
	while (m_duty_cycle != target_duty_cycle) {
		m_duty_cycle += step;
		pwm_set_gpio_level(m_ledPin, m_duty_cycle);
		vTaskDelay(pdMS_TO_TICKS(fade_speed_ms));
	}
}

void Fader::set_pwm_pin(uint freq, uint duty_c) { // duty_c between 0..10000

	gpio_set_function(m_ledPin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(m_ledPin);
	uint chan = pwm_gpio_to_channel(m_ledPin);
	float div = (float)clock_get_hz(clk_sys) / (freq * 10000);
	pwm_config config = pwm_get_default_config();
	pwm_config_set_clkdiv(&config, div);
	pwm_config_set_wrap(&config, freq); 
	pwm_init(slice_num, &config, true); // start the pwm running according to the config
	pwm_set_gpio_level(m_ledPin, duty_c); //connect the pin to the pwm engine and set the on/off level. 
	pwm_set_enabled	(slice_num, true);	
	printf("Set up LED pin %i", m_ledPin);
};

 /***
  * Main Run Task for agent
  */
 void Fader::run(void *data){

	printf("Fader Instance Started\n");

	static bool initialized=false;

	// Perform initialisation

	set_pwm_pin(255, 0); // level is set later
	// Start with LED off
	pwm_set_gpio_level(m_ledPin, 0);

	printf("Initialized Fader on pin %i\n", m_ledPin);

	while (true) { // Loop forever
		fade(255, 10); // Fade to full brightness
		vTaskDelay(pdMS_TO_TICKS(1000));
		fade(0, 10);   // Fade to off
	}

 }
