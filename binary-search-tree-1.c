
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // ��� ����
	int key; // ���� key
	struct node *left; // node �� ������ left
	struct node *right; // node �� ������ right
} Node;

// �Լ� ����Ʈ
void inorderTraversal(Node* ptr);	  // ������ȸ
void preorderTraversal(Node* ptr);    // ������ȸ
void postorderTraversal(Node* ptr);	  // ������ȸ

int insert(Node* head, int key);           // Ʈ���� ��� ����
int deleteLeafNode(Node* head, int key);  // leaf ��� ����

Node* searchRecursive(Node* ptr, int key);   // ��� Ž��
Node* searchIterative(Node* head, int key);  // ��� Ž��

int initializeBST(Node** h); // �ʱ�ȭ
int freeBST(Node* head);     // Ʈ�� ����

void freeNode(Node* ptr); // ��� ����

int main()
{
	char command; 
	int key; 
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
        printf("[----- [�����]  [2020039102] -----]");
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
		scanf(" %c", &command); // �� �ޱ�

		switch(command) {
		case 'z': case 'Z': // �� z �Ǵ� Z �� ���
			initializeBST(&head);
			break;
		case 'q': case 'Q': // �� q �Ǵ� Q �� ���
			freeBST(head);
			break;
		case 'n': case 'N': // �� n �Ǵ� N �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			insert(head, key);
			break;
		case 'd': case 'D': // �� d �Ǵ� D �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': // �� f �Ǵ� F �� ���
			printf("Your Key = "); 
			scanf("%d", &key); // �� �ޱ�
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // �� s �Ǵ� S �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': // �� i �Ǵ� I �� ���
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': // �� p �Ǵ� P �� ���
			preorderTraversal(head->left);
			break;
		case 't': case 'T': // �� t �Ǵ� T �� ���
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // �� q �Ǵ� Q �� �ƴ� ��� ���� ����

	return 1;
}

// Ʈ�� �ʱ�ȭ
int initializeBST(Node** h) {

	if(*h != NULL) // tree�� NULL�� �ƴϸ�
		freeBST(*h); // �޸� ����

	// head node ����
	*h = (Node*)malloc(sizeof(Node)); // *h�� Node Ÿ������ �ּ� �ޱ�
	(*h)->left = NULL; // *h ����Ű�� left �� NULL ����
	(*h)->right = *h; // *h ����Ű�� right �� �ּ� ����
	(*h)->key = -9999; // key -9999 �� �ʱ�ȭ
	return 1;
}

// ������ȸ
void inorderTraversal(Node* ptr)
{
	if(ptr) { // ������ȸ ����
		inorderTraversal(ptr->left); // left ���� ��ȸ
		printf(" [%d] ", ptr->key); // key ���
		inorderTraversal(ptr->right); // right ���� ��ȸ
	}
}

// ������ȸ
void preorderTraversal(Node* ptr)
{
	if(ptr) { // ������ȸ ����
		printf(" [%d] ", ptr->key); // key ���
		preorderTraversal(ptr->left); // left ���� ��ȸ
		preorderTraversal(ptr->right); // right ���� ��ȸ
	}
}

// ������ȸ
void postorderTraversal(Node* ptr)
{
	if(ptr) { // ������ȸ ����
		postorderTraversal(ptr->left); // left ���� ��ȸ
		postorderTraversal(ptr->right); // right ���� ��ȸ
		printf(" [%d] ", ptr->key); // key ���
	}
}

// ��� ����
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Node Ÿ������ �ּ� �ޱ�
	newNode->key = key; // key ����
	newNode->left = NULL; // NULL ����
	newNode->right = NULL; // NULL ����

	if (head->left == NULL) { // NULL �̸�
		head->left = newNode; 
		return 1;
	}

	Node* ptr = head->left; 
	Node* parentNode = NULL;

	while(ptr != NULL) { // NULL �� �ƴϸ�

		if(ptr->key == key) return 1; 
        parentNode = ptr;
        if(ptr->key < key) // ���� key �� �Է¹��� key ���� ������
			ptr = ptr->right; // right tree �� ����
		else
			ptr = ptr->left; // left tree �� ����
	}

	if(parentNode->key > key) // ���� key �� �Է¤����� key ���� ũ��
		parentNode->left = newNode; // left �� newNode ����
	else
		parentNode->right = newNode; // right �� newNoded ����
	return 1;
}

int deleteLeafNode(Node* head, int key) // key �Է¹��� ���� ��� ����
{
	if (head == NULL) { // NULL �̸�
		printf("\n Nothing to delete!!\n"); // ��� ���
		return -1;
	}

	if (head->left == NULL) { // NULL �̸�
		printf("\n Nothing to delete!!\n"); // ��� ���
		return -1;
	}

	Node* ptr = head->left; // ptr head ����Ű�� left �ּ� ����


	Node* parentNode = head; // head �� �ּ� ����

	while(ptr != NULL) { // NULL �� �ƴϸ�

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				if(parentNode == head)
					head->left = NULL; // head ����Ű�� left �� NULL ����

				if(parentNode->left == ptr)
					parentNode->left = NULL; // parentNode ����Ű�� left �� NULL ����
				else
					parentNode->right = NULL; // parenrNode ����Ű�� right �� NULL ����

				free(ptr); // ��� ����
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); // ��� ���
			}
			return 1;
		}

		// ����
		parentNode = ptr;

		// key comparison
		if(ptr->key < key) // ���� key �� �Է¹��� key ���� ũ��
			ptr = ptr->right; // right tree �� ����
		else
			ptr = ptr->left; // left tree �� ����
	}

	printf("Cannot find the node for key [%d]\n ", key); // ��� ���
	return 1;
}

// Ž��
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // NULL �̸�
		return NULL;

	if(ptr->key < key) // ���� key �� �Է¹��� key�� �� ũ��
		ptr = searchRecursive(ptr->right, key); // ȣ��
	else if(ptr->key > key) // ���� key �� �Է¹��� key ���� ������
		ptr = searchRecursive(ptr->left, key); // ȣ��

	return ptr; // ���� key �� �Է¹��� key �� ������

}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr != NULL) // NULL �� �ƴϸ�
	{
		if(ptr->key == key) // ���� key �� �Է¹��� key �� ������
			return ptr; // ��ȯ

		if(ptr->key < key) ptr = ptr->right; // ���� key �� �Է¹��� key ���� ũ��
		else
			ptr = ptr->left; // left �� �ּ� ����
	}
	return NULL;
}

// ��� ����
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); // left tree ȣ��
		freeNode(ptr->right); // right tree ȣ��
		free(ptr); // ����
	}
}

// �޸� ����
int freeBST(Node* head)
{
	if(head->left == head) // left �� head �� ������
	{
		free(head); // ����
		return 1;
	}

	Node* p = head->left; // lefr �� �ּ� ����

	freeNode(p); // �Ű����� p �ְ� ȣ��
	free(head); // head ����
    
	return 1;
}