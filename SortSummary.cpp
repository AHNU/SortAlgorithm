#include<iostream>
using namespace std;
#include<vector>
#include<stack>

// 1.冒泡排序实现
vector<int > BubbleSort(vector<int > array)
{
	int len = array.size(); // 计算数组长度
	for(int i=0;i<len-1;i++) // 遍历len-1遍
	{
		bool isSorted = true; // 设置一个变量来标识当前数组是否已经有序
		for(int j=0;j<len-1-i;j++) // 从第一个元素开始比较，一直遍历到len-1-i-1
		{
			if(array[j]>array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				isSorted = false;
			}
		}
		if(isSorted==true)
			break; // 当前数组已经有序，停止遍历
	}
	return array;
}

// 2.1 快排实现(递归)
int partition(vector<int> &array, int begin, int end)
{
	int mid = (begin + end ) / 2;
	int temp = array[mid] ; // 随机选择一个元素，这里选择中间元素，并对其设置一个哨位
	array[mid] = array[end]; 
	// 设置哨位的作用是将最后一个元素放置在随机选择的元素（这里是中间元素）上，把最后那个位置空出来
	int i = begin;
	int j = end;
	while(i<j)
	{
		while(i<j&&array[i]<=temp) // 从前面找到大于该元素的元素
			i++;
		array[j] =array[i];
		while(j>i&&array[j]>temp) // 从后面找到小于或等于该元素的元素
			j--;
		array[i] = array[j];
	}
	array[i] = temp;
	return i; // 返回之前选择的元素最终放置的位置
}

void QuickSort(vector<int > &array, int begin, int end)
{
	if(begin>=end)
		return ;
	// 调用partition函数得到随机元素经过一次快排后最终放置的位置
	int index = partition(array, begin, end); 
	QuickSort(array,begin,index-1);
	QuickSort(array,index+1,end);
}

// 2.2 快排实现(非递归)
stack<int > waitSort;
void QuickSort2(vector<int > &array, int begin, int end)
{
	if(begin>=end)
		return ;
	int index = partition(array, begin, end); // 进行一次快排
	if(index-1>begin) // 若左区间需要排序，入栈
	{
		waitSort.push(index-1); // 由于“栈”后进先出的特点，先入区间右端点
		waitSort.push(begin);
	}
	if(index+1<end) // 若右区间需要排序，入栈
	{
		waitSort.push(end);
		waitSort.push(index+1);
	}
	while(!waitSort.empty())
	{
		begin = waitSort.top();
		waitSort.pop();
		end = waitSort.top();
		waitSort.pop();
		index = partition(array, begin, end); // 进行一次快排
		if(index-1>begin) // 若左区间需要排序，入栈
		{
			waitSort.push(index-1); // 由于“栈”后进先出的特点，先入区间右端点
			waitSort.push(begin);
		}
		if(index+1<end) 
		{
			waitSort.push(end);
			waitSort.push(index+1);
		}
	}
}

// 3 简单选择排序
vector<int > SelectSort(vector<int > array)
{
	int len = array.size(); // 计算数组长度
	for(int i=0;i<len-1;i++) // 遍历n-1遍
	{
		int max = array[0]; // 记录最大值
		int max_location = 0; // 最大值的位置
		for(int j=0;j<len-i;j++) // 每次比较到len-1-i
		{
			if(array[j]>=max)
			{
				max = array[j];
				max_location = j;
			}
		}
		array[max_location] = array[len-1-i];
		array[len-1-i] = max;		
	}
	return array;
}

// 4. 堆排序
void AdjustHeap(vector<int > &array, int loc, int len) // 调整大根堆,这里用递归实现
{
	int left = 2*loc + 1; // 记录左孩子的位置
	int right = 2*loc + 2; // 记录右孩子的位置
	int largest = loc; // 记录当前结点、左孩子结点、右孩子结点中最大值的位置
	if(left<=len && array[largest]<array[left]) // 如果左孩子存在,并且该结点的值小于左孩子的值,最大值为左孩子结点
	{
		largest = left;
	}
	if(right<=len && array[largest]<array[right]) // 如果右孩子存在,并且该结点的值小于右孩子的值，最大值为右孩子结点
	{
		largest = right;
	}
	if(largest!=loc) // 只有在当前结点不是最大值的情况下才需要进一步调整
	{
		int temp = array[loc];
		array[loc] = array[largest];
		array[largest] = temp; 
		AdjustHeap(array, largest, len); // // 递归调整与父结点交换的那个孩子结点
	}
}

void HeapSort(vector<int > &array)
{
	int len = array.size(); // 计算数组长度
	/* 构建大根堆 */
	int i;
	for(i=len/2-1;i>=0;i--)// 由于叶子结点是符合大根堆的性质，因此只需要从第一个非叶子结点进行调整即可(n0=n2+1);
		AdjustHeap(array,i,len);

	// 构建完成，与最后一个元素互换，且该堆数量减一
	for(i=0;i<len-1;i++) // 调整n-1次，每次得到一个剩下元素的最大值
	{
		int temp = array[0];
		array[0] = array[len-1-i];
		array[len-1-i] = temp;
		AdjustHeap(array, 0, len-i-2);
	}
}

