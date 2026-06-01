#include <iostream>
using namespace std;

struct Block{
    int id;
    bool is_used;
    int token_count;

};
void fake_use_block(Block b){

    b.is_used = true;
    b.token_count = 999;
}

void use_block(Block& b){
    b.is_used = true;
    b.token_count = 999;

}
void print_block(const Block& b){

    //在 print_block 里面不允许修改：

    cout<<"id is "<<b.id<<endl;
    cout<<"used or not "<<b.is_used<<endl;
    cout<<"token count is "<<b.token_count<<endl;

}

int main(){
    // assignment 1
    Block b;
    b.id = 0;
    b.is_used = false;
    b.token_count = 0;
    // assignment 2

    cout<<"id is "<<b.id<<endl;
    cout<<"used or not "<<b.is_used<<endl;
    cout<<"token count is "<<b.token_count<<endl;
    cout<<&b<<endl;
    //assignment 3

    Block* ptr;
    ptr = &b;
    ptr->is_used = true;
    ptr->token_count = 128;
     cout<<"id is "<<b.id<<endl;
    cout<<"used or not "<<b.is_used<<endl;
    cout<<"token count is "<<b.token_count<<endl;

    // assignment 4
    Block c;
    c.id = 3;
    c.is_used = false;
    c.token_count = 0;
    fake_use_block(c);
    cout<<"id is "<<c.id<<endl;
    cout<<"used or not "<<c.is_used<<endl;
    cout<<"token count is "<<c.token_count<<endl;

    //引用的时候 这只是引用block 所以还是传block本身才对

    use_block(c);
    cout<<"id is "<<c.id<<endl;
    cout<<"used or not "<<c.is_used<<endl;
    cout<<"token count is "<<c.token_count<<endl;
    

    cout<<"assignment 6"<<endl;
    print_block(c);




}