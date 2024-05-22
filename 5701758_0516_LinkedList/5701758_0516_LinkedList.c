#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return h;
    }
    p->data = value;
    p->link = h;
    return p;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    if (pre == NULL) {
        fprintf(stderr, "Insert parameter error: pre == NULL\n");
        return head;
    }
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return head;
    }
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
    if (pre == NULL || pre->link == NULL) {
        fprintf(stderr, "Delete parameter error\n");
        return head;
    }
    ListNode* remove = pre->link;
    pre->link = remove->link;
    free(remove);
    return head;
}

ListNode* delete_first(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode* remove = head;
    head = remove->link;
    free(remove);
    return head;
}

void print_list(ListNode* head) {
    while (head != NULL) {
        printf("[%d] ", head->data);
        head = head->link;
    }
    printf("\n");
}

void debug_list(ListNode* head) {
    printf("Current list: ");
    print_list(head);
}

int main() {
    ListNode* head = NULL; // 초기화
    int choice = 0;
    int n1, n2;
    while (1) {
        printf("1. 리스트에 숫자 추가\n");
        printf("2. 리스트에서 숫자 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("리스트에 추가할 숫자를 입력하세요 : ");
            scanf_s("%d", &n1);
            printf("리스트에 추가할 숫자의 위치(이전 노드)를 입력하세요 : ");
            scanf_s("%d", &n2);
            if (n2 == 0) {
                head = insert_first(head, n1);
            }
            else {
                ListNode* pre = head;
                for (int i = 0; i < n2 - 1 && pre != NULL; i++) {
                    pre = pre->link;
                }
                if (pre != NULL) {
                    head = insert(head, pre, n1);
                }
                else {
                    fprintf(stderr, "Invalid position\n");
                }
            }
            debug_list(head);
            break;
        case 2:
            printf("리스트에서 삭제할 숫자의 위치를 입력하세요 : ");
            scanf_s("%d", &n2);
            if (n2 == 0) {
                head = delete_first(head);
            }
            else {
                ListNode* pre = head;
                for (int i = 0; i < n2 - 1 && pre != NULL; i++) {
                    pre = pre->link;
                }
                if (pre != NULL && pre->link != NULL) {
                    head = delete(head, pre);
                }
                else {
                    fprintf(stderr, "Invalid position\n");
                }
            }
            debug_list(head);
            break;
        case 3:
            printf("리스트를 출력합니다.\n");
            print_list(head);
            break;
        case 0:
            exit(0);
        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }
    return 0;
}