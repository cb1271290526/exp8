#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <queue>

using namespace std;
constexpr auto MAXLEN = 100;
typedef int datatype;

typedef struct  //顺序表结构
{
	datatype idata[MAXLEN] = { 0 };  //保存数据序列
	int tag = -1;  //记录最后一个元素下标
}iNum;

typedef struct orderBtree  //二叉排序树结点的结构
{
	datatype key;  //关键字
	struct orderBtree* left;  //左孩子
	struct orderBtree* right;  //右孩子
}orderBtree;


/*顺序表的创建与查找开始------------------------------------------------------*/
bool create_array_from_file(iNum* num);  //导入数据，构建数组
int Bisearch(iNum* num, datatype x);  //查找元素
/*----------------------------------------------------------------------------*/
//导入数据，构建数组
bool create_array_from_file(iNum* num)
{
	string filename;
	cout << "请输入文件名（#退出）" << endl;
	cin >> filename;
	if (filename == "#")
		return false;
	filename = "D:\\VS\\exp8\\searchdata\\" + filename + ".txt";

	ifstream file;
	file.open(filename, ios::in);
	if (!file)
	{
		cout << "文件打开失败" << endl;
		return false;
	}
	string line;
	getline(file, line);  //读取第一行数据
	file.close();

	int length = line.length();
	string temp;
	string::size_type posStart = 0, posEnd = 0;
	num->tag = -1;
	while (true)
	{
		posEnd = line.find(",", posStart);
		if (posEnd == string::npos)
			break;
		temp = line.substr(posStart, posEnd - posStart);
		num->tag++;
		num->idata[num->tag] = stoi(temp, 0, 10);
		posStart = posEnd + 1;
	}
	return true;
}

//查找元素
int Bisearch(iNum* num, datatype x)
{
	int low, high, mid;
	low = 0;
	high = num->tag;
	while (low <= high)
	{
		mid = (low + high) / 2;
		cout << "被比较元素：" << num->idata[mid] << "\t" << "下标：" << mid << endl;
		if (x == num->idata[mid])
		{
			cout << x << "已找到" << endl;
			return mid;
		}
		else if (x < num->idata[mid])
		{
			cout << x << "小于中间值" << num->idata[mid] << endl;
			high = mid - 1;
		}
		else
		{
			cout << x << "大于中间值" << num->idata[mid] << endl;
			low = mid + 1;
		}
	}
	return -1;  //查找不到x
}
/*顺序表的输入与查找结束------------------------------------------------------*/


/*数表的创建和查找开始--------------------------------------------------------*/
void mid_print_order_Btree(orderBtree*& BT, orderBtree* p = NULL);  //二叉排序树中序打印
void printfs_order_Btree(orderBtree*& BT);  //二叉排序树的父子边打印
orderBtree* locate_father(orderBtree*& BT, datatype x, int& pType);  //定位结点父结点并判断结点自身类型
orderBtree* insert_order_Btree(orderBtree*& BT, datatype x);  //二叉排序树插入结点
orderBtree* search_order_Btree(orderBtree*& BT, datatype x);  //二叉排序树查找元素
bool delete_order_Btree(orderBtree*& BT, datatype x);  //二叉排序树删除结点
int high_order_Btree(orderBtree*& BT);  //计算树高度
orderBtree* lowest_imbanlance(orderBtree*& BT, int& choice);  //查找最低不平衡点，并判断不平衡类型
void LL(orderBtree*& BT, orderBtree*& A);  //LL不平衡
void LR(orderBtree*& BT, orderBtree*& A);  //LR不平衡
void RL(orderBtree*& BT, orderBtree*& A);  //RL不平衡
void RR(orderBtree*& BT, orderBtree*& A);  //RR不平衡
void balance_order_Btree(orderBtree*& BT, iNum* num);  //构造平衡二叉树
void destroy_order_Btree(orderBtree*& BT);  //销毁二叉排序树
/*----------------------------------------------------------------------------*/

//二叉排序树中序打印
void mid_print_order_Btree(orderBtree*& BT, orderBtree* p)  //当二叉排序树有结点和p一样时，将其打括号标记
{
	if (BT != NULL)
	{
		mid_print_order_Btree(BT->left, p);
		if (p != NULL && BT->key == p->key)  //重点标记某个元素
			cout << "(";
		cout << BT->key << " ";
		if (p != NULL && BT->key == p->key)
			cout << ")";
		mid_print_order_Btree(BT->right, p);
	}
}

