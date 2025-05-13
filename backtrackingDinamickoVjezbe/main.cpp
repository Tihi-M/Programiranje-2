#include <iostream>
#include <climits>
#include <cstring>
/**
    Dat je niz prirodnih brojeva a i broj s.
    Da li postoji podskup a cija je suma jednaka s.
*/

/// samo vrace da li rjesenje postoji

bool podniz1(int* arr,int len,int s){
    if(s == 0) /// dosli smo do s
        return true;
    if(len == 0) /// prosli smo niz, nismo dosli do s
        return false;

    bool with = podniz1(arr,len-1,s-arr[len-1]);/// promjenjiva koja uzima trenutni element,oduzima ga od s

    if (with)///ako je s = 0, vracamo true
        return true;

    /// posto nije to znaci da rjesenje ne sadrzi trenutni el
    /// vracamo rezultat bez trenutnog elementa
    bool without = podniz1(arr,len-1,s);
    return without;
}

const int MAX = 1000;

int sol[MAX];///solution
int cnt = 0;

/// za stampanje rjesenja i broj rjesenja

int podniz2(int* arr,int len,int s){
    if(s == 0){ /// dosli smo do rjesenja
        for(int i = 0;i < cnt;++i)
            std::cout<<sol[i]<< " "; /// stampamo rjesenje
        std::cout<<"\n";
        return 1; /// vracamo 1 jer je pronadjeno rjesenje
    }

    if(len == 0) /// prosli smo kroz niz
        return 0; /// vracamo 0, nije nadjeno rjesenje
    sol[cnt++] = arr[len-1]; /// cuvamo poziciju za trenutni element
    int with = podniz2(arr,len-1,s-arr[len-1]); /// trazimo broj rjesenja sa trenutnim elementom
    cnt--;
    int without = podniz2(arr,len-1,s);/// trazimo broj rjesenja bez trenutnog elementa

    return with+without;/// vracemo broj rjesenja
}


int best_sol[MAX]; /// cuva samo najbolje rjesenje, sa najmanje elemenata
int best_cnt=INT_MAX;

/// trazi rjesenje sa najmanjim brojem elemenata

int podniz3(int* arr,int len,int s){
    if(s == 0){ ///pronadjeno je rjesenje
        if(cnt < best_cnt){ /// ako je pronadjeno krace od najboljeg
            best_cnt = cnt; /// cuvamo ga
            for(int i = 0;i< cnt;i++)
                best_sol[i] = sol[i];
        }
        return 0;/// pronadjeno je rjesenje - ne treba nam vise elemenata, zato 0
    }

    if(len == 0) /// nije pronadjeno rjesenje
        return INT_MAX; /// vracamo max

    sol[cnt++] = arr[len-1]; /// pamtimo trenutni put do rjesenja, ali ne odmah u bestSol

    int with = podniz3(arr,len-1,s-arr[len-1]); /// opcija sa trenutnim elmentom

    if(with < INT_MAX)
        with+=1;/// pronadjeno je, povecavamo duzinu rjesenja sa trenutnim elementom

    --cnt;
    int without = podniz3(arr,len-1,s); /// opcija bez trenutnog

    return with < without ? with : without; /// vracemo kracu opciju
}


/**
    Dynamic programming (bolja verzija backtracking-a)
    Tehnike dinamickog prog:
        1. memoizacija
        2. tabulacija
*/

const int lenMat = 1000;
int dp[lenMat][lenMat];///cuva min broj el koji su potrebni
                    /// da se dostigne suma j koristeci i elmenata


/// ponovo trazimo minimalan broj elemenata koji daje sumu s


int podniz_3_din_memo(int arr[],int len,int s){
    if(s == 0) /// pronadjena je suma
        return 0;/// ne treba nam vise el

    if(len == 0) /// prosli smo kroz niz
        return INT_MAX;///nema rjesenja

    if(dp[len][s]!=-1)/// ako smo vec nasli sumu
        return dp[len][s];/// vracamo je


    /// opcija gdje koristimo trenutni element za rjesenje
    int with = podniz_3_din_memo(arr,len-1,s-arr[len-1]);

    if(with < INT_MAX)
        with++; /// duzina with + trenutni

    /// opcija gdje ne koristimo trenutni element za rjesenje
    int without = podniz_3_din_memo(arr,len-1,s);


    /// cuvamo najbolje rjesenje za trenutnu duzinu
    dp[len][s] = with < without ? with : without;
    return dp[len][s]; /// koordinate rjesenja

}



