/*--------------------------------------------------------------------------
File   : i2c_spi_nrf52_irq.cpp

Author : Hoang Nguyen Hoan          July 20, 2018

Desc   : Shared IRQ handler for I2C, SPI

Copyright (c) 2018, I-SYST inc., all rights reserved

Permission to use, copy, modify, and distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright
notice and this permission notice appear in all copies, and none of the
names : I-SYST or its contributors may be used to endorse or
promote products derived from this software without specific prior written
permission.

For info or contributing contact : hnhoan at i-syst dot com

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------
Modified by         Date            Description

----------------------------------------------------------------------------*/

#include "device_intrf.h"
#include "i2c_spi_nrf52_irq.h"

typedef struct {
	DEVINTRF *pDev;				// Device interface data
	IRQHANDLER Handler ;		// Device interface interrupt handler
} IRQDATA;

#define MAX_NB_DEV		2

static IRQDATA s_DevIrq[MAX_NB_DEV] = { {NULL, }, };

void SetI2cSpiIntHandler(int DevNo, DEVINTRF *pDev, IRQHANDLER Handler)
{
	if (DevNo < 0 || DevNo >= MAX_NB_DEV)
	{
		return;
	}

	s_DevIrq[DevNo].pDev = pDev;
	s_DevIrq[DevNo].Handler = Handler;
}

extern "C" void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void)
{
	if (s_DevIrq[0].pDev != NULL)
	{
		s_DevIrq[0].Handler(0, s_DevIrq[0].pDev);
	}
}

extern "C" void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void)
{
	if (s_DevIrq[1].pDev != NULL)
	{
		s_DevIrq[1].Handler(1, s_DevIrq[1].pDev);
	}
}
