#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define  NORMAL_NUM         6
#define  SPE_NUM            1

#define  COMBINE_NUM                (SPE_NUM+NORMAL_NUM)

#define  NORMAL_NUM_MAX             50
#define  SPECIAL_NUM_MAX            50


#define ANALYSIS_PHASE      30
#define WEIGHT_SUM      3

int norNumDb[4096][NORMAL_NUM];
int specNumDb[4096][SPE_NUM];
uint32_t maxPhase;

// int SPE_WEIGHT_LIST[SPE_NUM][10] = {
//     {0,1,,},
// }



// 检测有多少个数值符合
uint16_t CheckNum(int *norSrcData, int *norDstData, int *speSrcData, int *speDstData)
{
    int i, j, Cnt = 0;


    for(i = 0; i < NORMAL_NUM; i++)
    {
        for(j = 0; j < NORMAL_NUM; j++)
            if(norSrcData[i] == norDstData[j])
                Cnt++;
    }

    for(i = 0; i < SPE_NUM; i++)
    {
        for(j = 0; j < SPE_NUM; j++)
            if(speSrcData[j] == speDstData[j])
                Cnt++;
    }
    return Cnt;
}

// 检查指定数量有几个符合目标
uint16_t CheckTheAimNormalNum(int *srcData, int *dstData, int CheckNum)
{
    uint16_t i, j, luckyCnt = 0;
    for(i = 0; i < NORMAL_NUM; i++)
    {
        for(j = 0; j < CheckNum; j++)
        {
            if(srcData[j] == dstData[i])
            {
                luckyCnt ++;
                break;
            }
        }
    }
    return luckyCnt;
}

// 获取一段区间内的统计数据
void GetDataSum(uint32_t startPhase, uint32_t endPhase, int *normalSum, int* speSum)
{
    uint32_t i, j;

    memset(normalSum, 0, NORMAL_NUM_MAX);
    memset(speSum, 0, SPECIAL_NUM_MAX);

    for(i = startPhase; i <= endPhase; i++)
    {
        for(j = 0; j < (NORMAL_NUM); j++)
        {
            normalSum[norNumDb[i][j]]++;
            speSum[specNumDb[i][j]]++;
        }
    }

    return;
}


void GetSpeWeight(int * sumData, int *weightSum)
{
    uint16_t i, j;
    memset(weightSum, 0, dataNum);
    for(i = WEIGHT_SUM/2; i < dataNum-(WEIGHT_SUM/2); i++)
    {
        for(j = i-(WEIGHT_SUM/2); j < WEIGHT_SUM; j++)
        {
            weightSum[i] += sumData[j];
        }
    }
    return weightSum;
}

void GetNormalWeight(int * sumData, int *weightSum)
{
    uint16_t i, j;
    memset(weightSum, 0, dataNum);
    for(i = WEIGHT_SUM/2; i < dataNum-(WEIGHT_SUM/2); i++)
    {
        for(j = i-(WEIGHT_SUM/2); j < WEIGHT_SUM; j++)
        {
            weightSum[i] += sumData[j];
        }
    }
    return weightSum;
}


void AnalysisWeight(uint16_t analysisPhaseTimes)
{
    int normalTemp[NORMAL_NUM_MAX], specTemp[SPECIAL_NUM_MAX];
    GetDataSum(0, ANALYSIS_PHASE, normalTemp, specTemp);
}

void GetTheSSQ_Data(void)
{
    char filename[100] = ".\\src\\python\\ssq.csv"; //文件名
    char *ptr;
    FILE *fp;
    char StrLine[1024];             //每行最大读取的字符数
    uint32_t i, j;
    int  dataTemp[COMBINE_NUM];
    //getcwd(filename,100);
    if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
    {
        printf("error!");
        return;
    }

    i = 0;
    feof(fp);
    fgets(StrLine,1024,fp);  //读取一行
    while (!feof(fp))
    {
        memset(StrLine, 0, 1024);
        fgets(StrLine,1024,fp);  //读取一行

        ptr = strstr(StrLine, ",");
        if(ptr == NULL){
            i--;
            break;
        }

        ptr++;
        ptr = strstr(ptr, ",");
        ptr++;
        norNumDb[i][0] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        norNumDb[i][1] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        norNumDb[i][2] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        norNumDb[i][3] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        norNumDb[i][4] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        norNumDb[i][5] = atoi(ptr);

        ptr = strstr(ptr, "  ");
        ptr += 2;
        specNumDb[i][0] = atoi(ptr);

        printf("%d, %d, %d, %d, %d, %d, %d\n", norNumDb[i][0], norNumDb[i][1], norNumDb[i][2], norNumDb[i][3], norNumDb[i][4], norNumDb[i][5],
                                                 specNumDb[i][0]); //输出
        printf("%s\n", StrLine); //输出
        if(i>=4095)
            break;
        i++;
    }

    // 重新排序，序号越大的数据越新
    maxPhase = i;
    for(i = 0; i < (maxPhase+1)/2; i++){
        for(j = 0; j < NORMAL_NUM; j++){
            dataTemp[j] = norNumDb[i][j];
            norNumDb[i][j] = norNumDb[maxPhase-i][j];
            norNumDb[maxPhase-i][j] = dataTemp[j];
        }

        for(j = 0; j < SPE_NUM; j++){
            dataTemp[j] = specNumDb[i][j];
            specNumDb[i][j] = specNumDb[maxPhase-i][j];
            specNumDb[maxPhase-i][j] = dataTemp[j];
        }
    }
}



int main()
{
    int i, j, k;
    int normalSumTemp[NORMAL_NUM_MAX], speSumTemp[SPECIAL_NUM_MAX];
    int normalWeight[ANALYSIS_PHASE], specWeight[ANALYSIS_PHASE], normalWeightSum[ANALYSIS_PHASE], specWeightSum[ANALYSIS_PHASE];

    // printf("**************Congratulations**************\n");

    GetTheSSQ_Data();
    memset(normalSumTemp, 0, SPECIAL_NUM_MAX);
    memset(speSumTemp, 0, SPECIAL_NUM_MAX);

    memset(normalWeight, 0, ANALYSIS_PHASE);
    memset(specWeight, 0, ANALYSIS_PHASE);
    memset(normalWeightSum, 0, ANALYSIS_PHASE);
    memset(specWeightSum, 0, ANALYSIS_PHASE);
    
    while(1){
        for(i = 0; i < (maxPhase-ANALYSIS_PHASE); i++){
            // 获取该期间内各个数据出现的频率
            GetDataSum(i, i+ANALYSIS_PHASE, normalSumTemp, speSumTemp);
            // 计算出该期间的权重
            GetNormalWeight(normalSumTemp, normalWeight);
            GetSpeWeight(speSumTemp, specWeight);

        }
        
    }

    return 0;
}