int podniz3_din_tab(int* arr,int len,int s){
    int dp[len+1][s+1];
    ///dp[i][j] - minimalni broj elemenata potrebnih da se
    ///             dobije suma j, od prvih i elemenata niza
    for(int i = 0;i <= n;++i)
        dp[i][0] = 0;/// nula elemenata je potrebno da se napravi suma = 0

    for(int j = 1;j <= s;++j)
        dp[0][j] = INT_MAX; /// suma bez elemenata?

    for(int i = 1;i <= n;++i){ /// prolazimo kroz niz
        for(int j = 1;j <= s;++j){/// prolazimo kroz sve sume od 1 do s
            int with = INT_MAX; /// pocetna duzina- zato je temp intMax
            if(arr[i-1] <= j){ /// dp ide za jedan napred u indeksima,
                                /// zato je indeks trenutnog u nizu za 1 manji
                                /// trenutni clan ne smije biti veci od sume j
                with = dp[i-1][j-arr[i-1]; /// od j sume uklanjamo arr[i-1] element
                                        /// sada je with broj elemenata potreban za tu sumu
                if(with < INT_MAX)
                    ++with;
            }
            int without = dp[i-1][j]; /// opcija bez arr[i-1] elementa
            dp[i][j] = with<without ? with : without; /// cuvamo odgovarajuci rezultata
        }
    }

    return dp[len][s];
}

/// broj koraka potrebnih da se dobije
/// jedan string iz drugog zamjenom karaktera
/// dodavanjem, brisanjem


int levenshtein_distance(const std::string& a,const std::string& b,int m,int n){
    if(m == 0 && n == 0)
        return 0;

    if(n == 0)
        return m;
    if(m == 0)
        return n;
    if(a[m-1] == b[n-1])
        return levenshtein_distance(a,b,m-1,n-1);

    int zamjena = 1 + levenshtein_distance(a,b,m-1,n-1);
    int brisanje = 1 + levenshtein_distance(a,b,m-1,n);
    int umetanje = 1 + levenshtein_distance(a,b,m-1,n);

    return std::min(zamjena,std::min(brisanje,umetanje));

}

int levenshtein_distance_tab(const std::string& a,const std::string& b){
    int m = a.size();
    int n = b.size();

    int dp[m+1][n+1]; /// dp[i][j]-minimalan broj operacija
                    /// potrebnih da se i char iz a
                    /// pretvori u j char iz b

    int operacije[m+1][n+1]; /// dp[i][j] - cuva tip operacije


    /// za obije petlje vazi
    /// ako je duzina jednog od stringova = 0
    /// tada je potrebno onoliko operacija kolika je duzina
    /// drugog stringa

    for(int i = 0;i <= m;i++){
        dp[i][0] = i;
        operacije[i][0]= 1;///brisanje do praznog drugog
    }

    for(int j = 0;i <= n;j++){
        dp[0][j] = j;
        operacije[0][j]= 2;///umetanje do punog prvog
    }

    operacije[0][0] = -1;

    for(int i = 1;i <= m;++i){
        for(int j = 1;j <= n;j++){
            if(a[i-1] == b[j-1]){ /// ako su karakteri jednaki
                                    /// operacija nije potrebna
                dp[i][j] = dp[i-1][j-1]; /// broj koraka je isti jer nije bilo op
                operacije[i][j] = 0;
            }
            else{///ako su razliciti karakteri
                ///isprobavamo sve komb
                int zamjena = 1 + dp[i-1][j-1];
                int brisanje = 1 + dp[i-1][j];
                int umetanje = 1 + dp[i][j-1];


                ///cuvamo samo najbolju opciju
                dp[i][j] = std::min(zamjena,std::min(brisanje,umetanje));

                if(dp[i][j] == zamjena)
                    operacije[i][j] = 3;
                else if(dp[i][j] == brisanje)
                    operacije[i][j] = 1;
                else operacije[i][j] = 2;
            }
        }
    }

    int i = m,j = n;
    while(i > 0 || j > 0){
        if(operacije[i][j] == 0){
            --i;
            --j;
        }
        else if(operacije[i][j] == 1){
            std::cout<<"Brisanje -> "<< a[i-1] << "\n";
            --i;
        }
        else if(operacije[i][j] == 2){
            std::cout<<"Umetanje -> "<< a[j-1] << "\n";
            --j;
        }
        else{
            std::cout<<"Zamjena -> "<< a[i-1] << "\n";
            --i;
            --j;
        }
    }

    return dp[m][n];

}

/**
    n novicica, dva igraca i svaki uzima 1,k,l novcica.
    (k i l se zadaju posebno)
    Pobjednik je onaj koji uzme posljednji novcic


*/

int igraNovcica(int n,k,int l,int igrac){
    if(n == 0) /// uzeti su svi novcici
        return 1-igrac; /// pobjednik je prethodni igrac

    int potez1 = igraNovcica(n-1,k,l,1-igrac); /// igrac uzima jedan novcic

    int potez2 = 1-igrac;
    if(k <= n) /// uzima se k novica kao ih ima dovoljno
        potez2 = igraNovcica(n-k,k,l,1-igrac);

    int potez3 = 1-igrac;/// uzima se l novcica ako ih ima dovoljno
    if(l <= n)
        potez3 = igraNovcica(n-l,k,l,1-igrac);

    if(potez1 == igrac || potez2 == igrac || potez3 == igrac)
        return igrac;
    return 1-igrac;
}

int igraNovcicaDin(int n,int k,int l){
    int dp[n+1][2];
    dp[0][0] = 1;
    dp[0][1] = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= 1;j++){
            int potez1 = dp[i-1][1-j];
            int potez2 = 1-i;
            int potez3 = 1-j;

            if(k <= i)
                potez2 = dp[i-k][1-j];
            if(l <= i)
                potez3 = dp[i-l][1-j];

            if(potez==j || potez2 == j || potez3 == j)
                dp[i][j] = j;
            else
                dp[i][j] = 1-j;
        }
    }
    return dp[n][0];
}

