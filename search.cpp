#include "search.h"

int main(void)
{
	int choice;
	iNum num;  //�������ݵĽṹ��
	orderBtree* BT = NULL;
	int position;  //�������Ԫ�ص�λ��
	while (true)
	{
		if (BT != NULL)
			cout << "��������������" << endl;
		cout << "0.�˳���ɾ��������������" << endl;
		cout << "1.������ֲ���" << endl;
		cout << "2.����������������" << endl;
		cout << "3.��������������Ԫ��" << endl;
		cout << "4.����������ɾ�����" << endl;
		cout << "5.����ƽ�������" << endl;
		cout << "6.ɾ������������" << endl;
		cout << "7.��ӡ���������" << endl;
		cout << "������ѡ�";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 0:
		{
			if (BT != NULL)
				destroy_order_Btree(BT);
			return 0;
		}

		case 1:
		{
			while (true)
			{
				cout << "�ļ������У�1.1.��1.2" << endl;
				if (create_array_from_file(&num) == false)
					break;
				int x;
				cout << "��������Ϊ" << endl;
				for (int i = 0; i <= num.tag; i++)
					cout << num.idata[i] << " ";
				cout << endl;
				while (true)
				{
					cout << "���������Ԫ�أ�9999���أ���";
					cin >> x;
					if (x == 9999)
						break;
					position = Bisearch(&num, x);
					if (position == -1)
						cout << "Ԫ�ز�����" << endl;
					else
						cout << "Ԫ��" << x << "�±꣺" << position << endl;
				}
				system("cls");
			}
			break;
		}
		case 2:
		{
			if (BT != NULL)
				cout << "������������Ϊ��" << endl;
			while (true)
			{
				cout << "0.����" << endl;
				cout << "1.�ֶ���������" << endl;
				cout << "2.�ļ���������" << endl;
				int i;
				cin >> i;
				if (i == 0)
					break;
				system("cls");
				if (BT != NULL)  //���Ѵ��ڣ���ӡ
				{
					mid_print_order_Btree(BT);
					cout << endl;
				}
				while (i == 1)
				{
					datatype x;
					orderBtree* p;
					cout << "���������Ԫ�أ�9999�˳�����";
					cin >> x;
					if (x == 9999)
						break;
					p = insert_order_Btree(BT, x);
					if (p == NULL)
						cout << "Ԫ���Ѵ���";
					else
						mid_print_order_Btree(BT, p);
					cout << endl;
				}
				if (i == 2)
				{
					cout << "�ļ������У�2.1.��2.2." << endl;
					if (create_array_from_file(&num) != false)
					{
						for (int j = 0; j <= num.tag; j++)
							insert_order_Btree(BT, num.idata[j]);
						mid_print_order_Btree(BT);
						cout << endl;
						system("pause");
					}
				}
				system("cls");
			}
			break;
		}
		case 3:
		{
			if (BT == NULL)
			{
				cout << "����������Ϊ�գ����Ƚ�����" << endl;
				system("pause");
				break;
			}
			cout << "��ǰ����������Ϊ��";
			mid_print_order_Btree(BT);
			cout << endl;
			while (true)
			{
				orderBtree* p = NULL;
				datatype x;
				cout << "���������Ԫ�أ�9999�˳�����";
				cin >> x;
				if (x == 9999)
					break;
				p = search_order_Btree(BT, x);
				if (p != NULL)
				{
					cout << "�ҵ�" << x << endl;
					mid_print_order_Btree(BT, p);
					cout << endl;
				}
				else
					cout << x << "������" << endl;
			}
			break;
		}
		case 4:
		{
			if (BT == NULL)
			{
				cout << "����������Ϊ�գ����Ƚ���" << endl;
				system("pause");
				break;
			}
			cout << "ԭ�������������" << endl;
			mid_print_order_Btree(BT);
			cout << endl;
			datatype x;
			while (true)
			{
				cout << "������ɾ��Ԫ�أ�9999�˳�����";
				cin >> x;
				if (x == 9999)
					break;
				cout << "ɾ��ǰ�������������" << endl;
				mid_print_order_Btree(BT);
				cout << endl;
				delete_order_Btree(BT, x);
				cout << "ɾ�����������������" << endl;
				mid_print_order_Btree(BT);
				cout << endl;
			}
			break;
		}
		case 5:
		{
			if (BT != NULL)
			{
				cout << "�����������Ѵ��ڣ��봴��������ɾ������" << endl;
				system("pause");
				break;
			}
			cout << "�ļ������У�5.1��5.2" << endl;
			if (create_array_from_file(&num) == false)
				break;
			balance_order_Btree(BT, &num);
			printfs_order_Btree(BT);
			system("pause");
			break;
		}
		case 6:
		{
			destroy_order_Btree(BT);
			BT = NULL;
			cout << "ɾ���ɹ�" << endl;
			system("pause");
			break;
		}
		case 7:
		{
			if (BT == NULL)
			{
				cout << "����������Ϊ�գ����Ƚ�����" << endl;
				system("pause");
				break;
			}
			mid_print_order_Btree(BT);
			cout << endl;
			printfs_order_Btree(BT);
			system("pause");
		}
		}
		system("cls");
	}
}