#pragma once

#include <cassert>
#include <initializer_list>
#include <memory>
#include <array>
#include <string>
#include <iostream>

// ======================================== Array ========================================
template<typename T, size_t size>
class Array {
public:
	Array(const std::initializer_list<T>& init_list) {
		assert(init_list.size() == size);

		size_t i = 0;
		for (const auto& val : init_list) {
			_data[i++] = val;
		}
	}

	~Array() = default;

	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;
	Array(Array&&) = delete;
	Array& operator=(Array&&) = delete;

	template<typename T, size_t size>
	friend std::ostream& operator<<(std::ostream& os, const Array<T, size>& arr);

	T* begin() { return _data.get(); }
	T* end() { return _data.get() + size; }
private:
	std::unique_ptr<T[]> _data{ std::make_unique<T[]>(size) };
};

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const Array<T, size>& arr) {
	for (size_t i = 0; i < size; i++) {
		os << arr._data[i] << " ";
	}

	return os;
}

// ======================================== Linked List ========================================
template<typename T>
struct Node {
	Node(const T& data) :
		data(data), next_ptr(nullptr) {
		std::cout << "Node created with data : " << data << "\n";
	}
	~Node() {
		std::cout << "Node deleted with data : " << data << "\n";
	}

	T data{};
	Node* next_ptr{};
};

template<typename LinkedList>
class LinkedListIter {
public:
	using value_t = LinkedList::value_t;
	using referece_t = value_t&;
	using node_ptr_t = LinkedList::node_ptr_t;
public:
	LinkedListIter(node_ptr_t ptr) : _ptr(ptr) {}
	~LinkedListIter() = default;

	bool operator!=(const LinkedListIter& other) const { return _ptr != other._ptr; }
	bool operator==(const LinkedListIter& other) const { return _ptr == other._ptr; }
	referece_t operator*() { return _ptr->data; }

	LinkedListIter& operator++() {
		_ptr = _ptr->next_ptr;
		return *this;
	}

	LinkedListIter operator++(int) {
		LinkedListIter lliter = *this;
		++(*this);
		return lliter;
	}

private:
	node_ptr_t _ptr{};
};

template<typename T>
class LinkedList {
public:
	using value_t = T;
	using node_t = Node<T>;
	using node_ptr_t = Node<T>*;
	using iter_t = LinkedListIter<LinkedList<T>>;

public:
	LinkedList(const std::initializer_list<T>& lst) {

		for (const auto& data : lst) {
			Push(data);
		}
	}

	~LinkedList() {

		if (nullptr != _init_node_ptr) {
			node_ptr_t curr_node_ptr = _init_node_ptr;
			do {
				node_ptr_t next_node_ptr = curr_node_ptr->next_ptr;
				delete curr_node_ptr;
				curr_node_ptr = next_node_ptr;
			} while (nullptr != curr_node_ptr);
		}

	}

	void Push(const T& data) {

		node_ptr_t new_node_ptr = new Node<T>{ data };

		if (nullptr == _init_node_ptr) {
			_init_node_ptr = new_node_ptr;
		}
		else {
			node_ptr_t curr_node_ptr = _init_node_ptr;
			while (true) {
				if (nullptr == curr_node_ptr->next_ptr) {
					curr_node_ptr->next_ptr = new_node_ptr;
					break;
				}

				curr_node_ptr = curr_node_ptr->next_ptr;
			}
		}
	}

	LinkedList(const LinkedList&) = delete;
	LinkedList(LinkedList&&) = delete;
	LinkedList& operator=(const LinkedList&) = delete;
	LinkedList& operator=(LinkedList&&) = delete;

	iter_t begin() { return _init_node_ptr; }
	iter_t end() { return nullptr; }

	template<typename T>
	friend std::ostream& operator<<(std::ostream& ostr, const LinkedList<T>& llst);
private:
	node_ptr_t _init_node_ptr{ nullptr };
};

template<typename T>
std::ostream& operator<<(std::ostream& ostr, const LinkedList<T>& llst) {
	if (nullptr != llst._init_node_ptr) {
		typename LinkedList<T>::node_ptr_t curr_node_ptr = llst._init_node_ptr;
		do {
			std::cout << curr_node_ptr->data << " ";
			curr_node_ptr = curr_node_ptr->next_ptr;;
		} while (nullptr != curr_node_ptr);
	}

	return ostr;
}


void TestIterator() {
	// ======================================== Array ========================================
	std::array<int, 4> std_arr{ 1, 2, 3, 4 };

	std::cout << "STD::Array : ";
	for (std::array<int, 4>::iterator it = std_arr.begin(); it != std_arr.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

	Array<int, 4> arr{ 1, 2, 3, 4 };
	std::cout << "Array : " << arr << "\n";

	std::cout << "Array : ";
	for (auto val : arr) {
		std::cout << val << " ";
	}
	std::cout << "\n";

	// ======================================== Linked List ========================================
	LinkedList<std::string> llst{ "hello", "kavinda", "how", "are", "you"};

	std::cout << "LL Data : " << llst << "\n";

	std::cout << "LL Data : ";
	for (LinkedList<std::string>::iter_t it = llst.begin(); it != llst.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

	std::cout << "LL Data : ";
	for (const auto& data : llst) {
		std::cout << data << " ";
	}
	std::cout << "\n";
}
