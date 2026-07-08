#include <iostream>
#include "include/BlockManager.h"

using namespace std;

int main(){
     /*    cmake --build build  改完代码用这个重新建构
     .\build\BlockManagerTest.exe    */

    BlockManager manager(3);

    manager.allocate_blocks_for_request(1001, 1);

    manager.append_token(1001);
    manager.append_token(1001);
    manager.append_token(1001);
    manager.append_token(1001);
    manager.append_token(1001);


    cout << "After request 1001 append 5 times:" << endl;
    manager.print_request_number();
    manager.print_request_detail(1001);
    cout << "Total blocks: " << manager.total_block_count() << endl;
    manager.print_status();

    manager.free_for_request(1001);

    cout << "\nAfter free request 1001:" << endl;
    manager.print_request_number();
    manager.print_status();

    manager.allocate_blocks_for_request(1002, 1);
    manager.append_token(1002);

    cout << "\nAfter request 1002 allocate and append:" << endl;
    manager.print_request_number();
    manager.print_request_detail(1002);
    manager.print_status();

    return 0;


}






























