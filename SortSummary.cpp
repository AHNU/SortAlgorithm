#include<iostream>
using namespace std;
#include<vector>
#include<stack>

// 1.ð������ʵ��
vector<int > BubbleSort(vector<int > array)
{
	int len = array.size(); // �������鳤��
	for(int i=0;i<len-1;i++) // ����len-1��
	{
		bool isSorted = true; // ����һ����������ʶ��ǰ�����Ƿ��Ѿ�����
		for(int j=0;j<len-1-i;j++) // �ӵ�һ��Ԫ�ؿ�ʼ�Ƚϣ�һֱ������len-1-i-1
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
			break; // ��ǰ�����Ѿ�����ֹͣ����
	}
	return array;
}

// 2.1 ����ʵ��(�ݹ�)
int partition(vector<int> &array, int begin, int end)
{
	int mid = (begin + end ) / 2;
	int temp = array[mid] ; // ���ѡ��һ��Ԫ�أ�����ѡ���м�Ԫ�أ�����������һ����λ
	array[mid] = array[end]; 
	// ������λ�������ǽ����һ��Ԫ�ط��������ѡ���Ԫ�أ��������м�Ԫ�أ��ϣ�������Ǹ�λ�ÿճ���
	int i = begin;
	int j = end;
	while(i<j)
	{
		while(i<j&&array[i]<=temp) // ��ǰ���ҵ����ڸ�Ԫ�ص�Ԫ��
			i++;
		array[j] =array[i];
		while(j>i&&array[j]>temp) // �Ӻ����ҵ�С�ڻ���ڸ�Ԫ�ص�Ԫ��
			j--;
		array[i] = array[j];
	}
	array[i] = temp;
	return i; // ����֮ǰѡ���Ԫ�����շ��õ�λ��
}

void QuickSort(vector<int > &array, int begin, int end)
{
	if(begin>=end)
		return ;
	// ����partition�����õ����Ԫ�ؾ���һ�ο��ź����շ��õ�λ��
	int index = partition(array, begin, end); 
	QuickSort(array,begin,index-1);
	QuickSort(array,index+1,end);
}

// 2.2 ����ʵ��(�ǵݹ�)
stack<int > waitSort;
void QuickSort2(vector<int > &array, int begin, int end)
{
	if(begin>=end)
		return ;
	int index = partition(array, begin, end); // ����һ�ο���
	if(index-1>begin) // ����������Ҫ������ջ
	{
		waitSort.push(index-1); // ���ڡ�ջ������ȳ����ص㣬���������Ҷ˵�
		waitSort.push(begin);
	}
	if(index+1<end) // ����������Ҫ������ջ
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
		index = partition(array, begin, end); // ����һ�ο���
		if(index-1>begin) // ����������Ҫ������ջ
		{
			waitSort.push(index-1); // ���ڡ�ջ������ȳ����ص㣬���������Ҷ˵�
			waitSort.push(begin);
		}
		if(index+1<end) 
		{
			waitSort.push(end);
			waitSort.push(index+1);
		}
	}
}

