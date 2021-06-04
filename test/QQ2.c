#include <stdio.h>
#include <stdint.h>

void merge(int32_t list[],int32_t sorted[] ,int32_t begin ,int32_t end) {
    int32_t mid = (begin + end)/2;
    if(begin == end) {
        return ;
    }
    merge(list,sorted,begin,mid);
    merge(list,sorted,mid+1,end);
    int32_t lindex = begin;
    int32_t rindex = mid+1;
    int32_t sindex = begin;
    while(lindex <= mid && rindex <= end) {
        if(list[lindex] <= list[rindex]) {
            sorted[sindex++] = list[lindex++];
        }
        else if(list[lindex] > list[rindex]) {
            sorted[sindex++] = list[rindex++];
        }
    }
    while(lindex <= mid) {
        sorted[sindex++] = list[lindex++];
    }
    while(rindex <= end) {
        sorted[sindex++] = list[rindex++];
    }
    for(int32_t i = begin ; i < sindex ; i++)
    {
        list[i] = sorted[i];
    }
}

void binarySearch(int32_t left ,int32_t right ,int32_t list[] ,int32_t dist[],int32_t index,int32_t limit) {
    if(index > limit) {
        return ;
    }
    int32_t middle = (left+right)/2;
    int32_t L_dist = list[middle] - list[left];
    int32_t R_dist = list[right] - list[middle];
    if(middle == left) {
        L_dist = -1;
    }
    if(right == middle) {
        R_dist = -1;
    }
    if(L_dist >= 0 && R_dist >= 0 && L_dist < R_dist) {
        dist[index] = L_dist;
        printf("dist[%d]: %d\n", index, dist[index]);
        binarySearch(middle+1,right,list,dist,index+1,limit);
    }
    else if(L_dist >= 0 && R_dist >= 0 && L_dist > R_dist) {
        dist[index] = R_dist;
        printf("dist[%d]: %d\n", index, dist[index]);
        binarySearch(left,middle-1,list,dist,index+1,limit);
    }
    else if(L_dist < 0 && R_dist >= 0) {
        dist[index] = R_dist;
        printf("dist[%d]: %d\n", index, dist[index]);
    }
    else if(R_dist < 0 && L_dist >= 0) {
        dist[index] = L_dist;
        printf("dist[%d]: %d\n", index, dist[index]);
    }
}

void print(int32_t list[],int32_t n) {
    for(int32_t i = 0 ; i < n ; i++) {
        printf("%d ",list[i]);
    }
    printf("\n");
} 

int main() {
    int32_t n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int32_t input[20005] = {0};
    int32_t sorted[20005] = {0};
    int32_t distance[20005] = {0};
    for(int32_t i = 0 ; i < n ; i++) {
        scanf("%d",&input[i]);
    }
    if(n == 1) {
        printf("0\n");
        return 0;
    }
    merge(input,sorted,0,n-1);
    binarySearch(0,n-1,sorted,distance,1,m);
    for(int32_t i = 1 ; i < m ; i++) {
        printf("%d ",distance[i]);
    }
    printf("\n");
    int32_t ans = distance[1];
    for(int32_t i = 1 ; i <= m ; i++) {
        if(distance[i] > ans) {
            ans = distance[i];
        }
    }
    printf("%d\n",ans);
}

/*

1 2 3 10 11 12 13





*/