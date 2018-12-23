#!/bin/bash

export MBED_LIB_DIR=..
export PRJROOT_ETHERIF=${MBED_LIB_DIR}/EthernetInterface
export TARGET_ATHRILL

make $*
