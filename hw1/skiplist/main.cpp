#include <iostream>
#include <vector>
#define MATH_MIN std::numeric_limits<int>::min()
#define MATH_MAX std::numeric_limits<int>::max()


class SkipList {
    struct node {
        int data;
        struct node *next;
    };
};

struct Node {
    int data;
    mutable Node* next;
    mutable Node* down;
};

int cointoss() {
    int count = 0;

    while ( rand()%2 != 0 ) {
        count++;
    }
    return count;

}

class LinkedList {

    std::vector<Node*> left_sentinel;
    std::vector<Node*> right_sentinel;

    // constructor
    public:
    LinkedList() : right_sentinel(NULL), left_sentinel(NULL) {
        Node* sen_node = new Node();
        Node* sen_node2 = new Node();
        left_sentinel.push_back(sen_node);
        right_sentinel.push_back(sen_node2);
        sen_node->data = MATH_MIN;
        sen_node2->data = MATH_MAX;
        sen_node->next = sen_node2;
        sen_node2->next = NULL;

    };

    void display_left_sentinel() {
        std::cout << "---------------" << std::endl;
        std::cout << "left_sentinel value"<< std::endl;
        std::cout << "size:" <<left_sentinel.size() << std::endl;
        for (Node* node : left_sentinel) {
            std::cout << node->data << " ";
        }
        std::cout << std::endl;
    };

    void pad_sentinel(int height){
        int sentinel_length = left_sentinel.size() ;
        while (sentinel_length <= height) {
            Node* new_left_sentinel = new Node();
            Node* new_right_sentinel = new Node();
            new_left_sentinel->data = MATH_MIN;
            new_right_sentinel->data = MATH_MAX;
            new_left_sentinel->next = new_right_sentinel;
            new_left_sentinel->down = left_sentinel[left_sentinel.size() - 1];
            new_right_sentinel->down = right_sentinel[right_sentinel.size() - 1];
            left_sentinel.push_back(new_left_sentinel);
            right_sentinel.push_back(new_right_sentinel);
            sentinel_length++;
        }
    };

    //return the latest location of the node on the same layer
    Node* traverse(Node* current, int key) {
        while (true) {
            if (current->data < key && (current->next)->data >= key ) {
                return current;
            }else {
                current = current->next;
            }
        }
    }
    void insert(int x) {
        std::cout << "-------------------" << std::endl;
        std::cout << "inserting " << x << std::endl;
        // find out the height of the node that we are going to insert
        int curr_height = cointoss();
        std::cout << "contois height: " <<curr_height << std::endl;
        int coin_toss_result = curr_height;
        pad_sentinel(curr_height);

        Node* current_node = left_sentinel[curr_height];

        Node* to_insert_node = new Node();
        Node* next_to_insert_node = new Node();

        to_insert_node->data = x;
        next_to_insert_node->data = x;

        while (curr_height >= 0 ) {

            std::cout << "at layer " << curr_height << std::endl;
            current_node = traverse(current_node, x);
            std::cout << "stopped at " << current_node->data << std::endl;
            if (coin_toss_result < curr_height){
                curr_height--;
                current_node = current_node->down;
            }else {
                to_insert_node->next = current_node->next;
                current_node->next = to_insert_node;
                if (curr_height>0) {
                    to_insert_node -> down = next_to_insert_node;
                }
                to_insert_node = next_to_insert_node;
                next_to_insert_node = new Node();
                next_to_insert_node->data = x;
                current_node = current_node->down;
                curr_height--;
            }
        }

        delete next_to_insert_node;




        std::cout << "Done inserting " << x << std::endl;
    }

    void remove(int x){
        int curr_height = left_sentinel.size() - 1 ;
        Node* current_node = left_sentinel[curr_height];

        while (curr_height >= 0 ) {
            std::cout << "at layer " << curr_height << std::endl;
            current_node = traverse(current_node, x);
            if (current_node->next -> data == x) {
                Node * temp = current_node->next;
                current_node->next = temp->next;
                delete temp;
            }
            current_node = current_node->down;
            curr_height--;
        }
    }



    void display_layer(Node* given) {
        auto head = given->next;
        if (head->data == MATH_MAX) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* temp = head;
        while (temp ->data != MATH_MAX) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void display_eachlevel() {
        for (auto it = left_sentinel.rbegin(); it != left_sentinel.rend(); ++it) {
            display_layer(*it);
        }
    }

};



int main() {
    LinkedList list1;
    // list1.insert(5);
    // list1.insert(10);
    // list1.display_root();


    list1.display_left_sentinel();

    list1.insert(10);
    // list1.display_eachlevel();
    list1.insert(9);
    // list1.display_eachlevel();
    list1.insert(8);
    // list1.display_eachlevel();
    list1.insert(7);
    // list1.display_eachlevel();

    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    list1.insert(5);
    list1.display_eachlevel();

    list1.remove(6);
    list1.remove(1);
    list1.remove(10);
    list1.remove(4);
    list1.remove(8);    



    list1.display_eachlevel();


    return 0;
}

