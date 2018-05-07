/**
 *  \file       pong.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.05.02  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "ping.h"
#include "pong.h"
#include "pong_ssp.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define PONG_WAIT_TIME          RKH_TIME_SEC(2)
#define PING_DELAY_TIME         RKH_TIME_SEC(1)

/* ......................... Declares active object ........................ */
typedef struct Pong Pong;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE ponging;

/* ........................ Declares initial action ........................ */
static void pong_init(Pong *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void close(Pong *const me, RKH_EVT_T *pe);
static void send_pong(Pong *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(ponging, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ponging)
    RKH_TRINT(evTerminate,  NULL, close),
    RKH_TRINT(evPing,       NULL, send_pong),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Pong
{
    RKH_SMA_T sma;      /* base structure */
};

RKH_SMA_CREATE(Pong, pong, 1, HCAL, &ponging, pong_init, NULL);
RKH_SMA_DEF_PTR(pong);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
pong_init(Pong *const me, RKH_EVT_T *pe)
{
	(void)pe;

    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &ponging);
	RKH_TR_FWK_SIG(evPing);

	pong_ssp_init();

    bsp_serial_open(PONG_PORT);
}

/* ............................ Effect actions ............................. */
static void
close(Pong *const me, RKH_EVT_T *pe)
{
	(void)me;
	(void)pe;

    bsp_serial_close(PONG_PORT);
}

static void
send_pong(Pong *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_send_pong();
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
