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
#if defined(RKH_USE_TRC_SENDER)
static rui8_t ssp;
#endif

static RKH_ROM_STATIC_EVENT(e_pong, evPong);

/* ----------------------- Local function prototypes ----------------------- */
static void rcv_pong(unsigned char data);

/* ---------------------------- Local functions ---------------------------- */
SSP_CREATE_NORMAL_NODE(root);
SSP_CREATE_BR_TABLE(root)
	SSPBR("pong\r\n", rcv_pong,   &root),
SSP_END_BR_TABLE

static void
rcv_pong(unsigned char data)
{
	(void)data;

    RKH_SMA_POST_FIFO(ping, &e_pong, &ssp);
}

/* ---------------------------- Global functions --------------------------- */
void
ping_ssp_init(void)
{
	ssp_init(&root);
}

/* ------------------------------ End of file ------------------------------ */
