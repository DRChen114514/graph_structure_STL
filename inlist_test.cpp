//这是一个简单的所有功能的演示，包括创建图、插入节点、访问节点、插入边、遍历邻接点、生成可视化 DOT 代码、删除边与节点、比较功能等。
#include "initlist.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Directed Graph Library Demo ===" << std::endl;

    // 1. 创建图 (支持 string 类型)
    directed_graph<std::string> graph;
    std::cout << "\n1. Graph created. Empty: " << (graph.empty() ? "Yes" : "No") << std::endl;

    // 2. 插入节点 (Insert)
    std::cout << "\n2. Inserting nodes...";
    graph.insert("Alice");
    graph.insert("Bob");
    auto [iter, success] = graph.insert("Charlie"); // 结构化绑定
    if (success) std::cout << " Charlie added." << std::endl;

    // 3. 访问节点 (Access & Find)
    std::cout << "\n3. Accessing nodes:";
    std::cout << " Node 0: " << graph["Alice"] << std::endl;
    
    auto it = graph.find("Bob");
    if (it != graph.end()) {
        std::cout << " Found Bob." << std::endl;
    }

    // 4. 插入边 (Edges)
    std::cout << "\n4. Creating edges...";
    graph.insert_edge("Alice", "Bob");
    graph.insert_edge("Alice", "Charlie");
    graph.insert_edge("Bob", "Charlie");
    std::cout << " Done." << std::endl;

    // 5. 遍历与查询邻接点 (Traversal & Adjacency)
    std::cout << "\n5. Adjacency list:" << std::endl;
    for (const auto& name : {"Alice", "Bob", "Charlie"}) {
        auto adj = graph.get_adjacent_nodes_values(name);
        std::cout << " " << name << " -> { ";
        for (const auto& n : adj) std::cout << n << " ";
        std::cout << "}" << std::endl;
    }

    // 6. 生成可视化 DOT 代码
    std::cout << "\n6. DOT Language Output (Copy & paste to https://dreampuf.github.io/GraphvizOnline):" << std::endl;
    std::cout << graph.to_dot("MySocialNetwork") << std::endl;

    // 7. 删除边与节点 (Erase)
    std::cout << "\n7. Removing edge Alice -> Bob...";
    graph.erase_edge("Alice", "Bob");
    
    std::cout << "\n8. Removing node Bob...";
    graph.erase("Bob");

    // 9. 最终状态
    std::cout << "\n9. Final state:" << std::endl;
    std::cout << graph.to_dot("FinalGraph") << std::endl;

    // 10. 比较功能 (Comparison)
    directed_graph<std::string> graph2;
    graph2.insert("Alice");
    graph2.insert("Charlie");
    graph2.insert_edge("Alice", "Charlie");

    std::cout << "\n10. Comparison: Graph == Graph2 -> " << (graph == graph2 ? "True" : "False") << std::endl;

    return 0;
}