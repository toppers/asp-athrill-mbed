/*
 *  TTSP
 *      TOPPERS Test Suite Package
 * 
 *  Copyright (C) 2010-2011 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010-2011 by Digital Craft Inc.
 *  Copyright (C) 2010-2011 by NEC Communication Systems, Ltd.
 *  Copyright (C) 2010-2011 by FUJISOFT INCORPORATED
 * 
 *  上記著作権者は，以下の(1)~(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: ttsp_target_test.c 2 2012-05-09 02:23:52Z nces-shigihara $
 */

#include "kernel_impl.h"
#include <sil.h>
#include "ttsp_target_test.h"
#include "target_timer.h"

static unsigned int athrill_device_raise_interrupt __attribute__ ((section(".athrill_device_section")));
static unsigned int is_ttsp_target_timer_running = 1;

/*
 *  ティック更新の停止
 */
void
ttsp_target_stop_tick(void)
{
	SIL_PRE_LOC;
	
	SIL_LOC_INT();

	dev_disable_int(INTNO_TIMER);
	SetTimerStopTAA(INTNO_TIMER);
	x_clear_int(INTNO_TIMER);
	SIL_UNL_INT();

	is_ttsp_target_timer_running = 0;
	return;
}

/*
 *  ティック更新の再開
 */
void
ttsp_target_start_tick(void)
{
	SIL_PRE_LOC;
	
	SIL_LOC_INT();

	SetTimerStartTAA(TIMER_DTIM_ID);
	dev_enable_int(INTNO_TIMER);
	
	SIL_UNL_INT();

	is_ttsp_target_timer_running = 1;
	return;
}

/*
 *  ティックの更新
 */
void
ttsp_target_gain_tick(void)
{
	SIL_PRE_LOC;

	SIL_LOC_INT();
	SetTimerStartTAA(TIMER_DTIM_ID);
	dev_enable_int(INTNO_TIMER);

	do_halt();

	SIL_UNL_INT();

	SIL_LOC_INT();
	dev_disable_int(INTNO_TIMER);
	SetTimerStopTAA(INTNO_TIMER);
	SIL_UNL_INT();

}

/*
 *  割込みの発生   
 */
void
ttsp_int_raise(INTNO intno)
{
	athrill_device_raise_interrupt = intno;
}

/*
 *  CPU例外の発生
 */
void
ttsp_cpuexc_raise(EXCNO excno)
{
	do_trap(0x01);
}

/*
 *  CPU例外発生時のフック処理(athrillでは不要)
 */
void
ttsp_cpuexc_hook(EXCNO excno, void* p_excinf)
{
}

/*
 *  割込み要求のクリア
 */
void
ttsp_clear_int_req(INTNO intno)
{
	x_clear_int(intno);
}

