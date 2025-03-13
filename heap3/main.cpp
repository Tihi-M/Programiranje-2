#include <iostream>
#include <queue>

/// zad1 - N kanapa, potrebno ih je povezati u jedan
/// cijena povezivajanja je suma njihovih duzina
/// trazi se minimalna cijena povezivanja N kanapa

/// pr 5: 4 3 2 6 7 suma = 0
/// 3 + 2 = 5- suma = 5, umece se u heap i nalazi se iza 4
/// 4 + 5 = 9- suma = 14, umece se u heap i nalazi se iza 7
/// 6 + 7 = 13 - suma = 27, umece se u heap i nalazi se iza 9
/// 9 + 13 = 22 - suma = 49, u ovom trenutku heap je prazan
/// res: 49
void kanapi(){
    int n;
    std::cin >> n;
    /// obican priority queue je maxHeap
    /// greater<int> ga cini minHeap-om
    std::priority_queue<int,std::vector<int>,std::greater<int>> pq;

    for(int i = 0; i < n;i++){
        int duzina;
        std::cin>>duzina;
        pq.push(duzina);
    }

    int suma = 0;
    while(true){
        int prvi = pq.top();
        pq.pop();
        int drugi = pq.top();
        pq.pop();

        /// uzimamo dva najkraca kanapa sa vrha
        /// i sabiramo ih

        int suma2 = prvi+drugi;
        suma += suma2; /// cijena se povecava za vrijednosti
                        /// duzina najkracih kanapa sa vrha
        std::cout<<suma<<std::endl;
        if(pq.empty()){/// ako je red prazan to znaci da smo nasli cijenu
            std::cout<<suma<<std::endl;
            break;
        }
        else pq.push(suma2);/// ako ne, izracunata duzina se gura u heap
    }
}



/// citava se k, matrica mxn
/// element matrice i,j je iznos novca na racunu klijenta j
/// trazi se k najbogatijih osoba(ukupan iznos novca klijenta je
/// suma iznosa na svim racunima, tj kolona i)

typedef struct Klijent{///struktura klijenta, sadrzi svoje j, iznos novca, komparator
    int id;
    float val;
    bool operator < (const Klijent& other) const{
    return val < other.val;
    }

}Klijent;

void klijenti(){
    int k;
    std::cin >> k;
    int m,n;
    std::cin >> m >> n;

    float mat[m][n];

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            std::cin>>mat[i][j];
            if(mat[i][j] != 0 && mat[i][j] != 1){
                std::cout<<"Input error"<<std::endl;
                exit(1);
            }
        }

    std::priority_queue<Klijent> pq;

    for(int j =0; j < n;j++){
        int iznos = 0;
        for(int i = 0;i < m;i++)
            iznos+=mat[i][j];

        Klijent temp = {j,iznos};
        pq.push(temp);
    }

    while(k > 0){
        if(!pq.empty()){
            Klijent temp = pq.top();
            std::cout<<temp.id<<std::endl;
            pq.pop();
            k--;
        }
        else return;
    }

}


/// zad3 - ucitava se broj k i matrica mxn, popunjena sa 0 i 1
/// 1 - vojnik, 0 - civil
/// Treba naci k najslabijih redova

typedef struct Red{///predstavlja red matrice
    int id;
    int val;
    bool operator > (const Red& other) const{
        return val > other.val;
    }
}Red;

void vojnici(){
    int k,m,n;
    std:: cin>> k >> m >> n;

    int mat[m][n];
    for(int i = 0; i < m;i++)
        for(int j = 0; j < n; j++)
            std::cin>>mat[i][j];

    std::priority_queue<Red,std::vector<Red>,std::greater<Red>> pq;

    for(int i = 0; i < m;i++){
        int cnt = 0;
        for(int j = 0; j < n;j++)
            if(mat[i][j] == 1)
            cnt++;
        Red temp = {i,cnt};
        pq.push(temp);
    }

    while(k > 0){
        if(!pq.empty()){
            Red temp = pq.top();
            pq.pop();
            std::cout<<temp.id<<std::endl;
            k--;
        }
        else return;
    }
}


/// zad4 - za dati skup ocjena racuna se najniza
/// koja ce se prikazati na sajtu
/// prikazuje se trecina najboljih ocjena
/// 2 9 3 1 6 4 5 7 - trecina je 8 div 3 = 2
/// najvece ocjene su 9 i 7 -> najmanja je 7

void ocjene1(){/// kada se unaprijed zna broj ocjena
    int n;
    std::cin >> n;
    int k = n / 3 - 1;
    std::priority_queue<int> pq;
    for(int i = 0; i < n;i++){
        int ocjena;
        std::cin>>ocjena;
        pq.push(ocjena);
    }

    while(k > 0){
        pq.pop();
        k-=1;

    }

    int najmanjaOcj = pq.top();
    std::cout<<najmanjaOcj;
}


/// zad5 - medijan

void medijan(){
    std::string unos;
    std::cin >> unos;

    std::priority_queue<int> maxHeap;/// za manju polovinu
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;///za vecu polovinu

    while(unos != "0"){
        if(unos == "M"){
            if(maxHeap.size() == minHeap.size()){
                std::cout<<(maxHeap.top() + minHeap.top())/2.0 << std::endl;
            }
            else std::cout<<maxHeap.top()<<std::endl;
        }
        else{
            int el = stoi(unos);
            maxHeap.push(el);
            if(maxHeap.size() > minHeap.size()+1){
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
            else if(!minHeap.empty() && maxHeap.top() > minHeap.top()){
                maxHeap.push(minHeap.top());
                minHeap.push(maxHeap.top());
                minHeap.pop();
                maxHeap.pop();
            }
        }
        std::cin>>unos;
    }
}

/// zad6 - unose se prirodni brojevi
/// Q - K-ti broj po velicini od unijetih br
/// K - na pocetku jedan, korisnik moze da ga promijeni
/// unosom K pa broja.

void zad6(){
    int k = 1;
    std::priority_queue<int> pq;
    std::priority_queue<int> temp;

    std::string unos;
    std::cin>>unos;
    while(unos != "0"){
        if(unos == "Q"){
            int i = k-1;
            while(i > 0){
                temp.push(pq.top());
                pq.pop();
                i--;
            }
            std::cout<<pq.top()<<std::endl;
            while(!temp.empty()){
                pq.push(temp.top());
                temp.pop();
            }
        }
        else if( unos == "K"){
            int novoK;
            std::cin>>novoK;
            k = novoK;
        }
        else{
            int el = stoi(unos);
            pq.push(el);
        }
        std::cin>>unos;
    }

}

int main()
{
    //kanapi();
    //klijenti();
    //vojnici();
    //ocjene();
    //medijan();
    //zad6();
    return 0;
}
