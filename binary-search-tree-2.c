#include <stdio.h>
#include <stdlib.h>

typedef struct node {		// ����ü node ����
	int key;				// int�� ���� key
	struct node *left;		// ����ü node�� ���� ������ left
	struct node *right;		// ����ü node�� ���� ������ right
} Node;						// ����ü node�� Node�� ����

#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];	// Node�� ���� MAX_STACK_SIZE ũ�� ��ŭ�� ������ �迭 stack	
int top = -1;					// stack�� ����� top -1�� �ʱ�ȭ

Node* pop();					// stack�� pop ���
void push(Node* aNode);			// stack�� push ���

#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];	// Node�� ���� MAX_QUEUE_SIZE ũ�� ��ŭ�� ������ �迭 queue
int front = -1;					// queue�� ����� front -1�� �ʱ�ȭ
int rear = -1;					// queue�� ����� rear -1�� �ʱ�ȭ

Node* deQueue();			// queue�� deQueue ���
void enQueue(Node* aNode);	// queue�� enQueue ���


int initializeBST(Node** h); // ����Ʈ�� �ʱ�ȭ 

void recursiveInorder(Node* ptr);	  // recursive ������� ���� ��ȸ
void iterativeInorder(Node* ptr);     // iterative ������� ���� ��ȸ
void levelOrder(Node* ptr);	          // level order ��ȸ
int insert(Node* head, int key);      // ����Ʈ���� �Է¹��� key�� ���� ��� ����
int deleteNode(Node* head, int key);  // �Է¹��� key�� ���� ��� ����
int freeBST(Node* head); // Ʈ�� ����

