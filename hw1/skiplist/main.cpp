#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

#define MATH_MIN std::numeric_limits<int>::min()
#define MATH_MAX std::numeric_limits<int>::max()

#include <time.h>

struct timespec allocation_clock_start, allocation_clock_end;
struct timespec coin_toss_clock_start, coin_toss_clock_end;
struct timespec traverse_clock_start, traverse_clock_end;

float total_time_coin_toss;
float total_allocation_time;
float total_traverse_time;



struct Node {
    int data;
    mutable Node* next;
    mutable Node* down;
};

float getSeconds(timespec clock_start, timespec clock_end) {
    return (clock_end.tv_sec - clock_start.tv_sec) + (clock_end.tv_nsec - clock_start.tv_nsec) * 1e-9;
}

class SkipList {
    std::vector<Node*> left_sentinel;
    std::vector<Node*> right_sentinel;
    int size;
    // constructor
    public:
    SkipList() {
        const auto sen_node = new Node();
        const auto sen_node2 = new Node();
        left_sentinel.push_back(sen_node);
        right_sentinel.push_back(sen_node2);
        sen_node->data = MATH_MIN;
        sen_node2->data = MATH_MAX;
        sen_node->next = sen_node2;
        size = 0;

    };

    int cointoss() const {
        int count = 0;
        while ( rand()/static_cast<float>(RAND_MAX) >= 0.5 ) {
            count++;
        }

        return count;

    }


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
        while (left_sentinel.size() <= height ) {
            auto new_left_sentinel = new Node();
            auto new_right_sentinel = new Node();
            new_left_sentinel->data = MATH_MIN;
            new_right_sentinel->data = MATH_MAX;

            new_left_sentinel->next = new_right_sentinel;
            new_left_sentinel->down = left_sentinel[left_sentinel.size() - 1];
            new_right_sentinel->down = right_sentinel[right_sentinel.size() - 1];
            left_sentinel.push_back(new_left_sentinel);
            right_sentinel.push_back(new_right_sentinel);
        }
    };

    //return the latest location of the node on the same layer
    static Node* traverse( Node* current, int key) {
        // std::cout << "tarvrse current start at " << current->data << std::endl;

        while (true) {
            // std::cout <<"next traverse is " << current->next->data << std::endl;
            if (current->data < key and current->next-> data >= key) {
                // std::cout << "did not move" << std::endl;
                return current;
            }else {
                current = current->next;
                // std::cout <<" move to " << current->data << std::endl;
            }
        }

    }

    int insert(const int x) {
        size++;
        // std:: cout << "------------------------"<<std::endl << "before inserting " << x << std::endl;
        // display_eachlevel();
        // std:: cout << "------------------------"<<std::endl << "inserting " << x << std::endl;
        int node_touched = 0;
        int coin_toss_result = cointoss();
        pad_sentinel(coin_toss_result);
        int curr_height = left_sentinel.size() - 1;
        Node* current_node = left_sentinel[curr_height];
        Node* temp1 = new Node();
        Node* temp2 = new Node();
        temp1->data = x;
        temp2->data = x;
        temp1-> down = temp2;

        // std::cout << "coin toss:" << coin_toss_result << std::endl;
        // std::cout << "height:" << curr_height << std::endl;
        while (curr_height > 0 ) {
            // std::cout <<"before travsere in 0: "<<current_node->data << std::endl;
            current_node = traverse(current_node, x);
            // std::cout << "after travsere in 0: " << current_node->data << std::endl;
            if (coin_toss_result <= curr_height and curr_height > 0){
                curr_height--;
                // std::cout <<"go down" << std::endl;
                current_node = current_node->down;
            }else {
                temp1->next = current_node->next;
                current_node->next = temp1;
                temp1 = temp2;
                temp2 = new Node();
                temp2->data = x;
                temp1-> down = temp2;
                current_node = current_node->down;
                curr_height--;
                // std::cout<<"go down" << std::endl;
            }
        }
        // std::cout << current_node->data << std::endl;
        current_node = traverse(current_node, x);
        temp1->next = current_node->next;
        current_node->next = temp1;

        // I hate c this dumbass line  made me waste 3 hour
        temp1-> down = NULL;

        delete temp2;


        return node_touched;




        // std::cout << "Done inserting " << x << std::endl;
    }
    bool find(int x) {
        int height = left_sentinel.size() - 1;
        Node * current_node = left_sentinel[left_sentinel.size()-1];
        while (current_node != NULL) {
            if (height < -3) {
                std::cout <<"retard" << std::endl;
                return false;
            }
            // std::cout<< "height "<< height << std::endl;
            // std::cout <<"current node" << current_node->data << " " << std::endl;
            current_node = traverse(current_node, x);
            if (current_node->next ->data == x) {
                return true;
            }
            else {
                current_node = current_node->down;
                height--;
            }

        }
        return false;
    }

    void remove(int x){
        int curr_height = left_sentinel.size() - 1 ;
        Node* current_node = left_sentinel[curr_height];

        while (curr_height >= 0 ) {
            // std::cout << "at layer " << curr_height << std::endl;
            // std::cout <<"Before traverse"<< current_node->data << " ";
            current_node = traverse(current_node, x);
            // std::cout << "After traverse"<< current_node->data << " ";
            // std::cout << "next node data" << current_node->next -> data << std::endl;

            if (current_node-> next -> data == x) {
                Node * temp = current_node->next;
                temp->next ->next = NULL;

                current_node->next = temp->next;
                delete temp;
                std::cout << "done deleteing" << std::endl;
            }

            current_node = current_node->down;
            curr_height--;
        }
    }



    void display_layer(Node* given) {
        auto head = given;
        Node* temp = head;
        while (temp  != NULL) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void display_eachlevel() {
        for (auto it = left_sentinel.rbegin(); it != left_sentinel.rend(); ++it) {
            display_layer(*it);
        }
    } void check_if_root_down_null() {
        auto head = left_sentinel[0];
        for (auto it = head;  it != NULL;  it = it->next) {
            if (it->down == NULL)
                std::cout << "key: "<<it->data << " null" << std::endl;
            else
                std::cout << "key: "<<it->data << "have" <<it->down->data <<"something wrong"  << std::endl;
        }
    }



};



