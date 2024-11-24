#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

vector<ll> solve(int N, int Q, vector<ll>& d, vector<ll>& p, vector<ll>& q) {
    vector<ll> odgovori(Q);

    vector<pair<ll, ll>> periodi;

    ll kraj_dana = -1;
    for (int i = 0; i < N; i++) {
        ll d_i = d[i];
        ll p_i = p[i];

        if (kraj_dana < d_i - 1) {
            ll pocetak = d_i;
            ll kraj = d_i + p_i - 1;
            periodi.push_back({pocetak, kraj});
            kraj_dana = kraj;
        } else {
            kraj_dana += p_i;
            periodi.back().second = kraj_dana;
        }
    }

    int M = periodi.size();
    vector<ll> krajevi(M);
    vector<ll> kum_duzine(M + 1);

    for (int i = 0; i < M; i++) {
        ll pocetak = periodi[i].first;
        ll kraj = periodi[i].second;
        krajevi[i] = kraj;
        ll duzina = kraj - pocetak + 1;
        kum_duzine[i + 1] = kum_duzine[i] + duzina;
    }

    for (int i = 0; i < Q; i++) {
        ll k_j = q[i];

        auto it = lower_bound(krajevi.begin(), krajevi.end(), k_j);
        int indeks = it - krajevi.begin();

        if (it != krajevi.end() && *it == k_j) {
            indeks++;
        }

        ll pojedeno = kum_duzine[indeks];

        if (indeks < M && periodi[indeks].first <= k_j) {
            ll pocetak = periodi[indeks].first;
            pojedeno += k_j - pocetak + 1;
        }

        odgovori[i] = pojedeno;
    }

    return odgovori;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<ll> d(N);
    vector<ll> p(N);

    for (int i = 0; i < N; i++) {
        cin >> d[i] >> p[i];
    }

    vector<ll> q(Q);
    for (int i = 0; i < Q; i++) {
        cin >> q[i];
    }

    vector<ll> odgovori = solve(N, Q, d, p, q);

    for (ll odgovor : odgovori) {
        cout << odgovor << endl;
    }

    return 0;
}