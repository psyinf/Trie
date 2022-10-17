#pragma once


#include <memory>
#include <string>
#include <vector>


namespace common
{
/**
 * Trie (https://de.wikipedia.org/wiki/Trie) data-structure to optimize searching longest prefixes in a list of candidates. Usually used for looking up auto-completion strings in set of candidates.
 */
class TrieNode
{

public:
    TrieNode() = default;

    /**
	 * \brief	Gets longest matching prefix from the key.
	 * \param	key	The key to be searched for .
	 * \return	The longest prefix.
	 */
    std::string getLongestPrefix(const std::string& key) const;

    /**
	 * \brief	Adds a string to the Trie
	 * \param	str	The string.
	 */
    void addString(const std::string& str);
    
   
    /**
	 * \brief	Retrieve completions of prefixes.
	 * \param	key			 	The key.
	 * \param	get_estimates	If set, prefixes longer than the actual entries will produce results 
	 * 							(e.g. looking for "abcd" will return all abcXXXX)
	 * \return	The completions.
	 */
    std::vector<std::string> getCompletions(const std::string& key, bool get_estimates = false) const;

private:
    using LabelType  = char;
    using ChildPtr   = std::shared_ptr<TrieNode>;
    using ChildEntry = std::pair<LabelType, ChildPtr>;

    friend bool operator<(const ChildEntry& a, const ChildEntry& b)
    {
        return a.first < b.first;
    }

    std::vector<ChildEntry> mChildren;
    bool                    mWord = false;


    ChildPtr getChild(const LabelType& l) const;

    void collectChildPath(ChildPtr ptr, std::vector<char>& current_path, std::vector<std::string>& results) const;

    bool createPrefixPath(const std::vector<LabelType>& path, size_t& pos);

    ChildPtr getLastMatching(const std::vector<LabelType>& path, size_t& pos, size_t& biggest_pos) const;
};
} // namespace common