#include <iostream>
#include <string>
struct list {
private:
    struct item{
        int val;
        int id;
        item *next;
        item(int nval, int nid = 0):
                val(nval), id(nid), next(nullptr){
        };
        void chngId(int frid, int val){
            for (item* p = this; p; p = p->next){
                if (p->id >= frid){
                    p->id += val;
                }
            }
        }
    };
    int len = 0;
    item *fst = nullptr;
    item* getVal(int fid){
        item* p = fst;
        for (; p->id!=fid; p = p->next);
        return p;
    }
public:
    int getNum(int i){
        return getVal(i)->val;
    }
    int getLen(){
        return len;
    }
    bool isEmpty(){
        return !len;
    }
    void append(int nval){
        if (!fst){
            fst = new item(nval);
        }else{
            item* p = fst;
            for(;p->next; p = p->next);
            p->next = new item(nval, len);
        }
        len += 1;
    }
    void printList(){
        for (item *p = fst; p; p = p->next) {
            std::cout << p->val;
        }
        std::cout << std::endl;
    }
    int del(){
        int toRet;
        if (len){
            if (len > 1){
                int i = 0;
                for (; i < len-2; i++);
                item* p = getVal(i);
                toRet = p->next->val;
                delete p->next;
                p->next = nullptr;
            }else{
                toRet = fst->val;
                delete fst;
                fst = nullptr;
            }
            --len;
            return toRet;
        }
        return 0;
    }
    ~list(){
        item *temp;
        len = 0;
        while (fst){
            temp = fst;
            fst = fst->next;
            delete temp;
        }
    }
};
struct arrStack{
    private:
    int len;
    int* arr;
    public:
    bool isEmpty(){
        return !len;
    }
    void printArr(){
        for (int i = 0; i < len; i++){
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }
    int getLen(){
        return len;
    }
    int getNum(int i){
        return arr[i];
    }
    void append(int val){
        if (len){
            int* temp = arr;
            arr = new int[len+1];
            for (int i = 0; i < len; i++){
                arr[i] = temp[i];
            }
            arr[len] = val;
            delete temp;
        }else{
            arr = new int[len+1];
            arr[0] = val;
        }
        len += 1;
    }
    arrStack(std::string s){
        len = 0;
        std::string b = "";
        for (int i = 0; i < s.length(); i ++){
            b = s[i];
            append(std::stoi(b));
        }
    }
    arrStack():len(0){}
    int del(){
        if (len>0){
            int snd = arr[len-1];
            --len;
            int* temp = arr;
            if (!len){
                arr = nullptr;
            }else{
                arr = new int[len];
                for (int i = 0; i < len; i++){
                    arr[i] = temp[i];
                }
            }
            delete temp;
            return snd;
        }
        return 0;
    }

};
list* strToStack(std::string s){
    list* a = new list();
    std::string b = "";
    for (int i = 0; i < s.length(); i ++){
        b = s[i];
        a->append(std::stoi(b));
    }
    return a;
}
int main() {
    std::string numa, numb;
    std::cin >> numa >> numb;

    list* res = new list();
    int per = 0;
    list* a = strToStack(numa);
    list* b = strToStack(numb);
    if (a->getLen()<b->getLen()){
        list* temp = a;
        a = b;
        b = temp;
    }
    int k;
    while (!a->isEmpty()){
        if (!b->isEmpty()){
            k = a->del()+b->del()+per;
            res->append(k%10);
            per = k/10;
        }else{
            k = a->del()+per;
            res->append(k%10);
            per = k/10;
        }
    }
    if (per){
        res->append(per);
    }
    for (int i = res->getLen()-1; i >= 0; i--){
        std::cout<<res->getNum(i);
    }
    std::cout<<std::endl;
    arrStack* aa = new arrStack(numa);
    arrStack* bb = new arrStack(numb);
    arrStack* resres = new arrStack();
    per = 0;
    if (aa->getLen()<bb->getLen()){
        arrStack* temp = aa;
        aa = bb;
        bb = temp;
    }
    while (!aa->isEmpty()){
        if (!bb->isEmpty()){
            k = aa->del()+bb->del()+per;
            resres->append(k%10);
            per = k/10;
        }else{
            k = aa->del()+per;
            resres->append(k%10);
            per = k/10;
        }
    }
    if (per){
        resres->append(per);
    }
    for (int i = resres->getLen()-1; i >= 0; i--){
        std::cout<<resres->getNum(i);
    }
    delete a;
    delete b;
    delete aa;
    delete bb;
    delete res;
    delete resres;
    return 0;
}
