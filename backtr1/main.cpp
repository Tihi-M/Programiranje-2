#include <iostream>

int stepenice_back(int n){
    if(n == 0)
        return 1;/// popeli smo se

    if(n == 1)
        return 1;/// pravimo jos jedan korak
    return stepenice_back(n-1) + stepenice_back(n-2);
    /// broj nacina kad napravimo jedan korak + broj nacina kad napravimo dva koraka
}
const int MAX = 100;
int sol[MAX];
int cnt = 0;

int stepenice_din(int n){
    if(n == 0)
        return 1;
    if(n == 1)
        return 1;
    if(sol[n] != 0)
        return sol[n];
    sol[n] = stepenice_din(n-1)+stepenice_din(n-2);
    return sol[n];
}

int best_sol[MAX];
int best_cnt =INT_MAX;

int zad2(int n,int k){
    if(n == 0){/// nasli smo rjesenje
        if(best_cnt > cnt){
            best_cnt = cnt;
            for(int i = 0;i < cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;
    }
    if(n<0)///nije validno
        return INT_MAX;
    if(k > n)///nije validno
        return INT_MAX;

    sol[cnt++] = k;
    int with = zad2(n-k,k+10);
    cnt--;

    int without = zad2(n,k+10);
    return with < without ? with : without;
}


int main()
{

    int n,k;
    std::cin>>n>>k;
    zad2(n,k);
    if(best_cnt != INT_MAX){
        for(int i = 0;i < best_cnt;i++)
            std::cout<<best_sol[i]<<" ";
        std::cout<<std::endl;
    }
    else std::cout<< -1 << std::endl;
    return 0;
}
