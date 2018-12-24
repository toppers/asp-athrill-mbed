#!/bin/bash

export ATHRILL_ROOT=../../../../athrill

export MBED_LIB_DIR=..
export PRJROOT_ETHERIF=${MBED_LIB_DIR}/EthernetInterface
export PRJROOT_ASP=../../asp-athrill
export PRJROOT_SAMPLE=${MBED_LIB_DIR}/sample

make $*
