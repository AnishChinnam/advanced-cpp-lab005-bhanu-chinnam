#include "frequency.h"

#include <stdexcept>
#include <unordered_map>

namespace algorithm_lab {

int mostFrequentNaive(const std::vector<int>& values) {
    if (values.empty()) {
        throw std::invalid_argument("values must not be empty");
    }

    int best_value = values.front();
    int best_count = 0;

    for (std::size_t i = 0; i < values.size(); ++i) {
        int current = values[i];
        int count = 0;
        for (std::size_t j = 0; j < values.size(); ++j) {
            if (values[j] == current) {
                ++count;
            }
        }

        if (count > best_count || (count == best_count && current < best_value)) {
            best_count = count;
            best_value = current;
        }
    }

    return best_value;
}

int mostFrequentEfficient(const std::vector<int>& values) {
    if (values.empty()) {
        throw std::invalid_argument("values must not be empty");
    }

    // One pass over the input builds the frequency table. Each insert and each
    // lookup is expected constant time, so building the table is O(n) average
    // case instead of the O(n^2) rescanning the naive version performs.
    std::unordered_map<int, int> counts;
    for (int value : values) {
        ++counts[value];
    }

    // A second pass over the distinct values picks the winner. The tie-breaking
    // rule matches mostFrequentNaive: on equal counts the smaller value wins,
    // which keeps the two implementations comparable.
    int best_value = values.front();
    int best_count = 0;

    for (const auto& entry : counts) {
        int value = entry.first;
        int count = entry.second;
        if (count > best_count || (count == best_count && value < best_value)) {
            best_count = count;
            best_value = value;
        }
    }

    return best_value;
}

}
