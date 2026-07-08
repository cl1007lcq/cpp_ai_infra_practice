#include <queue>
#include <unordered_map>
#include <memory>
#include "Block.h"
#include <vector>
#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H



class BlockManager {
    private:
    std::queue<int> free_blocks;
    std::unordered_map<int, std::unique_ptr<Block>> blocks;
    std::unordered_map<int, std::vector<int>> request_to_blocks;

    public:
    static const int BLOCK_CAPACITY = 4;

    BlockManager(int num_blocks);

    void allocate_block();

    void release_block(int block_id);

    void print_status();

    int total_block_count();

    int free_block_count();

    void allocate_blocks_for_request(int request_id, int num_blocks);

    void free_for_request(int request_id);

    void print_request_number();

    int acquire_free_block();

    bool append_token(int request_id);

    void print_request_detail(int request_id);

    


};
/*key: request_id, value: 这个 request 使用的 block_id 列表*/
/*
block_table	保存所有 Block 的真实状态
free_block_ids	保存当前空闲的 block id
request_to_blocks	保存每个 request 占用了哪些 block 
*/


#endif




