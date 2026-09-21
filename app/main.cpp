// Small demonstration driver for the algorithm analysis lab.
//
// It runs both implementations of all three problems on fixed inputs and
// reports whether the naive and efficient versions agree. Timing experiments
// live in benchmark/benchmark.cpp; this program only demonstrates correctness.

#include <iostream>
#include <string>
#include <vector>

#include "common.h"
#include "duplicate.h"
#include "frequency.h"

namespace {

bool report(const std::string& label, bool naive_matches_efficient) {
    std::cout << (naive_matches_efficient ? "[ok]   " : "[FAIL] ") << label << '\n';
    return naive_matches_efficient;
}

}  // namespace

int main() {
    using namespace algorithm_lab;

    bool all_agree = true;

    const std::vector<int> no_duplicates = {1, 2, 3, 4, 5};
    const std::vector<int> with_duplicates = {3, 1, 3, 2, 5};

    std::cout << "Problem 1 - duplicate detection\n";
    std::cout << "  {1,2,3,4,5}  naive=" << hasDuplicateNaive(no_duplicates)
              << " efficient=" << hasDuplicateEfficient(no_duplicates) << '\n';
    std::cout << "  {3,1,3,2,5}  naive=" << hasDuplicateNaive(with_duplicates)
              << " efficient=" << hasDuplicateEfficient(with_duplicates) << '\n';
    all_agree &= report("duplicate detection agrees",
                        hasDuplicateNaive(no_duplicates) == hasDuplicateEfficient(no_duplicates) &&
                            hasDuplicateNaive(with_duplicates) == hasDuplicateEfficient(with_duplicates));

    const std::vector<int> frequency_sample = {3, 1, 3, 2, 1, 3};
    const std::vector<int> tie_sample = {2, 1, 1, 2, 3, 4, 4};

    std::cout << "\nProblem 2 - most frequent value\n";
    std::cout << "  {3,1,3,2,1,3}    naive=" << mostFrequentNaive(frequency_sample)
              << " efficient=" << mostFrequentEfficient(frequency_sample) << '\n';
    std::cout << "  {2,1,1,2,3,4,4}  naive=" << mostFrequentNaive(tie_sample)
              << " efficient=" << mostFrequentEfficient(tie_sample)
              << "  (tie broken toward the smaller value)\n";
    all_agree &= report("most frequent value agrees",
                        mostFrequentNaive(frequency_sample) == mostFrequentEfficient(frequency_sample) &&
                            mostFrequentNaive(tie_sample) == mostFrequentEfficient(tie_sample));

    const std::vector<int> left = {1, 2, 2, 3};
    const std::vector<int> right = {2, 2, 4, 5};

    std::cout << "\nProblem 3 - distinct common elements\n";
    std::cout << "  {1,2,2,3} vs {2,2,4,5}  naive=" << countCommonDistinctNaive(left, right)
              << " efficient=" << countCommonDistinctEfficient(left, right) << '\n';
    all_agree &= report("common element count agrees",
                        countCommonDistinctNaive(left, right) == countCommonDistinctEfficient(left, right));

    std::cout << '\n'
              << (all_agree ? "All implementations agree. Run `make benchmark` for timing data.\n"
                            : "Implementations disagree; the benchmark would not be valid.\n");

    return all_agree ? 0 : 1;
}
