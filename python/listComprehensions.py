#列表生成式
列表生成式是python内置的非常简单却强大的可以用来创建list的生成式。
举个例子，要生成list[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]可以用range(1, 11):

>>>range(1, 11)
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

但如果要生成[1*1, 2*2, 3*3, ..., 10*10]怎么做？方法一是循环：

>>>L = []
>>>for x in range(1, 11):
		L.append(x * x)
		
>>>L
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]

但是循环太繁琐，而列表生成式则可以用一行语句代替循环生成上面的list:

>>>[x * x for x in range(1, 11)]
[1, 4, 9, 16, 25, 36, 49, 81, 100]

写成列表生成式时，把要生成的元素x * x放到前面，后面跟for循环，就可以把list
创建出来，十分有用，多谢几次，很快就可以熟悉这种语法。

for循环后面还可以加上if判断，这样就可以筛选出仅偶数的平方：

>>>[x * x for x in range(1, 11) if x % 2 == 0]
[1, 4, 16, 36, 100]

还可以使用两层循环，可以生成全排列：

>>>[m + n for m in 'ABC' for n in 'XYZ']
['AX', 'AY', 'AZ', 'BX', 'BY', 'BZ', 'CX', 'CY', 'CZ']

三层和三成以上的循环就很少用到了。

运用列表生成式，可以写出非常简洁的代码。例如，列出当前目录下的所有文件和
目录名，可以通过一行代码实现：

>>>import os
>>>[d for d in os.listdir('.')]

for循环其实可以同时使用两个甚至多个变量，比如dict的iteritems()可以同时迭代key和value:

>>>d = {'x': 'A', 'y': 'B', 'z': 'C'}
>>>for k, v in d.iteritems():
		print k, '=', v
		
y = B
x = A
z = C

因此，列表生成式也可以使用两个变量来生成list:

>>>d = {'x': 'A', 'y': 'B', 'z': 'C'}
>>>[k + '=' + v for k, v in d.iteritems()]
['y = B', 'x = A', ' z = C']

最后把一个list中所有的字符串变成小写:

>>>L = ['Hello', 'World', 'IBM', 'Apple']
>>>[s.lower() for s in L]
['hello', 'world', 'ibm', 'apple']

小结：
运用列表生成式，可以快速生成list, 可以通过一个list推导出另一个list,
而代码却十分简洁。

但是，如果list中既包含字符串，又包含整数，由于字符串类型没有lower()方法，
所以列表生成式会报错：

>>>L = ['Hello', 'World', 18, 'Apple', None]
>>>[s.lower() for s in L]
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
 AttributeError: 'int' object has no attribute 'lower'
 
使用内建的instance函数可以判断一个变量是否是字符串：

>>>x = 'abc'
>>>y = 123
>>>isinstacne(x, str)
True
>>>isinstance(y, str)
False

通过添加if语句可以保证上面的列表生成式正常执行：

>>>L = ['Hello', 'World', 18, 'Apple', None]
>>>[s.lower() for s in L if isinstance(s, str)]
['hello', 'world', 'apple']

#生成器

通过列表生成式，可以直接创建一个列表。但是，收到内存限制，列表容量
肯定是有限的。而且，创建一个包含100万个元素的列表，不仅占用很大的
存储空间，如果仅仅需要访问前面几个元素，那后面绝大多数元素占用的空间
都白白浪费了。
所以，如果列表元素可以按照某种算法推算出来，那是否可以在循环的过程中
不断推算出后续的元素呢？这样就不比创建完整的list，从而节省大量的空间。
在python中，这种一边循环一边计算的机制，成为生成器。

要创建一个生成器(generator)，有很多种方法。第一种方法很简单，只要把一
个列表生成式的[]改成()，就创建了一个generator:

#列表生成式
>>>L = [x * x for x in range(1, 11)]
>>>L
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
#生成器
>>>g = (x * x for x in range(1, 11))
>>>g
<generator object <genexpr> at 0x104feab40>

创建L和g的区别仅仅在于最外层的[]和(), L是一个list, 而g是一个generator.
可以直接打印出一个list中的每一个元素，但是怎样打印generator的每一个
元素呢？
如果要一个一个打印出来，可以通过generator的next()方法：

>>>g.next()
1
>>>g.next()
4
>>>g.next()
9
>>>g.next()
16
...

generator保存的是算法，每次调用next()，就计算下一个元素的值，直到计算最后
一个元素，没有更多的元素时，抛出StopIteration的错误。

当然，上面这种不断调用next()方法实在是太变态了，正确的方法是使用for循环，
因为generator也是可迭代对象：

>>>g= (x * x for x in range(10))
>>>for n in g:
		print n
		
0
1
4
9
16
25
36
49
64
81

所以，创建了一个generator后，基本上永远也不会调用next()方法，而是通过
for循环来迭代它。

generator非常强大，如果推算的算法比较复杂，用类似列表生成式的for循环
无法实现的时候，还可以用函数来实现。

比如，著名的斐波那契数列，除第一个和第二个数外，任意一个数都可由前两个数相加
得到：

1, 1, 2, 3, 5, 8, 13, 21, 34,...

斐波那契数列用列表生成式写不出来，但是，用函数把它打印出来却很容易：