// 3 ��ѡ������
vector<int > SelectSort(vector<int > array)
{
	int len = array.size(); // �������鳤��
	for(int i=0;i<len-1;i++) // ����n-1��
	{
		int max = array[0]; // ��¼���ֵ
		int max_location = 0; // ���ֵ��λ��
		for(int j=0;j<len-i;j++) // ÿ�αȽϵ�len-1-i
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

// 4. ������
void AdjustHeap(vector<int > &array, int loc, int len) // ���������,�����õݹ�ʵ��
{
	if(2*loc+1<=len && array[loc]<array[2*loc+1]) // ������Ӵ���,���Ҹý���ֵС�����ӵ�ֵ����Ҫ����
	{
		int temp = array[loc];
		array[loc] = array[2*loc+1];
		array[2*loc+1] = temp;
		AdjustHeap(array, 2*loc+1, len); // �ݹ�������ӽ��
	}
	if(2*loc+2<=len && array[loc]<array[2*loc+2]) // ����Һ��Ӵ���,���Ҹý���ֵС���Һ��ӵ�ֵ����Ҫ����
	{
		int temp = array[loc];
		array[loc] = array[2*loc+2];
		array[2*loc+2] = temp; 
		AdjustHeap(array, 2*loc+2, len); // // �ݹ�����Һ��ӽ��
	}
}

void HeapSort(vector<int > &array)
{
	int len = array.size(); // �������鳤��
	/* ��������� */
	int i;
	for(i=len/2-1;i>=0;i--)// ����Ҷ�ӽ���Ƿ��ϴ���ѵ����ʣ����ֻ��Ҫ�ӵ�һ����Ҷ�ӽ����е�������(n0=n2+1);
		AdjustHeap(array,i,len);

	// ������ɣ������һ��Ԫ�ػ������Ҹö�������һ
	for(i=0;i<len-1;i++) // ����n-1�Σ�ÿ�εõ�һ��ʣ��Ԫ�ص����ֵ
	{
		int temp = array[0];
		array[0] = array[len-1-i];
		array[len-1-i] = temp;
		AdjustHeap(array, 0, len-i-2);
	}
}

// 5 ��������
void InsertSort(vector<int >&array)
{
	int len = array.size(); // �������鳤��
	for(int i= 1;i<len;i++) // �ӵڶ���Ԫ�ؿ�ʼ��ǰ������������в���
	{
		int temp = array[i];
		int j = i-1;
		while(j>=0&&array[j]>temp) // �ҵ���һ��������temp��λ��
		{
		
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = temp;
		
	}
}

// 6 �۰���������ԣ�

// 7 ϣ������
void Print(vector<int >array)
{
	for(int i=0;i<array.size();i++)
		cout<<array[i]<<ends;
	cout<<endl;
}

void ShellSort(vector<int >&array) // ����ϣ������
{
	int len = array.size(); // �������鳤��
	int index = len / 2; // �����������з��飬ÿ��Ԫ��֮�����index����
	while(index>=1)
	{
		for(int start=0;start<index;start++) // ����ǰ���鱻�ֳ�index�飬ÿ�����ʼԪ����ԭ�����е�λ��Ϊstart
		{
			for(int i= start+index;i<len;i=i+index) // ��ÿ��ڶ���Ԫ�ؿ�ʼ��ǰ������������в���
			{
				int temp = array[i];
				int j = i-index;
				while(j>=0&&array[j]>temp) // �ҵ���һ��������temp��λ��
				{
				
					array[j+index] = array[j];
					j = j - index;
				}
				array[j+index] = temp;	
			}
		}
		index = index / 2; // �����۰��С
	}
}

void ShellSort2(vector<int >&array) // �Ľ����ϣ������
{
	int len = array.size(); // �������鳤��
	int index = len / 2; // �����������з��飬ÿ��Ԫ��֮�����index����
	while(index>=1)
	{
		for(int i= index;i<len;i++) // �ӵ�index��Ԫ�ؿ�ʼ��ǰ������������в���
			                        //��ֱ�Ӳ���˼�����ƣ�ֻ������Ԫ��֮�����index��Ԫ��
		{
			int temp = array[i];
			int j = i-index;
			while(j>=0&&array[j]>temp) // �ҵ���һ��������temp��λ��
			{
			
				array[j+index] = array[j];
				j = j - index;
			}
			array[j+index] = temp;
			
		}
		//Print(array);
		index = index / 2; // �����۰����
	}
}


// 8. �鲢����
void Print(vector<int >array,int begin, int end)
{
	for(int i=begin;i<=end;i++)
		cout<<array[i]<<ends;
	cout<<endl;
}
void merge(vector<int> &array, int begin, int mid, int end) // ����һ���������ڹ鲢��ǰ���Ϊ[begin,mid], ����Ϊ[mid+1,end]
{
	vector<int > result ; // �����µ�������������鲢�Ľ��
	int i = begin;
	int j = mid+1;
	//Print(array, begin ,end);
	while(i<=mid && j<=end)
	{
		if(array[i]<=array[j]) // ȡС��
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
	while(i<=mid) // δ�ȶ�����ȫ�����μ��������鼴��
		result.push_back(array[i++]);
	while(j<=end) // ��while����һ��while���ҽ���һ����ִ��
		result.push_back(array[j++]);
	j = 0;
	for(i=begin;i<=end;i++)
		array[i] = result[j++]; // �ѹ鲢���������ԭ������
}

void mergeSort(vector<int >&array, int begin, int end) // �ݹ�ʵ�ֹ鲢����
{
	if(begin>=end)
		return ;
	int mid = (begin + end) / 2 ;
	mergeSort(array, begin, mid); // �ȹ鲢����������
	mergeSort(array, mid+1, end); // �ٹ鲢����������
	merge(array, begin, mid, end); // �ϲ���������
}

void mergeSort2(vector<int >&array) // �ǵݹ�ʵ�ֹ鲢����
{
	int len = array.size(); // �������鳤��
	for(int i=1;i<len;i=i*2) // ���ò���Ϊ1,2,4,8...
	{
		for(int j=0;j+2*i-1<len;j=j+2*i) 
			merge(array, j, j+i-1, j+2*i-1); // �鲢������������
		if(j<len)
			merge(array, j, j+i-1, len-1); // �鲢���ʣ����������飨����һ�����鳤��С��i��
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
