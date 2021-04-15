#include "pch.h"
#include "CppUnitTest.h"
#include "../Coding/iterator.h"
#include "../Coding/Shannon-Fano.h"
#include "../Coding/Shannon-Fano.cpp"
#include "../Coding/Linkedlist.h"
#include "../Coding/Linkedlist.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodingTest
{
	TEST_CLASS(CodingTest)
	{
	public:
		TEST_METHOD(bubble_sort)
		{
			string str = "133322";
			LinkedList* list = new LinkedList();
			char cur;
			for (size_t i = 0; i < str.length(); i++)
			{
				cur = str[i];
				if (!list->find(cur))
					list->push_back(cur);
			}
			// 1 3 2
			list->bubbleSort();
			// 3 2 1
			Iterator* curent = list->create_iterator();
			Assert::AreEqual(curent->freq(), 3);
			curent->next();
			Assert::AreEqual(curent->freq(), 2);
			curent->next();
			Assert::AreEqual(curent->freq(), 1);
			curent->next();
		}
		TEST_METHOD(Codingsymbols_1)
		{
			string str = "A";
			LinkedList* list = new LinkedList();
			char cur;
			cur = str[0];
			if (!list->find(cur))
				list->push_back(cur);
			// A
			int arr[1] = { 1 };
			char arrSym[1] = { 'A' };
			Coding_symbols(list, arr, arrSym, 1);
			Assert::AreEqual(list->findSymbol("0"), 'A');
		}
		TEST_METHOD(Codingsymbols)
		{
			string str = "333221";
			LinkedList* list = new LinkedList();
			char cur;
			for (size_t i = 0; i < str.length(); i++)
			{
				cur = str[i];
				if (!list->find(cur))
					list->push_back(cur);
			}
			// 3 2 1
			int arr[3] = { 3, 2, 1 };
			char arrSym[3] = { '3','2','1' };
			Coding_symbols(list, arr, arrSym, 3);
			Assert::AreEqual(list->findSymbol("0"), '3'); 
			Assert::AreEqual(list->findSymbol("10"), '2');
			Assert::AreEqual(list->findSymbol("11"), '1');
		}
		TEST_METHOD(ShanonFano)
		{
			// 4321
			// 32 41
			// 2 3 1 4
			// 11 10 01 00
			LinkedList* list = ShannonFanoCoding("4444133322");
			Iterator* curent = list->create_iterator();
			Assert::AreEqual(curent->code(), (string)"00"); // 4
			curent->next();
			Assert::AreEqual(curent->code(), (string)"10"); // 3
			curent->next();
			Assert::AreEqual(curent->code(), (string)"11"); // 2
			curent->next();
			Assert::AreEqual(curent->code(), (string)"01"); // 1
			curent->next();
		}
		TEST_METHOD(cooding_str)
		{
			string code = coding_string("hello");
			Assert::AreEqual(code, (string)"1011000001");
		}
		TEST_METHOD(decoding_st)
		{
			string code = decoding_code("hello wordl!", "0111001010101");
			Assert::AreEqual(code, (string)"word");
		}
		TEST_METHOD(failed_to_decode)
		{
			try
			{
				decoding_code("hello wordl!", "01110010101011");
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("failed to decode", error.what());
			}
		}
	};
}
