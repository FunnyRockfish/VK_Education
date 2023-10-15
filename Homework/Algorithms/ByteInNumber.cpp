#include <iostream>
using namespace::std;

class BytesInInt{
public:
    int ByteInNumber(int num, int pos){
        return ((num>>pos)&1);
    }
};



int main() {
    int number = 0;
    int position = 0;
    cin >> number;
    cin >> position;
    BytesInInt binaryNumber;
    cout << binaryNumber.ByteInNumber(number, position) << endl;
    return 0;
}
