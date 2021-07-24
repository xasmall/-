#include<stdio.h>
#include<stdlib.h>
#include<math.h>
constexpr auto InitSize = 100;
typedef int ElemType;

typedef struct {
	ElemType* data;
	int MaxSize, length;   //数组的最大数量和当前长度
}SeqList;


//顺序表使用了动态存储分配，需要的时候需要进行一下data的分配
//L.data = (ElemType*)malloc(sizeof(ElemType)*InitSize);

//2.1
//从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值。
//空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行。
bool RetMin(SeqList* q, ElemType* e) {
	int min;
	int pos = 0;//最小值的位置
	if (!q||!q->length) return false;
	else min = q->data[0];

	for (int i = 1; i < q->length; i++) {
		if (min > q->data[i]) {
			 min = q->data[i];
			 pos = i;
		}
	}

	q->data[pos] = q->data[q->length - 1];
	q->length--;

	*e = min;
	return true;
}//RetMin

//2.2
//设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)
bool Reverse(SeqList* q) {
	// 为空表的时候不需要逆置，但不是逆置错误了，下面这行不用写
	// if (!q || !q->length) return false;
	int i = 0;
	// 注意类型
	ElemType temp;
	for (int j = q->length - 1; i < j; i++, j--) {
		temp = q->data[i];
		q->data[i] = q->data[j];
		q->data[j] = q->data[i];
	}
	return true;
}//Reverse

//2.3
//3．对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，
//该算法删除线性表中所有值为x的数据元素。
bool DeleteX(SeqList* q, ElemType x) {
	// 跟上面的原因一样，不用写
	// if (!q || !q->length) return false;
	int num = 0;
	for (int i = 0; i < q->length; i++)
		//第num个不等于x的元素排在第num-1个位置
		if (q->data[i] != x) q->data[num++] = q->data[i];
	// 更新一下顺序表长度
	q->length = num;
	return true;
}//DeleteX


// 并没有将删除后的空闲区域填补，
// 2.4与2.5的区别在于有序和无序，直接按照2.5写即可，
// 也可以使用先找到初始需要删除的地方，找到需要删除的位置个数多少，然后从后向前平移即可
//2.4
bool DeleteSTs(SeqList* q, ElemType s, ElemType t) {
	if (!q || !q->length || s >= t) return false;

	for (int i = 0; i < q->length; i++)
		if (q->data[i] >= s && q->data[i] <= t) q->length = i + 1;

	return true;
}//DeleteSTs

//2.5
bool DeleteST(SeqList* q, ElemType s, ElemType t) {
	if (!q || !q->length || s >= t) return false;

	int num = 0;
	for (int i = 0; i < q->length; i++)
		if (q->data[i] < s || q->data[i] > t) q->data[num++] = q->data[i];

	// 更新顺序表长度
	q->length = num;
	return true;
}//DeleteSTs

//2.6
bool DeleSame(SeqList* q) {
	if (!q || !q->length) return false;

	int num = 1;
	for (int i = 1; i < q->length; i++)
		if (q->data[i] != q->data[i - 1]) q->data[num++] = q->data[i];

	// 更新顺序表长度
	return true;
}//DeleSame




// 重要问题，initsize不一定够用，result的长度应该要满足p,q长度之和，并且比他们大
//2.7
bool Merge(SeqList* p, SeqList* q, SeqList* &result) {
	// 不用写
	// if (!q || !q->length) return false;

	SeqList m;
	m.data = (ElemType*)malloc(sizeof(ElemType)*(p->length+q->length+1));
	// m.MaxSize = InitSize;
	m.length = 0;
	SeqList* x = &m;

	int i = 0, j = 0, pos = 0;
	while (i < p->length && j < q->length) {
		if (p->data[i] < p->data[j])
			x->data[pos++] = p->data[i++];
		else x->data[pos++] = p->data[j++];
	}

	while (i < p->length) x->data[pos++] = p->data[i++];
	while (j < p->length) x->data[pos++] = p->data[j++];

	x->length = p->length + q->length;
	result = x;
	return true;
}//Merge

// 2.8这种写法对于空间复杂度要求高，而且原有的数组还存放在内存中，但是是满足题意的，原地逆置需要掌握
//2.8
void ReverseMN(ElemType *q, int m, int n,int arraySize) {
	ElemType* x = (ElemType*)malloc(sizeof(ElemType) * (m + n));
	if(m+n>arraySize) exit(0);
	if (!x) exit(0);

	for (int i = 0; i < n; i++) x[i] = q[i + m];
	for (int i = 0; i < m; i++) x[i + n] = q[i];

	q = x;
}//ReverseMN

