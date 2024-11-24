#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200005;
const int MAXBIT = 31;

int N;
int A[MAXN], B[MAXN];
int prefiksXor[MAXN];
long long maxValue = 0;

struct TrieNode {
    TrieNode* child[2];
    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

void insert(TrieNode* root, int num) {
    TrieNode* trenutni = root;
    for(int i = MAXBIT - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if(trenutni->child[bit] == nullptr) {
            trenutni->child[bit] = new TrieNode();
        }
        trenutni = trenutni->child[bit];
    }
}

int query(TrieNode* root, int num) {
    TrieNode* trenutni = root;
    int maxNum = 0;
    for(int i = MAXBIT - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if(trenutni->child[1 - bit]) {
            maxNum |= (1 << i);
            trenutni = trenutni->child[1 - bit];
        } else if(trenutni->child[bit]) {
            trenutni = trenutni->child[bit];
        } else {
            break;
        }
    }
    return maxNum;
}

void deleteTrie(TrieNode* root) {
    if(root->child[0]) deleteTrie(root->child[0]);
    if(root->child[1]) deleteTrie(root->child[1]);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; i++)
        cin >> A[i];
    for(int i = 1; i <= N; i++)
        cin >> B[i];

    prefiksXor[0] = 0;
    for(int i = 1; i <= N; i++) {
        prefiksXor[i] = prefiksXor[i - 1] ^ A[i];
    }

    for(int i = 1; i <= N; i++) {
        int andValue = B[i];
        int pos = i;
        while(andValue > 0 && pos <= N) {
            int R = pos;
            int trenutniAnd = andValue;

            while(R + 1 <= N && (trenutniAnd & B[R + 1]) == trenutniAnd) {
                R++;
            }

            TrieNode* root = new TrieNode();
            insert(root, prefiksXor[pos - 1]);
            int maxXor = 0;
            for(int j = pos; j <= R; j++) {
                int trenutniXor = prefiksXor[j];
                int trenutniMax = query(root, trenutniXor);
                maxXor = max(maxXor, trenutniMax);
                insert(root, prefiksXor[j]);
            }
            maxValue = max(maxValue, (long long)maxXor * trenutniAnd);
            deleteTrie(root);

            if(R + 1 <= N)
                andValue &= B[R + 1];
            else
                andValue = 0;
            pos = R + 1;
        }
    }

    cout << maxValue << endl;
    return 0;
}