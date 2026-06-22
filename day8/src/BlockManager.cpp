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