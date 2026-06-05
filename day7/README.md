1. 什么是浅拷贝
int main() {
    SimpleBuffer buf(100);
    return 0;
}

创建时申请内存，结束时释放内存。

但是如果你写：

SimpleBuffer buf1(100);
SimpleBuffer buf2 = buf1;

buf1.data 指向地址 0x1000
buf2.data 也指向地址 0x1000

也就是说，两个对象都指向同一块内存。

这会导致严重问题：

buf1 析构时 delete[] data
buf2 析构时也 delete[] data

同一块内存被释放两次

这叫：

double free，重复释放



2. 什么是深拷贝
不仅复制指针，还重新申请一块新内存，把原来的内容复制过去。

也就是说：

buf1.data 指向 0x1000
buf2.data 指向 0x2000

两个对象各自拥有自己的内存。

这样析构时：

buf1 释放自己的内存
buf2 释放自己的内存


3. 什么是拷贝构造函数
SimpleBuffer buf1(100);
SimpleBuffer buf2 = buf1;

会触发拷贝构造函数。

拷贝构造函数的形式是：

SimpleBuffer(const SimpleBuffer& other)

解释：

const SimpleBuffer& other

表示：

拿另一个 SimpleBuffer 作为参考，但不修改它。

示意代码：

SimpleBuffer(const SimpleBuffer& other) {
    size = other.size;
    data = new char[size];

    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }

    cout << "Copy constructor called" << endl;
}


4. 什么是拷贝赋值运算符
存在理由 如果两个指针指向同一个内存，删除的时候同一个内存被删了两次所必，所以必须自己写赋值逻辑不能复制地址。

要复制内容。
SimpleBuffer& operator=(const SimpleBuffer& other)
buf2 = buf1 其实就是这个意思
可以拆成两部分：

SimpleBuffer&

这是返回类型：返回当前对象的引用。

operator=(const SimpleBuffer& other)

这是函数名和参数：重载 =，参数是另一个 SimpleBuffer 的只读引用。

赋值操作 //this 是 当前对象自己的地址。
SimpleBuffer& operator=(SimpleBuffer&& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    size = other.size;
    data = other.data;

    other.size = 0;
    other.data = nullptr;

    cout << "Move assignment called" << endl;

    return *this;
}




5. 什么是移动构造函数

有时候你不想复制一整块资源，只想把资源“交给另一个对象”。

比如：

SimpleBuffer buf1(100);
SimpleBuffer buf2 = move(buf1);

这里触发的是移动构造函数。

移动构造的核心思想是：

不重新申请内存，不复制内容，直接把指针所有权拿过来。

形式是：
SimpleBuffer(SimpleBuffer&& other)

注意这里是：

&&
叫右值引用，你现在可以先理解成：

这个 other 是一个准备被“搬走资源”的对象。

示意代码：

SimpleBuffer(SimpleBuffer&& other) {
    size = other.size;
    data = other.data;

    other.size = 0;
    other.data = nullptr;

    cout << "Move constructor called" << endl;
}
这段很重要：
other.data = nullptr;





6. 什么是移动赋值运算符、

第一 检查是不是自己给自己赋值
第二 释放自己原来的资源
第三 接管 other 的资源
第四  把 other 置空
第五 返回自己

7. Rule of 5 是什么？

C++11 之后，增加了移动语义。

所以资源管理类通常要考虑 5 个函数：

1. 析构函数
2. 拷贝构造函数
3. 拷贝赋值运算符
4. 移动构造函数
5. 移动赋值运算符

和 BlockManager 的关系

你的 BlockManager 现在管理的是：

unordered_map<int, Block> block_table;
queue<int> free_block_ids;

这些 STL 容器本身已经帮你管理好资源了，所以你现在不一定要自己写析构、拷贝、移动。

但是以后如果你写：