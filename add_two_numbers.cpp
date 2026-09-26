/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool carrier = false;
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* node = nullptr;
        int l1val = 0;
        int l2val = 0;
        if (l1 != nullptr) {
            l1val = l1->val;
        }
        if (l2 != nullptr) {
            l2val = l2->val;
        }
        int val = carrier ? l1val + l2val + 1 : l1val + l2val;
        carrier = (val) >= 10 ? true : false;
        val = (val) % 10;
        if (l1 != nullptr && l2 != nullptr) {
            node = new ListNode(val, addTwoNumbers(l1->next, l2->next));
        } else if (l1 == nullptr && l2 != nullptr) {
            node = new ListNode(val, addTwoNumbers(nullptr, l2->next));
        } else if (l1 != nullptr && l2 == nullptr) {
            node = new ListNode(val, addTwoNumbers(l1->next, nullptr));
        } else {
            if (val) node = new ListNode(1);
        }
        return node;
    }
};
