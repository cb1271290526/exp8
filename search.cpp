#include "search.h"

int main(void)
{
	int choice;
	iNum num;  //保存数据的结构体
	orderBtree* BT = NULL;
	int position;  //保存查找元素的位置
	while (true)
	{
		if (BT != NULL)
			cout << "二叉排序树不空" << endl;
		cout << "0.退出（删除二叉排序树）" << endl;
		cout << "1.数组二分查找" << endl;
		cout << "2.二叉排序树插入结点" << endl;
		cout << "3.二叉排序树查找元素" << endl;
		cout << "4.二叉排序树删除结点" << endl;
		cout << "5.构造平衡二叉树" << endl;
		cout << "6.删除二叉排序树" << endl;
		cout << "7.打印排序二叉树" << endl;
		cout << "请输入选项：";
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
				cout << "文件数据有：1.1.、1.2" << endl;
				if (create_array_from_file(&num) == false)
					break;
				int x;
				cout << "数字序列为" << endl;
				for (int i = 0; i <= num.tag; i++)
					cout << num.idata[i] << " ";
				cout << endl;
				while (true)
				{
					cout << "请输入查找元素（9999返回）：";
					cin >> x;
					if (x == 9999)
						break;
					position = Bisearch(&num, x);
					if (position == -1)
						cout << "元素不存在" << endl;
					else
						cout << "元素" << x << "下标：" << position << endl;
				}
				system("cls");
			}
			break;
		}
		case 2:
		{
			if (BT != NULL)
				cout << "二叉排序树不为空" << endl;
			while (true)
			{
				cout << "0.返回" << endl;
				cout << "1.手动输入数据" << endl;
				cout << "2.文件输入数据" << endl;
				int i;
				cin >> i;
				if (i == 0)
					break;
				system("cls");
				if (BT != NULL)  //树已存在，打印
				{
					mid_print_order_Btree(BT);
					cout << endl;
				}
				while (i == 1)
				{
					datatype x;
					orderBtree* p;
					cout << "请输入插入元素（9999退出）：";
					cin >> x;
					if (x == 9999)
						break;
					p = insert_order_Btree(BT, x);
					if (p == NULL)
						cout << "元素已存在";
					else
						mid_print_order_Btree(BT, p);
					cout << endl;
				}
				if (i == 2)
				{
					cout << "文件数据有：2.1.、2.2." << endl;
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
				cout << "二叉排序树为空，请先建立树" << endl;
				system("pause");
				break;
			}
			cout << "当前二叉树序列为：";
			mid_print_order_Btree(BT);
			cout << endl;
			while (true)
			{
				orderBtree* p = NULL;
				datatype x;
				cout << "请输入查找元素（9999退出）：";
				cin >> x;
				if (x == 9999)
					break;
				p = search_order_Btree(BT, x);
				if (p != NULL)
				{
					cout << "找到" << x << endl;
					mid_print_order_Btree(BT, p);
					cout << endl;
				}
				else
					cout << x << "不存在" << endl;
			}
			break;
		}
		case 4:
		{
			if (BT == NULL)
			{
				cout << "二叉排序树为空，请先建立" << endl;
				system("pause");
				break;
			}
			cout << "原排序树中序遍历" << endl;
			mid_print_order_Btree(BT);
			cout << endl;
			datatype x;
			while (true)
			{
				cout << "请输入删除元素（9999退出）：";
				cin >> x;
				if (x == 9999)
					break;
				cout << "删除前排序树中序遍历" << endl;
				mid_print_order_Btree(BT);
				cout << endl;
				delete_order_Btree(BT, x);
				cout << "删除后排序树中序遍历" << endl;
				mid_print_order_Btree(BT);
				cout << endl;
			}
			break;
		}
		case 5:
		{
			if (BT != NULL)
			{
				cout << "二叉排序树已存在，想创建新树请删除旧树" << endl;
				system("pause");
				break;
			}
			cout << "文件数据有：5.1、5.2" << endl;
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
			cout << "删除成功" << endl;
			system("pause");
			break;
		}
		case 7:
		{
			if (BT == NULL)
			{
				cout << "二叉排序树为空，请先建立树" << endl;
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