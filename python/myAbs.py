# --*-- coding: utf-8 --*--

def myAbs(x):
	if x >= 0:
		return x
	else:
		return -x
		
#添加参数类型检查
def myAbs(x):
	if not isinstance(x, (int, float)):
		raise TypeError('bad operand type')
	if x >= 0:
		return x
	else:
		return -x
	
#函数参数
#默认参数
#计算x平方的函数
def power(x):
	return x * x
	
此时， 调用power函数时，必须传入有且仅有的一个参数x：
power(5), power(15)
问题：如果需要计算x的立方， x的四次方、...n次方，该怎么办？
解决办法：定义函数power(x, n)：
#计算x的n次方
def power(x, n):
	s = 1
	while n > 0:
		n = n - 1
		s = s * x
	return s
	
用这个函数可以计算x的任意n次方，但是原来定义的函数power(x)，没办法使用了
这时候，默认参数就派上用场了，由于经常计算x的平方，所以，完全可以把第二个参数n的默认值设定为2:
#带默认参数的函数
def power(x, n = 2):
	s = 1
	while n > 0:
		n = n - 1
		s = s * x
	return s
	
这样一来，当调用power(5)时，相当于调用power(5, 2)；而对于n > 2
的其他情况，就必须明确地传入n，比如power(5, 3)

设置默认参数可以简化函数的调用。设置默认参数时，有几点要注意：
一是必选参数在前，默认参数在后，否则python的解释器会报错；
二是如何设置默认参数：
当函数有多个参数时，把变化大的参数放在前面，变化小的参数放在后面。
变化小的参数就可以作为默认参数。
使用默认参数的最大好处是能降低调用函数的难度。

例如：
小学生注册的函数，需要传入name和gender两个参数：
def enroll(name, gender):
	print 'name:', name
	pritn 'gender:', gender
	
这样，调用enroll()函数时只需要传入两个参数：
enroll('Sarah', 'F')

如果要继续传入年龄、城市等信息怎么办？这样会使得调用函数的复杂度大大增加。
可以把年龄和城市设为默认参数：
def enroll(name, gender, age = 6, city = 'Beijing'):
	print 'name:', name
	print 'gender:', gender
	print 'age:', age
	print 'city:', city
	
这样，大部分学生在注册时不需要提供年龄和城市，只提供必须的两个参数：
enroll('Sarah', 'F')
name: Sarah
gender:F
age:6
city:Beijing

只有与默认参数不符的学生才需要提供额外的信息：
enroll('Bob', 'M', 7)
enroll('Adam', 'M', city = 'Tianjin')

由此可见，默认参数降低了函数调用的难度，而一旦需要更复杂的调用时，又
可以传递更多的参数来实现。无论是简单调用还是复杂调用，函数只需要定义一个。
有多个默认参数时，调用的时候，既可以按顺序提供默认参数，比如
调用enroll('Bob', 'M', 7),意思是除了name,gender这两个参数外，最后一个
参数应用在参数age上，city参数由于没有提供，仍然使用默认值。也可以不按
顺序提供部分默认参数。当不按顺序提供部分默认参数时，需要把参数名写上。
比如调用：enroll('Adam', 'M', city = 'Tianjin'),意思是city参数用传进去的值，
其他默认参数继续使用默认值。

默认参数很有用，但是使用不当也会掉进坑里，默认参数有一个最大的坑：
先定义一个函数，传入一个list，添加END，然后再返回。
def addEnd(L = [])
	L.append('END')
	return L
	
当正常调用时，似乎不错：
>>>addEnd([1, 2, 3])
[1, 2, 3, 'END']
>>>addEnd(['x', 'y', 'z'])
['x', 'y', 'z', 'END']

当使用默认参数调用时，一开始结果也是对的：
>>>addEnd()
['END']

但是再次调用addEnd()时就会出错：
>>>addEnd()
['END', 'END']
>>>addEnd()
['END', 'END', 'END']

原因如下：python函数在定义的时候，默认参数L的值就已经被计算出来了，即[]，因为默认
参数L也是一个变量，它指向对象[],每次调用该函数，如果改变了L的内容，则下次调用时，
默认参数的内容就变了，不再是函数定义时的[]了。
所以定义默认参数必须记住一点：默认参数必须指向不可变对象。

要修改上面的例子，可以使用None这个不变对象来实现：
def addEnd(L = None):
	if L is None:
		L = []
	L.append('END')
	return L
	
现在，无论调用多少次都不会出问题：
>>>addEnd()
['END']
>>>addEnd()
['END']

为什么要设计str，None这样的不变对象呢？因为不变对象一旦创建，对象内部的数据就不能再
修改，这样就减少了由于修改数据导致的错误。此外，由于对象不变，多任务环境下同时读取对
象，不需要加锁，同时读一点问题都没有。在编写程序时，如果可以设计一个不变对象，就尽量
设计成不变对象。

#可变参数
在python函数中，还可以定义可变参数。可变参数就是传入的参数个数是可变的，可以是1个、2个...
n个，甚至是0个。

以数学题为例子：给定一组数字a、b、c...计算a2 + b2 + c2 + ...
要定义出这个函数，必须确定输入的参数。由于参数个数不确定，可以把a,b,c...作为一个list或tuple
传进来，这样函数可以定义如下：
def calc(numbers):
	sum = 0
	for n in numbers:
		sum = sum + n * n
	return sum
	
但是调用的时候，需要先组装出一个list或tuple：
>>>calc([1, 2, 3])
14
>>> calc((1, 3, 5, 7))
84

如果利用可变参数，调用函数的方式可以简化成这样：
>>>calc(1, 2, 3)
14
>>>calc(1, 3, 5, 7)
84

所以，我们把函数的参数改为可变参数：
def calc(*numbers):
	sum = 0
	for n in numbers:
		sum = sum + n * n
	return sum
	
定义可变参数和定义list或tuple参数相比，仅仅是在参数前面加了一个*号。
在函数内部，参数numbers接收到的是一个tuple，因此，函数代码完全不变。
但是，调用该函数时，可以传入任意个参数，包括0个参数：
>>>calc(1, 2)
5
>>>calc()
0

如果已经有一个list或tuple，要调用一个可变参数怎么办？可以这样做：
>>>num = [1, 2, 3]
>>>calc(num[0], num[1], num[2])
14

这种写法当然可行，但问题是太繁琐，所以python允许在list或tuple之前加
一个*号，把list或tuple变成可变参数传进去。
>>>num = [1, 2, 3]
>>>calc(*num)
14

这种写法相当有用，而且很常见。

#关键字参数

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