//2.9
void Search(SeqList* q, ElemType x) {
	//最短时间
	int low = 0, high = q->length - 1, mid = 0;
	ElemType temp;
	while (low < high) {
		mid = (low + high) / 2; //折半
		if (q->data[mid] == x) break;
		if (q->data[mid] < x) low = mid + 1;
		else high = mid - 1;
	}

	if (q->data[mid] == x && mid != q->length - 1) {
		temp = q->data[mid];
		q->data[mid] = q->data[mid + 1];
		q->data[mid + 1] = temp;
	}

	int i;
	if (low > high) {  //未找到
		for (i = q->length - 1; i > high; i--) q->data[i+1]=q->data[i];
		q->data[i + 1] = x;
	}
}//Search

//2.10
//想法 (xy)的倒置 = y的倒置·x的倒置，所以(yx) = (x的倒置·y的倒置)的倒置
void Reverse(ElemType* data, int length) {
	for (int i = 0, j = length - 1; i < j; i++, j--) {
		ElemType temp = data[i];
		data[i] = data[j];
		data[j] = data[i];
	}
}//Reverse
void LeftMove(SeqList* q, int n) {
	Reverse(q->data, n);
	Reverse(q->data + n, q->length - n);
	Reverse(q->data, q->length);
}//LeftMove
//时间复杂度O(n),空间复杂度O(1);

//2.11
//想法：用两个标志t1,t2分别指向两个序列，设flag初始值为2，如果L小于等于2就在当前位置取值。
//如果L大于2，t2向前移动直到大于t1，然后t1往前移动一位，每移动一次flag加一，重复直到flag=L,此时较大的数就是中位数。
bool FindMid(SeqList* q1, SeqList* q2, int* num) {
	if (!q1 || !q2 || !q1->length || !q2->length) return false;

	int flag = 2;
	int t1 = 0, t2 = 0;
	int L = q1->length;
	if (L <= 2) {
		if (q1->data[t1] > q2->data[t2])
			*num = L == 1 ? q2->data[t2] : q1->data[t1];
		else *num = L == 1 ? q1->data[t1] : q2->data[t2];
		return true;
	}

	while(true){
		while (q1->data[t1] > q2->data[t2]) {
			t2++;
			if (++flag == L) {
				*num = q2->data[t2] > q1->data[t1] ? q2->data[t2] : q1->data[t1];
				return true;
			}
		}
		t1++;
		if (++flag == L) {
			*num = q2->data[t2] > q1->data[t1] ? q2->data[t2] : q1->data[t1];
			return true;
		}
	}
}//FindMid

void FindMid_Demo() {
	SeqList q1;
	q1.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q1.data[0] = 2; q1.data[1] = 4; q1.data[2] = 7; q1.data[3] = 8;
	q1.length = 4;
	q1.MaxSize = InitSize;
	SeqList* x1 = &q1;

	SeqList q2;
	q2.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q2.data[0] = 1; q2.data[1] = 2; q2.data[2] = 5; q2.data[3] = 6;
	q2.length = 4;
	q2.MaxSize = InitSize;
	SeqList* x2 = &q2;

	int num;
	FindMid(x1, x2, &num);
	printf_s("%d", num);
}//FindMid_Demo
 //验算成功
//时间复杂度O(L),空间复杂度O(1)

//2.12
//当n=1时，主元素就是当前元素，当n大于1时：
//遍历数组前半段，依次假设每一位为主元素，然后比较后面的数是否相同，建立两个数s、d
//当遇到相同数时，s++，当遇到不同数时，f++。当s等于⌈n/2⌉-1时,此时为主元素，当f等于⌈n/2⌉,跳到下一位数
//暴力破解方法，相等于记录每个数的次数，时间复杂度有点高
bool SearchMainElem(SeqList* q, ElemType* MainElem) {
	if (!q || !q->length) return false;

	if (q->length == 1) {
		*MainElem = q->data[0];
		return true;
	}
	
	int s = 0, d = 0;
	for (int i = 0; i < ceil((double)q->length / 2); i++) {//向上取整
		for (int j = i + 1; j < q->length; j++) {
			if (q->data[j] == q->data[i]) s++;
			else d++;
			if (s >= ceil((double)q->length / 2) - 1 ) {
				*MainElem = q->data[i];
				return true;
			}
			if (d >= ceil((double)q->length / 2)) {
				s = d = 0;
				break;
			}
		}
	}

	return false;//无主元素，查找失败
}//SearchMainElem

void SearchMainELem_Demo() {
	SeqList q1;
	q1.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q1.data[0] = 2; q1.data[1] = 3; q1.data[2] = 7; q1.data[3] = 3; q1.data[4] = 3; q1.data[5] = 3; q1.data[6] = 3; q1.data[7] = 2;
	q1.length = 8;
	q1.MaxSize = InitSize;
	SeqList* x1 = &q1;

	int Main;
	if (SearchMainElem(x1, &Main)) printf_s("%d", Main);
	else printf_s("false");
}//SearchMainELem_Demo
//int main() {
//	SearchMainELem_Demo();
//}//验算成功
//时间复杂度O(n²),空间复杂度O(1)


