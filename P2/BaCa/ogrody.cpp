// Jakub Łukasiewicz

// NOT 100%!

#include <cstdlib>

typedef unsigned int uInt;

// Fix names {{{

#define  Fruit           FRUIT_CLASS
#define  Branch          BRANCH_CLASS
#define  Tree            WOOD_CLASS
#define  Garden          GARDEN_CLASS

#define  cloneTree       cloneWood
#define  cutTree         cutWood
#define  extractTree     extractWood
#define  getTreePointer  getWoodPointer
#define  getTreesTotal   getWoodsTotal
#define  harvestTree     harvestWood
#define  plantTree       plantWood

#define  wiltFruit       fadeFruit
#define  wiltBranch      fadeBranch
#define  wiltTree        fadeWood
#define  wiltGarden      fadeGarden

#define  growFruit       growthFruit
#define  growBranch      growthBranch
#define  growTree        growthWood
#define  growGarden      growthGarden

// Fix names }}}

class Garden;
class Tree;
class Branch;
class Fruit;

template<typename T>
struct List {
    T obj;
    List* next;
    List* prev;
};


// Fruit {{{

class Fruit {
  public:
    Fruit();
    Fruit(uInt, Branch*);
    ~Fruit();

    void setBranchPointer(Branch*);

    // Task methods
    uInt    getLength();
    uInt    getWeight();
    void    growFruit();
    void    wiltFruit();
    void    pluckFruit();
    Branch* getBranchPointer();

  private:
    uInt weight;
    uInt length; // on which grows
    Branch* parent;
};

Fruit::Fruit() : weight(0), length(2), parent(NULL) {}

Fruit::Fruit(uInt l, Branch* p) : weight(0), length(l), parent(p)  {}

Fruit::~Fruit()
{
    weight = 0;
    length = 0;
    parent = NULL;
}

void Fruit::setBranchPointer(Branch* p)
{
    parent = p;
}

uInt Fruit::getLength()
{
    return length;
}

uInt Fruit::getWeight()
{
    return weight;
}

void Fruit::growFruit()
{
    ++weight;
}

void Fruit::wiltFruit()
{
    if (weight > 0) {
        --weight;
    }
}

void Fruit::pluckFruit()
{
    weight = 0;
}

Branch* Fruit::getBranchPointer()
{
    return parent;
}

// Fruit }}}

// Branch {{{

class Branch {
  public:
    Branch();
    Branch(uInt, Tree*);
    Branch(const Branch&, bool = false);
    ~Branch();

    void setHeight(uInt);
    void setTreePointer(Tree*);
    void untemp();

    // Task methods
    uInt   getFruitsTotal();
    uInt   getWeightsTotal();
    uInt   getHeight();
    uInt   getLength();
    void   growBranch();
    void   wiltBranch();
    void   harvestBranch(uInt);
    void   cutBranch(uInt);
    Fruit* getFruitPointer(uInt);
    Tree*  getTreePointer();

  private:
    uInt  size;
    uInt  length;
    uInt  height; // on which it grows
    Tree* parent;

    List<Fruit>* data;
    List<Fruit>* last;

    bool isTemp;
};

Branch::Branch() :
    size(0), length(0), height(0), parent(NULL), data(NULL), last(NULL), isTemp(false)
{}

Branch::Branch(uInt h, Tree* p) :
    size(0), length(0), height(h), parent(p), data(NULL), last(NULL), isTemp(false)
{}

Branch::Branch(const Branch& x, bool t) :
    size(x.size), length(x.length), height(x.height), parent(x.parent), data(NULL), last(NULL), isTemp(t)
{
    if (size > 0) {
        data = new List<Fruit>;
        data->obj = x.data->obj;
        data->obj.setBranchPointer(this);
        last = data;

        List<Fruit>* it  = data;
        List<Fruit>* itX = x.data;

        while (itX->next != NULL) {
            it->next = new List<Fruit>;

            itX = itX->next;
            it = it->next;

            it->obj = itX->obj;
            it->obj.setBranchPointer(this);

            last = it;
        }

        last->next = NULL;
    }
}

