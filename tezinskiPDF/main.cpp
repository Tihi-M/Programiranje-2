#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <limits>
#include <cmath>

std::vector<std::vector<int>> ucitaj_graf(int s){
    int n,m;
    std::cin>>n >> m >> s;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x >> y >> w;
        //x--;
        //y--;
        g[x][y] = w;
        //g[y][x] = w;
    }
    return g;
}

typedef struct my_cmp{
    bool operator() (std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
}my_cmp;

std::vector<int> dijsktra1(std::vector<std::vector<int>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> distance(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;

    pq.push(std::make_pair(start,0));
    distance[start] = 0;

    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distance[j] > distance[i] + g[i][j])
                    distance[j] = distance[i] + g[i][j];
                    pq.push(std::make_pair(j,distance[j]));
            }
        }

        posjecen[i] = 1;
    }

    return distance;
}

void zad1(){
    int start;
    std::vector<std::vector<int>> g = ucitaj_graf(start);
    start--;///!!!!!!!
    std::vector<int> distance = dijsktra1(g,start);

    int maxx = 0;
    for(int i = 0;i < g.size();i++){
        if(distance[i] == INT_MAX){
                std::cout<<-1;
                return;
        }
        else if(distance[i] > maxx)
            maxx = distance[i];
    }

    std::cout<< maxx;

}

void zad2(){
    int d;

    std::vector<std::vector<int>> g = ucitaj_graf(d);

    int min_d = INT_MAX;
    int res_node = -1;
    for(int i = 0;i < g.size();i++){
        std::vector<int> distance = dijsktra1(g,i);
        int cnt = 0;
        for(int j = 0;j < g.size();j++)
            if(distance[j] <= d)
                cnt++;
        if(cnt < min_d){
            min_d = cnt;
            res_node = i;
        }
        else if(min_d == cnt){
            res_node = std::max(i,res_node);
        }
    }

    std::cout<<res_node;
}


std::vector<std::vector<double>> ucitaj_graf2(int& a,int& b){
    int n,m;
    std::cin>> n >> m >> a >> b;

    std::vector<std::vector<double>> g(n,std::vector<double>(n,0.0));

    for(int i = 0;i < m;i++){
        int x,y;
        double w;
        std::cin >> x >> y >> w;
        g[x][y] = w;
        g[y][x] = w;
    }
    return g;
}

typedef struct my_cmp2{
    bool operator()(std::pair<int,double> a,std::pair<int,double> b){
        return a.second < b.second;
    }
}my_cmp2;

std::vector<int> dijsktra17(std::vector<std::vector<double>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<double> distanca(g.size(),0);

    std::priority_queue<std::pair<int,double>,std::vector<std::pair<int,double>>,my_cmp2> pq;
    pq.push(std::make_pair(start,1.0));
    distanca[start] = 1.0;
    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();
        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distanca[j] < distanca[i] * g[i][j]){
                    distanca[j] = distanca[i] * g[i][j];
                    putanja[j] = i;
                    pq.push(std::make_pair(j,distanca[j]));
                }
            }
        }

        posjecen[i] = 1;
    }

    return putanja;
}

void zad3(){
    int a,b;
    std::vector<std::vector<double>> g = ucitaj_graf2(a,b);

    std::vector<int> putanja = dijsktra17(g,a);

    std::stack<int> s;
    int curr = b;
    while(curr != -1){
        s.push(curr);
        curr = putanja[curr];
    }
    while(!s.empty()){
        std::cout<<s.top()<<" ";
        s.pop();
    }
}

std::vector<std::vector<int>> ucitaj_graf3(int& s,int& t,int& k){
    int n,m;
    std::cin>> n >> m >> s >> t >> k;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x >> y >> w;
        x--;
        y--;
        g[x][y] = w;
    }
    return g;
}

