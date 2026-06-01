#include <iostream>
#include <vector>

using namespace std;


struct Block{
    int id;
    bool is_used;
    int token_count;

};
void allocate_first_free_block(vector<Block>& blocks,int target_id){
    for(auto& item : blocks){
        if(item.id == target_id){
            item.is_used = false;
            item.token_count = 0;
            return;  //函数到这里提前结束
        }
    }

}

void release_block_by_id(vector<Block>& blocks){
    for(auto& item : blocks){
        if(item.is_used == false){
            item.is_used = true;
            item.token_count = 128;
            return;  //函数到这里提前结束
        }
    }

}


int main(){

    Block A,B,C;
    A.id = 0;
    A.is_used = false; 
    A.token_count = 0;

    B.id = 1;
    B.is_used = false; 
    B.token_count = 0;

    C.id = 2;
    C.is_used = false; 
    C.token_count = 0;
    
    
    vector<Block> blocks;

    blocks.push_back(A);
    blocks.push_back(B);
    blocks.push_back(C);

    cout<<"blcoks size are "<<blocks.size()<<endl;

    // 无法修改的值 
    //for (const auto& item :blocks){

    //    item.is_used = true ;
    //    item.token_count = 999;
    // }

    //
    //for ( auto& item :blocks){

    //    item.is_used = true ;
    //    item.token_count = 999;
    //}
    //cout << endl ;
    allocate_first_free_block(blocks);


   for (const auto& item :blocks){
        cout << "id is "<< item.id <<endl;
        cout << "used :"<< item.is_used <<endl;
        cout << "tokens : "<< item.token_count <<endl;
    }

    
    





    
  



}