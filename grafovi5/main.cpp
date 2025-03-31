#include <iostream>
#include <vector>
#include <queue>
#include <stack>

typedef std::vector<std::vector<char>> graf;
typedef struct tacka{
    int x;
    int y;
}tacka;

void bfs(graf& mat,int m,int n,tacka start, std::vector<tacka>& posjecen){
    std::queue<tacka> red;
    red.push(start);
    mat[start.x][start.y] = 'p';
    int dirs[4][4] = {{1,0},{0,-1},{0,1},{-1,0}};
    while(!red.empty()){
        tacka temp = red.front();
        red.pop();
        auto [x,y] = temp;
        posjecen.push_back({x,y});

        for(int i = 0; i < 4;i++){
            int novoX = x+dirs[i][0];
            int novoY = y+dirs[i][1];

            if(novoX >= 0 && novoY >= 0 && novoX < m && novoY < n && mat[novoX][novoY] == '.'){
                mat[novoX][novoY] = 'p';
                red.push({novoX,novoY});
            }
        }
    }

}



void zidovi(){
    int m,n,k;
    std::cin>>m>>n>>k;
    graf mat(m,std::vector<char>(n,'0'));
    int startX = -1;
    int startY = -1;

    for(int i = 0 ; i < m;i++)
        for(int j = 0; j < n;j++){
                std::cin>>mat[i][j];
            if(mat[i][j] == '.' && startX == -1 && startY == -1)
            {
                startX = i;
                startY = j;
            }
        }

    tacka start = {startX,startY};
    std::vector<tacka> posjecen;

    bfs(mat,m,n,start,posjecen);

    for(int i = (int)posjecen.size()-1;i >= (int)posjecen.size()-k;i--){
        auto[x,y] = posjecen[i];
        mat[x][y] = 'X';
    }

    std::cout<<std::endl;
    for(int i =0; i < m;i++){
        for(int j = 0; j < n;j++)
            if(mat[i][j] == 'p')
                std::cout<<'.'<<" ";
            else std::cout<<mat[i][j]<<" ";
            std::cout<<std::endl;
    }

}
int main()
{
    zidovi();
    return 0;
}
