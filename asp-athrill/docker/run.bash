#!/bin/bash

WORKSPACE_DIR=$(cd .. && pwd)
DOCKER_IMAGE=asp-athrill/v850:v1.0.0

sudo docker run \
	-v ${WORKSPACE_DIR}:/root/workspace/asp \
	-it --rm --net host --name asp-athrill ${DOCKER_IMAGE} 
