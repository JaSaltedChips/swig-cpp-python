#ifndef WORD_STORE_H
#define WORD_STORE_H

#include <string>
#include <vector>

class WordStore {
public:
    void add(const std::string& word);
    int count() const;
    std::string join(const std::string& sep) const;
    std::vector<std::string> words() const;
    const std::vector<std::string>& words_ref() const;

private:
    std::vector<std::string> words_;
};

int total_length(const std::vector<std::string>& items);

#endif
