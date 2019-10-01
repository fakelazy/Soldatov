#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, ibuf;
	MPI_Status status;
	float rbuf;
	MPI_Init(&argc, &argv);	//������������� ����� ���������� MPI-��������� 
				//(����� ����������,��������� �� ������ ��������)

	MPI_Comm_size(MPI_COMM_WORLD, &size);	//������� ���������� ����� ��������� ����������� ������������ ���������.
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//������� ����������� ����� ��������. comm - ������������� ������

	ibuf = rank;	//������������ ibuf � ����� ��������
	rbuf = 1.0 * rank;	

	if(rank==1) MPI_Send(&ibuf, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);	//������������� ��������-���������� 5
	if(rank==2) MPI_Send(&rbuf, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD);	//������������� ��������-���������� 5

	cout << "rank out of cycle= " << rank << endl;

	if(rank==0){
		MPI_Probe(MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);	
		//������� 0 ���� ��������� �� ������ �� ��������� 1 � 2 � ����� � ��� �� �����
		//���������� ����� ���������� ������ ����� ������ ���
		//MPI_Probe ������� ����������, �� ���� ������ ��������� ���������
		//����� ��������� ����������� �� MPI_Probe � ������ ���������� ���������� ���������
		//MPI_Recv ��������� ���������

		if(status.MPI_SOURCE == 1){	//status.MPI_SOURCE- �������� ��������� ���������

			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);	//�������� ��������� � 1: if(rank==1)
			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);	//�������� ��������� �� 2: if(rank==2)

			cout << "rank cycle(1)= " << rank << endl;

			cout << "Process 0 recv " << ibuf << " from process 1, " << rbuf << " from process 2\n";
		}

		else if(status.MPI_SOURCE == 2){	//status.MPI_SOURCE- �������� ��������� ���������

			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);

			cout << "rank cycle(2)= " << rank << endl;

			cout << "Process 0 recv " << rbuf << " from process 2, " << ibuf << "from process 1\n";
		}
	}

MPI_Finalize();
}