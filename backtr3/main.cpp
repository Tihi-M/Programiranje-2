#include <iostream>


const int MAX = 100;
int sol[MAX];
int cnt = 0;

int zad3(int n,int k,int s){
    if(n == 0 && s == 0){
        for(int i = 0; i < cnt;i++)
            std::cout<<sol[i]<<" ";
        std::cout<<std::endl;
        return 1;
    }
    if(n == 0)
        return 0;
    if(s == 0)
        return 0;
    int br_komb = 0;
    for(int i = 1;i <= k;i++){
        sol[cnt++] = i;
        int with = zad3(n-1,k,s-i);/// provjeravamo svaku stranu
        cnt--;
        int without = zad3(n-1,k,s);
        br_komb += with;
        br_komb += without;
    }

    return br_komb;
}

int main()
{

    int n,k,s;
    std::cin>> n >> k >> s;
    std::cout<<zad3(n,k,s);
    return 0;
}
