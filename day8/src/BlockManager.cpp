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
    blocks[block_id]->token_count = 0;

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
    //去 map 里找这个 key，找到就给你一个指向它的迭代器；找不到就给你 end()。”
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
        blocks[block_id]->token_count = 0;
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
void BlockManager::print_request_number() {
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


int BlockManager::acquire_free_block() {
    if(free_blocks.empty()){
        cout <<"No free block available."<<endl;
        return -1;
    }
    int block_id = free_blocks.front();
    free_blocks.pop();

    blocks[block_id]->is_used = true;
    blocks[block_id]->token_count = 0;

    return block_id;


}
//所有函数在设计的时候 应该都是可以直接调用的，判断是否成功调用或者失败 应该在调用函数内部实现
bool BlockManager::append_token(int request_id){
    //request_it = request_to_blocks.find(1001); 举例子，找到的是 request_it -> 1001 ----> [0,2,5]
    auto request_it = request_to_blocks.find(request_id);
    //Request 不存在
    if(request_it == request_to_blocks.end()){
        cout << "Request not found" << endl;
        return false;
    }
    // Request 存在，但没有 block
    if(request_it->second.empty()){
        cout << "Request has no allocated blocks" << endl;
        return false;
    }
    //找最后一个 block
    int last_block_id = request_it->second.back();

    //block iterator = block it ,find返回的不是 block,而是指向 map的某一项的指针 也叫迭代器，
    //返回不了block，因为map里存的是key-value
    auto block_it = blocks.find(last_block_id);
    /*1. blocks[last_block_id]
     如果 key 不存在，会尝试创建一个新元素。
    2. blocks.find(last_block_id)
     只是查，不会创建新元素。确实这两个都是block id 是一样的东西 但是block  统一要求用unodermap的blocks改*/
    //拿block_it去找 block，找不到就返回 blocks.end()，也就是“尾后迭代器”，可以理解成一个“没找到标记”。
    if(block_it == blocks.end()){
        cout << "Block not found" << endl;
        return false;
    }
    if(block_it->second == nullptr){
        cout << "Block pointer is null" << endl;
        return false;
    }
    //判断结束取block 
    Block& block =*(block_it->second);
    //判断最后一个block 有没有空间
    if(block.token_count < BLOCK_CAPACITY){
        block.token_count++;
        cout << "Token appended to block " << block.id << endl; 
        return true;
    }

    cout<< "not enough last block capacity, need to acquire a new block" << endl;
    int new_block_id = acquire_free_block();

    //把新token放进新block里
    blocks[new_block_id]->token_count = 1;
    //把新申请到的 block id，追加到当前 request 的 block 列表末尾。
    request_it->second.push_back(new_block_id);

    cout << "New block " << new_block_id
     << " allocated for request " << request_id << endl;

    return true;

}

void BlockManager::print_request_detail(int request_id) {

    auto request_it = request_to_blocks.find(request_id);
    // 1. 检查 request 是否存在
    if (request_it == request_to_blocks.end()) {
        cout << "Request not found" << endl;
        return;
    }

    cout << "Request " << request_id << " details:" << endl;
    // 2. 遍历该 request 的 block id
    for (int block_id : request_it->second) {
        auto block_it = blocks.find(block_id);
        
        /*如果在 blocks 这个 map 里，没有找到当前这个 block_id 对应的 block，
        就打印一条提示，然后跳过这次循环，继续处理下一个 block。*/
        
        if (block_it == blocks.end()) {
            cout << "Block " << block_id << " not found" << endl;
            continue;
        }

        cout << "Block ID: " << block_it->second->id
             << ", token_count: " << block_it->second->token_count
             << ", capacity: " << BLOCK_CAPACITY
             << endl;
    }
}
















