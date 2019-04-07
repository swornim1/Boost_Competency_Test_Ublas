/*Description: Example for * operator and execution speed of the * operator
 *
 * */
#include "../Boost.matrix/matrix.hpp"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main()
{	

	matrix_and_operators::matrix <float> A(2,2);
	matrix_and_operators::matrix <float> B(2,2);
	matrix_and_operators::matrix <float> C(2,2);
	std::ifstream A_file ("A.txt");
        std::ifstream B_file ("B.txt");
	std::ifstream C_file ("C.txt");
	A.load_matrix_from_file (A_file);
	B.load_matrix_from_file (B_file);
	C.load_matrix_from_file (C_file);
	matrix_and_operators::matrix<float> D(2,2);
	high_resolution_clock::time_point begin = high_resolution_clock::now();
	 D = A*B*C; 
	high_resolution_clock::time_point end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>( end-begin ).count();
	cout<<"Duration: "<<duration<< "\n";
	D.print_matrix();
 	return 0;
}
