# Graph Structure STL

> A lightweight, type-safe C++ template library for directed graphs with STL-like interfaces.

## 📖 Introduction

**Graph Structure STL** 是我在华南理工大学大一期间完成的第一个开源项目，也是一次对现代 C++ 模板编程和数据结构设计的实践探索。

该项目实现了一个轻量级的 **有向图（Directed Graph）模板库**，采用邻接表存储结构，并结合 **`std::vector` + `std::set`** 管理图数据。为了保证节点和边在插入、删除等操作后的引用稳定性，库引入了 **Pointer Mapping（指针映射）** 机制，在保持较高效率的同时避免迭代器和对象引用失效的问题。

此外，项目支持 **Graphviz DOT 格式导出**，可方便地对图结构进行可视化；同时提供了 **STL 风格迭代器接口** 与 **类型安全（Type Safety）** 的设计，使其既适合作为图算法实验平台，也适用于学习现代 C++ 数据结构设计。

## ✨ Features

* 🚀 Lightweight header-only template library
* 📌 Directed graph implementation based on adjacency lists
* 🔒 Pointer mapping for stable node and edge references
* 🔄 STL-like iterator interfaces
* 🛡️ Type-safe template design
* 📊 Graphviz DOT export for visualization
* 📚 Suitable for graph algorithm learning and experimentation
* ⚡ Easy to integrate into existing C++ projects

## 🎯 Design Goals

* 提供一个简洁、现代的 C++ 图数据结构实现
* 保证图对象在动态修改过程中的稳定性
* 提供符合 STL 使用习惯的接口
* 方便图算法开发、课程实验与竞赛练习
* 支持可视化调试，提高开发效率

## 📦 Use Cases

* 图论算法学习
* 数据结构课程实验
* ACM / ICPC 算法练习
* 图结构可视化
* C++ 模板编程学习

## ❤️ About

This repository represents my first open-source project as a freshman at **South China University of Technology (SCUT)**. Although it is a learning-oriented project, I hope it can be useful to anyone interested in graph algorithms, generic programming, and modern C++.

Contributions, suggestions, and discussions are always welcome!