int dijsktra18(std::vector<std::vector<int>>& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> distance(g.size(),INT_MAX);
    std::vector<int> putanja(g.size(),-1);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;

    pq.push(std::make_pair(start,0));
    distance[start] = 0;

    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();
        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distance[j] > distance[i] + g[i][j]){
                    distance[j] = distance[i] + g[i][j];
                    putanja[j] = i;
                    pq.push(std::make_pair(j,distance[j]));
                }
            }
        }
        posjecen[i] = 1;

    }

    int dist = 0;
    int curr = kraj;
    std::stack<int> s;
    while(curr != -1){
        s.push(curr);
        curr = putanja[curr];
    }

    while(!s.empty()){
        int top = s.top();
        s.pop();
        if(!s.empty())
            dist+=g[top][s.top()];
    }
    return dist;
}


void zad18(){
    int s,t,k;
    std::vector<std::vector<int>> g = ucitaj_graf3(s,t,k);
    s--;
    t--;
    int min_dist = dijsktra18(g,s,t);
    for(int i = 0;i < k;i++){
        int x,y,w;

        std::cin>>x>>y>>w;
        x--;
        y--;
        int prev_len = 0;
        if(g[x][y] != 0)
            prev_len = g[x][y];

        g[x][y] = w;

        int temp_dist = dijsktra18(g,s,t);
        if(min_dist > temp_dist)
            min_dist = temp_dist;

        g[x][y] = prev_len;
    }

    std::cout<<min_dist;
}

typedef struct Edge{
    int i;
    int j;
    int w;
}Edge;

typedef struct my_cmp3{
    bool operator()(Edge a,Edge b){
        return a.w > b.w;
    }
}my_cmp3;


std::vector<std::vector<int>> ucitaj_graf4(){
    int n,m;
    std::cin>>n >> m;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x >> y >> w;
        //x--;
        //y--;
        g[x][y] = w;
        //g[y][x] = w;
    }
    return g;
}

int kruskal(std::vector<std::vector<int>>& g){
    int cc[g.size()];
    int nadredjeni[g.size()];
    for(int i = 0;i < g.size();i++){
        cc[i] = i;
        nadredjeni[i] = -1;
    }

    std::priority_queue<Edge,std::vector<Edge>,my_cmp3> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
        if(g[i][j] != 0 && i!=j)
            pq.push({i,j,g[i][j]});

    int wt = 0;
    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        if(cc[i] != cc[j] && nadredjeni[j] == -1){
            nadredjeni[j] = i;
            for(int k = 0;k < g.size();k++)
                if(cc[k] == cc[i])
                    cc[k] = cc[j];

            wt+=w;

        }
    }

    int temp = 0;
    for(int i = 0;i < g.size();i++)
        if(nadredjeni[i] == -1)
            temp++;

    if(temp != 1)
        return -1;
    return wt;
}

void zad19(){
    std::vector<std::vector<int>> g = ucitaj_graf4();
    std::cout<<kruskal(g);

}

int manhattan(int x1,int y1,int x2,int y2){
    return std::abs(x1-x2) + std::abs(y1-y2);
}

typedef struct Tacka{
    int x;
    int y;
    int pos;
}Tacka;

std::vector<std::vector<int>> ucitaj_graf5(){
    int n;
    std::cin >> n;
    std::vector<Tacka> tacke;

    for(int i = 0;i < n;i++){
        int x,y;
        std::cin>> x >> y;
        tacke.push_back({x,y,i});
    }

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i=  0;i < n;i++){
        for(int j =i+1;j < n;j++){
            g[tacke[i].pos][tacke[j].pos] = manhattan(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
            g[tacke[j].pos][tacke[i].pos] = manhattan(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
        }
    }

    return g;
}

int kruskal2(std::vector<std::vector<int>>& g){
    int roditelj[g.size()];
    for(int i = 0;i < g.size();i++)
        roditelj[i] = -1;

    std::priority_queue<Edge,std::vector<Edge>,my_cmp3> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0; j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        while(roditelj[i] != -1)
            i = roditelj[i];

        while(roditelj[j] != -1)
            j = roditelj[j];

        if(i!=j){
            wt+=w;
            roditelj[j] = i;
        }

    }
    return wt;
}

