#include <string>
#include <iostream>
#include <Windows.h>
#include "filecat.h"

filecat::File* finput() {
	int id, uses;
	char filename[64];
	char doc[11];
	std::cout << "Введіть ID файлу\n";
	std::cin >> id;
	std::cout << "Введіть повну назву файлу\n";
	std::cin >> filename;
	std::cout << "Введіть дату створення файлу у форматі ДД.ММ.РРРР\n";
	std::cin >> doc;
	std::cout << "Введіть кількість використань файлу\n";
	std::cin >> uses;
	return (new filecat::File(id, filename, doc, uses));
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	filecat::NodeList list = filecat::NodeList();
	std::string oper;
	std::cout << "Яку операцію провести?\ninput - ввід елементів списку\nprint - вивід усього списку\nmused - вивід\
інформації про найбільш використовуваний файл\n\
delbyd - видалення файлів, дата створення яких менше заданої\nexit - вихід з програми\n";
	bool inp = false;
	for (;;) {
		std::cin >> oper;
		if (oper == "input") {
			std::cout << "Введіть 0, якщо хочете, щоб список був введений за замовчуванням, 1 - ввести вручну\n";
			int sw;
			std::cin >> sw;
			switch (sw)
			{
			case 0:
				list.addFirst(*(new filecat::File(1, "bibus.cpp", "25.05.2001", 45)));
				list.addFirst(*(new filecat::File(5, "amogus.cs", "27.07.2021", 228)));
				list.addLast(new filecat::File(2, "sus.cs", "27.07.2021", 200));
				list.addFirst(*(new filecat::File(3, "csgo.avi", "21.01.2012", 71)));
				list.addLast(new filecat::File(4, "newyear.doc", "01.01.2005", 15));
				list.insertAfter(new filecat::File(8, "what.png", "30.12.2009", 15), 4);
				list.insertBefore(new filecat::File(6, "sixyears.3gp", "01.05.2010", 15), 4);
				break;
			case 1:
				for (;;)
				{
					int sw1;
					std::cout << "Введіть 0, якщо хочете ввести перший елемент списку\n1 - ввести останній елемент\n\
2 - ввести елемент перед іншим із заданим ID\n3 - ввести елемент після іншого із заданим ID\n";
					std::cin >> sw1;
					switch (sw1) {
					case 0:
						list.addFirst(*finput());
						std::cout << "Файл занесений до списку успішно.\n";
						break;
					case 1:
						list.addLast(finput());
						std::cout << "Файл занесений до списку успішно.\n";
						break;
					case 2:
						int id;
						std::cout << "Введіть ID\n";
						std::cin >> id;
						list.insertBefore(finput(), id);
						std::cout << "Файл занесений до списку успішно.\n";
						break;
					case 3:
					{
						int id;
						std::cout << "Введіть ID\n";
						std::cin >> id;
						list.insertAfter(finput(), id);
						std::cout << "Файл занесений до списку успішно.\n";
						break;
					}
					default:
						std::cout << "Помилка.\n";
						break;
					}
					std::cout << "Бажаєте внести ще один елемент? Y - так, N - ні\n";
					char ans;
					std::cin >> ans;
					if (ans == 'Y')
						continue;
					else if (ans == 'N')
					{
						std::cout << "Повернення до головного меню\n";
						break;
					}
					else
						std::cout << "Помилка. Повернення до головного меню\n";
				}
				break;
			default:
				std::cout << "Помилка. Повернення до головного меню\n";
				break;
			}
		}
		else if (oper == "print")
		{
			list.print();
		}
		else if (oper == "mused")
		{
			list.mostUsed();
		}
		else if (oper == "delbyd") {
			std::cout << "Введіть дату у форматі ДД.ММ.РРРР. Якщо в каталозі є файли, створенні раніше цієї дати,\nто вони будуть видалені\
з каталогу\n";
			char filedate[11];
			bool fail = false;
			std::cin >> filedate;
			for (int i = 0; i < 10; i++) {
				if ((i == 2 || i == 5) && filedate[i] != '.')
				{
					fail = true;
					break;
				}
				else if (i != 2 && i != 5 && !isdigit(filedate[i])) {
					fail = true;
					break;
				}
			}
			if (fail) {
				std::cout << "Помилка вводу, спробуйте ще\n";
			}
			else {
				list.deleteByDate(filedate);
				std::cout << "Файли успішно видалені\n";
			}
		}
		else if (oper == "exit") {
			return 0;
		}
	}
}

