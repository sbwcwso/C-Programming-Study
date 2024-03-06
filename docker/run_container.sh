#!/bin/bash

# 指定宿主机上的目录路径
HOST_DIR="/home/lijunjie/Documents/Course/Introductory_C_Programming"
# 指定容器内的挂载点
CONTAINER_DIR="/data"

# 使用docker run命令启动容器，并挂载目录
docker run -it -v $HOST_DIR:$CONTAINER_DIR intro_c_env

