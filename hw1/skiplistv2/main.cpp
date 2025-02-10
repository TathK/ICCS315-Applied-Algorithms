#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

#define MATH_MIN std::numeric_limits<int>::min()
#define MATH_MAX std::numeric_limits<int>::max()
#include <chrono>
#include <fstream>

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
    mutable Node* up;
};


int cointoss() {
    int count = 0;
    while ( rand()/float(RAND_MAX) >= 0.5) {
        count++;
    }
    return count;

}



class SkipList {

    std::vector<Node*> left_sentinel;
    std::vector<Node*> right_sentinel;

    // constructor
    public:
    SkipList() : right_sentinel(NULL), left_sentinel(NULL) {
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
            left_sentinel[left_sentinel.size() - 1] -> up = new_left_sentinel;
            right_sentinel[right_sentinel.size() - 1] -> up = new_right_sentinel;
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


        while (curr_height > 0 ) {
            current_node = traverse(current_node, x);
            if (coin_toss_result <= curr_height and curr_height > 0){
                curr_height--;
                current_node = current_node->down;
            }else {
                temp1->next = current_node->next;
                current_node->next = temp1;
                temp1 = temp2;
                temp2 = new Node();
                temp2->data = x;
                temp1-> down = temp2;
                temp2-> up = temp1;
                current_node = current_node->down;
                curr_height--;
            }
        }
        // std::cout << current_node->data << std::endl;
        current_node = traverse(current_node, x);
        temp1->next = current_node->next;
        current_node->next = temp1;

        temp1->down = NULL;


        temp2->down = NULL;
        temp1->up = NULL;
        temp2->next = NULL;

        delete temp2;



        // std::cout << "Done inserting " << x << std::endl;
    }



    void remove(int x){
        int curr_height = left_sentinel.size() - 1 ;
        Node* current_node = left_sentinel[curr_height];
        while (curr_height >= 0 ) {
            // std::cout << "at layer " << curr_height << std::endl;
            current_node = traverse(current_node, x);
            if (current_node->next -> data == x) {
                Node * temp = current_node->next;
                current_node->next = temp->next;

                temp -> up = NULL;
                temp -> down = NULL;
                temp -> next = NULL;
                delete temp;
            }
            current_node = current_node->down;
            curr_height--;
        }
    }

    bool find(int x) {
        Node * current_node = left_sentinel[0];

        while (true) {
            if (current_node->data == x)
                return true;
            else if (current_node->data < x and current_node->next->data > x and current_node->down == NULL)
                return false;
            else if (current_node -> down == NULL and current_node -> up == NULL) {
                    current_node = current_node->next;
            }
            else if (current_node ->down == NULL and current_node -> next -> data == MATH_MAX)
                return false;

            else if(current_node -> down == NULL and current_node -> up !=NULL) {
                int up_right_elt = current_node -> up -> next -> data;
                int next_elt = current_node -> next  -> data;
                int current_elt = current_node -> data;
                if (up_right_elt <= x)
                    current_node = current_node -> up -> next;
                else
                    current_node = current_node -> next;

            }

            else if(current_node -> up == NULL) {
                if (current_node->next -> data <= x)
                    current_node = current_node -> next;
                else
                    current_node = current_node -> down;
            }

            else {
                int up_right_elt = current_node -> up -> next -> data;
                int next_elt = current_node -> next  -> data;
                int down_right_elt = current_node -> down -> next -> data;
                if (up_right_elt <= x)
                    current_node = current_node -> up -> next;
                else if(next_elt <= x)
                    current_node = current_node -> next;
                else if(down_right_elt <=x)
                    current_node = current_node -> down -> next;
                else
                    current_node = current_node -> down;

            }



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

    void delete_all() {
        for (auto it = left_sentinel.rbegin(); it != left_sentinel.rend(); ++it) {
            Node * current = *it;
            while (current->next != NULL) {
                Node * temp = current->next;
                current -> next = NULL;
                current ->down = NULL;
                current ->up = NULL;
                delete current;
                current = temp;
            }
        }
        left_sentinel.clear();
        right_sentinel.clear();
    }

    ~SkipList() {
        delete_all();  // Clean up nodes in the destructor
    }


};


void test_insert(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;


    std::stringstream ss;
    ss << "output/insert/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);
        for (int noise_no = 0; noise_no < 10; noise_no++) {
            SkipList list1;

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.insert(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}
void test_insert_base(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;


    std::stringstream ss;
    ss << "output_base/insert/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);

    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);
        for (int noise_no = 0; noise_no < 10; noise_no++) {
            std::set<int> list1;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.insert(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
        noise_list.clear();

    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }



    file.close();
}
void test_delete(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output/delete/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);
        for (int noise_no = 0; noise_no < 10; noise_no++) {
            SkipList list1;

            for (int i = 0; i < n; i++)
                list1.insert(v[i]);

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.remove(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}
void test_delete_base(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output_base/delete/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);

        for (int noise_no = 0; noise_no < 10; noise_no++) {
            std::set<int> list1;
            for (int i = 0; i < n; i++)
                list1.insert(v[i]);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.erase(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}

void test_lookup(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output/lookup/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);
        SkipList list1;
        for (int i = 0; i < n; i++)
            list1.insert(v[i]);

        for (int noise_no = 0; noise_no < 10; noise_no++) {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.find(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}
void test_lookup_base(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output_base/lookup/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        std::mt19937 g(seed_no);
        std::shuffle(v.begin(), v.end(), g);
        std::set<int> list1;
        for (int i = 0; i < n; i++)
            list1.insert(v[i]);
        for (int noise_no = 0; noise_no < 10; noise_no++) {

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                list1.find(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}

void test_lookupV2(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output/lookupv2/" << n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        SkipList list1;
        for (int i = 0; i < n; i++)
            list1.insert(v[i]);

        for (int noise_no = 0; noise_no < 10; noise_no++) {
            int hardcap = int(.25 *  n);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < hardcap; i++)
                list1.find(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}
void test_lookup_baseV2(int n) {
    std::vector<double> result = std::vector<double>();
    struct timespec start, end;
    std::stringstream ss;
    ss << "output_base/lookupv2/" <<n << ".txt";
    std::ofstream file(ss.str(), std::ios::app);
    for (int seed_no = 0; seed_no < 30; seed_no++) {
        std::vector<double> noise_list = std::vector<double>();
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }

        std::set<int> list1;
        for (int i = 0; i < n; i++)
            list1.insert(v[i]);

        for (int noise_no = 0; noise_no < 10; noise_no++) {
            int hardcap = int(.25 *  n);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < hardcap; i++)
                list1.find(v[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double tdiff = std::chrono::duration<double>(end - start).count();
            noise_list.push_back(tdiff);
        }
        double min_elt = *min_element(noise_list.begin(), noise_list.end());
        result.push_back(min_elt);
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        file << *it << std::endl;
    }

    file.close();
}

int main() {
    for (int i = 1; i <= 1e6; i += 25000) {
        test_lookupV2(i);
        test_lookup_baseV2(i);
    }


    return 0;
}


