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

typedef struct  //˳���ṹ
{
	datatype idata[MAXLEN] = { 0 };  //������������
	int tag = -1;  //��¼���һ��Ԫ���±�
}iNum;

typedef struct orderBtree  //�������������Ľṹ
{
	datatype key;  //�ؼ���
	struct orderBtree* left;  //����
	struct orderBtree* right;  //�Һ���
}orderBtree;


/*˳���Ĵ�������ҿ�ʼ------------------------------------------------------*/
bool create_array_from_file(iNum* num);  //�������ݣ���������
int Bisearch(iNum* num, datatype x);  //����Ԫ��
/*----------------------------------------------------------------------------*/
//�������ݣ���������
bool create_array_from_file(iNum* num)
{
	string filename;
	cout << "�������ļ�����#�˳���" << endl;
	cin >> filename;
	if (filename == "#")
		return false;
	filename = "D:\\VS\\exp8\\searchdata\\" + filename + ".txt";

	ifstream file;
	file.open(filename, ios::in);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		return false;
	}
	string line;
	getline(file, line);  //��ȡ��һ������
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

//����Ԫ��
int Bisearch(iNum* num, datatype x)
{
	int low, high, mid;
	low = 0;
	high = num->tag;
	while (low <= high)
	{
		mid = (low + high) / 2;
		cout << "���Ƚ�Ԫ�أ�" << num->idata[mid] << "\t" << "�±꣺" << mid << endl;
		if (x == num->idata[mid])
		{
			cout << x << "���ҵ�" << endl;
			return mid;
		}
		else if (x < num->idata[mid])
		{
			cout << x << "С���м�ֵ" << num->idata[mid] << endl;
			high = mid - 1;
		}
		else
		{
			cout << x << "�����м�ֵ" << num->idata[mid] << endl;
			low = mid + 1;
		}
	}
	return -1;  //���Ҳ���x
}
/*˳������������ҽ���------------------------------------------------------*/


/*����Ĵ����Ͳ��ҿ�ʼ--------------------------------------------------------*/
void mid_print_order_Btree(orderBtree*& BT, orderBtree* p = NULL);  //���������������ӡ
void printfs_order_Btree(orderBtree*& BT);  //�����������ĸ��ӱߴ�ӡ
orderBtree* locate_father(orderBtree*& BT, datatype x, int& pType);  //��λ��㸸��㲢�жϽ����������
orderBtree* insert_order_Btree(orderBtree*& BT, datatype x);  //����������������
orderBtree* search_order_Btree(orderBtree*& BT, datatype x);  //��������������Ԫ��
bool delete_order_Btree(orderBtree*& BT, datatype x);  //����������ɾ�����
int high_order_Btree(orderBtree*& BT);  //�������߶�
orderBtree* lowest_imbanlance(orderBtree*& BT, int& choice);  //������Ͳ�ƽ��㣬���жϲ�ƽ������
void LL(orderBtree*& BT, orderBtree*& A);  //LL��ƽ��
void LR(orderBtree*& BT, orderBtree*& A);  //LR��ƽ��
void RL(orderBtree*& BT, orderBtree*& A);  //RL��ƽ��
void RR(orderBtree*& BT, orderBtree*& A);  //RR��ƽ��
void balance_order_Btree(orderBtree*& BT, iNum* num);  //����ƽ�������
void destroy_order_Btree(orderBtree*& BT);  //���ٶ���������
/*----------------------------------------------------------------------------*/

//���������������ӡ
void mid_print_order_Btree(orderBtree*& BT, orderBtree* p)  //�������������н���pһ��ʱ����������ű��
{
	if (BT != NULL)
	{
		mid_print_order_Btree(BT->left, p);
		if (p != NULL && BT->key == p->key)  //�ص���ĳ��Ԫ��
			cout << "(";
		cout << BT->key << " ";
		if (p != NULL && BT->key == p->key)
			cout << ")";
		mid_print_order_Btree(BT->right, p);
	}
}

//�����������ĸ��ӱߴ�ӡ
void printfs_order_Btree(orderBtree*& BT)
{
	queue<orderBtree*>QB;
	orderBtree* p;
	QB.push(BT);
	cout << "ֵ\t" << "����\t" << "����\t" << endl;
	while (true)
	{
		if (QB.empty())
			break;
		p = QB.front();
		QB.pop();
		if (p->left != NULL || p->right != NULL)  //������ӽ�㣬��ӡ
		{
			cout << p->key << "\t";
			if (p->left != NULL)
			{
				cout << p->left->key << "\t";
				QB.push(p->left);  //���ӽ�����
			}
			else
				cout << "#" << "\t";
			if (p->right != NULL)
			{
				cout << p->right->key << "\t";
				QB.push(p->right);  //���ӽ�����
			}
			else
				cout << "#" << "\t";
			cout << endl;
		}
	}
}

