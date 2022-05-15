#include <stdio.h>
#include <stdlib.h>

typedef struct node {		// 구조체 node 선언
	int key;				// int형 변수 key
	struct node *left;		// 구조체 node에 대한 포인터 left
	struct node *right;		// 구조체 node에 대한 포인터 right
} Node;						// 구조체 node를 Node로 정의

#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];	// Node에 대한 MAX_STACK_SIZE 크기 만큼의 포인터 배열 stack	
int top = -1;					// stack에 사용할 top -1로 초기화

Node* pop();					// stack의 pop 기능
void push(Node* aNode);			// stack의 push 기능

#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];	// Node에 대한 MAX_QUEUE_SIZE 크기 만큼의 포인터 배열 queue
int front = -1;					// queue에 사용할 front -1로 초기화
int rear = -1;					// queue에 사용할 rear -1로 초기화

Node* deQueue();			// queue의 deQueue 기능
void enQueue(Node* aNode);	// queue의 enQueue 기능


int initializeBST(Node** h); // 이진트리 초기화 

void recursiveInorder(Node* ptr);	  // recursive 방식으로 중위 순회
void iterativeInorder(Node* ptr);     // iterative 방식으로 중위 순회
void levelOrder(Node* ptr);	          // level order 순회
int insert(Node* head, int key);      // 이진트리에 입력받은 key를 지닌 노드 삽입
int deleteNode(Node* head, int key);  // 입력받은 key를 지닌 노드 삭제
int freeBST(Node* head); // 트리 해제

