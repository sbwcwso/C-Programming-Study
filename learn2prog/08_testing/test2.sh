#!/bin/bash

# 第一:替换为正确版本
for i in {1..100} 
do
  ./isPrime-broken2 $i
done

# 第二:测试-10到100之间的整数
for i in {-10..100}
do
  ./isPrime-broken2 $i  
done

# 第三:测试字符串
./isPrime-broken2 nihao

# 第四:其他测试用例
# 测试非整数
./isPrime-broken2 1.5  

# 测试大整数
./isPrime-broken2 8462696833

# 测试边界值 
./isPrime-broken2 0
./isPrime-broken2 1
./isPrime-broken2 2

# 测试空参数
./isPrime-broken2

# 组合测试
./isPrime-broken2 10 twenty 30 forty hello
