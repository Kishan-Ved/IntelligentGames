#include<stdio.h>
// L = 0 , U = 1, R =2, D = 3
char MoveNames[4][2] = {"L","U","R","D"};
int revMoves[4] = {2,3,0,1};
long long int N_maxn1 = 15116544;
int L[6] = {1,3,2,4,0,5};
int U[6] = {2,1,3,5,4,0};
int R[6] = {4,0,2,1,3,5};
int D[6] = {5,1,0,2,4,3};
int* MOVES[] = {L,U,R,D};
int Loff[2] = {0,-1};
int Uoff[2] = {-1,0};
int Roff[2] = {0,1};
int Doff[2] = {1,0};
int* OFFSETS[] = {Loff,Uoff,Roff,Doff};
int X = -1;
int row1[3] = {0,0,0};
int row2[3] = {0,-1,0};
int row3[3] = {0,0,0};
int* M[3] = {row1,row2,row3};
int loc0 = 3*1+1;
int loc = 3*1+1;
long long Nque[15116544];
int Lque[15116544];
long long int Sque[15116544];
long long int pred_que[15116544];
// int SSque[15116544][36];
long long int lenque[15116544];
int visited[15116544]; 
void Disp(int** M){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int x = M[i][j];
            if(x==-1){
                printf("   ");
            } else {
                printf(" %d ",x);
            }
        }
        printf("\n");
    }
}
int apply(int move,int** M,int loc){
    int i = loc/3;
    int j = loc%3;
    int I = OFFSETS[move][0];
    int J = OFFSETS[move][1];
    I += i;
    J += j;
    int locN = 3*I+J;
    if((I>=0)&&(I<3)&&(J>=0)&&(J<3)){
        M[i][j] = MOVES[move][M[I][J]];
        M[I][J] = -1;
        return locN;
    }
    return loc;
}
int reachedend = 0;
long long int encode(int** M,int loc){
    long long int NN = 0;
    int I = loc/3;
    int J = loc%3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if((i!=I)||(j!=J)){
                NN = 6*NN + M[i][j];
            }
        }
    }
    NN = 9*NN + loc;
    return NN;
}
int decode(long long int N,int** M){
    int lloc = N%9;
    int I = lloc/3;
    int J = lloc%3;
    N = N/9;
    for(int i=2;i>=0;i--){
        for(int j=2;j>=0;j--){
            if((i!=I)||(j!=J)){
                M[i][j] = N%6;
                N = N/6;
            }
        }
    }
    M[I][J] = -1;
    return lloc;
}
int cur = 0;
int Last = 0;
int Update(int findSol){
    long long int N = Nque[cur];
    int lloc = Lque[cur];
    long long int S = Sque[cur];
    long long int lens = lenque[cur];
    long long int predN = Nque[cur];
    if(S<0) printf("Overflow");
    if((findSol)&&(N==4)){
        int sol[100000];
        printf("solution: ");
        if(lens==0){
            printf("Do nothing.");
        }
        int move;
        // int i=0;
        // printf("\n%lld\n%lld\n",S,lens);
        int i=0;
        while(cur>0){
            int this_move = Sque[cur];
            sol[i] = cur; // mai konse index se aaya (queue me se)
            cur = pred_que[cur];
            i++;
        }

        int ii = i;
        while (i>0)
        {
            i--;
            printf("%s",MoveNames[Sque[sol[i]]]);

        }
        printf("\n\n");
        printf("The boards are: \n\n");

        while(ii>0){
            ii--;
            decode(Nque[sol[ii]],M);
            Disp(M);
            printf("\n");
        }
        
        // printf("\nsolution occured after %d checks\n Final condition : \n",cur+1);
        // decode(N,M);
        // Disp(M);
        return 1;
    }
    lloc = decode(N,M);
    int locN;
    int childN;
    for(int move = 0;move<4;move++){
        locN = apply(move,M,lloc);
        if(locN!=lloc){
            childN = encode(M,locN);
            int vis = visited[childN];
            if(vis==0){
                Last++;
                Nque[Last] = childN;
                Lque[Last] = locN;
                Sque[Last] = move;
                pred_que[Last] = cur;
                lenque[Last] = lens + 1;
                visited[childN] = 1;
            }
            apply(revMoves[move],M,locN);
        }
    }
    visited[N] = 2;
    if((Last>=N_maxn1-1)&&(!reachedend)){
        printf("Every possibility is in que at %d iteration\n",cur+1);
        reachedend = 1;
    }
    if(Last<=cur){
        printf("Terminated after %d checks. All possiblities checked ",cur+1);
        if(findSol){
            printf(" and no solution found.\n");
        }else{
            int checks = 0;
            int supposedtocheck = 0;
            for(int i=0;i<N_maxn1;i++){
                if(visited[i]==2){checks+=1;}
                if(visited[i]==1){printf("unchecked sit %d\n",i);}
                if(visited[i]>0){supposedtocheck+=1;}
            }
            printf("\nsupposed to check :%d\n",supposedtocheck);
            printf("actually checked :%d\n",checks);
        }
        return 1;
    }
    cur++;
    return 0;
}
int main(){
    int move;
    printf("enter the orientations of painted faces of boxes (3 in a row) according to this scheme:\n");
    printf("0 for facing up,\n");
    printf("1 for facing left,\n");
    printf("2 for facing away from you,\n");
    printf("3 for facing down,\n");
    printf("4 for facing right,\n");
    printf("5 for facing towards you,\n");
    printf("-1 if there is there is no box.\n");
    for(int i=0;i<3;i++){
        printf("row %d :\n",i+1);
        for(int j=0;j<3;j++){
            printf("enter move :");
            scanf("%d",&move);
            if(move==-1){
                loc = 3*i + j;
            }
            M[i][j]=move;
        }
    }
    printf("The initial situation given :\n");
    Disp(M);
    printf("\n");
    visited[encode(M,loc)] = 1;
    Nque[0] = encode(M,loc);
    Lque[0] = loc;
    Sque[0] = 0;
    lenque[0] = 0;
    pred_que[0] = 0;
    for(int N=1;N<N_maxn1;N++){
        visited[N]=0;
    }
    int done = 0;
    for(int iterat=0;iterat<15116544;iterat++){
        done = Update(1);
        if(done){
            break;
        }
    }
    return 0;
}

// Solution to CCL's upitup game: 
// URDLDRURDLURULLDRDLURULDRULDRDLURRDL