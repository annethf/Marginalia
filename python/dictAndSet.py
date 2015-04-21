# -*- coding: utf-8 -*-

#dict(dictionary:相当于C++中的map）
#d 是一个dict
d = {'Micheal':95, 'Bob':75, 'Tracy':85}
d['Micheal']

#给dict赋值的另一种方式
d['Adam'] = 67
d['Adam']

#key只能对应一个value,多次对一个key放入value，后面的值会把前面的冲掉
d['Jack'] = 90
d['Jack']
90
d['Jack'] = 89
d['Jack']
89

#如果key不存在，dict会报错
d['Thomas']
出错信息

#判断key是否在dict中
#方式1 通过in判断
'Thomas' in d

#方式2 通过get方法判断
#返回None，交互界面不显示结果
d.get('Thomas')
#返回用户指定的值, 此处为-1
d.get('Thomes', -1)

#***使用注意事项***
#dictde key必须是不可变对象，这是因为dict是根据key来计算value的存储位置的，
#如果每次计算相同的key得出的结果不同，那dict就乱了。通过key计算位置的算法
#是Hash算法，要保证Hash的正确性，作为key的对象就不能变。在python中，字符串、
#整数等都是不可变的， 而list是可变的，就不可以作为key

#list作为key
key = [1, 2, 3]
d[key] = 'a list'
#出错信息

#dict特点(用空间换取时间）
#1、查找和插入的速度极快， 不会随着key的增加而增加
#2、需要占用大量的内存，内存浪费多

#删除dict中的元素
d.pop('Micheal')
#set
s = set([1, 2, 3])
s
set([1, 2, 3])
#重复元素自动删除
s = set([1, 1, 2, 2, 3, 3])
s
set([1, 2, 3])

s.add(4)
s
set([1, 2, 3, 4])
s.add(4)
s
set([1, 2, 3, 4])

s.remove(4)
s
set([1, 2, 3])

s1 


