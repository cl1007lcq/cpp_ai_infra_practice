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
    if (!free_blocks.empty()) {
        int block_id = free_blocks.front();
        free_blocks.pop();

        cout << "allocating id number is " << block_id << endl;
        blocks[block_id]->is_used = true;
        blocks[block_id]->token_count = 128;
    } else {
        cout << "no free space" << endl;
    }
}

void BlockManager::release_block(int block_id) {
    if (blocks.find(block_id) != blocks.end() && blocks[block_id]->is_used) {
        blocks[block_id]->is_used = false;
        blocks[block_id]->token_count = 0;
        free_blocks.push(block_id);

        cout << "Block " << block_id << " released and added back to free blocks." << endl;
    } else {
        cout << "Block " << block_id << " cannot be released." << endl;
    }
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