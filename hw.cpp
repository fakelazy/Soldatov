#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
double start_time, end_time;

	int N = atoi(argv[1]);
	int thr=0;
	cout << "N= " << N << endl;
//формируем массив
	int arr[N];  
  	for (unsigned int i = 0; i < N; ++i){
    		arr[i] = rand() % 201 - 100;
   		//cout << "arr[" << i << "]= " << arr[i] << "\n";
  	}
	int max_val = 0;

	for(thr=1; thr < 11; thr++){
	
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(thr) 
	{
	#pragma omp for
		for (int i = 0; i < N ; i++) {
               		if (arr[i] > max_val){
            			max_val = arr[i];
        		}
    		}
	}
	end_time = omp_get_wtime();
	cout << "thread = " << thr << endl;
	cout << "time= " << end_time-start_time << endl;
}
cout << "MAX= " << max_val << endl;

}