#include "lwip/sockets.h"
#include <string.h>
#include <stdlib.h>
#include "athrill_syscall.h"
#include "kernel.h"

#define FALSE	0
#define TRUE	1
#if 1
#define OS_DLY_TSK(arg)
#else
#define OS_DLY_TSK(arg)	dly_tsk(arg)
#endif

void lwip_socket_init(void)
{
	//nothing to do
    return;
}

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
	sys_int32 client_sockfd;
	struct sys_sockaddr_in client_sockaddr;

	do {
		client_sockfd = athrill_posix_accept(s, &client_sockaddr, addrlen);
		if (client_sockfd != SYS_API_ERR_AGAIN) {
			break;
		}
		else if (client_sockfd == SYS_API_ERR_AGAIN) {
			//sleep 1msec
			OS_DLY_TSK(1);
			continue;
		}
	} while (client_sockfd < 0);

	if (client_sockfd < 0) {
		return -1;
	}
	return client_sockfd;
}

int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen)
{
	if (name->sa_family == PF_INET) {
		sys_int32 err;
		struct sys_sockaddr_in sockaddr;
		struct sockaddr_in *addr_in = (struct sockaddr_in*)name;

		sockaddr.sin_family = ATHRILL_SYSCALL_SOCKADDR_FAMILIY_PF_INET;
		sockaddr.sin_addr = addr_in->sin_addr.s_addr;
		sockaddr.sin_port = addr_in->sin_port;

		err = athrill_posix_bind(s, &sockaddr, sizeof(sockaddr));
		if (err != 0) {
			return -1;
		}
		return 0;
	}
	else {
		return -1;
	}
}
int lwip_shutdown(int s, int how)
{
	//nothing to do
    return 0;
}
int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen)
{
    //not supported
    return -1;
}
int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen)
{
    //not supported
    return -1;
}
int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen)
{
    //not supported
    return -1;
}
int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen)
{
    //not supported
    return -1;
}
int lwip_close(int s)
{
	(void)athrill_posix_shutdown(s, ATHRILL_POSIX_SHUT_RDWR);
    return 0;
}
int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen)
{
	if (name->sa_family == PF_INET) {
		sys_int32 err;
		struct sys_sockaddr_in sockaddr;
		struct sockaddr_in *addr_in = (struct sockaddr_in*)name;

		sockaddr.sin_family = ATHRILL_SYSCALL_SOCKADDR_FAMILIY_PF_INET;
		sockaddr.sin_addr = addr_in->sin_addr.s_addr;
		sockaddr.sin_port = addr_in->sin_port;
		bool_t is_connected = 0;

		while (is_connected == 0) {
			(void)athrill_posix_connect(s, &sockaddr, sizeof(sockaddr));
			do {
				err = athrill_posix_sense(s, SYS_API_ID_CONNECT);
				if (err == SYS_API_ERR_OK) {
					is_connected = 1;
					break;
				}
				else if (err == SYS_API_ERR_AGAIN) {
					//sleep 1msec
					OS_DLY_TSK(1);
				}
				else if (err == SYS_API_ERR_CONNREFUSED) {
					break;
				}
				return -1;
			} while (err < 0);
		}
		return 0;
	}
	else {
		return -1;
	}
}

int lwip_listen(int s, int backlog)
{
	sys_int32 err = athrill_posix_listen(s, backlog);
	if (err != 0) {
		return -1;
	}
    return 0;
}

int lwip_recv(int s, void *mem, size_t len, int flags)
{
	sys_int32 err;
	err = athrill_posix_recv(s, (sys_addr)mem, len, ATHRILL_POSIX_MSG_DONTWAIT);
	if (err < 0) {
		return -1;
	}
	return err;
}

int lwip_read(int s, void *mem, size_t len)
{
    //not supported
    return -1;
}
int lwip_recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen)
{
    //not supported
    return -1;
}
int lwip_send(int s, const void *dataptr, size_t size, int flags)
{
	sys_int32 err;

	err = athrill_posix_send(s, (sys_addr)dataptr, size, ATHRILL_POSIX_MSG_DONTWAIT);
	if (err < 0) {
		return -1;
	}
    return 0;
}
int lwip_sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen)
{
    //not supported
    return -1;
}
int lwip_socket(int domain, int type, int protocol)
{
	int sockfd = athrill_posix_socket(ATHRILL_SYSCALL_SOCKET_DOMAIN_AF_INET, ATHRILL_SYSCALL_SOCKET_TYPE_STREAM, ATHRILL_SYSCALL_SOCKET_PROTOCOL_ZERO);
    return sockfd;
}
int lwip_write(int s, const void *dataptr, size_t size)
{
    //not supported
    return -1;
}
int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                struct timeval *timeout)
{
    //TODO
    return 0;
}
int lwip_ioctl(int s, long cmd, void *argp)
{
    //not supported
    return -1;
}
int lwip_fcntl(int s, int cmd, int val)
{
    //not supported
    return -1;
}
struct hostent *lwip_gethostbyname(const char *name)
{
    //not supported
    return NULL;
}
char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen)
{
    //not supported
    return NULL;
}

void *__dso_handle=0;

void *malloc(size_t size)
{
	return (void*)athrill_posix_malloc((sys_uint32)size);
}
void free(void *addr)
{
	athrill_posix_free((sys_addr)addr);
}

void *calloc(size_t nmemb, size_t size)
{
	return (void*)athrill_posix_calloc((sys_uint32)nmemb, (sys_uint32)size);
}

void *realloc(void *ptr, size_t size)
{
	return (void*)athrill_posix_realloc((sys_addr)ptr, (sys_uint32)size);
}

void *_malloc_r(struct _reent *reent, unsigned int size)
{
	return malloc(size);
}
void *_calloc_r(struct _reent *reent, size_t nmemb, size_t size)
{
	return calloc(nmemb, size);
}
void *_realloc_r(struct _reent *reent, void *ptr, size_t size)
{
	return realloc(ptr, size);
}

void _free_r(struct _reent *reent, void *addr)
{
	free(addr);
}
int raise(int sig)
{
	return 0;
}