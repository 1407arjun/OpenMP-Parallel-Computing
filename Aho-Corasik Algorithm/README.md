# Aho-Corasik Algorithm

### Question

Implement the operations of Aho-Corasick Algorithm for Pattern Searching in serial and parallel (using OpenMP). Print the time taken for both the cases. [Solution File](./solution.cpp)

### Solution (C++)

```Cpp
#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

const int MAXS = 500;
const int MAXC = 26;
int out[MAXS], f[MAXS], g[MAXS][MAXC];

int findNextState(int currentState, char nextInput) {
	int answer = currentState;
	int ch = nextInput - 'a';

	while (g[answer][ch] == -1)
		answer = f[answer];

	return g[answer][ch];
}

int buildMatchingMachine_serial(string arr[], int k) {
	memset(out, 0, sizeof out);
	memset(g, -1, sizeof g);

	int states = 1;
    for (int i = 0; i < k; ++i) {
        const string &word = arr[i];
        int currentState = 0;

        for (int j = 0; j < word.size(); ++j) {
            int ch = word[j] - 'a';
            if (g[currentState][ch] == -1) {
                states++;
                g[currentState][ch] = states;
            }

            currentState = g[currentState][ch];
        }

        out[currentState] |= (1 << i);
    }

    for (int ch = 0; ch < MAXC; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;

    memset(f, -1, sizeof f);
    queue<int> q;


    for (int ch = 0; ch < MAXC; ++ch) {
        if (g[0][ch] != 0) {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    while (q.size()) {
        int state = q.front();
        q.pop();

        for (int ch = 0; ch <= MAXC; ++ch) {
            if (g[state][ch] != -1) {
                int failure = f[state];
                while (g[failure][ch] == -1)
                    failure = f[failure];

                failure = g[failure][ch];
                f[g[state][ch]] = failure;
                out[g[state][ch]] |= out[failure];
                q.push(g[state][ch]);
            }
        }
    }

	return states;
}

int buildMatchingMachine_parallel(string arr[], int k) {
	memset(out, 0, sizeof out);
	memset(g, -1, sizeof g);

	int states = 1;
    queue<int> q;
    #pragma omp parallel shared(states, q)
    {
        #pragma omp for
        for (int i = 0; i < k; ++i) {
            const string &word = arr[i];
            int currentState = 0;

            for (int j = 0; j < word.size(); ++j) {
                int ch = word[j] - 'a';
                if (g[currentState][ch] == -1) {
                    states++;
                    g[currentState][ch] = states;
                }

                currentState = g[currentState][ch];
            }

            out[currentState] |= (1 << i);
        }

        #pragma omp for
        for (int ch = 0; ch < MAXC; ++ch)
            if (g[0][ch] == -1)
                g[0][ch] = 0;

        memset(f, -1, sizeof f);

        #pragma omp for
        for (int ch = 0; ch < MAXC; ++ch) {
            if (g[0][ch] != 0) {
                f[g[0][ch]] = 0;
                q.push(g[0][ch]);
            }
        }

        while (q.size()) {
            int state = q.front();
            q.pop();

            #pragma omp for
            for (int ch = 0; ch <= MAXC; ++ch) {
                if (g[state][ch] != -1) {
                    int failure = f[state];
                    while (g[failure][ch] == -1)
                        failure = f[failure];

                    failure = g[failure][ch];
                    f[g[state][ch]] = failure;
                    out[g[state][ch]] |= out[failure];
                    q.push(g[state][ch]);
                }
            }
        }
    }

	return states;
}

void searchWords_serial(string arr[], int k, string text) {
	buildMatchingMachine_serial(arr, k);

	int currentState = 0;
    for (int i = 0; i < text.size(); ++i) {
		currentState = findNextState(currentState, text[i]);
		if (out[currentState] == 0)
			continue;

		for (int j = 0; j < k; ++j) {
			if (out[currentState] & (1 << j)) {
				cout << "Word " << arr[j] << " appears from "
					<< i - arr[j].size() + 1 << " to " << i << endl;
			}
		}
	}
}

void searchWords_parallel(string arr[], int k, string text) {
	buildMatchingMachine_parallel(arr, k);

	int currentState;

	#pragma omp parallel for private(currentState)
    for (int i = 0; i < text.size(); ++i) {
		currentState = findNextState(currentState, text[i]);
		if (out[currentState] == 0)
			continue;

		for (int j = 0; j < k; ++j) {
			if (out[currentState] & (1 << j)) {
				cout << "Word " << arr[j] << " appears from "
					<< i - arr[j].size() + 1 << " to " << i << endl;
			}
		}
	}
}

int main() {
    printf("Aho-Corasik Algorithm\n\n");
	string text = "helloworld";
    string arr[] = {"ll", "or", "ld"};
	int k = sizeof(arr)/sizeof(arr[0]);
    double start, end;

    start = omp_get_wtime();
	searchWords_serial(arr, k, text);
    end = omp_get_wtime();

    cout<<"Time in serial: "<<end-start<<endl<<endl;

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
	    searchWords_parallel(arr, k, text);
    }
    end = omp_get_wtime();

    cout<<"Time in parallel: "<<end-start<<endl;

	return 0;
}
```
