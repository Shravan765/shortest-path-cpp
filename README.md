# shortest-path-cpp
Finding shortest path/route between two places using Dijkstra's algorithm  
You can use either dijkstra int.c++ (for integer distances) or dijkstra.c++ for distances in real numbers  
Once you compile the code, run it as follows  

./a.out  
distances.txt  
12087 (source vertex)   
3469  (destination vertex)  

Assumptions:  
source and t vertex are part of file given  
i.e. Vertex labels ONLY correspond to airport IDs given in the csv file  
Handles Floating distance (assuming no distance exceeds int_max)  

