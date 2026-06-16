#include <queue>
#include <unordered_map>
#include <memory>
#include "Block.h"

#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H



class BlockManager {
    private:
    std::queue<int> free_blocks;
    std::unordered_map<int, std::unique_ptr<Block>> blocks;

    public:
    BlockManager(int num_blocks);

    void allocate_block();

    void release_block(int block_id);

    void print_status();

    int total_block_count();

    int free_block_count();


};




#endif




