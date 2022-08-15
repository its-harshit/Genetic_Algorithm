# I encountered a very interesting video by a YouTube channel named “Vesitarium”. It was about how luck and skill play a role for a person to become an astronaut. 
# Having recently read and learned about Genetic Algorithms, I thought of implementing them on this concept of the video. 
# Let’s assume that 100 people want to become an Astronaut. In order for them to be selected, we calculate their capability level. 
# The more the capable an individual is, the more is their chances of getting selected. 
# Capability turns out is dependent on 2 factors:
# • Skill (95%) • Luck (5%)
# I wanted to use Genetic Algorithm to simulate the ideal capability level that the candidate must have to be selected into Astronaut training program.
# The answer should come out to be 100% Capability (95% Skill + 5% Luck). This was a great way to implement my knowledge and concepts.

import numpy as np
import matplotlib.pyplot as plt
MUTATION_PROBABILITY = [0.02, 0.02]

class RandomVariable():
    def __init__(self):
        self.luck = 0
        self.skill = 0
        self.__calc_values()

    def __calc_values(self):
        self.luck = np.random.random() * 5
        self.skill = np.random.random() * 95
class Person():

    def __init__(self, luck, skill):
        self.luck = luck
        self.skill = skill
        self.capability = luck + skill

    def mate(self, par2):
        global MUTATION_PROBABILITY
        rv = RandomVariable()
        prob = np.random.rand(5)
        if prob[0] < (1-MUTATION_PROBABILITY[0])/2:
            new_luck = self.luck
        elif prob[0] < (1-MUTATION_PROBABILITY[0]):
            new_luck = par2.luck
        else:
            new_luck = rv.luck
        if prob[1] < (1-MUTATION_PROBABILITY[1])/2:
            new_skill = self.skill
        elif prob[1] < (1-MUTATION_PROBABILITY[1]):
            new_skill = par2.skill
        else:
            new_skill = rv.skill
        return Person(new_luck, new_skill)


class Generation():
    def __init__(self, parents, number):
        self.__parents = parents
        self.__number = number
        self.population = self.__mate()

    def __mate(self):
        population = []
        population.extend(self.__parents[:10])
        for i in range(90):
            par1 = np.random.choice(self.__parents[:30])
            par2 = np.random.choice(self.__parents[:30])
            child = par1.mate(par2)
            population.append(child)
        population = sorted(population,  key=lambda x: -x.capability)
        return population

    def print_fittest(self):
        print("Generation: {}".format(self.__number))
        print("    Capability: {}".format(self.population[0].capability))
        print("         Skill: {}".format(self.population[0].skill))
        print("          Luck:  {}".format(self.population[0].luck))

    def plot(self):
        plt.figure(figsize=(20, 10))
        plt.scatter(range(1, 101), [i.capability for i in self.population])
        plt.title("Generation " + str(self.__number))
        plt.xlabel("Person ID")
        plt.ylabel("Capability")
        plt.show()


population = []
for i in range(100):
    rv = RandomVariable()
    individual = Person(rv.luck, rv.skill)
    population.append(individual)
population = sorted(population, key=lambda x: -x.capability)
print("Generation: 1")
print("    Capability: {}".format(population[0].capability))
print("         Skill: {}".format(population[0].skill))
print("          Luck:  {}".format(population[0].luck))

plt.figure(figsize=(20, 10))
plt.scatter(range(1, 101), [i.capability for i in population])
plt.title("Generation 1")
plt.xlabel("Person ID")
plt.ylabel("Capability")
plt.show()

for i in range(2, 6):
    generation = Generation(population, i)
    generation.print_fittest()
    generation.plot()
    population = generation.population