Branch::~Branch()
{
    size   = 0;
    length = 0;
    height = 0;
    parent = NULL;
    last   = NULL;
    if (!isTemp) {
        List<Fruit>* it = data;
        List<Fruit>* temp;
        while (it != NULL) {
            temp = it;
            it = it->next;
            delete temp;
        }
    }
    data = NULL;
}

void Branch::setHeight(uInt h)
{
    height = h;
}

void Branch::setTreePointer(Tree* p)
{
    parent = p;
}

void Branch::untemp()
{
    isTemp = false;
}


uInt Branch::getFruitsTotal()
{
    return size;
}

uInt Branch::getWeightsTotal()
{
    uInt sum = 0;
    for (List<Fruit>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getWeight();
    }
    return sum;
}

uInt Branch::getHeight()
{
    return height;
}

uInt Branch::getLength()
{
    return length;
}

void Branch::growBranch()
{
    ++length;
    for (List<Fruit>* it = data; it != NULL; it = it->next) {
        it->obj.growFruit();
    }
    if (length > 0 && length % 2 == 0) {
        if (size > 0) {
            last->next = new List<Fruit>;
            last->next->obj = Fruit(length, this);
            last = last->next;
        }
        else {
            data = last = new List<Fruit>;
            last->obj = Fruit(length, this);
        }
        last->next = NULL;
        ++size;
    }
}

void Branch::wiltBranch()
{
    if (length > 0) {
        --length;
        if (size > 0) {
            if (last->obj.getLength() > length) {
                List<Fruit>* it = data;

                if (it == last) {
                    data = last = NULL;
                }
                else {
                    while (it->next != last) {
                        it->obj.wiltFruit();
                        it = it->next;
                    }
                    it->obj.wiltFruit();

                    last = it;
                    it = it->next;
                    last->next = NULL;
                }

                delete it;

                --size;

            }
            else {
                for (List<Fruit>* it = data; it != NULL; it = it->next) {
                    it->obj.wiltFruit();
                }
            }
        }
    }
}

void Branch::harvestBranch(uInt x)
{
    for (List<Fruit>* it = data; it != NULL; it = it->next) {
        if (it->obj.getWeight() >= x) {
            it->obj.pluckFruit();
        }
    }
}

void Branch::cutBranch(uInt l)
{
    length = l;
    if (size > 0) {
        if (last->obj.getLength() > length) {
            List<Fruit>* it = data;
            while (it != NULL) {
                if (it->obj.getLength() > length) {
                    break;
                }
                last = it;
                it = it->next;
            }

            if (it == data) {
                data = last = NULL;
            }

            List<Fruit>* temp;
            while (it != NULL) {
                --size;
                temp = it;
                it = it->next;
                delete temp;
            }

            if (last != NULL) {
                last->next = NULL;
            }
        }
    }
}

Fruit* Branch::getFruitPointer(uInt x)
{
    if (x > 0 && x % 2 == 0 && x <= length) {
        for (List<Fruit>* it = data; it != NULL; it = it->next) {
            if (it->obj.getLength() == x) {
                return &(it->obj);
            }
        }
    }
    return NULL;
}

Tree* Branch::getTreePointer()
{
    return parent;
}

// Branch }}}

// Tree {{{

class Tree {
  public:
    Tree();
    Tree(uInt, Garden*);
    Tree(const Tree&, bool = false);
    ~Tree();

    void setNumber(uInt);
    void untemp();
    void setGardenPointer(Garden*);

    // Task methods
    uInt    getBranchesTotal();
    uInt    getFruitsTotal();
    uInt    getWeightsTotal();
    uInt    getNumber();
    uInt    getHeight();
    void    growTree();
    void    wiltTree();
    void    harvestTree(uInt);
    void    cutTree(uInt);
    void    cloneBranch(Branch*);
    Garden* getGardenPointer();
    Branch* getBranchPointer(uInt);

