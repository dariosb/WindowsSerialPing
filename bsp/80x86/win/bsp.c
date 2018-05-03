/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp_blinky.c
 *  \brief      BSP for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Bali�a       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>

#include "ping.h"
#include "bsp.h"
#include "rkh.h"
#include "trace_io_cfg.h"
#include "wserial.h"
#include "wserdefs.h"
#include "ping.h"
#include "ssp.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ESC         0x1B

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
SERIAL_T serials[ NUM_CHANNELS ] =
{
	{	"COM8",	115200, 8, PAR_NONE, STOP_1, 0 },	// COM1
};

/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_Term, evTerminate);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
printBanner(void)
{
    printf("Ping/Pong: Simple example for test Win Serial Port lib.\n\n");
    printf("RKH version      = %s\n", RKH_RELEASE);
    printf("Port version     = %s\n", rkhport_get_version());
    printf("Port description = %s\n\n", rkhport_get_desc());
    printf("Description: \n\n"
           "The goal of this demo application is to show how to \n"
           "use WinSerial Lib with SSP parser machine\n\n\n");

    printf("1.- Press ESC to quit \n\n\n");
}

/* ---------------------------- Global functions --------------------------- */
void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printBanner();

    trace_io_setConfig(argc, argv);

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(ping);
    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();
}

void
bsp_keyParser(int c)
{
    if (c == ESC)
    {
        RKH_SMA_POST_FIFO(ping, &e_Term, 0);
        rkhport_fwk_stop();
    }
}

void
bsp_timeTick(void)
{
}

static
void
ser_rx_isr( unsigned char byte )
{
    ssp_doSearch(byte);
}

static
void
ser_tx_isr( void )
{
}

/*
 * Serial port callbacks
 */
static SERIAL_CBACK_T ser_cback =
{
	ser_rx_isr,
	NULL,
	NULL,
	ser_tx_isr,
	NULL,
	NULL,
	NULL
};

void
bsp_serial_open(void)
{
	init_serial_hard(TEST_PORT, &ser_cback );
	connect_serial(TEST_PORT);
    tx_data(TEST_PORT, 'O');
}

void
bsp_serial_close(void)
{
	disconnect_serial(TEST_PORT);
	deinit_serial_hard(TEST_PORT);
}

void
bsp_serial_puts(char *p)
{
    while(*p!='\0')
	{
        tx_data(TEST_PORT, *p);
		++p;
	}
}

void
bsp_send_ping(void)
{
	printf("Ping ->\n");
	bsp_serial_puts("ping\r\n");
}

void
bsp_timeout(void)
{
    printf("Timeout!!!\n");
}

void
bsp_received_pong(void)
{
	printf("Pong <-\n");
}


/* ------------------------------ File footer ------------------------------ */