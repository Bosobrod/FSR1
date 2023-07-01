#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
	ifstream inp("data_ks/ks_19_0");
	long long N, W;
	inp >> N >> W;
	vector <long long> v(N);
	vector <long long> w(N);
    //reading file
	for (int i = 0; i < N; i++) 
		inp >> v[i] >> w[i];


    vector <vector <long long> > sol(N, vector <long long> (W + 1, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= W; j++) {
			if (w[i] <= j) {
				if (i > 0) 
					sol[i][j] = max(sol[i - 1][j], sol[i - 1][j - w[i]] + v[i]);
				else 
					sol[i][j] = v[i];
			}
			else 
				if (i > 0) 
					sol[i][j] = sol[i - 1][j];
		}
	}

	vector <int> solution(N, 0);
	int i = N - 1, j = W;
	while (sol[i][j] && i>=1) 
	{
        if (sol[i][j] == sol[i - 1][j]) 
            i--;
        else if (sol[i][j] == v[i] + sol[i - 1][j - w[i]]) {
            solution[i] = 1;
            j -= w[i];
            i--;
        }
	}
	long long vsum = 0, wsum = 0;
	for (int i = 0; i < N; i++){
	    if (solution[i]) {
		    vsum += v[i];
		    wsum += w[i];
	    }
	}
	cout << vsum << endl;
	inp.close();
	return 0;
}