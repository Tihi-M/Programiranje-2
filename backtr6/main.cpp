#include <iostream>

const int MAX = 100;
int sol[MAX];
int cnt = 0;
int best_sol[MAX];
int best_cnt = INT_MAX;

int zad6(int len,int* arr,int s){
    if(s == 0){
        if(cnt < best_cnt){
            best_cnt = cnt;
            for(int i = 0; i < cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;
    }
    if(s < 0)
        return INT_MAX;
    if(len == 0)
        return INT_MAX;

    sol[cnt++] = arr[len-1];
    int with = zad6(len,arr,s-arr[len-1]);/// koristimo istu novcanicu i dalje zato nije len-1
    if(with < INT_MAX)
        with++;
    cnt--;
    int without = zad6(len-1,arr,s);

    return with < without ? with : without;
}

int main()
{
    int s,len;
    std::cin>> s>>len;
    int arr[len];
    for(int i = 0;i < len;i++)
        std::cin>>arr[i];

    std::cout<<zad6(len,arr,s);
    return 0;
}
