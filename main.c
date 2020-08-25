/* --------0.Project information--------------------
 * SSI MICROWIRE COMMUNICATION TM4C123G
 * Author : TRAN MINH THUAN
 * -------------------------------------------------*/

/* --------1.System requirement--------------------
 * Create a simple SSI communication system
 * Master-Slave
 * -------------------------------------------------*/

/* --------2.Pre-processor Directives Section-------------------*/
//Add libraries
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_nvic.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"

#include "driverlib/ssi.c"
#include "driverlib/sysctl.c"

uint32_t Data_recv=0;
/*--------------------------\\//------------------------------- */
/*-------------------------Define value------------------------*/
void SSI0_Init(void);
void GPIOF_Init(void);
void main(void)
{
    SSI0_Init();
    GPIOF_Init();
	while(true)
	{
	    while(SSIBusy(SSI0_BASE));              //Stay inside while still
	    SSIDataGet(SSI0_BASE, &Data_recv);
	    if(Data_recv==0) GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	    else             GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
	}
}
void SSI0_Init(void){
    //Enable peripheral (Change SSI base and GPIO base in order to use another SSI)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);         //Enable the SSI0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);        //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0));  //Wait for the SSI0 module to be ready
    //Pin configure for SSI0 (Change CLK,FSS,TX,RX)
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);                 //PA2 CLK
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);                 //PA3 FSS
    GPIOPinConfigure(GPIO_PA5_SSI0TX);                  //PA5 TX
    GPIOPinConfigure(GPIO_PA4_SSI0RX);                  //PA4 RX
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);
    //Configure for SSI0
    //Clock=2 000 000, 8bit data, slave
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,SSI_MODE_SLAVE, 2000000, 8);
    SSIEnable(SSI0_BASE);
}
void GPIOF_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); //LED RED
}
