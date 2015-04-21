# -*- coding: utf-8 -*-

# for...in loop

names = ['Michael', 'Bob', 'Tracy']  #python list
for name in names:
	print name
	

sum = 0
for x in [1, 2, 3, 4, 5, 6 ,7, 8, 9, 10]:
	sum = sum + x
print sum


range(5) #生成小于5的整数

# 计算0-100的整数的和
sum = 0
for x in range(101):
	sum = sum + x
print sum

# while loop
# 计算100以内所有奇数的和
sum = 0
n = 99
while n > 0:
	sum = sum + n
	n = n - 2
print sum

# 一个错误
#raw_input函数相当于C中的scanf
birth = raw_input('birth: ') 
if birth < 2000:
	print u'00前'
else:
	print u'00后'
	
#输入1982会输出00后，原因是raw_input读取的内容永远以字符串的形式返回

# 正确写法
#把raw_input返回的字符串转换成整形
birth = int(raw_input('birth: ')) 
if birth < 2000:
	print u'00前'
else:
	print u'00后'
	




