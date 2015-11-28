//
//  SortingAlgorithm.cpp
//  YUSortingAlgorithm
//
//  Created by BruceYu on 12/10/24.
//  Copyright © 2012年 BruceYu. All rights reserved.
//

#include "SortingAlgorithm.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#include <iostream>
using namespace std;

/*******************************************************************************
	冒泡排序
 *******************************************************************************/
long Bubblesort(long R[], long n)
{
    int flag=1;						//当flag为0,则停止排序
    long BC=0;
    for(long i=1;i<n;i++)
    {								//i表示趟数,最多n-1趟
        flag=0;						//开始时元素未交换
        for(long j=n-1;j>=i;j--)
        {
            if(R[j]<R[j-1])			//发生逆序
            {
                long t=R[j];
                R[j]=R[j-1];
                R[j-1]=t;flag=1;   //交换,并标记发生了交换
            }
            BC++;
        }
    }
    return BC;
}


/*******************************************************************************
	选择排序
 *******************************************************************************/
long selectsort(long R[], long n)
{
    long i,j,m;long t,SC=0;
    for(i=0;i<n-1;i++)
    {
        m=i;
        for(j=i+1;j<n;j++)
        {
            SC++;
            if(R[j]<R[m]) m=j;
            if(m!=i)
            {
                t=R[i];
                R[i]=R[m];
                R[m]=t;
            }
        }
    }
    return SC;
}


/*******************************************************************************
	直接插入排序
 *******************************************************************************/
long insertsort(long R[], long n)
{
    long IC=0;
    for(long i=1;i<n;i++)			//i表示插入次数,共进行n-1次插入
    {
        long temp=R[i];				//把待排序元素赋给temp
        long j=i-1;
        while((j>=0)&&(temp<R[j]))
        {
            R[j+1]=R[j];j--;		//顺序比较和移动
            IC++;
        }
        IC++;
        R[j+1]=temp;
    }
    return IC;
}

/*******************************************************************************
	希尔排序
 *******************************************************************************/
long ShellSort(long R[], int n)
{
    long temp,SC=0;
    for(int i = n / 2; i > 0; i /= 2)					//将所有记录分成增量为t的子序列
    {
        for(int j = 0; j < i; j ++)						//对每个子序列进行插入排序
            for(int k = j + i; k < n; k += i)			//依次将记录插入有序子序列中
                for(int p = j; p < k; p += i)			//循环查找要插入的位置
                    if (R[k] < R[p]) {
                        temp = R[k];
                        for(int q = k; q > p; q -= i){	//插入位置以后的记录依次后移
                            R[q] = R[q - i];
                            SC++;
                        }
                        R[p] = temp;					//插入记录
                        break;
                    }
    }
    return SC;
}

/*******************************************************************************
	快速排序
 *******************************************************************************/
long quicksort(long R[], long left, long right)
{
    static long QC=0;
    long i=left,j=right;
    long temp=R[i];
    while(i<j)
    {
        while((R[j]>temp)&&(j>i))
        {
            QC++;
            j=j-1;
        }
        if(j>i)
        {
            R[i]=R[j];
            i=i+1;
            QC++;
        }
        while((R[i]<=temp)&&(j>i))
        {
            QC++;
            i=i+1;
        }
        if(i<j)
        {
            R[j]=R[i];
            j=j-1;
            QC++;
        }
    }
    //二次划分得到基准值的正确位置
    R[i]=temp;
    if(left<i-1)
        quicksort(R,left,i-1);		//递归调用左子区间
    if(i+1<right)
        quicksort(R,i+1,right);		//递归调用右子区间
    return QC;
}


/*******************************************************************************
	堆排序
 *******************************************************************************/
static long HC=0;
void Heap(long R[], int n)			//重新构造小顶堆
{
    long temp;
    for(int i = 0; i * 2 < n; i ++)
    {
        if (R[i] >= R[2 * i] && R[2 * i]) {
            temp = R[i];
            R[i] = R[2 * i];
            R[2 * i] = temp;
            HC++;
        }
        if (R[i] >= R[2 * i + 1] && R[2 * i + 1]) {
            temp = R[i];
            R[i] = R[2 * i + 1];
            R[2 * i + 1] = temp;
            HC++;
        }
    }
}

long HeapSort(long R[], int n)			//取出堆顶
{
    for(int i = n - 1; i >= 0; i --)
    {
        Heap(R, i);
        R[0] = R[i];
    }
    return HC;
}


/*******************************************************************************
	归并排序
 *******************************************************************************/
static long MC=0;
void Merge(long c[], long d[], int l, int m, int r)
{//合并c[1:m]和c[m+1:r]到d[1:r]
    int i = l, j = m + 1, k = l;
    while ((i <= m) && (j <= r)) {
        if (c[i] <= c[j])
            d[k ++] = c[i ++];
        else
            d[k ++] = c[j ++];
        MC++;
    }
    if (i > m)
        for(int q = j; q <= r; q ++)
            d[k ++] = c[q];
    else
        for(int q = i; q <= m; q ++)
            d[k ++] = c [q];
}

