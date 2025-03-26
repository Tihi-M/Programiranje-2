#include <iostream>
#include <vector>
#include <stack>
#include <queue>

std::vector<std::vector<int>> ucitajgraf(){
    /// n - broj cvorova, m - broj grana

    int n,m;
    std::cin>>n>>m;
    /// matrica n*n - ako je polje 1 postoji
    /// grana koja povezuje cvorove,inc 0
    std::vector<std::vector<int>> graf(n,std::vector<int>(n,0));

    bool usmjeren;
    std::cin>>usmjeren;

    for(int i = 0; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        graf[x][y] = 1;
        if(!usmjeren)
            graf[y][x] = 1;
    }

    return graf;


}

std::vector<std::vector<int>> ucitajGrafFile(char* putanja){
    int n, m;
    FILE* f = fopen(putanja, "r");
      if (!f) {
        printf("Error: Unable to open file %s\n", putanja);
        return {};
    }
    fscanf(f, "%d%d", &n, &m);
    std::vector<std::vector<int>> graf(n, std::vector<int>(n, 0));

    int usmjeren;
    fscanf(f, "%d", &usmjeren);
    for(int i=0; i<m; i++){
        int x, y;
        fscanf(f, "%d%d",  &x, &y);
        graf[x][y] = 1;

        if(!usmjeren){
            graf[y][x] = 1;
        }
    }
    fclose(f);
    return graf;
}

bool postojiPut(std::vector<std::vector<int>>& graf,int start,int kraj,std::vector<int>& posjecen,std::vector<int>& prethodni){
    if(start == kraj)
        return true;

    posjecen[start] = 1;
    for(int i =0;i < graf.size();i++){
        if(graf[start][i] == 1 && posjecen[i] == 0 && postojiPut(graf,i,kraj,posjecen,prethodni))
        {
            prethodni[i] = start;
            return true;
        }
    }

    return false;
}
void dfs(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen){
    posjecen[start] = true;

    for(int i = 0; i < graf.size();i++)
    {
        if(graf[start][i] != 0 && posjecen[i] == false)
            dfs(graf,i,posjecen);

    }
}

void dfsPutanja(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen,std::vector<int>& prethodni){
    posjecen[start] = true;

    for(int i = 0; i < graf.size();i++){
        if(graf[start][i] == 1 && posjecen[i] == false){
            prethodni[i] = start;
            dfsPutanja(graf,i,posjecen,prethodni);
            }

    }
}

bool postojiPutDfs(std::vector<std::vector<int>>& graf,int start,int kraj, std::vector<int>& posjecen,std::vector<int>& prethodni){
    dfsPutanja(graf,start,posjecen,prethodni);
    return posjecen[kraj];
}


void stampajGraf(std::vector<std::vector<int>> graf){
    int n = graf.size();
    for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
            std::cout<<graf[i][j]<<" ";
        std::cout<<std::endl;
    }
}

void stampajPutanju(int start,int kraj,std::vector<int>& prethodni){
    int tren = kraj;
    std::stack<int> s;
    s.push(kraj);

    while(tren!=start){
        tren = prethodni[tren];
        s.push(tren);
    }
    std::cout<<s.top();
    s.pop();
    while(!s.empty()){
        std::cout<<"->"<<s.top();
        s.pop();
    }
    std::cout<<std::endl;
}

void bfs(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen){
    std::queue<int> red;

    red.push(start);
    while(!red.empty()){
        int tren = red.front();
        red.pop();
        posjecen[tren] = true;

        for(int i = 0; i < graf.size();i++)
            if(graf[tren][i] != 0 && posjecen[i] == false)
                red.push(i);
    }
}

void bfsPutanja(std::vector<std::vector<int>>& graf,int start, std::vector<int>& posjecen,std::vector<int>& prethodni){
    std::queue<int> red;

    red.push(start);
    posjecen[start] = true;

    while(!red.empty()){
        int tren = red.front();
        red.pop();

        for(int i = 0; i < graf.size();i++){
            if(graf[tren][i] != 0 && posjecen[i] == false){
                prethodni[i] = tren;
                posjecen[i] = true;
                red.push(i);
            }
        }
    }
}

bool postojiPutBfs(std::vector<std::vector<int>>& graf,int start,int kraj,std::vector<int>& posjecen,std::vector<int>& prethodni){
    bfsPutanja(graf,start,posjecen,prethodni);
    return posjecen[kraj];
}

int brojKomponentiPovezanostiDfs(std::vector<std::vector<int>>& graf){
    std::vector<int> posjecen(graf.size(),0);

    int cnt = 0;
    for(int i = 0; i < graf.size();i++){
        if(posjecen[i] == 0){
            dfs(graf,i,posjecen);
            cnt++;
        }
    }

    return cnt;
}

int brojKomponentiPovezanostiBfs(std::vector<std::vector<int>>& graf){
    std::vector<int> posjecen(graf.size(),0);
    for(int i = 0; i < graf.size();i++)
        posjecen[i] = false;

    int cnt = 0;
    for(int i = 0; i < graf.size();i++){
        if(posjecen[i] == 0){
            bfs(graf, i, posjecen);
            cnt++;
        }
    }
    return cnt;
}

int main()
{

    std::vector<std::vector<int>> graf = ucitajGrafFile("grafUnos1.txt");
    stampajGraf(graf);
    std::cout<<std::endl;
    //std::vector<int> prethodni(graf.size(),-1);
    //std::vector<int> posjecen(graf.size(),0);


    //bool postoji = postojiPutBfs(graf,0,5,posjecen,prethodni);
    //if(postoji)
     //   stampajPutanju(0,5,prethodni);
    std::cout<<brojKomponentiPovezanostiBfs(graf)<<std::endl;
    return 0;
}
