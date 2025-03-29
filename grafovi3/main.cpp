#include <iostream>
#include <stack>
#include <queue>
#include <vector>

std::vector<std::vector<int>> ucitajGraf(){
    int n,m;
    std::cin>>n>>m;
    std::vector<std::vector<int>> graf(n,std::vector<int>(n,0));
    bool usmjeren;
    std::cin>>usmjeren;

    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        graf[x][y] = 1;
        if(!usmjeren)
            graf[y][x] = 1;
    }

    return graf;
}

std::vector<std::vector<int>> ucitajGrafFile(char* putanja){
    int n,m;
    FILE* f = fopen(putanja,"r");
    fscanf(f,"%d%d",&n,&m);

    std::vector<std::vector<int>> graf(n,std::vector<int>(n,0));
    int usmjeren;
    fscanf(f,"%d",&usmjeren);
    for(int i = 0; i < m;i++){
        int x,y;
        fscanf(f,"%d%d",&x,&y);
        graf[x][y] = 1;
        if(!usmjeren)
            graf[y][x] = 1;
    }
    return graf;
}

void stampajGraf(std::vector<std::vector<int>>& graf){
    for(int i = 0; i < graf.size();i++){
        for(int j = 0; j < graf.size();j++)
            std::cout<<graf[i][j] << " ";
        std::cout<<std::endl;
    }
}

bool postojiPut(std::vector<std::vector<int>>& graf,int start,int kraj,std::vector<int>& posjecen,std::vector<int>& prethodni){
    if(start == kraj)
        return true;

    posjecen[start] = 1;
    for(int i = 0; i < graf.size();i++)
        if(graf[start][i] == 1 && posjecen[i] == 0 && postojiPut(graf,i,kraj,posjecen,prethodni)){
            prethodni[i] = start;
            return true;
        }
    return false;
}

void stampajPutanju(std::vector<int>& prethodni,int start,int kraj){
    int temp = kraj;
    std::stack<int> s;
    s.push(temp);
    while(temp != start){
        temp = prethodni[temp];
        s.push(temp);
    }

    std::cout<<s.top();
    s.pop();
    while(!s.empty()){
        std::cout<<"->"<<s.top();
        s.pop();
    }
    std::cout<<std::endl;
}

void dfs(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen){
    posjecen[start] = 1;
    for(int i = 0; i < graf.size();i++){
        if(graf[start][i] == 1 && posjecen[i]==0)
            dfs(graf,i,posjecen);
    }
}

void dfsPutanja(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen,std::vector<int>& prethodni){
    posjecen[start] = 1;
    for(int i = 0; i < graf.size();i++){
        if(graf[start][i] == 1 && posjecen[i] == 0)
        {
            prethodni[i] = start;
            dfsPutanja(graf,i,posjecen,prethodni);
        }
    }
}

bool postojiPutDfs(std::vector<std::vector<int>>& graf, int start,int kraj, std::vector<int>& posjecen,std::vector<int>& prethodni){
    dfsPutanja(graf,start,posjecen,prethodni);
    return posjecen[i];
}

void bfs(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen){
    std::queue<int> red;
    red.push(start);

    while(!red.empty){
        int temp = red.front();
        red.pop();
        posjecen[temp] = 1;
        for(int i = 0; i < graf.size();i++){
            if(graf[temp][i] == 1 && posjecen[i] == 0)
                red.push(i);
        }
    }
}

void bfsPutanja(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen, std::vector<int>& prethodni){
    std::queue<int> red;
    red.push(start);

    while(!red.empty()){
        int temp = red.front();
        red.pop();
        posjecen[temp] = 1;
        for(int i =0 ; i < graf.size();i++){
            if(graf[temp][i] == 1 && posjecen[i] == 0){
                prethodni[i] = temp;
                red.push(i)
            }
        }
    }
}

bool postojiPutBfs(std::vector<std::vector<int>>& graf,int start,int kraj, std::vector<int>& posjecen,std::vector<int>& prethodni){
    bfsPutanja(graf,start,posjecen,prethodni);
    return posjecen[kraj];
}

int brojKompPovDfs(std::vector<std::vector<int>>& graf){
    int cnt = 0;

    std::vector<int> posjecen(graf.size(),0);
    for(int i = 0; i < graf.size();i++){
        if(posjecen[i] == 0){
            dfs(graf,i,posjecen);
            cnt++;
        }
    }

    return cnt;
}


int brojKompPovDfs(std::vector<std::vector<int>>& graf){
    int cnt = 0;

    std::vector<int> posjecen(graf.size(),0);
    for(int i = 0; i < graf.size();i++){
        if(posjecen[i] == 0){
            bfs(graf,i,posjecen);
            cnt++;
        }
    }

    return cnt;
}

bool bipartitan(std::vector<std::vector<int>>& graf){
    std::vector<int> boja(graf.size(),0);

    std::queue<int> red;
    for(int i = 0; i < graf.size();i++){
        if(boja[i] == -1){
            red.push(i);
            boja[i] == 0;
            while(!red.empty()){
                int temp = red.front();
                red.pop();

                for(int j = 0; j < graf.size();j++){
                    if(graf[temp][j] == 1){
                        if(boja[j] == - 1){
                            boja[j] = 1-boja[temp];
                            red.push();
                        }
                        else if(boja[j] == boja[i])
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

void dfsTopSort(std::vector<std::vector<int>>& graf,int start,std::vector<int>& posjecen,std::stack<int>& s){
    if(posjecen[start])
        return;

    posjecen[start] = 1;

    for(int i = 0; i < graf.size();i++)
        if(graf[start][i] == 1)
        dfsTopSort(graf,i,posjecen,s);
    s.push(start);
}

void topSort(std::vector<std::vector<int>>& graf){
    std::vector<int> posjecen(graf.size(),0);
    std::stack<int> s;

    for(int i = 0 ;i < graf.size();i++){
        if(posjecen[i] == 0)
            dfsTopSort(graf,i,posjecen,s);
    }

    while(!s.empty()){
        std::cout<<s.top()<<" ";
        s.pop();
    }

    std::cout<<std::endl;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
