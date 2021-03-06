#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXMATRIXSIZE 8
#define MAXSTACKSIZE 100
struct MazePosition {
    short int Row;
    short int Col;
    short int Dir;
};
typedef struct MazePosition ElementType;
typedef struct SNode * PtrToSNode;
struct SNode{
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;
struct Offsets {
    short int Vert;
    short int Horiz;
};

Stack CreateStack(){
    Stack S;
    S=malloc(sizeof(struct SNode));
    S->Next=NULL;
    return S;

}
bool IsEmpty(Stack S){
    return(S->Next==NULL);
}
bool Push(Stack S,ElementType X){
    PtrToSNode TmpCell;
    TmpCell=(PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data=X;
    TmpCell->Next=S->Next;
    S->Next=TmpCell;
    return true;

}
ElementType Pop(Stack S){
    PtrToSNode FirstCell;
    ElementType TomElem;

    if(IsEmpty(S)){
        printf("ept");
         
    }
    else{
        FirstCell=S->Next;
        TomElem=FirstCell->Data;
        S->Next=FirstCell->Next;
        free(FirstCell);
        return TomElem;

    }
}
void Path(int Maze[][MAXMATRIXSIZE], int EXITROW, int EXITCOL) {
    struct Offsets Move[8] = {{1, 1},{-1, -1},{-1, 0},{1, 0},{0, 1},{0, -1},{-1, 1},{1, -1}};
    int Mark[MAXMATRIXSIZE][MAXMATRIXSIZE]={0};
    Stack S;
    struct MazePosition P;
    short int Row, Col, NextRow, NextCol, Dir;
    bool Found = false;
    S = CreateStack(MAXSTACKSIZE);
    Mark[EXITROW][EXITCOL] = 1;
    P.Row = EXITROW;
    P.Col = EXITCOL;
    P.Dir = 0;
    Push(S, P);
    while (!IsEmpty(S) && !Found) {
        P = Pop(S);
        Row = P.Row;
        Col = P.Col;
        Dir = P.Dir;
        while (Dir < 8 && !Found) {
            NextRow = Row + Move[Dir].Vert;
            NextCol = Col + Move[Dir].Horiz;
            if (NextRow == 1 && NextCol == 1)
                Found = true;
            else if (!Maze[NextRow][NextCol] && !Mark[NextRow][NextCol]) {
                Mark[NextRow][NextCol] = 1;
                P.Row = Row;
                P.Col = Col;
                P.Dir = Dir + 1;
                Push(S, P);
                Row = NextRow;
                Col = NextCol;
                Dir = 0;
            } else ++Dir;
        }
        if (Found) {
            printf("%d %d\n", 1, 1);
            printf("%d %d\n", Row, Col);
            while (!IsEmpty(S)) {
                P = Pop(S);
                printf("%d %d\n", P.Row, P.Col);
            }
        } else
            printf("none\n");
    }


}

int main() {
    int a[8][8]={
       //0,1,2,3,4,5,6,7
        {1,1,1,1,1,1,1,1},//0
        {1,0,1,1,1,1,1,1},//1
        {1,1,0,1,0,0,1,1},//2
        {1,1,0,1,0,1,1,1},//3
        {1,1,0,1,1,0,1,1},//4
        {1,1,1,0,1,1,1,1},//5
        {1,1,0,1,0,0,0,1},//6
        {1,1,1,1,1,1,1,1} //7
    };
    Path(a,6,6);
    // printf("%d",a[6][6]);
    return 0;
}
