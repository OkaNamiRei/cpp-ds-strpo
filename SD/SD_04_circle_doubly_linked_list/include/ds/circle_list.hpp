#pragma once

#include "ds/circle.hpp"

#include <cstddef>
#include <iosfwd>
#include <string>

namespace ds {

class CircleList {
public:
    CircleList();
    CircleList(const CircleList& other);
    CircleList(CircleList&& other) noexcept;
    ~CircleList();

    CircleList& operator=(const CircleList& other);
    CircleList& operator=(CircleList&& other) noexcept;

    void push_front(const Circle& circle);
    void push_back(const Circle& circle);

    bool remove_first(const Circle& circle);
    std::size_t remove_all(const Circle& circle);
    void clear();

    void sort_by_area();

    std::size_t size() const;
    bool empty() const;

    void save_to_file(const std::string& path) const;
    void load_from_file(const std::string& path);

    friend std::ostream& operator<<(std::ostream& os, const CircleList& list);

private:
    class Node {
    public:
        Node();
        Node(Node* prev, Node* next, const Circle& circle);
        ~Node();

        Node* prev;
        Node* next;
        Circle data;
    };

    Node head_;
    Node tail_;
    std::size_t size_;

    void init_empty();
    static void copy_from(CircleList& dst, const CircleList& src);
    void swap(CircleList& other) noexcept;
};

}  // namespace ds
