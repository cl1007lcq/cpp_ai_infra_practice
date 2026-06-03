#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>

using namespace std;




struct Block {
    int id;
    bool is_used;
    int token_count;

};
class Blockmanager{

    private:
    unordered_map<int, unique_ptr<Block>> block_table; 
    queue<int> free_blocks;

     /*为什么构造函数适合初始化所有 block？
     因为创建 BlockManager 时，它就应该处于可用状态。
     构造函数可以自动创建所有 block，并把它们放进空闲队列。
     */
    
    public:
    Blockmanager(int num_blocks){
        for(int i = 0; i < num_blocks; i++){
            Block block;
            block.id = i;
            block.is_used = false;
            block.token_count = 0;
            block_table[i] = make_unique<Block>(block);
            free_blocks.push(i);//队列是先进先出
            /*push()  从后面进
            front() 从前面看
            pop()   从前面出*/
        }

    } 
    void print_status(){
        for(const auto& pair : block_table){
            Block block = *(pair.second);
            cout << "Block ID: " << block.id
                    << ", Is Used: " << block.is_used
                    << ", Token Count: " << block.token_count << endl;

        }
    }
    //因为它操作的是 BlockManager 自己内部的 free_block_ids 和 block_table。
    //这些数据已经是成员变量，不需要从外面传进来。
    void allocate_block() {
        if (!free_blocks.empty() ) {
            int block_id = free_blocks.front();
            free_blocks.pop();

            cout << "Allocating block id: " << block_id << endl;

            block_table[block_id]->is_used = true;
            block_table[block_id]->token_count = 128;
        } else {
            cout << "No free block available" << endl;
        }
    }
    //为什么 release_block(int block_id) 需要参数？  因为释放时，外部必须告诉 manager 要释放哪个 block。
    void release_block(int block_id){
        if(block_table.find(block_id)!= block_table.end() && block_table[block_id]->is_used){
            block_table[block_id]->is_used = false;
            block_table[block_id]->token_count = 0;
            free_blocks.push(block_id);
            cout<<"Block "<<block_id<<" released and added back to free blocks."<<endl;
        }else{
            cout<<"Block "<<block_id<<" cannot be released (not found or already free)."<<endl;
        }

    }


    int total_block_count(){

        return block_table.size();//总的block数量

    }

   int free_block_count(){

        return free_blocks.size();//返回当前空闲block的数量

    }

};
//1.构造函数就是创建的时候 会自动创建对象  析构函数是什么？析构函数是在对象销毁时自动执行.
          /*SimpleBuffer 像一个大仓库
           BlockManager 像仓库管理员
           Block 像仓库里的一个货架/格子
           queue 记录哪些格子是空的
           unordered_map 记录每个格子的状态*/

         
class SimpleBuffer{


    private:
        size_t size; // 这块 buffer 有多大。
        char* buffer; // 这个是指针，在堆区申请size个char的连续内存，然后让buffer指向内存

        // buffer 可以理解成：一块连续的内存空间，用来临时存数据。


    public:
        SimpleBuffer(size_t size):size(size), buffer(new char[size]) {
            cout << "SimpleBuffer constructor called, size: " << size << endl;//打印的时候构造多大的buffer
        }

        ~SimpleBuffer() {
            cout << "SimpleBuffer destructor called, size: " << size << endl;
            delete[] buffer;
        }
        

};
int main(){
        //1 观察构造函数和析构函数
        {SimpleBuffer buf(1024); }// 创建一个 SimpleBuffer 对象，大小为 1024 字节
                                // buf 对象在这里超出作用域，析构函数会被自动调用，释放内存

        //2 手动 new/delete
        int* p = new int(10);
        cout << "Value of p: " << *p << endl; // 输出 p 指向的值，即 10
        delete p;

        //3 使用 unique_ptr 管理 int

        unique_ptr<int> uniquePter = make_unique<int>(20);// 创建一个 unique_ptr，指向一个值为 20 的 int
        cout << "Value of uniquePter: " << *uniquePter << endl; // 输出 uniquePter 
        

        //4 unique_ptr 管理 Block 对象
        cout<< "unique_ptr 管理 Block 对象" << endl;
        unique_ptr<Block> blockPtr = make_unique<Block>();
        blockPtr->id = 1;
        blockPtr->is_used = false;
        blockPtr->token_count = 0;
        cout << "Block ID: " << blockPtr->id << ", is_used: " << blockPtr->is_used << ", token_count: " << blockPtr->token_count << endl;
        
        //5 使用 move 转移 unique_ptr
        unique_ptr<Block> anotherBlockPtr = move(blockPtr); // 转移所有权
        if (!blockPtr) {
            cout << "blockPtr is now empty after move." << endl;
        }
        cout << "Another Block ID: " << anotherBlockPtr->id << ", is_used: " << anotherBlockPtr->is_used << ", token_count: " << anotherBlockPtr->token_count << endl;
         
        //6 shared_ptr 引用计数 // raii Resource Acquisition Is Initialization
        cout << "shared_ptr 引用计数" << endl;
        shared_ptr<Block> sharedBlockPtr = make_shared<Block>();
        //shared_ptr 可以和 shared_ptr 共享；也可以接收 unique_ptr move 过来的对象，但这叫“所有权转移”，不是共享。
        sharedBlockPtr->id = 2;
        sharedBlockPtr->is_used = true;
        sharedBlockPtr->token_count = 10;
        cout << "Shared Block ID: " << sharedBlockPtr->id << ", is_used: " << sharedBlockPtr->is_used << ", token_count: " << sharedBlockPtr->token_count << endl;
        shared_ptr<Block> anotherSharedBlockPtr = sharedBlockPtr; // 共享所有权
        cout<<"the shared block ptr use count:"<<sharedBlockPtr.use_count()<<endl; // 输出引用计数，即 2
    return 0;


}

































