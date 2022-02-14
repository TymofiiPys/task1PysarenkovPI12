#include "filecat.h"
#include <string>
#include <iostream>
filecat::File::File(int id, char const* name, char const* doc, int uses) {
	this->id = id;
	strcpy_s(_name, name);
	strcpy_s(_doc, doc);
	this->uses = uses;
}

void filecat::NodeList::addFirst(File& data) {
	Node* node = new Node(&data);
	if (head == nullptr) {
		head = node; tail = node; tail->next = nullptr;
	}
	else {
		node->next = head;
		head = node;
	}
}

void filecat::NodeList::addLast(File* data) {
	Node* node = new Node(data);
	if (head == nullptr) { head = node; tail = node; }
	else {
		tail->next = node;
		tail = node;
		tail->next = nullptr;
	}
}

void filecat::NodeList::insertAfter(File* data, int id)
{
	Node* node = new Node(data);
	if (head == nullptr) {
		head = node; tail = node; tail->next = nullptr;
	}
	else {
		Node* iter = head;
		while (iter != nullptr) {
			if (iter->data->id == id)
			{
				node->next = iter->next;
				iter->next = node;
				if (iter == tail)
				{
					tail = node;
					tail->next = nullptr;
				}
				return;
			}
			iter = iter->next;
		}
	}
}

void filecat::NodeList::insertBefore(File* data, int id)
{
	Node* node = new Node(data);
	if (head == nullptr) {
		head = node; tail = node; tail->next = nullptr;
	}
	else {
		Node* iter = head;
		Node* prev = nullptr;
		while (iter != nullptr) {
			if (iter->data->id == id)
			{
				node->next = iter;
				prev->next = node;
				return;
			}
			prev = iter;
			iter = iter->next;
		}
	}
}

void filecat::NodeList::print()
{
	if (head == nullptr) {
		std::cout << "В списку нема нічого" << std::endl;
	}
	Node* iter = head;
	while (iter != nullptr) {
		std::cout << iter->data->id << std::endl;
		std::cout << iter->data->_name << std::endl;
		std::cout << iter->data->_doc << std::endl;
		std::cout << iter->data->uses << std::endl << std::endl;
		iter = iter->next;
	}
}

void filecat::NodeList::deleteByDate(char const* filedate) {
	Node* iter = head;
	Node* prev = nullptr;
	std::string di, mi, yi, d, m, y;
	bool del;
	//Файли, дата створення яких буде менше визначеної нижче, видялятимуться
	for (int i = 0; i < 10; i++) {
		if (i >= 0 && i < 2)
		{
			d += filedate[i];
		}
		else if (i > 2 && i < 5)
		{
			m += filedate[i];
		}
		else if (i > 5)
		{
			y += filedate[i];
		}
	}
	while (iter != nullptr) {
		di = "", mi = "", yi = "";
		del = false;
		//Розкладаємо дату створення файлу-елемента списку
		for (int i = 0; i < 10; i++) {
			if (i >= 0 && i < 2)
			{
				di += iter->data->_doc[i];
			}
			else if (i > 2 && i < 5)
			{
				mi += iter->data->_doc[i];
			}
			else if (i > 5)
			{
				yi += iter->data->_doc[i];
			}
		}
		//Порівнюємо дати
		if (yi == y)
		{
			if (mi == m) {
				if (di < d) {
					if (iter == head) {
						if (head == tail)
							head = nullptr;
						else {
							head = iter->next;
						}
					}
					else {
						prev->next = iter->next;
					}
					del = true;
				}
			}
			else if (mi < m) {
				if (iter == head) {
					if (head == tail)
						head = nullptr;
					else {
						head = iter->next;
					}
				}
				else {
					prev->next = iter->next;
				}del = true;
			}
		}
		else if (yi < y) {
			//тут шось із видаленням буде
			if (iter == head) {
				if (head == tail)
					head = nullptr;
				else {
					head = iter->next;
				}
			}
			else {
				prev->next = iter->next;
			}del = true;
		}
		if (!del)
		{
			prev = iter;
		}
		iter = iter->next;
	}
}

void filecat::NodeList::mostUsed() {
	int max = -1, idmax = -1;
	Node* iter = head;
	while (iter != nullptr) {
		if (iter->data->uses > max) {
			max = iter->data->uses;
			idmax = iter->data->id;
		}
		iter = iter->next;
	}
	iter = head;
	while (iter != nullptr) {
		if (iter->data->id == idmax) {
			std::cout << "Найбільш використовуваний файл (id, назва, кількість використань):" << std::endl;
			std::cout << iter->data->id << std::endl;
			std::cout << iter->data->_name << std::endl;
			std::cout << iter->data->uses << std::endl;
			break;
			//виводим інфу про файл
		}
		iter = iter->next;
	}
}

filecat::NodeList::Node::Node(File* data)
{
	this->data = data;
}
