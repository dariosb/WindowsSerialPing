/**
 *  \file       pong_ssp.c
 *  \brief      Ping Pong SSP´ tree.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.5  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdlib.h>
#include "ping.h"
#include "pong.h"
#include "pong_ssp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static SSP pongSsp;

static void rcv_ping(unsigned char data);

SSP_CREATE_NORMAL_NODE(pongRoot);
SSP_CREATE_BR_TABLE(pongRoot)
	SSPBR("ping\r\n", rcv_ping,   &pongRoot),
SSP_END_BR_TABLE

static RKH_ROM_STATIC_EVENT(e_ping, evPing);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
rcv_ping(unsigned char data)
{
	(void)data;

    RKH_SMA_POST_FIFO(pong, &e_ping, &pongSsp);
}

/* ---------------------------- Global functions --------------------------- */
void
pong_ssp_init(void)
{
	ssp_init(&pongSsp, &pongRoot);
}

void
pong_ssp_doSearch(unsigned char byte)
{
    ssp_doSearch(&pongSsp, byte);
}

/* ------------------------------ End of file ------------------------------ */