  private:
    uInt id;
    uInt height;
    uInt size;
    Garden* parent;
    List<Branch>* data;
    List<Branch>* last;

    bool isTemp;
};

Tree::Tree() :
    id(0), height(0), size(0), parent(NULL), data(NULL), last(NULL), isTemp(false)
{}

Tree::Tree(uInt i, Garden* p) :
    id(i), height(0), size(0), parent(p), data(NULL), last(NULL), isTemp(false)
{}

Tree::Tree(const Tree& x, bool t) :
    height(x.height), size(x.size), parent(x.parent), isTemp(t)
{
    if (size > 0) {
        data = new List<Branch>;
        data->obj = Branch(x.data->obj, true);
        data->obj.untemp();
        data->obj.setTreePointer(this);
        last = data;

        List<Branch>* it  = data;
        List<Branch>* itX = x.data;

        while (itX->next != NULL) {
            it->next = new List<Branch>;

            itX = itX->next;
            it = it->next;

            it->obj = Branch(itX->obj, true);
            it->obj.untemp();
            it->obj.setTreePointer(this);

            last = it;
        }

        last->next = NULL;
    }
}

Tree::~Tree()
{
    if (!isTemp) {
        List<Branch>* it = data;
        List<Branch>* temp;
        while (it != NULL) {
            temp = it;
            it = it->next;
            delete temp;
        }
    }
}

void Tree::setNumber(uInt x)
{
    id = x;
}

void Tree::untemp()
{
    isTemp = false;
}


uInt Tree::getBranchesTotal()
{
    return size;
}

uInt Tree::getFruitsTotal()
{
    uInt sum = 0;
    for (List<Branch>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getFruitsTotal();
    }
    return sum;
}

uInt Tree::getWeightsTotal()
{
    uInt sum = 0;
    for (List<Branch>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getWeightsTotal();
    }
    return sum;
}

uInt Tree::getNumber()
{
    return id;
}

uInt Tree::getHeight()
{
    return height;
}

void Tree::growTree()
{
    ++height;
    for (List<Branch>* it = data; it != NULL; it = it->next) {
        it->obj.growBranch();
    }
    if (height > 0 && height % 3 == 0) {
        if (size > 0) {
            last->next = new List<Branch>;
            last->next->obj = Branch(height, this);
            last = last->next;
        }
        else {
            data = last = new List<Branch>;
            last->obj = Branch(height, this);
        }
        last->next = NULL;
        ++size;
    }
}

void Tree::wiltTree()
{
    if (height > 0) {
        --height;
        if (last != NULL && last->obj.getHeight() > height) {
            List<Branch>* it = data;
            while (it != NULL) {
                if (it->obj.getHeight() > height) {
                    break;
                }
                last = it;
                it->obj.wiltBranch();
                it = it->next;
            }
            if (it == data) {
                data = last = NULL;
            }
            List<Branch>* temp;
            while (it != NULL) {
                --size;
                temp = it;
                it = it->next;
                delete temp;
            }
            if (last != NULL) {
                last->next = NULL;
            }
        }
        else {
            for (List<Branch>* it = data; it != NULL; it = it->next) {
                it->obj.wiltBranch();
            }
        }
    }
}

void Tree::harvestTree(uInt x)
{
    for (List<Branch>* it = data; it != NULL; it = it->next) {
        it->obj.harvestBranch(x);
    }
}

void Tree::cutTree(uInt h)
{
    height = h;
    if (size > 0) {
        if (last->obj.getHeight() > height) {
            List<Branch>* it = data;
            while (it != NULL) {
                if (it->obj.getHeight() > height) {
                    break;
                }
                last = it;
                it = it->next;
            }
            if (it == data) {
                data = last = NULL;
            }
            List<Branch>* temp;
            while (it != NULL) {
                --size;
                temp = it;
                it = it->next;
                delete temp;
            }
            if (last != NULL) {
                last->next = NULL;
            }
        }
    }
}

