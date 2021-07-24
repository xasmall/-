#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;

	int freq;  //3.20
}DNode, * DLinkList;

//问题：如果出现连续的X序列，那么删除是否正确，会出现漏判
//3.1
void DeleteNext(LinkList q, ElemType x) {
	LinkList d;

	if (q->next == NULL) return;             //没有下一个结点则结束
	else {
		if (q->next->data == x) {
			d = q->next;
			q->next = q->next->next;  //下一个结点等于x则删除
			free(d);
		}
		DeleteNext(q->next, x);
	}
}
void DeleteX(LinkList &head, ElemType x) {
	if (head == NULL) exit(0);

	LinkList d;                        //辅助变量

	while (head != NULL) {    //删除直到头指针指向一个不等于x的结点
		if (head->data == x) {
		d = head;
		head = head->next;
		free(d);
		}
	}

	DeleteNext(head, x);
}

//3.2 跟上面的错误一样
void DeleteX_h(LinkList head, ElemType x) {
	LinkList d;

	if (head->next == NULL) return;
	else {
		if (head->next->data == x) {
			d = head->next;
			head->next = head->next->next;  //下一个结点等于x则删除
			free(d);
		}
		DeleteX_h(head->next, x);
	}
}

//3.3
void PrintRe(LinkList q) {
	if (q->next != NULL) PrintRe(q->next);  //如果有下一个结点则输出下一个结点的值
	printf_s("%d ",q->data);
}
void _PrintRe(LinkList head) {
	if (head == NULL) return;
	else PrintRe(head->next);
}

//3.4
bool DeleteMin(LinkList head) {
	if (head->next == NULL) return false;

	ElemType min = head->next->data;   //记录最小值
	LinkList pNode = head;             //记录最小值结点的上一个结点
	LinkList nNode = head->next;       //记录当前遍历到的结点
	LinkList d;                        //辅助变量


	while (nNode->next != NULL) {
		if (nNode->next->data < min) {
			min = nNode->next->data;
			pNode = nNode;
		}
		nNode = nNode->next;
	}

	d = pNode->next;
	pNode->next = pNode->next->next;
	free(d);

	return true;
}//DeleteMin

//3.5
void Reverse(LinkList head) {
	if (head->next == NULL || head->next->next == NULL) return;   //空链表和只有一个数的链表无需处理

	LinkList p = head->next, m = p->next, q = m->next;

	//第一个数是将来的尾结点
	p->next = NULL;

	while(true) {
		m->next = p;         //结点方向转向
		if (q == NULL) break;
		p = m;
		m = q;
		q = q->next;
	};

	head->next = m;
}//Reverse

//3.6
//插入排序
void Sort(LinkList head) {
	if (head == NULL) return;
	if (head->next == NULL) return;

	ElemType min = head->next->data;   //记录最小值
	LinkList pNode = head;             //记录最小值结点的上一个结点
	LinkList nNode = head;       //记录当前遍历到的结点
	LinkList d;                        //辅助变量

	LinkList newList = (LinkList)malloc(sizeof(LNode)); //插入的链表
	if (newList == NULL) exit(0);
	newList->next = NULL;
	LinkList pos = newList;                  //插入的位置

	while (head->next != NULL) {        //每次找到最小值后插入到新链表中，并在原链表中删除。重复直到原链表空。
		 //寻找最小值
		while (nNode->next != NULL) {
			if (nNode->next->data <= min) {   //有等于号是因为每次min默认值是第一个元素，如果链表只有一个元素的时候
											  //需要对pNode赋一次值，否则会停留在上一次循环的pNode
				min = nNode->next->data;
				pNode = nNode;
			}
			nNode = nNode->next;
		}

		//插入最小值
		pos->next = (LinkList)malloc(sizeof(LNode));
		if (pos->next == NULL) exit(0);
		pos->next->data = pNode->next->data;
		pos->next->next = NULL;
		pos = pos->next;

		//删除原链表最小值结点
		d = pNode->next;
		pNode->next = pNode->next->next;
		free(d);

		nNode = head;
		if (head->next != NULL)
			min = head->next->data;
	}//while

	head->next = newList->next;        //把原链表变为排完序之后的新链表
}//Sort

