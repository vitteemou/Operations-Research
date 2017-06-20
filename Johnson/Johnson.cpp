#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//Johnson's scheduling algorithm implementation
//Detail has its processing time 'a' on the machine A and processing time 'b' on the machine B

class Detail 
{
 public:
	int a; 
	int b;

        int min(int a, int b)
        {
                return a < b ? a : b;
        }

	bool operator < (Detail p) const 
	{
		return min(a, b) < min(p.a, p.b);
	}
};

int main()
{
	int n;
	cin >> n;

	vector<Detail> all_details(n);
	for(int i = 0; i < n; i++)
	{
		cin>>all_details[i].a;
		cin>>all_details[i].b;
	}
	sort (all_details.begin(), all_details.end());

	vector<Detail> a;
	vector<Detail> b;
	for (int i = 0; i < n; i++)
	{
		(all_details[i].a <= all_details[i].b ? a : b).push_back(all_details[i]);
	}
	a.insert (a.end(), b.rbegin(), b.rend());
	 
	int time1 = 0;
	int time2 = 0;
	for (int i = 0; i < n; i++) 
	{ 
		time1 += a[i].a;
		time2 = max(time2, time1) + a[i].b;
	}
	
	cout << "Min time: " << time1 << endl;
	return 0;
}