//二叉排序树的父子边打印
void printfs_order_Btree(orderBtree*& BT)
{
	queue<orderBtree*>QB;
	orderBtree* p;
	QB.push(BT);
	cout << "值\t" << "左子\t" << "右子\t" << endl;
	while (true)
	{
		if (QB.empty())
			break;
		p = QB.front();
		QB.pop();
		if (p->left != NULL || p->right != NULL)  //结点右子结点，打印
		{
			cout << p->key << "\t";
			if (p->left != NULL)
			{
				cout << p->left->key << "\t";
				QB.push(p->left);  //左子结点入队
			}
			else
				cout << "#" << "\t";
			if (p->right != NULL)
			{
				cout << p->right->key << "\t";
				QB.push(p->right);  //右子结点入队
			}
			else
				cout << "#" << "\t";
			cout << endl;
		}
	}
}

//定位结点父结点并判断结点自身类型
orderBtree* locate_father(orderBtree*& BT, datatype x, int& pType)
{//pType 1代表BT为左子结点，2代表BT为右子结点，0代表BT为根结点
	orderBtree* pf = BT;
	if (x == pf->key)  //BT为根结点
	{
		pType = 0;
		return pf;
	}
	while (true)
	{
		if (x < pf->key)
		{
			if (x == pf->left->key)  //BT为左子结点
			{
				pType = 1;
				return pf;
			}
			pf = pf->left;
		}
		else
		{
			if (x == pf->right->key)  //BT为右子结点
			{
				pType = 2;
				return pf;
			}
			pf = pf->right;
		}
	}
}

//二叉排序树插入结点
orderBtree* insert_order_Btree(orderBtree*& BT, datatype x)
{
	if (BT != NULL)
	{
		if (x < BT->key)  //插入位置左偏
			return insert_order_Btree(BT->left, x);
		else if (x > BT->key)  //插入位置右偏
			return insert_order_Btree(BT->right, x);
		else  //插入元素已存在
			return NULL;
	}
	else
	{
		BT = new orderBtree;
		BT->key = x;
		BT->left = NULL;
		BT->right = NULL;
		return BT;  //将插入结点返回
	}
}

//二叉排序树查找元素
orderBtree* search_order_Btree(orderBtree*& BT, datatype x)
{
	orderBtree* p = BT;
	while (p != NULL)
	{
		cout << "被比较元素：" << p->key << "\t";
		if (x == p->key)  //找到结点，返回
			return p;
		else if (x < p->key)  //查找结点左偏
		{
			cout << x << "比" << p->key << "小" << endl;
			p = p->left;
		}
		else if (x > p->key)  //查找结点右偏
		{
			cout << x << "比" << p->key << "大" << endl;
			p = p->right;
		}
	}
	return p;  //查找元素不存在
}

//二叉排序树删除结点
bool delete_order_Btree(orderBtree*& BT, datatype x)
{
	int pType = -1;
	orderBtree* p;  //待删除结点
	orderBtree* pf;  //p的父结点
	orderBtree* s;  //p的直接前驱
	orderBtree* sf;  //s的父结点

	//搜索待删除结点
	pf = locate_father(BT, x, pType);
	if (pType == -1)//无结点，删除失败
		return false;
	if (pType == 0)
		p = pf;
	else if (pType == 1)
		p = pf->left;
	else
		p = pf->right;
	if (p->left != NULL)  //有直接前驱
	{
		//搜索p的直接前驱
		sf = p;  //sf初始指向p	
		s = p->left;  //s初始指向p的左孩子
		while (s->right != NULL)  //反复搜索右分支
		{
			sf = s;	 //sf保存s父结点指针
			s = s->right;  //s右移
		}  //循环结束，s即为最右结点指针
		//删除结点
		p->key = s->key;
		if (sf == p)    //s为p（sf）左子树的根结点。
			sf->left = s->left;
		else
			sf->right = s->left;
		delete s;
	}
	else if (p->right != NULL)  //无直接前驱但有直接后驱
	{
		if (pType == 0)  //p为根结点,直接删除p
		{
			BT = BT->right;
			delete p;
		}
		else if (pType == 1)  //p为左子结点
		{
			pf->left = p->right;
			delete p;
		}
		else
		{
			pf->right = p->right;
			delete p;
		}
	}
	else
		delete p;  //无子结点

	return true;
}


/*构造平衡二叉树---------------------------------------------------------------*/
//计算树高度
int high_order_Btree(orderBtree*& BT)
{
	int high1 = 0;  //左子树高度
	int high2 = 0;  //右子树高度
	if (BT != NULL)
	{
		high1 = high_order_Btree(BT->left);
		high2 = high_order_Btree(BT->right);
		if (high1 < high2)
			high1 = high2;  //取子树中最高的
		high1++;
	}
	return high1;
}

