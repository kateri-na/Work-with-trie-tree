#pragma once
#include <string>
#include <iostream>

struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
	root = nullptr;
}

bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;
	}
	if (word.length() - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i+1);
}

bool all_ptr_empty(TrieTree t)
{
	bool result = true;
	size_t i = 0;
	while (i < 26 && result)
		if (!t->ptrs[i])
			++i;
		else
			result = false;
	return result;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void print(TrieTree t, std::string word)
{
	if (t->eow)
		std::cout << word << '\n';
	for (size_t i = 0; i < 26; ++i)
		if (t->ptrs[i])
			print(t->ptrs[i], word + char(i + 'a'));
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)
		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}