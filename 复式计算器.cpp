#define _CRT_SECURE_NO_WARNINGS
//复式计算器中文版本
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<Windows.h>

#define M 1/2   //兑现比例,可以修改，要用分数

int main(void)
{
	int BOND; //BOND作为初始手数,可以修改，要用整数
	int bond; //bond作为动态手数
	float cost_price;//成本价，自己修改
	float profit = 0, whole_cost;
	float price, pre_high = 130.0, now_high = 130.0, low = 120.0;
	//130没别的意思，就是为了第一次可以触发now_high的更新
	float reduce, restrain;//回撤参数|收敛参数
	char filename[50];
	FILE* fp;
	//版权声明
	printf("----------------------------------------------\n");
	printf("复式计算器\n");
	printf("逍遥开发，禁止商业使用，侵权必究\n");
	printf("----------------------------------------------\n\n");
	//写入初始参数
	if ((fp = fopen("配置文件.txt", "r,ccs = UTF-8")) == NULL)
	{
		printf("配置文件损坏，请保证内容格式正确，或者重新下载\n");
		Sleep(2000);
		exit(EXIT_FAILURE);
	}
	fwscanf(fp, L"转债手数:%d\n", &BOND);
	bond = BOND;
	fwscanf(fp, L"平均成本:%f\n", &cost_price);
	whole_cost = 10 * BOND * cost_price;
	fwscanf(fp, L"回撤参数:%f\n", &reduce);
	fwscanf(fp, L"收敛参数:%f\n", &restrain);
	fclose(fp);
	//写入最新价
	printf("输入转债名(中文名)后按[Enter]键 : ");
	scanf("%s", filename);
	strcat(filename, ".txt");
	if ((fp = fopen(filename, "a+")) == NULL)
	{
		printf("打开价格文件%s失败\n", filename);
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	printf("\n输入今天的收盘价 ");
	scanf("%f", &price);
	printf("总成本： %.2f\n\n", BOND * cost_price * 10);
	fprintf(fp, "%f\n", price);
	//循环读取历史所有价格
	rewind(fp);
	while (fscanf(fp, "%f", &price) != EOF)
	{
		printf("价格: %.2f\n", price);
		if (price < 130) //130验证门
		{
			printf("%.1f 价格低于130，忽略\n", price);
			continue;
		}
		if (price > now_high) //新高
		{
			now_high = price;

			if (now_high > pre_high)
			{
				pre_high = now_high;
				reduce = 10.0;
			}

			low = now_high - reduce;
		}
		if (price <= low) //到下限
		{
			printf("\n卖出 %d 手，卖出价： %.2f 元\n", bond / M, price);
			profit += 10 * (int)(bond / M) * (price - cost_price);//int多此一举
			printf("现在赚到 %.2f 的利润, 收益率： %.2f%%\n",
				profit, 100 * profit / whole_cost);
			bond = bond - bond / M;
			printf("还剩 %d 手\n\n", bond);

			now_high = price;
			reduce *= restrain;
			low = now_high - reduce;
		}
		if (bond == 1)
		{
			printf("\n最后一手了，是落袋为安还是留着看戏，看自己吧\n");
			break;
		}
	}
	fclose(fp);
	system("pause");

	return 0;
}


