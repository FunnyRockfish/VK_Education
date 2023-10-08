#include <iostream>
using namespace::std;

struct DinamicCircBuf{
    int size = 0;
    int* buffer = new int[size];
    DinamicCircBuf(int size){
        this->size = size + 10;
        buffer = new int[size];
    }
private:
    int head = 0;
    int tail= 0;
    int countOfElements = 0;
public:
    int popFront(){
        int elem = buffer[head];
        //cout << "HEAD IS NOW = "<< head << endl;
        if (countOfElements > 0){
            head = (head+1)%(size); // меняем голову
            //printBuf();
        }else{
            return -1;
        }
        countOfElements--;
        return elem;
    }
    int popBack(){
        if (countOfElements > 0){
            tail = (tail-1)%(size); // меняем хвост
        }
        else{
            return -1;
        }
        int elem = buffer[tail];
        countOfElements--;
        return elem;
    }
    void pushFront(int num){
        buffer[head] = num;
        head = (head-1)%size;
        countOfElements++;
    }
    void pushBack(int num){
        buffer[tail] = num;
        tail = (tail + 1) % size;
        countOfElements++;
        if (countOfElements >= size) {
            head = (head + 1) % size;  // Сдвигаем голову, так как буфер полный
        }
    }
    void printBuf(){
        int current = head;
        //cout << "COUNT OF ELEMS IS = " << countOfElements << endl;
        for (int i = 0; i < countOfElements +1 ; i++) {
            cout << buffer[i] << ' ';
            //current = (current + 1) % size;
        }
    }
    ~DinamicCircBuf() {
        delete[] buffer;
    }
};

int main() {

    //buf.pushBack(44);
    //buf.pushBack(50);
    //buf.printBuf();
    //cout << buf.popBack() << endl;

    int command = 0;
    int countOfCommands = 0;
    int expectedNumber;
    cin >> countOfCommands;
    DinamicCircBuf buf(countOfCommands);
    int flag = 0;
    for (int i = 0; i < countOfCommands; i++){
        cin >> command;
        cin >> expectedNumber;
       // cout << "COMMAND = " << command << endl;
        //cout << "NUMBER = " << expectedNumber << endl;
        if (command == 2){
            int elem = buf.popFront();
            //cout << "ELEM FROM HEAD = " << elem << endl;
            if (elem != expectedNumber){
                // << "NO" << endl;
                flag = 1;
            }
        }
        if (command == 3){
            buf.pushBack(expectedNumber);
            //buf.printBuf();
        }
        if (command == 1){
            buf.pushFront(expectedNumber);
        }
        if (command == 4){
            int elem = buf.popBack();
            //cout << "ELEM FROM HEAD = " << elem << endl;
           // buf.printBuf();
            if (elem != expectedNumber){
                //cout << "NO" << endl;
                flag = 1;
            }
        }
    }
    if (flag == 0){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }

    return 0;
}
