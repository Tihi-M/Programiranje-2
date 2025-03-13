#include <iostream>
#include <queue>

typedef struct Node{
    int val;
    Node* left;
    Node* right;
}Node;

void dodaj(Node*& head,int val){
    Node* novi = new Node;
    novi->left = nullptr;
    novi->right = nullptr;
    novi->val = val;

    if(head == nullptr)
    {
        head = novi;
        return;
    }

    Node* prev = nullptr;
    Node* temp = head;

    while(temp!=nullptr){
        prev = temp;
        if(val < temp->val)
            temp = temp->left;
        else if (val < temp->right)
            temp = temp->right;
        else return;
    }

    if(val < prev->val)
        prev->left = novi;
        else prev->right = novi;
}

void dodajRec(Node*& head,int val){
    if(head == nullptr){
        Node* novi = new Node;
        novi->val = val;
        novi->right = nullptr;
        novi->left = nullptr;

        head = novi;
        return;
    }

    if(val < head->val)
        dodajRec(head->left,val);
    else if (val > head->val)
        dodajRec(head->right,val);
    else return;
}

void inOrder(Node& head){
    if(head == nullptr)
        return;

    inOrder(head->left);
    std::cout<< head->val << " ";
    inOrder(head->right);
}


void preOrder(Node& head){
    if(head == nullptr)
        return;

    std::cout<< head->val << " ";
    preOrder(head->left);
    preOrder(head->right);
}


void postOrder(Node& head){
    if(head == nullptr)
        return;

    postOrder(head->left);
    postOrder(head->right);
    std::cout<< head->val << " ";
}

bool postojiCvor(Node& head,int val){
    if(head == nullptr)
        return false;
    if(val < head->val)
        return postojiCvor(head->left,val);
    else if(val > head->val)
        return postojiCvor(head->right, val);
    else return true;
}

Node* minCvor(Node& head){
    if(head == nullptr)
        return nullptr;
    if(head->left == nullptr)
        return head;
    else return minCvor(head->left);
}

void brisiCvor(Node*& head,int val){
    if(head == nullptr)
        return;

    else if(val < head->val)
        brisiCvor(head->left , val);
    else if(val > head->val)
        brisiCvor(head->right , val);
    else{
        if(head->left == nullptr && head->right == nullptr){
            delete head;
            head=nullptr;
        }
        else if(head->left == nullptr){// ima samo jedno dijete
            Node* temp = head;
            head = head->right;//mijenjamo ga sa tim djetetom
            delete temp;
        }
        else if(head->right == nullptr){//         -||-
            Node* temp = head;
            head = head->left;
            delete  temp;
        }
        else{
            Node* sled = minCvor(head->right);
            head->val = sled->val;
            brisiCvor(head->right, sled->val);
        }
    }
}

int visinaStabla(Node& head){
    if(head == nullptr)
        return 0;
    if(visinaStabla(head->left) > visinaStabla(head->right))
        return visinaStabla(head->left) + 1;
    else return visinaStabla(head->right) + 1;
}

bool identicnaStabla(Node& head1, Node& head2){
    if(head1 == nullptr && head2 == nullptr)
        return true;
    if(head1->val != head2->val)
        return false;
    else return identicnaStabla(head1->left,head2->left) && identicnaStabla(head1->right,head2->right);
}

void stampajNivo(Node* head, int val){
    if(head == nullptr)
        return;
    if(val == 0)
        std::cout<<head->val << " ";
    stampajNivo(head->left,val-1);
    stampajNivo(head->right,val-1)
}

void stampaNivoe(Node* head){
    int visina = visinaStabla(head);

    for(int i = 0; i < visina;i++){
        stampajNivo(head,i);
        std::cout<<std::endl;
    }
}

void stampaNivoeBfs(Node* head){
    if(head == nullptr)
        return;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty())
    {
        Node* temp = red.front();

        std::cout<< temp->val<< " ";
        red.pop();

        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right != nullptr)
            red.push(temp->right);
    }
}

