#include <iostream>
#include<memory>

class Node{
public:
    int val;
    int number_of_copies;
    int number_of_left;
    int height = 1;

    Node* left;
    Node* right;

    Node(int _val, int k, int _n_of_l):
            val(_val), number_of_copies(k), number_of_left(_n_of_l), left(nullptr), right(nullptr)
    {};

    static int get_height(Node *node) {
        if (!node) return 0;
        return node->height;
    }

    static int getBalance(Node *node)
    {
        if (!node)
            return 0;
        return (get_height(node->left) - get_height(node->right));
    }

    static Node* rotate_left(Node *root) {
        if (!root) return root;
        if (!root->right) return root;
        Node *right = root->right;

        root->right = right->left;
        right->left = root;

        // Update heights
        root->height = std::max(get_height(root->left),
                                get_height(root->right)) + 1;
        right->height = std::max(get_height(right->left),
                                 get_height(right->right)) + 1;

        right->number_of_left += root->number_of_copies + root->number_of_left;

        return right;
    }

    static Node* rotate_right(Node *root) {
        if (!root) return root;
        if (!root->left) return root;

        Node* left = root->left;

        // Perform rotation
        root->left = left->right;
        left->right = root;

        // Update heights
        root->height = std::max(get_height(root->left),
                                get_height(root->right)) + 1;
        left->height = std::max(get_height(left->left),
                                get_height(left->right)) + 1;

        root->number_of_left -= left->number_of_copies + left->number_of_left;

        // Return new root
        return left;
    }

    Node* insert (int value, int count, int position){
        Node *res = this;

        if (position <= this->number_of_left){
            res->number_of_left += count;

            if(res->left)
                res->left = res->left->insert (value, count, position);
            else {
                res->left = new Node(value, count, 0);
            }

            res->height = std::max(get_height(res->left),
                                    get_height(res->right)) + 1;
        }
        else if (res->number_of_left < position && position < res->number_of_left + res->number_of_copies){
            int how_much_left = position - res->number_of_left;
            int how_much_right = number_of_copies - how_much_left;
            int old_value = res->val;
            int old_index = res->number_of_left;

            res->number_of_copies = count;
            res->val = value;


            if (res->right)
                res->right = res->right->insert(old_value, how_much_right, 0);
            else
                res->right = new Node(old_value, how_much_right, 0);

            if (res->left)
                res = res->insert(old_value, how_much_left, old_index);
            else {
                res->left = new Node(old_value, how_much_left, 0);
                res->number_of_left += how_much_left;
            }
        }
        else if (position >= res->number_of_left + res->number_of_copies){
            if (res->right)
                res->right = res->right->insert(value, count, position - res->number_of_left - res->number_of_copies);
            else {
                res = res;
                res->right = new Node(value, count, 0);
            }

            res->height = std::max(get_height(res->left),
                                    get_height(res->right)) + 1;
        }

        int balance = getBalance(res);

        if (balance > 1) {
            res = rotate_right(res);
        } else if (balance < 0) {
            res = rotate_left(res);
        }
//        //insert into res.left.left
//        if (balance > 1 && Node::getBalance(res->left) >= 0) {
//            res = Node::rotate_right(res);
//        } else if (balance > 1 && Node::getBalance(res->left) < 0) {
//            res->left = Node::rotate_left(res->left);
//            res = Node::rotate_right(res);
//        } else if (Node::getBalance(res) < 0 && Node::getBalance(res->right) > 0) {
//            res->right = Node::rotate_right(res->right);
//            res = Node::rotate_left(res);
//        } else if (balance < 0 && Node::getBalance(res->right) <= 0) {
//            res = Node::rotate_left(res);
//        }

        return res;
    }

    int get (int position){
        if (position < this->number_of_left) return this->left->get(position);
        if (position >= this->number_of_left && position < this->number_of_left + this->number_of_copies){
            return this->val;
        }
        else return this->right->get(position - this->number_of_left - this->number_of_copies);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    std::cin.tie(NULL);

    int last_get = 0;
    int length = 0;
    int how_much_operation;
    Node* node = NULL;
    char operation;
    int value, count, position;

    std::cin >> how_much_operation;

    for (int i = 0; i < how_much_operation; i++){
        std::cin >> operation;

        //std::cout<< operation <<std::endl;
        if (operation == 'g'){
            // std::cout << "position" <<std::endl;
            std::cin >> position;
            position = (position + last_get) % length;
            last_get = node->get(position);
            std::cout << last_get << "\n";
        }
        else {
            std::cin >> position;
            std::cin >> value;
            std::cin >> count;

            if (!node){
                node = new Node(value, count, 0);
                length += count;
            }
            else {
                position = (position + last_get) % (length + 1);
                node = node->insert(value, count, position);
                length += count;
            }
        }
    }
    return 0;
}