#ifndef DIRECTED_GRAPH_HPP
#define DIRECTED_GRAPH_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <string>
#include <sstream>
#include <stdexcept>

template<typename T>
class directed_graph;

template<typename T>
class graph_node {
public:
    graph_node(directed_graph<T>* graph, const T& t);
    graph_node(directed_graph<T>* graph, T&& t);
    
    T& value() noexcept;
    const T& value() const noexcept;

    bool operator==(const graph_node& other) const {
        return m_graph == other.m_graph && m_data == other.m_data;
    }
    bool operator!=(const graph_node& other) const {
        return !(*this == other);
    }

    std::set<graph_node<T>*>& get_adjacent_nodes() { return m_adjacentNodes; }
    const std::set<graph_node<T>*>& get_adjacent_nodes() const { return m_adjacentNodes; }

private:
    friend class directed_graph<T>;
    directed_graph<T>* m_graph;
    T m_data;
    std::set<graph_node<T>*> m_adjacentNodes;
};

template<typename T>
class directed_graph {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    class const_iterator;
    class iterator;

    directed_graph() = default;
    ~directed_graph() = default;

    size_type size() const noexcept;
    bool empty() const noexcept;

    reference operator[](const T& node_value); 
    const_reference operator[](const T& node_value) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    std::pair<iterator, bool> insert(const T& node_value);
    std::pair<iterator, bool> insert(T&& node_value);
    bool erase(const T& node_value);
    bool insert_edge(const T& from, const T& to);
    bool erase_edge(const T& from, const T& to);
    void clear() noexcept;

    iterator find(const T& node_value);
    const_iterator find(const T& node_value) const;

    std::set<T> get_adjacent_nodes_values(const T& node_value) const;

    bool operator==(const directed_graph& rhs) const;
    bool operator!=(const directed_graph& rhs) const;

    std::string to_dot(const std::string& graph_name = "G") const;

private:
    friend class graph_node<T>;
    using nodes_container_type = std::vector<graph_node<T>>;
    nodes_container_type m_nodes;

    // 显式声明 find_node 返回类型，避免推导错误
    typename nodes_container_type::iterator find_node(const T& value);
    typename nodes_container_type::const_iterator find_node(const T& value) const;
    void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);
};

// ---------- 迭代器实现 ----------
template<typename T>
class directed_graph<T>::const_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    // 默认构造
    const_iterator() = default;
    // 从 vector 的 const_iterator 构造
    explicit const_iterator(typename nodes_container_type::const_iterator it) : m_it(it) {}

    reference operator*() const { 
        return m_it->value(); 
    }
    
    pointer operator->() const { 
        return &m_it->value(); 
    }

    const_iterator& operator++() { 
        ++m_it; 
        return *this; 
    }

    const_iterator operator++(int) { 
        auto tmp = *this; 
        ++(*this); 
        return tmp; 
    }

    bool operator==(const const_iterator& rhs) const { return m_it == rhs.m_it; }
    bool operator!=(const const_iterator& rhs) const { return m_it != rhs.m_it; }

private:
    typename nodes_container_type::const_iterator m_it;
    friend class directed_graph;
};

template<typename T>
class directed_graph<T>::iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator() = default;
    explicit iterator(typename nodes_container_type::iterator it) : m_it(it) {}

    reference operator*() const { 
        return m_it->value(); 
    }
    
    pointer operator->() const { 
        return &m_it->value(); 
    }

    iterator& operator++() { 
        ++m_it; 
        return *this; 
    }

    iterator operator++(int) { 
        auto tmp = *this; 
        ++(*this); 
        return tmp; 
    }

    bool operator==(const iterator& rhs) const { return m_it == rhs.m_it; }
    bool operator!=(const iterator& rhs) const { return m_it != rhs.m_it; }

private:
    typename nodes_container_type::iterator m_it;
    friend class directed_graph;
};

// ---------- graph_node 实现 ----------
template<typename T>
graph_node<T>::graph_node(directed_graph<T>* graph, const T& t) : m_graph(graph), m_data(t) {}

template<typename T>
graph_node<T>::graph_node(directed_graph<T>* graph, T&& t) : m_graph(graph), m_data(std::move(t)) {}

template<typename T>
T& graph_node<T>::value() noexcept { return m_data; }

template<typename T>
const T& graph_node<T>::value() const noexcept { return m_data; }

// ---------- directed_graph 实现 ----------
template<typename T>
typename directed_graph<T>::size_type directed_graph<T>::size() const noexcept { 
    return m_nodes.size(); 
}

template<typename T>
bool directed_graph<T>::empty() const noexcept { 
    return m_nodes.empty(); 
}

template<typename T>
typename directed_graph<T>::reference directed_graph<T>::operator[](const T& node_value) {
    auto it = find_node(node_value);
    if (it == m_nodes.end()) {
        // 插入并返回引用
        return insert(node_value).first.operator*();
    }
    return it->value();
}

