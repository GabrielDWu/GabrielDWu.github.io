---
layout: post
title:  "Flipping Coins"
date:   2022-01-07
author: Gabriel Wu
permalink: flipping-coins
desc: What's the expected value of the number of times you must flip a coin before you encounter a given string, such as "HTTH"? Here's an algorithm to compute it.
tags: [math, computer science]
words: 3000
suggested: true
---

*Prerequisites:*
- expected value, linearity of expectation
- basic linear algebra
- time complexity with Big-O notation (only in certain sections)

<br>

# The Problem

Say you're given a string of coin flips, such as **HTTH** or **TTTHHT**. What is the expected number of times you must flip a coin until you encounter that string?

A common initial (incorrect) intuition about this problem is that all strings of length $$n$$ should have the same answer -- something like $$2^n$$. We sense that there should be some sort of symmetry between heads and tails, so it feels odd that **HHHH** should appear any earlier or later than **HTHT**. But in this case, our intuition is simply wrong. It is true that the answer will always be on the order of $$2^n$$ (specifically, bounded between $$2^{n}$$ and $$2^{n+1}-2$$), but the string itself *does* matter, as we shall see.

Let's consider a simple example. How many coins do you need to flip before getting a **H**? For this particular string, the number of flips you need creates the [Bernoulli distribution](https://en.wikipedia.org/wiki/Bernoulli_distribution), which has an expected value of $$2$$. One slick way to see this is to imagine computing the answer by conducting many consecutive "trials" by flipping the coin a large number of times (say you do $$N = 10^9$$ total flips). The total number of trials you end up completing is simply the number of heads you encounter, which should be close to $$N/2$$. And since the expected number of flips per trial is approximated by the average number of flips over a large number of trials, our answer is $$\frac{N}{N/2} = 2$$. While this method considering a large number of consecutive trials works well for the string **H**, we will need to find a more general method for longer strings.[^1]

[^1]: The reason this method does not easily generalize to longer strings is because I see no efficient way to compute the approximate number of disjoint occurrences of, say, **HHTH** in a string of length $$N$$ (where $$N$$ is very large). What I mean by "disjoint" is that we don't care about the total number of times **HHTH** appears (that would be $$N/16$$), but rather the number of trials that are completed. Each trial is associated with an occurrence of **HHTH** that does not share any characters with any other trial -- there can only be one trial running at a time. If you can come up with a global way to count this value (i.e. a way that doesn't use states), please let me know! This method does, however, give an *upper bound* on the number of disjoint occurrences, which gives a *lower bound* on the final answer. The number of disjoint occurrences is at most the number of total occurrences which is $$N/2^n$$, so a lower bound on the expected number of flips per trial is $$2^n$$ for any string of length $$n$$. This lower bound is achieved by **HHH...HT** (all occurrences of this string must be disjoint).

# States

The solution is to use *states*, a technique common to expected value problems. The idea of states is simple: define a bunch of variables to represent different stages of progress towards a goal. Create relations among the variables corresponding to "transitions" from one state to another, then solve the system of (usually) linear equations for the answer. In our case, when given string $$S$$ of length $$n$$, we will use $$n+1$$ state variables: $$e_0, e_1, \dots, e_n$$. The variable $$e_i$$ will represent _the expected number of additional flips required to obtain string $$S$$ given that we've just flipped the first $$i$$ characters of $$S$$_. By definition, $$e_n$$ represents the expected number of flips to obtain $$S$$ if we've already flipped all of $$S$$, so $$e_n = 0$$. Our final answer will be $$e_0$$ (because we start out with nothing flipped).

Formally, what we're doing here is a creating "state function" $$f: \{\text{H}, \text{T}\}^* \to \{0, 1, \dots, n\}$$ that maps every possible string of coin flips to a unique state in $$\{0, 1, \dots, n\}$$. In this case, our state function $$f$$ takes in a string $$s$$ and outputs the largest nonnegative integer $$i$$ such that &#124;$$s$$&#124; $$\geq i$$ and the last $$i$$ characters of $$s$$ are the first $$i$$ characters of $$S$$. For example, if $$S$$ is **HTHH**, then the empty string gets assigned state $$0$$, **H<mark>HT</mark>** gets state $$2$$, **HHHT<mark>HTH</mark>** gets state $$3$$, and **T<mark>HTHH</mark>** gets state $$4$$.

