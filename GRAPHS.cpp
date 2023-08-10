#include <bits/stdc++.h>
using namespace std;


//  breadth first search 
void
bfs (int curr, vector < vector < int >>&edges, vector < bool > &vis)
{
  queue < int >q;
  q.push (curr);
  vis[curr] = true;
  while (!q.empty ())
    {
      int t = q.front ();
      cout << t << " ";
      q.pop ();
    for (auto it:edges[t])
	{
	  if (!vis[it])
	    {
	      vis[it] = true;
	      q.push (it);
	    }
	}

    }

}

//  depth first search 
void
dfs (int curr, vector < vector < int >>&edges, vector < bool > &vis)
{

  vis[curr] = true;
  cout << curr << " ";

for (auto it:edges[curr])
    {
      if (!vis[it])
	{
	  dfs (it, edges, vis);
	}
    }
  cout <<"\n" ; 
}

//  find the components for each set of nodes ; 0th component , 1st component, 2nd etc ... 
void
dfs_for_components (int curr, vector < vector < int >>&edges,
		    vector < bool > &vis, int cnt, vector < int >&comp)
{

  comp[curr] = cnt;
  vis[curr] = true;
  //cout << curr <<" " ; 

for (auto it:edges[curr])
    {
      if (!vis[it])
	{
	  dfs_for_components (it, edges, vis, cnt, comp);
	}
    }

}

//  Detect cycle in an undirected graph
void
detect_cycle (int curr, vector < vector < int >>&edges, vector < bool > &vis,
	      vector < int >&parent)
{
  queue < int >q;
  q.push (curr);
  vis[curr] = true;

  while (!q.empty ())
    {

      int t = q.front ();
      cout << t << " ";
      q.pop ();
    for (auto it:edges[t])
	{
	  if (it == parent[t])
	    continue;
	  if (!vis[it])
	    {
	      vis[it] = true;
	      parent[it] = t;
	      q.push (it);
	    }
	  else
	    cout << "CYCLE FOUND\n";

	}
    }


}

int
main ()
{

  int n, m;			// n = nodes/vertices 
  cin >> n >> m;		// m = edges (n>=m) 


  vector < vector < int >>edges (n, vector < int >());	// creating an adjacency list

  for (int i = 0; i < m; ++i)
    {
      int u, v;
      cin >> u >> v;
      edges[u].push_back (v);
      edges[v].push_back (u);

    }

  vector < bool > visited (n, false);	// creating a boolean vector to keep a track of all visited nodes

  dfs (0, edges, visited);	//  call the dfs function 

  bfs (0, edges, visited);	//  call the bfs function  

  vector < int >components (n, -1);	// vector that keep note of the (n-1)th component of the graph 

  int cnt = 0;			// counts the number of componenets in a graph   

  for (int i = 0; i < n; ++i)
    {
      if (!visited[i])
	{
	  visited[i] = true;
	  dfs_for_components (i, edges, visited, cnt, components);	// dfs of all nodes one by one  
	  ++cnt;
	}
    }

  //  Display the component vector denoting the (n-1)thn component of the graph 
   for (auto it:components)
      cout << it << " ";

  vector < int >parent (n, -1);	// vector to keep track of each parent node 

  detect_cycle (0, edges, visited, parent);	// function to detect cycle in an undirected graph 


  return 0;
}
