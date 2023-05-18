#include <iostream>
#include <vector>
#include <time.h>

struct node {
    int data;
    node* left;
    node* right;
    node(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    node* root;
    size_t size;

    void print_tree(node* root) const{
        if (!root)
        {
            std::cout << "null" << std::endl;
            return;
        }
        std::cout << root->data << std::endl;
        print_tree(root->left);
        print_tree(root->right);
    }

    node* r_insert(node*& tmp, int value) {
        if (!tmp) {
            tmp = new node(value);
            return tmp;
        }
        if (tmp->data > value) {
            tmp->left = r_insert(tmp->left, value);
        }
        if (tmp->data < value) {
            tmp->right = r_insert(tmp->right, value);
        }
        return tmp;
    }

    node* min(node* root)
    {
        if (!root->left) { return root; }
        return min(root->left);
    }

    node* r_erase(node*& root, int value) {
        if (!root) {
            return root;
        }
        if (value < root->data) {
            root->left = r_erase(root->left, value);
        }
        else if (value > root->data) {
            root->right = r_erase(root->right, value);
        }
        else if (root->left && root->right)
        {
            root->data = min(root->right)->data;
            root->right = r_erase(root->right, root->data);
        }
        else
        {
            if (root->left) {
                root = root->left;
            }
            else if (root->right) {
                root = root->right;
            }
            else {
                return nullptr;
            }

        }
        return root;

    }

    node* copy(node* new_root) {
        if (!new_root) {
            return nullptr;
        }
        node* temp = new node(new_root->data);
        temp->left = copy(new_root->left);
        temp->right = copy(new_root->right);
        return temp;
    }
    void r_clear(node* root) {
        if (root->left) {
            r_clear(root->left);
        }
        if (root->right) {
            r_clear(root->right);
        }
        root = nullptr;
    }

public:
    BinaryTree() : root(nullptr), size(0) {}

    BinaryTree(const BinaryTree& second_root) {
        if (!second_root.root) {
            r_clear(root);
            delete root;
        }
        else {
            if (!root) {
                root = copy(second_root.root);
            }
            else {
                r_clear(root);
                delete root;
                root = copy(second_root.root);
            }
        }
    }

    ~BinaryTree() {
        if (root) {
            r_clear(root);
            delete root;
        }

    }

    BinaryTree(int key)
    {
        root = new node(key);
        size = 1;
    }

    BinaryTree& operator=(const BinaryTree& new_root) {
        if (!new_root.root) {
            r_clear(root);
            delete root;
            return *this;
        }
        else {
            if (!root) {
                root = copy(new_root.root);
            }
            else {
                r_clear(root);
                delete root;
                root = copy(new_root.root);
            }
            return *this;
        }
    }

    void print(){
        print_tree(root);
    }

    bool insert(int value) {
        if (contains(value))
            return false;
        return r_insert(root, value);
    }

    bool contains(int key) {
        node* tmp = root;
        while (tmp && tmp->data != key) {
            if (tmp->data > key) {
                tmp = tmp->left;
            }
            else
                tmp = tmp->right;
        }
        return tmp;
    }

    bool erase(int value) {
        if (!contains(value))
            return false;
        return r_erase(root, value);
    }

    void clear() {
        r_clear(root);
    }
};

//задание
std::vector<int> repeat_element(const std::vector<int>& vec) {
    BinaryTree tree;
    std::vector<int> result;
    bool flag;
    for (int i = 0; i < vec.size(); i++) {
        flag = tree.insert(vec[i]);
        if (!flag && (std::find(result.begin(), result.end(), vec[i]) == result.end())) 
            result.push_back(vec[i]);
    }
     return result;
    }

//для теста
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

double avg100(const double* arr) {
    double sum = 0;
    for (size_t i = 0; i < 100; ++i) {
        sum += arr[i];
    }
    return sum / 100;
}

double avg1000(const double* arr) {
    double sum = 0;
    for (size_t i = 0; i < 1000; ++i) {
        sum += arr[i];
    }
    return sum / 1000;
}

int main()
{
    BinaryTree tree;
    tree.insert(20);
    tree.insert(45);
    tree.insert(10);
    tree.insert(7);
    tree.insert(15);
    tree.insert(30);
    tree.insert(80);
    tree.print();
    std::cout << std::endl;
    tree.erase(7);
    tree.erase(20);
    tree.print();
    std::cout << std::endl;
    
    std::cout << "Contains 10: " << tree.contains(10) << std::endl;
    std::cout << "Contains 21: " << tree.contains(21) << std::endl;

    //задание
    std::vector<int> vec = {1, 9, 8, 8, 8, 9, 7, 3, 3, 3, 5, 10};
    auto vec1 = repeat_element(vec);
    std::cout << "Repeating elements:" << std::endl;
    for (auto i : vec1) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;

   /* //ТЕСТ
   BinaryTree tree_1000, tree_10000, tree_100000;
   std::vector<int> vector_1000, vector_10000, vector_100000;

   double vect_attempts_1000[100], vect_attempts_10000[100], vect_attempts_100000[100];
   double set_attempts_1000[100], set_attempts_10000[100], set_attempts_100000[100];

   //ЗАПОЛНЕНИЕ НА 1000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;

	   //start
	   clock_t begin = clock();
	   while (counter != 1000) {
		   tree_1000.insert(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end

	   if (i != 99) { tree_1000.clear(); }
	   set_attempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill tree with 1000 elem: " << avg100(set_attempts_1000) << std::endl;

   //ЗАПОЛНЕНИЕ НА 10000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;
	   //start
	   clock_t begin = clock();
	   while (counter != 10000) {
		   tree_10000.insert(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end
	   if (i != 99) { tree_10000.clear(); }
	   set_attempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill tree with 10000 elem: " << avg100(set_attempts_10000) << std::endl;

   //ЗАПОЛНЕНИЕ НА 100000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;
	   //start
	   clock_t begin = clock();
	   while (counter != 100000) {
		   tree_100000.insert(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end
	   if (i != 99) { tree_100000.clear(); }
	   set_attempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill tree with 100000 elem: " << avg100(set_attempts_100000) << std::endl;

   std::cout << "-------------------------------------------------------------------" << std::endl;

   //ЗАПОЛНЕНИЕ std::vector НА 1000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;
	   //start
	   clock_t begin = clock();
	   while (counter != 1000) {
		   vector_1000.push_back(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end
	   if (i != 99) { vector_1000.clear(); }
	   vect_attempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill vector with 1000 elem: " << avg100(vect_attempts_1000) << std::endl;

   //ЗАПОЛНЕНИЕ std::vector НА 10000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;
	   //start
	   clock_t begin = clock();
	   while (counter != 10000) {
		   vector_10000.push_back(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end
	   if (i != 99) { vector_10000.clear(); }
	   vect_attempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill vector with 10000 elem: " << avg100(vect_attempts_10000) << std::endl;

   //ЗАПОЛНЕНИЕ std::vector НА 100000
   for (size_t i = 0; i < 100; ++i) {
	   int counter = 0;
	   //start
	   clock_t begin = clock();
	   while (counter != 100000) {
		   vector_100000.push_back(lcg());
		   ++counter;
	   }
	   clock_t end = clock();
	   //end
	   if (i != 99) { vector_100000.clear(); }
	   vect_attempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to fill vector with 100000 elem: " << avg100(vect_attempts_100000) << std::endl;

   std::cout << "-------------------------------------------------------------------" << std::endl;

   double findattempts_1000[1000], findattempts_10000[1000], findattempts_100000[1000];
   //ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 1000
   for (size_t i = 0; i < 1000; ++i) {
	   //start
	   clock_t begin = clock();
	   tree_1000.contains(lcg());
	   clock_t end = clock();
	   //end

	   findattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in tree with 1000 elem: " << avg1000(findattempts_1000) << std::endl;

   //ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 10000
   for (size_t i = 0; i < 1000; ++i) {
	   //start
	   clock_t begin = clock();
	   tree_10000.contains(lcg());
	   clock_t end = clock();
	   //end

	   findattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in tree with 10000 elem: " << avg1000(findattempts_10000) << std::endl;

   //ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 100000
   for (size_t i = 0; i < 1000; ++i) {
	   //start
	   clock_t begin = clock();
	   tree_100000.contains(lcg());
	   clock_t end = clock();
	   //end

	   findattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in tree with 100000 elem: " << avg1000(findattempts_100000) << std::endl;

   std::cout << "-------------------------------------------------------------------" << std::endl;

   double vfindattempts_1000[1000], vfindattempts_10000[1000], vfindattempts_100000[1000];
   //ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 1000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   for (size_t i = 0; i < vector_1000.size(); ++i) {
		   if (vector_1000[i] == elem) { break; }
	   }
	   clock_t end = clock();
	   //end

	   vfindattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in std::vector with 1000 elem: " << avg1000(vfindattempts_1000) << std::endl;

   //ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 10000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   for (size_t i = 0; i < vector_10000.size(); ++i) {
		   if (vector_10000[i] == elem) { break; }
	   }
	   clock_t end = clock();
	   //end

	   vfindattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in std::vector with 10000 elem: " << avg1000(vfindattempts_10000) << std::endl;

   //ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 100000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   for (size_t i = 0; i < vector_100000.size(); ++i) {
		   if (vector_100000[i] == elem) { break; }
	   }
	   clock_t end = clock();
	   //end

	   vfindattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to find elem in std::vector with 100000 elem: " << avg1000(vfindattempts_100000) << std::endl;

   std::cout << "-------------------------------------------------------------------" << std::endl;

   double add_del_attempts_1000[1000], add_del_attempts_10000[1000], add_del_attempts_100000[1000];
   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 1000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   tree_1000.insert(elem);
	   tree_1000.erase(elem);
	   clock_t end = clock();
	   //end

	   add_del_attempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in set with 1000 elem: " << avg1000(add_del_attempts_1000) << std::endl;

   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 10000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   tree_10000.insert(elem);
	   tree_10000.erase(elem);
	   clock_t end = clock();
	   //end

	   add_del_attempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in set with 10000 elem: " << avg1000(add_del_attempts_10000) << std::endl;

   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 100000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   tree_100000.insert(elem);
	   tree_100000.erase(elem);
	   clock_t end = clock();
	   //end

	   add_del_attempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in set with 100000 elem: " << avg1000(add_del_attempts_100000) << std::endl;

   std::cout << "-------------------------------------------------------------------" << std::endl;

   double add_del_vecattempts_1000[1000], add_del_vecattempts_10000[1000], add_del_vecattempts_100000[1000];
   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 1000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   vector_1000.push_back(elem);
	   vector_1000.pop_back();
	   clock_t end = clock();
	   //end

	   add_del_vecattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in std::vector with 1000 elem: " << avg1000(add_del_vecattempts_1000) << std::endl;

   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 10000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   vector_10000.push_back(elem);
	   vector_10000.pop_back();
	   clock_t end = clock();
	   //end

	   add_del_vecattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in std::vector with 10000 elem: " << avg1000(add_del_vecattempts_10000) << std::endl;

   //ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 100000
   for (size_t i = 0; i < 1000; ++i) {
	   int elem = lcg();
	   //start
	   clock_t begin = clock();
	   vector_100000.push_back(elem);
	   vector_100000.pop_back();
	   clock_t end = clock();
	   //end

	   add_del_vecattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
   }
   std::cout << "Average time to add and delete elem in std::vector with 100000 elem: " << avg1000(add_del_vecattempts_100000) << std::endl;
   */
}
