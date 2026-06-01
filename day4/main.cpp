#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


struct Block{
    int id;
    bool is_used;
    int token_count;

};

void get_queue(queue<int>& free_blocks, int times){
    // if 判断只执行一次
    while(times>0 && !free_blocks.empty()){
        int block_id = free_blocks.front();
        free_blocks.pop();
        times--;
        cout<<"Allocated block id: " << block_id <<endl;

    }
}
void check_id(unordered_map<int, Block> block_table, int id){
    if(block_table.find(id) != block_table.end()){
        cout<<"Block id "<<id<<" exists in the table."<<endl;
    }else{
        cout<<"Block id "<<id<<" does not exist in the table."<<endl;
    }
}

void allocate_block(unordered_map<int, Block>& block_table, queue<int>& free_blocks) {
    if (!free_blocks.empty()) {
        int block_id = free_blocks.front();
        //哦 就是这个block_id 是作为key 不是block_table 里的第几个  因为id不一定就是table 里的第几个对
        free_blocks.pop();

        cout << "Allocating block id: " << block_id << endl;

        block_table[block_id].is_used = true;
        block_table[block_id].token_count = 128;

        cout << "Block " << block_id
             << " allocated with token count: "
             << block_table[block_id].token_count << endl;
    } else {
        cout << "No free block available" << endl;
    }
}
//unordered_map 里，.end() ,它不是最后一个元素，而是一个特殊标记，表示“没找到”或者“遍历结束”。
void release_block(unordered_map<int, Block>& block_table, queue<int>& free_blocks, int block_id){
    if(block_table.find(block_id)!= block_table.end() && block_table[block_id].is_used){
        // 就算block_tbale 里有这个id,但可能就是free 状态
        block_table[block_id].is_used = false;
        block_table[block_id].token_count = 0;
        free_blocks.push(block_id);
        cout<<"Block "<<block_id<<" released and added back to free blocks."<<endl;
    }else{
        cout<<"Block "<<block_id<<" cannot be released (not found or already free)."<<endl;
    }

}

void print_all_blcok(const unordered_map<int,Block>& block_table){
    for(const auto& pair : block_table){
        cout<<"block id: "<<pair.second.id<<endl;
        cout<<"is used : "<< pair.second.is_used<<endl;
        cout<<"token count: "<<pair.second.token_count<<endl;
    }
}





int main(){

    //unordered_map 不是无限大，它是动态增长的 key-value 表；插入多少就有多少，但受内存限制。
    unordered_map<int, Block> block_table;

    queue<int> free_blocks;

    Block b0, b1, b2,b3;
    b0.id=0;
    b0.is_used=false;
    b0.token_count=0;

    b1.id=100;
    b1.is_used=false;   
    b1.token_count=0;

    b2.id=200;
    b2.is_used=false;   
    b2.token_count=0;

    b3.id=300;
    b3.is_used=false;
    b3.token_count=0;

    block_table[0] = b0;
    block_table[100] = b1;    
    block_table[200] = b2;
    block_table[300] = b3;
    // block_id 应该被放进去  在block table 里 和free——block里
    free_blocks.push(0);
    free_blocks.push(100);    
    free_blocks.push(200);
    free_blocks.push(300);
    
    
    allocate_block(block_table, free_blocks);
    print_all_blcok(block_table);

    release_block(block_table, free_blocks, 0);
    print_all_blcok(block_table);

    allocate_block(block_table, free_blocks);
    print_all_blcok(block_table);
    // 这个时候allocate的 id 就是1了 因为 0被释放了  又被放回去了最后 
    
    
    


}