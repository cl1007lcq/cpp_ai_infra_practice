#include <iostream>
#include "include/BlockManager.h"

using namespace std;

int main(){

    BlockManager manager(5);
    cout << "print all status:" << endl;

    manager.print_status();

    cout << "\n3. allocate twice:" << endl;
    manager.allocate_block();
    manager.allocate_block();

    cout << "\n4. status after allocating twice:" << endl;
    manager.print_status();


    cout << "\n5. release block 0:" << endl;
    manager.release_block(0);

    cout << "\n6. status after releasing block 0:" << endl;
    manager.print_status(); 

    cout << "\n7. allocate one more time:" << endl;
    manager.allocate_block();

    cout << "\n8. status after allocating again:" << endl;
    manager.print_status();















return 0;

}






