int main()
{
	char command;
	int key;
	Node* head = NULL;
	int flag = 0;	// Ʈ���� �ʱ�ȭ �ߴ��� �Ǵ��� ����

	printf("[-------------------- [����â] [2021040021] --------------------]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			flag=1;
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			if(flag == 0)
			{
				printf("Please Initialize BST!\n");
				break;
			}
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			if(flag == 0)
			{
				printf("Please Initialize BST!\n");
				break;
			}
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			if(flag == 0)
			{
				printf("Please Initialize BST!\n");
				break;
			}
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			if(flag == 0)
			{
				printf("Please Initialize BST!\n");
				break;
			}
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h)	// ����Ʈ�� �ʱ�ȭ 
{
	if(*h != NULL) 		// h�� ����Ű�� ���� ����ִ� �ּҰ� NULL�� �ƴ� ���. ��, ����Ʈ���� ����
		freeBST(*h);	// ����Ʈ�� ����

	*h = (Node*)malloc(sizeof(Node));	
	/* �޸��� Heap �������� node ��ŭ�� ũ�⸦ ���� ������ �����,
	�װ��� �ּҸ� �޸��� Stack ������ �ִ� h�� �ִ´�. ��, ����� ���� */
	(*h)->left = NULL;	// h�� ����Ű�� ���� ����Ű�� ���� left�� NULL�� �ִ´�. ��Ʈ ��尡 ����
	(*h)->right = *h;	// h�� ����Ű�� ���� ����Ű�� ���� right�� h�� ����Ű�� ���� �ּҸ� �ִ´�.
	(*h)->key = -9999;	// h�� ����Ű�� ���� ����Ű�� ���� key�� -9999�� �ʱ�ȭ

	top = -1;	// top�� -1�� �ʱ�ȭ

	front = rear = -1;	// fear�� rear�� -1�� �ʱ�ȭ

	return 1;
}



void recursiveInorder(Node* ptr) // recursive ������� ���� ��ȸ
{
	if(ptr)	// ptr�� NULL�� �ƴ� �ٸ� ���� ����ִ� ��� 
	{
		recursiveInorder(ptr->left); 
		// recursiveInorder �Լ��� �Ű������� ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ְ� ����
		printf(" [%d] ", ptr->key);	// ptr�� ����Ű�� ���� key ���
		recursiveInorder(ptr->right);
		// recursiveInorder �Լ��� �Ű������� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ְ� ���� 
	}
}

void iterativeInorder(Node* node) // iterative ������� ���� ��ȸ
{
	for(;;) // ���ѹݺ�
	{
		for(; node; node = node->left)	
		//  node�� NULL�� �ƴ� ������ �ݺ�. 
		// �� �� ������ ������ node�� node�� ����Ű�� ���� left�� ����ִ� �ּҸ� ����
		{
				push(node);	// node�� ����ִ� �ּҸ� stack�� �ִ´�.
		}
		node = pop();	// node�� stack[top]�� �ִ¤���.

		if(!node) break;	// node�� NULL�̶�� Ż��
		printf(" [%d] ", node->key);	// node�� ����Ű�� ���� key ���

		node = node->right;	// node�� node�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.
	}
}

void levelOrder(Node* ptr)	// level order ��ȸ
{

	if(!ptr) return;	// ptr�� NULL�� ����Ű�� ����
	enQueue(ptr);		// ptr�� ����ִ� �ּҸ� queue�� �ִ´�.

	for(;;)	// ���ѹݺ�
	{
		ptr=deQueue();	// ptr�� queue[front]�� �ִ´�.
		if(ptr)	// ptr�� NULL�� �ƴ� ���� ����Ű�� ���
		{
			printf(" [%d] ", ptr->key);	// ptr�� ����Ű�� ���� key ���
			if(ptr->left)	// ptr�� ����Ű�� ���� left�� NULL�� �ƴ� ���� ����ִ� ���
				enQueue(ptr->left);	
				// ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� queue[rear]�� �ִ´�.
			if(ptr->right)	// ptr�� ����Ű�� ���� right�� NULL�� �ƴ� ���� ����ִ� ���
				enQueue(ptr->right);
				// ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� queue[rear]�� �ִ´�.
		}
		else break; // ptr�� NULL�� ����ִٸ� Ż��
	}
}


int insert(Node* head, int key)	// ����Ʈ���� �Է¹��� key�� ���� ��� ����
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	// �޸��� Heap ������ Node ũ�� ��ŭ�� ������ �����,
	// �װ��� �ּҸ� �޸��� Stack ������ �ִ� newNode�� �ִ´�.
	newNode->key = key;    // newNode�� ����Ű�� ���� key�� �Է¹��� key�� �ִ´�. 
	newNode->left = NULL;  // newNode�� ����Ű�� ���� left�� NULL�� �ִ´�.
	newNode->right = NULL; // newNode�� ����Ű�� ���� right�� NULL�� �ִ´�.

	if (head->left == NULL)	// head�� ����Ű�� ���� left�� NULL�� ���. ��Ʈ��尡 ���� ��� 
	{	
		head->left = newNode;	
		// head�� ����Ű�� ���� left�� newNode�� ����ִ� �ּҸ� �ִ´�.
		// newNode�� ��Ʈ��尡 �ȴ�.
		return 1;
	}

	// ��Ʈ��尡 �����ϴ� ��Ȳ���� �۵��ϴ� �κ�

	Node* ptr = head->left; // ptr�� head�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.

	Node* parentNode = NULL; // parentNode�� NULL�� �ִ´�.
	while(ptr != NULL) 	// ptr�� NULL�� �ƴ� ������ �ݺ�
	{
		if(ptr->key == key) return 1; // ptr�� ����Ű�� ���� key�� �Է¹��� key�� ���ٸ� ����

		parentNode = ptr; // parentNode�� ptr�� ����ִ� �ּҸ� �ִ´�.
		// �ڽĳ�带 Ž���ϱ� ���� �θ��带 ����ϴ� ���̴�.

		if(ptr->key < key)		// ptr�� ����Ű�� ���� key�� �Է¹��� key���� ���� ���
			ptr = ptr->right;	// ptr�� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.
		else					// ptr�� ����Ű�� ���� key�� �Է¹��� key���� ū ���
			ptr = ptr->left;	// ptr�� ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.
	}

	// ���� ������ ��尡 ������尡 �Ǵ� ��� �۵��ϴ� �κ�

	if(parentNode->key > key) // parentNode�� ����Ű�� ���� key�� �Է¹��� key���� ū ���
		parentNode->left = newNode;	
		// parentNode�� ����Ű�� ���� left�� newNode�� ����ִ� �ּҸ� �ִ´�.
	else // parentNode�� ����Ű�� ���� key�� �Է¹��� key���� ���� ���
		parentNode->right = newNode; 
		// parentNode�� ����Ű�� ���� right�� newNode�� ����ִ� �ּҸ� �ִ´�. 
	return 1;
}


