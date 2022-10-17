#include "trie.h"

#include <algorithm>
using namespace common;


std::string TrieNode::getLongestPrefix(const std::string& key) const
{
    size_t start       = 0;
    size_t biggest_pos = 0;
    if (getLastMatching(std::vector<char>(std::begin(key), std::end(key)), start, biggest_pos))
    {
        return std::string(std::begin(key), std::begin(key) + biggest_pos);
    }
    return "";
}

void TrieNode::addString(const std::string& str)
{
    size_t start = 0;
    createPrefixPath(std::vector<char>(std::begin(str), std::end(str)), start);
}

std::vector<std::string> TrieNode::getCompletions(const std::string& key, bool get_estimates) const
{
    size_t start       = 0;
    size_t biggest_pos = 0;
    auto   child       = (getLastMatching(std::vector<char>(std::begin(key), std::end(key)), start, biggest_pos));
    if (!get_estimates && biggest_pos < key.size()) //we assume null-terminator
    {
        return std::vector<std::string>();
    }
    else
    {
        std::vector<char>        s(std::begin(key), std::begin(key) + biggest_pos);
        std::vector<std::string> results;
        collectChildPath(child, s, results);
        return results;
    }
}

TrieNode::ChildPtr TrieNode::getChild(const LabelType& l) const
{
    auto pair = std::equal_range(std::begin(mChildren), std::end(mChildren), ChildEntry({l, nullptr}));
    if (pair.first == pair.second)
    {
        return nullptr;
    }
    else
    {
        return pair.first->second;
    }
}

void TrieNode::collectChildPath(ChildPtr ptr, std::vector<char>& current_path, std::vector<std::string>& results) const
{
    if (!ptr)
    {
        return;
    }
    for (auto iter = std::begin(ptr->mChildren); iter != std::end(ptr->mChildren); ++iter)
    {
        current_path.push_back((*iter).first);
        if ((*iter).second->mWord)
        {
            results.push_back(std::string(std::begin(current_path), std::end(current_path)));
        }
        collectChildPath((*iter).second, current_path, results);

        current_path.pop_back();
    }
}

bool TrieNode::createPrefixPath(const std::vector<LabelType>& path, size_t& pos)
{
    if (pos >= path.size())
    {
        mWord = true;
        return true;
    }
    auto child_ptr = getChild(path[pos]);
    if (!child_ptr)
    {
        child_ptr = std::make_shared<TrieNode>();
        mChildren.push_back(std::make_pair(path[pos], child_ptr));
        std::sort(mChildren.begin(), mChildren.end());
    }
    return (child_ptr->createPrefixPath(path, ++pos));
}

TrieNode::ChildPtr TrieNode::getLastMatching(const std::vector<LabelType>& path, size_t& pos, size_t& biggest_pos) const
{
    if (pos >= path.size())
    {
        return nullptr;
    }
    auto child_ptr = getChild(path[pos]);
    if (nullptr == child_ptr)
    {
        return nullptr;
    }

    auto tree_child = child_ptr->getLastMatching(path, ++pos, biggest_pos);
    if (nullptr == tree_child)
    {
        biggest_pos = pos;
        return child_ptr;
    }
    return tree_child;
}