template<typename T>
typename directed_graph<T>::const_reference directed_graph<T>::operator[](const T& node_value) const {
    auto it = find_node(node_value);
    if (it == m_nodes.end()) {
        throw std::out_of_range("Key not found");
    }
    return it->value();
}

template<typename T>
typename directed_graph<T>::iterator directed_graph<T>::begin() noexcept { 
    return iterator(m_nodes.begin()); 
}

template<typename T>
typename directed_graph<T>::iterator directed_graph<T>::end() noexcept { 
    return iterator(m_nodes.end()); 
}

template<typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::begin() const noexcept { 
    return const_iterator(m_nodes.begin()); 
}

template<typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::end() const noexcept { 
    return const_iterator(m_nodes.end()); 
}

// 核心修复：find_node
template<typename T>
typename directed_graph<T>::nodes_container_type::iterator 
directed_graph<T>::find_node(const T& value) {
    // 显式指定 lambda 参数类型为 const graph_node<T>&
    return std::find_if(m_nodes.begin(), m_nodes.end(), 
                        [&value](const typename nodes_container_type::value_type& node) { 
                            return node.value() == value; 
                        });
}

template<typename T>
typename directed_graph<T>::nodes_container_type::const_iterator 
directed_graph<T>::find_node(const T& value) const {
    return const_cast<directed_graph*>(this)->find_node(value);
}

// 核心修复：insert
template<typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const T& node_value) {
    auto it = find_node(node_value);
    if (it != m_nodes.end()) {
        return { iterator(it), false };
    }
    // emplace_back 返回引用，我们取其地址构造迭代器
    m_nodes.emplace_back(this, node_value);
    return { iterator(m_nodes.end() - 1), true };
}

template<typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(T&& node_value) {
    auto it = find_node(node_value);
    if (it != m_nodes.end()) {
        return { iterator(it), false };
    }
    m_nodes.emplace_back(this, std::move(node_value));
    return { iterator(m_nodes.end() - 1), true };
}

template<typename T>
bool directed_graph<T>::erase(const T& node_value) {
    auto it = find_node(node_value);
    if (it == m_nodes.end()) return false;
    remove_all_links_to(it);
    m_nodes.erase(it);
    return true;
}

template<typename T>
void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter) {
    // 获取要删除节点的指针
    const auto* target_ptr = &(*node_iter);
    for (auto& node : m_nodes) {
        // 从邻接表中擦除该指针
        // 注意：这里需要 const_cast 因为 set 的 key 是非 const 指针，但我们在 const_iterator 循环中
        node.get_adjacent_nodes().erase(const_cast<graph_node<T>*>(target_ptr));
    }
}

template<typename T>
bool directed_graph<T>::insert_edge(const T& from, const T& to) {
    auto from_it = find_node(from);
    auto to_it = find_node(to);
    if (from_it == m_nodes.end() || to_it == m_nodes.end()) return false;
    
    auto* to_ptr = &(*to_it);
    from_it->get_adjacent_nodes().insert(to_ptr);
    return true;
}

template<typename T>
bool directed_graph<T>::erase_edge(const T& from, const T& to) {
    auto from_it = find_node(from);
    auto to_it = find_node(to);
    if (from_it == m_nodes.end() || to_it == m_nodes.end()) return false;
    
    auto* to_ptr = &(*to_it);
    return from_it->get_adjacent_nodes().erase(to_ptr) > 0;
}

template<typename T>
void directed_graph<T>::clear() noexcept {
    m_nodes.clear();
}

template<typename T>
typename directed_graph<T>::iterator directed_graph<T>::find(const T& node_value) {
    return iterator(find_node(node_value));
}

template<typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::find(const T& node_value) const {
    return const_iterator(find_node(node_value));
}

template<typename T>
std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T& node_value) const {
    auto it = find_node(node_value);
    if (it == m_nodes.end()) return {};
    
    std::set<T> result;
    for (const auto* ptr : it->get_adjacent_nodes()) {
        result.insert(ptr->value());
    }
    return result;
}

template<typename T>
bool directed_graph<T>::operator==(const directed_graph& rhs) const {
    if (size() != rhs.size()) return false;
    for (const auto& node : m_nodes) {
        auto rhs_it = rhs.find_node(node.value());
        if (rhs_it == rhs.m_nodes.end()) return false;
        if (get_adjacent_nodes_values(node.value()) != rhs.get_adjacent_nodes_values(node.value())) 
            return false;
    }
    return true;
}

template<typename T>
bool directed_graph<T>::operator!=(const directed_graph& rhs) const {
    return !(*this == rhs);
}

template<typename T>
std::string directed_graph<T>::to_dot(const std::string& graph_name) const {
    std::stringstream ss;
    ss << "digraph " << graph_name << " {\n  rankdir=LR;\n";
    for (const auto& node : m_nodes) {
        auto adj = get_adjacent_nodes_values(node.value());
        if (adj.empty()) {
            ss << "  " << node.value() << ";\n";
        } else {
            for (const auto& target : adj) {
                ss << "  " << node.value() << " -> " << target << ";\n";
            }
        }
    }
    ss << "}\n";
    return ss.str();
}

#endif