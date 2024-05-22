#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value, int* count) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = h;
    *count = 1;
    return p;
}

ListNode* insert(ListNode* head, ListNode* pre, element value, int* count) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (pre == NULL) {
        printf("삽입 위치 오류\n");
        return head;
    }
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    *count += 1;
    return head;
}

ListNode* delete_first(ListNode* h) {
    if (h == NULL) return NULL;
    ListNode* remove = h;
    h = remove->link;
    free(remove);
    return h;
}

ListNode* delete(ListNode* h, ListNode* pre) {
    if (pre == NULL || pre->link == NULL) {
        printf("삭제 위치 오류\n");
        return h;
    }
    ListNode* remove = pre->link;
    pre->link = remove->link;
    free(remove);
    return h;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("%d -> ", h->data);
        h = h->link;
    }
    printf("NULL\n");
}

int main() {
    ListNode* head = NULL;
    int choice, position, value;

    while (1) {
        printf("메뉴:\n");
        printf("1. 숫자를 위치에 삽입\n");
        printf("2. 위치에서 숫자 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("선택하시오: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("삽입할 숫자를 입력하세요: ");
            scanf("%d", &value);
            printf("삽입할 위치를 입력하세요: ");
            scanf("%d", &position);
            int count = 0;
            ListNode* p = head;
            if (position == 0) {
                head = insert_first(head, value, &count);
            }
            else {
                for (count = 1; count < position && p != NULL; count++) {
                    p = p->link;
                }
                if (p != NULL) {
                    head = insert(head, p, value, &count);
                }
                else {
                    printf("유효하지 않은 위치입니다\n");
                }
            }
            printf("이동 횟수: %d\n", count);
            break;
        }
        case 2: {
            printf("삭제할 위치를 입력하세요: ");
            scanf("%d", &position);
            int count = 0;
            ListNode* p = head;
            if (position == 0) {
                head = delete_first(head);
                count = 1;
            }
            else {
                for (count = 1; count < position && p != NULL; count++) {
                    p = p->link;
                }
                if (p != NULL && p->link != NULL) {
                    head = delete(head, p);
                }
                else {
                    printf("유효하지 않은 위치입니다\n");
                }
            }
            printf("이동 횟수: %d\n", count);
            break;
        }
        case 3:
            print_list(head);
            break;
        case 0:
            exit(0);
        default:
            printf("유효하지 않은 선택입니다\n");
        }
    }
    return 0;
}
