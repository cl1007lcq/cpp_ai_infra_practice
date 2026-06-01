#include <iostream>
using namespace std;

struct Block{
    int id;
    bool is_used;
    int token_count;
};

struct Request{
    int request_id;
    int input_tokens;
    int output_tokens;
    bool is_finished;

};

void print_block(Block a){
cout<<"Block "<<a.id<<endl;
cout<<"Used "<<a.is_used<<endl;
cout<<"token_count "<<a.token_count<<endl;
}

int main() {
    Block a;
    a.id = 0;
    a.is_used = false;
    a.token_count = 0;

    Block free;
    free.id = 1;
    free.is_used = false;
    free.token_count = 0;

    Request request;
    request.request_id = 1001;
    request.input_tokens = 256;
    request.output_tokens = 0;
    request.is_finished = false;

    print_block(b);





  
   


}