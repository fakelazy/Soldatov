#include <iostream>
#include "mpi.h"
#define NTIMES 100	//���������, ������������ ���������� ����������, ��� ��������� ������������ ����������
using namespace std;
int main(int argc, char **argv)
{
	double time_start, time_finish; //������� �������
	int rank, i; 	//���� ��������, �������

	int len; 	//� len ������������ ���������� �������� � �����
			//�� ����������� ��������� MPI_MAX_PROCESSOR_NAME.  

	char *name = new char;

	MPI_Init(&argc, &argv);		//������������� ����� ���������� MPI-��������� 
					//(����� ����������,��������� �� ������ ��������)

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//����������� ������ ��������(�����) � �������������
						///MPI_COMM ������������� ������
						
	MPI_Get_processor_name(name, &len); ////���������� � ������ name ��� ����, �� ������� ������� ��������� �������

	time_start = MPI_Wtime();	//������ ������� �������� �������

	for (i = 0; i<NTIMES; i++)
		time_finish = MPI_Wtime();
	cout << "processor " << name << ", process " << rank << "time = " << (time_finish-time_start)/NTIMES << endl;

MPI_Finalize();	//���������� ������������ ����� ����������
}