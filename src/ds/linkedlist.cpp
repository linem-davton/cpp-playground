#include <iostream>
#include <thread>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next){};
    ~ListNode() {
        // if cycles then infinite loop
        std::cout << "Deleting " << val << std::endl;
        if (next != nullptr) {
            delete next;
        }
    }
};

void printList(ListNode *head) {
    while (head != nullptr) {
        std::cout << head->val << " " << std::flush;
        head = head->next;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << std::endl;
}

auto reverseList(ListNode *head) -> ListNode * {
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr != nullptr) {
        ListNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

void reorderList(ListNode *head) {
    // Make the list circular my parsing first
    auto *curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = head->next;
    head->next = curr;

    // Now We have 0, n-1, 1,...
    auto *desired = curr->next;

    while (desired->next->next != desired) {
        curr = desired;
        while (curr->next->next != desired) {
            curr = curr->next;
        }
        // Rewire the currrent node which is the last node
        curr->next = desired->next;
        desired->next = curr;
        desired = curr->next;
    }
    //
    desired->next = nullptr;
}

auto main() -> int {
    ListNode *head = nullptr;
    for (int i = 2; i < 10; i += 2) {
        head = new ListNode(i, head);
    }
    printList(head);
    head = reverseList(head);
    printList(head);
    reorderList(head);
    printList(head);
    delete head;
    return 0;
}
