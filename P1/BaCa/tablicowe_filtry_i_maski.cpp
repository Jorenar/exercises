// Jakub Lukasiewicz

#include <iostream>

int main()
{
    int n, mask_len, step, idx_first, idx_last;
    double arr[10000], active[10000], mask[21], distribution[21];
    char filter;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cin >> mask_len;

    for (int i = 0; i < mask_len; ++i) {
        std::cin >> distribution[i];
    }

    std::cin >> step >> idx_first >> idx_last >> filter;
    step++; // not how many items are between idexes, but how much one is supposed to in- or decrement

    int x, y, z; // x, y - iterators; z - length of active[] array
    x = y = z = idx_last > idx_first ? idx_last - idx_first + 1 : n - idx_first + idx_last + 1;

    int mask_mid = mask_len / 2; // in the middle of mask is the element for which is mask

    double mask_sum, temp; // mask_sum both for 'r' and 'w', temp for 'm'

    int idx0 = idx_first;
    while (y--) {
        active[z - y - 1] = arr[idx0];
        idx0 = (idx0 + 1) % n;
    }

    int p, idx2;

    int idx = idx_first;

    while (x--) {
        // Create mask
        mask[mask_mid] = arr[idx];
        for (int i = 1; i <= mask_mid; ++i) {
            p = i * step; // how far is the jump to the next element from idx0
            idx0 = idx2 = z - x - 1; // idx0 is reused!
            while (p--) {
                if (!idx2) {
                    idx2 = z;
                }
                idx2--;
            }
            mask[mask_mid - i] = active[idx2];                    // left half of mask
            mask[mask_mid + i] = active[( idx0 + i * step ) % z]; // right half of mask
        }

        mask_sum = 0;
        if (filter == 'r') {
            for (int i = 0; i < mask_len; ++i) {
                mask_sum += mask[i];
            }
            arr[idx] = mask_sum / mask_len;
        }
        else if (filter == 'm') {
            for (int i = 0; i < mask_len; ++i) {
                for (int j = 0; j < mask_len; ++j) {
                    if (mask[i] > mask[j]) {
                        temp    = mask[i];
                        mask[i] = mask[j];
                        mask[j] = temp;
                    }
                }
            }
            arr[idx] = mask[mask_mid]; // median is in the middle of sorted mask
        }
        else if (filter == 'w') {
            for (int i = 0; i < mask_len; ++i) {
                mask_sum += mask[i] * distribution[i];
            }
            arr[idx] = mask_sum;
        }

        idx = (idx + 1) % n;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (double)((int)(arr[i] * 100)) / 100 << " ";
    }

    std::cout << std::endl;

    return 0;
}

// vim: fen