int main() {

    struct timespec start, end;
    float total_time = 0;

    SkipList list1;


    int n = 10;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }

    std::random_device rd;  // Non-deterministic random number source


    int n_trails = 1;
    int touched = 0;
    for (int i = 0; i < n_trails; i++) {
        std::mt19937 g(i);
        std::shuffle(v.begin(), v.end(), g);
        SkipList list1;

        for(int j = 0; j < n-1; j++) {
            list1.insert(v[j]);
        }
        touched += list1.insert(v[n-1]);
    }
    std::cout << "touched on average:" <<touched/n_trails << std::endl;



    //
    // std::cout << "first and second elt " << v[0] << " " << v[1] << std::endl;
    std::cout << "insertion time" << std::endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++)
        list1.insert(v[i]);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double tdiff = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
    std::cout << tdiff << std::endl;
    // std::cout << "sentinellentght" <<std::endl;
    // list1.display_left_sentinel() ;
    // std::cout << "lookup time" << std::endl;
    // std::cout << total_time << std::endl;
    // std::cout << total_time_coin_toss << std::endl;
    // std::cout << total_allocation_time << std::endl;
    // std::cout << total_traverse_time << std::endl;

    list1.display_eachlevel();
    std::cout << "im finding 2 "<< list1.find(2);
    list1.remove(2);
    // list1.display_eachlevel();
    // list1.check_if_root_down_null();


    std:: cout << list1.find(3);
    std::cout << list1.find(2);


    return 0;
}

