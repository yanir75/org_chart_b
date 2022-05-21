#include <iostream>
#include <vector>

namespace ariel{
    class Node{
    public:
        std::string data;
        std::vector<Node*> children;
        Node* find(const std::string& to_find);
        std::string &add_str(std::string &str);
        unsigned int size() const{return data.length();}
        //friend std::ostream& operator <<(std::ostream &stream,const Node& n);
    };
    class level_order_it{
    public:
        Node *head;
        std::vector<Node *> it;
         int ind=0;
        explicit level_order_it(Node *start);
        level_order_it &operator++();
        const level_order_it operator++(int index);
        level_order_it &operator+( int size){ind=ind+size;
            return *this;}
        std::string &operator*();
        bool operator ==(const level_order_it &other) const{return ind==other.ind;}
        bool operator !=(const level_order_it &other) const{return ind!=other.ind;}
        //friend std::ostream& operator <<(std::ostream &stream,const level_order_it<Node>& n);
        Node *operator->(){return it[(unsigned long)ind];}
    };


    class reverse_level_order_it{
    public:
        Node *head;
        std::vector<Node *> it;
        int ind=-1;
        explicit reverse_level_order_it(Node *start);
        reverse_level_order_it &operator++();
        const reverse_level_order_it operator++(int index);
        reverse_level_order_it &operator+( int size){ind=ind+size;
            return *this;}
        std::string &operator*();
        bool operator ==(const reverse_level_order_it &other) const{return ind==other.ind;}
        bool operator !=(const reverse_level_order_it &other) const{return ind!=other.ind;}
        Node *operator->(){return it[(unsigned long)ind];}
    };

    class pre_level_order_it{
    public:
        Node *head;
        std::vector<Node *> it;
        int ind=0;
        explicit pre_level_order_it(Node *start);
        pre_level_order_it &operator++();
        const pre_level_order_it operator++(int index);
        pre_level_order_it &operator+( int size){ind=ind+size;
            return *this;}
        std::string &operator*();
        bool operator ==(const pre_level_order_it &other) const{return ind==other.ind;}
        bool operator !=(const pre_level_order_it &other) const{return ind!=other.ind;}
        Node *operator->(){return it[(unsigned long)ind];}
    };


    class regular_order_it{
    public:
        Node *head;
        std::vector<Node *> it;
         int ind=0;
        explicit regular_order_it(Node *start);
        regular_order_it &operator++();
        const regular_order_it operator++(int index);
        regular_order_it &operator+( int size){ind=ind+size;
            return *this;}
        std::string &operator*();
        bool operator ==(const regular_order_it &other) const{return ind==other.ind;}
        bool operator !=(const regular_order_it &other) const{return ind!=other.ind;}
        Node *operator->(){return it[(unsigned long)ind];}
    };

    class OrgChart{
    private:
        Node *head = nullptr;
         int size=0;
    public:
        OrgChart(){head= nullptr;size=0;};
        OrgChart(const OrgChart&) = default;
        OrgChart& operator= ( const OrgChart & ) = default;
        OrgChart ( OrgChart && ) = default;
        OrgChart& operator= (  OrgChart && ) = default;
        OrgChart& add_sub(const std::string& father,const std::string& child);
        OrgChart& add_root(const std::string& add);
        friend std::ostream& operator <<(std::ostream &stream,const OrgChart& chart);
        level_order_it begin_level_order(){if(size ==0){
            throw std::runtime_error("chart is empty");
        }
            return level_order_it(head);}
        level_order_it end_level_order(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return level_order_it(head)+size;}

        regular_order_it begin(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return regular_order_it(head);}
        regular_order_it end(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return regular_order_it(head)+(size);}

        reverse_level_order_it begin_reverse_order(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return reverse_level_order_it(head)+(size);}
        reverse_level_order_it reverse_order(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return reverse_level_order_it(head);}


        pre_level_order_it begin_preorder(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return pre_level_order_it(head);}
        pre_level_order_it end_preorder(){if(size ==0){
                throw std::runtime_error("chart is empty");
            }
            return pre_level_order_it(head)+(size);}
        ~OrgChart();
    };
//    std::ostream& ariel::operator<<(std::ostream& stream , const ariel::Node& n ){stream <<n.data;return stream;};
}