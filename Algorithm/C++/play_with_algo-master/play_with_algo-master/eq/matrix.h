#ifndef __MATRIX_H__
#define __MATRIX_H__
 
#include <vector>
 
template <typename T>
class CMatrix
{
public:
	explicit CMatrix() : m_array( 0 ) 
	{ }
 
	CMatrix( int rows, int cols) : m_array( rows )
	{
		for( int i = 0; i < rows; ++i )
		{
			m_array[i].resize( cols );
		}
	}
 	
 	CMatrix(T *m, int rows, int cols) : m_array( rows )
 	{
		for( int i = 0; i < rows; ++i )
		{
			m_array[i].assign(&m[i * cols], &m[i * cols + cols]);
		}
 	}

	CMatrix( const CMatrix<T>& m )
	{  *this = m; }
 
	void resize( int rows, int cols );           // �ı䵱ǰ�����С
	void swap_row( int row1, int row2 );         // �������е�����
 
	int  rows() const{ return m_array.size(); }
	int  cols() const { return rows() ? (m_array[0].size()) : 0; }
	bool empty() const { return rows() == 0; }        // �Ƿ�Ϊ��
	
	
	const std::vector<T>& operator[](int row) const { return m_array[row]; } //[]���������� 
    std::vector<T>& operator[](int row){ return m_array[row]; }
	
protected:
	std::vector< std::vector<T> > m_array;
};


#endif //__MATRIX_H__