#include "Trie_tree.h"
#include <fstream>
#include <Windows.h>

void count_words(TrieTree t, std::string word, int n,int& count,int& result)
{
	auto check = [](char sym)
	{
		return sym == 'a' || sym == 'e' || sym == 'i' || sym == 'o' || sym == 'u' || sym == 'y';
	};

	if (t->eow&&count==n)
		result++;
	for (size_t i = 0; i < 26; ++i)
		if (t->ptrs[i])
		{
			if (check(char(i + 'a')))
				count++;
			if(count<=n)
				count_words(t->ptrs[i], word + char(i + 'a'), n,count,result);
			if (check(char(i + 'a')))
				count--;
		}
}

int task(TrieTree t,int n)
{
	int count=0,result=0;
	count_words(t, "", n, count, result);
	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ifstream file("words.txt");

	TrieTree root;
	init(root);

	std::string word;
	while (std::getline(file, word))
	{
		if (word.length())
			add(root, word, 0);
	}
	print(root, "");
	std::cout << "---------------------------------------\n";
	char IsExit;
	do
	{
		std::cout << "Введите количество гласных:\n";
		int n;
		std::cin >> n;
		std::cout << "Количество слов: " << task(root, n)<<'\n';
		std::cout << "Для того, чтобы продолжить программу нажмите Y\nДля выхода-любую другую клавишу\n";
		std::cin >> IsExit;
	} while (IsExit == 'Y' || IsExit == 'y');
	clear(root);
	std::cin.get();
	return 0;
}