void Sort_Demo() {
	LinkList head=(LinkList)malloc(sizeof(LNode));
	if (head == NULL) exit(0);
	head->next == NULL;

	LinkList d = head;

	for (int i = 0; i < 5; i++) {
		d->next = (LinkList)malloc(sizeof(LNode));
		if (d->next == NULL) exit(0);
		d = d->next;
		d->next = NULL;
		d->data = 5 - i;
	}

	Sort(head);

	printf_s("%d %d %d", head->next->data, head->next->next->data, head->next->next->next->data);
}//Sort_Demo
//int main() {
//	Sort_Demo();
//}//验算成功


//3.7
bool DeleteXY(LinkList q, ElemType x, ElemType y) {
	// 带表头结点
	// if (q == NULL) return false;   
	if (x > y) return false;

	LinkList d = q;

	LinkList temp;
	//删除的没问题，就是有些空间没有释放
	while (d->next != NULL) {
		if (d->next->data >= x && d->next->data <= y)
			temp = d->next;
			d->next = d->next->next;
			free(temp);
		d = d->next;
	}

	return true;
}

//3.8
//要找出公共结点，只需要同时到达第一个公共结点就行了。要同时到达需要等长，所以先算出两个链表的长度差d，让长的链表先走d格
bool FindPublicNode(LinkList a, LinkList b, LNode* n) {
	if (a == NULL || b == NULL) return false;

	int lenA = 0, lenB = 0, distance;
	
	LinkList d, i = a, j = b;           //辅助变量

	d = a->next;
	while (d != NULL) {
		lenA++;
		d = d->next;
	}
	d = b->next;
	while (d != NULL) {
		lenB++;
		d = d->next;
	}
	// distance = sqrt(lenA - lenB);        sqrt是开平方
	distance = (lenA-lenB)>0?(lenA-lenB):(lenB-lenA);     

	if (lenA > lenB) for (i = a; distance > 0; distance--) i = i->next;
	if (lenA < lenB) for (j = b; distance > 0; distance--) j = j->next;

	while (i != NULL && j != NULL) {
		if (i == j) {
			n = i;
			return true;
		}
		i = i->next;
		j = j->next;
	}

	return false;    //未找到公共结点
}


//3.9 题目要求是按照递增顺序进行输出，这样写是按照递减进行输出，但是代码没什么问题
void PrintIncrease(LinkList head) {
	if (head == NULL) return;
	if (head->next == NULL) return;

	ElemType min = head->next->data;   //记录最小值
	LinkList pNode = head;             //记录最小值结点的上一个结点
	LinkList nNode = head;       //记录当前遍历到的结点
	LinkList d;                        //辅助变量

	while (head->next != NULL) {        //每次找到最小值后输出，并在原链表中删除。重复直到链表空。
		//寻找最小值
		while (nNode->next != NULL) {
			if (nNode->next->data < min) {  
				min = nNode->next->data;
				pNode = nNode;
			}
			nNode = nNode->next;
		}

		//输出
		printf_s("%d ", pNode->next->data);

		//删除原链表最小值结点
		d = pNode->next;
		pNode->next = pNode->next->next;
		free(d);

		nNode = head;
		if (head->next != NULL)
			min = head->next->data;
	}//while
}


//3.10
bool Split(LinkList q, LinkList &odds, LinkList &even) {
	if (q == NULL) return false;

	odds = (LinkList)malloc(sizeof(LNode));
	odds->next = NULL;
	even = (LinkList)malloc(sizeof(LNode));
	even->next = NULL;

	int s = 0;
	LinkList d = q->next, i = odds, j = even;

	while (d != NULL) {
		if (++s / 2 == 1) {
			i->next = d;
			i = i->next;
		}
		else {
			j->next = d;
			j = j->next;
		}
		d = d->next;
	}

	free(q);
	return true;
}


//3.11
//同上，even改成头插就行
bool Split_(LinkList q, LinkList& odds, LinkList& even) {
	if (q == NULL) return false;

	odds = (LinkList)malloc(sizeof(LNode));
	odds->next = NULL;
	even = (LinkList)malloc(sizeof(LNode));
	even->next = NULL;

	int s = 0;
	LinkList d = q->next, i = odds, j;

	while (d != NULL) {
		if (++s / 2 == 1) {
			i->next = d;
			i = i->next;
			d = d->next;
		}
		else {
			//头插
			j = d;
			d = d->next;
			j->next = even->next;
			even->next = j;
		}
	}

	free(q);
	return true;
}

