#include <iostream>
using namespace::std;

class twix{
public:
    int* findBrother(int* arr1, int size1, int* arr2, int size2){
        int resultSize = size1;
        int* resultArr = new int [resultSize];
        for (int i =0; i < size1; i++){
            int num = arr1[i];
            pair<int, int> borders = ExpFind(arr2, size2, num);
            int start = borders.first;
            int end = borders.second;
            int BS = binarySearch(arr2, start, end, num);
            //cout << "BS RETURN " << BS << endl;
            resultArr[i] = BS;
        }
        return resultArr;
        delete resultArr;
    }

    int binarySearch(int* arr, int start, int end, int target){
        int mid = 0;
        while (start < end){
            if (start + 1 == end){
                if (abs(arr[start] - target) <= abs(arr[end] - target)){
                    return start;
                }else{
                    return end;
                }
            }
            mid = (start + end)/2;
            if (arr[mid] < target){
                start = mid;
            }
            else{
                end = mid;
            }
        }
    }

    std::pair<int, int> ExpFind(const int* arr, int size, int target) {
        int i = 0;
        int start = 0;
        int end = 1;
        if (size==1){
            return std::make_pair(0, 0);
        }

        if (target < arr[0]){
            return std::make_pair(0, 1);
        }

        while (end < size - 1) {

            if (target < arr[(start + end) / 2]) {
                break;
            }
            //start = end;
            i++;
            end = end<<1;
        }
        end = min(end, size - 1);
        return std::make_pair(start, end);
    }
};

int main() {
    int size1 = 0;
    int size2 = 0;
    cin >> size1;
    int arr1[size1];
    for (int i = 0; i < size1; i++){
        cin >> arr1[i];
    }
    cin >> size2;
    int arr2[size2];
    for (int i = 0; i < size2; i++){
        cin >> arr2[i];
    }
        twix search;
        int *ans = new int[size1];
        ans = search.findBrother(arr2, size2, arr1, size1);
        for (int i = 0; i < size2; i++) {
            cout << ans[i] << ' ';
        }
        delete ans;
    return 0;
}
