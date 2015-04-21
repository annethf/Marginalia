# -*- coding: utf-8 -*-

# python中的if...else语句
age = 18
if age >= 18:
	print 'your age is', age
	print 'adult'
	
age = 3
if age >= 18:
	print 'your age is', age
	print 'adult'
else:
	print 'your age is', age
	print 'teenager'
	
age = 3
if age >= 18:
	print 'adult'
elif age >= 16:
	print 'teenager'
else:
	print 'kid'
	
age = 20
if age >= 6:
	print 'teenager'
elif age >= 18:
	print 'adult'
else:
	print 'kid'
	