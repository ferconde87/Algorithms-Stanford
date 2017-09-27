#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void swap(vector<int> & v, int i, int j){
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int mediaOfThree(vector<int> & v, int left, int mid, int right){
	int x = v[left];
	int y = v[mid];
	int z = v[right];
	if((x >= y && x <= z) || (x <= y && x >= z)) return left;
	if((y >= x && y <= z) || (y <= x && y >= z)) return mid;
	return right;
}

///return the index of the pivot
int choosePivotIndex(vector<int> & v, int left, int right){
	//assert(v.size()>0);
	//~ return left;//choose the first index as pivot
	//~ return right;//choose the last index as pivot
	int mid = (left+right)/2;//choose the media of three element
	return mediaOfThree(v, left, mid, right);
}

bool separateByPivot(vector<int> & v, int pivot, int left, int right, int i){
	//every element on the left is smaller than the pivot
	for(int j = left; j < i-1; j++){
		if(v[j] >= pivot) return false;
	}
	//the pivot is in 'i-1' position
	if(v[i-1] != pivot) return false;
	//every element on the right is greater or equal than the pivot 
	for(int j = i; j <= right; j++){
		if(v[j] < pivot) return false;
	}
	return true;
}

int partition(vector<int> & v, int left, int right){
	int index = choosePivotIndex(v, left, right);
	swap(v, left, index);///put the pivot in the first position
	int pivot = v[left]; 
	int i = left+1;
	for(int j = left+1; j <= right; j++){
		if(v[j] < pivot){
			swap(v, i, j);
			i++;
		}
	}
	swap(v, left, i-1);
	//assert(separateByPivot(v, pivot, left, right, i));
	return i-1;
}

void quickSort(vector<int> & v, int left, int right){
	if(left >= right) return;
	int index = partition(v, left, right);
	quickSort(v, left, index-1);
	quickSort(v, index+1, right);
}

void quickSort(vector<int> & v){
	quickSort(v, 0, v.size()-1);
}

void print(vector<int> & v){
	for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
}

int main(){
	//~ Unit test: 
	vector<int> v;
	v = {2,5,3,6,9,7,1,4,8};
	print(v);
	quickSort(v);
	print(v);
	v = {2,3,4,1};
	print(v);
	quickSort(v);
	print(v);
	
	v = {0,1,2,3};
	assert(mediaOfThree(v,1,2,3)==2);
	assert(mediaOfThree(v,2,2,3)==2);
	assert(mediaOfThree(v,2,2,2)==2);
	assert(mediaOfThree(v,1,2,2)==2);
	assert(mediaOfThree(v,3,1,2)==2);
	assert(mediaOfThree(v,2,3,1)==2);
	assert(mediaOfThree(v,3,2,1)==2);
}
