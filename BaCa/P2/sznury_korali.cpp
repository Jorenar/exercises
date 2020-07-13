// Jakub Lukasiewicz

// 76% ...

#include <iostream>

struct Bead;
struct Strand;
struct ID_strand;
template<typename T> struct List;
typedef short ID_bead;

struct ID_strand {

    ID_strand() {}

    ID_strand(const char* data_)
    {
        data1 = *(data_+0);
        data2 = *(data_+1);
        data3 = *(data_+2);
    }

    char data1;
    char data2;
    char data3;

    bool operator <(const ID_strand& obj)
    {
        if (data1 != obj.data1) {
            return data1 < obj.data1;
        }
        else if (data2 != obj.data2) {
            return data2 < obj.data2;
        }
        else {
            return data3 < obj.data3;
        }
    }

    bool operator >(const ID_strand& obj)
    {
        if (data1 != obj.data1) {
            return data1 > obj.data1;
        }
        else if (data2 != obj.data2) {
            return data2 > obj.data2;
        }
        else {
            return data3 > obj.data3;
        }
    }

    bool operator ==(const ID_strand& obj)
    {
        return
            data1 == obj.data1 &&
            data2 == obj.data2 &&
            data3 == obj.data3;
    }

    friend std::istream& operator >>(std::istream& in, ID_strand& id)
    {
        in >> id.data1;
        in >> id.data2;
        in >> id.data3;
        return in;
    }

    friend std::ostream& operator <<(std::ostream& out, const ID_strand& id)
    {
        return out << id.data1 << id.data2 << id.data3;
    }

};

template<typename T>
struct List {

    List() : node(NULL), first(NULL) {}

    ~List()
    {
        node = first;
        Node* temp;
        while (node) {
            temp = node;
            node = node->next;
            delete temp;
        }
    }

    struct Node {
        Node() : prev(NULL), next(NULL) {}
        Node(T* obj_) : obj(obj_), idInNode(obj_->idUP), prev(NULL), next(NULL) {}

        ~Node()
        {
            if (obj->copies == 1) {
                delete obj;
            }
            else {
                obj->copies -= 1;
            }
        }

        T* obj;
        ID_strand idInNode;
        Node* prev;
        Node* next;
    };

    Node* node;
    Node* first;

    bool changeToNodeWithId(T* x)
    {
        if (node) {
            while (node->obj->id > x->id && node->prev) {
                node = node->prev;
            }
            while (node->obj->id < x->id && node->next) {
                node = node->next;
            }

            return node->obj->id == x->id;
        }
        else {
            return false;
        }
    }

    void add(T* x)
    {
        Node* newNode = new Node(x);
        newNode->idInNode = x->idUP;
        x->copies += 1;
        if (node) {
            changeToNodeWithId(x);
            if (node->idInNode > x->idUP || ( node->idInNode == x->idUP &&  node->obj->id > x->id) ) {
                if (node == first) {
                    first = newNode;
                }
                newNode->prev = node->prev;
                newNode->next = node;
                node->prev = newNode;
                node = newNode;
                if (node->prev) {
                    node->prev->next = node;
                }
            }
            else {
                newNode->next = node->next;
                newNode->prev = node;
                node->next = newNode;
                node = newNode;
                if (node->next) {
                    node->next->prev = node;
                }
            }
        }
        else {
            node = newNode;
            first = node;
        }
    }

    void add(T x)
    {
        T* a = new T(x);
        add(a);
    }

    void deleteNode(Node* n)
    {
        if (n == first) {
            first = n->next;
        }
        if (n->prev) {
            n->prev->next = n->next;
        }
        if (n->next) {
            n->next->prev = n->prev;
        }
        Node* temp = n;
        if (n->prev) {
            n = n->prev;
        }
        else {
            n->next;
        }
        delete temp;
    }

    void deleteNodeById(T x)
    {
        if (changeToNodeWithId(&x)) {
            deleteNode(node);
        }
    }

    void deleteNodeById(T x, int)
    {
        if (changeToNodeWithId(&x)) {
            node->obj->bonds.iNoLongerLinkToYou(node->obj);
            node->obj->bondedTo.stopLinkingToMe(node->obj);
            deleteNode(node);
        }
    }

    void deleteNodeByObj(T* x)
    {
        Node* temp = first;
        while (temp) {
            if (temp->obj == x) {
                break;
            }
            temp = temp->next;
        }
        if (temp) {
            deleteNode(temp);
        }
    }

