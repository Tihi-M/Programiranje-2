#include <iostream>
#include <stack>
#include <queue>
#include <vector>

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m,usmjeren;
    std::cin>>n>>m>>usmjeren;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x>>y>>w;
        g[x][y]= w;
        if(!usmjeren)
            g[y][x] = w;
    }
    return g;
}

void print_matrix(std::vector<std::vector<int>>& g,int n){
    for(int i = 0;i < g.size();i++){
        for(int j = 0;j < g.size();j++)
            std::cout<< g[i][j] << " ";
        std::cout<<std::endl;
    }
}

void floyd_warshall(std::vector<std::vector<int>>& g,std::vector<std::vector<int>>& distance,std::vector<std::vector<int>>& putanja){
    for(int i =0;i < g.size();i++){
        for(int j = 0;j < g.size();j++){
            if(i == j){
                distance[i][j] = 0;
                putanja[i][j] = i;
            }
            else if(g[i][j] != 0){
                distance[i][j] = g[i][j];
                putanja[i][j] = j;
            }
            else{
                distance[i][j] = INT_MAX;
                putanja[i][j] = -1;

            }
        }
    }

    for(int k = 0;k < g.size();k++){
        for(int i = 0;i < g.size();i++){
            for(int j = 0;j < g.size();j++){
                if(distance[i][j]<INT_MAX && distance[k][j] < INT_MAX){
                    if(distance[i][j] > distance[i][k] + distance[k][j]){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        putanja[i][j]= putanja[i][k];
                    }
                }
            }
        }
    }

    print_matrix(distance,g.size());
    std::cout<<std::endl;
    print_matrix(putanja,g.size());
}

void recon_path(std::vector<std::vector<int>>& putanja,int i,int j){
    int curr = i;
    while(curr != j){
        std::cout<<putanja[curr][j]<< " ";
        curr = putanja[curr][j];
    }
    std::cout<<j << std::endl;
}

typedef struct Edge{
    int i;
    int j;
    int w;
}Edge;

typedef struct my_cmp{
    bool operator()(Edge a,Edge b){
        return a.w > b.w;
    }
}my_cmp;


int kruskal1(std::vector<std::vector<int>>& g){
    int cc[g.size()];

    for(int i =0;i < g.size();i++)
        cc[i] = i;

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        if(cc[i] != cc[j]){
            for(int k = 0;k < g.size();k++)
                if(cc[k] == cc[i])
                    cc[k] = cc[j];
        }
        wt+=w;
    }

    return wt;
}

int find_root(int i,std::vector<int>& parent){
    if(parent[i] == -1)
        return i;

    int r = find_root(parent[i],parent);
    parent[i] = r;
    return r;
}

void dsu_union(int ri,int rj,std::vector<int>& parent,std::vector<int>& rang){
    if(rang[ri] < rang[rj]){
        parent[ri] = rj;
        rang[rj] += rang[ri];
    }
    else {
        parent[rj] = ri;
        rang[ri] += rang[rj];
    }
}

int kruskal2(std::vector<std::vector<int>>& g){
     std::vector<int> parent(g.size(),-1);
     std::vector<int> rang(g.size(),1);

     std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

     for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;
    while(!pq.empty()){
        auto[i,j,w] = pq.top();

        int ri = find_root(i,parent);
        int rj = find_root(j,parent);
        if(ri != rj){
            wt+=w;
            dsu_union(ri,rj,parent,rang);
        }
    }

    return wt;

}

typedef struct my_cmp2{
    bool operator() (std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
}my_cmp2;

void dijkstra(std::vector<std::vector<int>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<int> distanca(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>,my_cmp2> pq;

    pq.push(std::make_pair(start,0));
    distanca[start] = 0;
    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distanca[j] > distanca[i] + g[i][j]){
                    distanca[j] = distanca[i] + g[i][j];
                    pq.push(std::make_pair(j,distanca[j]));
                }
            }
        }
        posjecen[i] = 1;
    }
}

bool podniz1(int* arr,int len,int s){
    if(s == 0)
        return true;
    if(len == 0)
        return false;

    int with =  podniz1(arr,len-1,s-arr[len-1]);
    if(with)
        return true;
    int without = podniz1(arr,len-1,s);
    return without;
}

const int MAX = 100;
int sol[MAX];
int cnt = 0;

int podniz2(int* arr,int len,int s){
    if(s == 0){
        for(int i = 0;i < cnt;i++)
            std::cout<<sol[i] << " ";
        std::cout<<std::endl;

        return 1;
    }
    if(len == 0)
        return INT_MAX;

    sol[cnt++] = arr[len-1];
    int with = podniz2(arr,len-1,s-arr[len-1]);
    cnt--;
    int without = podniz2(arr,len-1,s);
    return with + without;
}

int best_sol[MAX];
int best_cnt = INT_MAX;

int podniz3(int* arr,int len,int s){
    if(s == 0){
        if(best_cnt > cnt){
            best_cnt = cnt;
            for(int i = 0; i < cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;
    }
    if(len == 0)
        return INT_MAX;

    sol[cnt++] = arr[len-1];
    int with = podniz3(arr,len-1,s-arr[len-1]);
    if(with < INT_MAX)
        with++;
    cnt--;
    int without = podniz3(arr,len-1,s-arr[len-1]);
    return with < without ? with : without;
}

const int len_mat = 1000;
int dp[len_mat][len_mat];

int podniz3_din_memo(int* arr,int len,int s){
    if(s == 0)
        return 0;
    if(len == 0)
        return INT_MAX;

    if(dp[len][s] != -1)
        return dp[len][s];

    int with = podniz3_din_memo(arr,len-1,s-arr[len-1]);
    if(with < INT_MAX)
        with++;
    int without = podniz1_din_memo(arr,len-1,s);

    dp[len][s] = with < without ? with : without;
    return dp[len][s];

}

int podniz3_din_tab(int* arr,int len,int s){
    int dp[len+1][s+1];

    for(int i = 0;i <= len;i+)
        dp[i][0] = 0;

    for(int i = 1;i <= s;i++)
        dp[0][i]=INT_MAX;

    for(int i = 1;i <= len;i++){
        for(int j = 1;j <= s;j++){
            int with = INT_MAX;
            if(arr[i-1] <= j){
                with = dp[i-1][j-arr[i-1]];

                if(with < INT_MAX)
                    with++;
            }
            int without = dp[i-1][j];
            dp[i][j] = with < without ? with : without;
        }
    }

    return dp[len][s]
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
