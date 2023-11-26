import numpy as np
dt=np.dtype("<i4")
print(dt)
print(type(dt))
student=np.dtype([("name","S20"),("age","i4"),("marks","f4")])
print(student)
print(type(student))
#创建一维数组
arr =np.array([1,2,3,4,5])
print(arr)
print(type(arr))
#元素类型要相同
arr1 =np.array([1,2.3,4,5,6])
print(arr1)
print(type(arr1))
#多维数组
arr2 = np.array([[1,2,3],[2,3,8],[7,6,8]])
print(arr2)
#二维数组
arr3=np.array([1,2,3,4,5,6],ndmin=2)
print(arr3)
arr4=np.array([1,2.3,4,5,6],dtype="f")
print(arr4)
print(type(arr4))
arr5=np.array(("mayuqi",18,99.99),dtype=student)
print(arr5)
arr6=np.empty([3,2],dtype="i4",)
print(arr6) 
arr7=np.zeros([3,2],dtype="i4",)
print(arr7) 
#数据结构化
arr8=np.zeros([3,2],dtype=([("x","i4"),("m","f")]))
print(arr8) 
#np.ones与np.zeros用法相同 不同的在于它用1填充
arr9=np.ones([3,2],dtype=([("x","i4"),("m","f")]))
print(arr9) 
#full函数 以指定的数据进行填充
m_arr=np.full(5,fill_value=1024,dtype=([("x","i4"),("m","f")]))
print(m_arr)
#eye函数  对角线为1 其余位置为0
m_arr1=np.eye(3,dtype="i4")
print(m_arr1)
#arange函数  创建数值对象 并返回ndarry对象,不包含终止值
m_arr2=np.arange(1,100,2,dtype="f")
print(m_arr2)
#frombuffer(任意对象以流的形式读入,返回数据类型,读取的数据数量,读取的起始位置)
x=b"mayuqi"
m_arr3=np.frombuffer(x,dtype="S1",count=3,offset=2)
print(m_arr3)
#fromiter函数可以读取可迭代对象
x=[1,2,3,4,5]
z=iter(x)
m_arr4=np.fromiter(z,dtype="f")
print(m_arr4)
#linspace 函数 创建一个数组 这个数组是等差数列(初始值,最后值,生成的数量,默认为ture包含stop值，是否显示间距)
m_arr5=np.linspace(2,1000,dtype="i4",num=50,)
print(m_arr5)
#logspace 函数 创建一个等比数组
# m_arr6=np.logspace(1.0,10.0,endpoint=True,base=10,dtype="f")
# print(m_arr6)
m_arr6=np.logspace(1.0,10.0,10,dtype="i4")
print(m_arr6)
#random.rand函数  0~1    一~三维都可以
m_arr7=np.random.rand(3,2,3)
print(m_arr7)
#random.randint(low,high(不包含),size,dtpe)
m_arr8=np.random.randint(5,20,10,"i4")
print(m_arr8)
#random.randn 返回一个或者一组样本    以0为均值  1为标准差    一~三维都可以
m_arr9=np.random.randn(2,3,4)
print(m_arr9)
#normol(loc(浮点型 此概率分布的均值),scale(浮点型 此概率分布的标准差,越大越胖，越瘦越高),size)
m_arr10=np.random.normal(loc=1.0,scale=50,size=10)
print(m_arr10)