int brListova(Node* head){
    if(head==nullptr)
        return 0;
    if(head->left == nullptr && head->right == nullptr)
        return 1;
    else return brListova(head->left) + brListova(head->right);
}

int brListovaOpt(Node* head){
    if(head == nullptr)
        return 0;

    std::queue<int> red;
    red.push(head);
    int cnt = 0;
    while(!red.empty()){
        Node* temp = red.front();
        red.pop();

        if(temp->left == nullptr && temp->right == nullptr)
            cnt++;
        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right != nullptr)
            red.push(temp->right);
    }

    return cnt;
}

void inOrderQueue(Node* head,std::queue<int>& red){
    if(head == nullptr)
        return;
    inOrderQueue(head->left,red);
    red.push(head->val);
    inOrderQueue(head->right,red);
}

bool validnoStablo(Node* head){
    std::queue<int> red;
    inOrderQueue(head,red);

    if(red.empty())
        return true;

    int tren = red.front();
    red.pop();

    while(!red.empty()){
        if(tren > red.front())
        return false;

        tren = red.front();
        red.pop();
    }
    return true;
}

/// zad1 - br cvorova
int zad1(Node*& head){
    if(head == nullptr)
        return 0;
    return 1+zad1(head->left)+zad1(head->left);
}

/// zad2 - visina stabla
int zad2(Node*& head){
    if(head == nullptr)
        return 0;
    if(zad2(head->left) > zad2(head->right))
        return 1+zad2(head->left);
    else return 1+zad2(head->right);
}

/// zad3 - identicna stabla
int zad3(Node*& head1, Node*& head2){
    if(head1 == nullptr && head2 == nullptr)
    return true;
    if(head1->val != head2->val)
        return false;
    return zad3(head1->left,head2->left) && zad3(head1->right,head2->right);
}

/// zad4 - stampanje listova
void zad4(Node*& head){
    if(head == nullptr)
        return;
    if(head->left == nullptr && head->right == nullptr){
        std::cout<<head->val<< " ";
        return;
    }
    zad4(head->left);
    zad4(head->right);
}

void zad4Opt(Node*& head){
    if(head==nullptr)
        return;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        Node* temp = red.front();
        red.pop();

        if(temp->left == nullptr && temp->right == nullptr)
            std::cout<<temp->val << " ";
        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right !+ nullptr)
            red.push(temp->right);
    }
}

/// zad5 - stampanje lista na najmanjoj dubini

bool stampajList(Node*& head,int lvl){
    if(head == nullptr)
        return false;
    if(lvl == 0){
        std::cout<<head->val<<std::endl;
        return true;
    }
    return stampajList(head->left,lvl-1) || stampajList(head->right,lvl-1);
}

void zad5(Node*& head){
    int visina = zad2(head);

    for(int i =0; i < visina;i++)
        if(stampajList(head,i))
            break;
}

void zad5Opt(Node*& head){
    if(head==nullptr)
            return;

    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        Node* temp = red.front();

        if(temp->left == nullptr && temp->right == nullptr){
            std::cout<<temp->val<<std::endl;
            return;
        }
        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right != nullptr)
            red.push(temp->right);
    }
}

/// zad6 - stampanje cvorova na najvecoj dubini

void zad6(Node*& head){
    int lvl = zad2(head)-1;
    stampajNivo(head,lvl);
}

/// zad7 - stampanje cvorova koji imaju dva sina

void zad7(Node*& head){
    if(head == nullptr)
        return;

    if(head->left != nullptr && head->right != nullptr){
        std::cout<<head->val;
    }
    if(head->left != nullptr)
        zad7(head->left);
    if(head->right != nullptr)
        zad7(head->right);
}

/// zad8 - broj cvorova iste parnosti kao oba sina

bool imaObaSina(Node* head){
    return head->left!=nullptr && head->right != nullptr;
}

void zad8(Node*& head){
    if(head == nullptr)
        return 0;
    if(imaObaSina(head) &&
       head->val % 2 == head->left->val % 2 &&
       head->val % 2 == head->right->val %2)
        return 1+zad8(head->left)+zad8(head->right);
    else return zad8(head->left)+zad8(head->right);
}

