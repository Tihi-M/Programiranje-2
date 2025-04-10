#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <cstdlib>

typedef std::vector<std::vector<char>> graf;

typedef struct polje{
    int x;
    int y;
}polje;

void printMap(graf& g,int m,int n){
    for(int i = 0;i < m;i++)
    {
        for(int j = 0; j < n;j++)
            std::cout<<g[i][j]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    sleep(0.2);
    system("cls");
}

bool valid(int x,int y,int m,int n){
    return x>=0 && x < m && y >= 0 && y < n;
}


int bfs(graf& g,int m,int n,int startX,int startY,int ciljX,int ciljY){
    std::queue<polje> red;
    std::vector<std::vector<bool>> posjeceni(m,std::vector<bool>(n,false));
    int brKoraka = 0;

    posjeceni[startX][startY] = true;//posjeceno;
    g[startX][startY] =  ',';
    red.push({startX,startY});

    int dirs[4][2] = {{1,0},{0,-1},{0,1},{-1,0}};

    while(!red.empty()){
        int redLen = red.size();
        for(int i = 0; i < redLen;++i){
            auto[x,y]=red.front();
            red.pop();

            if(x == ciljX && y == ciljY){
                return brKoraka;
            }

            for(int j = 0; j < 4 ;++j){
                int x_ = x+dirs[j][0];
                int y_ = y+dirs[j][1];

                if(valid(x_,y_,m,n) && !posjeceni[x_][y_] && (g[x_][y_] == '.' || g[x_][y_] == '*')){
                    posjeceni[x_][y_] = true;
                    //prev[x_][y_] = {x,y};
                    red.push({x_,y_});
                }
                printMap(g,m,n);
            }
        }
        brKoraka++;
    }
    return -1;
}

void robot(char* putanja){
    int m,n;
    std::cin>>n>>m;
    //FILE* f = fopen("mapa1.txt","r");
    //fscanf(f,"%d %d",&m,&n);
    //std::cout<<m<<" "<<n;
    graf g(m,std::vector<char>(n));
    int robotX,robotY;
    std::queue<polje> ciljevi;
    for(int i = 0; i < m;i++){
        for(int j = 0;j < n;j++){
            std::cin>>g[i][j];
            //fscanf(f," %c",&g[i][j]);
            if(g[i][j] == '@')
            {
                robotX = i;
                robotY = j;
            }
            else if(g[i][j] == '*')
                ciljevi.push({i,j});
        }
    }

    //fclose(f);
    int ukupnoKoraka = 0;
    while(!ciljevi.empty()){
        auto[x,y] = ciljevi.front();
        ciljevi.pop();
        int koraci = bfs(g,m,n,robotX,robotY,x,y);
        if(koraci == -1){
            std::cout<<-1<<std::endl;
            return;
        }
        ukupnoKoraka += koraci;
        robotX = x;
        robotY = y;
        g[x][y] = '.';
    }
    std::cout<<ukupnoKoraka<<std::endl;

}

int main()
{
    robot("mapa2.txt");
    return 0;
}
