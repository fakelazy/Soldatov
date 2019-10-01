#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
using namespace std;
int main(int argc, char *argv[]){

double start_time, end_time; //������ �������, ������������ �� ��������
int N = atoi(argv[1]); //������ ������, �������� � ��������� ������
cout << "N= " << N << endl;
double a[N][N], b[N][N], c[N][N]; //������ ���������� �������

int thr=0; //��������� ���������� �����
double t1, t2; //��������� �������
int i, j, k;   


// ������������� ������
	for (i=0; i<N; i++){
        	for (j=0; j<N; j++){
           		 a[i][j]=b[i][j]=(i+1)*(j+1);
        	}
   	}	

//����� �������
	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << a[i][j] << "\t"; 
		cout << endl;
	}*/

	//cout << endl << endl;

	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << b[i][j] << "\t"; 
		cout << endl;
	}*/


//������ ���������� ����� thr
    for(thr=1; thr < 10; thr++){
	start_time = omp_get_wtime();

	#pragma omp parallel shared(a, b, c) private(i, j, k) num_threads(thr)

 	#pragma omp for
        for(i=0; i<N; i++){

            for(j=0; j<N; j++){
                c[i][j] = 0.0;
	        for(k=0; k<N; k++) c[i][j]+=a[i][k]*b[k][j];
            }
        }
	
    cout << "thread = " << thr << endl; //���������� ����� ����
    end_time = omp_get_wtime();

	cout << "time= " << end_time-start_time << endl;
       	//cout << "effic= " << fix/(end_time-start_time) << endl; //�������������: t1/t, ��� t1 - ����� ������������
    }                                                           //����� �������, t - ����� ������������ �� n �������.
    

	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << c[i][j] << "\t"; 
		cout << endl;
	}*/
}