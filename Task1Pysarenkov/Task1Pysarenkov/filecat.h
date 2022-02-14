#pragma once

namespace filecat {
	struct File {
		int id;
		char _name[64];
		char _doc[11]; //ÄÄ.ÌÌ.ÐÐÐÐ
		int uses;
		File(int id, char const* name, char const* doc, int uses);
	};
	struct NodeList {
	private:
		struct Node {
			File* data;
			Node* next;
			Node(File* data);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		void addFirst(File& data);
		void addLast(File* data);
		void insertAfter(File* data, int id);
		void insertBefore(File* data, int id);
		void deleteByDate(char const* filedate);
		void mostUsed();
		void print();
	};
}