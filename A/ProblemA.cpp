#include <iostream>
#include <vector>
using namespace std;

int check(const vector<long>& nizStaklatita, long pericinaVisina) {
    for (int i = 0; i < nizStaklatita.size(); i++) {
        if (nizStaklatita[i] <= pericinaVisina) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    long N, L;
    cin >> N >> L;

    vector<long> nizStaklatita(N);
    for (long i = 0; i < N; i++) {
        cin >> nizStaklatita[i];
    }

    cout << check(nizStaklatita, L) << endl;

    return 0;
}