#include <cstdio>
#include <cassert>
#include <utility>

template<typename T> // T is later put as sudoku (which is a struct) in the solve function ahead
struct stack{
    T elements[2048];
    int top;
    stack(){
        top = 0; // stores one index ahead of topmost element
    }
};

template<typename T>
bool is_empty(stack<T> &s){
    return (s.top==0);
}

template<typename T>
T pop(stack<T> &s){
    --(s.top);
    return s.elements[s.top];
}

template<typename T>
void push(stack<T> &s, T e){
    s.elements[s.top++] = e;
}

template<typename T>
T top(stack<T> &s){
    return s.elements[s.top-1];
}

typedef struct{
    int board[9][9];
} sudoku;

void print_board(sudoku& s){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(s.board[i][j]) printf("%d ",s.board[i][j]);
            else printf(". ");
        }
        printf("\n");
    }
}

void read_board(sudoku& s){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            int v=0;
            scanf("%d",&v);
            s.board[i][j] = v;
        }
    }
}

bool is_valid(sudoku& s){
    for(int i=0;i<9;i++){
        int seen[10] = {0,0,0,0,0,0,0,0,0,0};
        for(int j=0;j<9;j++){
            int v = s.board[i][j];
            if(v && seen[v]){
                return false;
            }
            seen[v] = 1;
        }
    }
    for(int i=0;i<9;i++){
        int seen[10] = {0,0,0,0,0,0,0,0,0,0};
        for(int j=0;j<9;j++){
            int v = s.board[j][i];
            if(v && seen[v]){
                return false;
            }
            seen[v] = 1;
        }
    }
    int boxrow=0;
    int boxcol=0;
    while(boxrow<9){
        while(boxcol<9){
            int seen[10] = {0,0,0,0,0,0,0,0,0,0};
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    int v = s.board[boxrow+i][boxcol+j];;
                    if(v && seen[v]){
                        return false;
                    }
                    seen[v] = 1;
                }
            }
            boxcol+=3;
        }
        boxrow+=3;
        boxcol=0;
    }
    return true;
}

bool is_full(sudoku &s){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(s.board[i][j]==0){
                return false;
            }
        }
    }
    return true;
}

std::pair<int,int> first_empty_space(sudoku &s){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(s.board[i][j]==0){
                return {i,j};
            }
        }
    }
}

void solve(sudoku& s){
    int valid_board=0; //only for assert statement
    stack<sudoku> st;
    // assert(is_valid(s));
    push(st,s);
    while(!is_empty(st)){
        sudoku u = pop(st);
        // print_board(u);
        if(is_full(u)){
            // printf("yes");
            print_board(u);
            return;
        }
        else{
            auto pos = first_empty_space(u);
            assert(u.board[pos.first][pos.second]==0);
            // printf("%d %d\n",pos.first,pos.second);
            for(int i=1;i<=9;i++){
                u.board[pos.first][pos.second] = i;
                // print_board(u);
                if(is_valid(u)){
                    // print_board(u);
                    push(st,u);
                }
            }
        }
    }
    assert(valid_board==1);
}

int main(){
    sudoku s;
    printf("Enter board:\n");
    printf("For empty spaces, enter 0:\n");
    read_board(s);
    printf("\nYour sudoku board:\n");
    print_board(s);
    printf("\nSolution:\n");
    solve(s);
    return 0;
}

// Sample board

// 5 3 0 0 7 0 0 0 0
// 6 0 0 1 9 5 0 0 0
// 0 9 8 0 0 0 0 6 0
// 8 0 0 0 6 0 0 0 3
// 4 0 0 8 0 3 0 0 1
// 7 0 0 0 2 0 0 0 6
// 0 6 0 0 0 0 2 8 0
// 0 0 0 4 1 9 0 0 5
// 0 0 0 0 8 0 0 7 9

// Solution:
// 5 3 4 6 7 8 9 1 2 
// 6 7 2 1 9 5 3 4 8
// 1 9 8 3 4 2 5 6 7
// 8 5 9 7 6 1 4 2 3
// 4 2 6 8 5 3 7 9 1
// 7 1 3 9 2 4 8 5 6
// 9 6 1 5 3 7 2 8 4
// 2 8 7 4 1 9 6 3 5
// 3 4 5 2 8 6 1 7 9