//查找最低不平衡点，并判断不平衡类型
orderBtree* lowest_imbanlance(orderBtree*& BT, int& choice) 
{// choice返回二叉排序树不平衡的情况1,2,3,4分别代表LL，LR，RL，RR
	int gap1 = 0;  //最低不平衡点不平衡因子
	int gap2 = 0;  //不平衡点高度较高的子结点平衡因子
	orderBtree* p = NULL;
	if (BT != NULL)
	{
		p = lowest_imbanlance(BT->left, choice);
		if (p == NULL)  //左子结点平衡因子正常
			p = lowest_imbanlance(BT->right, choice);  //检测右子结点平衡因子
		if (p != NULL)  //右子结点平衡因子不正常，返回最低不平衡点
			return p;
		gap1 = high_order_Btree(BT->left) - high_order_Btree(BT->right);  //左右子结点正常，检测结点本身
		if (gap1 == 2)  //左子树过高于右子树
		{
			gap2 = high_order_Btree(BT->left->left) - high_order_Btree(BT->left->right);
			if (gap2 == 1)  //LL类型
			{
				choice = 1;
				return BT;
			}
			else  //LR类型
			{
				choice = 2;
				return BT;
			}
		}
		else if (gap1 == -2)  //右子树过高于左子树
		{
			gap2 = high_order_Btree(BT->right->left) - high_order_Btree(BT->right->right);
			if (gap2 == 1)  //RL类型
			{
				choice = 3;
				return BT;
			}
			else  //RR类型
			{
				choice = 4;
				return BT;
			}
		}
	}
	return p;
}

//LL不平衡
void LL(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A的父结点
	orderBtree* B = A->left;  //A的左子结点
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //定位A的父结点
	if (ADir == 0)  //A为根结点，调整B为根结点
		BT = B;
	else if (ADir == 1)  //A为左子结点
		Af->left = B;
	else if (ADir == 2)  //A为右子结点
		Af->right = B;
	A->left = B->right;
	B->right = A;
}
//LR不平衡
void LR(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A的父结点
	orderBtree* B = A->left;  //A的左子结点
	orderBtree* C = B->right;  //B的右子结点
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //定位A的父结点
	if (ADir == 0)  //A为根结点，调整C为根结点
		BT = C;
	else if (ADir == 1)  //A为左子结点
		Af->left = C;
	else if (ADir == 2)  //A为右子结点
		Af->right = C;
	B->right = C->left;
	A->left = C->right;
	C->right = A;
	C->left = B;
}
//RL不平衡
void RL(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A的父结点
	orderBtree* B = A->right;  //A的右子结点
	orderBtree* C = B->left;  //B的左子结点
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //定位A的父结点
	if (ADir == 0)  //A为根结点，调整C为根结点
		BT = C;
	else if (ADir == 1)  //A为左子结点
		Af->left = C;
	else if (ADir == 2)  //A为右子结点
		Af->right = C;
	B->left = C->right;
	A->right = C->left;
	C->left = A;
	C->right = B;
}
//RR不平衡
void RR(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A的父结点
	orderBtree* B = A->right;  //A的右子结点
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //定位A的父结点
	if (ADir == 0)  //A为根结点，调整B为根结点
		BT = B;
	else if (ADir == 1)  //A为左子结点
		Af->left = B;
	else if (ADir == 2)  //A为右子结点
		Af->right = B;
	A->right = B->left;
	B->left = A;
}

//平衡二叉排序树
void balance_order_Btree(orderBtree*& BT, iNum* num)
{
	int choice;
	orderBtree* A;  //最低不平衡点
	if (num->tag == -1)  //无元素
		return;
	for (int i = 0; i < num->tag; i++)
	{
		choice = 0;
		insert_order_Btree(BT, num->idata[i]);  //将数组元素插入平衡二叉排序树
		A = lowest_imbanlance(BT, choice);  //获取最低不平衡点
		switch (choice)  //选择不平衡类型，0为平衡
		{
		case 0:
			break;
		case 1:
			LL(BT, A);
			break;
		case 2:
			LR(BT, A);
			break;
		case 3:
			RL(BT, A);
			break;
		case 4:
			RR(BT, A);
			break;
		}
	}
}
/*构造平衡二叉树结束-----------------------------------------------------------*/

//销毁二叉排序树
void destroy_order_Btree(orderBtree*& BT)  //销毁二叉排序树
{
	if (BT != NULL)
	{
		destroy_order_Btree(BT->left);
		destroy_order_Btree(BT->right);
		delete BT;
	}
}

/*数表的创建和查找结束--------------------------------------------------------*/
#endif