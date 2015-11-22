#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "Kentec320x240x16_ssd2119_8bit.h"

/**************************
YOSEMIT XOLALPA ROSALES
PROF. VENKI
CPE403
TIVAC-LAB10-C
**************************/
extern const uint8_t g_pui8Image[];
tContext sContext;
tRectangle sRect;

void ClrScreen(void);

int main(void)
{
   SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

   Kentec320x240x16_SSD2119Init();
   GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);
   ClrScreen();

   GrImageDraw(&sContext, g_pui8Image, 0, 0);
   GrFlush(&sContext);

   SysCtlDelay(SysCtlClockGet());
   // Later lab steps go between here

   ClrScreen();

   sRect.i16XMin = 1;
   sRect.i16YMin = 1;
   sRect.i16XMax = 318;
   sRect.i16YMax = 238;
   GrContextForegroundSet(&sContext, ClrRed);
   GrContextFontSet(&sContext, &g_sFontCmss30b);
   GrStringDraw(&sContext, "CPE403", -1, 110, 2, 0);
   GrStringDraw(&sContext, "LAB 10", -1, 80, 32, 0);
   GrStringDraw(&sContext, "GRAPHICS", -1, 100, 62, 0);
   GrStringDraw(&sContext, "LIBRARY", -1, 135, 92, 0);
   GrContextForegroundSet(&sContext, ClrWhite);
   GrRectDraw(&sContext, &sRect);
   GrFlush(&sContext);

   SysCtlDelay(SysCtlClockGet());

   // and here
   ClrScreen();
   while(1)
   {
   }
}

void ClrScreen()
{
   sRect.i16XMin = 0;
   sRect.i16YMin = 0;
   sRect.i16XMax = 319;
   sRect.i16YMax = 239;
   GrContextForegroundSet(&sContext, ClrBlack);
   GrRectFill(&sContext, &sRect);
   GrFlush(&sContext);
}
