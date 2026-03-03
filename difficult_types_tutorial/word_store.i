%module wordstore

%{
#include "word_store.h"
%}

%include <std_string.i>
%include <std_vector.i>

%template(StringVector) std::vector<std::string>;

class WordStore {
public:
    void add(const std::string& word);
    int count() const;
    std::string join(const std::string& sep) const;
    std::vector<std::string> words() const;
    const std::vector<std::string>& words_ref() const;
};

int total_length(const std::vector<std::string>& items);
