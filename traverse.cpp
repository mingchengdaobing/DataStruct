/******************************
***二叉树的遍历****************
******************************/
#include <stack>
#include <queue>
#include <iostream>

using namespace std;

//typedef struct node * BinTree *;
typedef struct node {
	int data;
	struct node *lnode;
	struct node *rnode;
}BinTree;

/*********************
****前序遍历**********
*********************/

void traverse(BinTree * h, void (*visit)(BinTree *))
{
	stack<BinTree *> s;
	
	s.push(h);
	while (!s.empty()) {
		(*visit)(h = s.top());
		//cout << h->data << " ";
		s.pop();
		if (h->rnode != NULL) s.push(h->rnode);
		if (h->lnode != NULL) s.push(h->lnode);
	}
}

/*********************
*****中序遍历*********
*********************/
void traverseM(BinTree * h, void (*visit)(BinTree *)) {
	stack<BinTree *> s;
	//s.push_back(h);
	while (h != NULL || !s.empty()) {
		while (h != NULL) {
			s.push(h);
			//(*visit)(h);
			h = h->lnode;
		}
		if (!s.empty()) {
			h = s.top();
			(*visit)(h);
			s.pop();
			h = h->rnode;
		}
		//(*visit)(h = s.begin());
		//if (h->lnode != NULL) s.push_front(h->lnode);
		//if (h->rnode != NULL) s.push_back(h->rnode);
	}
}


/**********************************
*************后序遍历**************
**********************************/
void traverseL(BinTree * T, void (*visit)(BinTree *)) {
	
	BinTree * p = T;
	
	typedef struct {
		BinTree * btnode;
		bool isFirst;
	}BTnode;
	BTnode *tmp;
	stack<BTnode *> s;
	while(p!=NULL||!s.empty()) {
		while (p != NULL) {
			BTnode *btn = (BTnode *)malloc(sizeof(BTnode));
			btn->btnode = p;
			btn->isFirst = true;
			s.push(btn);
			p = p->lnode;
		}

		if (!s.empty()) {
			tmp = s.top();
			s.pop();
			if (tmp->isFirst == true) {
				tmp->isFirst = false;
				s.push(tmp);
				p = tmp->btnode->rnode;
			}
			else {
				(*visit)(tmp->btnode);
				p = NULL;
			}
		}
	}
}

/*******************************
*****后序遍历另一种实现*********
第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，
因此对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，
则可以直接访问它；或者P存在左孩子或者右孩子，
但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
若非上述两种情况，则将P的右孩子和左孩子依次入栈，
这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，
左孩子和右孩子都在根结点前面被访问。
*******************************/

void traverseL_1(BinTree* T, void (*visit)(BinTree *)) {
	BinTree * pre = NULL;
	BinTree * cur;
	stack<BinTree *> s;
	s.push(T);
	while (!s.empty()) {
		cur = s.top();
		if (((cur->lnode == NULL) && (cur->rnode == NULL)) || ((pre != NULL) && ((pre == cur->lnode) || (pre == cur->rnode)))) {
			//((pre != NULL) && ((pre = cur->lnode) || (pre = cur->rnode)))) {	//如果当前结点没有孩子结点或者孩子节点都已被访问过
			
				(*visit)(cur);
				s.pop();
				pre = cur;
		}
		else {
			if (cur->rnode != NULL)
				s.push(cur->rnode);
			if (cur->lnode != NULL)
				s.push(cur->lnode);
		}
	}
}

int buff[10];
void printData(BinTree * T) {
	int i=0;
	if (i < 10)
		buff[i++] = T->data;
	cout << T->data << " ";
}

void createBiTree(BinTree * &T)  //按引用传递
{  
    int c;  
    cin >> c;  
    if(100 == c)  
        T = NULL;  
    else  
    {  
        T = new (BinTree);  
        T->data = c;  
        createBiTree(T->lnode);  
        createBiTree(T->rnode);  
    }  
}

void main() {
	BinTree * T = NULL;
	createBiTree(T);
	traverseL_1(T,printData);
}