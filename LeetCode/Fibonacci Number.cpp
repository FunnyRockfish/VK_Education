class Solution {
public:
    int fib(int n) {
        //vector<int> acc(30);
        int num1 = 0;
        int num2 = 1;
        int num3 = 0;
        //acc[0] = 0;
        //acc[1] = 1;
        if (n == 1){
            return 1;
        }
        for (int i =0; i < n-1; i++){
            num3 = num1 + num2;
            num1 =  num2;
            num2 = num3;
        }
        return num3;
    }
};