int deleteNode(Node* head, int key) // �Է¹��� key�� ���� ��� ����
{
	if(head == NULL) // head�� NULL�� ���. ��� ��尡 ���� ���
	{
		printf("\n Nothing to delete!!\n");	// ������ ���� ���ٴ� ���� ���
		return -1;
	}

	if(head->left == NULL)	// head�� ����Ű�� ���� left�� NULL�� ���. ��Ʈ��尡 ���� ���
	{
		printf("\n Nothing to delete!!\n");	// ������ ���� ���ٴ� ���� ���
		return -1;
	}

	// ��Ʈ��尡 �����ϴ� ��� �۵��ϴ� �κ�

	Node* root = head->left; // root�� head�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�. 

	Node* parent = NULL;	// parentNode�� NULL�� �ִ´�.
	Node* ptr = root;		// ptr�� root�� ����ִ� �ּҸ� �ִ´�.

	while((ptr != NULL) && (ptr->key != key))
	// ptr�� NULL�� �ƴϰ� ptr�� ����Ű�� ���� key�� �Է¹��� key�� �ƴ� ������ �ݺ�
	{
		if(ptr->key != key)	// ptr�� ����Ű�� ���� keyr�� �Է¹��� key�� �ƴ� ���
		{
			parent = ptr;	// parent�� ptr�� ����ִ� �ּҸ� �ִ´�.

			if(ptr->key > key)	// ptr�� ����Ű�� ���� key�� �Է¹��� key���� ū ���
			{
				ptr = ptr->left; // ptr�� ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.
			}
			else	// ptr�� ����Ű�� ���� key�� �Է¹��� key���� ���� ���
			{
				ptr = ptr->right; // ptr�� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.
			}
		}
	}

	if(ptr == NULL)	// ptr�� NULL�� ���. �Է¹��� key�� ���� ��尡 ���� ���
	{
		printf("No node for key [%d]\n", key); // �ش� key�� ���� ��尡 ���ٴ� ���� ���
		return -1;
	}

	// ���� ��带 �����ϴ� ���
	if(ptr->left == NULL && ptr->right == NULL)
	// ptr�� ����Ű�� ���� left�� NULL�̰� ptr�� ����Ű�� ���� right�� NULL�� ���
	{
		if(parent != NULL)	// parent�� NULL�� �ƴ� ���
		{
			if(parent->left == ptr)	
			// parent�� ����Ű�� ���� left�� ptr�� ����ִ� �ּҿ� ���� ���
			{
				parent->left = NULL; // parent�� ����Ű�� ���� left�� NULL�� �ִ´�.
			}
			else // parent�� ����Ű�� ���� left�� ptr�� ����ִ� �ּҿ� �ٸ� ���
			{
				parent->right = NULL; // parent�� ����Ű�� ���� right�� NULL�� �ִ´�.
			}
		}
		else // parent�� NULL�� ���. ��, ��Ʈ��� �ϳ��� ���� �� ��Ʈ��� ����
		{
			head->left = NULL;	// head�� ����Ű�� ���� left�� NULL�� �ִ´�.
		}

		free(ptr);	// ptr ����
		return 1;
	}

	// �����ؾ��� ��尡 �ϳ��� �ڽĳ�带 ������ ���
	if((ptr->left == NULL || ptr->right == NULL))
	// ptr�� ����Ű�� ���� left�� NULL�̰ų� ptr�� ����Ű�� ���� right�� NULL�� ���
	{
		Node* child;
		if(ptr->left != NULL)	// ptr�� ����Ű�� ���� left�� NULL�� �ƴ� ���
			child = ptr->left;	// child�� ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.
		else // ptr�� ����Ű�� ���� left�� NULL�� ���
			child = ptr->right;	// child�� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.
		
		if(parent != NULL)	// parent�� NULL�� �ƴ� ���
		{
			if(parent->left == ptr)		// parent�� ����Ű�� ���� left�� ptr�� ���
				parent->left = child;	
				// parent�� ����Ű�� ���� left�� child�� ����ִ� �ּҸ� �ִ´�.
			else	// parent�� ����Ű�� ���� left�� ptr�� �ƴ� ���
				parent->right = child;	
				// parent�� ����Ű�� ���� right�� child�� ����ִ� �ּҸ� �ִ´�.
		}
		else	
		// parent�� NULL�� ���. ��, ��Ʈ��带 �����ؾ��ϴµ� �ڽĳ�带 �ϳ� ���� �ִ� ���
		{
			root = child;	// root�� child�� ����ִ� �ּҸ� �ִ´�.
		}

		free(ptr);	// ptr ����
		return 1;
	}

	// �����ؾ��� ��尡 �� ���� �ڽ� ��带 ���� �ִ� ��� �۵��ϴ� �κ�

	Node* candidate;
	parent =ptr; // parent�� ptr�� ����ִ� �ּҸ� �ִ´�.

	candidate = ptr->right; // candidate�� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.

	// ���� ���� ���� ������ ����Ʈ���� ���� ���ʿ� �ִ�.
	while(candidate->left != NULL)	// candidate�� ����Ű�� ���� left�� NULL�� �ƴ� ������ �ݺ�
	{
		parent = candidate;			 // parent�� candidate�� ����ִ� �ּҸ� �ִ´�. 
		candidate = candidate->left; 
		// candidate�� candidate�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.
	}

	// candidate ���� �����ؾ��� ����� ������ ����.
	// candidate ���� ���� �ڽ��� ����.
	if(parent->right == candidate)	// parent�� ����Ű�� ���� right�� candidate�� ���� ���
		parent->right = candidate->right;
		// parent�� ����Ű�� ���� right�� candidate�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.
	else // parent�� ����Ű�� ���� right�� candidate�� �ٸ� ���
		parent->left = candidate->right;
		// parent�� ����Ű�� ���� left�� candidate�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ִ´�.

	ptr->key = candidate->key; // ptr�� ����Ű�� ���� key�� candidate�� ����Ű�� ���� key�� �ִ´�.

	free(candidate); // candidate ����
	return 1;
}


