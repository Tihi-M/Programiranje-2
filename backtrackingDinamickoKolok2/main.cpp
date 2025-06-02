#include <iostream>
#include <climits>
#include <cstring>

bool podniz1(int* arr,int len,int s){
    if(s == 0)
        return true;
    if(len == 0)
        return false;

    bool with = podniz1(arr,len-1,s-arr[len-1]);
    if(with)
        return true;
    bool without = podniz1(arr,len-1,s);
    return without;
}

const int MAX = 1000;

int sol[MAX];
int cnt = 0;

int podniz2(int* arr,int len,int s){
    if(s == 0){
        for(int i = 0;i < cnt;i++)
            std::cout<<sol[i]<< " ";
        std::cout<<std::endl;

        return 1;
    }

    if(len == 0)
        return 0;

    sol[cnt++] = arr[len-1];
    int with = podniz2(arr,len-1,s-arr[len-1]);
    cnt--;
    int without = podniz2(arr,len-1,s);

    return with+without;
}

int best_sol[MAX];
int best_cnt = INT_MAX;

int podniz3(int* arr,int len,int s){
    if( s == 0)
    {
        if(best_cnt > cnt)
        {
            best_cnt = cnt;
            for(int i = 0;i < cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;
    }

    if(len == 0)
        return INT_MAX;

    int with = podniz3(arr,len-1,s-arr[len-1]);

    if(with < INT_MAX)
        with+=1;

    cnt--;
    int without = podniz3(arr,len-1,s);

    return with < without ? with : without;
}

int podniz3_din_tab(int* arr,int len,int s){
    int dp[len+1][s+1];

    for(int i = 0; i <= len;++i)
        dp[i][0] = 0;

    for(int j = 0;j <= s;++j)
        dp[0][j] = INT_MAX;

    for(int i = 1;i <= len;++i){
        for(int j = 1;j <= s;++j){
            int with = INT_MAX;
            if(arr[i-1] <= j){
                with = dp[i-1][j-arr[i-1]];
                if(with < INT_MAX)
                    ++with;
            }
            int without = dp[i-1][j];
            dp[i][j] = with < without ? with : without;

        }
    }
    return dp[len][s];
}


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
