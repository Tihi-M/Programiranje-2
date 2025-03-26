#include <iostream>
#include <vector>
#include <stack>
#include <queue>

std::vector<std::vector<int>> ucitajGraf(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graf(n, std::vector<int>(n, 0));

    bool usmjeren;
    std::cin >> usmjeren;

    for(int i=0; i<m; i++){
        int x, y;
        std::cin >> x >> y;

        x--;
        y--;

        graf[x][y] = 1;
        if(!usmjeren){
            graf[y][x] = 1;
        }
    }

    return graf;
}

std::vector<std::vector<int>> ucitajGrafIzFajla(char* putanja){
    int n, m;
    FILE* f = fopen(putanja, "r");
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

bool postojiPut(std::vector<std::vector<int>>& graf, int start, int kraj, std::vector<int>& posjecen, std::vector<int>& prethodni){
    if(start==kraj)
        return true;

    posjecen[start] = 1;
    for(int i=0; i<graf.size(); i++){
        if(graf[start][i]==1 && posjecen[i]==0 && postojiPut(graf, i, kraj, posjecen, prethodni)){
            prethodni[i] = start;
            return true;
        }
    }

    return false;
}

void stampajPutanju(int start, int kraj, std::vector<int>& prethodni){
    int tren = kraj;
    std::stack<int> s;
    s.push(kraj);

    while(tren!=start){
        tren = prethodni[tren];
        s.push(tren);
    }

    std::cout << s.top();
    s.pop();
    while(!s.empty()){
        std::cout << "->" << s.top();
        s.pop();
    }
    std::cout << std::endl;
}

void stampajGraf(std::vector<std::vector<int>> graf){
    for(int i = 0; i < graf.size();i++)
    {
        for(int j = 0; j < graf[0].size();j++)
            std::cout<<graf[i][j] <<  " ";
        std::cout<<std::endl;
    }
}

int main(){

    std::vector<std::vector<int>> graf = ucitajGrafIzFajla("grafUnos.txt");
    stampajGraf(graf);

    std::vector<int> prethodni(graf.size(),-1);
    std::vector<int> posjeceni(graf.size(),0);

    bool postoji = postojiPut(graf,2,7,posjeceni,prethodni);

    if(postoji)
        stampajPutanju(2,7,prethodni);

    return 0;
}