//2.13
//想法：建立一个长度为n+1的标志数组，每一位代表1~n+2是否出现，遍历给定数组，最后检测标志数组中未出现最小的数
bool FindMinPositive(SeqList* q, int* min) {
	// 题中已经给了数组长度大于1，形参可以直接使用一个数组就行
	// if (!q || !q->length) return false;

	ElemType* L = (ElemType*)malloc(sizeof(ElemType) * (q->length + 1));
	if (!L) exit(0);

	// 直接用int数组就行，题中已经给了数组，并且你写L[i] = 0也代表这个
	// 类型是整形
	for (int i = 0; i < q->length + 1; i++) L[i] = 0;//初始化

	for (int i = 0; i < q->length; i++)
		if (q->data[i] <= q->length + 1 && q->data[i] > 0) L[q->data[i] - 1] = 1;

	for(int i = 0; i < q->length + 1; i++) 
		if (L[i] == 0) {
			*min = i + 1;
			return true;
		}

	*min = q->length+1;
	return false;//如果运行到这一步则出现未知情况，查找失败
}//FindMinPositive
//时间复杂度O(n),空间复杂度O(n)

//2.14
//定义三个标志t1,t2,t3分别指向三个数组，计算出他们的距离D。因为是升序排序，此时只有一定最小那个数的标志才有可能
//让距离变短，移动后如果距离变小就更新D。重复计算D和移动标志直到最小值无法向前移动，此时D为最小距离
int MinValue(int a, int b, int c) {//寻找三个值里最小的，t1最小返回1，以此类推
	if (a <= b) return a < c ? 1 : 3;
	if (a > b) return b < c ? 2 : 3;
}
bool FindMinDistance(SeqList* q1, SeqList* q2, SeqList* q3, int* dist) {
	if (!q1 || !q1->length||!q2 || !q2->length||!q3 || !q3->length) return false;

	int t1 = 0, t2 = 0, t3 = 0;
	int distance = abs(q1->data[t1] - q2->data[t2]) + abs(q1->data[t1] - q3->data[t3]) + abs(q2->data[t2] - q3->data[t3]);
	int min = MinValue(q1->data[t1], q2->data[t2], q3->data[t3]);

	int d;
	while (true) {
		if (min == 1) {
			if (t1++ >= q1->length - 1) break;
			d = abs(q1->data[t1] - q2->data[t2]) + abs(q1->data[t1] - q3->data[t3]) + abs(q2->data[t2] - q3->data[t3]);
			distance = d < distance ? d : distance;                    //更新distance
			min = MinValue(q1->data[t1], q2->data[t2], q3->data[t3]);  //更新min
		}
		else if (min == 2) {
			if (t2++ >= q2->length - 1) break;
			d = abs(q1->data[t1] - q2->data[t2]) + abs(q1->data[t1] - q3->data[t3]) + abs(q2->data[t2] - q3->data[t3]);
			distance = d < distance ? d : distance;
			min = MinValue(q1->data[t1], q2->data[t2], q3->data[t3]);
		}
		else {
			if (t3++ >= q3->length - 1) break;
			d = abs(q1->data[t1] - q2->data[t2]) + abs(q1->data[t1] - q3->data[t3]) + abs(q2->data[t2] - q3->data[t3]);
			distance = d < distance ? d : distance;
			min = MinValue(q1->data[t1], q2->data[t2], q3->data[t3]);
		}
	}

	*dist = distance;
	return true;
}//FindMinDistance

void FindMinDist_Demo() {
	SeqList q1;
	q1.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q1.data[0] = 2; q1.data[1] = 3; q1.data[2] = 7; q1.data[3] = 10; q1.data[4] = 20; q1.data[5] = 33; //q1.data[6] = 3; q1.data[7] = 2;
	q1.length = 6;
	q1.MaxSize = InitSize;
	SeqList* x1 = &q1;

	SeqList q2;
	q2.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q2.data[0] = 1; q2.data[1] = 3; q2.data[2] = 7; q2.data[3] = 13; //q1.data[4] = 3; q1.data[5] = 3; q1.data[6] = 3; q1.data[7] = 2;
	q2.length = 4;
	q2.MaxSize = InitSize;
	SeqList* x2 = &q2;

	SeqList q3;
	q3.data = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	q3.data[0] = 6; q3.data[1] = 10; q3.data[2] = 15; q3.data[3] = 19; q3.data[4] = 31; //q1.data[5] = 3; q1.data[6] = 3; q1.data[7] = 2;
	q3.length = 5;
	q3.MaxSize = InitSize;
	SeqList* x3 = &q3;

	int min;
	FindMinDistance(x1, x2, x3, &min);
	printf("%d", min);
}//FindMinDist_Demo
//int main() {
//	FindMinDist_Demo();
//}//验算成功
//时间复杂度O(n),空间复杂度O(1)