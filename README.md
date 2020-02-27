# Lem-in
Graph Algorithm Project @ 42

Lem-in is an algorithmic project that relies on graph theory. The aim is to 
find the shortest and quickest solution for a number of ants to traverse an 
ant colony (the graph) from the source node to the sink node in the least 
amount of steps.
To achieve this we will need to find the maximum flow through the shortest path or paths.
For this project, I used an adaptation of the Edmonds-Karp algorithm 
(based on the Ford-Fulkerson algorithm).

Input:
- number of ants
- the rooms (vertex)
- the links (edges)

Output:
- the input
- the solution (paths + nbr of steps)

The constraints:

- An ant can only move once per turn.
- A room (vertex) can only contain one ant (except the source and the sink).
- The program must take less than 2 seconds. Therefore the algorithm has to<br>
avoid trafic jam and overlapping.

## Usage

git clone https://github.com/MathieuJouffroy/Lem-in.git && cd Lem-in && make

./lem-in < maps/[map_name]

#### Map example
![Lem-in](images/map.png)

It's graphical representation<br>
![Lem-in](images/graph.png)

Comments "##start" and '##end' indicates the sink and source node respectively.
They must be linked together (graph traversal).

## Example 
#### 1000 rooms (vertices)
./lem-in < maps/1000.map -s -c<br>

![Lem-in](images/example.png)

- -s option will indicate the number of steps required to move all the ants from the<br>
source to the sink
- -c option adds color to differenciate the paths

