#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int count = 0;

void countSplitInversion(vector<int> & v, vector<int> & w, int startL, int endL, int startR, int endR){
	int i = startL;
	int j = startR;
	int k = startL;
	while(i <= endL && j <= endR){
		if(v[i] <= v[j]){
			w[k] = v[i];
			i++;
		}else{
			w[k] = v[j];
			j++;
			count+= endL-i+1;
		}
		k++;
	}
	while(i <= endL){
		w[k] = v[i];
		i++; k++;
	}
	while(j <= endR){
		w[k] = v[j]; j++; k++;
	}
	
	for(int i = startL; i <= endR; i++){
		v[i] = w[i];
	}
}

void countingInversion(vector<int> & v, vector<int> & w, int start, int end){
	if(start >= end) return;
	int mid = (start + end) / 2;
	countingInversion(v,w,start,mid);
	countingInversion(v,w,mid+1,end);
	countSplitInversion(v,w,start,mid,mid+1,end);
}

void countingInversion(vector<int> & v){
	vector<int> w(v.size());
	countingInversion(v, w, 0, v.size()-1);
}

int main(){
	count = 0;	
	vector<int> v = {1,2,3,4,5,6};
	countingInversion(v);
	assert(count==0);
	v = {6,5,4,3,2,1};
	countingInversion(v);
	assert(count==15);
}
