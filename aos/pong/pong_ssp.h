/**
 *  \file       pong_ssp.h
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

/* --------------------------------- Module -------------------------------- */
#ifndef __PONG_SSP_H__
#define __PONG_SSP_H__

/* ----------------------------- Include files ----------------------------- */
#include "ssp.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
SSP_DCLR_NORMAL_NODE    root;

void pong_ssp_init(void);
void pong_ssp_doSearch(unsigned char byte);

/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
