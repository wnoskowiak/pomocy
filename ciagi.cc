#include <iostream>
#include <memory>

class Node
{
public:
    int value, NoC, NoL, h = 1;

    Node *l, *r;

    Node(int val, int k, int nol) : value(val), NoC(k), NoL(nol), l(nullptr), r(nullptr){};

    static int getH(Node *node)
    {
        if (node)
        {
            return node->h;
        }
        else
        {
            return 0;
        }
    }

    static int branchDifference(Node *node)
    {
        if (node)
        {
            return (getH(node->l) - getH(node->r));
        }
        else
        {
            return 0;
        }
    }

    static Node *rotLeft(Node *root)
    {
        if (!root)
        {
            return root;
        }
        else if (!root->r)
        {
            return root;
        }
        else
        {
            Node *right = root->r;
            root->r = right->l;
            right->l = root;
            root->h = std::max(getH(root->l),
                               getH(root->r)) +
                      1;
            right->h = std::max(getH(right->l),
                                getH(right->r)) +
                       1;
            right->NoL += root->NoC + root->NoL;

            return right;
        }
    }

    static Node *rotRight(Node *root)
    {
        if (!root)
        {
            return root;
        }

        else if (!root->l)
        {
            return root;
        }
        else
        {
            Node *left = root->l;
            root->l = left->r;
            left->r = root;
            root->h = std::max(getH(root->l),
                               getH(root->r)) +
                      1;
            left->h = std::max(getH(left->l),
                               getH(left->r)) +
                      1;

            root->NoL -= left->NoC + left->NoL;
            return left;
        }
    }

    Node *insert(int valu, int count, int position)
    {
        Node *res = this;
        int balance;

        if (position <= this->NoL)
        {
            res->NoL += count;

            if (res->l)
                {res->l = res->l->insert(valu, count, position);}
            else
            {
                res->l = new Node(valu, count, 0);
            }

            res->h = std::max(getH(res->l),
                              getH(res->r)) +
                     1;
        }
        else if (res->NoL < position && position < res->NoL + res->NoC)
        {
            int how_much_left = position - res->NoL,
                how_much_right = NoC - how_much_left,
                old_value = res->value,
                old_index = res->NoL;
                

            res->NoC = count;
            res->value = valu;

            if (res->r)
                {res->r = res->r->insert(old_value, how_much_right, 0);}
            else
                {res->r = new Node(old_value, how_much_right, 0);
}
            if (res->l)
                {res = res->insert(old_value, how_much_left, old_index);}
            else
            {
                res->l = new Node(old_value, how_much_left, 0);
                res->NoL += how_much_left;
            }
        }
        else if (position >= res->NoL + res->NoC)
        {
            if (res->r)
                {res->r = res->r->insert(valu, count, position - res->NoL - res->NoC);}
            else
            {
                res = res;
                res->r = new Node(valu, count, 0);
            }

            res->h = std::max(getH(res->l),
                              getH(res->r)) +
                     1;
        }

        balance = branchDifference(res);

        if (balance < 0)
        {
            res = rotLeft(res);
        }
        else if (balance > 1)
        {
            res = rotRight(res);
        }
        return res;
    }

    int get(int pos)
    {
        if (pos >= this->NoL && pos < this->NoL + this->NoC)
        {
            return this->value;
        }
        if (pos < this->NoL)
        {
            return this->l->get(pos);
        }
        else
        {
            return this->r->get(pos - this->NoL - this->NoC);
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::cin.tie(NULL);

    Node *node = NULL;
    int last_get = 0, len = 0, nOfOps, valu, nOf, pos;
    char operation;

    std::cin >> nOfOps;

    for (int i = 0; i < nOfOps; i++)
    {
        std::cin >> operation;
        if (operation == 'g')
        {
            std::cin >> pos;
            pos = (pos + last_get) % len;
            last_get = node->get(pos);
            std::cout << last_get << "\n";
        }
        else
        {
            std::cin >> pos;
            std::cin >> valu;
            std::cin >> nOf;

            if (!node)
            {
                node = new Node(valu, nOf, 0);
                len += nOf;
            }
            else
            {
                pos = (pos + last_get) % (len + 1);
                node = node->insert(valu, nOf, pos);
                len += nOf;
            }
        }
    }
    return 0;
}