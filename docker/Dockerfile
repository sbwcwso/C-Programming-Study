# 使用Ubuntu作为基础镜像
FROM ubuntu:20.04

# 更新软件包列表
RUN apt-get update

# 安装Valgrind
RUN apt-get install -y valgrind make gcc gdb

# 设置工作目录
WORKDIR /data

# 默认运行bash
CMD ["/bin/bash"]

