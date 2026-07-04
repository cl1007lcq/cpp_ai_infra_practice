#include <iostream>
#include "BlockManager.h"

using namespace std;

BlockManager::BlockManager(int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        Block block;
        block.id = i;
        block.is_used = false;
        block.token_count = 0;

        blocks[i] = make_unique<Block>(block);
        free_blocks.push(i);
    }
}
/*分配一个 block，并立刻修改这个 block 的状态”
它没有要记录“这个 block 属于哪个 request”，所以不需要往 request_to_blocks 里插。*/
void BlockManager::allocate_block() {
    if (free_blocks.empty()) {
        cout << "No free block available." << endl;
        return;
    }

    int block_id = free_blocks.front();
    free_blocks.pop();

    blocks[block_id]->is_used = true;
    blocks[block_id]->token_count = 128;

    cout << "Block " << block_id << " allocated successfully." << endl;
}


//如果没找到这个 block_id” 可以把它理解成一种“查找失败标记”。
void BlockManager::release_block(int block_id) {
    auto it = blocks.find(block_id);

    if (it == blocks.end()) {
        cout << "Block " << block_id << " does not exist." << endl;
        return;
    }

    if (!it->second->is_used) { // ！的优先级最低
        cout << "Block " << block_id << " is already free." << endl;
        return;
    }

    it->second->is_used = false;
    it->second->token_count = 0;
    free_blocks.push(block_id);

    cout << "Block " << block_id << " released successfully." << endl;
}


void BlockManager::print_status() {
    for (const auto& pair : blocks) {
        cout << "Block ID: " << pair.second->id
             << ", is_used: " << pair.second->is_used
             << ", token_count: " << pair.second->token_count
             << endl;
    }
}

int BlockManager::total_block_count() {
    return blocks.size();
}

int BlockManager::free_block_count() {
    return free_blocks.size();
}
//request id 代表 第几个请求的编号
/*2. 
没找到如果这个 request_id 不存在，find(request_id) 会返回：

request_to_blocks.end()
也就是“尾后迭代器”，可以理解成一个“没找到标记”。
*/
void BlockManager::allocate_blocks_for_request(int request_id, int num_blocks){
    //要插入的时候 不等于说明 找到了 已经存在了 request id存在了
    if (request_to_blocks.find(request_id) != request_to_blocks.end()) {
        cout << "Request already exists" << endl;
        return;
    }

    if(free_blocks.size() < num_blocks){
        cout << "not enough free block"<<endl;
        return;
    }
    //区别是“一个是临时列表，一个是请求编号”。
    vector<int> allocated_blocks;

    //循环 填满所有需要的block
    for(int i =0; i< num_blocks; i++){
        int block_id = free_blocks.front();
        free_blocks.pop();

        blocks[block_id]->is_used = true;
        blocks[block_id]->token_count = 128;
        // 每一次都把修改的block，插进存储block的 unordered_map blocks中
        allocated_blocks.push_back(block_id);

    }

     //请求编号  ->  这个请求对应的 block 列表，这个时候上面的vector<int>收集齐了，request id 是key，直接把新的做value
        request_to_blocks[request_id] = allocated_blocks;
        cout << "Request " << request_id << " allocated "
     << allocated_blocks.size() << " blocks" << endl;

}


void BlockManager::free_for_request(int request_id){

    auto it = request_to_blocks.find(request_id);
    // 删除的时候 == 说明没找到 ，是不对要终止的情况
     if (it == request_to_blocks.end()) {
        cout << "Request not found" << endl;
        return;
    }
    //把 it 指向的那个 request 对应的 block 列表 取出来，复制给一个新的 vector<int> 变量 allocated_blocks。
    vector<int> allocated_blocks = it->second;

    for(int block_id : allocated_blocks){
        blocks[block_id]->is_used = false;
        blocks[block_id]->token_count = 0;
        free_blocks.push(block_id);
    }

     request_to_blocks.erase(request_id);

    cout << "Request " << request_id << " freed" << endl;


     
}
/*遍历 request_to_blocks 里的每一个键值对。”
这里每次拿到的 item，其实就是 map 里的一项，比如
item = {1001, {0, 1, 2}}
其中：
item.first 是 key，也就是 request_id
item.second 是 value，也就是 vector<int>*/
void BlockManager::print_request_status() {
    if (request_to_blocks.empty()) {
        cout << "No active requests" << endl;
        return;
    }

    for (const auto& item : request_to_blocks) {
        cout << "Request " << item.first << ": ";

        for (const auto& block_id : item.second) {
            cout << block_id << " ";
        }

        cout << endl;
    }
}