//��λ��㸸��㲢�жϽ����������
orderBtree* locate_father(orderBtree*& BT, datatype x, int& pType)
{//pType 1����BTΪ���ӽ�㣬2����BTΪ���ӽ�㣬0����BTΪ�����
	orderBtree* pf = BT;
	if (x == pf->key)  //BTΪ�����
	{
		pType = 0;
		return pf;
	}
	while (true)
	{
		if (x < pf->key)
		{
			if (x == pf->left->key)  //BTΪ���ӽ��
			{
				pType = 1;
				return pf;
			}
			pf = pf->left;
		}
		else
		{
			if (x == pf->right->key)  //BTΪ���ӽ��
			{
				pType = 2;
				return pf;
			}
			pf = pf->right;
		}
	}
}

//����������������
orderBtree* insert_order_Btree(orderBtree*& BT, datatype x)
{
	if (BT != NULL)
	{
		if (x < BT->key)  //����λ����ƫ
			return insert_order_Btree(BT->left, x);
		else if (x > BT->key)  //����λ����ƫ
			return insert_order_Btree(BT->right, x);
		else  //����Ԫ���Ѵ���
			return NULL;
	}
	else
	{
		BT = new orderBtree;
		BT->key = x;
		BT->left = NULL;
		BT->right = NULL;
		return BT;  //�������㷵��
	}
}

//��������������Ԫ��
orderBtree* search_order_Btree(orderBtree*& BT, datatype x)
{
	orderBtree* p = BT;
	while (p != NULL)
	{
		cout << "���Ƚ�Ԫ�أ�" << p->key << "\t";
		if (x == p->key)  //�ҵ���㣬����
			return p;
		else if (x < p->key)  //���ҽ����ƫ
		{
			cout << x << "��" << p->key << "С" << endl;
			p = p->left;
		}
		else if (x > p->key)  //���ҽ����ƫ
		{
			cout << x << "��" << p->key << "��" << endl;
			p = p->right;
		}
	}
	return p;  //����Ԫ�ز�����
}