void zad20(){
    std::vector<std::vector<int>> g = ucitaj_graf5();
    std::cout<< kruskal2(g);
}

double euclid(int x1,int y1,int x2,int y2){
    return std::sqrt(std::pow(x2-x1,2) + std::pow(y2-y1,2));
}

std::vector<std::vector<double>> ucitaj_graf6(int& k){
    int n;
    std::cin >> n >> k;

    std::vector<Tacka> tacke;

    for(int i = 0;i < n;i++){
        int x,y;
        std::cin >> x >> y;
        tacke.push_back({x,y,i});
    }

    std::vector<std::vector<double>> g(n,std::vector<double>(n,0.0));

    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            g[tacke[i].pos][tacke[j].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
            g[tacke[j].pos][tacke[i].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
        }
    }

    return g;
}

typedef struct Edge2{
    int i;
    int j;
    double w;
}Edge2;

typedef struct my_cmp4{
    bool operator() (Edge2 a, Edge2 b){
        return a.w > b.w;
    }
}my_cmp4;

double kruskal3(std::vector<std::vector<double>>& g,double stari_kablovi,int k){
    int roditelji[g.size()];

    for(int i = 0;i < g.size();i++)
        roditelji[i] = -1;

    std::priority_queue<Edge2,std::vector<Edge2>,my_cmp4> pq;

    for(int i = 0;i < g.size();i++){
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});
    }

    double wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        while(roditelji[i] != -1)
            i = roditelji[i];

        while(roditelji[j] != -1)
            j = roditelji[j];

        if(i != j){
            wt+=w;
            roditelji[j] = i;
        }
    }

    return wt*k - stari_kablovi;
}

void zad21(){
    int k;
    std::vector<std::vector<double>> g =  ucitaj_graf6(k);
    int m;
    std::cin>>m;

    double vec_postoji = 0;
    for(int i = 0; i< m;i++){
        int x,y;
        std::cin>>x>>y;
        if(g[x][y] != 0)
            vec_postoji+=g[x][y];
    }

    std::cout<<std::ceil(kruskal3(g,vec_postoji*k,k)*100.0)/100.0;

}

typedef struct Tacka2{
    int x;
    int y;
    int pos;
    bool voda;
}Tacka2;

std::vector<std::vector<double>> ucitaj_graf7(int& k){
    int n;
    std::cin>> n >>k;

    std::vector<Tacka2> tacke;

    for(int i = 0;i < n; i++){
        int x,y,v;

        std::cin>>x>>y>>v;
        tacke.push_back({x,y,i,v});
    }

    std::vector<std::vector<double>> g(n,std::vector<double>(n,-1.0));

    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            if(tacke[i].voda && tacke[j].voda){
                g[tacke[i].pos][tacke[j].pos] = 0;
                g[tacke[j].pos][tacke[i].pos] = 0;
            }
            else{
                g[tacke[i].pos][tacke[j].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);;
                g[tacke[j].pos][tacke[i].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
            }
        }
    }

    return g;
}

double kruskal4(std::vector<std::vector<double>>& g,int k){
    int roditelj[g.size()];

    for(int i = 0;i < g.size();i++)
        roditelj[i] = -1;

    std::priority_queue<Edge2,std::vector<Edge2>,my_cmp4> pq;

    for(int i = 0;i < g.size();i++)
        for(int j =i+1;j < g.size();j++)
            if(g[i][j] >= 0.0)
                pq.push({i,j,g[i][j]});

    double wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        while(roditelj[i] != -1)
            i = roditelj[i];

        while(roditelj[j] != -1)
            j = roditelj[j];

        if(i != j)
        {
            wt+=w;
            roditelj[j] = i;
        }
    }

    return wt*k;
}

void zad22(){
    int k;
    std::vector<std::vector<double>> g = ucitaj_graf7(k);

    std::cout<<std::ceil(kruskal4(g,k)*100.0)/100.0;
}

int main()
{
    zad22();
    return 0;
}
