#include <cstring>   // memcpy
#include <iostream>  // cout, endl
using namespace std;

/*方式           复制资源          转移资源
创建新对象        拷贝构造          移动构造
已有对象赋值      拷贝赋值          移动赋值
*/

// the right way to write the copy function

class SimpleBuffer {
private:
    static int next_id;  // 静态变量：用来给每个对象自动分配不同的 id
    int id;              // 当前对象编号，方便观察是谁在构造/析构
    size_t size;         // 当前 buffer 的大小
    char* data;          // 指向堆区申请出来的 char 数组

public:
    // 1. 普通构造函数
    // 创建对象时调用，例如：SimpleBuffer buf1(100);
    SimpleBuffer(size_t size) {
        this->id = next_id++;
        this->size = size;  // 通过 this 这个地址，找到当前对象里面的 size 成员变量
        this->data = new char[size];

        cout << "Buffer " << id << " constructor called, size: " << size << endl;
    }

    // 2. 拷贝构造函数
    // 它只在“创建新对象时复制”调用：
    /*
    SimpleBuffer buf1(100);
    SimpleBuffer buf2 = buf1;  // 调用拷贝构造函数
    */
    SimpleBuffer(const SimpleBuffer& other) {
        this->id = next_id++;  // 新对象应该有自己的新 id，不复制 other 的 id
        this->size = other.size;
        this->data = new char[other.size];

        // 把一块内存的数据，原封不动地复制到另一块内存
        // memcpy(目标地址, 源地址, 复制字节数);
        memcpy(this->data, other.data, other.size);

        cout << "Buffer " << id << " copy constructor from Buffer "
             << other.id << ", size: " << size << endl;
    }

    // 拷贝构造函数：新对象还没出生，用别人来创建我。
    // 拷贝赋值运算符：我已经存在了，现在把我改成别人。
    // 3. 拷贝赋值运算符
    SimpleBuffer& operator=(const SimpleBuffer& other) {
        if (this == &other) {
            return *this;
        }

        delete[] this->data;

        // 赋值时 id 不变，因为“我还是我”，只是内容变成 other 的内容
        this->size = other.size;
        this->data = new char[other.size];
        memcpy(this->data, other.data, other.size);

        cout << "Buffer " << id << " copy assignment from Buffer "
             << other.id << ", size: " << size << endl;

        return *this;
    }

    // 4. 移动构造函数
    // 这里的 && 不是两个取地址。它是一个整体，叫：右值引用
    // 意思是：专门接收临时对象 / 即将被移动的对象。
    SimpleBuffer(SimpleBuffer&& other) {
        this->id = next_id++;  // 新对象有自己的新 id
        this->size = other.size;
        this->data = other.data;

        other.size = 0;
        other.data = nullptr;

        cout << "Buffer " << id << " move constructor from Buffer "
             << other.id << ", size: " << size << endl;
    }

    // 5. 移动赋值运算符
    SimpleBuffer& operator=(SimpleBuffer&& other) {
        if (this == &other) {
            return *this;
        }

        delete[] this->data;

        // 赋值时 id 不变，因为对象本身没变，只是接管 other 的资源
        this->size = other.size;
        this->data = other.data;

        other.size = 0;
        other.data = nullptr;

        cout << "Buffer " << id << " move assignment from Buffer "
             << other.id << ", size: " << size << endl;

        return *this;
    }

    // 6. 析构函数
    ~SimpleBuffer() {
        if (data != nullptr) {
            cout << "Buffer " << id << " destructor called, releasing memory, size: "
                 << size << endl;
            delete[] data;
        } else {
            cout << "Buffer " << id << " destructor called, no memory to release, size: "
                 << size << endl;
        }
    }
};

// 静态成员变量必须在类外初始化
int SimpleBuffer::next_id = 1;

int main() {
    cout << "===== 1. Normal constructor =====" << endl;
    SimpleBuffer buf1(100);

    cout << "\n===== 2. Copy constructor =====" << endl;
    SimpleBuffer buf2 = buf1;

    cout << "\n===== 3. Copy assignment operator =====" << endl;
    SimpleBuffer buf3(50);
    buf3 = buf1;

    cout << "\n===== 4. Move constructor =====" << endl;
    SimpleBuffer buf4 = move(buf1);

    cout << "\n===== 5. Move assignment operator =====" << endl;
    SimpleBuffer buf5(200);
    buf5 = move(buf4);

    return 0;
}