//opt

/// zad9 - suma1 - suma svih cvorova > suma sinova

int zad9(Node*& head){
    if(head == nullptr)
        return 0;
    if(imaObaSina(head) && head->val > head->left->val + head->right->val)
        return 1+zad9(head->left)+zad9(head->right);
    else return zad9(head->left)+zad9(head->right);
}

/// zad10 - suma2 - suma parnih - suma neparnih na nivou n

int zad10(Node*& head,int lvl){
    if(head == nullptr)
        return 0;
    if(lvl == 0)
    {
        if(head->val % 2 == 0)
            return head->val;
        else return -1*head->val;
    }
    else return zad10(head->left,lvl-1) + zad10(head->right,lvl-1);
}

/// zad11 - provjerava da li je stablo simetricno

bool simetricnoStablo(Node* lijevo,Node* desno){
    if(lijevo == nullptr && desno == nullptr)
        return true;
    if(lijevo != nullptr && desno == nullptr)
        return false;
    if(lijevo == nullptr && desno != nullptr)
        return false;
    if(lijevo->val != desno->val)
        return false;
    return simetricnoStablo(lijevo->left,desno->right) && simetricnoStablo(lijevo->right,desno->left);
}

/// zad12 - provjerava da li je stablo izbalansirano

bool zad12(Node*& head){
    if(head == nullptr)
        return true;
    if(abs(visinaStabla(head->left) - visinaStabla(head->right)) > 1)
        return false;
    else return zad12(head->left) && zad12(head->right);
}

/// zad13 - da li je validno stablo

bool zad13(Node*& head){
    std::queue<int> red;
    inOrderQueue(head,red);

    if(red.empty())
        return true;
    int temp = red.front();
    red.pop()

    while(!red.empty()){
        if(temp > red.front())
            return false;

        temp = red.front();
        red.pop();
    }
    return true;
}

/// zad14 - stampanje po nivoima

void zad14(Node*& head){
    std::queue<Node*> red;
    red.push(head);

    if(red.empty())
        return;

    while(!red.empty()){
        Node* temp = red.front();
        red.pop();

        std::cout<< temp->val << " ";

        if(temp->left != nullptr)
            red.push(temp->left);
        if(temp->right != nullptr)
            red.push(temp->right);
    }
}

/// zad15

int sirinaNivoa(Node*& head,int lvl){
    if(head == nullptr)
        return 0;
    if(lvl == 0)
        return 1;
    else return sirinaNivoa(head->left,lvl-1) + sirinaNivoa(head->right,lvl-1);
}

int sirinaStabla(Node*& head){
    int visina = visinaStabla(head);
    int maxx = 0;
    for(int i = 0; i < visina;i++){
        int tempMax = sirinaNivoa(head,i);

        if(tempMax > maxx)
            maxx = tempMax;
    }

    return maxx;
}

int sirinaStablaOpt(Node*& head){
    if(head == nullptr)
        return 0;

    int maxx = 0;
    std::queue<Node*> red;
    red.push(head);

    while(!red.empty()){
        int sirinaLvl = red.size();

        if(maxx < sirinaLvl)
            maxx = sirinaLvl;
        while(sirinaLvl > 0){
            Node* temp = red.front();
            red.pop();

            if(temp->left != nullptr)
                red.push(temp->left);
            if(temp->right != nullptr)
                red.push(temp->right);

            sirinaLvl--;
        }
    }

    return maxx;
}

/// zad16 - stampanje krajnje lijevog i krajnje desnog cvora

void zad16(Node*& head){
    std::queue<Node*> red;
    red.push(head);

    if(red.empty())
        return;

    while(!red.empty){

        int lvlSize = red.size();

        std::cout<< red.front()->val << " " << red.back()->val<< std::endl;

        while(lvlSize > 0){
            Node* temp = red.front();

            if(temp->left != nullptr)
                red.push(temp->left);
            if(temp->right != nullptr)
                red.push(temp->right);

            lvlSize--;
        }
    }

}

int main(){

    return 0;
}
