/*
 * File: main.c
 * Target: TMS320F28379D
 * Purpose: Receive RS422 distance data from Micro-Epsilon optoNCDT sensor via UART (SCIA)
 */

#include "F28x_Project.h"
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

static char rxBuffer[BUFFER_SIZE];
static Uint16 bufferIndex = 0;
volatile float distance = 0.0f;

static void initSCIA(void);
static void initGPIO(void);
__interrupt void sciaRxISR(void);

void main(void)
{
    InitSysCtrl();
    InitGpio();
    initGPIO();
    initSCIA();

    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;
    PieVectTable.SCIA_RX_INT = &sciaRxISR;
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
    IER |= M_INT9;
    EINT;

    while (1) {
        // Main loop idle; processing occurs in ISR
    }
}

static void initGPIO(void)
{
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;
    EDIS;
}

static void initSCIA(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    SciaRegs.SCICCR.all = 0x0007;
    SciaRegs.SCICTL1.all = 0x0003;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    SciaRegs.SCIHBAUD.all = 0x0000;
    SciaRegs.SCILBAUD.all = 0x0064;
    SciaRegs.SCICTL1.all = 0x0023;
    EDIS;
}

__interrupt void sciaRxISR(void)
{
    char ch = SciaRegs.SCIRXBUF.all;

    if (ch == '\n') {
        rxBuffer[bufferIndex] = '\0';
        distance = atof(rxBuffer);
        bufferIndex = 0;
    } else if (bufferIndex < BUFFER_SIZE - 1) {
        rxBuffer[bufferIndex++] = ch;
    } else {
        bufferIndex = 0;
    }

    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;
}
