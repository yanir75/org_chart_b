//
// Created by yanir on 5/13/2022.
//
#include <stdexcept>
#include "OrgChart.hpp"
#include <queue>
#include <stack>
/**
 * Finds if a string exists in a tree
 * @param to_find
 * @return
 */
ariel::Node *ariel::Node::find(const std::string& to_find) {
    if(data==to_find){
        return this;
    }
    for(Node* child:children){
        Node *tmp = child->find(to_find);
        if(tmp != nullptr){
            return tmp;
        }
    }
    return nullptr;
}
/**
 * return the tostring of a tree
 * @param str
 * @return
 */
std::string& ariel::Node::add_str(std::string &str) {
    std::queue<Node *>node_queue;
    node_queue.push(this);
    while (!node_queue.empty()){
        int size = node_queue.size();
        while (size>0) {
            Node *tmp=node_queue.front();
            node_queue.pop();
            for (Node *child: tmp->children) {
                node_queue.push(child);
            }
            if(size>1) {
                str += tmp->data + "---";
            }
            else{
                str += tmp->data;
            }
            size--;
        }
        str+='\n';
    }
    return str;
}

///**
// * Return the tostring of a node
// * @param stream
// * @param n
// * @return
// */
//std::ostream &ariel::operator<<(std::ostream &stream, const ariel::Node &n) {
//    stream <<n.data;
//    return stream;
//}


/**
 * add a new node as the root of the tree
 * @param add
 * @return
 */
ariel::OrgChart &ariel::OrgChart::add_root(const std::string& add) {
    if(head== nullptr){
        head = new Node();
        head->data=add;
        size++;
    }
    else{
        head->data=add;
    }
    return *this;
}

/**
 * Add a child according to the given father
 * @param father
 * @param child
 * @return
 */
ariel::OrgChart &ariel::OrgChart::add_sub(const std::string &father, const std::string &child) {
    if(head == nullptr){
        throw std::runtime_error("employer doesn't exist");
    }
    Node *tmp=head->find(father);
    if(tmp== nullptr){
        throw std::runtime_error("employer doesn't exist");
    }
    Node *add = new Node;
    add->data = child;
    tmp->children.push_back(add);
    size++;
    return *this;
}

/**
 * Return the tostream of a tree
 * @param stream
 * @param chart
 * @return
 */
std::ostream &ariel::operator<<(std::ostream &stream, const ariel::OrgChart &chart) {
    if(chart.head!= nullptr){
        std::string str;
        stream << chart.head->add_str(str);
    }
    return stream;

}

ariel::OrgChart::~OrgChart() {
    if(head!= nullptr) {
        std::vector<Node *> vec = begin().it;
        for (Node *n: vec) {
            delete n;
        }
    }
}


/**
 * return a level_order_iterator
 * @param start
 */
ariel::level_order_it::level_order_it(ariel::Node *start) {
    head = start;
    std::queue<Node *>node_q;
    it.push_back(head);
    node_q.push(head);
    while (!node_q.empty()){
        Node *tmp =node_q.front();
        node_q.pop();
        for(Node *child:tmp->children){
            it.push_back(child);
            node_q.push(child);
        }
    }
}
/**
 * adds one to the iterator
 * @return
 */
ariel::level_order_it &ariel::level_order_it::operator++() {
    ind++;
    return *this;
}
/**
 * adds 1 to the iterator
 * @param index
 * @return
 */
const ariel::level_order_it ariel::level_order_it::operator++(int index) {
    ind++;
    return level_order_it(head)+(ind-1);
}
/**
 * return the node which is given
 * @return
 */
std::string  &ariel::level_order_it::operator*() {
    return it[(unsigned long)ind]->data;
}





//std::ostream &ariel::operator<<(ostream &stream, const level_order_it<Node> &n) {
//    stream << n.it[n.ind];
//    return stream;
//}

/**
 * Reverse order iterator
 * @param start
 */
ariel::reverse_level_order_it::reverse_level_order_it(ariel::Node *start) {
    head = start;
    std::queue<Node *>node_q;
    node_q.push(head);
    while (!node_q.empty()){
        Node *tmp =node_q.front();
        node_q.pop();
        it.push_back(tmp);
        for (unsigned int i=1; i<=tmp->children.size(); i++) {
            node_q.push(tmp->children[tmp->children.size()-i]);
        }
    }
}
/**
 * subtracts one from the iterator
 * @return
 */
ariel::reverse_level_order_it & ariel::reverse_level_order_it::operator++() {
    ind--;
    return *this;
}
/**
 * subtracts one from the iterator
 * @param index
 * @return
 */
const ariel::reverse_level_order_it ariel::reverse_level_order_it::operator++(int index) {
    ind--;
    return reverse_level_order_it(head)+(ind+1);
}

std::string &ariel::reverse_level_order_it::operator*() {
    return it[(unsigned long)ind]->data;
}


/**
 * return a pre level order iterator
 * @param start
 */
ariel::pre_level_order_it::pre_level_order_it(ariel::Node *start) {
    head = start;
    std::stack<Node *> node_s;
    node_s.push(head);
    while (!node_s.empty()) {
        Node *tmp = node_s.top();
        it.push_back(tmp);
        node_s.pop();
        for (unsigned int i=1; i<=tmp->children.size(); i++) {
            node_s.push(tmp->children[tmp->children.size()-i]);
        }
    }
}
/**
 * adds one to the iterator moving to the next stage
 * @return
 */
ariel::pre_level_order_it & ariel::pre_level_order_it::operator++() {
    ind++;
    return *this;
}

/**
 * adds one to the iterator moving to the next stage
 * @param index
 * @return
 */
const ariel::pre_level_order_it ariel::pre_level_order_it::operator++(int index) {
    ind++;
    return pre_level_order_it(head)+(ind-1);
}
/**
 * return the node of the iterator
 * @return
 */
std::string &ariel::pre_level_order_it::operator*() {
    return it[(unsigned long)ind]->data;
}

/**
 * return a regular order iterator
 * @param start
 */
ariel::regular_order_it::regular_order_it(ariel::Node *start) {
    head = start;
    std::queue<Node *>node_q;
    it.push_back(head);
    node_q.push(head);
    while (!node_q.empty()){
        Node *tmp =node_q.front();
        node_q.pop();
        for(Node *child:tmp->children){
            it.push_back(child);
            node_q.push(child);
        }
    }
}
/**
 * adds one to the iterator
 * @return
 */
ariel::regular_order_it & ariel::regular_order_it::operator++() {
    ind++;
    return *this;
}

/**
 * adds one to the iterator
 * @param index
 * @return
 */
const ariel::regular_order_it ariel::regular_order_it::operator++(int index) {
    ind++;
    return regular_order_it(head)+(ind-1);
}
/**
 * returns the node of the given iterator
 * @return
 */
std::string &ariel::regular_order_it::operator*() {
    return it[(unsigned long)ind]->data;
}

