#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

class Tacka {
public:
    ll x, y;

    Tacka(ll x = 0, ll y = 0) : x(x), y(y) {}

    Tacka operator+(Tacka v) {
        return Tacka(x+v.x,y+v.y);
    }

    Tacka operator-(Tacka v) {
        return Tacka(x-v.x,y-v.y);
    }

    static bool poKoordinatama(Tacka a, Tacka b) {
        if (a.y != b.y)
            return a.y < b.y;
        else
            return a.x < b.x;
    }

    bool orijent(Tacka a, Tacka b) {
        Tacka p = a - *this;
        Tacka q = b - *this;
        return (p.x*q.y - p.y*q.x) >= 0;
    }

    static bool poOrijent(Tacka a, Tacka b) {
        return Tacka().orijent(a, b);
    }
};

vector<Tacka> KonveksOmotac(vector<Tacka> p) {
    if(p.size() <= 2)
        return p;

    sort(p.begin(), p.end(), Tacka::poKoordinatama);
    Tacka o = p[0];
    for(auto& i : p)
        i = i - o;
    sort(p.begin() + 1, p.end(), Tacka::poOrijent);

    vector<Tacka> omotac;
    for(auto& i : p) {
        size_t vel = omotac.size();
        while(vel > 1 && omotac[vel-1].orijent(omotac[vel-2], i)) {
            omotac.pop_back();
            vel--;
        }
        omotac.push_back(i);
    }

    for(auto& i : omotac)
        i = i + o;
    return omotac;
}

ll Povrsina(vector<Tacka> p) {
    if(p.size() <= 2)
        return 0;

    ll sum = 0, n = p.size();
    for(size_t i=0;i<n;i++)
        sum += (p[i].x*p[(i+1)%n].y - p[(i+1)%n].x*p[i].y) / 2;

    if(sum < 0)
        sum = -sum;
    return sum;
}

vector<Tacka> delovi[100001];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    vector<Tacka> p(n);
    for(auto& i : p)
        cin >> i.x >> i.y;
    
    auto omotac = KonveksOmotac(p);
    Tacka o = omotac[0];

    for(auto& i : p) i = i - o;
    for(auto& i : omotac) i = i - o;

    ll vel = omotac.size();
    sort(p.begin(), p.end(), Tacka::poKoordinatama);
    sort(p.begin() + 1, p.end(), Tacka::poOrijent);

    for(int i=2,j=2;i<n;i++) {
        if(p[i].x == omotac[j].x && p[i].y == omotac[j].y) 
            j++;
        else 
            delovi[j].push_back(p[i]);
    }

    vector<Tacka> pom;
    for(int i=1;i<n;i++)
        pom.push_back(p[i]);

    ll rez = Povrsina(KonveksOmotac(pom));
    ll mpov = Povrsina(omotac);

    pom = delovi[2];
    pom.push_back(omotac[0]);
    pom.push_back(omotac[2]);
    ll pov1 = Povrsina(KonveksOmotac(pom));
    pom.push_back(omotac[1]);
    ll pov2 = Povrsina(KonveksOmotac(pom));
    if(mpov - pov2 + pov1 < rez)
        rez = mpov - pov2 + pov1;
    
    pom = delovi[vel-1];
    pom.push_back(omotac[0]);
    pom.push_back(omotac[vel-2]);
    pov1 = Povrsina(KonveksOmotac(pom));
    pom.push_back(omotac[vel-1]);
    pov2 = Povrsina(KonveksOmotac(pom));
    if(mpov - pov2 + pov1 < rez)
        rez = mpov - pov2 + pov1;

    for(int i=2;i<vel-1;i++) {
        pom = delovi[i];
        for(auto& tac : delovi[i+1])
            pom.push_back(tac);
        
        pom.push_back(omotac[i-1]);
        pom.push_back(omotac[i+1]);
        pov1 = Povrsina(KonveksOmotac(pom));
        pom.push_back(omotac[i]);
        pov2 = Povrsina(KonveksOmotac(pom));
        if(mpov - pov2 + pov1 < rez)
            rez = mpov - pov2 + pov1;
    }
    
    cout << rez << '\n';
    return 0;
}