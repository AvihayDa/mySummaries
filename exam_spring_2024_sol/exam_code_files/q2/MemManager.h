#include <exception>

using namespace std;

class NoMoreBlocks : public exception {
public:
    const char* what() const throw(){
        return "No more blocks";
    }
};


template <typename T>
class MemManager {
private:
    T* data;
    int numBlock;
    int blockSize;
    int* follow;

public:
    MemManager(int numBlock, int blockSize){
        if(numBlock <= 0 || blockSize <= 0) throw invalid_argument("Invalid argument");
        this->numBlock = numBlock;
        this->blockSize = blockSize;
        data = new T[numBlock * blockSize];
        
        try{
            follow = new int[numBlock];
        }
        catch(bad_alloc& e){
            delete[] data;
            throw;
        }

        for(int i = 0; i < numBlock; i++){
            follow[i] = 0;
        }
    }

    ~MemManager(){
        delete[] data;
        delete[] follow;
    }
    T* acquire(){
        int t = -1;
        for(int i = 0; i < numBlock; i++){
            if(follow[i] == 0){
                t = i;
                break;
            }
        }
        if(t == -1) throw NoMoreBlocks();
        follow[t] = 1;
        return data + t * blockSize;
    }

    void release(const T* block){
        int i;
        for(i = 0; i < numBlock; i++){
            if(data + i * blockSize == block){
                break;
            }
        }
        follow[i] = 0;
    }
};
