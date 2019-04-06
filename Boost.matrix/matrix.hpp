#ifndef MATRIX_OPERATION
#define MATRIX_OPERATION
#include <type_traits>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
namespace matrix_and_operators{
	
	template <typename Condition>
		using EnableIf = typename std::enable_if<Condition::value>::type;
	template<typename T, EnableIf<std::is_arithmetic<T>>...>
	class matrix{
		private:			
			
			T ** matrix_container;
			int matrix_row;
			int matrix_col;	
		
		public:
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
			matrix operator+(const matrix& input_matrix) 
			{
				matrix return_value(matrix_row,matrix_col);
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
	};
} 
#endif 