int knapsack_unb(int* v,int* z,int n,int q){
    if(q == 0)
        return 0;

    int best = 0;

    for(int i =0;i < n;i++){
        int val = 0;
        if(z[i] <= q)
            val = knapsack_unb(v,z,n,q-z[i])+v[i];
        if(val > best)
            best = val;
    }
    return best;
}

int knapsack01(int* v,int* z,int n,int q){
    if(q == 0)
        return 0;
    if(n == 0)
        return 0;

    int with = 0;
    if(z[n-1] <= q)
        with = knapsack01(v,z,n-1,q-z[n-1]+v[n-1]);

    int without = knapsack01(v,z,n-1,q);

    return  with > without ? with:without;
}

int knapsack_unb_din(int* v,int* z,int n,int q){

    int dp[q+1];
    int predmeti[q+1];

    dp[0]=0;
    predemti[0] = -1;

    for(int i =1;i <= q;i++){
        dp[i] = 0;
        for(int j = 0;j< n;j++){
            if(z[j] <= i){
                if(dp[i] < dp[i-z[j]]+v[j])
                {
                    dp[i] = dp[i-z[j]]+v[j];
                    predmeti[i]=j;
                }
            }
        }
    }
    int i = q;
    while(predmeti[i] != -1){
        std::cout<<predmeti[i] << " ";
        i = i - z[predmeti[i]];
    }

    return dp[q];
}

int knapsack01_din(int* v,int* z,int n,int q){
    int dp[q+1][n+1]

    for(int i =0;i <= q;i++)
        dp[i][0] = 0;

    for(int j = 0;j <= n;++j)
        dp[0][j] = 0;

    for(int i = 1; i <= q;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            dp[i][j]=dp[i][j-1];

            if(z[j-1] <= i)
                dp[i][j] = std::max(dp[i-z[j-1]][j-1]+v[j-1],dp[i][j]);
        }

    }
    return dp[q][n];
}

int igraPogadjanja(int a,int b){
    if (a == b)
        return 0;
    int v = a + igraPogadjanja(a+1,b);
    v = std::min(v,b+igraPogadjanja(a,b-1));

    for(int i = a+1;i <= b-1;i++)
        v = std::min(v,i+std::max(igraPogadjanja(a,i-1),igraPogadjanja(i+1,b)));

    return v;
}

int main()
{

    int arr[] = {2, 3, 5, 6, 8};
    int len = 5;
    int s = 10;


/*
    podniz3(arr,len,s);
    if(best_cnt != INT_MAX){
        std::cout<<"Duzina najkraceg podniza: "<<best_cnt<<"\n";
        std::cout<<"Podniz:";
        for(int i = 0;i < best_cnt;++i)
            std::cout<<best_sol[i] << " ";
        std::cout<<"\n";
    }
    else{
        std::cout<<"Nije pronadjeno rjesenje"<<std::endl;
    }
*/
    for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j)
        dp[i][j] = -1;

    int result = podniz_3_din_memo(arr,len,s);
    if(result != INT_MAX){
        std::cout<<"Duzina najkraceg: "<< result<<"\n";

    }
    else{
        std::cout<<"Nema rjesenja\n";
    }
    return 0;
}
