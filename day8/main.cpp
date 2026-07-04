#include <iostream>
#include "include/BlockManager.h"

using namespace std;

int main(){
     /*    cmake --build build  改完代码用这个重新建构
     .\build\BlockManagerTest.exe    */
    BlockManager manager(5);

    cout <<  "Before allocation" << endl;
    manager.print_status();
    cout << "Free block count " << manager.free_block_count()<<endl;

    manager.allocate_blocks_for_request(100, 3);

    cout << "\nAfter allocate request 100:" << endl;
    manager.print_status();
    manager.print_request_status();
    cout << "Free block count: " << manager.free_block_count() << endl;

    manager.free_for_request(100);

    cout << "\nAfter free request 100:" << endl;
    manager.print_status();
    manager.print_request_status();
    cout << "Free block count: " << manager.free_block_count() << endl;

    return 0;
















return 0;

}






























