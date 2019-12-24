#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define  NORMAL_NUM         6
#define  SPE_NUM            1

#define  COMBINE_NUM                (SPE_NUM+NORMAL_NUM)

#define  NORMAL_NUM_MAX             49
#define  SPECIAL_NUM_MAX            49


#define ANALYSIS_PHASE      30
#define WEIGHT_SUM      3

uint8_t norNumDb[1024][NORMAL_NUM];
uint8_t specNumDb[1024][SPE_NUM];


// 检测有多少个数值符合
uint16_t CheckNum(uint8_t *norSrcData, uint8_t *norDstData, uint8_t *speSrcData, uint8_t *speDstData)
{
    uint8_t i, j, Cnt = 0;


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
uint16_t CheckTheAimNormalNum(uint8_t *srcData, uint8_t *dstData, uint8_t CheckNum)
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
void GetDataSum(uint32_t startPhase, uint32_t endPhase, uint8_t *normalSum, uint8_t* speSum)
{
    uint32_t i, j;

    memset(normalSum, 0, NORMAL_NUM_MAX);
    memset(speSum, 0, SPECIAL_NUM_MAX);

    for(i = startPhase; i <= endPhase; i++)
    {
        for(j = 0; j < (NORMAL_NUM); j++)
        {
            normalSum[norNumDb[i][j]-1]++;
            speSum[specNumDb[i][j]-1]++;
        }
    }

    return;
}


uint8_t* GetWeight(uint8_t * sumData)
{
    uint16_t i, j;
    static uint8_t weightSum[NORMAL_NUM_MAX];
    memset(weightSum, 0, NORMAL_NUM_MAX);
    for(i = WEIGHT_SUM/2; i < NORMAL_NUM_MAX-(WEIGHT_SUM/2); i++)
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
    uint8_t normalTemp[NORMAL_NUM_MAX], specTemp[NORMAL_NUM_MAX];
    GetDataSum(0, ANALYSIS_PHASE, normalTemp, specTemp);
}





int main()
{
    uint32_t maxPhase, i;

    printf("**************Congratulations, make a big asset!**************\n");

    for(i = ANALYSIS_PHASE-1; i < maxPhase; i++)
    {

    }

    return 0;
}
