#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<queue>
#include<set>
#include<map>

using namespace std;

void init(map <int, vector< vector<int> > >&m, set<int>&nodes, string name)
{
    ifstream file(name);
    string temp = "";

    while(getline(file, temp))
    {
        istringstream iss(temp);
        vector<int>parts;
        string part;
        while (getline(iss, part, ',')) {
            parts.push_back(stoi(part));
        }
        
        vector<int>v{parts[1], parts[2]};
        m[parts[0]].push_back(v);
        nodes.insert(parts[0]);
        nodes.insert(parts[1]);
        
    }
}

void print_path(map<int, int>p, map<int, int>d,  int s , int t);

void dijkstra(map <int, vector< vector<int> > > adj_list, set<int>nodes , int source, int t)
{

    map<int, int>parent;
    map<int, int>distance_from_source;

    for(int n : nodes)
    {
        parent[n] = -1;
        distance_from_source[n] = __INT_MAX__;
    }

    distance_from_source[source] = 0;

    priority_queue< vector<int> , vector< vector<int> >, greater< vector<int> > >pq; 
    //we store vertices in <distance, vertex>, and we specify the greater < vector<int> > to create a min heap

    pq.push({0,source});

    while(!pq.empty())
    {
        vector<int> temp = pq.top();
        int d = temp[0];
        int v = temp[1];
        pq.pop();

        if(d <= distance_from_source[v])
        {//only compute if we see a better path
            for(auto temp : adj_list[v])
            {//temp again is 1-d vector with 2 elements : node , distance
                int node = temp[0];
                int distance = temp[1];
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

void print_path(map<int, int>p, map<int, int>d,  int s , int t)
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
    vector<int>stk;
    int node = p[t];
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
    int source, t;
    string filename = "";
    cin>>filename;
    cin>>source;
    cin>>t;

    map <int, vector< vector<int> > > adj_list;
    set<int>nodes;
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