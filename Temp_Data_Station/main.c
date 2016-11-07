#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/**************************
YOSEMIT XOLALPA ROSALES
PROF. VENKI
CPE403
TIVAC-LAB03
 **************************/

uint8_t ui8PinData=2;	//pins 8+4+2=14 meaning all three LEDs will light

int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
/*** TASK 6: While() Loop ***/
	while(1)
	{
/*** TASK 21: changing code to original set-up ***/
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);			//ui8PinData references the entire 8-bit
								//data port: ports 1, 2, and 3.
								
		SysCtlDelay(8000000);	//loop timer where count parameter
								//is the loop count (not actual delay
								//in clock cycles).
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
		SysCtlDelay(8000000);
		
		//cycle through LEDs: 2, 4, 8, 2, 4,...
		if(ui8PinData==8) {ui8PinData=2;} else {ui8PinData=ui8PinData*2;}
	}
}
