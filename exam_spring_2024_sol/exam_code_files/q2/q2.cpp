#include <iostream>
#include <string>
#include <stdexcept>
#include "MemManager.h"
#include <memory>


int main(){
    int numBlocks, blockSize;

    std::cin >> numBlocks >> blockSize;

    // Creating a memory manager
    MemManager<int> manager(numBlocks, blockSize);

    // Allocating a blok to be used as an array
    int* arr = manager.acquire();

    for(int i = 0; i < blockSize; i++){
        std::cin >> arr[i];
    }

    // Allocating another block
    int *arr2 = manager.acquire();

    // not on the original question, but neccessary to pass compilation
    for(int i = 0; i < blockSize; i++){
        std::cin >> arr2[i];
    }
    int *arr3 = manager.acquire();
    for(int i = 0; i < blockSize; i++){
        std::cin >> arr3[i];
    }

    // some more code that uses arr and arr2

    // Releasing the blocks back to the manager
    manager.release(arr);
    manager.release(arr2);

    return 0;
}