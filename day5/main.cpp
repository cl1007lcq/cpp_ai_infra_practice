#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/*你的疑问很好：public/private 不是让数据“永远不改变”，而是控制“谁有资格改”。

核心区别是：

private：外部不能直接乱改内部数据
public：外部只能通过你提供的函数来改*/


class Printer{
    public :
    void printer(){
        cout <<"Hello world"<<endl;
    }
};

class Counter{
    private:
    int count;
    public:
    Counter(int initial_value)  {
        count = initial_value;  // Constructor to initialize count
    } 
    void increase(){
        count++;
    }
    void decrease(){
        count--;
    }
    void printCount(){
        cout << "Current count: " << count << endl;
    }

};

struct Block{

    int id;
    bool is_used;
    int token_count;

};
class Blockmanager{

    private:
    unordered_map<int, Block> block_table; 
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
            block_table[i] = block;
            free_blocks.push(i);//队列是先进先出
            /*push()  从后面进
            front() 从前面看
            pop()   从前面出*/
        }

    } 
    void print_status(){
        for(const auto& pair : block_table){
            Block block = pair.second;
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

            block_table[block_id].is_used = true;
            block_table[block_id].token_count = 128;
        } else {
            cout << "No free block available" << endl;
        }
    }
    //为什么 release_block(int block_id) 需要参数？  因为释放时，外部必须告诉 manager 要释放哪个 block。
    void release_block(int block_id){
        if(block_table.find(block_id)!= block_table.end() && block_table[block_id].is_used){
            block_table[block_id].is_used = false;
            block_table[block_id].token_count = 0;
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

int main(){
    // 1. 访问控制：public 成员可以被类外部访问，而 private 成员只能在类内部访问。这有助于保护数据不被外部直接修改。
    Printer pr;
    pr.printer();
    //2. 封装：通过将数据成员设为 private，并提供 public 的成员函数来访问和修改这些数据，可以实现封装。这有助于隐藏实现细节，提供更清晰的接口。


    Blockmanager manager(5);
    manager.print_status();
    manager.allocate_block();
    manager.allocate_block();
    manager.print_status();
    manager.release_block(0);
    manager.print_status();


    



    



    return 0; 
}



































