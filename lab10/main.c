#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"
#include "Kentec320x240x16_ssd2119_8bit.h"
#include "touch.h"

/**************************
YOSEMIT XOLALPA ROSALES
PROF. VENKI
CPE403
TIVAC-LAB10-partE
**************************/
extern tCanvasWidget g_sBackground;
extern tPushButtonWidget g_sPushBtn;

void OnButtonPress(tWidget *pWidget);

Canvas(g_sHeading, &g_sBackground, 0, &g_sPushBtn,
       &g_sKentec320x240x16_SSD2119, 0, 0, 320, 23,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT),
       ClrBlack, ClrWhite, ClrRed, g_psFontCm20, "LED Control", 0, 0);

Canvas(g_sBackground, WIDGET_ROOT, 0, &g_sHeading,
       &g_sKentec320x240x16_SSD2119, 0, 23, 320, (240 - 23),
       CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0);

RectangularButton(g_sPushBtn, &g_sHeading, 0, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 60, 200, 40,
                  (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                   PB_STYLE_FILL), ClrGray, ClrWhite, ClrRed, ClrRed,
                   g_psFontCmss22b, "Toggle red LED", 0, 0, 0, 0, OnButtonPress);

bool g_RedLedOn = false;

void OnButtonPress(tWidget *pWidget)
{
    g_RedLedOn = !g_RedLedOn;

    if(g_RedLedOn)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }
}
int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);

    Kentec320x240x16_SSD2119Init();

    TouchScreenInit();

    TouchScreenCallbackSet(WidgetPointerMessage);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);

    WidgetPaint(WIDGET_ROOT);

    while(1)
    {
        WidgetMessageQueueProcess();
    }
}
