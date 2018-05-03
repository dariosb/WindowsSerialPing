/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHPORT_H
#define _MOCK_RKHPORT_H

#include "rkhport.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhport_Init(void);
void Mock_rkhport_Destroy(void);
void Mock_rkhport_Verify(void);




#define rkh_enter_critical_Ignore() rkh_enter_critical_CMockIgnore()
void rkh_enter_critical_CMockIgnore(void);
#define rkh_enter_critical_Expect() rkh_enter_critical_CMockExpect(__LINE__)
void rkh_enter_critical_CMockExpect(UNITY_LINE_TYPE cmock_line);
#define rkh_exit_critical_Ignore() rkh_exit_critical_CMockIgnore()
void rkh_exit_critical_CMockIgnore(void);
#define rkh_exit_critical_Expect() rkh_exit_critical_CMockExpect(__LINE__)
void rkh_exit_critical_CMockExpect(UNITY_LINE_TYPE cmock_line);
#define rkh_set_tickrate_Ignore() rkh_set_tickrate_CMockIgnore()
void rkh_set_tickrate_CMockIgnore(void);
#define rkh_set_tickrate_Expect(tick_rate_hz) rkh_set_tickrate_CMockExpect(__LINE__, tick_rate_hz)
void rkh_set_tickrate_CMockExpect(UNITY_LINE_TYPE cmock_line, rui32_t tick_rate_hz);
#define rkh_set_tickrate_IgnoreArg_tick_rate_hz() rkh_set_tickrate_CMockIgnoreArg_tick_rate_hz(__LINE__)
void rkh_set_tickrate_CMockIgnoreArg_tick_rate_hz(UNITY_LINE_TYPE cmock_line);
#define rkh_get_port_version_IgnoreAndReturn(cmock_retval) rkh_get_port_version_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_get_port_version_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return);
#define rkh_get_port_version_ExpectAndReturn(cmock_retval) rkh_get_port_version_CMockExpectAndReturn(__LINE__, cmock_retval)
void rkh_get_port_version_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return);
#define rkh_get_port_desc_IgnoreAndReturn(cmock_retval) rkh_get_port_desc_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_get_port_desc_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return);
#define rkh_get_port_desc_ExpectAndReturn(cmock_retval) rkh_get_port_desc_CMockExpectAndReturn(__LINE__, cmock_retval)
void rkh_get_port_desc_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return);

#endif
