#define _CRT_SECURE_NO_WARNINGS
//��ʽ���������İ汾
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<Windows.h>

#define M 1/2   //���ֱ���,�����޸ģ�Ҫ�÷���

int main(void)
{
	int BOND; //BOND��Ϊ��ʼ����,�����޸ģ�Ҫ������
	int bond; //bond��Ϊ��̬����
	float cost_price;//�ɱ��ۣ��Լ��޸�
	float profit = 0, whole_cost;
	float price, pre_high = 130.0, now_high = 130.0, low = 120.0;
	//130û�����˼������Ϊ�˵�һ�ο��Դ���now_high�ĸ���
	float reduce, restrain;//�س�����|��������
	char filename[50];
	FILE* fp;
	//��Ȩ����
	printf("----------------------------------------------\n");
	printf("��ʽ������\n");
	printf("��ң��������ֹ��ҵʹ�ã���Ȩ�ؾ�\n");
	printf("----------------------------------------------\n\n");
	//д���ʼ����
	if ((fp = fopen("�����ļ�.txt", "r,ccs = UTF-8")) == NULL)
	{
		printf("�����ļ��𻵣��뱣֤���ݸ�ʽ��ȷ��������������\n");
		Sleep(2000);
		exit(EXIT_FAILURE);
	}
	fwscanf(fp, L"תծ����:%d\n", &BOND);
	bond = BOND;
	fwscanf(fp, L"ƽ���ɱ�:%f\n", &cost_price);
	whole_cost = 10 * BOND * cost_price;
	fwscanf(fp, L"�س�����:%f\n", &reduce);
	fwscanf(fp, L"��������:%f\n", &restrain);
	fclose(fp);
	//д�����¼�
	printf("����תծ��(������)��[Enter]�� : ");
	scanf("%s", filename);
	strcat(filename, ".txt");
	if ((fp = fopen(filename, "a+")) == NULL)
	{
		printf("�򿪼۸��ļ�%sʧ��\n", filename);
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	printf("\n�����������̼� ");
	scanf("%f", &price);
	printf("�ܳɱ��� %.2f\n\n", BOND * cost_price * 10);
	fprintf(fp, "%f\n", price);
	//ѭ����ȡ��ʷ���м۸�
	rewind(fp);
	while (fscanf(fp, "%f", &price) != EOF)
	{
		printf("�۸�: %.2f\n", price);
		if (price < 130) //130��֤��
		{
			printf("%.1f �۸����130������\n", price);
			continue;
		}
		if (price > now_high) //�¸�
		{
			now_high = price;

			if (now_high > pre_high)
			{
				pre_high = now_high;
				reduce = 10.0;
			}

			low = now_high - reduce;
		}
		if (price <= low) //������
		{
			printf("\n���� %d �֣������ۣ� %.2f Ԫ\n", bond / M, price);
			profit += 10 * (int)(bond / M) * (price - cost_price);//int���һ��
			printf("����׬�� %.2f ������, �����ʣ� %.2f%%\n",
				profit, 100 * profit / whole_cost);
			bond = bond - bond / M;
			printf("��ʣ %d ��\n\n", bond);

			now_high = price;
			reduce *= restrain;
			low = now_high - reduce;
		}
		if (bond == 1)
		{
			printf("\n���һ���ˣ������Ϊ���������ſ�Ϸ�����Լ���\n");
			break;
		}
	}
	fclose(fp);
	system("pause");

	return 0;
}


