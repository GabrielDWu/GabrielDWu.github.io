---
layout: post
title:  "A Butterfly's View of Probability"
date:   2022-06-13
author: Gabriel Wu
permalink: butterfly-probability
desc: "Chaos theory provides an alternative to both the frequentist and Bayesian interpretations of probability."
tags: [philosophy, math]
words: 3500
suggested: true
image: "butterfly-probability/dice.png"
preview: What do we really mean when we use the word "probability"? Assuming that the universe obeys deterministic physical laws, an event must occur with either probability 0 or 1. The future positions of every atom in the universe are completely determined by their initial conditions. So what do we mean when we make statements like "Trump has a 25% chance of winning in 2024"?
---

*Thanks to Alex Cai and Haneul Shin for discussing these ideas with me.*

<div style="text-align:center;font-size:14px">
<img src="assets/butterfly-probability/dice.png" width="80%">
</div>

<br>

What do we really mean when we use the word "probability"? Assuming that the universe obeys deterministic physical laws, an event must occur with either probability 0 or 1. The future positions of every atom in the universe are completely determined by their initial conditions. So what do we mean when we make statements like "Trump has a 25% chance of winning in 2024"? It will either happen, or it won't. From an objective, omniscient standpoint, there's no room for doubt.

One response is to reject determinism. Maybe in Newton's day we believed the universe was deterministic, but now we know about wave functions and Heisenberg uncertainty and all of that stuff. If we accept that there is true randomness occurring on the quantum level, then the outcome of the next election isn't predetermined -- it will depend on all of the quantum interactions that occur between now and 2024. With this view, it makes complete sense to assign fractional probabilities.

But quantum randomness is a highly non-obvious property of physics... Is there a way to make sense of probability without relying on it? In this post, I hope to outline <mark>a new way of defining the probability of a future event in a deterministic system</mark>. In contrast with the Bayesian view -- in which uncertainty about an event comes from incomplete information -- and the frequentist view -- which relies on an experiment being repeatable -- this "Butterfly's View of probability" draws its randomness from chaos theory.

# Bayesianism and Frequentism

Let's go over these two existing views, which are by far the most commonly accepted interpretations of probability.