We require $$f$$ to have two properties in order to be a valid state function. Define the subset of "accept strings" $$A \subset \{\text{H}, \text{T}\}^* $$ to be all strings for which we have just encountered all of $$S$$ (so, strings that have $$S$$ as a suffix). Then our first requirement is that $$A$$ corresponds to a state[^2] $$\sigma$$, i.e. that $$s \in A \Longleftrightarrow f(s) = \sigma$$. Our second requirement is that _transitions are well-defined on states_. Define the transition function $$T(s, \sigma')$$ to be the probability that when you add **H** or **T** at random to string $$s$$ you end up with some string $$s'$$ satisfying $$f(s') = \sigma'$$. Then this requirement says that $$T(s, \underline{\quad})$$ depends only on the state $$f(s)$$, i.e. $$T(s, \sigma') \equiv \tau(f(s), \sigma')$$ for some function $$\tau$$. You may want to take some time to think about why these two properties are important in a state function. Then, convince yourself that our definition of $$f$$ does in fact satisfy both of them. The first requirement is straightforward ($$A$$ is just state $$n$$), but the second one is not as immediate.

[^2]: We would also be fine if $$A$$ corresponded to a union of states (in other words, if there were some $$\sigma_1, \dots, \sigma_k$$ such that $$s \in A \Longleftrightarrow f(s) \in \{\sigma_1, \dots, \sigma_k\}$$).

It's fine if you don't follow all of this formality (in fact, I never went through the formalization until writing this post). On a more intuitive level, what we're doing is finding a way to compress the infinite set of coin flip strings into a finite set of states. We do this in a way that *preserves all relevant information* to the number of coin flips needed to get accepted, including how likely it is to transition from one state to another. This will allow us to build a finite system of equations (as opposed to an infinite system of equations) that we can solve to find the answer.

So what exactly is this system of equations? Take the example in which $$S$$ is **HTHH**. For each state we have an equation that relates its expected value to the expected values of the states it can transition to. If we currently have the first $$0$$ characters of $$S$$ (which would correspond to flip sequences such as the empty string, or **TTT**, or **HTHTT**), then if we flip an **H** next we will end up in state $$1$$. But if we flip a **T** next, we will remain in state $$0$$. By linearity of expectation, this lets us write the equation $$e_0 = 1 + \frac{1}{2}e_1 + \frac{1}{2}e_0$$. Similarly, if we currently are in state $$1$$, then flipping a **H** will keep us in state $$1$$, while flipping a **T** will transition us to state $$2$$. So $$e_1 = 1 + \frac{1}{2}e_1 + \frac{1}{2}e_2$$. Continuing this process, we get the following equations:

|        State        |     New state (**H** flipped)    |     New state (**T** flipped)    |                    Equation                   |
|:-------------------:|:--------------------------------:|:--------------------------------:|:---------------------------------------------:|
|     $$0$$ (...)     |   $$1$$ (...**<mark>H</mark>**)  |         $$0$$ (...**T**)         | $$e_0 = 1 + \frac{1}{2}e_1 + \frac{1}{2}e_0$$ |
|   $$1$$ (...**H**)  |  $$1$$ (...**H<mark>H</mark>**)  |  $$2$$ (...**<mark>HT</mark>**)  | $$e_1 = 1 + \frac{1}{2}e_1 + \frac{1}{2}e_2$$ |
|  $$2$$ (...**HT**)  |  $$3$$ (...**<mark>HTH</mark>**) |        $$0$$ (...**HTT**)        | $$e_2 = 1 + \frac{1}{2}e_3 + \frac{1}{2}e_0$$ |
|  $$3$$ (...**HTH**) | $$4$$ (...**<mark>HTHH</mark>**) | $$2$$ (...**HT<mark>HT</mark>**) | $$e_3 = 1 + \frac{1}{2}e_4 + \frac{1}{2}e_2$$ |
| $$4$$ (...**HTHH**) |                n/a               |                n/a               |                  $$e_4 = 0$$                  |


Now we can solve this system of four equations and four unknowns with our favorite linear system technique (for example, Gaussian elimination). In the end, we get $$e_0 = 18$$, which is our final answer to the question "What is the expected number of coin flips I need to perform before encountering **HTHH**?"

For a general string $$S$$, how do we systematically generate these equations? Each of these equations comes in the form $$e_i = 1 + \frac{1}{2}e_j + \frac{1}{2}e_k$$. In particular, for a given state $$i$$, we get that $$j$$ is the state of the string $$S_{0\dots i-1}$$**H** (i.e. the first $$i$$ characters of $$S$$ followed by a **H**), while $$k$$ is the state of $$S_{0\dots i-1}$$**T**.

This suffices as a complete algorithm to calculate the answer for any given string $$S$$. First, generate the $$n$$ equations by computing the states of the appropriate strings. Then, solve the system of equations for $$e_0$$. In the next section, I will analyze the time complexity of this algorithm and present two powerful optimizations to the naive strategy.

# Time complexity

*The following sections assume the knowledge of Big-O time complexity for measuring the asymptotic speed of algorithms.*

Naively, we can compute the state of a string $$s$$ by checking if the $$i$$th suffix of $$s$$ is equal to the $$i$$th prefix of $$S$$ for all possible $$i$$. Each string comparison can be done in $$O(n)$$ and there are $$O(n)$$ possible $$i$$ values, so this takes $$O(n^2)$$ time. We will need to call this state function for each equation we generate, so it takes $$O(n^3)$$ time to generate all $$n$$ equations. Once we have these equations, Gaussian elimination takes an additional $$O(n^3)$$ time, so overall our naive algorithm has a cubic time complexity.

Technically, we must add on an extra factor of $$n$$ to account for computation using arbitrarily large numbers. The integer values encountered in this problem grow exponentially in $$n$$, so they can be $$O(n)$$ digits long. When the numbers are this big, even addition takes $$O(n)$$ time (and speicial BigInteger classes will have to be used in certain programming languages because the values will not fit into 64-bit words). But in this analysis I will treat the standard operations of addition and subtraction as taking only $$O(1)$$ time (perhaps we only need the residue of the answer modulo some large prime, as is common in many competitive programming problems). This means I will omit the extra factor of $$n$$ in the time complexities.

Now that we have established a straightforward $$O(n^3)$$ algorithm, I will show how we can make this process much more efficient. The result will be linear-time ($$O(n)$$) algorithm. This optimization must affect both stages of the algorithm: we must be able to generate the $$n$$ equations in linear time, and we must be able to solve the resultant system in linear time.

# The Longest Prefix-Suffix (LPS) Array

As explained earlier, the problem of generating the $$n$$ equations reduces to computing the states of $$S_{0\dots i-1}$$**H** and $$S_{0\dots i-1}$$**T** for all $$i$$ from $$0$$ to $$n-1$$. For any given $$i$$, it is obvious which state $$S_{0\dots i-1}S_i$$ corresponds to: it's just state $$i+1$$. So the only question is what state the string $$S_{0\dots i-1}\overline{S_i}$$ corresponds to. To compute this efficiently, we will introduce the **Longest Prefix-Suffix (LPS)** array, which some readers may recognize as the cornerstone of the Knuth-Morris-Pratt (KMP) string searching algorithm. We define $$LPS$$ to be an integer array of length $$n$$, where $$LPS[i]$$ (for $$0 \leq i \leq n-1$$) represents the length of the longest proper[^3] prefix of $$S_{0\dots i}$$ that is also a suffix of $$S_{0\dots i}$$ (we will call this a proper prefix-suffix). For example, if $$S = $$ **HHTHHTH**, then $$LPS = [0, 1, 0, 1, 2, 3, 4]$$ because:
- **H** has length 1, so it has no positive-length proper prefix
- the first character of **<mark>H</mark>H** is the last character of **H<mark>H</mark>**
- there is no positive-length proper prefix of **HHT** that is also a suffix
- the first character of **<mark>H</mark>HTH** is the last character of **HHT<mark>H</mark>**
- the first two characters of **<mark>HH</mark>THH** are the last two characters of **HHT<mark>HH</mark>**
- the first three characters of **<mark>HHT</mark>HHT** are the last three characters of **HHT<mark>HHT</mark>**
- the first four characters of **<mark>HHTH</mark>HTH** are the last four characters of **HHT<mark>HHTH</mark>**

[^3]: A *proper prefix* is a prefix that has strictly less length than the original string.
<br>

In addition to $$LPS$$, we will have three more arrays of length $$n$$: $$LIPS$$, $$LPSH$$, and $$LPST$$. These arrays are not typically used in the KMP algorithm, but they are useful for solving this problem. We define them as follows. $$LIPS[i]$$ represents the length of the longest proper prefix-suffix of $$S_{0\dots i-1}\overline{S_i}$$ (the $$I$$ stands for "last character **i**nverted"). $$LPSH[i]$$ represents the length of the longest proper prefix-suffix of $$S_{0\dots i}$$ that has **H** as the next character after the prefix, or $$-1$$ if this does not exist. In other words, for $$LPSH[i] \neq -1$$ we must have $$S_{LPSH[i]} = $$ **H**. Similarly, $$LPST[i]$$ represents the length of the longest proper prefix-suffix of $$S_{0\dots i}$$ that has **T** for the next character after the prefix, or $$-1$$ if this does not exist. In the example from above ($$S = $$ **HHTHHTH**), we have $$LIPS = [0, 0, 2, 0, 0, 2, 0]$$, $$LPSH = [0, 1, 0, 1, 1, 3, 4]$$, and $$LPST = [-1, -1, -1, -1, 2, -1, -1]$$.

It turns out that we can generate all four of these arrays in linear time using dynamic programming![^4] Here's my C++ code:

[^4]: This actually gives us a linear time algorithm for generating $$LPS$$ that is different from the standard technique (described [here](https://medium.com/@aakashjsr/preprocessing-algorithm-for-kmp-search-lps-array-algorithm-50e35b5bb3cb)) that is typically used in KMP. One advantage to my technique is that it is clearer to see that it runs in $$O(n)$$ than the standard method. It may also be more intuitive to some people.

```c++

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
```

Let's break down the transitions here. The first observation is that $$LPS[i]$$ must correspond to a prefix-suffix of $$S_{0\dots i}$$ that is one longer than a prefix-suffix of $$S_{0\dots i-1}$$. But it cannot extend just any prefix-suffix of $$S_{0\dots i-1}$$. It must extend one that agrees with $$S_i$$ on the next character. If $$S_i = $$ **H**, then this is exactly the prefix-suffix that $$LPSH[i-1]$$ represents, so we set $$LPS[i] = LPSH[i-1] + 1$$. Otherwise, we set $$LPS[i] = LPST[i-1] + 1$$. We can determine $$LIPS[i]$$ similarly -- just imagine $$S_i$$ is inverted and treat it like $$LPS[i]$$.

Now, without loss of generality, say that the longest prefix-suffix of $$S_{0\dots i}$$ has **H** as the next character after that prefix (the other case is handled symmetrically). Then we can simply set $$LPSH[i]$$ to be the same length as $$LPS[i]$$. We also know that $$LPST[i]$$ must be strictly smaller than $$LPS[i]$$, i.e. it must indicate the longest proper prefix-suffix of $$S_{0\dots LPS[i]-1}$$ that has a **T** as the next character (if this exists). But this is exactly what $$LPST[LPS[i]-1]$$ represents! This gives us $$O(1)$$ transitions for all four arrays.

Long story short, we can build the four arrays in linear time. How does this help us? Well, notice that the state of a string of the form $$S_{0\dots i-1}\overline{S_i}$$ is equal to its longest proper prefix-suffix. This is because its first $$j \leq i$$ characters are guaranteed to also be the first $$j$$ characters of $$S$$. But we already know how to generate the longest proper prefix-suffix of $$S_{0\dots i-1}\overline{S_i}$$ -- this is just $$LIPS[i]$$! Thus, we can easily generate our $$n$$ equations by reading off the values of $$LIPS$$.

# A Well-Behaved Matrix

All that's left is to show how we can solve our system of $$n$$ equations in linear time. In general, this is impossible. But in this specific problem there are many nice properties of our system. For example, it is extremely sparse: each equation $$e_i = 1 + \frac{1}{2}e_j + \frac{1}{2}e_k$$ relates at most three different variables. We also know that (swapping $$j$$ and $$k$$ if necessary) we get the conditions $$j \leq i$$ and $$k = i+1$$ for each equation. If we rewrite each equation in the form $$-e_j + 2e_i - e_{i+1} = 2$$ and aggregate them into the standard linear system matrix used in Gaussian elimination, the structure becomes clearer (the following matrix is for $$S = $$ **HTHH**):

$$\begin{bmatrix}
1 & -1 & 0 & 0 & 0 & 2 \\
0 & 1 & -1 & 0 & 0 & 2 \\
-1 & 0 & 2 & -1 & 0 & 2 \\
0 & 0 & -1 & 2 & -1 & 2 \\
0 & 0 & 0 & 0 & 1 & 0 
\end{bmatrix}$$

In all rows except the last, the main diagonal is filled with $$2$$s, with a $$-1$$ just to the right. There is also a $$-1$$ somewhere to the left (or on top of) the $$2$$ (if it is on top of the $$2$$, it is just written as a $$1$$). As with any system of linear equations, our goal is now to reduce this matrix by adding rows to each other. Here's where the well-behaved structure of the matrix becomes useful. Define a row to be *almost-reduced* if it has a $$1$$ on the main diagonal, a $$-1$$ just to the right of it, and $$0$$s everywhere else besides the last column. In the matrix above, the top two rows are almost-reduced.

Observe that if the first $$i$$ rows of the matrix are already almost-reduced, then it is easy to almost-reduce the $$i+1$$th row. Say that row $$i+1$$ has a $$-1$$ in position $$j < i+1$$, a $$2$$ in position $$i+1$$ and another $$-1$$ in position $$i+2$$. Then if we add all rows $$j, j+1, \dots, i$$ to row $$i+1$$, it will become almost-reduced because the $$1$$s and $$-1$$s end up telescoping in on each other.

$$\begin{bmatrix}
1 & -1 & 0 & 0 & 0 & 2 \\
0 & 1 & -1 & 0 & 0 & 2 \\
-1 & 0 & 2 & -1 & 0 & 2 \\
0 & 0 & -1 & 2 & -1 & 2 \\
0 & 0 & 0 & 0 & 1 & 0 
\end{bmatrix} \implies
\begin{bmatrix}
1 & -1 & 0 & 0 & 0 & 2 \\
0 & 1 & -1 & 0 & 0 & 2 \\
0 & 0 & 1 & -1 & 0 & 6 \\
0 & 0 & -1 & 2 & -1 & 2 \\
0 & 0 & 0 & 0 & 1 & 0 
\end{bmatrix}$$

<div style="text-align:center;font-size:14px">
<em>The first two rows are added to the third row, resulting in it becoming almost-reduced.</em>
</div>

<br>

In this manner, we can almost-reduce a row in $$O(1)$$ time by maintaining prefix sums[^5] of the values in the last column of the matrix. In fact, the only values we ever need to store besides these prefix sums are the locations of the left-most $$-1$$ in each row (which correspond to $$LIPS[i]$$). Once we have almost-reduced all rows, the final answer $$e_0$$ is the sum of the entire right-most column (the last prefix sum). All of this can be done in linear time.

[^5]: The [prefix sums](https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/) of an array $$a$$ are the values $$a[0], a[0]+a[1], a[0]+a[1]+a[2], \dots$$. This is a common technique which allows you to compute the sum of any subarray in $$O(1)$$ time. In this case, we use it to compute the sum of the values in the right-most column of rows $$j, j+1, \dots, i$$.

# Conclusion

The algorithm presented here computes the expected number of coin flips required to achieve a given string in $$O(n)$$ time. I am sure that I am not the first person to have thought of this problem, but as far as I know this is the first instance of a linear-time algorithm to solve it -- although if you find this on some old AtCoder contest, please let me know... I wouldn't be surprised :). Thank you for reading!

***

<br>