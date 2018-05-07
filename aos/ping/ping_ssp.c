/**
 *  \file       ping_ssp.c
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
#include "ping_ssp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static SSP pingSsp;

static void rcv_pong(unsigned char data);

SSP_CREATE_NORMAL_NODE(pingRoot);
SSP_CREATE_BR_TABLE(pingRoot)
	SSPBR("pong\r\n", rcv_pong,   &pingRoot),
SSP_END_BR_TABLE

static RKH_ROM_STATIC_EVENT(e_pong, evPong);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
rcv_pong(unsigned char data)
{
	(void)data;

    RKH_SMA_POST_FIFO(ping, &e_pong, &pingSsp);
}

/* ---------------------------- Global functions --------------------------- */
void
ping_ssp_init(void)
{
	ssp_init(&pingSsp, &pingRoot);
}

void
ping_ssp_doSearch(unsigned char byte)
{
    ssp_doSearch(&pingSsp, byte);
}

/* ------------------------------ End of file ------------------------------ */
