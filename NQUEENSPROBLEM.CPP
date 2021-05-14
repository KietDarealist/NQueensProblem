/*Họ và tên: Huỳnh Ngọc Tuấn Kiệt
MSSV: 20110508
Bài toán tám quân hậu.
*/

/*Bài toán tám quân hậu là bài toán đặt tám quân hậu trên bàn cờ
vua kích thước 8x8 sao cho không có quân hậu nào có thể ăn
được quân hậu khác*/

/*Hay nói cách khác là một cách xếp tám quân hậu trên bàn cờ sao
cho không có hai quân nào đứng trên cùng hàng, cùng cột hoặc cùng
đường chéo*/

#include<iostream>
#include<stdio.h>
using namespace std;
#define N 4

/*Các bước giải - src: geeksforgeeks*/
/*
1) Bắt đầu với cột đầu tiên từ trái đếm qua(cột 0)
2) Nếu N quân hậu đã được sắp xếp, trả về true.
3) Thử tất cả các dòng tại cột đang đứng
	Làm theo các bước sau trong mỗi lần thử dòng:

	a) Nếu quân hậu có thể đặt vào an toàn trong
	dòng này thì đánh dấu vị trí [dòng, cột] như
	là 1 trong những bước đến lời giải và thực hiện
	đệ quy kiểm tra nếu đặt quân hậu ở đây có thể
	dẫn đến lời giải cuối cùng.
	b) Nếu đặt quân hậu ở vị trí [dòng, cột] này
	có thể dẫn đến vị lời giải cuối cùng thì
	trả về true.
	c) Nếu đặt quân hậu ở vị trí [dòng, cột] này
	không dẫn đến lời giải cuối cùng thì xóa đánh
	dấu của vị trí [dòng, cột] này bằng BackTracking
	và thực hiện lại bước a để thử dòng khác.

4) Nếu tất cả các dòng đều đã được thử nhưng không
đem lại kết quả cuối cùng thì trả về false.*/

//Hàm dùng để in lời giải
void printSolution(int board[N][N])
{
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<N;j++)
		{
			cout.width(4);
			cout << board[i][j];
		}
		cout << endl;
	}

}

/*Hàm kiểm tra xem vị trí đó có an toàn hay không.
Giải thích: Thuật toán này cơ bản sử dụng đệ quy cho cột
nên không cần xét những điều kiện liên quan đến cột*/
bool isSafe(int board[N][N], int row, int col)
{
	int i, j;
	/*Kiểm tra các hàng ở bên trái xem có quân hậu
	nào đã được đặt chưa*/
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;
	/*Kiểm tra các vị trí của các đường chéo bên trái
	xem có quân hậu nào đã được đặt chưa*/
	//Kiểm tra các vị trí ở trên
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
	//Kiểm tra các vị trí ở dưới
   for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

	//Nếu tất cả điều kiện trên đã thỏa mãn
		return true;
}

//Hàm sử dụng đệ quy và backTracking để tìm lời giải
bool solveNQUtil(int board[N][N], int col)
{
	/*Điều kiện để dừng đệ quy*/
	if (col>=N)			//Tất cả các cột đều đã có quân hậu
		return true;

	/*Xem cét cột hiện tại và thử đặt quân hậu vào tất
	cả các hàng lần lượt*/
	for (int i=0;i<N;i++){
		/*Kiểm tra nếu quân hậu có thể đặt trên vị trí [i][cột]*/
		if (isSafe(board,i,col))
		{
			board[i][col]=1;

		/*Dùng đệ quy để xét hết tất cả cột*/
		if (solveNQUtil(board,col+1))
			return true;
		/*Nếu đặt quân hậu tại vị trí [i][cột] không dẫn
		đến lời giải cuối cùng, BackTracking để xóa đánh
		dấu của quân hậu, coi như chưa đi qua.*/
		board[i][col]=0;
	}
	}
	//Nếu không tìm được lời giải:
	return false;

}
//Hàm cuối cùng để chạy bài toán
bool solveNQ()
{
	int board[N][N]={
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};
	if (solveNQUtil(board,0)==false)
	{
		printf("Solution does not exist");
		return false;
	}
	printSolution(board);
	return true;
}

//Hàm main
int main()
{
	solveNQ();
	return 0;
}
