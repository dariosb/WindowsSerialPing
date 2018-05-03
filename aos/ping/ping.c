/**
 *  \file       ping.c
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
#include "ping_ssp.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define PONG_WAIT_TIME          RKH_TIME_SEC(2)
#define PING_DELAY_TIME         RKH_TIME_SEC(1)

/* ......................... Declares active object ........................ */
typedef struct Ping Ping;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE pinging, ping_delay;

/* ........................ Declares initial action ........................ */
static void ping_init(Ping *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void close(Ping *const me, RKH_EVT_T *pe);
static void send_ping(Ping *const me, RKH_EVT_T *pe);
static void timeout(Ping *const me, RKH_EVT_T *pe);
static void rcv_pong(Ping *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(pinging, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(pinging)
    RKH_TRINT(evTerminate,  NULL, close),
    RKH_TRINT(evTimeout,    NULL, timeout),
    RKH_TRREG(evPong,       NULL, rcv_pong, &ping_delay),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(ping_delay, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ping_delay)
    RKH_TRINT(evTerminate,  NULL, close),
    RKH_TRREG(evTimeout,    NULL, send_ping, &pinging),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Ping
{
    RKH_SMA_T sma;      /* base structure */
    RKH_TMR_T timer;    /* which is responsible for toggling the LED */
                        /* posting the TIMEOUT signal event to active object */
                        /* 'ping' */
};

RKH_SMA_CREATE(Ping, ping, 0, HCAL, &pinging, ping_init, NULL);
RKH_SMA_DEF_PTR(ping);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/*
 *  Declare and allocate the 'e_tout' event.
 *  The 'e_tout' event with TIMEOUT signal never changes, so it can be
 *  statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */
static RKH_ROM_STATIC_EVENT(e_tout, evTimeout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
ping_init(Ping *const me, RKH_EVT_T *pe)
{
	(void)pe;

    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &pinging);
    RKH_TR_FWK_TIMER(&me->timer);
    RKH_TR_FWK_SIG(evTerminate);
	RKH_TR_FWK_SIG(evTimeout);
	RKH_TR_FWK_SIG(evPong);

    RKH_TMR_INIT(&me->timer, &e_tout, NULL);

	ping_ssp_init();

    bsp_serial_open();

    send_ping(me, NULL);
}

/* ............................ Effect actions ............................. */
static void
close(Ping *const me, RKH_EVT_T *pe)
{
	(void)pe;

    bsp_serial_close();
    rkh_tmr_stop(&me->timer);
}

static void
send_ping(Ping *const me, RKH_EVT_T *pe)
{
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), PONG_WAIT_TIME);
    bsp_send_ping();
}

static void
timeout(Ping *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_timeout();
    send_ping(me, NULL);
}

static void
rcv_pong(Ping *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), PING_DELAY_TIME);
	bsp_received_pong();
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