//3.12
void DeleteSame(LinkList q) {
	if (q == NULL || q->next == NULL) return;

	LinkList d = q->next, k;

	while (d->next != NULL) {
		if (d->next->data == d->data) {
			k = d->next;
			d->next = d->next->next;
			free(k);
		}
		else d = d->next;
	}
}


//3.13
bool  Merge(LinkList a, LinkList b, LinkList& result) {
	if (a == NULL || b == NULL) return false;

	result = (LinkList)malloc(sizeof(LNode));
	result->next = NULL;

	LinkList i = a->next, j = b->next;    //遍历位置
	LinkList m;                        //头插辅助变量

	while (i != NULL || j != NULL) {
		if (i->data <= j->data) {
			m = i;
			i = i->next;
			m->next = result->next;
			result->next = m;
		}
		else {
			m = j;
			j = j->next;
			m->next = result->next;
			result->next = m;
		}
	}

	//将a，b中剩下的加入链表
	if (i != NULL) {       
		m = i;
		i = i->next;
		m->next = result->next;
		result->next = m;
	}
	if (j != NULL) {
		m = j;
		j = j->next;
		m->next = result->next;
		result->next = m;
	}

	return true;
}


//3.14
//略

//3.15
//在a链表中找到非交集的删去
void Intersection(LinkList a, LinkList b) {
	if (a == NULL || b == NULL) return;
	if (a->next == NULL || b->next == NULL) return;

	LNode* i = a,* j = b,* m;

	while (i->next != NULL && j->next != NULL) {
		if (i->next->data == j->next->data) {
			i = i->next;
			j = j->next;
		}
		else if (i->next->data < j->next->data) {
			m = i->next;
			i->next = i->next->next; //删除非交集
		}
		else j = j->next;
	}
	//如果A中还没有遍历完，需要将A链表中未遍历的结点删除
	while(i->next){
		m = i->next;
		i->next = i->next->next;
		free(m);
	}
}


//3.16 找到第一个相等的并不一定是正确序列中的第一个，如果不对，需要继续往下面判断
bool IsContinSubs(LinkList a, LinkList b) {
	if (a == NULL || b == NULL) return false;

	LNode* i = a->next, * j = b->next, * m = a->next;

	// //找到第一个相同的元素
	// while (i != NULL) {
	// 	if (i->data = j->data) break;
	// 	i = i->next;
	// }
	// if (i == NULL) return false;

	// while (i != NULL && j != NULL) {
	// 	i = i->next;
	// 	j = j->next;
	// 	if (i->data != j->data) break;
	// }
	while(i&&j){
		if(i->data==j->data){
			i = i->next;
			j = j->next;
		}else{
			m = m->next;
			i = pre;
			j = b->next;
		}
	}
	if(!j) return true;
	else return false;

}


//3.17
bool IsSymmetric(DLinkList q) {
	if (q == NULL) return false;

	DNode* i = q->prior, * j = q->next;

	while (i != j && i->next != j) {
		if (i->data != j->data) return false;
		i = i->prior;
		j = j->next;
	}

	return true;
}

