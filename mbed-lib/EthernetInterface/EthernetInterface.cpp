/* EthernetInterface.cpp */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "EthernetInterface.h"

static char mac_addr[19];
static char ip_addr[17] = "\0";
static char gateway[17] = "\0";
static char networkmask[17] = "\0";

int EthernetInterface::init() {
    return 0;
}

int EthernetInterface::init(const char* ip, const char* mask, const char* gateway) {
    /* not supported */
    return -1;
}

int EthernetInterface::connect(unsigned int timeout_ms) {
    return 0;
}

int EthernetInterface::disconnect() {
    /* nothing to do */
    return 0;
}

char* EthernetInterface::getMACAddress() {
    return mac_addr;
}

char* EthernetInterface::getIPAddress() {
    return ip_addr;
}

char* EthernetInterface::getGateway() {
    return gateway;
}

char* EthernetInterface::getNetworkMask() {
    return networkmask;
}