>>>def fib(max):
		n, a, b = 0, 0, 1
		while n < max:
			print b
			a, b = b, a + b
			n = n + 1

上面的函数可以输出斐波那契数列的前N个数：

>>>fib(6)
1
1
2
3
5
8

仔细观察，可以看出，fib函数实际上是定义了斐波那契数列的推算规则，可以从
第一个元素开始，推算出后续任意的元素，这种逻辑其实非常类似generator。

也就是说，上面的函数和generator仅一步之遥。要把fib函数变成generator,只需
要把print b改为yield b就可以了：

>>>def fib(max):
		n, a, b = 0, 0, 1
		while n < max:
			yield b
			a, b = b, a + b
			n = n + 1
			
这就是定义generator的另一种方法。如果一个函数定义中包含yield关键字，那么这个
函数就不再是一个普通函数，而是一个generator:

>>>fib(6)
<generator object fib at ...>

这里，最难理解的就是generator和函数的执行流程是不一样的。函数是顺序执行，遇到
return语句或者最后一行函数语句就返回，而变成generator的函数，在每次调用next()
的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行。

举个简单的例子，定义一个generator，依次返回数字1, 3, 5:

>>>def odd():
		print 'step 1'
		yield 1
		print 'step 2'
		yield 3
		print 'step 3'
		yield 5
		
>>>o = odd()
>>>o.next()
step 1
1
>>>o.next()
step 2
3
>>>o.next()
step 3
5
>>>o.next()
Tracebace (most recent call last):
 File "<stdin>", line 1, in <module>
StopIteration

可以看到，odd不是普通函数，而是generator, 在执行过程中，遇到yield就
中断，下次继续执行。执行3次yield后，已经没有yield可以执行了，所以，
第4次调用next()就报错。

同样地，把函数改成generator后，基本上从来不会用next()来调用它，而是直
接使用for循环来迭代：

>>>for n in fib(6):
		print n
		
1
1
2
3
5
8

小结：
generator是非常强大的工具，在pyghon中，可以简单地把列表生成式改成generator,
也可以通过函数实现复杂逻辑的generator。

要理解generator的工作原理，它是在for循环的过程中不断计算出下一个元素，并在
适当的条件结束for循环。对于函数改成的generator来说，遇到return语句或执行到
函数体最后一行语句，就是结束generator的指令，for循环随之结束。

#函数式编程 Functional Programming

函数式编程的思想更接近数学计算。它是一种抽象程度很高的编程范式，纯粹的函数式
编程语言编写的函数没有变量，因此，任意一个函数，只要输入是确定的，输出就是确
定的，这种纯函数被称为没有副作用。而允许使用变量的程序设计语言，由于函数内部
的变量状态不确定，同样的输入，可能得到不同的输出，因此，这种函数是有副作用的。

函数式编程的一个特点就是允许把函数本身作为参数传入另一个函数，还允许返回一个函数！

python对函数式编程提供部分支持，由于python允许使用变量，因此，python不是纯函数式
编程语言。

#高阶函数 Higher-order function

#变量可以指向函数
以python内置的求绝对值的函数abs()为例，调用该函数用以下代码：

>>>abs(-10)
10

但是，如果只写abs呢？

>>>abs
<bulit-in funciotn abs>

可见，abs(-10)是函数调用，而abs是函数本身。
要获得函数调用结果，可以把结果赋值给变量：

>>>x = abs(-10)
>>>x
10

但是，如果把函数本身赋值给变量呢？

>>>f = abs
>>>f
<built-in function abs>

结论：函数本身也可以赋值给变量，即：变量可以指向函数。
如果一个变量指向了一个函数，那么，可否通过该变量来调用这个函数？

>>>f = abs
>>>f(-10)
10

成功，说明变量f现在已经指向了abs函数本身。

#函数名也是变量

那么函数名是什么呢？函数名其实就是指向函数的变量！对于abs()这个函数，
完全可以把函数名abs看成变量，它指向一个可以计算绝对值的函数！

如果把abs指向其他对象，会有什么情况发生？

>>>abs = 10
>>>abs(-10)
Traceback (most recent call last):
 File "<stdin>", line 1, in <module>
TypeError: 'int' object is not callable

把abs指向10后，就无法通过abs(-10)调用该函数了，因为abs这个变量已经不指向
求绝对值函数了！
实际代码是不能这么写的，这里只是为了说明函数名也是变量，要恢复abs函数，请
重启python交互环境。
注：由于abs函数实际上是定义在_builtin_模块中的，所以要让修改abs变量的指向
在其他模块中也生效，要用_builtin_.abs = 10.

#传入函数
既然变量可以指向函数，函数的参数能接收变量，那么一个函数就可以接收另一个函
数作为参数，这种函数就称之为高阶函数。

>>>def add(x, y, f):
		return f(x) + f(y)
	
当调用add(-5, 6, abs)时，参数x, y和f分别接收-5, 6和abs，根据函数定义，就可以
推导计算过程为：
x ==> -5
y ==> 6
f ==> abs
f(x) + f(y) ==> abs(-5) + abs(6) ==> 11

用代码验证一下：

>>>add(-5, 6, abs)
11

编写高阶函数，就是让函数的参数能够接收别的函数。

小结：
把函数作为参数传入，这样的函数成为高阶函数，函数式编程就是这种高度抽象的编程范式。



