void Copy(long a[], long b[], int left, int right)
{
    for(int i = left; i <= right; i ++)
        a[i] = b[i];
}

long MergeSort(long a[], int left, int right)
{//递归将数组分成子数组
    long* b = new long [right + 1];
    if (left < right) {
        int i = (left + right) / 2;
        MergeSort(a, left, i);
        MergeSort(a, i + 1, right);
        Merge(a, b, left, i, right);
        Copy(a, b, left, right);
    }
    return MC;
}

/*******************************************************************************
	基数排序
 *******************************************************************************/
class node				//结点类
{
    friend class list;
public:
    int value;
    node* next;
    node(){value = 0; next = NULL;}
protected:
private:
};

class list				//链表类
{
public:
    void Insert(list& L, int value);
    node* head;
    list(){head = NULL;}
protected:
private:
};

void list::Insert(list &L, int value)			//插入结点
{
    node* N = new node;
    N->value = value;
    if (!L.head) {
        L.head = N;
    }
    else {
        node* p = L.head;
        while (p->next) {
            p = p->next;
        }
        p->next = N;
    }
}

long RadixSort(long R[], int n)
{
    list a[10];
    int i,RC=0;;
    for(int t = 1; t < 1000; t *= 10)
    {
        for(i = 0; i < 10; i ++)
        {
            int j = R[i] / t % 10;
            a[j].Insert(a[j], (int)R[i]);
        }
        int n = 0;
        for(i = 0; i < 10; i ++)
        {
            node* p = a[i].head;
            while (p) {
                R[n] = p->value;
                p = p->next;
                n ++;
            }
            a[i].head = NULL;
        }
    }
    return RC;
}



/*******************************************************************************
	操作选择函数
 *******************************************************************************/
void operate(long a[], int n)
{
    long * R = new long [n];
    time_t start, end;
    double dif;
    long degree;
    char ch;
    cout << "请选择排序算法：\t";
    cin >> ch;
    switch(ch){
        case '1':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = Bubblesort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "冒泡排序所用时间：\t" << dif << '\n';
            cout << "冒泡排序交换次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '2':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = selectsort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "选择排序所用时间：\t" << dif << '\n';
            cout << "选择排序交换次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '3':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = insertsort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "直接插入排序所用时间：  " << dif << '\n';
            cout << "直接插入排序交换次数：  " << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '4':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = ShellSort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "希尔插入排序所用时间：  " << dif << '\n';
            cout << "希尔插入排序交换次数：  " << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '5':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = quicksort(R, 0, n - 1);
            time(&end);
            dif = difftime(end, start);
            cout << "快速排序所用时间：\t" << dif << '\n';
            cout << "快速排序交换次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '6':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = HeapSort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "堆排序所用时间：\t" << dif << '\n';
            cout << "堆排序交换次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '7':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = MergeSort(R, 0, n);
            time(&end);
            dif = difftime(end, start);
            cout << "归并排序所用时间：\t" << dif << '\n';
            cout << "归并排序比较次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '8':
        {
            for(int i = 0; i < n; i ++)
            {
                R[i] = a[i];
            }
            time(&start);
            degree = RadixSort(R, n);
            time(&end);
            dif = difftime(end, start);
            cout << "基数排序所用时间：\t" << dif << '\n';
            cout << "基数排序交换次数：\t" << degree << '\n';
            cout << '\n';
            operate(a, n);
            break;
        }
        case '9':
            break;
        default:
        {
            cout << "输入错误，请选择正确的操作！" << '\n';
            break;
        }
    }
    
}

/*******************************************************************************
	主函数
 *******************************************************************************/
int main(int argc, const char * argv[]) {
    
    time_t first, second;
//    system("ipconfig");
     time(&first);
//    first = time(NULL);
    sleep(2000);
    time(&second);
//    second = time(NULL);
    printf("The difference is: %f seconds\n",difftime(second,first));
    
    
    // insert code here...
    cout<<"\n**              排序算法比较                      **"<<endl;
    cout<<"===================================================="<<endl;
    cout<<"**              1 --- 冒泡排序                    **"<<endl;
    cout<<"**              2 --- 选择排序                    **"<<endl;
    cout<<"**              3 --- 直接插入排序                **"<<endl;
    cout<<"**              4 --- 希尔排序                    **"<<endl;
    cout<<"**              5 --- 快速排序                    **"<<endl;
    cout<<"**              6 --- 堆排序                      **"<<endl;
    cout<<"**              7 --- 归并排序                    **"<<endl;
    cout<<"**              8 --- 基数排序                    **"<<endl;
    cout<<"**              9 --- 退出程序                    **"<<endl;
    cout<<"===================================================="<<endl;
    
    cout << "\n请输入要产生的随机数的个数：";
    int n;
    cin >> n;
    cout << endl;
    long *a = new long [n];
    srand((unsigned int)time(NULL));
    for (long i = 0; i < n; i ++)
    {
        a[i] = rand() % n;
    }
    
    operate(a, n);
    
    return 0;
}
