#include <list>
#include <iostream>
#include <queue>
#include <string>

struct CharFreqPair
{
    char character;
    unsigned frequency;
};
struct Node
{
    CharFreqPair pair;

    Node *leftChild;
    Node *rightChild;

    inline explicit Node(CharFreqPair const &_pair) noexcept
    {
        pair = _pair;

        leftChild = nullptr;
        rightChild = nullptr;
    }
    inline Node(const Node &_node)
    {
        *this = _node;
    }
    bool leaf() const
    {
        return leftChild == nullptr and rightChild == nullptr;
    }
};

// overloading std::less for node *
namespace std
{
    template <>
    struct less<Node *>
    {
        bool operator()(Node const *const &_node1, Node const *const &_node2)
        {
            return _node1->pair.frequency > _node2->pair.frequency;
        }
    };
}

Node *build_huffman_tree(std::list<CharFreqPair> const &_listOfCharacters)
{
    std::priority_queue<Node *> queue;

    for (const auto &pair : _listOfCharacters)
    {
        queue.push(new Node(pair));
    }

    while (queue.size() > 1)
    {
        Node *parent = new Node({'\0', 0});

        auto const leftChild = queue.top();
        parent->leftChild = leftChild;
        queue.pop();

        auto const rightChild = queue.top();
        parent->rightChild = rightChild;
        queue.pop();

        parent->pair.frequency = leftChild->pair.frequency + rightChild->pair.frequency;
        queue.push(parent);
    }

    return queue.top();
}

struct CharCodePair
{
    char character;
    std::string code;
};

void assign_codes(Node const *const &_node, std::list<CharCodePair> &_list, std::string _code)
{
    if (_node->leaf())
    {

        _list.push_back(CharCodePair({_node->pair.character, _code}));
        return;
    }
    else
    {
        assign_codes(_node->leftChild, _list, _code + "0");
        assign_codes(_node->rightChild, _list, _code + "1");
    }
}

void print_codes(std::list<CharCodePair> const &_list)
{
    for (const auto &pair : _list)
    {
        std::cout << '{' << pair.character << ", " << pair.code << "}\n";
    }
}

int main(void)
{

    std::list<CharFreqPair> charFreqList;
    for (char c = 'a'; c <= 'z'; ++c)
    {
        CharFreqPair pair;
        pair.character = c;
        pair.frequency = rand();
        charFreqList.push_back(pair);
    }

    const auto tree = build_huffman_tree(charFreqList);

    std::list<CharCodePair> charCodeList;
    assign_codes(tree, charCodeList, "");
    print_codes(charCodeList);
}
