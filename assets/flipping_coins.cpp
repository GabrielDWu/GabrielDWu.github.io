#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

typedef std::decay<decltype(MOD)>::type mod_t;
struct mi {
	mod_t val;
	explicit operator mod_t() const { return val; }
	mi() { val = 0; }
	mi(const long long& v) {
		val = (-MOD <= v && v < MOD) ? v : v % MOD;
		if (val < 0) val += MOD; }
	friend std::istream& operator >> (std::istream& in, mi& a) {
		long long x; std::cin >> x; a = mi(x); return in; }
	friend std::ostream& operator << (std::ostream& os, const mi& a) { return os << a.val; }
	friend bool operator == (const mi& a, const mi& b) { return a.val == b.val; }
	friend bool operator != (const mi& a, const mi& b) { return !(a == b); }
	friend bool operator < (const mi& a, const mi& b) { return a.val < b.val; }
	friend bool operator > (const mi& a, const mi& b) { return a.val > b.val; }
	friend bool operator <= (const mi& a, const mi& b) { return a.val <= b.val; }
	friend bool operator >= (const mi& a, const mi& b) { return a.val >= b.val; }
	mi operator - () const { return mi(-val); }
	mi& operator += (const mi& m) {
		if ((val += m.val) >= MOD) val -= MOD;
		return *this; }
	mi& operator -= (const mi& m) {
		if ((val -= m.val) < 0) val += MOD;
		return *this; }
	mi& operator *= (const mi& m) { val = (long long) val * m.val % MOD;
		return *this; }
	friend mi pow(mi a, long long p) {
		mi ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
		return ans; }
	friend mi inv(const mi& a) { assert(a != 0); return pow(a, MOD - 2); }
	mi& operator /= (const mi& m) { return (*this) *= inv(m); }
	friend mi operator + (mi a, const mi& b) { return a += b; }
	friend mi operator - (mi a, const mi& b) { return a -= b; }
	friend mi operator * (mi a, const mi& b) { return a *= b; }
	friend mi operator / (mi a, const mi& b) { return a /= b; }
};

int main(){
	cin.tie(0)->sync_with_stdio(0);

	string S;
	cin >> S;

	int n = S.size();

	vector<int> LPS(n), LIPS(n), LPSH(n), LPST(n);

	//initialize base cases
	LIPS[0] = 0;
	LPS[0] = 0;
	if(S[0] == 'H'){
		LPSH[0] = 0;
		LPST[0] = -1;
	} else {	// S[0] == 'T'
		LPSH[0] = -1;
		LPST[0] = 0;
	}

	for(int i=1; i<n; i++){

		// set LPS[i] and LIPS[i]
		if(S[i] == 'H'){
			LPS[i] = LPSH[i-1] + 1;
			LIPS[i] = LPST[i-1] + 1;
		} else {	// S[i] == 'T'
			LPS[i] = LPST[i-1] + 1;
			LIPS[i] = LPSH[i-1] + 1;
		}

		// set LPSH[i] and LPST[i]
		if(S[LPS[i]] == 'H'){
			LPSH[i] = LPS[i];
			LPST[i] = (LPS[i] > 0 ? LPST[LPS[i]-1] : -1);
		} else {	// S[LPS[i]] == 'T'
			LPST[i] = LPS[i];
			LPSH[i] = (LPS[i] > 0 ? LPSH[LPS[i]-1] : -1);
		}
	}

	vector<mi> val(n);  // the (n+1)th column of the matrix
	vector<mi> pref(n);	// prefix sums of val
	pref[0] = 2;
	val[0] = 2;

	for(int i=1; i<n; i++){
		val[i] = 2 + pref[i-1] - (LIPS[i]-1 >= 0 ? pref[LIPS[i]-1] : 0);
		pref[i] = pref[i-1] + val[i];
	}

	cout << pref[n-1] << "\n";
}