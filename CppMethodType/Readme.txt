const SpreadsheetCell add(const SpreadsheetCell& cell) const;
最后一个const表明这是一个const方法，说明不允许这个函数改变任意
一个数据成员；倒数第二个const表明传入的参数是一个常引用，使用
const表明不允许这个方法修改实参，传引用是因为传入的是类对象，为了
提高效率。第一个const说明这一函数返回一个常量，即不允许用户改变
返回值，这个值只是用来赋值给其他对象的。