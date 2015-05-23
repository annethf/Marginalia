/**
	ʹ�ù���洢��
	һ�η���32*1024���̣߳�ѭ��32��
**/

#ifndef __CUDACC__  
    #define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
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
	int sum = 0;
	float d = 0.0;
	for(int i = 0; i < DATA_SIZE; i++)
	{
		int temp = a[i] - b[i];
		sum += temp * temp;
	}
	d = sqrt((float)sum);
	return d;
}

__global__ void vectorDistance(int *a, int *b, int *sum)
{
	extern __shared__ int shared[];
	unsigned int tid = threadIdx.x;
	shared[tid] = 0;
	//һ�η���32*1024���߳�
	if(tid < BLOCK_NUM * THREAD_NUM)
	{
		for(unsigned int i = blockIdx.x * THREAD_NUM + tid; i < DATA_SIZE; i += BLOCK_NUM * THREAD_NUM)
			shared[tid] += (a[i] - b[i]) * (a[i] - b[i]);
		//�߳�ͬ��
		__syncthreads();
	}
	if(tid == 0)
	{
		for(int i = 1; i < THREAD_NUM; i++)
			shared[0] += shared[i];
		sum[blockIdx.x] = shared[0];
	}
}

int main()
{
	//�����϶�������
	int *a = new int[DATA_SIZE];
	memset(a, 0, sizeof(int) * DATA_SIZE);
	int *b = new int[DATA_SIZE];
	memset(b, 0, sizeof(int) * DATA_SIZE);
	int *sum = new int[BLOCK_NUM];
	memset(sum, 0, sizeof(int) * BLOCK_NUM);

	//�����������
	srand(time(NULL));
	genVector(a);
	genVector(b);

	//�豸�϶�����Ӧ����
	int *dev_a, *dev_b, *dev_sum;
	//���豸�Ͽ��ٴ洢�ռ�
	HANDLE_ERROR(cudaMalloc((void**)&dev_a, sizeof(int) * DATA_SIZE));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b, sizeof(int) * DATA_SIZE));
	HANDLE_ERROR(cudaMalloc((void**)&dev_sum, sizeof(int) * BLOCK_NUM));

	//�������ݵ��豸��
	HANDLE_ERROR(cudaMemcpy(dev_a, a, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));
	
	//�����豸��ִ��ʱ��
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//��ʱ��ʼ
	cudaEventRecord(start, 0);
	//���豸�Ͻ��м���
	vectorDistance<<<BLOCK_NUM, THREAD_NUM, THREAD_NUM * sizeof(int)>>>(dev_a, dev_b, dev_sum);
	//��ʱ����
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	//����GPU��ִ��ʱ��
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "GPU time: " << elapsedTime << endl;
	//�����������
	HANDLE_ERROR(cudaMemcpy(sum, dev_sum, sizeof(int) * BLOCK_NUM, cudaMemcpyDeviceToHost));
	//�ͷ��豸�洢�ռ�
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_b));
	HANDLE_ERROR(cudaFree(dev_sum));

	int result = 0;
	for(int i = 0; i < BLOCK_NUM; i++)
		result += sum[i];

	//�������
	float distance = sqrt((float)result);
	cout << "(GPU)distance = " << distance << endl;

	float d = 0.0;
	clock_t sTime = clock();
	d = dis(a, b);
	clock_t eTime = clock();
	cout << "CPU time: " << eTime - sTime << endl;
	cout << "(CPU)distance = " << d << endl;

	//�ͷ������ϵĴ洢�ռ�
	delete [] a;
	delete [] b;
	delete [] sum;
	system("pause");
    return 0;
}