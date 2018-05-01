//*************************************************************************************
//Frank MacDonald
//Cs3610 Project 4
//April 11, 2018
//A project to simulate an external sorting algorithm
//*************************************************************************************
#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;
//*************************************************************************************
int partition(vector<int>& list, int first, int last) 
{
  // The pivot should be the median of the
  // first, middle, and last elements.

	int f = list[first];
	int m = list[(first+last)/2];
	int l = list[last];

		if(f <= m && m <= l){return (first+last)/2;}
		if(l <= m && m <= f){return (first+last)/2;}
		if(m <= f && f <= l){return (first);}
		if(l <= f && f <= m){return (first);}
		if(m <= l && l <= f){return (last);}
		if(f <= l && l <= m){return (last);}
		
}
//*************************************************************************************
void quicksort(vector<int>& list, int first, int last) 
{	
	if(first < last)
	{
		int list_position = partition(list,first,last);
		quicksort(list, first, list_position-1);
		quicksort(list, list_position+1, last);
	}
}
//*************************************************************************************
void multiway_merge(vector<vector<int> >& input_lists, vector<int>& output_list) 
{
	// You can use a priority queue to automatically merge the split lists.	
	priority_queue <int, vector<int>, greater<int> > PrioQ;
	
	int position = 0;
	int row = input_lists.size();
	int col = input_lists[0].size();

	int i = 0;
	while(i < row)
	{
		int j = 0;
		while(j < col)
		{
			PrioQ.push(input_lists[i][j]);
			j++;
		}
		i++;
	}
	while(!PrioQ.empty())
	{
		output_list[position] = PrioQ.top();
		position++;
		PrioQ.pop();
	}
} 
//*************************************************************************************
int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;
}
//*************************************************************************************
