#include<stdio.h>
 
int getmax(int arr[], int n){
	int max=arr[0];
	for(int i=1;i<n;i++){
		if(arr[i]>max) max=arr[i];
	}
	return max;
} 

//int countDigit(int max){
//	int c=0;
//	while(max>0){
//		c++;
//		max /= 10;
//	}
//	return c;
//}

void countSort(int arr[], int n, int exp){
	int output[n];
	int i, count[10]={0};
	for(i=0;i<n;i++){
		count[(arr[i]/exp)%10]++;
	}
	for(i=1;i<10;i++){
		count[i]+=count[i-1];
	}
	for(i=n-1;i>=0;i--){
		output[--count[(arr[i]/exp)%10]]=arr[i];
	}
	for(i=0;i<n;i++){
		arr[i]=output[i];
	}
}

void radixSort(int arr[], int n){
	int max=getmax(arr,n);
	for(int exp=1; max/exp>0; exp*=10){
		countSort(arr,n,exp);
	}
}

void printArray(int arr[], int n){
	for(int i=0; i<n; i++){
		printf("%d ",arr[i]);
	}
}

int main(){
int arr[]= {24,56,12,67,89,45,69};
int n= sizeof(arr)/sizeof(arr[0]);
radixSort(arr,n);
printArray(arr,n);
return 0;
}

