#include <iostream>
#include <cmath>
using namespace std;

class ChessPiece {
protected:
    string Name;
    string Color;
    int x_pos;
    int y_pos;

public:
    ChessPiece() {}
    ChessPiece(string c, string n, int x, int y) : Color(c), Name(n), x_pos(x), y_pos(y) {}

    string getColor() { return Color; }
    string getName() { return Name; }
    int getX_pos() { return x_pos; }
    int getY_pos() { return y_pos; }

    void whereispiece() {
        cout << Name << "(" << x_pos << "," << y_pos << ")" << endl;
    }

    virtual int Turn(int new_x, int new_y) = 0;
    friend ostream& operator<<(ostream& out, ChessPiece& piece) {
        out << "Имя фигруы: " << piece.Name << " цвет: " << piece.Color << " находится на клетке:" << "(" << piece.x_pos << "," << piece.y_pos << ")" << endl;
        return out;
    }
};

class Bishop : public virtual ChessPiece {
public:
    static const string BishopName;

    Bishop() {}
    Bishop(string c, int x, int y) : ChessPiece(c, BishopName, x, y) {
        Color = c;
        x_pos = x;
        y_pos = y;
    }

    virtual int Turn(int new_x, int new_y) {
        if (((new_x != x_pos) && (new_y != y_pos)) && ((abs(new_x - x_pos) == abs(new_y - y_pos)))) {
            x_pos = new_x;
            y_pos = new_y;
            return 1;
        }
        else {
            return 0;
        }
    }
};
const string Bishop::BishopName = "Слон";

class Rook : public virtual ChessPiece {
public:
    static const string RookName;

    Rook() {}
    Rook(string c, int x, int y) : ChessPiece(c, RookName, x, y) {
        Color = c;
        x_pos = x;
        y_pos = y;
    }

    virtual int Turn(int new_x, int new_y) {
        if ((x_pos == new_x && y_pos != new_y) || (x_pos != new_x && y_pos == new_y)) {
            x_pos = new_x;
            y_pos = new_y;
            return 1;
        }
        else {
            return 0;
        }
    }
};
const string Rook::RookName = "Ладья";

class Queen : public Bishop, public Rook {
public:
    static const string QueenName;

    Queen(string c, int x, int y) : ChessPiece(c, QueenName, x, y) {
        Color = c;
        x_pos = x;
        y_pos = y;
    }

    virtual int Turn(int new_x, int new_y) {
        if (Bishop::Turn(new_x, new_y) == 1) {
            return 1;
        }
        else if (Rook::Turn(new_x, new_y) == 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
};
const string Queen::QueenName = "Королева";

struct node {
    ChessPiece* inf;
    node* next;
    node* prev;
};

class List {
private:
    node* head;
    node* tail;

public:
    List() : head(NULL), tail(NULL) {}
    void push(ChessPiece* piece);
    void print();
    void allturn(int i, int j);
};

void List::push(ChessPiece* piece) {
    node* newNode = new node;
    newNode->inf = piece;
    newNode->next = NULL;
    if (!head && !tail) {
        newNode->prev = NULL;
        head = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
}
void List::allturn(int i, int j) {
    node* r = head;
    while (r != NULL) {
        r->inf->Turn(i, j);
        r = r->next;
    }
    cout << '\n';
}
void List::print() {
    node* r = head;
    while (r != NULL) {
        cout << *(r->inf);
        r = r->next;
    }
    cout << '\n';
}


int main() {
    setlocale(LC_ALL, "Russian");
    List Chesslist;
    Bishop b1("Белый", 8, 1);
    Rook r1("Черный", 3, 2);
    Queen q1("Белый", 6, 6);
    ChessPiece* lst[3]; //массив указателей 
    lst[0] = &b1;
    lst[1] = &r1;
    lst[2] = &q1;
    for (int i = 0; i < 3; i++) { //запись в список
        Chesslist.push(lst[i]);
    }
    Chesslist.print();
    Chesslist.allturn(6, 2);
    Chesslist.print(); //вывод списка
}
