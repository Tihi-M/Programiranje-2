#include <iostream>

int stepenice(int n){
    if(n == 0)
        return 1;
    if(n == 1)
        return 1;
    return stepenice(n-1) + stepenice(n-2);
}

const int MAX = 100;

int sol1[MAX];
int cnt = 0;

int stepenice_din(int n){
    if(n == 0)
        return 1;
    if(n == 1)
        return 1;
    if(sol1[n] != 0)
        return sol1[n];

    sol1[n] = stepenice_din(n-1)+stepenice_din(n-2);
    return sol1[n];

}

int sol2[MAX];
int cnt2 = 0;
int best_sol2[MAX];
int best_cnt2 = INT_MAX;

int jedinice(int n,int k){
    if(n == 0){
        if(best_cnt2 > cnt2){
            best_cnt2 = cnt2;
            for(int i = 0;i < cnt2;i++)
                best_sol2[i] = sol2[i];
        }
        return 0;
    }
    if(k > n || n < 0)
        return INT_MAX;
    sol2[cnt2++] = k;
    int with = jedinice(n-k,k+10);
    cnt2--;
    int without = jedinice(n,k+10);
    return with < without ? with : without;
}


int sol3[MAX];
int cnt3=0;
int kockice(int n,int k,int s){
    if(s == 0 && n ==0){
        for(int i = 0;i < cnt3;i++)
            std::cout<<sol3[i]<< " ";
        std::cout<<std::endl;
        return 1;
    }
    if(n == 0)
        return 0;
    if(s == 0)
        return 0;
    int br_komb=0;
    for(int i = 1; i <= k;i++){
        sol3[cnt3++] = i;
        int with = kockice(n-1,k,s-i);
        cnt3--;
        int without = kockice(n-1,k,s);
        br_komb +=with+without;

    }

    return br_komb;
}

int sol5[MAX];
int cnt5=0;
int best_sol5[MAX];
int best_cnt5 = INT_MAX;

int novcanice(int n,int s,int* arr){
    if(s == 0){
        if(best_cnt5 > cnt5){
            best_cnt5 = cnt5;
            for(int i = 0;i < cnt5;i++)
                best_sol5[i] = sol5[i];
        }
        return 0;
    }
    if(n == 0)
        return INT_MAX;
    if(s < 0)
        return INT_MAX;
    sol5[cnt5++] = arr[n-1];
    int with = novcanice(n-1,s-arr[n-1],arr);
    if(with < INT_MAX)
        with++;
    cnt5--;
    int without = novcanice(n-1,s,arr);
    return with < without ? with : without;
}


int cnt6 = 0;
int sol6[MAX];
int best_cnt6 = INT_MAX;
int best_sol6[MAX];

int bankomati(int n,int* arr,int s){
    if(s == 0){
        if(best_cnt6 > cnt6){
            best_cnt6 = cnt6;
            for(int i = 0;i < cnt6;i++)
                best_sol6[i] = sol6[i];
        }
        return 0;
    }
    if(n == 0)
        return INT_MAX;
    if(s < 0)
        return INT_MAX;

    sol6[cnt6++] = arr[n-1];
    int with = bankomati(n,arr,s-arr[n-1]);
    if(with < INT_MAX)
        with++;
    cnt6--;
    int without = bankomati(n-1,arr,s);
    return with < without ? with : without;
}


int main()
{
    int n,k;
    std::cin>>k >> n;
    /*
    jedinice(n,k);
    if(best_cnt2 != INT_MAX){
       for(int i = 0;i < best_cnt2;i++)
        std::cout<<best_sol2[i]<< " ";
    }
    else std::cout<< -1 <<std::endl;
    std::cin>> n >> k;
    int arr[n];
    for(int i =0;i < n;i++)
        std::cin>>arr[i];
    int res = novcanice(n,k,arr);
    std::cout << res << std::endl;
    if(res != INT_MAX){
        std::cout<<res<<std::endl;
        for(int i =0; i< best_cnt5;i++)
            std::cout<<best_sol5[i]<< " ";

    }
    else std::cout<<-1;
    */
    int arr[n];
    for(int i = 0;i < n;i++)
        std::cin>>arr[i];

    std::cout<<bankomati(n,arr,k);

   return 0;
}

