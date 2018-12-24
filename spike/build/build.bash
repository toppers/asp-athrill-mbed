#!/bin/bash

export MBED_LIB_DIR=..
export PRJROOT_ETHERIF=${MBED_LIB_DIR}/EthernetInterface
export PRJROOT_ASP=../../asp-athrill

make $*
