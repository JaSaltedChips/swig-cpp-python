#include "word_store.h"

#include <sstream>

void WordStore::add(const std::string& word) {
    // Store a new word in insertion order.
    words_.push_back(word);
}

int WordStore::count() const {
    // Return the current number of stored words.
    return static_cast<int>(words_.size());
}

std::string WordStore::join(const std::string& sep) const {
    // Join all words with a caller-provided separator.
    std::ostringstream out;
    for (size_t i = 0; i < words_.size(); ++i) {
        if (i > 0) {
            out << sep;
        }
        out << words_[i];
    }
    return out.str();
}

std::vector<std::string> WordStore::words() const {
    // Return a copy so Python owns the result safely.
    return words_;
}

const std::vector<std::string>& WordStore::words_ref() const {
    // Return a reference to internal storage (caller must keep this object alive).
    return words_;
}

int total_length(const std::vector<std::string>& items) {
    // Sum the lengths of all strings in the input list.
    int total = 0;
    for (const auto& item : items) {
        total += static_cast<int>(item.size());
    }
    return total;
}
