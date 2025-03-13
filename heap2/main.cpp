#include <iostream>
#include <queue>

/// unosi se n stringova
/// odstampati u opadajucem redu stringove
/// po broju velikih slova
int izbrojVelikaSlova(std::string& str){
    int cnt = 0;
    for(int i = 0; i < str.length();i++)
        if(str[i] >= 'A' && str[i] <= 'Z')
            cnt++;
    return cnt;
}

typedef struct mojString{
    std::string txt;
    int brojVelikihSlova;
}mojString;


struct stringComparator{
    bool operator()(const mojString& a, const mojString& b) const{
        return a.brojVelikihSlova < b.brojVelikihSlova;
    }
};

void stringovi(){
    int n;
    std::cin >> n;
    ///priority queue se inicijalizuje tipom elementa koji sadrzi,
    ///vectorom tog tipa elemenata i definisanim komparatorom za element
    std::priority_queue<mojString,std::vector<mojString>,stringComparator> pq;


    ///ucitavamo stringove, kreiramo mojString uz broj velikih slova
    /// guramo elemente u red
    for(int i = 0; i < n; ++i){
        std::string str;
        std::cin >> str;
        mojString temp = {str,izbrojVelikaSlova(str)};
        pq.push(temp);
    }

    /// dok nije prazan stampamo elemente
    while(!pq.empty()){
        std::cout<<pq.top().txt<<std::endl;
        pq.pop();
    }
}

void medijan(){
    std::string unos;
    std::cin >> unos;

    std::priority_queue<int> maxHeap;///Cuva manju polovinu brojeva, a najveci je na vrhu!!!
    std::priority_queue<int,std::vector<int>,std::greater<int>> minHeap;/// Cuva vecu polovinu brojeva a najmanji je na vrhu!!!

    while(unos != "Q"){///Q predstavlja kraj unosa stringova
        if(unos == "M"){///M - trazimo medijan
            if(maxHeap.size() == minHeap.size()){
                /// ako je velicina maxHeap-a jednaka velicini minHeap-a
                /// racunamo prosjek to dvoje
                    std::cout<<(maxHeap.top()+minHeap.top())/2<<std::endl;
            }
            else std::cout<<maxHeap.top()<<std::endl; /// ako ne gledamo vrh maxHeap-a
        }

        else{///dodajemo novi clan na heap
            int br = stoi(unos);
            maxHeap.push(br);

            /// ako je velicina maxHeap-a veca za 2 i vise
            /// tada vrh maxHeap-a guramo na minHeap
            if(maxHeap.size() > minHeap.size() + 1){
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
            else if(!minHeap.empty() && maxHeap.top() > minHeap.top()){

                ///elementi u maxHeap-u moraju biti manji od elemenata iz minHeap-a

                maxHeap.push(minHeap.top());
                minHeap.push(maxHeap.top());
                minHeap.pop();
                maxHeap.pop();
            }
        }
        std::cin>>unos;

    }

}

int main()
{

    //stringovi();
    medijan();
    return 0;
}
