#include <stdio.h>

#define INPUT_MAX 3 //輸入預設數量
#define DEFAULT_VALUE_MAX 99999999 //輸入預設最大值
#define ARRAY_MAX 50 //預設記錄資料陣列大小
#define DEBUG 0 //印出資訊

typedef struct{
    unsigned int data[ARRAY_MAX];
    unsigned int index;
}LogArray;//記錄資料及位置用

void findPrime(unsigned int *_val, LogArray* _result){
    unsigned int val = *_val;
    int i=0;

    _result->index = 0;
    for(i=2; i<=val; i++){//質因數分解
        while(val!=i){
            if((val%i)==0){
                val=val/i;
                _result->data[_result->index++] = i;
            }else{
                break;
            }
        }
    }
    _result->data[_result->index] = val;

    #if DEBUG //顯示分解結果
    for(i=0; i<_result->index+1; i++){
        if(i==_result->index){
            printf("%d\r\n",_result->data[i]);
        }else{
            printf("%d*",_result->data[i]);
        }
    }
    #endif
}

int getE10(int i){//計算10^i
    if(i--){
        return 10*getE10(i);
    }else{
        return 1;
    }
}

unsigned int findMultiply(unsigned int *_val, LogArray* _result){
    unsigned int val = *_val;
    int i=0,j=0,res=0,index=0,multi=1,e10=1;

    if(val == _result->data[_result->index] || (_result->data[_result->index]>10)){
        res=-1;//如果分解結果最後一碼和自己相同或是大於10則找不出最小整數乘法
    }else{
        for(i=_result->index; i>0; i--){
            if((multi*_result->data[i]*_result->data[i-1]) < 10){
                multi*=_result->data[i];
            }else{
                #if DEBUG
                printf("%d",multi*_result->data[i]);
                #endif
                e10 = getE10(index++);
                res += multi * _result->data[i] * e10;
                multi=1;
            }
        }
        e10 = getE10(index++);
        res += multi*_result->data[i] * e10;
        #if DEBUG
        printf("%d\r\n",multi*_result->data[i]);
        #endif
    }
    return res;
}

unsigned int findAnswer(unsigned int *_input) {
    LogArray log1;//記錄質因數分解結果

    //1.
    findPrime(_input, &log1);//質因數分解

    //2.
    return findMultiply(_input, &log1);//找出最小整數相乘
}

int main()
{
    unsigned int input[INPUT_MAX];//存輸入值
    unsigned int result[INPUT_MAX];//存計算結果
    unsigned int defaultMax = DEFAULT_VALUE_MAX;//預設最大值
    int i;

    for(i=0;i<INPUT_MAX;i++){
    retry:
        printf("input%d:",i+1);
        scanf("%d", &input[i]);//輸入資料
        if(input[i]>=defaultMax){ //檢查輸入資料小於最大值
            printf("input%d must < %d retry...\r\n",i+1,defaultMax);
            goto retry;
        }
        result[i] = findAnswer(&input[i]);//計算最小整數乘法
    }

    for(i=0;i<INPUT_MAX;i++){
        printf("Result%d:%d\r\n",i+1,result[i]);//印出結果
    }
    return 0;
}
