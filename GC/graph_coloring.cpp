#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	ifstream file("data_gc/gc_70_9");
	int v, e; 
	file >> v >> e;

	vector <pair <int, int> > edges(e);
	for (int i = 0; i < e; i++) 
	{
		file >> edges[i].first >> edges[i].second;
	}

	vector<int> color(v, 0);
	color[0] = 1;
	for (int i = 1; i < v; i++) {				
	    set <int> colors;

	    for (int j = 0; j < e; j++){				
	        if (edges[j].first == i)			
	            colors.insert(color[edges[j].second]);			
	        else if (edges[j].second == i) 		       
	            colors.insert(color[edges[j].first]);		       
	    }
        set <int>::iterator search;
        for (int j = 1; j < v + 1; j++) {			
            search = colors.find(j);				
            if (search == colors.end()){				
                color[i] = j;						
                break; 
            }
        }
	}

    sort(color.begin(), color.end());
	cout << *(color.end() - 1)<<endl;
	file.close();
}