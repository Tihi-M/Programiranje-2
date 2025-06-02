#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>

void stampaj_matricu(int** x,int n){
    for(int i = 0; i < n;i++){
        for(int j = 0;j < n;j++)
            std::cout<<x[i][j]<< " ";
        std::cout<<"\n";
    }
}

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m,usmjeren;
    std::cin>>n>>m>>usmjeren;

    std::vector<std::vector<int>> graf(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x >> y >> w;
        graf[x][y] = w;
        if(!usmjeren);
            graf[y][x] = w;
    }
    return graf;
}

int shortest_path(std::vector<std::vector<int>>& graf,int start,int kraj,std::vector<int>& posjecen,std::vector<int>& prethodni){
    if(start == kraj)
        return 0;
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