The Bayesian view of probability is that randomness arises from incomplete information about the world. It is impossible to be aware of the current position of every atom in the universe at once. A Bayesian reasoner embraces this uncertainty by considering probability distributions over all possible universes consistent with his observations. At the core of this philosophy is Bayesian updating: starting with a prior probability distribution, upon seeing new evidence about the world a Bayesian reasoner will update this distribution according to [Bayes' rule](https://arbital.com/p/bayes_rule/). The probability of an event is the proportion of universes in this distribution in which the event occurs.

Bayesianism has a lot going for it. It works great in theory, serving as the fundamental mathematical law by which a rational agent's knowledge about the world must interact with itself. It also works great in practice, making accurate predictions as the cornerstone of modern statistics.

But there is one thing that Bayesianism lacks: *objectivity*. This is not to say that it is unmathematical, but rather that Bayesian probability is inherently subjective. The probability of an event is only defined relative to an agent. Alice and Bob, while both being perfect Bayesian reasoners, can assign different probabilities to Trump winning simply because they have different observations or priors. Because of this, Bayesian probability is often thought of as a "degree of personal belief" rather than an objective probability. In the real world, this is more of a feature than a bug -- nobody has perfect information, and if we did then we wouldn't care about probability in the first place. But in this post, our goal is to find an interpretation of probability that still makes sense from an objective, omniscient standpoint. The omniscient Bayesian would have a posterior probability distribution that places 100% credence on a single possible universe, eliminating all fractional probabilities -- so Bayesianism falls short of this goal.

The alternative to Bayesianism is called frequentism. A frequentist defines the probability of an event to be the limit of its relative frequency as you repeat it more and more times. A coin has a 50% chance of landing heads because if you flip it 100 times, close to 50 of the flips will be heads. In contrast with Bayesianism, the frequentist view is perfectly objective: the limit of a ratio will be the same no matter who observes it.

But the problem with frequentism is that it only makes sense when you're talking about a well-defined repeatable random experiment like a coin flip. How would a frequentist define the probability that Trump wins the election? It's not like we can just run the election 100 times in a row and take the average -- by definition, the 2024 election is a non-repeatable historical event. We could consider simulating the same election over and over, but what initial conditions do we use for each trial? Frequentism doesn't give us a recipe for how to define these simulations. This post will be my attempt to generalize the frequentist view by providing this recipe.

Bayesianism is rooted in uncertainty, so it is inherently subjective. Frequentism only applies to black-boxed repeatable experiments, so it struggles at describing events in the physical universe. Now I present a third view of probability that solves these two problems. I call this *the Butterfly's View*.

# The Butterfly Effect

On a perfect pool table, it is only possible to predict nine collisions before you have to take into account the gravitational force of a person standing in the room.[^1] Even an imperceptible change in the initial conditions becomes noticeable after just a few seconds. This is known as the "Butterfly Effect" -- the idea that if you make a tiny change to a complex deterministic system, that change will propagate and compound at an exponential rate. This makes it extremely hard (though not impossible in theory) to predict the state of a chaotic physical system, even over short time periods.

[^1]: This observation is credited to the physicist Michael Berry (1978) and the calculations are explained in [this paper](https://scholar.harvard.edu/files/schwartz/files/3-equilibrium.pdf). The idea is that, given some tiny error in the angle of a trajectory $$\Delta \theta$$, the next collision will have an angle error of about $$\left(\frac \ell R\right) \Delta \theta$$, then the next will have an error of $$\left(\frac \ell R\right)^2 \Delta \theta$$, and so on (where $$\ell$$ is the distance traveled between collisions and $$R$$ is the radius of each ball). So even though $$\Delta \theta$$ might be vanishingly small, the error becomes quite large after only a few collisions.

<br>

<div style="text-align:center;font-size:14px">
<img src="https://upload.wikimedia.org/wikipedia/commons/e/e3/Demonstrating_Chaos_with_a_Double_Pendulum.gif?20200228190911" alt="An animated GIF of a double pendulum." width="50%"> <br> <br>
<em>Imperceptible changes to the initial conditions of a double pendulum quickly become noticeable, stolen straight from Wikipedia.</em>
</div>

<br>

I believe that almost every aspect of our physical universe has the same chaotic properties as the pool table. The Brownian motion of air molecules, the complex firing patterns of neurons in our brain, and the turbulent flow of ocean currents are all extremely sensitive to changes. One tiny nudge could completely change the course of history.

How might this happen? Consider the consequences of adding a single electron at the edge of the observable universe. The gravitational pull of this electron is enough to disrupt the trajectories of all air molecules on Earth after [only 50 collisions](https://michaelberryphysics.files.wordpress.com/2013/07/berry174.pdf)... a fraction of a microsecond. This changes the atmospheric noise that [random.org](https://www.random.org/randomness/) uses to seed its random number generators, which changes the order in which my Spotify playlist gets shuffled[^2], which subtly affects my current mental state, which causes me to write this sentence with a different word order, and so on. In a matter of minutes, human events are unfolding in a measurably different fashion than they would have had that electron never existed.

[^2]: OK fine, Spotify doesn't use random.org to shuffle its playlists, but I'm just trying to give an illustrative example.

# The Formalization

We can use the random-seeming chaos generated by the Butterfly Effect to define a new notion of probability in a deterministic system. Informally, the "Butterfly Probability" of an event is the percentage of small perturbations to the current universe that result in that event occurring. To be more precise, I've come up with the following formalization.

Let $$\mathcal{U}$$ be the space of all possible universes. Every $$U \in \mathcal{U}$$ represents some particular arrangement of elementary particles (along with their velocities, spins, and so on) at a particular point in time. Think of this as a "snapshot" of a universe. One of the elements of $$\mathcal{U}$$ is a snapshot of our current universe -- let's call it $$U_0$$.

Since we're assuming a deterministic version of physics, we have some transition function $$f: \mathcal{U} \times \mathbb{R}_ {\geq 0} \to \mathcal{U}$$. This function takes in a universe snapshot and some $$t \geq 0$$, then outputs the configuration that this universe will be in after $$t$$ seconds.[^3]

[^3]: If you prefer an interpretation of physics in which time is discretized (as it is in a cellular automata), you can instead use a single-step transition function $$\hat f: \mathcal{U} \to \mathcal{U}$$. Then you can think of $$f(U, t)$$ as $$\hat f(\hat f( \cdots (U)))$$, where $$\hat f$$ is iterated $$t$$ times.

Now we define a distance metric on $$\mathcal{U}$$. This function $$d: \mathcal{U} \times \mathcal{U} \to \mathbb{R}_ {\geq 0}$$ takes in two universes $$U_1$$, $$U_2$$ and tells us how physically different they are. Think of this as an "edit distance" on the physical structure of the universe. We can use a definition along the lines of the following:

> In one operation, you can pay $$$x$$ to translate one atom/particle by $$x$$ meters or to change the velocity of an atom/particle by $$x$$ m/s. You can also pay $$$y$$ to add or delete an atom/particle of mass $$y$$. Then $$d(U_1, U_2)$$ is defined to be the minimum cost of any series of operations that transforms $$U_1$$ into $$U_2$$. 

The exact details of $$d$$ are unimportant. All that matters is that $$d$$ is a valid distance function on $$\mathcal{U}$$ that gets very close to $$0$$ when comparing two universes that are basically identical.

Now we're ready to define probability! Say we have some predicate $$r: \mathcal{U} \to \{0, 1\}$$ such as "Trump wins in 2024". $$r$$ takes in a universe snapshot and tells us whether or not a given event has occurred. If $$r$$ doesn't make sense on a given universe (for example, if you try to plug in a universe that has no Earth, or nobody named "Trump"), then it outputs $$0$$. Then we define the function $$P_{\mathcal{E}}$$ (parameterized by $$\mathcal{E} > 0$$) with type signature $$(\mathcal{U} \to \{0, 1\}) \times \mathcal{U} \times \mathbb{R}_ {\geq 0} \to [0, 1]$$:

$$\displaystyle P_{\mathcal{E}}(r, U_0, t) := \Pr_ {U \sim \mathcal{B}_ \mathcal{E}(U_0)} \left[r(f(U, t)) = 1\right]$$

Notice the subscript: $$U \sim \mathcal{B}_ \mathcal{E}(U_0)$$. This means that we are drawing a universe $$U$$ uniformly at random[^4] from all universes that satisfy $$d(U_0, U) < \mathcal{E}$$. In other words, it is sampling from the $$\mathcal{E}$$-ball of universes around $$U_0$$. The final value of $$P_{\mathcal{E}}$$ is the proportion of universes in this $$\mathcal{E}$$-ball that end up with $$r$$ being realized within the given timeframe $$t$$. Essentially, $$P_\mathcal{E}$$ is asking something like: "Given a uniformly random small perturbation to our universe, what's the probability that it results in Trump getting elected in 2024?"[^5]

[^4]: We technically haven't defined a preferred probability distribution on $$\mathcal{U}$$ for which we can invoke the phrase "uniformly at random". I suppose one way you could do this would be to think of $$\mathcal{U}$$ as $$\mathbb{R}^{6n}$$ (three spatial components and velocity components for each particle), where $$n$$ is the number of particles in the universe, and weight your probability distribution by $$6n$$-dimensional volume. Or you could think of $$\mathcal{U}$$ as being discretized by choosing some super small "precision level" at which to encode positions and velocities. But at this point we're just getting silly -- it really doesn't matter.

[^5]: Don't let it bother you that this definition involves a $$\Pr$$. We're not being circular because we're only constructing this definition for physical-world probabilities -- we're allowed to assume that the mathematical theory of probability rests on solid ground.

But we're not done yet. Our function is still parameterized by $$\mathcal{E}$$. Choosing different values of $$\mathcal{E}$$ will result in different answers -- which one do we mean by *the* probability of $$r$$?

Consider the following graph which shows how $$P_{\mathcal E}(r, U_0, t)$$ changes as we vary $$\mathcal{E}$$.

<div style="text-align:center;font-size:14px">
<img src="assets/butterfly-probability/graph1.png" width="100%"> <br>
</div>

For very large values of $$\mathcal{E}$$, $$P_{\mathcal{E}}$$ should be near $$0$$ because the $$\mathcal{E}$$-ball will mostly contain universes vastly different from $$U$$ -- most of them won't even have a human being named "Trump". As $$\mathcal{E}$$ shrinks, we start to get $$\mathcal{E}$$-balls that contain universes more similar to ours, so $$P_{\mathcal{E}}$$ becomes non-negligible. Finally, as $$\mathcal{E}$$ approaches $$0$$, $$P_{\mathcal{E}}$$ converges to some value, marked by the dotted line. This is what we define the true, unparameterized, "Butterfly's Probability" of $$r$$ to be -- the limit of $$P_\mathcal{E}$$ as $$\mathcal{E}$$ vanishes.

But wait! What happens if we zoom very far into the left part of this graph?

<div style="text-align:center;font-size:14px">
<img src="assets/butterfly-probability/graph2.png" width="100%">
<em>The graph after zooming in with respect to the horizontal axis (tick marks for scale).</em>
</div>

<br>

The value of $$P_\mathcal{E}$$ will hover around the dotted line for a while, but then it collapses to $$0$$ or $$1$$ at the very end. This corresponds to values of $$\mathcal{E}$$ that are extremely small: small enough that even the Butterfly Effect doesn't have enough time to produce much variation in the resultant universes. In other words, $$\mathcal{E}$$ is so small that we get the chain of implications

$$d(U_0, U) < \mathcal{E} \implies d(f(U_0, t), f(U, t)) \in O(1) \implies r(f(U_0, t)) = r(f(U, t)).$$

If we assume that the Butterfly Effect acts exponentially, this would require $$\mathcal{E}$$ to be double exponentially small (something like $$\mathcal{E} \approx 2^{-2^{100}}$$ should suffice for reasonable values of $$t$$).

This means that we can't actually define the Butterfly Probability as $$\lim_{\mathcal{E} \to 0} P_\mathcal{E}$$. Doing so would bring us back to our original problem of only having probabilities in $$\{0, 1\}$$. Instead, we have to define it as

> **Def.** The *Butterfly's Probability* of $$r$$ occurring within time $$t$$ is the value that $$P_\mathcal{E}(r, U_0, t)$$ converges to as $$\mathcal{E} \to 0$$, before it collapses to 0 or 1. 

I admit that the final caveat in the definition is imprecise, but I am at a loss for how to mathematically formulate this notion of "double convergence". However, I conjecture that in almost every example of a real-world probability, it will be abundantly clear what this almost-asymptote value should be by simply looking at the graph of $$P_\mathcal{E}$$. My intuition for this is explained in the next section.

# The Intuition

Essentially, I claim that the graph of $$P_{\mathcal{E}}$$ follows three qualitatively different regions. I'll redraw it here, with the horizontal scale modified to show all three regions at once.

<div style="text-align:center;font-size:14px">
<img src="assets/butterfly-probability/graph3.png" width="100%">
</div>

The behavior in each of these three regions is dominated by a different phenomenon. In the red region, the perturbations are too small for the Butterfly Effect to produce a noticeable difference in the universe over the given timescale. In the green region, the $$\mathcal{E}$$-ball is too big for the changes to be meaningful -- the sampled universes will simply be too different. Finally, the blue region describes the sweet spot in which the behavior of universes in the $$\mathcal{E}$$-ball is dominated by the Butterfly Effect.

Our definition of Butterfly Probability relies on the existence of a clear "phase shift" between each of the regions. If the cutoffs between the regions were less stark, then it might be ambiguous which value in the blue region we should count as the true probability. So why do I think that there is an obvious blue region? 

My intuition for this is that the Butterfly Effect is so chaotic and sensitive that, once $$\mathcal{E}$$ is large enough (but still small enough to have the changes be imperceptible to a human), there can be no large-scale structure in the locations of positive and negative perturbations. Imagine coloring each universe in $$\mathcal{U}$$ either black or white, depending on $$r(f(U, t))$$. Then the argument is that in the neighborhood of universes around $$U_0$$, the color of each point is basically random -- there is no pattern among the clustering of black or white universes. $$P_\mathcal{E}$$ will be equal to the proportion of black to white universes near $$U_0$$. It won't really go up or down as you grow $$\mathcal{E}$$ because that would require something like "rings" of darker or lighter regions centered around $$U_0$$, which constitutes large-scale structure.

The best way to think about this is by imagining the density of a gas. Fix some point $$p_0$$ in the air around you. Consider the average density of matter in the sphere centered at $$p_0$$ with radius $$r$$ -- in other words, the total amount of mass contained in the sphere, divided by the volume of the sphere. Start with $$r$$ set to $$10$$ meters, then consider what happens as $$r$$ shrinks to $$0$$. In the beginning, the density will vary a lot with $$r$$ -- the size of the radius will determine what ratio of the sphere is filled with solid matter. This corresponds to the green region above. But then once $$r$$ is small enough (perhaps less than a centimeter), the density stops changing with $$r$$ because the immediate vicinity of air around $$p_0$$ is homogenous and has some local density. This is the blue region. But once you shrink $$r$$ to be super small, the density collapses to either $$0$$ or $$10^{18}$$ kg/m^3, depending on if $$p_0$$ is located in the empty space between atoms or within a nucleus of an atom. This corresponds to the red region.

My intuition is that the distribution of black and white universes in $$\mathcal{U}$$ is qualitatively similar to the distribution of mass in a gas: locally homogenous at a small-but-not-atomically-small scale. This property of $$\mathcal{U}$$ -- having a continuous "local density" -- is really what we're getting at with Butterfly's Probability. Local density measures a meaningful property of the universe that is much more robust than the particular color it happens to be.

# Conclusion

To say that properly calculating the Butterfly's Probability of an event is computationally intractable would be the understatement of the century. Calculating even a single probability would require knowing the exact positions of all matter in the universe and the ability to simulate it with near-perfect accuracy. In fact, if the computer which you are using to simulate the universe is itself part of the universe, this leads to paradoxes. Because of this, the value of the Butterfly View formalism done in this blog post is mostly theoretical. It gives us a way to understand what probability would mean from the perspective of God (someone who is completely omniscient and computationally unbounded) without actually being able to carry it out in practice.

However, any time a political scientist or meteorologist builds a big model to predict the future, they are in some sense running an *approximation algorithm* of a Butterfly's Probability. In doing so, they make the implicit assumption that the blue region in the graph is large enough that lots of irrelevant information can be left out of the model without much effect on the local density of $$\mathcal{U}$$. For example, a meteorologist may exclude the presence of the Andromeda galaxy from her simulation -- but even though a universe without the Andromeda galaxy is quite different from ours, one can hope that it doesn't make a big difference on the probability of a predicate like "It rains tomorrow".

I will conclude with what I believe to be the strengths and weaknesses of the Butterfly View as a theoretical framework for understanding probability.

Strengths:
 - It combines features of the Bayesian and frequentist views: we can talk about the probabilities of one-off events like the 2024 election without the need for an epistemic reference frame or a prior distribution. 
 - It can be applied to any deterministic system without the need for built-in randomness, as long as the system is chaotic enough to exhibit the Butterfly Effect.
 - It accurately captures what people mean with the colloquial use of the word "random." When someone says "the stock market is hard to predict... it's so random," they probably don't mean that market volatility is caused by quantum randomness. Instead, it seems to me that they're trying to describe how there are too many sensitive moving parts for its behavior to be predicted with confidence.
 - It has a cool name.

Weaknesses:
 - As mentioned before, it is computationally intractable.
 - It cannot be adapted to deal with *logical* uncertainty (i.e. "What's the probability that the millionth digit of $$\pi$$ is a $$7$$?"). All of the "randomness" in the Butterfly View stems from physical uncertainty. But the decimal expansion of $$\pi$$ will always be the same no matter how atoms are perturbed, so the Butterfly's Probability of a mathematical statement is always either $$0$$ or $$1$$. 
 - It is time-dependent. Over short timeframes ("What's the probability that this coin flips heads in the next second?"), the Butterfly Effect might not have enough time to make much of a difference, so the probability will either be $$0$$ or $$1$$. Also, it is impossible to talk about probabilities of past events (unless you plug in a snapshot of the universe from before the event occurred).

As you can see, the Butterfly's View of probability has one more strength than it has weaknesses, making it a good theory!

Thank you for reading all of these words :).

<div style="text-align:center;font-size:14px">
<img src="assets/butterfly-probability/meme.png" width="70%">
</div>

<br>

***

<br>