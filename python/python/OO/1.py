#!/usr/bin/env python

class AddrBookEntry(object):
    """
    address book entry class
    """
    a = 0       #类变量
    def __init__(self, nm, ph):
        self.name = nm
        self.phone = ph
        AddrBookEntry.a += 1    #修改类变量需要指定类名
        print('created instance for:' + self.name)
        print('instance number:' + str(AddrBookEntry.a))

    def updatePhone(self, newph):
        self.phone = newph
        print('Updated phone# for:' + self.name)
    @classmethod        #类方法,默认参数是类而不是实例， 类和实例都可以调用，无法访问实例变量，可以访问类变量
    def update(cls):
        cls.a += 1
        print('cls:' + str(cls))

class EmplAddrBookEntry(AddrBookEntry):
    """
    Employee Address Book Entry Class
    """
    def __init__(self, nm, ph, id, em): #如果子类不定义__init__则调用父类的__init__方法， 如果子类定义了，则不再调用父类
        AddrBookEntry.__init__(self, nm, ph) #除非自己手动调用
        self.empid = id
        self.email = em

    
    def updateEmail(self, newem):
        self.email = newem
        print('Updated email address for:' + self.name)

    @staticmethod       #静态方法,没有默认参数，类和实例都可以调用,无法访问类变量和实例变量
    def static_method():
        print('static method')

a = EmplAddrBookEntry('lyt', 1234, 1, 'liyunteng@163.com')
print(a.a)      #引用的类变量
print(EmplAddrBookEntry.a)
a.a += 1        #生成实例变量并将类变量隐藏
print(a.a)      #打印的实例变量
print(EmplAddrBookEntry.a)
del(a.a)        #删除了实例变量，类变量变为可见
print(a.a)      #打印的类变量
print('-'*20)
EmplAddrBookEntry.a += 1        #修改了子类的类变量，将父类中的覆盖
print(a.a)
print(EmplAddrBookEntry.a)      
print(AddrBookEntry.a)
print('*'*20)
AddrBookEntry.a += 100
print(a.a)              
print(EmplAddrBookEntry.a)
print(AddrBookEntry.a)
del(EmplAddrBookEntry.a)        #删除掉子类的类变量，父类的类变量变为可见
print("#"*20)
print(EmplAddrBookEntry.a)
print(AddrBookEntry.a)
print(a.a)
