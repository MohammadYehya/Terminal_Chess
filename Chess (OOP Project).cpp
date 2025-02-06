#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <fstream>
#define DEAD false
#define ALIVE true
#define space "\t\t"
using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);// color = foreground + 16 * background
/*
	Mohammad Yehya Hayati K21-3309
	Deepak Chawla K21-4931
	Asad Noor Khan K21-4678
*/
void title()//Global Function
{
	SetConsoleTextAttribute(color, 4);
	cout<< space << "           88                                        " << endl  
		<< space << "           88                                        " << endl 
		<< space << "           88                                        " << endl
		<< space << " ,adPPYba, 88,dPPYba,   ,adPPYba, ,adPPYba, ,adPPYba," << endl
		<< space << "a8\"     \"\" 88P\'    \"8a a8P_____88 I8[    \"\" I8[    \"\"" << endl
		<< space << "8b         88       88 8PP\"\"\"\"\"\"\"  `\"Y8ba,   `\"Y8ba,"  << endl
		<< space << "\"8a,   ,aa 88       88 \"8b,   ,aa aa    ]8I aa    ]8I" << endl
 		<< space << " `\"Ybbd8\"\' 88       88  `\"Ybbd8\"\' `\"YbbdP\"\' `\"YbbdP\"\'" << endl;
 	cout << endl << endl;
 	SetConsoleTextAttribute(color, 15);
}
bool CheckStringArray(string s , string *x)//Global Function
{
	for (int i = 0 ; i < 16 ; i++)
	{
		if(s == x[i]) return true;
	}
	return false;
}
class ChessPiece
{
	protected:
		string Name;
		int PositionX;
		int PositionY;
		char color;
		int NumberMovement;
		bool State;
		string Type;
	public:
		ChessPiece(){Name = "     ";}
		ChessPiece(string n , const int x , const int y) : Name(n) , PositionX(x) , PositionY(y) , State(ALIVE){color = n[1];NumberMovement = 0;}
		~ChessPiece(){}
		string getName()
		{
			char c[5];
			int count = 0;
			for (int i = 0 ; Name[i] != '\0' ; i++) {if (Name[i] != ' ') c[count++] = Name[i];}
			return (string)c;
		}
		const int getNumberMovement(){return NumberMovement;}
		const int getPositionX(){return PositionX;}
		const int getPositionY(){return PositionY;}
		const bool getState(){return State;}
		const string getType(){return Type;}
		const char getColor(){return color;}
		ChessPiece& setPositionX(const int x){this->PositionX = x; return *this;}
		ChessPiece& setPositionY(const int y){this->PositionY = y; return *this;}
		void setState(int s){this->State = s;}
		void IncrementNumberofMovement(){NumberMovement++;}
		static ChessPiece EmptyPiece()
		{
			ChessPiece x;
			x.Name = "     ";
			x.PositionX = 0;
			x.PositionY = 0;
			x.color = '\0';
			x.State = DEAD;
			x.Type = "";
			return x;
		}
		bool operator == (ChessPiece x)
		{
			if(this->Name == x.Name && this->PositionX == x.PositionX && this->PositionY == x.PositionY && this->color == x.color && this->State == x.State && this->Type == x.Type)
			return true;
			return false;
		}
		bool operator != (ChessPiece x) {return(!(*this == x));}
		friend class ChessBoard;
		friend ostream& operator << (ostream& display , const ChessPiece &x);
};
ostream& operator << (ostream& display , const ChessPiece &x) {display << x.Name;}
class King : public ChessPiece
{
	public:
		King(){}
		King(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "KING";color = n[0];}
		~King(){}
};
class Pawn : public ChessPiece
{
	public:
		Pawn(){}
		Pawn(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "PAWN";}
		~Pawn(){}
};
class Rook : public ChessPiece
{
	public:
		Rook(){}
		Rook(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "ROOK";}
		~Rook(){}
};
class Knight : public ChessPiece
{
	public:
		Knight(){}
		Knight(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "KNIGHT";}
		~Knight(){}
};
class Bishop : public ChessPiece
{
	public:
		Bishop(){}
		Bishop(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "BISHOP";}
		~Bishop(){}
};
class Queen : public ChessPiece
{
	public:
		Queen(){}
		Queen(string n , const int x , const int y) : ChessPiece(n,x,y){Type = "QUEEN";color = n[2];}
		~Queen(){}
};
class ChessBoard
{
	protected:
		ChessPiece** Grid;
	public:
		ChessPiece *Now;
		ChessPiece Consider;
		ChessBoard(){}
		ChessBoard(Pawn Wp[8] , Pawn Bp[8] , Rook Wr[2] , Rook Br[2] , Bishop Wb[2] , Bishop Bb[2] , Knight Wk[2] , Knight Bk[2] , Queen& Wq , Queen& Bq , King& WKing , King& BKing)
		{
			int i;
			Grid = new ChessPiece*[8];
			for(i = 0 ; i < 8 ; i++) Grid[i] = new ChessPiece[8];
			reset(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
		}
		~ChessBoard(){delete Grid;}
		//Function to Set all the Values of all the pieces to their intial values
		void reset(Pawn Wp[8] , Pawn Bp[8] , Rook Wr[2] , Rook Br[2] , Bishop Wb[2] , Bishop Bb[2] , Knight Wk[2] , Knight Bk[2] , Queen& Wq , Queen& Bq , King& WKing , King& BKing)
		{
			int i , j;
			Grid[0][0] = Wr[0]; Wr[0].setPositionX(0).setPositionY(0);
			Grid[0][1] = Wk[0]; Wk[0].setPositionX(1).setPositionY(0);
			Grid[0][2] = Wb[0]; Wb[0].setPositionX(2).setPositionY(0);
			Grid[0][3] = Wq;	Wq.setPositionX(3).setPositionY(0);
			Grid[0][4] = WKing; WKing.setPositionX(4).setPositionY(0);
			Grid[0][5] = Wb[1]; Wb[1].setPositionX(5).setPositionY(0);
			Grid[0][6] = Wk[1]; Wk[1].setPositionX(6).setPositionY(0);
			Grid[0][7] = Wr[1]; Wr[1].setPositionX(7).setPositionY(0);
			for (i = 0 ; i < 8 ; i++) {Grid[1][i] = Wp[i]; Wp[i].setPositionX(i).setPositionY(1);}
			
			for (i = 2 ; i < 6 ; i++) {for (j = 0 ; j < 8 ; j++) {Grid[i][j] = ChessPiece::EmptyPiece();}}
			
			Grid[7][0] = Br[0]; Br[0].setPositionX(0).setPositionY(7);
			Grid[7][1] = Bk[0]; Bk[0].setPositionX(1).setPositionY(7);
			Grid[7][2] = Bb[0]; Bb[0].setPositionX(2).setPositionY(7);
			Grid[7][3] = Bq; Bq.setPositionX(3).setPositionY(7);
			Grid[7][4] = BKing; BKing.setPositionX(4).setPositionY(7);
			Grid[7][5] = Bb[1]; Bb[1].setPositionX(5).setPositionY(7);
			Grid[7][6] = Bk[1]; Bk[1].setPositionX(6).setPositionY(7);
			Grid[7][7] = Br[1]; Br[1].setPositionX(7).setPositionY(7);
			for (i = 0 ; i < 8 ; i++) {Grid[6][i] = Bp[i]; Bp[i].setPositionX(i).setPositionY(6);}
		}
		//Function to print the Chess Board/Grid
		void PrintGrid()
		{
			int i , j;
			for (i = 7 ; i >= 0 ; i--)
			{
				if(i == 7)
				{
					SetConsoleTextAttribute(color, 111);
					cout << space << "     " << "  A  " << "  B  " << "  C  " << "  D  " << "  E  " << "  F  " << "  G  " << "  H  " << "     " << endl;
					SetConsoleTextAttribute(color, 15);
				}
				cout << space;
				for (j = 0 ; j < 8 ; j++) 
				{
					if(j == 0)
					{
						SetConsoleTextAttribute(color, 111);
						cout << "  " << i + 1 << "  ";
						SetConsoleTextAttribute(color, 15);
					}
					if ((i + j) % 2 == 0) SetConsoleTextAttribute(color, 240);
					else SetConsoleTextAttribute(color, 15);
					cout << Grid[i][j];
					if(j == 7)
					{
						SetConsoleTextAttribute(color, 111);
						cout << "  " << i + 1 << "  ";
						SetConsoleTextAttribute(color, 15);
					}
				}
				cout << endl;
				if(i == 0)
				{
					SetConsoleTextAttribute(color, 111);
					cout << space << "     " << "  A  " << "  B  " << "  C  " << "  D  " << "  E  " << "  F  " << "  G  " << "  H  " << "     " << endl;
					SetConsoleTextAttribute(color, 15);
				}
			}
		}
		//Function to Upadte the values of all the pieces on the Grid
		void UpdateGrid(Pawn Wp[8] , Pawn Bp[8] , Rook Wr[2] , Rook Br[2] , Bishop Wb[2] , Bishop Bb[2] , Knight Wk[2] , Knight Bk[2] , Queen& Wq , Queen& Bq , King& WKing , King& BKing)
		{
			int i , j;
			for (i = 0 ; i < 8 ; i++) {for (j = 0 ; j < 8 ; j++) Grid[i][j] = ChessPiece::EmptyPiece();}
			for (i = 0 ; i < 8 ; i++) if(Wp[i].State == ALIVE) Grid[Wp[i].getPositionY()][Wp[i].getPositionX()] = Wp[i];
			for (i = 0 ; i < 8 ; i++) if(Bp[i].State == ALIVE) Grid[Bp[i].getPositionY()][Bp[i].getPositionX()] = Bp[i];
			for (i = 0 ; i < 2 ; i++) if(Wr[i].State == ALIVE) Grid[Wr[i].getPositionY()][Wr[i].getPositionX()] = Wr[i];
			for (i = 0 ; i < 2 ; i++) if(Br[i].State == ALIVE) Grid[Br[i].getPositionY()][Br[i].getPositionX()] = Br[i];
			for (i = 0 ; i < 2 ; i++) if(Wb[i].State == ALIVE) Grid[Wb[i].getPositionY()][Wb[i].getPositionX()] = Wb[i];
			for (i = 0 ; i < 2 ; i++) if(Bb[i].State == ALIVE) Grid[Bb[i].getPositionY()][Bb[i].getPositionX()] = Bb[i];
			for (i = 0 ; i < 2 ; i++) if(Wk[i].State == ALIVE) Grid[Wk[i].getPositionY()][Wk[i].getPositionX()] = Wk[i];
			for (i = 0 ; i < 2 ; i++) if(Bk[i].State == ALIVE) Grid[Bk[i].getPositionY()][Bk[i].getPositionX()] = Bk[i];
			if(Wq.State == ALIVE) Grid[Wq.getPositionY()][Wq.getPositionX()] = Wq;
			if(Bq.State == ALIVE) Grid[Bq.getPositionY()][Bq.getPositionX()] = Bq;
			Grid[WKing.getPositionY()][WKing.getPositionX()] = WKing;
			Grid[BKing.getPositionY()][BKing.getPositionX()] = BKing;
		}
		//Function to find a specific Piece and point the Now Pointer to it
		void FindPiece(string s) {for (int i = 0 ; i < 8 ; i++){for (int j = 0 ; j < 8 ; j++) {if (Grid[i][j].getName() == s) {Now = &Grid[i][j]; return;}}}}
		//Function to Check if a particular spot on the grid is empty or not
		bool CheckSlot(int x , int y) 
		{
			if (x < 0 || x > 7 || y < 0 || y > 7) return false;
			if (Grid[y][x] == ChessPiece::EmptyPiece()) return true;
			return false;
		}
		//Function to Update the Consider Variable Which is used in Check Logic
		void MakeConsider(ChessPiece x , int d1 , int d2){Consider = x;Consider.setPositionX(d1);Consider.setPositionY(d2);}
		//Function that will return the color of the piece on a specific position
		char ColorCheck(int x , int y){return Grid[y][x].color;}
		//Function to find and set the state of a dead piece to DEAD
		void Kill(int x , int y , Pawn Wp[8] , Pawn Bp[8] , Rook Wr[2] , Rook Br[2] , Bishop Wb[2] , Bishop Bb[2] , Knight Wk[2] , Knight Bk[2] , Queen& Wq , Queen& Bq)                  
		{
			int i;
			if (Grid[y][x].getName()[0] == 'B')
			{
				for (i = 0 ; i < 8 ; i++){if (Bp[i].getName() == Grid[y][x].getName()) {Bp[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Br[i].getName() == Grid[y][x].getName()) {Br[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Bb[i].getName() == Grid[y][x].getName()) {Bb[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Bk[i].getName() == Grid[y][x].getName()) {Bk[i].setState(DEAD);return;}}
				if (Bq.getName() == Grid[y][x].getName()) {Bq.setState(DEAD);return;}
			}
			if (Grid[y][x].getName()[0] == 'W')
			{
				for (i = 0 ; i < 8 ; i++){if (Wp[i].getName() == Grid[y][x].getName()) {Wp[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Wr[i].getName() == Grid[y][x].getName()) {Wr[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Wb[i].getName() == Grid[y][x].getName()) {Wb[i].setState(DEAD);return;}}
				for (i = 0 ; i < 2 ; i++){if (Wk[i].getName() == Grid[y][x].getName()) {Wk[i].setState(DEAD);return;}}
				if (Wq.getName() == Grid[y][x].getName()) {Wq.setState(DEAD);return;}
			}
		}
		//Function to check if there is an obstacle between a Rook and the entered position
		bool RookObstacleCheck(int d1 , int d2 , bool Horizontal)
		{
			if(d1 < 0 || d1 > 8 || d2 < 0 || d2 > 8) return true;
			if(Horizontal == false)
			{
				if(d1 < d2)
				{
					for(int i = d1 + 1 ; i < d2 ; i++)
					{
						if(Grid[i][Now->getPositionX()] == ChessPiece::EmptyPiece()){}
						else return true;
					}
					return false;
				}
				else if(d1 > d2)
				{
					for(int i = d1 - 1 ; i > d2 ; i--)
					{
						if(Grid[i][Now->getPositionX()] == ChessPiece::EmptyPiece()){}
						else return true;
					}
					return false;
				}
			}
			else if (Horizontal == true)
			{
				if (d1 < d2)
				{
					for(int i = d1 + 1; i < d2 ; i++)
					{
						if(Grid[Now->getPositionY()][i] == ChessPiece::EmptyPiece()){}
						else return true;
					}
					return false;
				}
				else if(d1 > d2)
				{
					for(int i = d1 - 1; i > d2 ; i--)
					{
						if(Grid[Now->getPositionY()][i] == ChessPiece::EmptyPiece()){}
						else return true;
					}
					return false;
				}
			}
		}
		//Overloaded Function to check if there is an obstacle between a Rook and the entered position with ignoring a specific piece
		bool RookObstacleCheck(int d1 , int d2 , bool Horizontal , ChessPiece& Ignore)
		{
			if(d1 < 0 || d1 > 7 || d2 < 0 || d2 > 7) return true;
			if(Horizontal == false)
			{
				if(d1 < d2)
				{
					for(int i = d1 + 1 ; i < d2 ; i++)
					{
						if (Consider.getPositionX() == Now->getPositionX() && Consider.getPositionY() == i) return true;
						else if(Grid[i][Now->getPositionX()] == ChessPiece::EmptyPiece() || Grid[i][Now->getPositionX()] == Ignore){}
						else return true;
					}
					return false;
				}
				else if(d1 > d2)
				{
					for(int i = d1 - 1 ; i > d2 ; i--)
					{
						if (Consider.getPositionX() == Now->getPositionX() && Consider.getPositionY() == i) {return true;}
						else if(Grid[i][Now->getPositionX()] == ChessPiece::EmptyPiece() || Grid[i][Now->getPositionX()] == Ignore){}
						else return true;
					}
					return false;
				}
			}
			else if (Horizontal == true)
			{
				if (d1 < d2)
				{
					for(int i = d1 + 1; i < d2 ; i++)
					{
						if (Consider.getPositionY() == Now->getPositionY() && Consider.getPositionX() == i) return true;
						else if(Grid[Now->getPositionY()][i] == ChessPiece::EmptyPiece() || Grid[Now->getPositionY()][i] == Ignore){}
						else return true;
					}
					return false;
				}
				else if(d1 > d2)
				{
					for(int i = d1 - 1; i > d2 ; i--)
					{
						if (Consider.getPositionY() == Now->getPositionY() && Consider.getPositionX() == i) return true;
						else if(Grid[Now->getPositionY()][i] == ChessPiece::EmptyPiece() || Grid[Now->getPositionY()][i] == Ignore){}
						else return true;
					}
					return false;
				}
			}
		}
		//Function to check if the entered position is actually a viable position for the bishop to move to
		bool BishopViableDiagonal(int d1 , int d2)
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				if(Now->getPositionX() + i == d1 && Now->getPositionY() + i == d2) return true;
				if(Now->getPositionX() - i == d1 && Now->getPositionY() + i == d2) return true;
				if(Now->getPositionX() + i == d1 && Now->getPositionY() - i == d2) return true;
				if(Now->getPositionX() - i == d1 && Now->getPositionY() - i == d2) return true;
			}
			return false;
		}
		//Function to check if there is an obstacle between a Bishop and the entered position
		bool BishopObstacleCheck(int d1 , int d2 , bool Up , bool Right)
		{
			int i = 0;
			if(Up == true && Right == true)
			{
				while(1)
				{
					if(Now->getPositionX() + i + 1 >= d1 || Now->getPositionY() + i + 1 >= d2) return false;
					if(Now->getPositionX() + i + 1 > 8 || Now->getPositionY() + i + 1 > 8) return false;
					if(Grid[Now->getPositionY() + i + 1][Now->getPositionX() + i + 1] == ChessPiece::EmptyPiece()){}
					else return true;
					i++;
				}
			}
			if(Up == true && Right == false)
			{
				while(1)
				{
					if(Now->getPositionX() - i - 1 <= d1 || Now->getPositionY() + i + 1 >= d2) return false;
					if(Now->getPositionX() - i - 1 < 0 || Now->getPositionY() + i + 1 > 8) return false;
					if(Grid[Now->getPositionY() + i + 1][Now->getPositionX() - i - 1] == ChessPiece::EmptyPiece()){}
					else return true;
					i++;
				}
			}
			if(Up == false && Right == true)
			{
				while(1)
				{
					if(Now->getPositionX() + i + 1 >= d1 || Now->getPositionY() - i - 1 <= d2) return false;
					if(Now->getPositionX() + i + 1 > 8 || Now->getPositionY() - i - 1 < 0) return false;
					if(Grid[Now->getPositionY() - i - 1][Now->getPositionX() + i + 1] == ChessPiece::EmptyPiece()){}
					else return true;
					i++;
				}
			}
			if(Up == false && Right == false)
			{
				while(1)
				{
					if(Now->getPositionX() - i - 1 <= d1 || Now->getPositionY() - i - 1 <= d2) return false;
					if(Now->getPositionX() - i - 1 < 0 || Now->getPositionY() - i - 1 < 0) return false;
					if(Grid[Now->getPositionY() - i - 1][Now->getPositionX() - i - 1] == ChessPiece::EmptyPiece()){}
					else return true;
					i++;
				}
			}
		}
		//Overloaded Function to check if there is an obstacle between a Bishop and the entered position with ignoring a specific piece
		bool BishopObstacleCheck(int d1 , int d2 , bool Up , bool Right , ChessPiece& Ignore)
		{
			int i = 0;
			if(Up == true && Right == true)
			{
				while(1)
				{
					if(Now->getPositionX() + i + 1 >= d1 || Now->getPositionY() + i + 1 >= d2) return false;
					if(Now->getPositionX() + i + 1 > 8 || Now->getPositionY() + i + 1 > 8) return false;
					if(Consider.getPositionX() == Now->getPositionX() + i + 1 && Consider.getPositionY() == Now->getPositionY() + i + 1) return true;
					else if(Grid[Now->getPositionY() + i + 1][Now->getPositionX() + i + 1] == ChessPiece::EmptyPiece() || Grid[Now->getPositionY() + i + 1][Now->getPositionX() + i + 1] == Ignore){}
					else return true;
					i++;
				}
			}
			if(Up == true && Right == false)
			{
				while(1)
				{
					if(Now->getPositionX() - i - 1 <= d1 || Now->getPositionY() + i + 1 >= d2) return false;
					if(Now->getPositionX() - i - 1 < 0 || Now->getPositionY() + i + 1 > 8) return false;
					if(Consider.getPositionX() == Now->getPositionX() - i - 1 && Consider.getPositionY() == Now->getPositionY() + i + 1) return true;
					if(Grid[Now->getPositionY() + i + 1][Now->getPositionX() - i - 1] == ChessPiece::EmptyPiece() || Grid[Now->getPositionY() + i + 1][Now->getPositionX() - i - 1] == Ignore){}
					else return true;
					i++;
				}
			}
			if(Up == false && Right == true)
			{
				while(1)
				{
					if(Now->getPositionX() + i + 1 >= d1 || Now->getPositionY() - i - 1 <= d2) return false;
					if(Now->getPositionX() + i + 1 > 8 || Now->getPositionY() - i - 1 < 0) return false;
					if(Consider.getPositionX() == Now->getPositionX() + i + 1 && Consider.getPositionY() == Now->getPositionY() - i - 1) return true;
					if(Grid[Now->getPositionY() - i - 1][Now->getPositionX() + i + 1] == ChessPiece::EmptyPiece() || Grid[Now->getPositionY() - i - 1][Now->getPositionX() + i + 1] == Ignore){}
					else return true;
					i++;
				}
			}
			if(Up == false && Right == false)
			{
				while(1)
				{
					if(Now->getPositionX() - i - 1 <= d1 || Now->getPositionY() - i - 1 <= d2) return false;
					if(Now->getPositionX() - i - 1 < 0 || Now->getPositionY() - i - 1 < 0) return false;
					if(Consider.getPositionX() == Now->getPositionX() - i - 1 && Consider.getPositionY() == Now->getPositionY() - i - 1) return true;
					if(Grid[Now->getPositionY() - i - 1][Now->getPositionX() - i - 1] == ChessPiece::EmptyPiece()  || Grid[Now->getPositionY() - i - 1][Now->getPositionX() - i - 1] == Ignore){}
					else return true;
					i++;
				}
			}
		}
		//Function to check if the entered position is actually a viable position for the knight to move to
		bool KnightViableSpot(int d1 , int d2)
		{
			if(Now->getPositionX() + 2 == d1 && Now->getPositionY() + 1 == d2) return true;
			if(Now->getPositionX() + 2 == d1 && Now->getPositionY() - 1 == d2) return true;
			if(Now->getPositionX() - 2 == d1 && Now->getPositionY() + 1 == d2) return true;
			if(Now->getPositionX() - 2 == d1 && Now->getPositionY() - 1 == d2) return true;
			if(Now->getPositionX() + 1 == d1 && Now->getPositionY() + 2 == d2) return true;
			if(Now->getPositionX() - 1 == d1 && Now->getPositionY() + 2 == d2) return true;
			if(Now->getPositionX() + 1 == d1 && Now->getPositionY() - 2 == d2) return true;
			if(Now->getPositionX() - 1 == d1 && Now->getPositionY() - 2 == d2) return true;
			return false;
		}
		//Function for CHECK of a specific King
		bool Check(Pawn p[8] , Rook r[2] , Bishop b[2] , Knight k[2] , Queen& q , King& King , int d1 , int d2)
		{
			int c = p[0].getColor()=='W'?1:p[0].getColor()=='B'?0:(-1);
			for(int i = 0 ; i < 8 ; i++) if(p[i].getState() == ALIVE){if(((p[i].getPositionX() == d1 - 1) && (p[i].getPositionY() == d2 + pow(-1,c))) || ((p[i].getPositionX() == d1 + 1) &&  (p[i].getPositionY() == d2 + pow(-1,c)))) {return true;}}
			for(int i = 0 ; i < 2 ; i++) if(r[i].getState() == ALIVE){Now = &r[i];if((!RookObstacleCheck(r[i].getPositionX() , d1 , true) && Now->getPositionY() == d2) || (!RookObstacleCheck(r[i].getPositionY() , d2 , false) && Now->getPositionX() == d1)) {return true;}}
			for(int i = 0 ; i < 2 ; i++)
			{
				if(b[i].getState() == ALIVE)
				{
					Now = &b[i];
					if(BishopViableDiagonal(d1,d2))
					{
						bool Up , Right;
						if(Now->getPositionX() < d1 && Now->getPositionY() < d2) {Up = true;Right = true;}
						if(Now->getPositionX() < d1 && Now->getPositionY() > d2) {Up = false;Right = true;}
						if(Now->getPositionX() > d1 && Now->getPositionY() < d2) {Up = true;Right = false;}
						if(Now->getPositionX() > d1 && Now->getPositionY() > d2) {Up = false;Right = false;}
						if(!BishopObstacleCheck(d1 , d2 , Up , Right))
						{
							return true;
						}
					}
				}
			}
			for(int i = 0 ; i < 2 ; i++) if(k[i].getState() == ALIVE){Now = &k[i];if(KnightViableSpot(d1 , d2)) {return true;}}
			Now = &q;
			if(q.getState() == ALIVE)
			{
				if((!RookObstacleCheck(q.getPositionX() , d1 , true) && Now->getPositionY() == d2) || (!RookObstacleCheck(q.getPositionY() , d2 , false) && Now->getPositionX() == d1)){return true;}
			}
			if(q.getState() == ALIVE)
			{
			 	if(BishopViableDiagonal(d1,d2))
				{
					bool Up , Right;
					if(Now->getPositionX() < d1 && Now->getPositionY() < d2) {Up = true;Right = true;}
					if(Now->getPositionX() < d1 && Now->getPositionY() > d2) {Up = false;Right = true;}
					if(Now->getPositionX() > d1 && Now->getPositionY() < d2) {Up = true;Right = false;}
					if(Now->getPositionX() > d1 && Now->getPositionY() > d2) {Up = false;Right = false;}
					if(!BishopObstacleCheck(d1 , d2 , Up , Right)){return true;}
				}
			}
			for(int i = -1 ; i <= 1 ; i++){for(int j = -1 ; j <= 1 ; j++){if(d1 + i < 0 || d1 + i > 7 || d2 + j < 0 || d2 + j > 7){}else if(King.getPositionX() == d1 && King.getPositionY() == d2){return true;}}}
			return false;
		}
		//Overloaded function for CHECK of a specific King with ingnoring a specific piece
		bool Check(Pawn p[8] , Rook r[2] , Bishop b[2] , Knight k[2] , Queen& q , King& King , int d1 , int d2 , ChessPiece& Ignore)
		{
			int c = p[0].getColor()=='W'?1:p[0].getColor()=='B'?0:(-1);
			for(int i = 0 ; i < 8 ; i++) if(p[i].getState() == ALIVE){if(((p[i].getPositionX() == d1 - 1) && (p[i].getPositionY() == d2 + pow(-1,c))) || ((p[i].getPositionX() == d1 + 1) &&  (p[i].getPositionY() == d2 + pow(-1,c)))) {return true;}}
			for(int i = 0 ; i < 2 ; i++) if(r[i].getState() == ALIVE){Now = &r[i];if((!RookObstacleCheck(r[i].getPositionX() , d1 , true , Ignore) && Now->getPositionY() == d2) || (!RookObstacleCheck(r[i].getPositionY() , d2 , false , Ignore) && Now->getPositionX() == d1)) {return true;}}
			for(int i = 0 ; i < 2 ; i++)
			{
				if(b[i].getState() == ALIVE)
				{
					Now = &b[i];
					if(BishopViableDiagonal(d1,d2))
					{
						bool Up , Right;
						if(Now->getPositionX() < d1 && Now->getPositionY() < d2) {Up = true;Right = true;}
						if(Now->getPositionX() < d1 && Now->getPositionY() > d2) {Up = false;Right = true;}
						if(Now->getPositionX() > d1 && Now->getPositionY() < d2) {Up = true;Right = false;}
						if(Now->getPositionX() > d1 && Now->getPositionY() > d2) {Up = false;Right = false;}
						if(!BishopObstacleCheck(d1 , d2 , Up , Right , Ignore))
						{
							return true;
						}
					}
				}
			}
			for(int i = 0 ; i < 2 ; i++) if(k[i].getState() == ALIVE){Now = &k[i];if(KnightViableSpot(d1 , d2)) {return true;}}
			Now = &q;
			if(q.getState() == ALIVE)
			{
				if((!RookObstacleCheck(q.getPositionX() , d1 , true , Ignore) && Now->getPositionY() == d2) || (!RookObstacleCheck(q.getPositionY() , d2 , false , Ignore) && Now->getPositionX() == d1)){return true;}
			}
			if(q.getState() == ALIVE)
			{
			 	if(BishopViableDiagonal(d1,d2))
				{
					bool Up , Right;
					if(Now->getPositionX() < d1 && Now->getPositionY() < d2) {Up = true;Right = true;}
					if(Now->getPositionX() < d1 && Now->getPositionY() > d2) {Up = false;Right = true;}
					if(Now->getPositionX() > d1 && Now->getPositionY() < d2) {Up = true;Right = false;}
					if(Now->getPositionX() > d1 && Now->getPositionY() > d2) {Up = false;Right = false;}
					if(!BishopObstacleCheck(d1 , d2 , Up , Right , Ignore)){return true;}
				}
			}
			for(int i = -1 ; i <= 1 ; i++){for(int j = -1 ; j <= 1 ; j++){if(d1 + i < 0 || d1 + i > 7 || d2 + j < 0 || d2 + j > 7){}else if(King.getPositionX() == d1 && King.getPositionY() == d2){return true;}}}
			return false;
		}
		//Function to check if the entered position is actually a viable position for the king to move to
		bool KingViableSpot(int d1 , int d2 , King& Return)
		{
			int flag1 = 0 , flag2 = 0;
			Now = &Return;
			for(int i = -1 ; i <=1 ; i++)
			{
				if(Now->getPositionX() == d1 + i)flag1 = 1;
				if(Now->getPositionY() == d2 + i)flag2 = 1;
			}
			if(flag1 == 1 && flag2 == 1 && (Now->getColor() != ColorCheck(d1,d2)))return true;
			return false;
		}
		//Game End Condition / CheckMate
		bool GameEnd(Pawn p[8] , Rook r[2] , Bishop b[2] , Knight k[2] , Queen& q , King& King , int d1 , int d2)
		{
			int flag = 0;
			if(Check(p , r , b , k , q , King , d1 , d2))
			{
				for(int i = -1 ; i <= 1 ; i++)
				{
					for (int j = -1 ; j <= 1 ; j++)
					{
						if(d1 + i < 0 || d1 + i > 8 || d2 + j < 0 || d2 + j > 8 || (i == 0 && j == 0))continue;
						if(!Check(p , r , b , k , q , King , d1 + i , d2 + j)){return false;}
//						if(ColorCheck(d1 + i , d1 + j) == ColorCheck(d1 , d2))continue;
					}
				}
			}
			else return false;
			return true;
		}
};
int main()
{
	Pawn Wp[8] = {Pawn(" WP1 " , 0 , 0) , Pawn(" WP2 " , 0 , 0) , Pawn(" WP3 " , 0 , 0) , Pawn(" WP4 " , 0 , 0) , Pawn(" WP5 " , 0 , 0) , Pawn(" WP6 " , 0 , 0) , Pawn(" WP7 " , 0 , 0) , Pawn(" WP8 " , 0 , 0) ,};
	Pawn Bp[8] = {Pawn(" BP1 " , 0 , 0) , Pawn(" BP2 " , 0 , 0) , Pawn(" BP3 " , 0 , 0) , Pawn(" BP4 " , 0 , 0) , Pawn(" BP5 " , 0 , 0) , Pawn(" BP6 " , 0 , 0) , Pawn(" BP7 " , 0 , 0) , Pawn(" BP8 " , 0 , 0) ,};
	Rook Wr[2] = {Rook(" WR1 " , 0 , 0) , Rook(" WR2 " , 0 , 0)};
	Rook Br[2] = {Rook(" BR1 " , 0 , 0) , Rook(" BR2 " , 0 , 0)};
	Bishop Wb[2] = {Bishop(" WB1 " , 0 , 0) , Bishop(" WB2 " , 0 , 0)};
	Bishop Bb[2] = {Bishop(" BB1 " , 0 , 0) , Bishop(" BB2 " , 0 , 0)};
	Knight Wk[2] = {Knight(" WK1 " , 0 , 0) , Knight(" WK2 " , 0 , 0)};
	Knight Bk[2] = {Knight(" BK1 " , 0 , 0) , Knight(" BK2 " , 0 , 0)};
	Queen Wq(" WQ  " , 0 , 0);
	Queen Bq(" BQ  " , 0 , 0);
	King WKing("WKING" , 0 , 0);
	King BKing("BKING" , 0 , 0);
	ChessBoard a(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
	int count = 0;
	int flag;
	string s, s1;
	string wx[16] = {"WP1" , "WP2" , "WP3" , "WP4" , "WP5" , "WP6" , "WP7" , "WP8" , "WR1" , "WR2" , "WB1" , "WB2" , "WK1" , "WK2" , "WQ" , "WKING"};
	string bx[16] = {"BP1" , "BP2" , "BP3" , "BP4" , "BP5" , "BP6" , "BP7" , "BP8" , "BR1" , "BR2" , "BB1" , "BB2" , "BK1" , "BK2" , "BQ" , "BKING"};
	do
	{
		if((a.GameEnd(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY())) || (a.GameEnd(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY()))){break;}
		if (count%2)
		{
			flag = 0;
			do
			{
				system("CLS");
				title();
				a.PrintGrid();
				cout << "Black's Turn!" << endl;
				do
				{
					cout << "Enter the name of Piece to Move: "; cin >> s;
					if (!CheckStringArray(s,bx)) {cout << "Wrong Piece! You can only move Black Pieces!" << endl; getch();}
				}
				while(!CheckStringArray(s,bx));
				a.FindPiece(s);
				if(a.Now->getType() == "PAWN")
				{
					a.Now = &Bp[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Initial 2 Space Forward Movement
					if(flag == 0)
					{
						if (a.Now->getNumberMovement() == 0 && (a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()-1) && a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()-2)) && (s1[1] - 48 == a.Now->getPositionY() - 2 + 1) && (s1[0] - 65 == a.Now->getPositionX()))
						{
							a.MakeConsider(Bp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
							if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Bp[((int)s[2]) - 49]))
							{
								cout << "Can not Perform Action! King in Check!" << endl;getch();
								a.Now = &Bp[((int)s[2]) - 49];
								continue;
							}
							else
							{
								a.Now = &Bp[((int)s[2]) - 49];
								a.Now->setPositionY(a.Now->getPositionY() - 2);
								a.Now->IncrementNumberofMovement();
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								flag = 1;
							}
						}
					}
					//Normal 1 Space Forward Movement
					if(flag == 0)
					{
						if (a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()-1) && (s1[1] - 48 == a.Now->getPositionY() - 1 + 1) && (s1[0] - 65 == a.Now->getPositionX()))
						{
							a.MakeConsider(Bp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
							if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Bp[((int)s[2]) - 49]))
							{
								cout << "Can not Perform Action! King in Check!" << endl;getch();
								a.Now = &Bp[((int)s[2]) - 49];
								continue;
							}
							else
							{
								a.Now = &Bp[((int)s[2]) - 49];
								a.Now->setPositionY(a.Now->getPositionY() - 1);
								a.Now->IncrementNumberofMovement();
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								flag = 1;
							}
						}
					}
					//Kill Forward Left
					if(flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX() - 1 && s1[1] - 48 == a.Now->getPositionY() - 1 + 1)
						{
							if (!a.CheckSlot(a.Now->getPositionX()-1 , a.Now->getPositionY()-1) && a.ColorCheck(a.Now->getPositionX()-1 , a.Now->getPositionY()-1) == 'W')
							{
								a.MakeConsider(Bp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Bp[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Bp[((int)s[2]) - 49];
									continue;
								}
								else
								{
									a.Now = &Bp[((int)s[2]) - 49];
									a.Kill(a.Now->getPositionX()-1 , a.Now->getPositionY()-1 , Bp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(a.Now->getPositionX()-1).setPositionY(a.Now->getPositionY()-1);
									a.Now->IncrementNumberofMovement();
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									flag = 1;
								}
							}
						}
					}
					//Kill Forward Right
					if(flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX() + 1 && s1[1] - 48 == a.Now->getPositionY() - 1 + 1)
						{
							if (!a.CheckSlot(a.Now->getPositionX()+1 , a.Now->getPositionY()-1) && a.ColorCheck(a.Now->getPositionX()+1 , a.Now->getPositionY()-1) == 'W')
							{
								a.MakeConsider(Bp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Bp[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Bp[((int)s[2]) - 49];
									continue;
								}
								else
								{
									a.Now = &Bp[((int)s[2]) - 49];
									a.Kill(a.Now->getPositionX()+1 , a.Now->getPositionY()+1 , Bp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(a.Now->getPositionX()+1).setPositionY(a.Now->getPositionY()-1);
									a.Now->IncrementNumberofMovement();
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									flag = 1;
								}
							}
						}
					}
					//Puts down Piece
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Incorrect Move Entered
					if (flag == 0) {cout << "Invalid Move!" << endl << endl;getch();}
				}
				if (a.Now->getType() == "ROOK")
				{
					a.Now = &Br[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Vertical Movements
					if (flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionY() , s1[1] - 48 - 1 , false))
							{
								a.MakeConsider(Br[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Br[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Br[((int)s[2]) - 49];
									continue;
								}
								a.Now = &Br[((int)s[2]) - 49];
								if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'W') 
								{
									a.Kill(a.Now->getPositionX() , s1[1] - 48 - 1 , Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Horizontal Movements
					if (flag == 0)
					{
						if(s1[1] - 48 - 1 == a.Now->getPositionY())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionX() , s1[0] - 65 , true))
							{
								a.MakeConsider(Br[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , BKing.getPositionX() , BKing.getPositionY() , Br[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Br[((int)s[2]) - 49];
									continue;
								}
								a.Now = &Br[((int)s[2]) - 49];
								if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'W') 
								{
									a.Kill(s1[0] - 65 , a.Now->getPositionY() , Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Br , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Put piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "BISHOP")
				{
					a.Now = &Bb[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//All diagnonal Movements
					if (flag == 0)
					{
						if(a.BishopViableDiagonal(s1[0] - 65 , s1[1] - 48 - 1))
						{
							bool Up , Right;
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = true;}
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = true;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = false;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = false;}
							if(!a.BishopObstacleCheck(s1[0] - 65 , s1[1] - 48 - 1 , Up , Right))
							{
								if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
								{
									a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else
								{
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "KNIGHT")
				{
					a.Now = &Bk[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Movement in all 'L' Directions
					if (flag == 0)
					{
						if(a.KnightViableSpot(s1[0] - 65 , s1[1] - 48 - 1))
						{
							if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
							{
								a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
								a.Now->setPositionX(s1[0] - 65);
								a.Now->setPositionY(s1[1] - 48 - 1);
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								a.Now->IncrementNumberofMovement();
								flag = 1;
							}
							else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
							{
								cout << "Invalid Move!" << endl;
								getch();
								continue;
							}
							else
							{
								a.Now->setPositionX(s1[0] - 65);
								a.Now->setPositionY(s1[1] - 48 - 1);
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								a.Now->IncrementNumberofMovement();
								flag = 1;
							}
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "QUEEN")
				{
					a.Now = &Bq;
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//All horizontal Movements
					if (flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionY() , s1[1] - 48 - 1 , false))
							{
								if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'W') 
								{
									a.Kill(a.Now->getPositionX() , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//All vertical movements
					if (flag == 0)
					{
						if(s1[1] - 48 - 1 == a.Now->getPositionY())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionX() , s1[0] - 65 , true))
							{
								if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'W') 
								{
									a.Kill(a.Now->getPositionY() , s1[0] - 65 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//ALl diagonal Movements
					if (flag == 0)
					{
						if(a.BishopViableDiagonal(s1[0] - 65 , s1[1] - 48 - 1))
						{
							bool Up , Right;
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = true;}
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = true;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = false;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = false;}
							if(!a.BishopObstacleCheck(s1[0] - 65 , s1[1] - 48 - 1 , Up , Right))
							{
								if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
								{
									a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else
								{
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "KING")
				{
					a.Now = &BKing;
					cout << "Enter which position to move: "; cin >> s1;
					//Movement of 1 space in all directions
					if(flag == 0)
					{
						if(a.Check(Wp , Wr , Wb , Wk , Wq , WKing , s1[0] - 65 , s1[1] - 48 - 1))
						{
							cout << "Can not Perform Action! King in Check!" << endl;getch();
							a.Now = &BKing;
							continue;
						}
						else if (a.KingViableSpot(s1[0] - 65 , s1[1] - 48 - 1 , BKing))
						{
							a.Now = &BKing;
							a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
							a.Now->setPositionX(s1[0] - 65);
							a.Now->setPositionY(s1[1] - 48 - 1);
							a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
							a.Now->IncrementNumberofMovement();
							flag = 1;
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if (flag == 0) {cout << "Invalid Move!" << endl << endl;getch();}
				}
			}
			while (flag == 0);
		}
		else
		{
			flag = 0;
			do
			{
				system("CLS");
				title();
				a.PrintGrid();
				cout << "White's Turn!" << endl;
				do
				{
					cout << "Enter the name of Piece to Move: "; cin >> s;
					if (!CheckStringArray(s,wx)) {cout << "Wrong Piece! You can only move White Pieces!" << endl; getch();}
				}
				while(!CheckStringArray(s,wx));
				a.FindPiece(s);
				if(a.Now->getType() == "PAWN")
				{
					a.Now = &Wp[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Initial 2 Space Forward Movement
					if(flag == 0)
					{
						if (a.Now->getNumberMovement() == 0 && (a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()+1) && a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()+2)) && (s1[1] - 48 == a.Now->getPositionY() + 2 + 1) && (s1[0] - 65 == a.Now->getPositionX()))
						{
							a.MakeConsider(Wp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
							if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wp[((int)s[2]) - 49]))
							{
								cout << "Can not Perform Action! King in Check!" << endl;getch();
								a.Now = &Wp[((int)s[2]) - 49];
								continue;
							}
							else
							{
								a.Now = &Wp[((int)s[2]) - 49];
								a.Now->setPositionY(a.Now->getPositionY() + 2);
								a.Now->IncrementNumberofMovement();
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								flag = 1;
							}
						}
					}
					//Normal 1 Space Forward Movement
					if(flag == 0)
					{
						if (a.CheckSlot(a.Now->getPositionX() , a.Now->getPositionY()+1) && (s1[1] - 48 == a.Now->getPositionY() + 1 + 1) && (s1[0] - 65 == a.Now->getPositionX()))
						{
							a.MakeConsider(Wp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
							if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wp[((int)s[2]) - 49]))
							{
								cout << "Can not Perform Action! King in Check!" << endl;getch();
								a.Now = &Wp[((int)s[2]) - 49];
								continue;
							}
							else
							{
								a.Now = &Wp[((int)s[2]) - 49];
								a.Now->setPositionY(a.Now->getPositionY() + 1);
								a.Now->IncrementNumberofMovement();
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								flag = 1;
							}
						}
					}
					//Kill Forward Left
					if(flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX() - 1 && s1[1] - 48 == a.Now->getPositionY() + 1 + 1)
						{
							if (!a.CheckSlot(a.Now->getPositionX()-1 , a.Now->getPositionY()+1) && a.ColorCheck(a.Now->getPositionX()-1 , a.Now->getPositionY()+1) == 'B')
							{
								a.MakeConsider(Wp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wp[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wp[((int)s[2]) - 49];
									continue;
								}
								else
								{
									a.Now = &Wp[((int)s[2]) - 49];
									a.Kill(a.Now->getPositionX()-1 , a.Now->getPositionY()+1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(a.Now->getPositionX()-1).setPositionY(a.Now->getPositionY()+1);
									a.Now->IncrementNumberofMovement();
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									flag = 1;
								}
							}
						}
					}
					//Kill Forward Right
					if(flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX() + 1 && s1[1] - 48 == a.Now->getPositionY() + 1 + 1)
						{
							if (!a.CheckSlot(a.Now->getPositionX()+1 , a.Now->getPositionY()+1) && a.ColorCheck(a.Now->getPositionX()+1 , a.Now->getPositionY()+1) == 'B')
							{
								a.MakeConsider(Wp[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wp[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wp[((int)s[2]) - 49];
									continue;
								}
								else
								{
									a.Now = &Wp[((int)s[2]) - 49];
									a.Kill(a.Now->getPositionX()+1 , a.Now->getPositionY()+1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(a.Now->getPositionX()+1).setPositionY(a.Now->getPositionY()+1);
									a.Now->IncrementNumberofMovement();
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									flag = 1;
								}
							}
						}
					}
					//Puts down Piece
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Incorrect Move Entered
					if (flag == 0) {cout << "Invalid Move!" << endl << endl;getch();}
				}
				if (a.Now->getType() == "ROOK")
				{
					a.Now = &Wr[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Vertical Movements
					if (flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionY() , s1[1] - 48 - 1 , false))
							{
								a.MakeConsider(Wr[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wr[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wr[((int)s[2]) - 49];
									continue;
								}
								a.Now = &Wr[((int)s[2]) - 49];
								if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'B') 
								{
									a.Kill(a.Now->getPositionX() , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Horizontal Movements
					if (flag == 0)
					{
						if(s1[1] - 48 - 1 == a.Now->getPositionY())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionX() , s1[0] - 65 , true))
							{
								a.MakeConsider(Wr[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wr[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wr[((int)s[2]) - 49];
									continue;
								}
								a.Now = &Wr[((int)s[2]) - 49];
								if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'B') 
								{
									a.Kill(s1[0] - 65 , a.Now->getPositionY() , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "BISHOP")
				{
					a.Now = &Wb[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//All diagonal movements
					if (flag == 0)
					{
						bool Up , Right;
						if(a.BishopViableDiagonal(s1[0] - 65 , s1[1] - 48 - 1))
						{
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = true;}
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = true;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = false;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = false;}
							if(!a.BishopObstacleCheck(s1[0] - 65 , s1[1] - 48 - 1 , Up , Right))
							{
								a.MakeConsider(Wb[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wb[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wb[((int)s[2]) - 49];
									continue;
								}
								a.Now = &Wb[((int)s[2]) - 49];
								if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
								{
									a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else
								{
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "KNIGHT")
				{
					a.Now = &Wk[((int)s[2]) - 49];
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Movement in all 'L' directions
					if (flag == 0)
					{
						if(a.KnightViableSpot(s1[0] - 65 , s1[1] - 48 - 1))
						{
							a.MakeConsider(Wk[((int)s[2]) - 49] , s1[0] - 65 , s1[1] - 48 - 1);
							if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wk[((int)s[2]) - 49]))
							{
								cout << "Can not Perform Action! King in Check!" << endl;getch();
								a.Now = &Wk[((int)s[2]) - 49];
								continue;
							}
							a.Now = &Wk[((int)s[2]) - 49];
							if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
							{
								a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
								a.Now->setPositionX(s1[0] - 65);
								a.Now->setPositionY(s1[1] - 48 - 1);
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								a.Now->IncrementNumberofMovement();
								flag = 1;
							}
							else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
							{
								cout << "Invalid Move!" << endl;
								getch();
								continue;
							}
							else
							{
								a.Now->setPositionX(s1[0] - 65);
								a.Now->setPositionY(s1[1] - 48 - 1);
								a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
								a.Now->IncrementNumberofMovement();
								flag = 1;
							}
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "QUEEN")
				{
					a.Now = &Wq;
					if (a.Now->getState() == DEAD)
					{
						cout << "Piece is Dead!" << endl;
						getch();
						continue;
					}
					cout << "Enter which position to move: "; cin >> s1;
					//Puts Piece Back
					if (flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Movement in Horizantal directions
					if (flag == 0)
					{
						if(s1[0] - 65 == a.Now->getPositionX())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionY() , s1[1] - 48 - 1 , false))
							{
								a.MakeConsider(Wq , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wb[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wq;
									continue;
								}
								a.Now = &Wq;
								if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'B') 
								{
									a.Kill(a.Now->getPositionX() , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(a.Now->getPositionX() , s1[1] - 48 - 1) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Movement in all Vertical Directions
					if (flag == 0)
					{
						if(s1[1] - 48 - 1 == a.Now->getPositionY())
						{
							if(!a.RookObstacleCheck(a.Now->getPositionX() , s1[0] - 65 , true))
							{
								a.MakeConsider(Wq , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wb[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wq;
									continue;
								}
								a.Now = &Wq;
								if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'B') 
								{
									a.Kill(a.Now->getPositionY() , s1[0] - 65 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , a.Now->getPositionY()) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else 
								{
									a.Now->setPositionX(s1[0] - 65);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Movement in all diagnonal directions
					if (flag == 0)
					{
						if(a.BishopViableDiagonal(s1[0] - 65 , s1[1] - 48 - 1))
						{
							bool Up , Right;
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = true;}
							if(a.Now->getPositionX() < s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = true;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() < s1[1] - 48 - 1) {Up = true;Right = false;}
							if(a.Now->getPositionX() > s1[0] - 65 && a.Now->getPositionY() > s1[1] - 48 - 1) {Up = false;Right = false;}
							if(!a.BishopObstacleCheck(s1[0] - 65 , s1[1] - 48 - 1 , Up , Right))
							{
								a.MakeConsider(Wq , s1[0] - 65 , s1[1] - 48 - 1);
								if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , WKing.getPositionX() , WKing.getPositionY() , Wb[((int)s[2]) - 49]))
								{
									cout << "Can not Perform Action! King in Check!" << endl;getch();
									a.Now = &Wq;
									continue;
								}
								a.Now = &Wq;
								if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'B')
								{
									a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
								else if(a.ColorCheck(s1[0] - 65 , s1[1] - 48 - 1) == 'W')
								{
									cout << "Invalid Move!" << endl;
									getch();
									continue;
								}
								else
								{
									a.Now->setPositionX(s1[0] - 65);
									a.Now->setPositionY(s1[1] - 48 - 1);
									a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
									a.Now->IncrementNumberofMovement();
									flag = 1;
								}
							}
						}
					}
					//Invalid Move Entered
					if(flag == 0) {cout << "Invalid Move!" << endl; getch();}
				}
				if(a.Now->getType() == "KING")
				{
					a.Now = &WKing;
					cout << "Enter which position to move: "; cin >> s1;
					//Movement of 1 space in all directions
					if(flag == 0)
					{
						if(a.Check(Bp , Br , Bb , Bk , Bq , BKing , s1[0] - 65 , s1[1] - 48 - 1))
						{
							cout << "Can not Perform Action! King in Check!" << endl;getch();
							a.Now = &WKing;
							continue;
						}
						else if (a.KingViableSpot(s1[0] - 65 , s1[1] - 48 - 1 , WKing))
						{
							a.Now = &WKing;
							a.Kill(s1[0] - 65 , s1[1] - 48 - 1 , Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq);
							a.Now->setPositionX(s1[0] - 65);
							a.Now->setPositionY(s1[1] - 48 - 1);
							a.UpdateGrid(Wp , Bp , Wr , Br , Wb , Bb , Wk , Bk , Wq , Bq , WKing , BKing);
							a.Now->IncrementNumberofMovement();
							flag = 1;
						}
					}
					//Puts piece back down
					if(flag == 0)
					{
						if (s1[0] - 65 == a.Now->getPositionX() && s1[1] - 48 == a.Now->getPositionY() + 1)
						{
							cout << "Puts " << s << " down." << endl;
							getch();
							continue;
						}
					}
					//Invalid Move Entered
					if (flag == 0) {cout << "Invalid Move!" << endl << endl;getch();}
				}
			}
			while (flag == 0);
		}
		count++;
		fstream f("MatchStatistics.txt" , ios::out);
		if(!f)cout << "Error File <MatchStatistics.txt> Not Found!" << endl;
		else
		{
			for(int i = 0 ; i < 8 ; i++)f<<Wp[i].getName()<<" movement#: "<<Wp[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 8 ; i++)f<<Bp[i].getName()<<" movement#: "<<Bp[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Wr[i].getName()<<" movement#: "<<Wr[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Br[i].getName()<<" movement#: "<<Br[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Wb[i].getName()<<" movement#: "<<Wb[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Bb[i].getName()<<" movement#: "<<Bb[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Wk[i].getName()<<" movement#: "<<Wk[i].getNumberMovement()<<endl;
			for(int i = 0 ; i < 2 ; i++)f<<Bk[i].getName()<<" movement#: "<<Bk[i].getNumberMovement()<<endl;
			f<<Wq.getName()<<" movement#: "<<Wq.getNumberMovement()<<endl;
			f<<Bq.getName()<<" movement#: "<<Bq.getNumberMovement()<<endl;
			f<<WKing.getName()<<" movement#: "<<WKing.getNumberMovement()<<endl;
			f<<BKing.getName()<<" movement#: "<<BKing.getNumberMovement()<<endl;
		}
		f.close();
	}
	while(1);
	cout << "Game has Ended!" << endl << ((count - 1)%2 == 0?"White Wins!":"Black Wins!");
}
