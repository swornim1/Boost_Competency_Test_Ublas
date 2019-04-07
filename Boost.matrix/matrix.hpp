/***********************************************************************************************************************************************************
*Author: Swornim Baral																																	   *
*Description: Implementation of Matrix Class and different functionality including + , +=, -, -=, *, and loading a matrix from file 						   * 
***********************************************************************************************************************************************************/
#ifndef MATRIX_OPERATION
#define MATRIX_OPERATION
#include <type_traits>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
namespace matrix_and_operators{
	
	template <typename Condition>
	/*Template only allowing numerical types*/
	using EnableIf = typename std::enable_if<Condition::value>::type;
	template<typename T, EnableIf<std::is_arithmetic<T>>...>
	class matrix{
		private:			
			
			T ** matrix_container;
			int matrix_row;
			int matrix_col;	

			/*Structure made for passing three matrices for matrix multiplication*/	
			struct matrix_storage_structure
			{
				int row, col;
				int a_row, a_col, b_row, b_col;
			        T ** matrix_a;
				T ** matrix_b;
				T ** matrix_result;	
			};
		
		public:
			matrix()
			{
				matrix_row =0;
				matrix_col =0;
			}
			/*Constructor for  initializing matrix*/
			matrix(int row ,int col)
			{
				matrix_container =new T*[row];
				for(int i=0; i<col; i++)
				{		
					matrix_container[i]= new T[col];
				}
				matrix_row =row;
				matrix_col =col;
			}
			
			matrix operator+(const matrix& input_matrix) 
			{
				matrix return_value(matrix_row,matrix_col);

				/*Checking the dimensions of two matrices for determining the eligibility for addition*/
				if(this->matrix_col != input_matrix.matrix_col || this->matrix_row != input_matrix.matrix_row)
				{
					return_value.matrix_container = NULL;
					std::cout<<"Operation cannot be Performed ";
				}else
				{
					for (int i=0; i<matrix_row; i++)
					{
						for(int j=0; j<matrix_row; j++)
						{
							return_value.matrix_container[i][j] = matrix_container[i][j] + input_matrix.matrix_container[i][j];
						}
					}				
				}
				return return_value;
			
			}
            matrix operator-(const matrix& input_matrix)
            {
                matrix return_value(matrix_row,matrix_col);
                /*Checking the dimensions of two matrices for determining the eligibility for subtraction*/
                if(this->matrix_col != input_matrix.matrix_col || this->matrix_row != input_matrix.matrix_row)
                {
                                        return_value.matrix_container = NULL;
                                        std::cout<<"Operation cannot be Performed ";
                }else
                    {
                        for (int i=0; i<matrix_row; i++)
                        {
                            for(int j=0; j<matrix_row; j++)
                            {
                                return_value.matrix_container[i][j] = matrix_container[i][j] - input_matrix.matrix_container[i][j];
                            }
                        }
                    }

                return return_value;
              }
              
            void operator+=(const matrix& input_matrix)
            {
            	/*Checking the dimensions of two matrices for determining the eligibility for addition*/	
               	if(this->matrix_col != input_matrix.matrix_col || this->matrix_row != input_matrix.matrix_row)
               	{
                	std::cout<<"Operation cannot be Performed ";
                }
                else
                {
                    for(int i=0; i<matrix_row; i++)
                        {
                            for(int j=0; j<matrix_col; j++)
                                {
                                    this->matrix_container[i][j]+=input_matrix.matrix_container[i][j];
                                }
                        }
                }

              }

		void operator-=(const matrix& input_matrix)
			{
                
                /*Checking the dimensions of two matrices for determining the eligibility for addition*/
                if(this->matrix_col != input_matrix.matrix_col || this->matrix_row != input_matrix.matrix_row)
                {
                                        std::cout<<"Operation cannot be Performed ";
				}
				else
				{
					for(int i=0; i<matrix_row; i++)
					{
						for(int j=0; j<matrix_col; j++)
						{
							this->matrix_container[i][j]-=input_matrix.matrix_container[i][j];
						}
					}
				}
				
			}   

			/*Multiplication function takes in structures consisting of three matrices. Three matrices include two matrices that are multiplied
			and stored in a result matrix. The function calculates the sum of the product of row of matrix A and column of matrix B */
            static void * multiplication(void * structure)
            {
                matrix_storage_structure * calc = (matrix_storage_structure *) structure;
                T sum= 0;
                for (int i =0; i<calc->a_col; i++)
                {

                     sum= sum +((calc->matrix_a[calc->row][i])*(calc->matrix_b[i][calc->col]));
                }
                calc->matrix_result[calc->row][calc->col] = sum;
                pthread_exit((void *) structure);

            }

			matrix operator*(const matrix& input_matrix)
			{
				if(this->matrix_col == input_matrix.matrix_row)
				 {
				 	pthread_t * worker; 
					
					int number_of_threads= this->matrix_row * this->matrix_col;
					worker = new pthread_t[number_of_threads]; /*array of p_thread*/
					
					int index_for_worker = 0;
					
					matrix output(this->matrix_row, input_matrix.matrix_col);/*For storing output*/
					
					for(int i =0; i<this->matrix_row;i++)
					{
						for(int j=0; j<input_matrix.matrix_col; j++)
						{
							/*Declaring a storage structure to pass into multiplication function*/
							matrix_storage_structure * result_structure = new matrix_storage_structure;
							result_structure->row=i;
							result_structure->col =j;
							result_structure->a_row = this->matrix_row;
							result_structure->a_col = this->matrix_col; 
							result_structure->b_row = input_matrix.matrix_row;
							result_structure->b_col = input_matrix.matrix_col;
							result_structure->matrix_a = this->matrix_container;
							result_structure->matrix_b = input_matrix.matrix_container;
							result_structure->matrix_result = output.matrix_container;
						    
						    pthread_create(&(worker[index_for_worker]),NULL,multiplication,(void*)result_structure);
							index_for_worker++;

						}
					}

					for(int i=0; i<number_of_threads; i++)
					{
						pthread_join(worker[i], NULL);
					}
					
					return output;
				 
				 }else{
				 
				 	std::cout<<"Operation cannot be performed";
				 
				 }	
			}
			/*Loads a matrix from file*/
			void load_matrix_from_file(std::ifstream &input_file)
			{
				for (int i=0; i<matrix_row; i++)
				{      
					for (int j=0; j<matrix_col; j++)
					{
						input_file >> matrix_container[i][j]; 	
					}	
				}	
			}

			/*Print matrix  in output stream*/
			void print_matrix()
			{
				if(matrix_container ==NULL)
				{
					std::cout<<"Message Cannot be Printed"<<'\n';
				}
				{
					for (int i=0; i<matrix_row; i++)
					{	
						for (int j=0; j<matrix_col; j++)
						{
							std::cout<< matrix_container[i][j]<<" ";
						}
						std::cout<<'\n';
					}
				}	
			
			}
	};
} 
#endif 
