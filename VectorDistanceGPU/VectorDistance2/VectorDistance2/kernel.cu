/**
	多个block进行并行
	一次发动32*1024个线程
	循环48次
**/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "book.h"
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define BLOCK_NUM 32
#define	THREAD_NUM 1024
#define DATA_SIZE 1572864

void genVector(int *a)
{
	for(int i = 0; i < DATA_SIZE; i++)
		a[i] = rand() % 10;
}

float dis(int *a, int *b)
{
	int sum = 0.0;
	float d = 0.0;
	for(int i = 0; i < DATA_SIZE; i++)
	{
		float temp = a[i] - b[i];
		sum += temp * temp;
	}
	d = sqrt((float)sum);
	return d;
}

__global__ void vectorDistance(int *a, int *b, int *sum)
{
	unsigned int tid = threadIdx.x + blockIdx.x * blockDim.x;
	//一次发动32*1024个线程
	if(tid < BLOCK_NUM * THREAD_NUM)
	{
		for(unsigned int i = tid; i < DATA_SIZE; i += BLOCK_NUM * THREAD_NUM)
			sum[i] = (a[i] - b[i]) * (a[i] - b[i]);
	}
}

int main()
{
	//主机上定义向量
	int *a = new int[DATA_SIZE];
	memset(a, 0, sizeof(int) * DATA_SIZE);
	int *b = new int[DATA_SIZE];
	memset(b, 0, sizeof(int) * DATA_SIZE);
	int *sum = new int[DATA_SIZE];
	memset(sum, 0, sizeof(int) * DATA_SIZE);

	//随机生成向量
	srand(time(NULL));
	genVector(a);
	genVector(b);

	//设备上定义相应变量
	int *dev_a, *dev_b, *dev_sum;
	//在设备上开辟存储空间
	HANDLE_ERROR(cudaMalloc((void**)&dev_a, sizeof(int) * DATA_SIZE));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b, sizeof(int) * DATA_SIZE));
	HANDLE_ERROR(cudaMalloc((void**)&dev_sum, sizeof(int) * DATA_SIZE));

	//传输数据到设备上
	HANDLE_ERROR(cudaMemcpy(dev_a, a, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));
	
	//计算设备上执行时间
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//计时开始
	cudaEventRecord(start, 0);
	//在设备上进行计算
	vectorDistance<<<BLOCK_NUM, THREAD_NUM>>>(dev_a, dev_b, dev_sum);
	//计时结束
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	//计算GPU上执行时间
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "GPU time: " << elapsedTime << endl;

	//结果传回主机
	HANDLE_ERROR(cudaMemcpy(sum, dev_sum, sizeof(int) * DATA_SIZE, cudaMemcpyDeviceToHost));
	//释放设备存储空间
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_b));
	HANDLE_ERROR(cudaFree(dev_sum));

	int result = 0;
	for(int i = 0; i < DATA_SIZE; i++)
		result += sum[i];

	//计算距离
	float distance = sqrt((float)result);
	cout << "(GPU)distance = " << distance << endl;

	float d = 0.0;
	clock_t sTime = clock();
	d = dis(a, b);
	clock_t eTime = clock();
	cout << "CPU time: " << eTime - sTime << endl;
	cout << "(CPU)distance = " << d << endl;

	//释放主机上的存储空间
	delete [] a;
	delete [] b;
	delete [] sum;
	system("pause");
    return 0;
}

