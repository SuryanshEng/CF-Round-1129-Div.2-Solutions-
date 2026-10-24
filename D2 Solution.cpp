#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 big;
const ll MOD = 998244353;
ll rooney[64];
big ronaldo[64];
map<pair<int,ll>, ll> lampard;

ll modded(big x){ ll r = x % MOD; return r < 0 ? r + MOD : r; }

int gambhir(ll s){
    int g = 0;
    for(int i = 0; i < 62; i++) if(s >> i & 1) g += i + 1;
    return g;
}

big zaheer(ll s){
    big best = (big)4 * s + gambhir(s);
    for(int i = 0; i <= 60; i++){
        if(s >> i & 1) continue;
        ll t = ((s >> i) | 1) << i;
        best = min(best, (big)4 * t + gambhir(t));
    }
    return best;
}

ll kapil(int p, big cap){
    if(p == 0) return 0;
    if(cap <= 5) return modded(cap) * rooney[p] % MOD;
    if(cap > ronaldo[p]) cap = ronaldo[p];
    pair<int,ll> key = {p, (ll)cap};
    if(lampard.count(key)) return lampard[key];
    big B = ((big)1 << (p + 1)) + p;
    ll res = kapil(p - 1, min(cap, B));
    res = (res + 2LL * p % MOD * modded(min(B, cap))) % MOD;
    res = (res + modded(B) * rooney[p - 1]) % MOD;
    res = (res + kapil(p - 1, cap - B)) % MOD;
    return lampard[key] = res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int i = 1; i < 64; i++) rooney[i] = (2 * rooney[i-1] + 2 * i) % MOD;
    for(int p = 0; p < 62; p++) ronaldo[p] = (big)4 * (((big)1 << p) - 1) + (big)p * (p + 1) / 2;

    int tests;
    cin >> tests;
    while(tests--){
        ll l, r;
        cin >> l >> r;
        ll ends[2] = {r, l - 1};
        ll answer = 0;

        for(int side = 0; side < 2; side++){
            ll N = ends[side];
            if(N <= 0) continue;
            ll total = 1;
            if(N >= 2){
                ll M = N - 1;
                ll lo = 1, hi = 1LL << 59;
                while(lo < hi){
                    ll mid = (lo + hi) / 2;
                    if(4 * mid - 2 * __builtin_popcountll(mid) >= M) hi = mid;
                    else lo = mid + 1;
                }
                ll s = lo;
                ll prev = 4 * (s - 1) - 2 * __builtin_popcountll(s - 1);

                ll X = s - 1, part = 0;
                if(X > 0){
                    ll Y = X + 1;
                    for(int p = 59; p >= 0; p--){
                        if(!(Y >> p & 1)) continue;
                        ll A = (Y >> (p + 1)) << (p + 1);
                        big base = (big)4 * A + gambhir(A);
                        big cA = zaheer(A + (1LL << p)) - base;
                        ll w0 = A > 0 ? 2LL * (__builtin_ctzll(A) + 1) : 0;
                        ll v = modded(base) * ((rooney[p] + w0) % MOD) % MOD;
                        v = (v + kapil(p, cA)) % MOD;
                        v = (v + w0 * modded(min((big)0, cA))) % MOD;
                        part = (part + v) % MOD;
                    }
                }
                ll S1 = (part + modded(zaheer(s)) * modded(M - prev)) % MOD;
                ll tri = modded((big)M * (M + 1) / 2);
                total = ((total + S1 - M % MOD - tri) % MOD + 2 * MOD) % MOD;
            }
            if(side == 0) answer += total; else answer -= total;
        }
        cout << ((answer % MOD) + MOD) % MOD << '\n';
    }
}