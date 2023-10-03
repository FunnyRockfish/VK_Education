class Solution {
public:
    bool isPowerOfTwo(int n) {
        if ((n == 1) || (n == 2)){
            return true;
        }else if (n%2 == 1){
            return false;
        }
       long int num = 2;
        while (num <= n){
            //n = n>>1;
            if (num == n){
                return true;
            }
            cout << "N = " <<n << endl;
            cout << num << endl;
            num = num<<1;
            if (num == n){
                return true;
            }
        }
        cout << num << endl;
        return false;
    }
};
