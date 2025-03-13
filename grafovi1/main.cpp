#include <iostream>
#include <vector>

std::vector<std::vector<int>> ucitajGraf(){
    int n,m;
    std::cin>>n>>m;

    bool usmjeren;
    std::cin>>usmjeren;

    std::vector<std::vector<int>> graf(n,std::vector<int>(n,0));

    for(int i = 0;  i < m;i++){
        int x,y;
        std::cin>> x >> y;
        graf[x][y] = 1;
        if(usmjeren)
            graf[x][y] = 0;
    }

    return graf;
}


bool postojiPut(int start, int kraj, std::vector<std::vector<int>>& graf, bool* posjecen){
    if(start==kraj)
        return true;

    posjecen[start] = true;
    for(int i=0; i<graf.size(); i++){
        if(graf[start][i]==1 && posjecen[i]==false && postojiPut(i, kraj, graf, posjecen))
            return true;
    }

    return false;
}

int main()
{

std::vector<std::vector<int>> graf = ucitajGraf();

    for(int i = 0; i < graf.size();i++){
        for(int j = 0; j < graf.size();j++)
            std::cout<< graf[i][j] << " ";
    std::cout<<std::endl;
    }

    /*
    bool* posjecen = new bool[graf.size()];
    for(int i=0; i<graf.size(); i++)
        posjecen[i] = false;

    std::cout<<postojiPut(0,7,graf,posjecen)<<std::endl;*/
    return 0;
}
