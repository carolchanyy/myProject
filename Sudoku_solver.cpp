#include <iostream>
#include<queue>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

ofstream fout("sudoku.out");
ifstream fin("sudoku.in");

int N=9;
int grid[9][9];

void print(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fout << grid[i][j] << " ";
        }
        fout << endl;
    }
    fout << endl;
}

bool isAnyUnassigned(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j]==0){
                return true;
            }
        }
    }

    return false;
}

bool isSafe(int row, int col, int value){
    //Row check. Any value used in that row
    for(int j=0; j<N; j++){
        if(grid[row][j]==value){
            return false;
        }
    }

    //Column check. Any value used in that column
    for(int i=0; i<N; i++){
        if(grid[i][col]==value){
            return false;
        }
    }

    //subgrid check
    for(int NRow=(row/3)*3; NRow<(row/3)*3 +3; NRow++){
        for(int Ncol=(col/3)*3; Ncol<(col/3)*3 +3; Ncol++){
            if(grid[NRow][Ncol]==value){
                return false;
            }
        }
    }

    return true;
}

bool solve(int row, int col){

    if(!isAnyUnassigned()){
        return true;  //all assigned
    }

    if(col==N){
        row++;
        col=0;
    }

    if(grid[row][col]!=0){
        return solve(row, col+1);
    }

    for (int value=1; value<=N; value++){
        if(isSafe(row, col, value)){
            grid[row][col]=value;

            if(solve(row, col+1)){
                return true;
            }
            grid[row][col]=0;
        }
    }


    return false;
}


int main() {



    int count=100;

    while(count>0){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                fin >> grid[i][j];
            }
        }

        if(solve(0,0)){
            print();
        }

        else{
            fout << "No Solution" << endl;
        }

        count--;
    }



	return 0;
}
