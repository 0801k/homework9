
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 노드 생성
	int key; // 변수 key
	struct node *left; // node 의 포인터 left
	struct node *right; // node 의 포인터 right
} Node;

// 함수 리스트
void inorderTraversal(Node* ptr);	  // 중위순회
void preorderTraversal(Node* ptr);    // 전위순회
void postorderTraversal(Node* ptr);	  // 후위순회

int insert(Node* head, int key);           // 트리에 노드 삽입
int deleteLeafNode(Node* head, int key);  // leaf 노드 삭제

Node* searchRecursive(Node* ptr, int key);   // 노드 탐색
Node* searchIterative(Node* head, int key);  // 노드 탐색

int initializeBST(Node** h); // 초기화
int freeBST(Node* head);     // 트리 해제

void freeNode(Node* ptr); // 노드 해제

int main()
{
	char command; 
	int key; 
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
        printf("[----- [노관범]  [2020039102] -----]");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 값 받기

		switch(command) {
		case 'z': case 'Z': // 값 z 또는 Z 일 경우
			initializeBST(&head);
			break;
		case 'q': case 'Q': // 값 q 또는 Q 일 경우
			freeBST(head);
			break;
		case 'n': case 'N': // 값 n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			insert(head, key);
			break;
		case 'd': case 'D': // 값 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': // 값 f 또는 F 일 경우
			printf("Your Key = "); 
			scanf("%d", &key); // 값 받기
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // 값 s 또는 S 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': // 값 i 또는 I 일 경우
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': // 값 p 또는 P 일 경우
			preorderTraversal(head->left);
			break;
		case 't': case 'T': // 값 t 또는 T 일 경우
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 값 q 또는 Q 이 아닐 경우 동안 진행

	return 1;
}

// 트리 초기화
int initializeBST(Node** h) {

	if(*h != NULL) // tree가 NULL이 아니면
		freeBST(*h); // 메모리 해제

	// head node 생성
	*h = (Node*)malloc(sizeof(Node)); // *h에 Node 타입으로 주소 받기
	(*h)->left = NULL; // *h 가리키는 left 에 NULL 삽입
	(*h)->right = *h; // *h 가리키는 right 에 주소 삽입
	(*h)->key = -9999; // key -9999 로 초기화
	return 1;
}

// 중위순회
void inorderTraversal(Node* ptr)
{
	if(ptr) { // 중위순회 진행
		inorderTraversal(ptr->left); // left 중위 순회
		printf(" [%d] ", ptr->key); // key 출력
		inorderTraversal(ptr->right); // right 중위 순회
	}
}

// 전위순회
void preorderTraversal(Node* ptr)
{
	if(ptr) { // 전위순회 진행
		printf(" [%d] ", ptr->key); // key 출력
		preorderTraversal(ptr->left); // left 전위 순회
		preorderTraversal(ptr->right); // right 전위 순회
	}
}

// 후위순회
void postorderTraversal(Node* ptr)
{
	if(ptr) { // 후위순회 진행
		postorderTraversal(ptr->left); // left 후위 순회
		postorderTraversal(ptr->right); // right 후위 순회
		printf(" [%d] ", ptr->key); // key 출력
	}
}

// 노드 삽입
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Node 타입으로 주소 받기
	newNode->key = key; // key 삽입
	newNode->left = NULL; // NULL 삽입
	newNode->right = NULL; // NULL 삽입

	if (head->left == NULL) { // NULL 이면
		head->left = newNode; 
		return 1;
	}

	Node* ptr = head->left; 
	Node* parentNode = NULL;

	while(ptr != NULL) { // NULL 이 아니면

		if(ptr->key == key) return 1; 
        parentNode = ptr;
        if(ptr->key < key) // 현재 key 가 입력받은 key 보다 작으면
			ptr = ptr->right; // right tree 에 삽입
		else
			ptr = ptr->left; // left tree 에 삽입
	}

	if(parentNode->key > key) // 현재 key 가 입력ㅂ다은 key 보다 크면
		parentNode->left = newNode; // left 에 newNode 삽입
	else
		parentNode->right = newNode; // right 에 newNoded 삽입
	return 1;
}

int deleteLeafNode(Node* head, int key) // key 입력받은 리프 노드 삭제
{
	if (head == NULL) { // NULL 이면
		printf("\n Nothing to delete!!\n"); // 경고문 출력
		return -1;
	}

	if (head->left == NULL) { // NULL 이면
		printf("\n Nothing to delete!!\n"); // 경고문 출력
		return -1;
	}

	Node* ptr = head->left; // ptr head 가리키는 left 주소 삽입


	Node* parentNode = head; // head 에 주소 삽입

	while(ptr != NULL) { // NULL 이 아니면

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				if(parentNode == head)
					head->left = NULL; // head 가리키는 left 에 NULL 삽입

				if(parentNode->left == ptr)
					parentNode->left = NULL; // parentNode 가리키는 left 에 NULL 삽입
				else
					parentNode->right = NULL; // parenrNode 가리키는 right 에 NULL 삽입

				free(ptr); // 노드 해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); // 경고문 출력
			}
			return 1;
		}

		// 유지
		parentNode = ptr;

		// key comparison
		if(ptr->key < key) // 현재 key 가 입력받은 key 보다 크면
			ptr = ptr->right; // right tree 에 삽입
		else
			ptr = ptr->left; // left tree 에 삽입
	}

	printf("Cannot find the node for key [%d]\n ", key); // 경고문 출력
	return 1;
}

// 탐색
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // NULL 이면
		return NULL;

	if(ptr->key < key) // 현재 key 가 입력받은 key보 다 크면
		ptr = searchRecursive(ptr->right, key); // 호출
	else if(ptr->key > key) // 현재 key 가 입력받은 key 보다 작으면
		ptr = searchRecursive(ptr->left, key); // 호출

	return ptr; // 현재 key 가 입력받은 key 랑 같으면

}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr != NULL) // NULL 이 아니면
	{
		if(ptr->key == key) // 현재 key 가 입력받은 key 와 같으면
			return ptr; // 반환

		if(ptr->key < key) ptr = ptr->right; // 현재 key 가 입력받은 key 보다 크면
		else
			ptr = ptr->left; // left 안 주소 삽입
	}
	return NULL;
}

// 노드 해제
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); // left tree 호출
		freeNode(ptr->right); // right tree 호출
		free(ptr); // 해제
	}
}

// 메모리 해제
int freeBST(Node* head)
{
	if(head->left == head) // left 와 head 가 같으면
	{
		free(head); // 해제
		return 1;
	}

	Node* p = head->left; // lefr 안 주소 삽입

	freeNode(p); // 매개변수 p 주고 호출
	free(head); // head 헤제
    
	return 1;
}