Great job finding this site Easter Egg! This is where I store significant amounts of text that I've cut from blogs.

-----

From flipping_coins (removed because generating $$LIPS$$ is actually $$O(n^2)$$ using this algorithm):

It turns out that the entire $$LPS$$ array can be computed in $$O(n)$$ using the following C++ code:
```c++
lps[0] = 0;
for(int i=1; i<n; i++) {
	bool done = false;
	int prev = lps[i-1];

	while(!done) {
		if(s[i] == s[prev]) {
			lps[i] = prev+1;
			done = true;
		} else {
			if(prev > 0) {
				prev = lps[prev-1];
			} else {
				lps[i] = 0;
				done = true;
			}
		}
	}
}
```
A more detailed explanation as to why this works can be found [here](https://medium.com/@aakashjsr/preprocessing-algorithm-for-kmp-search-lps-array-algorithm-50e35b5bb3cb), but the key observation is that the longest proper prefix-suffix of $$S_{0\dots i+1}$$ must be one longer than a proper prefix-suffix of $$S_{0\dots i}$$, so we simply check all proper prefix-suffixes of $$S_{0\dots i}$$ in decreasing size until we find one for which the following character matches (i.e. $$S_{i+1} = S_{LPS[i+1]-1}$$). The reason this process only takes $$O(n)$$ time is that the number of times the `while` loop is executed for a given $$i$$ is roughly bounded above by $$LPS[i-1] - LPS[i]$$. Since each term is at most one greater than the previous, this only affords a potential $$O(n)$$ total decrease between consecutive terms.

```c++
lps[0] = 0;
lips[0] = 0;
for(int i=1; i<n; i++) {
	bool done = false;
	int prev = lps[i-1];

	//compute lips[i]
	while(!done) {
		if(s[i] != s[prev]) {	//pretend that s[i] is inverted
			lips[i] = prev+1;
			done = true;
		} else {
			if(prev > 0) {
				prev = lps[prev-1];
			} else {
				lips[i] = 0;
				done = true;
			}
		}
	}

	//reset done and prev
	done = false;
	prev = lps[i-1];

	//compute lps[i] like before
	while(!done) {
		if(s[i] == s[prev]) {
			lps[i] = prev+1;
			done = true;
		} else {
			if(prev > 0) {
				prev = lps[prev-1];
			} else {
				lps[i] = 0;
				done = true;
			}
		}
	}
}
```

-----