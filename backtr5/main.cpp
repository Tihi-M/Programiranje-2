#include <iostream>


const int MAX = 100;
int sol[MAX];
int cnt = 0;
int best_cnt = INT_MAX;
int best_sol[MAX];

int zad5(int len,int* arr,int s){
    if(s == 0){
        if(best_cnt > cnt){
            best_cnt = cnt;
            for(int i = 0;i < cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;
    }
    if(len == 0)
        return INT_MAX;
    sol[cnt++] = arr[len-1];
    int with = zad5(len-1,arr,s-arr[len-1]);
    if(with < INT_MAX)
        with++;
    cnt--;
    int without = zad5(len-1,arr,s);
    return with < without ? with : without;

}

int main()
{
    int len,s;
    std::cin>>len>>s;
    int arr[len];
    for(int i = 0; i<len;i++)
        std::cin>>arr[i];
    int res = zad5(len,arr,s);

    if(res != INT_MAX){
        std::cout<<res<<std::endl;
        for(int i = 0;i < best_cnt;i++)
            std::cout<<best_sol[i]<<" ";
    }
    else std::cout<<-1;
    return 0;
}