//����������ɾ�����
bool delete_order_Btree(orderBtree*& BT, datatype x)
{
	int pType = -1;
	orderBtree* p;  //��ɾ�����
	orderBtree* pf;  //p�ĸ����
	orderBtree* s;  //p��ֱ��ǰ��
	orderBtree* sf;  //s�ĸ����

	//������ɾ�����
	pf = locate_father(BT, x, pType);
	if (pType == -1)//�޽�㣬ɾ��ʧ��
		return false;
	if (pType == 0)
		p = pf;
	else if (pType == 1)
		p = pf->left;
	else
		p = pf->right;
	if (p->left != NULL)  //��ֱ��ǰ��
	{
		//����p��ֱ��ǰ��
		sf = p;  //sf��ʼָ��p	
		s = p->left;  //s��ʼָ��p������
		while (s->right != NULL)  //���������ҷ�֧
		{
			sf = s;	 //sf����s�����ָ��
			s = s->right;  //s����
		}  //ѭ��������s��Ϊ���ҽ��ָ��
		//ɾ�����
		p->key = s->key;
		if (sf == p)    //sΪp��sf���������ĸ���㡣
			sf->left = s->left;
		else
			sf->right = s->left;
		delete s;
	}
	else if (p->right != NULL)  //��ֱ��ǰ������ֱ�Ӻ���
	{
		if (pType == 0)  //pΪ�����,ֱ��ɾ��p
		{
			BT = BT->right;
			delete p;
		}
		else if (pType == 1)  //pΪ���ӽ��
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
		delete p;  //���ӽ��

	return true;
}


/*����ƽ�������---------------------------------------------------------------*/
//�������߶�
int high_order_Btree(orderBtree*& BT)
{
	int high1 = 0;  //�������߶�
	int high2 = 0;  //�������߶�
	if (BT != NULL)
	{
		high1 = high_order_Btree(BT->left);
		high2 = high_order_Btree(BT->right);
		if (high1 < high2)
			high1 = high2;  //ȡ��������ߵ�
		high1++;
	}
	return high1;
}

//������Ͳ�ƽ��㣬���жϲ�ƽ������
orderBtree* lowest_imbanlance(orderBtree*& BT, int& choice) 
{// choice���ض�����������ƽ������1,2,3,4�ֱ����LL��LR��RL��RR
	int gap1 = 0;  //��Ͳ�ƽ��㲻ƽ������
	int gap2 = 0;  //��ƽ���߶Ƚϸߵ��ӽ��ƽ������
	orderBtree* p = NULL;
	if (BT != NULL)
	{
		p = lowest_imbanlance(BT->left, choice);
		if (p == NULL)  //���ӽ��ƽ����������
			p = lowest_imbanlance(BT->right, choice);  //������ӽ��ƽ������
		if (p != NULL)  //���ӽ��ƽ�����Ӳ�������������Ͳ�ƽ���
			return p;
		gap1 = high_order_Btree(BT->left) - high_order_Btree(BT->right);  //�����ӽ������������㱾��
		if (gap1 == 2)  //������������������
		{
			gap2 = high_order_Btree(BT->left->left) - high_order_Btree(BT->left->right);
			if (gap2 == 1)  //LL����
			{
				choice = 1;
				return BT;
			}
			else  //LR����
			{
				choice = 2;
				return BT;
			}
		}
		else if (gap1 == -2)  //������������������
		{
			gap2 = high_order_Btree(BT->right->left) - high_order_Btree(BT->right->right);
			if (gap2 == 1)  //RL����
			{
				choice = 3;
				return BT;
			}
			else  //RR����
			{
				choice = 4;
				return BT;
			}
		}
	}
	return p;
}

//LL��ƽ��
void LL(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A�ĸ����
	orderBtree* B = A->left;  //A�����ӽ��
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //��λA�ĸ����
	if (ADir == 0)  //AΪ����㣬����BΪ�����
		BT = B;
	else if (ADir == 1)  //AΪ���ӽ��
		Af->left = B;
	else if (ADir == 2)  //AΪ���ӽ��
		Af->right = B;
	A->left = B->right;
	B->right = A;
}
//LR��ƽ��
void LR(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A�ĸ����
	orderBtree* B = A->left;  //A�����ӽ��
	orderBtree* C = B->right;  //B�����ӽ��
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //��λA�ĸ����
	if (ADir == 0)  //AΪ����㣬����CΪ�����
		BT = C;
	else if (ADir == 1)  //AΪ���ӽ��
		Af->left = C;
	else if (ADir == 2)  //AΪ���ӽ��
		Af->right = C;
	B->right = C->left;
	A->left = C->right;
	C->right = A;
	C->left = B;
}
//RL��ƽ��
void RL(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A�ĸ����
	orderBtree* B = A->right;  //A�����ӽ��
	orderBtree* C = B->left;  //B�����ӽ��
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //��λA�ĸ����
	if (ADir == 0)  //AΪ����㣬����CΪ�����
		BT = C;
	else if (ADir == 1)  //AΪ���ӽ��
		Af->left = C;
	else if (ADir == 2)  //AΪ���ӽ��
		Af->right = C;
	B->left = C->right;
	A->right = C->left;
	C->left = A;
	C->right = B;
}
//RR��ƽ��
void RR(orderBtree*& BT, orderBtree*& A)
{
	orderBtree* Af;  //A�ĸ����
	orderBtree* B = A->right;  //A�����ӽ��
	int ADir = -1;
	Af = locate_father(BT, A->key, ADir);  //��λA�ĸ����
	if (ADir == 0)  //AΪ����㣬����BΪ�����
		BT = B;
	else if (ADir == 1)  //AΪ���ӽ��
		Af->left = B;
	else if (ADir == 2)  //AΪ���ӽ��
		Af->right = B;
	A->right = B->left;
	B->left = A;
}

//ƽ�����������
void balance_order_Btree(orderBtree*& BT, iNum* num)
{
	int choice;
	orderBtree* A;  //��Ͳ�ƽ���
	if (num->tag == -1)  //��Ԫ��
		return;
	for (int i = 0; i < num->tag; i++)
	{
		choice = 0;
		insert_order_Btree(BT, num->idata[i]);  //������Ԫ�ز���ƽ�����������
		A = lowest_imbanlance(BT, choice);  //��ȡ��Ͳ�ƽ���
		switch (choice)  //ѡ��ƽ�����ͣ�0Ϊƽ��
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
/*����ƽ�����������-----------------------------------------------------------*/

//���ٶ���������
void destroy_order_Btree(orderBtree*& BT)  //���ٶ���������
{
	if (BT != NULL)
	{
		destroy_order_Btree(BT->left);
		destroy_order_Btree(BT->right);
		delete BT;
	}
}

/*����Ĵ����Ͳ��ҽ���--------------------------------------------------------*/
#endif