/******************************
***�������ı���****************
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
****ǰ�����**********
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
*****�������*********
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
*************�������**************
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
*****���������һ��ʵ��*********
�ڶ���˼·��Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ�
��˶�����һ���P���Ƚ�����ջ�����P���������Ӻ��Һ��ӣ�
�����ֱ�ӷ�����������P�������ӻ����Һ��ӣ�
���������Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣
�������������������P���Һ��Ӻ�����������ջ��
�����ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ���������Һ���ǰ�汻���ʣ�
���Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�
*******************************/

void traverseL_1(BinTree* T, void (*visit)(BinTree *)) {
	BinTree * pre = NULL;
	BinTree * cur;
	stack<BinTree *> s;
	s.push(T);
	while (!s.empty()) {
		cur = s.top();
		if (((cur->lnode == NULL) && (cur->rnode == NULL)) || ((pre != NULL) && ((pre == cur->lnode) || (pre == cur->rnode)))) {
			//((pre != NULL) && ((pre = cur->lnode) || (pre = cur->rnode)))) {	//�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�
			
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

void createBiTree(BinTree * &T)  //�����ô���
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