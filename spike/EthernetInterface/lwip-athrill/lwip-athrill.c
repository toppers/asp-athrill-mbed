#include "lwip/sockets.h"
#include <string.h>
#include <stdlib.h>
#include "athrill_syscall.h"

void lwip_socket_init(void)
{
    return;
}

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    //TODO
    return 0;
}

int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    //TODO
    return 0;
}
int lwip_shutdown(int s, int how)
{
    //TODO
    return 0;
}
int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen)
{
    //TODO
    return 0;
}
int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen)
{
    //TODO
    return 0;
}
int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen)
{
    //TODO
    return 0;
}
int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen)
{
    //TODO
    return 0;
}
int lwip_close(int s)
{
    //TODO
    return 0;
}
int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    //TODO
    return 0;
}
int lwip_listen(int s, int backlog)
{
    //TODO
    return 0;
}
int lwip_recv(int s, void *mem, size_t len, int flags)
{
    //TODO
    return 0;
}
int lwip_read(int s, void *mem, size_t len)
{
    //TODO
    return 0;
}
int lwip_recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen)
{
    //TODO
    return 0;
}
int lwip_send(int s, const void *dataptr, size_t size, int flags)
{
    //TODO
    return 0;
}
int lwip_sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen)
{
    //TODO
    return 0;
}
int lwip_socket(int domain, int type, int protocol)
{
    //TODO
    return 0;
}
int lwip_write(int s, const void *dataptr, size_t size)
{
    //TODO
    return 0;
}
int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                struct timeval *timeout)
{
    //TODO
    return 0;
}
int lwip_ioctl(int s, long cmd, void *argp)
{
    //TODO
    return 0;
}
int lwip_fcntl(int s, int cmd, int val)
{
    //TODO
    return 0;
}
struct hostent *lwip_gethostbyname(const char *name)
{
    //TODO
    return NULL;
}
char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen)
{
    //TODO
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