int main()
{
	char command;
	int key;
	Node* head = NULL;
	int flag = 0;	// 트리를 초기화 했는지 판단할 변수

	printf("[-------------------- [복무창] [2021040021] --------------------]");

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

int initializeBST(Node** h)	// 이진트리 초기화 
{
	if(*h != NULL) 		// h가 가리키는 곳에 들어있는 주소가 NULL이 아닌 경우. 즉, 이진트리가 존재
		freeBST(*h);	// 이진트리 해제

	*h = (Node*)malloc(sizeof(Node));	
	/* 메모리의 Heap 영역에서 node 만큼의 크기를 갖는 공간을 만들고,
	그곳의 주소를 메모리의 Stack 영역에 있는 h에 넣는다. 즉, 헤드노드 생성 */
	(*h)->left = NULL;	// h가 가리키는 곳이 가리키는 곳의 left에 NULL을 넣는다. 루트 노드가 없음
	(*h)->right = *h;	// h가 가리키는 곳이 가리키는 곳의 right에 h가 가리키는 곳의 주소를 넣는다.
	(*h)->key = -9999;	// h가 가리키는 곳이 가리키는 곳의 key를 -9999로 초기화

	top = -1;	// top을 -1로 초기화

	front = rear = -1;	// fear와 rear를 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr) // recursive 방식으로 중위 순회
{
	if(ptr)	// ptr에 NULL이 아닌 다른 것이 들어있는 경우 
	{
		recursiveInorder(ptr->left); 
		// recursiveInorder 함수에 매개변수로 ptr이 가리키는 곳의 left에 들어있는 주소를 주고 실행
		printf(" [%d] ", ptr->key);	// ptr이 가리키는 곳의 key 출력
		recursiveInorder(ptr->right);
		// recursiveInorder 함수에 매개변수로 ptr이 가리키는 곳의 right에 들어있는 주소를 주고 실행 
	}
}

void iterativeInorder(Node* node) // iterative 방식으로 중위 순회
{
	for(;;) // 무한반복
	{
		for(; node; node = node->left)	
		//  node가 NULL이 아닐 때까지 반복. 
		// 한 번 루프가 끝나면 node에 node가 가리키는 곳의 left에 들어있는 주소를 넣음
		{
				push(node);	// node에 들어있는 주소를 stack에 넣는다.
		}
		node = pop();	// node에 stack[top]을 넣는ㄴ다.

		if(!node) break;	// node가 NULL이라면 탈출
		printf(" [%d] ", node->key);	// node가 가리키는 곳의 key 출력

		node = node->right;	// node에 node가 가리키는 곳의 right에 들어있는 주소를 넣는다.
	}
}

void levelOrder(Node* ptr)	// level order 순회
{

	if(!ptr) return;	// ptr이 NULL을 가리키면 종료
	enQueue(ptr);		// ptr에 들어있는 주소를 queue에 넣는다.

	for(;;)	// 무한반복
	{
		ptr=deQueue();	// ptr에 queue[front]를 넣는다.
		if(ptr)	// ptr이 NULL이 아닌 것을 가리키는 경우
		{
			printf(" [%d] ", ptr->key);	// ptr이 가리키는 곳의 key 출력
			if(ptr->left)	// ptr이 가리키는 곳의 left에 NULL이 아닌 것이 들어있는 경우
				enQueue(ptr->left);	
				// ptr이 가리키는 곳의 left에 들어있는 주소를 queue[rear]에 넣는다.
			if(ptr->right)	// ptr이 가리키는 곳의 right에 NULL이 아닌 것이 들어있는 경우
				enQueue(ptr->right);
				// ptr이 가리키는 곳의 right에 들어있는 주소를 queue[rear]에 넣는다.
		}
		else break; // ptr에 NULL이 들어있다면 탈출
	}
}


int insert(Node* head, int key)	// 이진트리에 입력받은 key를 지닌 노드 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	// 메모리의 Heap 영역에 Node 크기 만큼의 공간을 만들고,
	// 그곳의 주소를 메모리의 Stack 영역에 있는 newNode에 넣는다.
	newNode->key = key;    // newNode가 가리키는 곳의 key에 입력받은 key를 넣는다. 
	newNode->left = NULL;  // newNode가 가리키는 곳의 left에 NULL을 넣는다.
	newNode->right = NULL; // newNode가 가리키는 곳의 right에 NULL을 넣는다.

	if (head->left == NULL)	// head가 가리키는 곳의 left가 NULL인 경우. 루트노드가 없는 경우 
	{	
		head->left = newNode;	
		// head가 가리키는 곳의 left에 newNode에 들어있는 주소를 넣는다.
		// newNode가 루트노드가 된다.
		return 1;
	}

	// 루트노드가 존재하는 상황에서 작동하는 부분

	Node* ptr = head->left; // ptr에 head가 가리키는 곳의 left에 들어있는 주소를 넣는다.

	Node* parentNode = NULL; // parentNode에 NULL을 넣는다.
	while(ptr != NULL) 	// ptr이 NULL이 아닐 때까지 반복
	{
		if(ptr->key == key) return 1; // ptr이 가리키는 곳의 key가 입력받은 key와 같다면 종료

		parentNode = ptr; // parentNode에 ptr에 들어있는 주소를 넣는다.
		// 자식노드를 탐색하기 위해 부모노드를 기억하는 것이다.

		if(ptr->key < key)		// ptr이 가리키는 곳의 key가 입력받은 key보다 작은 경우
			ptr = ptr->right;	// ptr에 ptr이 가리키는 곳의 right에 들어있는 주소를 넣는다.
		else					// ptr이 가리키는 곳의 key가 입력받은 key보다 큰 경우
			ptr = ptr->left;	// ptr에 ptr이 가리키는 곳의 left에 들어있는 주소를 넣는다.
	}

	// 새로 생성한 노드가 리프노드가 되는 경우 작동하는 부분

	if(parentNode->key > key) // parentNode가 가리키는 곳의 key가 입력받은 key보다 큰 경우
		parentNode->left = newNode;	
		// parentNode가 가리키는 곳의 left에 newNode에 들어있는 주소를 넣는다.
	else // parentNode가 가리키는 곳의 key가 입력받은 key보다 작은 경우
		parentNode->right = newNode; 
		// parentNode가 가리키는 곳의 right에 newNode에 들어있는 주소를 넣는다. 
	return 1;
}


int deleteNode(Node* head, int key) // 입력받은 key를 지닌 노드 삭제
{
	if(head == NULL) // head가 NULL인 경우. 헤드 노드가 없는 경우
	{
		printf("\n Nothing to delete!!\n");	// 삭제할 것이 없다는 문구 출력
		return -1;
	}

	if(head->left == NULL)	// head가 가리키는 곳의 left가 NULL인 경우. 루트노드가 없는 경우
	{
		printf("\n Nothing to delete!!\n");	// 삭제할 것이 없다는 문구 출력
		return -1;
	}

	// 루트노드가 존재하는 경우 작동하는 부분

	Node* root = head->left; // root에 head가 가리키는 곳의 left에 들어있는 주소를 넣는다. 

	Node* parent = NULL;	// parentNode에 NULL을 넣는다.
	Node* ptr = root;		// ptr에 root에 들어있는 주소를 넣는다.

	while((ptr != NULL) && (ptr->key != key))
	// ptr이 NULL이 아니고 ptr이 가리키는 곳의 key가 입력받은 key가 아닐 때까지 반복
	{
		if(ptr->key != key)	// ptr이 가리키는 곳의 keyr가 입력받은 key가 아닌 경우
		{
			parent = ptr;	// parent에 ptr에 들어있는 주소를 넣는다.

			if(ptr->key > key)	// ptr이 가리키는 곳의 key가 입력받은 key보다 큰 경우
			{
				ptr = ptr->left; // ptr에 ptr이 가리키는 곳의 left에 들어있는 주소를 넣는다.
			}
			else	// ptr이 가리키는 곳의 key가 입력받은 key보다 작은 경우
			{
				ptr = ptr->right; // ptr에 ptr이 가리키는 곳의 right에 들어있는 주소를 넣는다.
			}
		}
	}

	if(ptr == NULL)	// ptr이 NULL인 경우. 입력받은 key를 지닌 노드가 없는 경우
	{
		printf("No node for key [%d]\n", key); // 해당 key를 지닌 노드가 없다는 문구 출력
		return -1;
	}

	// 리프 노드를 삭제하는 경우
	if(ptr->left == NULL && ptr->right == NULL)
	// ptr이 가리키는 곳의 left가 NULL이고 ptr이 가리키는 곳의 right가 NULL인 경우
	{
		if(parent != NULL)	// parent가 NULL이 아닌 경우
		{
			if(parent->left == ptr)	
			// parent가 가리키는 곳의 left가 ptr에 들어있는 주소와 같은 경우
			{
				parent->left = NULL; // parent가 가리키는 곳의 left에 NULL을 넣는다.
			}
			else // parent가 가리키는 곳의 left가 ptr에 들어있는 주소와 다른 경우
			{
				parent->right = NULL; // parent가 가리키는 곳의 right에 NULL을 넣는다.
			}
		}
		else // parent가 NULL인 경우. 즉, 루트노드 하나만 있을 때 루트노드 삭제
		{
			head->left = NULL;	// head가 가리키는 곳의 left에 NULL을 넣는다.
		}

		free(ptr);	// ptr 해제
		return 1;
	}

	// 삭제해야할 노드가 하나의 자식노드를 가지는 경우
	if((ptr->left == NULL || ptr->right == NULL))
	// ptr이 가리키는 곳의 left가 NULL이거나 ptr이 가리키는 곳의 right가 NULL인 경우
	{
		Node* child;
		if(ptr->left != NULL)	// ptr이 가리키는 곳의 left가 NULL이 아닌 경우
			child = ptr->left;	// child에 ptr이 가리키는 곳의 left에 들어있는 주소를 넣는다.
		else // ptr이 가리키는 곳의 left가 NULL인 경우
			child = ptr->right;	// child에 ptr이 가리키는 곳의 right에 들어있는 주소를 넣는다.
		
		if(parent != NULL)	// parent가 NULL이 아닌 경우
		{
			if(parent->left == ptr)		// parent가 가리키는 곳의 left가 ptr인 경우
				parent->left = child;	
				// parent가 가리키는 곳의 left에 child에 들어있는 주소를 넣는다.
			else	// parent가 가리키는 곳의 left가 ptr이 아닌 경우
				parent->right = child;	
				// parent가 가리키는 곳의 right에 child에 들어있는 주소를 넣는다.
		}
		else	
		// parent가 NULL인 경우. 즉, 루트노드를 삭제해야하는데 자식노드를 하나 갖고 있는 경우
		{
			root = child;	// root에 child에 들어있는 주소를 넣는다.
		}

		free(ptr);	// ptr 해제
		return 1;
	}

	// 삭제해야할 노드가 두 개의 자식 노드를 갖고 있는 경우 작동하는 부분

	Node* candidate;
	parent =ptr; // parent에 ptr에 들어있는 주소를 넣는다.

	candidate = ptr->right; // candidate에 ptr이 가리키는 곳의 right에 들어있는 주소를 넣는다.

	// 가장 작은 노드는 오른쪽 서브트리의 가장 왼쪽에 있다.
	while(candidate->left != NULL)	// candidate가 가리키는 곳의 left가 NULL이 아닐 때까지 반복
	{
		parent = candidate;			 // parent에 candidate에 들어있는 주소를 넣는다. 
		candidate = candidate->left; 
		// candidate에 candidate가 가리키는 곳의 left에 들어있는 주소를 넣는다.
	}

	// candidate 노드는 삭제해야할 노드의 오른쪽 노드다.
	// candidate 노드는 왼쪽 자식이 없다.
	if(parent->right == candidate)	// parent가 가리키는 곳의 right가 candidate와 같은 경우
		parent->right = candidate->right;
		// parent가 가리키는 곳의 right에 candidate가 가리키는 곳의 right에 들어있는 주소를 넣는다.
	else // parent가 가리키는 곳의 right가 candidate와 다른 경우
		parent->left = candidate->right;
		// parent가 가리키는 곳의 left에 candidate가 가리키는 곳의 right에 들어있는 주소를 넣는다.

	ptr->key = candidate->key; // ptr이 가리키는 곳의 key에 candidate가 가리키는 곳의 key를 넣는다.

	free(candidate); // candidate 해제
	return 1;
}


void freeNode(Node* ptr)	// 노드 해제
{
	if(ptr) 
	{	// ptr에 NULL이 아닌 것이 들어있는 경우
		freeNode(ptr->left);	
		// freeNode 함수의 매개변수로 ptr이 가리키는 곳의 left에 들어있는 주소를 주고 실행
		freeNode(ptr->right);
		// freeNode 함수의 매개변수로 ptr이 가리키는 곳의 right에 들어있는 주소를 주고 실행
		free(ptr);	// ptr 해제
	}
}

int freeBST(Node* head)	// 트리 해제
{
	if(head->left == head)	// head가 가리키는 곳의 left가 head에 들어있는 주소와 같은 경우
	// 헤드노드만 존재하는 경우
	{
		free(head);	// head 해제
		return 1;
	}

	Node* p = head->left;	// p에 head가 가리키는 곳의 left에 들어있는 주소를 넣는다.

	freeNode(p);	// freeNode로 노드 해제

	free(head);		// head 해제
	return 1;
}



Node* pop() // stack의 pop 기능
{
	if(top<0) return NULL; // top이 0보다 작다면 NULL 반환
	
	return stack[top--]; // stack[top] 반환 후 top -1 감소
}

void push(Node* aNode)	// stack의 push 기능
{
	stack[++top] = aNode;	// top 1 증가 후, stack[top]에 aNode에 들어있는 주소를 넣는다.
}

Node* deQueue() // queue의 deQueue 기능
{
	if(front == rear)	// front와 rear가 같은 경우. 즉, queue가 가득 찬 상태
	{
		return NULL;	// 반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	// front에 (front + 1) % MAX_QUEUE_SIZE 연산의 결과를 넣는다.
	return queue[front];	// queue[front]에 들어있는 주소를 반환
}

void enQueue(Node* aNode)	// queue의 enQueue 기능
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	// rear에 (rear + 1) % MAX_QUEUE_SIZE 연산의 결과를 넣는다.
	if(front == rear)	// front 와 rear가 같은 경우. 즉, queue가 가득 찬 상태
	{
		return;
	}

	queue[rear] = aNode; // queue[rear]에 aNode에 들어있는 주소를 넣는다.
}