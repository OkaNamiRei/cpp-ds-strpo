#include "ds/circle_list.hpp"

#include <fstream>
#include <stdexcept>
#include <utility>

namespace ds {

CircleList::Node::Node() : prev(nullptr), next(nullptr), data() {}

CircleList::Node::Node(Node* prev_node, Node* next_node, const Circle& circle)
    : prev(prev_node), next(next_node), data(circle) {
    if (prev != nullptr) {
        prev->next = this;
    }
    if (next != nullptr) {
        next->prev = this;
    }
}

CircleList::Node::~Node() {
    if (prev != nullptr) {
        prev->next = next;
    }
    if (next != nullptr) {
        next->prev = prev;
    }
}

CircleList::CircleList() : head_(), tail_(), size_(0) {
    init_empty();
}

CircleList::CircleList(const CircleList& other) : head_(), tail_(), size_(0) {
    init_empty();
    copy_from(*this, other);
}

CircleList::CircleList(CircleList&& other) noexcept : head_(), tail_(), size_(0) {
    init_empty();
    swap(other);
}

CircleList::~CircleList() {
    clear();
}

CircleList& CircleList::operator=(const CircleList& other) {
    if (this != &other) {
        CircleList copy(other);
        swap(copy);
    }
    return *this;
}

CircleList& CircleList::operator=(CircleList&& other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

void CircleList::init_empty() {
    head_.prev = nullptr;
    head_.next = &tail_;
    tail_.prev = &head_;
    tail_.next = nullptr;
    size_ = 0;
}

void CircleList::copy_from(CircleList& dst, const CircleList& src) {
    for (Node* node = src.head_.next; node != &src.tail_; node = node->next) {
        dst.push_back(node->data);
    }
}

void CircleList::swap(CircleList& other) noexcept {
    using std::swap;
    swap(head_.next, other.head_.next);
    swap(tail_.prev, other.tail_.prev);
    swap(size_, other.size_);

    if (head_.next == &other.tail_) {
        head_.next = &tail_;
        tail_.prev = &head_;
    } else {
        head_.next->prev = &head_;
        tail_.prev->next = &tail_;
    }

    if (other.head_.next == &tail_) {
        other.head_.next = &other.tail_;
        other.tail_.prev = &other.head_;
    } else {
        other.head_.next->prev = &other.head_;
        other.tail_.prev->next = &other.tail_;
    }
}

void CircleList::push_front(const Circle& circle) {
    new Node(&head_, head_.next, circle);
    ++size_;
}

void CircleList::push_back(const Circle& circle) {
    new Node(tail_.prev, &tail_, circle);
    ++size_;
}

bool CircleList::remove_first(const Circle& circle) {
    for (Node* node = head_.next; node != &tail_; node = node->next) {
        if (node->data == circle) {
            delete node;
            --size_;
            return true;
        }
    }
    return false;
}

std::size_t CircleList::remove_all(const Circle& circle) {
    std::size_t removed = 0;
    Node* node = head_.next;
    while (node != &tail_) {
        Node* next = node->next;
        if (node->data == circle) {
            delete node;
            --size_;
            ++removed;
        }
        node = next;
    }
    return removed;
}

void CircleList::clear() {
    Node* node = head_.next;
    while (node != &tail_) {
        Node* next = node->next;
        delete node;
        node = next;
    }
    init_empty();
}

void CircleList::sort_by_area() {
    if (size_ < 2) {
        return;
    }
    bool changed = true;
    while (changed) {
        changed = false;
        for (Node* node = head_.next; node->next != &tail_; node = node->next) {
            if (node->data.area() > node->next->data.area()) {
                std::swap(node->data, node->next->data);
                changed = true;
            }
        }
    }
}

std::size_t CircleList::size() const { return size_; }
bool CircleList::empty() const { return size_ == 0; }

void CircleList::save_to_file(const std::string& path) const {
    std::ofstream fout(path.c_str());
    if (!fout) {
        throw std::runtime_error("cannot open output file");
    }
    for (Node* node = head_.next; node != &tail_; node = node->next) {
        fout << node->data.center().x() << ' '
             << node->data.center().y() << ' '
             << node->data.radius() << '\n';
    }
}

void CircleList::load_from_file(const std::string& path) {
    std::ifstream fin(path.c_str());
    if (!fin) {
        throw std::runtime_error("cannot open input file");
    }
    clear();
    Circle circle;
    while (fin >> circle) {
        push_back(circle);
    }
}

std::ostream& operator<<(std::ostream& os, const CircleList& list) {
    os << "CircleList(size=" << list.size_ << ")";
    if (list.empty()) {
        os << " {}";
        return os;
    }
    os << " {\n";
    std::size_t index = 0;
    for (CircleList::Node* node = list.head_.next; node != &list.tail_; node = node->next) {
        os << "  [" << index++ << "] " << node->data << '\n';
    }
    os << '}';
    return os;
}

}  // namespace ds