void Tree::cloneBranch(Branch* b)
{
    if (b != NULL && size > 0) {
        List<Branch>* it = data;
        while (it != NULL) {
            if (it->obj.getLength() == 0) {
                break;
            }
            it = it->next;
        }
        if (it != NULL) {
            uInt h = it->obj.getHeight();
            it->obj = Branch(*b, true);
            it->obj.untemp();
            it->obj.setHeight(h);
            it->obj.setTreePointer(this);
        }
    }
}

Garden* Tree::getGardenPointer()
{
    return parent;
}

Branch* Tree::getBranchPointer(uInt x)
{
    if (x > 0 && x % 3 == 0 && x <= height) {
        for (List<Branch>* it = data; it != NULL; it = it->next) {
            if (it->obj.getHeight() == x) {
                return &(it->obj);
            }
        }
    }
    return NULL;
}

// Tree }}}

// Garden {{{

class Garden {
  public:
    Garden();
    ~Garden();

    // Task methods
    uInt  getTreesTotal();
    uInt  getBranchesTotal();
    uInt  getFruitsTotal();
    uInt  getWeightsTotal();
    void  plantTree();
    void  extractTree(uInt);
    void  growGarden();
    void  wiltGarden();
    void  harvestGarden(uInt);
    void  cloneTree(uInt);
    Tree* getTreePointer(uInt);

  private:
    uInt size;
    List<Tree>* data;
    List<Tree>* last;

    uInt potentialGaps;
};

Garden::Garden() : size(0), data(NULL), last(NULL), potentialGaps(0) {}

Garden::~Garden()
{
    List<Tree>* it = data;
    List<Tree>* temp;
    while (it != NULL) {
        temp = it;
        it = it->next;
        delete temp;
    }
}

uInt Garden::getTreesTotal()
{
    return size;
}

uInt Garden::getBranchesTotal()
{
    uInt sum = 0;
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getBranchesTotal();
    }
    return sum;
}

uInt Garden::getFruitsTotal()
{
    uInt sum = 0;
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getFruitsTotal();
    }
    return sum;
}

uInt Garden::getWeightsTotal()
{
    uInt sum = 0;
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        sum += it->obj.getWeightsTotal();
    }
    return sum;
}

void Garden::plantTree()
{
    if (size > 0) {
        if (potentialGaps == 0) {
            last->next = new List<Tree>;
            last->next->prev = last;
            last->next->obj = Tree(last->obj.getNumber() + 1, this);
            last = last->next;
            last->next = NULL;
        }
        else {
            if (data->obj.getNumber() > 0) {
                List<Tree>* temp = new List<Tree>;
                temp->prev = NULL;
                temp->obj = Tree(0, this);
                temp->next = data;
                data->prev = temp;
                data = temp;
                --potentialGaps;
            }
            else {
                List<Tree>* it = data;
                while (it->next != NULL) {
                    if (it->obj.getNumber() + 1 < it->next->obj.getNumber()) {
                        break;
                    }
                    it = it->next;
                }

                List<Tree>* temp = it->next;
                it->next = new List<Tree>;
                it->next->prev = it;
                it->next->obj = Tree(it->obj.getNumber() + 1, this);

                if (temp != NULL) {
                    temp->prev = it->next;
                }
                if (it->next != NULL) {
                    it->next->next = temp;
                }

                if (it == last) {
                    last = it->next;
                    potentialGaps = 0;
                }
                else if (potentialGaps > 0 ) {
                    --potentialGaps;
                }
            }
        }
    }
    else {
        data = last = new List<Tree>;
        last->obj = Tree(0, this);
        last->next = NULL;
    }
    ++size;
}

void Garden::growGarden()
{
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        it->obj.growTree();
    }
}