    void print()
    {
        Node* temp = first;
        while (temp) {
            temp->obj->print();
            temp = temp->next;
        }
    }

    void print(int)
    {
        Node* temp = first;
        while (temp) {
            std::cout << " " << temp->idInNode << " " << temp->obj->id;
            temp = temp->next;
        }
    }

    void printPtr()
    {
        Node* temp = first;
        while (temp) {
            std::cout << temp->obj << std::endl;
            temp = temp->next;
        }
    }

    T* getObjById(T x)
    {
        Node* temp = first;
        while (temp) {
            if (temp->obj->id == x.id) {
                return temp->obj;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void iNoLongerLinkToYou(T* x)
    {
        Node* temp = first;
        while (temp) {
            temp->obj->bondedTo.deleteNodeByObj(x);
            temp = temp->next;
        }
    }

    void stopLinkingToMe(T* x)
    {
        Node* temp = first;
        while (temp) {
            temp->obj->bonds.deleteNodeByObj(x);
            temp = temp->next;
        }
    }

    void deleteAllBeads()
    {
        Node* temp = first;
        Node* temp2;
        while (temp) {
            temp->obj->bonds.iNoLongerLinkToYou(temp->obj);
            temp->obj->bondedTo.stopLinkingToMe(temp->obj);
            temp2 = temp->next;
            deleteNode(temp);
            temp = temp2;
        }
    }
};

struct Bead {
    Bead(ID_bead id_) : id(id_), copies(0) {}
    Bead(ID_bead id_, ID_strand idUP_) : id(id_), idUP(idUP_), copies(0) {}
    ID_bead id;
    ID_strand idUP;
    short copies;
    List<Bead> bonds;
    List<Bead> bondedTo;

    void link(Bead* obj)
    {
        bonds.add(obj);
        obj->bondedTo.add(this);
    }

    void unLink(Bead* obj)
    {
        bonds.deleteNodeByObj(obj);
        obj->bondedTo.deleteNodeByObj(this);
    }

    void print()
    {
        std::cout << id;
        bonds.print(1);
        std::cout << std::endl;
    }
};

struct Strand {
    Strand(const char* id_) : id(id_), idUP("000"), copies(0) {}
    Strand(ID_strand id_) : id(id_), idUP("000"), copies(0) {}

    ID_strand id;
    ID_strand idUP;
    short copies;
    List<Bead> beads;

    void print()
    {
        std::cout << id << std::endl;
        beads.print();
    }
};

int main()
{
    char command;
    List<Strand> strands;

    ID_strand dS;
    ID_strand s;
    ID_strand sn;
    ID_strand sS;

    ID_bead dK;
    ID_bead k;
    ID_bead kr;
    ID_bead sK;

    Bead* temp;

    do {
        std::cin >> command;

        switch (command) {
            case 'S':
                std::cin >> s;
                strands.add(s);
                break;
            case 'B':
                std::cin >> kr;
                std::cin >> sn;
                temp = new Bead(kr, sn);
                strands.getObjById(sn)->beads.add(temp);
                break;
            case 'L':
                std::cin >> sK;
                std::cin >> sS;
                std::cin >> dK;
                std::cin >> dS;
                strands.getObjById(sS)->beads.getObjById(sK)->link(strands.getObjById(dS)->beads.getObjById(dK));
                break;
            case 'U':
                std::cin >> sK;
                std::cin >> sS;
                std::cin >> dK;
                std::cin >> dS;
                strands.getObjById(sS)->beads.getObjById(sK)->unLink(strands.getObjById(dS)->beads.getObjById(dK));
                break;
            case 'D':
                std::cin >> k;
                std::cin >> s;
                strands.getObjById(s)->beads.deleteNodeById(k, 1);
                break;
            case 'M':
                std::cin >> k;
                std::cin >> sS;
                std::cin >> dS;
                temp = strands.getObjById(sS)->beads.getObjById(k);
                temp->idUP = dS;
                strands.getObjById(dS)->beads.add(temp);
                strands.getObjById(sS)->beads.deleteNodeByObj(temp);
                break;
            case 'R':
                std::cin >> s;
                strands.getObjById(s)->beads.deleteAllBeads();
                strands.deleteNodeById(s);
                break;
            case 'P':
                strands.print();
                break;
        }

        std::cin.clear();

    } while (command != 'F');

    return 0;
}

// vim: fen
