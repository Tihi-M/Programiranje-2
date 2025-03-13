#include <iostream>
#include <queue>

typedef int heapElement;

typedef struct Heap{
    heapElement* data; ///Niz koji sadrzi elemente heap-a
    int capacity;///Kapacitet heap-a
    int counter;///Broj trenutnih elmenata
    bool (*compare)(heapElement&, heapElement&);///Pokazivac na funkciju koja poredi dva elementa
}Heap;

///pri inicijalizaciji prosljedjujemo pokazivac na
/// jednu od ove dvije funkcije koje ce odrediti
/// da li kreiramo max ili min heap

bool compareMax(heapElement& a, heapElement& b){
    return a > b;
}

bool compareMin(heapElement& a, heapElement& b){
    return a < b;
}


/// inicijalizacija novog heap-a
void init(Heap& hp, int cap,bool (*compare)(heapElement&, heapElement&)){
    hp.data = new heapElement[cap];
    hp.capacity = cap;
    hp.counter = 0;
    hp.compare = compare;
}

void destroy(Heap& hp){
    delete[] hp.data;
    hp.capacity = 0;
    hp.counter = 0;
    hp.compare = nullptr;
}

/// heap je prazan ako je cnt == 0;
bool isEmpty(Heap& h){
    return h.counter == 0;
}

/// heap je pun ako je cap == cnt
bool isFull(Heap& h){
    return h.capacity == h.counter;
}


void insertHeapElement(Heap& h, heapElement x){
    if(isFull(h)){
        std::cout<<"Heap je pun"<<std::endl;
        return;
    }

    h.data[h.counter] = x;///Novi element postavljamo na kraj niza;
    int pos = h.counter;
    h.counter+=1;///broj elemenata se povecao za 1

    while(pos > 0){
        int parentPos = (pos - 1)/2;///formula za dobijanje roditeljske pozicije
                                    ///na osnovu trenutne
        if(!h.compare(h.data[parentPos],h.data[pos])){
            std::swap(h.data[parentPos],h.data[pos]);
            ///ako smo predali compareMax radimo sa max heap-om
            /// tada ako je parent element manji od child elementa
            /// oni tada zamjenjuju pozicije
        }
        else{/// ako parent el nije manji tada je heap u redu i ne provjeravamo dalje
            break;
        }
        /// doslo je do zamjene mjesta i sada se umetnuti element nalazi na poziciji
        /// na kojoj je bio parent
        pos = parentPos;
    }
}

heapElement removeHeapElement(Heap& h){
    if(isEmpty(h)){
        std::cout<<"Heap je prazan"<<std::endl;
        exit(1);
    }

    heapElement top = h.data[0];///cuvamo prvi element
    h.data[0] = h.data[h.counter-1];///na njegovo mjesto dolazi posljednji
    h.counter-=1;///smanjujemo broj elemenata za jedan

    int pos = 0;///pocetni element cemo rotirati
                /// dok ne dodje do svog mjesta

    while(2*pos+1 < h.counter){
        int leftSonPos = 2*pos+1;
        int rightSonPos = 2*pos+2;

        int cmpSonPos = leftSonPos;

        if(rightSonPos < h.counter && h.compare(h.data[rightSonPos], h.data[leftSonPos])){
            ///provjeravamo da li ima desnog sina?
            ///i da li je veci od lijevog
            cmpSonPos = rightSonPos;
        }
        ///ako trenutni nije veci od svog sina u max heap-u
        /// mijenjaju mjesta
        if(!h.compare(h.data[pos], h.data[cmpSonPos])){
            std::swap(h.data[pos], h.data[cmpSonPos]);
        }
        else{///heap je u redu kraj petlje
            break;
        }
        ///doslo je do zamjene mjesta i sada je trenutni presao
        /// na mjesto svog sina
        pos = cmpSonPos;
    }

    return top;
}

heapElement top(Heap& h){
    if(isEmpty(h)){
        std::cout<<"Heap je prazan"<<std::endl;
        exit(2);
    }

    heapElement top = h.data[0];
    return top;
}

///mozemo definisati nas komparator
///koji poredi dva elementa po nasem
///kriterijumu
struct myComparator{
    bool operator()(int a, int b){
        return a%10 > b%10;
    }
};

typedef struct Student{
    std::string ime;
    int brInd;
    float prosjek;
    ///mozemo predefinisati operatore
    /// poredjenja za strukture koje pravimo
    bool operator < (const Student& other) const{
        return prosjek < other.prosjek;
    }
}Student;

struct studentComparator{
    bool operator()(Student& a, Student& b){
        return a.prosjek> b.prosjek;
    }
};

int main()
{

    /*
    Heap h;
    init(h, 5, compareMax);
    insertHeapElement(h, 10);
    insertHeapElement(h, 7);
    insertHeapElement(h, 19);
    insertHeapElement(h, 23);
    insertHeapElement(h, 14);

    std::cout << isFull(h) << std::endl;

    std::cout << removeHeapElement(h) << std::endl;

    std::cout << top(h) << std::endl;

    std::cout << removeHeapElement(h) << std::endl;
    std::cout << removeHeapElement(h) << std::endl;
    std::cout << removeHeapElement(h) << std::endl;
    std::cout << removeHeapElement(h) << std::endl;

    std::cout << isEmpty(h) << std::endl;


    destroy(h);
    */
    ///prioritetni red iz queue biblioteke
    /*
    std::priority_queue<int, std::vector<int>, myComparator> pq1;
    pq1.push(12);
    pq1.push(23);
    pq1.push(621);
    pq1.push(246);
    pq1.push(325);

    std::cout<<pq1.top()<<std::endl;
    pq1.pop();
    std::cout<<pq1.top()<<std::endl;
    pq1.pop();
    */
    /*
    Student s1 = {"Marko", 5, 7.9};
    Student s2 = {"Milica", 3, 9.4};
    Student s3 = {"Marija", 7, 8.5};

    std::priority_queue<Student, std::vector<Student>, studentComparator> pq2;
    //priority_queue<Student> pq2;

    pq2.push(s1);
    pq2.push(s2);
    pq2.push(s3);

    std::cout << pq2.top().ime << " " << pq2.top().brInd << " " << pq2.top().prosjek << std::endl;
    pq2.pop();
    std::cout << pq2.top().ime << " " << pq2.top().brInd << " " << pq2.top().prosjek << std::endl;
    pq2.pop();
    std::cout << pq2.top().ime << " " << pq2.top().brInd << " " << pq2.top().prosjek << std::endl;
    pq2.pop();
    */
    return 0;
}
