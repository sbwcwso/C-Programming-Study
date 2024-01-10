#!/bin/bash

# 第一:替换为正确版本
for i in {1..100} 
do
  ./isPrime-broken4 $i
done

# 第二:测试-10到100之间的整数
for i in {-10..100}
do
  ./isPrime-broken4 $i  
done

# 第三:测试字符串
./isPrime-broken4 nihao

# 第四:其他测试用例
# 测试非整数
./isPrime-broken4 1.5  

# 测试大整数
./isPrime-broken4 8462696833

# 测试边界值 
./isPrime-broken4 0
./isPrime-broken4 1
./isPrime-broken4 2

# 测试空参数
./isPrime-broken4

# 组合测试
./isPrime-broken4 10 twenty 30 forty hello