// 5 插入排序
void InsertSort(vector<int >&array)
{
	int len = array.size(); // 计算数组长度
	for(int i= 1;i<len;i++) // 从第二个元素开始往前面的有序数组中插入
	{
		int temp = array[i];
		int j = i-1;
		while(j>=0&&array[j]>temp) // 找到第一个不大于temp的位置
		{
		
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = temp;
		
	}
}

// 6 折半插入排序（略）

// 7 希尔排序
void Print(vector<int >array)
{
	for(int i=0;i<array.size();i++)
		cout<<array[i]<<ends;
	cout<<endl;
}

void ShellSort(vector<int >&array) // 基本希尔排序
{
	int len = array.size(); // 计算数组长度
	int index = len / 2; // 设置增量进行分组，每组元素之间相隔index个数
	while(index>=1)
	{
		for(int start=0;start<index;start++) // 代表当前数组被分成index组，每组的起始元素在原数组中的位置为start
		{
			for(int i= start+index;i<len;i=i+index) // 从每组第二个元素开始往前面的有序数组中插入
			{
				int temp = array[i];
				int j = i-index;
				while(j>=0&&array[j]>temp) // 找到第一个不大于temp的位置
				{
				
					array[j+index] = array[j];
					j = j - index;
				}
				array[j+index] = temp;	
			}
		}
		index = index / 2; // 增量折半减小
	}
}

void ShellSort2(vector<int >&array) // 改进后的希尔排序
{
	int len = array.size(); // 计算数组长度
	int index = len / 2; // 设置增量进行分组，每组元素之间相隔index个数
	while(index>=1)
	{
		for(int i= index;i<len;i++) // 从第index个元素开始往前面的有序数组中插入
			                        //和直接插入思想类似，只是相邻元素之间相隔index个元素
		{
			int temp = array[i];
			int j = i-index;
			while(j>=0&&array[j]>temp) // 找到第一个不大于temp的位置
			{
			
				array[j+index] = array[j];
				j = j - index;
			}
			array[j+index] = temp;
			
		}
		//Print(array);
		index = index / 2; // 增量折半减少
	}
}


// 8. 归并排序
void Print(vector<int >array,int begin, int end)
{
	for(int i=begin;i<=end;i++)
		cout<<array[i]<<ends;
	cout<<endl;
}
void merge(vector<int> &array, int begin, int mid, int end) // 定义一个函数用于归并，前半段为[begin,mid], 后半段为[mid+1,end]
{
	vector<int > result ; // 定义新的数组用来保存归并的结果
	int i = begin;
	int j = mid+1;
	//Print(array, begin ,end);
	while(i<=mid && j<=end)
	{
		if(array[i]<=array[j]) // 取小的
		{
			result.push_back(array[i]);
			i++;
		}
		else
		{
			result.push_back(array[j]);
			j++;
		}
	}
	while(i<=mid) // 未比对完则全部依次加入结果数组即可
		result.push_back(array[i++]);
	while(j<=end) // 该while与上一个while有且仅有一个会执行
		result.push_back(array[j++]);
	j = 0;
	for(i=begin;i<=end;i++)
		array[i] = result[j++]; // 把归并结果拷贝到原数组中
}

void mergeSort(vector<int >&array, int begin, int end) // 递归实现归并排序
{
	if(begin>=end)
		return ;
	int mid = (begin + end) / 2 ;
	mergeSort(array, begin, mid); // 先归并排序左区间
	mergeSort(array, mid+1, end); // 再归并排序右区间
	merge(array, begin, mid, end); // 合并左右区间
}

void mergeSort2(vector<int >&array) // 非递归实现归并排序
{
	int len = array.size(); // 计算数组长度
	for(int i=1;i<len;i=i*2) // 设置步长为1,2,4,8...
	{
		for(int j=0;j+2*i-1<len;j=j+2*i) 
			merge(array, j, j+i-1, j+2*i-1); // 归并相邻两个数组
		if(j<len)
			merge(array, j, j+i-1, len-1); // 归并最后剩余的两个数组（其中一个数组长度小于i）
	}
}

int main()
{
	int a[] ={5, 3, 6, 5, 2, 1, 5};
	vector<int > array(a, a+sizeof(a)/sizeof(int));
	//vector<int > result = BubbleSort(array);
	//QuickSort2(array, 0 , array.size()-1);
	//vector<int > result = SelectSort(array);
	//HeapSort(array);
	//InsertSort(array);
	ShellSort2(array);
	//mergeSort2(array);
	vector<int > result = array;
	for(int i=0;i<result.size();i++)
		cout<<result[i]<<ends;
	cout<<endl;
	return 0;
}