void Garden::extractTree(uInt x)
{
    if (size > 0) {
        if (x == last->obj.getNumber()) {
            List<Tree>* temp = last;
            if (last == data) {
                data = last = NULL;
            }
            else {
                last = last->prev;
                last->next = NULL;
            }

            delete temp;
            --size;
        }
        else if (x < last->obj.getNumber()) {
            List<Tree>* it   = data;
            List<Tree>* prev = NULL;

            while (it->next != NULL) {
                if (it->obj.getNumber() == x) {
                    break;
                }
                prev = it;
                it = it->next;
            }

            if (it->obj.getNumber() == x) {
                if (it == data && it == last) {
                    data = last = NULL;
                    potentialGaps = 0;
                }
                else if (it == data) {
                    data = data->next;
                    data->prev = NULL;
                    ++potentialGaps;
                }
                else if (it == last) {
                    last = prev;
                    last->next = NULL;
                }
                else {
                    prev->next = it->next;
                    it->next->prev = prev;
                    ++potentialGaps;
                }

                delete it;

                --size;
            }

        }
    }
}

void Garden::wiltGarden()
{
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        it->obj.wiltTree();
    }
}

void Garden::harvestGarden(uInt x)
{
    for (List<Tree>* it = data; it != NULL; it = it->next) {
        it->obj.harvestTree(x);
    }
}

void Garden::cloneTree(uInt x)
{
    if (size > 0) {
        if (x <= last->obj.getNumber()) {
            List<Tree>* it = data;
            List<Tree>* it2 = last;
            List<Tree>* X = NULL;
            List<Tree>* A = NULL;

            bool beforeData = false;
            if (potentialGaps == 0) {
                A = last;
            }
            else if (data->obj.getNumber() > 0) {
                beforeData = true;
                A = data;
            }

            if (last->obj.getNumber() == x) {
                X = last;
            }

            while (it != NULL && it2 != NULL && (X == NULL || A == NULL)) {
                if (X == NULL && it->obj.getNumber() == x) {
                    X = it;
                }
                else if (X == NULL && it2->obj.getNumber() == x) {
                    X = it2;
                }
                else if (X == NULL && it->obj.getNumber() >= it2->obj.getNumber()) {
                    break;
                }

                if (A == NULL && it == last) {
                    A = it;
                }
                else if (A == NULL) {
                    if (it->obj.getNumber() + 1 < it->next->obj.getNumber()) {
                        A = it;
                    }
                }

                it  = it->next;
                it2 = it2->prev;
            }

            if (X != NULL) {
                if (beforeData) {
                    A = new List<Tree>;
                    A->next = data;
                    A->prev = NULL;
                    data->prev = A;
                    A->obj  = Tree(X->obj, true);
                    A->obj.untemp();
                    A->obj.setNumber(0);
                    data = A;
                    --potentialGaps;
                }
                else {
                    List<Tree>* temp = A->next;
                    A->next = new List<Tree>;
                    A->next->prev = A;
                    A->next->obj = Tree(X->obj, true);
                    A->next->obj.untemp();
                    A->next->obj.setNumber(A->obj.getNumber() + 1);
                    if (temp != NULL) {
                        temp->prev = A->next;
                    }
                    A->next->next = temp;

                    if (A == last) {
                        potentialGaps = 0;
                    }
                    else if (potentialGaps > 0) {
                        --potentialGaps;
                    }
                }

                ++size;
            }
        }
    }
}

Tree* Garden::getTreePointer(uInt x)
{
    if (size > 0) {
        if (x == last->obj.getNumber()) {
            return &(last->obj);
        }
        else if (x < last->obj.getNumber()) {
            for (List<Tree>* it = data; it != NULL; it = it->next) {
                if (it->obj.getNumber() == x) {
                    return &(it->obj);
                }
                else if (it->obj.getNumber() > x) {
                    break;
                }
            }
        }
    }
    // if (data != NULL && x == 2) return &(data->obj);
    return NULL;
}

// Garden }}}

// vim: fen