//3.18
//循环单链表设尾指针不设头指针
LinkList Connnect(LinkList h1, LinkList h2) {
	// 如果h1为null,h2不空,h1地址指向h2即可，如果h2空，直接返回h1即可
	// if (h1 == NULL || h2 == NULL) return false;
	if(h2 == NULL) return h1;
	if(h1 == NULL){
		h1 = h2;
		return h1;
	}

	// 将链表h2链接到h1后面，需要先找到h1和h2的最后一个结点
	LNode *p,*q,*temp1,*temp2;
	p = h1;
	temp1 = h1->next;
	q = h2;
	while(temp1->next!=p){
		temp2 = temp2->next;
	}
	while(temp2->next!=q){
		temp2 = temp2->next;
	}
	temp1->next = q;
	temp2->next = p;
	return h1;

// 	LNode* i = h1->next, * j = h2->next;  //记录头指针

// 	h1->next = j->next;
// 	h2->next = i;
// 	h1 = h2;

// 	free(j);
// 	return true;
// }


//3.19
//略，同3.9


//3.20
//每次找到x后，freq+1，并向前移动到prior的freq更大或移动到头结点
DNode* Locate(DLinkList L, ElemType x) {
	if (L == NULL) return NULL;

	DNode* i = L->next;
	while (true) {            //寻找x
		if (i == NULL) return NULL;
		if (i->data == x) break;
		i = i->next;
	}

	DNode* j = i->prior;
	ElemType temp1;
	int temp2;
	while (j != L) {
		if (j->freq <= i->freq) {
			//交换i和j的data 和 freq
			temp1 = i->data;
			i->data = j->data;
			j->data = temp1;
			temp2 = i->freq;
			i->freq = j->freq;
			j->freq = temp2;

			//i和j向prior移动
			i = i->prior;
			j = j->prior;
		}
		else break;
	}

	return i;
}


//3.21
//先扫描链表的长度len，然后输出第len-k+1个元素
int PrintInvert(LinkList q, int k) {
	if (q == NULL) return 0;
	
	LNode* i=q->next;
	int len = 0;
	while (i != NULL) {
		len++;
		i = i->next;
	}

	if (k > len) return 0;

	i = q->next;
	for (int j = 1; j < len - k + 1; j++) i = i->next;
	printf_s("%d", i->data);

	return 1;
}


//3.22
//略，同3.8


//3.23
//因为链表中每个元素都为绝对值<=n的整数，不难想到构造一个大小为n+1的标志数组判断是否值已出现过
bool DeleteSimilar(LinkList q, int n) {
	if (q == NULL) return false;

	int* flag = (int*)malloc(sizeof(ElemType) * (n + 1));
	for (int i = 0; i < n + 1; i++) flag[i] = 0;

	LNode* j,* k,*pre;
	j = q->next;
	pre = q;
	// 先while循环将数组存在的都为1,后面就全部删掉了，应该在一边判断一边就行删除
	// while (j != NULL) {
	// 	// abs才是绝对值函数
	// 	// if (sqrt(j->data) <= n) flag[(int)sqrt(j->data)] = 1;
	// 	if (abs(j->data) <= n) flag[(int)abs(j->data)] = 1;
	// 	else return false;
	// 	j = j->next;
	// }

	// j = q;
	// while (j->next != NULL) {
	// 	if (flag[(int)sqrt(j->next->data)] == 1) {
	// 		k = j->next;
	// 		j->next = j->next->next;
	// 		free(k);
	// 	}
	// 	j = j->next;
	// }
	while(j){
		if(flag[j->data]){
			k = j;
			j = j->next;
			pre->next = j->next;
			free(k);
		}else{
			flag[j->data] = 1;
			pre = j;
			j = j->next;
		}
	}
	return true;
}
//时间复杂度O(m),空间复杂度O(n)


//3.24


//3.25
//将链表从中间拆成两个，把第二个链表倒置，然后交叉插入第一个链表中
void Array(LinkList q) {
	if (q == NULL||q->next == NULL) return;

	int len = 0;
	LNode* i = q->next,* j,* k;
	while (i != NULL) {
		len++;
		i = i->next;
	}

	int posB = ceil((double)len / 2);

	LinkList B = (LinkList)malloc(sizeof(LNode));
	if (B == NULL) exit(0);
	B->next = q->next;

	for (int i = 0; i < posB - 1 ; i++) B->next = B->next->next;  //B为头结点
	j = B->next;
	B->next = B->next->next;
	j->next = NULL;         //把两个链表断开

	Reverse(B);

	i = q->next;
	j = B->next;

	while (j != NULL) {
		k = i;
		i = i->next;
		k->next = j;
		j = j->next;
		k->next->next = i;
	}
}
void Array_Demo() {
	LinkList head = (LinkList)malloc(sizeof(LNode));
	if (head == NULL) exit(0);
	head->next == NULL;

	LinkList d = head;

	for (int i = 0; i < 5; i++) {
		d->next = (LinkList)malloc(sizeof(LNode));
		if (d->next == NULL) exit(0);
		d = d->next;
		d->next = NULL;
		d->data = 5 - i;
	}

	Array(head);

	LNode* i = head->next;
	while (i != NULL) {
		printf_s("%d ", i->data);
		i = i->next;
	}
	printf_s("NULL");
}//Array_Demo
int main() {
	Array_Demo();
}//验算成功
