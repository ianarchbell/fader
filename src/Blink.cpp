

#include "Blink.hpp"

#include "stdio.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
	#include "pico/cyw43_arch.h"
#endif

/***
 * Constructor in hpp
 */


/***
 * Destructor
 */
Blink::~Blink() {
	stop();
}


 /***
  * Main Run Task for agent
  */
 void Blink::run(void *data){

	printf("Blink Instance Started\n");

	static bool initialized=false;

	if (!initialized){
	// Perform initialisation
		#if defined(PICO_DEFAULT_LED_PIN)
			// A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
			// so we can use normal GPIO functionality to turn the led on and off
			gpio_init(PICO_DEFAULT_LED_PIN);
			gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
			return PICO_OK;
		#elif defined(CYW43_WL_GPIO_LED_PIN)
			// For Pico W devices we need to initialise the driver etc
			cyw43_arch_init();
		#endif
		initialized=true;
	}

	int led_on = 1;
	while (true) { // Loop forever
		#if defined(PICO_DEFAULT_LED_PIN)
			// Just set the GPIO on or off
			gpio_put(PICO_DEFAULT_LED_PIN, led_on);
		#elif defined(CYW43_WL_GPIO_LED_PIN)
			// Ask the wifi "driver" to set the GPIO on or off
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
		#endif
			vTaskDelay(m_delay);
			led_on = !led_on;
	}

 }
