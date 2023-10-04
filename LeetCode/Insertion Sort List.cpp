#include <iostream>

struct ListNode {
 int val;
 ListNode *next;
 ListNode() : val(0), next(nullptr) {}
 ListNode(int x) : val(x), next(nullptr) {}
 ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* save = head;
        if (head == nullptr){
            return nullptr;
        }
        while (head != nullptr){
            ListNode* tmp = head;
            tmp = tmp->next;
            while(tmp != nullptr) {
                if (head->val > tmp->val) {
                    int acc = head->val;
                    head->val = tmp->val;
                    tmp->val = acc;
                    std::cout << "List now: ";
                    printList(head);
                }
                tmp = tmp->next;
            }
            head = head->next;
        }
        return save;
    }


};


int main() {

    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    std::cout << "Original List: ";
    printList(head);

    // Сортируем список
    Solution solution;
    head = solution.insertionSortList(head);

    std::cout << "Sorted List: ";
    printList(head);

    return 0;
}
