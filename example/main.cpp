#include "trie.h"


#include <algorithm>
#include <format>
#include <iostream>
#include <ranges>

int main(int argc, char** argv) { 
	common::TrieNode trie;
  auto strings = {"anton",    "xaver", "rolinka", "adele", "adalbert",
                        "ada",   "agneta", "ara",     "abel",  "adagnate"};

	std::ranges::for_each(strings,
                              [&trie](const auto &s) { trie.addString(s); });
  
	//get all strings that start with the prefix
    std::cout << std::format("completions for '{}'\n", "ad");
	std::ranges::for_each(trie.getCompletions("ad"), [](const auto& s){ std::cout << s << std::endl;});


	std::cout << std::format("completions for '{}' with approximates\n", "adaa");
	std::ranges::for_each(trie.getCompletions("ad", true), [](const auto &s) {
          std::cout << s << std::endl;
        });
	return 0;
}