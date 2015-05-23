/**
	һ���̼߳��������Ĳ��ƽ��
	ѭ��1536��
**/
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "book.h"
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define THREAD_NUM 1024
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

//��������������Ӧ�����Ĳ��ƽ��
__global__ void vectorDistance(int *a, int *b, int *sum)
{
	unsigned int tid = threadIdx.x;
	if(tid < THREAD_NUM) //ֻ��0~1023���߳�
	{
		//ÿ���̼߳���1536��Ԫ��
		for(unsigned int i = tid; i < DATA_SIZE; i = i + THREAD_NUM)
			sum[i] = (a[i] - b[i]) * (a[i] - b[i]);
	}
}

int main()
{
	//�������϶�����������ʼ��Ϊ0
	int *a = new int[DATA_SIZE];
	memset(a, 0, sizeof(int) * DATA_SIZE);
	int *b = new int[DATA_SIZE];
	memset(b, 0, sizeof(int) * DATA_SIZE);
	int *sum = new int[DATA_SIZE];
	memset(sum, 0, sizeof(int) * DATA_SIZE);

	//�����������
	srand(time(NULL));
	genVector(a);
	genVector(b);

	//�����������϶�Ӧ���豸����
	int *dev_a, *dev_b, *dev_sum;
	//���豸�Ϸ���洢�ռ�
	HANDLE_ERROR(cudaMalloc((void**)&dev_a, sizeof(int) * DATA_SIZE)); 
	HANDLE_ERROR(cudaMalloc((void**)&dev_b, sizeof(int) * DATA_SIZE));
	HANDLE_ERROR(cudaMalloc((void**)&dev_sum, sizeof(int) * DATA_SIZE));
	//���������豸��
	HANDLE_ERROR(cudaMemcpy(dev_a, a, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice));

	//�����豸�ϵ�ִ��ʱ��
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//��ʱ��ʼ
	cudaEventRecord(start, 0); 
	//���豸�Ͻ��м���
	vectorDistance<<<1, THREAD_NUM>>>(dev_a, dev_b, dev_sum);
	//��ʱ����
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	//��ȡ��¼��ʱ��
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime,start,stop);
	cout << "GPU time: " << elapsedTime << endl;

	//�Ѽ��������豸����������
	HANDLE_ERROR(cudaMemcpy(sum, dev_sum, sizeof(int) * DATA_SIZE, cudaMemcpyDeviceToHost));
	//�ͷ��豸�洢�ռ�
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_b));
	HANDLE_ERROR(cudaFree(dev_sum));

	int result = 0;
	for(int i = 0; i < DATA_SIZE; i++)
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
