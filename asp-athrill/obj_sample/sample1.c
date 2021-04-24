#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

/*
 *  サービスコールのエラーのログ出力
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))


void cyclic_handler(intptr_t exinf)
{
}

/*
 *  メインタスク
 */
void main_task(intptr_t exinf)
{
	int cnt = 0;
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int_t) exinf);
	while (1) {
		syslog(LOG_NOTICE, "cnt=%d", cnt++);
		dly_tsk(100);

	}

	syslog(LOG_NOTICE, "Sample program ends.");
	SVC_PERROR(ext_ker());
}
