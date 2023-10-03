class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0){
            return -1;
        }
        int end = nums.size();
        int start = 0;
        int mid = 0;
        while (start < end){
            mid = (start + end) / 2;
            cout << "elem= " <<nums[mid] << endl;
            if (nums[mid] < target){
                start = mid + 1;
            }else if (nums[mid] == target){
                return mid;
            }else{
                end = mid;
            }
            cout << "START = " <<start << endl;
            cout << "END = " <<end << endl;
            cout << "MID = " <<mid << endl;
            cout << " " << endl;
        }
        cout << start << endl;
        cout << end << endl;
        if ((start == nums.size()) || (nums[start] != target)){
            return -1;
        }else{
            return start;
        }
    }
};
