#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<queue>
#include<set>
#include<map>

/*
Assumption : source and t vertex are part of file given
i.e. Vertex labels ONLY correspond to airport IDs given in the csv file
Handles Floating distance (assuming no distance exceeds __int_max__)

trial examples :

./a.out
airline_distances.txt         
12087
3469
Distance from 12087 to 3469 = 14293 
Path : 
12087 -> 3043 -> 3382 -> 3364 -> 3469 

./a.out
airline_distances.txt
12087
3720
Distance from 12087 to 3720 = 13686.1 
Path : 
12087 -> 3043 -> 3382 -> 3364 -> 3577 -> 3720

*/

using namespace std;

void init(map <float, vector< vector<float> > >&m, set<float>&nodes, string name)
{
    ifstream file(name);
    string temp = "";

    while(getline(file, temp))
    {
        istringstream iss(temp);
        vector<float>parts;
        string part;
        while (getline(iss, part, ',')) {
            parts.push_back(stof(part));
        }
        
        vector<float>v{parts[1], parts[2]};
        m[parts[0]].push_back(v);
        nodes.insert(parts[0]);
        nodes.insert(parts[1]);
        
    }
}

void print_path(map<float, float>p, map<float, float>d,  float s , float t);

void dijkstra(map <float, vector< vector<float> > > adj_list, set<float>nodes , float source, float t)
{

    map<float, float>parent;
    map<float, float>distance_from_source;

    for(float n : nodes)
    {
        parent[n] = -1;
        distance_from_source[n] = __INT_MAX__;
    }

    distance_from_source[source] = 0;

    priority_queue< vector<float> , vector< vector<float> >, greater< vector<float> > >pq; 
    //we store vertices in <distance, vertex>, and we specify the greater < vector<float> > to create a min heap

    pq.push({0,source});

    while(!pq.empty())
    {
        vector<float> temp = pq.top();
        float d = temp[0];
        float v = temp[1];
        pq.pop();

        if(d <= distance_from_source[v])
        {//only compute if we see a better path
            for(auto temp : adj_list[v])
            {//temp again is 1-d vector with 2 elements : node , distance
                float node = temp[0];
                float distance = temp[1];
                if(distance_from_source[v] + distance < distance_from_source[node])
                {
                    distance_from_source[node] = distance_from_source[v] + distance;
                    parent[node] = v;
                    pq.push( {distance_from_source[node], node} );
                }
            }
        }
    }

    /* for (int node : nodes) {
        
            
            print_path(parent, distance_from_source, source, node);
            
        
    } */

    print_path(parent, distance_from_source, source, t);

}

void print_path(map<float, float>p, map<float, float>d,  float s , float t)
{
    if(p[t] == -1)
    {
        if(t != s)
        {
            cout<<"No path exists from "<<s<<" to "<<t<<"\n";
            return;
        }
    }
    cout<<"Distance from "<<s<<" to "<<t<<" = "<<d[t]<<" \n";
    cout<<"Path : \n";
    vector<float>stk;
    float node = p[t];
    while(node != -1)
    {
        stk.push_back(node);
        node = p[node];
    }
    while(!stk.empty())
    {
        cout<< stk[stk.size()-1] <<" -> ";
        stk.pop_back();
    }
    cout<<t<<" \n";
}


int main()
{
    float source, t;
    string filename = "";
    cin>>filename;
    cin>>source;
    cin>>t;

    map <float, vector< vector<float> > > adj_list;
    set<float>nodes;
    init(adj_list, nodes, filename);
    

    /* for(auto&[k,v] : adj_list)
    {
        for(int i = 0; i<v.size();i++)
        {
            cout<<k<<" "<<v[i][0]<<" "<<v[i][1]<<"\n";
        }
    }  */
    dijkstra(adj_list, nodes, source, t);

}