void freeNode(Node* ptr)	// ��� ����
{
	if(ptr) 
	{	// ptr�� NULL�� �ƴ� ���� ����ִ� ���
		freeNode(ptr->left);	
		// freeNode �Լ��� �Ű������� ptr�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ְ� ����
		freeNode(ptr->right);
		// freeNode �Լ��� �Ű������� ptr�� ����Ű�� ���� right�� ����ִ� �ּҸ� �ְ� ����
		free(ptr);	// ptr ����
	}
}

int freeBST(Node* head)	// Ʈ�� ����
{
	if(head->left == head)	// head�� ����Ű�� ���� left�� head�� ����ִ� �ּҿ� ���� ���
	// ����常 �����ϴ� ���
	{
		free(head);	// head ����
		return 1;
	}

	Node* p = head->left;	// p�� head�� ����Ű�� ���� left�� ����ִ� �ּҸ� �ִ´�.

	freeNode(p);	// freeNode�� ��� ����

	free(head);		// head ����
	return 1;
}



Node* pop() // stack�� pop ���
{
	if(top<0) return NULL; // top�� 0���� �۴ٸ� NULL ��ȯ
	
	return stack[top--]; // stack[top] ��ȯ �� top -1 ����
}

void push(Node* aNode)	// stack�� push ���
{
	stack[++top] = aNode;	// top 1 ���� ��, stack[top]�� aNode�� ����ִ� �ּҸ� �ִ´�.
}

Node* deQueue() // queue�� deQueue ���
{
	if(front == rear)	// front�� rear�� ���� ���. ��, queue�� ���� �� ����
	{
		return NULL;	// ��ȯ
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	// front�� (front + 1) % MAX_QUEUE_SIZE ������ ����� �ִ´�.
	return queue[front];	// queue[front]�� ����ִ� �ּҸ� ��ȯ
}

void enQueue(Node* aNode)	// queue�� enQueue ���
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	// rear�� (rear + 1) % MAX_QUEUE_SIZE ������ ����� �ִ´�.
	if(front == rear)	// front �� rear�� ���� ���. ��, queue�� ���� �� ����
	{
		return;
	}

	queue[rear] = aNode; // queue[rear]�� aNode�� ����ִ� �ּҸ� �ִ´�.
}