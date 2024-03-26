#include "boolmatrix.h"

// theory:
// TO-DO: add formulas for:
// 0) number of 1-good maps (known (n!)^2)
// 1) number of 1-structures (known n) 
// 2) number of good maps (known (n^2)!) 
// 3) number of (n - 1)-structures (known n!)
// 4) number for k-structures (**labeled** trees with n vertices and depth k)
// TO-DO: all (n - 1)-good maps for all n
// TO-DO: all k-good maps for all n (1 < k < n - 1)
// program:
// TO-DO: optimize with: 1) multithreading, 2) another algorithms, 3) micro-optimizations
// TO-DO: add functor for edges for countKGoodMaps and countMatricesWithScramblingIndexEqualToK 
// TO-DO: graphics for graph output

void countKGoodMaps(int n, int k, int edges = 0) {
    assert(k < n);

    std::vector<BoolMatrix> all_matrices = generateAllBoolMatrices(n);
    
    std::vector<BoolMatrix> good_matrices;
    for (const auto &matrix : all_matrices) {
        if (matrix.scrambling_index(k) == k && (edges == 0 || matrix.number_of_edges() == edges)) {
            good_matrices.push_back(matrix);
        }
    }

    int cnt = 0;
    std::vector<int> perm(n * n);
    std::iota(std::begin(perm), std::end(perm), 0);
    int iter = 0;
    do {
        bool is_kgood = true;
        for (const auto& good_matrix : good_matrices) {
            if (good_matrix.apply_perm(perm).scrambling_index(k) != k) {
                is_kgood = false;
                break;
            }
        }
        ++iter;
        cnt += (int)is_kgood;
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << "Number of " << k << "-good maps on matrices of size " << n << ": " << cnt << std::endl;
}

void countKGoodMapsOnKStructures(int n, int k) {
    countKGoodMaps(n, k, n);
}

void countMatricesWithScramblingIndexEqualToK(int n, int k, int edges = 0, bool verbose = false) {
    assert(k < n);

    std::vector<BoolMatrix> all_matrices = generateAllBoolMatrices(n);
    int cnt = 0;
    std::vector<BoolMatrix> good_matrices;

    for (const auto &matrix : all_matrices) {
        if (matrix.scrambling_index(k) == k && (edges == 0 || matrix.number_of_edges() == edges)) {
            ++cnt;
            if (verbose) {
                good_matrices.push_back(matrix);
            }
        }        
    }
    
    if (verbose) {
        for (const auto& matrix : good_matrices) {
            matrix.print();
            std::cout << '\n';
        }
    }

    std::cout << "Number of ";
    if (edges == n) {
        std::cout << k << "-structures on matrices of size ";
    } else if (edges != 0) {
        std::cout << "matrices with exactly " << edges << " edges and scrambling-index equal to " << k << " of size ";
    } else {
        std::cout << "matrices with scrambling-index equal to " << k << " of size ";
    }
    std::cout << n << ": " << cnt << std::endl;
}

void countKStructures(int n, int k, bool verbose = false) {
    countMatricesWithScramblingIndexEqualToK(n, k, n, verbose);
}

int main() {
    countKGoodMaps(3, 1);
    countKGoodMaps(3, 2);
    std::cout <<'\n';
    countKStructures(3, 1);
    countKStructures(3, 2);
    countKStructures(4, 1);
    countKStructures(4, 2);
    countKStructures(4, 3);
    std::cout << '\n';
    countMatricesWithScramblingIndexEqualToK(3, 1);
    countMatricesWithScramblingIndexEqualToK(3, 2);
    countMatricesWithScramblingIndexEqualToK(4, 1);
    countMatricesWithScramblingIndexEqualToK(4, 2);
    countMatricesWithScramblingIndexEqualToK(4, 3);

    return 0;
}