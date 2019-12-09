#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define  NORMAL_NUM         6
#define  SPE_NUM            1
#define  COMBINE_NUM        (SPE_NUM+NORMAL_NUM)

#define  NUM_MAX            49


#define ANALYSIS_PHASE      30
#define WEIGHT_SUM      3


uint8_t *srcDbData;

uint16_t CheckNum(uint8_t *srcData, uint8_t *dstData,  uint8_t normalCnt, uint8_t speCnt)
{
    uint8_t i, j, Cnt = 0;

    for(i = 0; i < normalCnt; i++)
    {
        for(j = 0; j < normalCnt; j++)
            if(srcData[i] == dstData[j])
                Cnt++;
    }

    for(i = 0; i < speCnt; i++)
    {
        for(j = 0; j < speCnt; j++)
            if(srcData[i+normalCnt] == dstData[normalCnt+j])
                Cnt++;
    }
    return Cnt;
}

void GetDataSum(uint32_t startPhase, uint32_t endPhase, uint8_t *normalSum, uint8_t* speSum)
{
    uint32_t i, j;

    memset(normalSum, 0, sizeof(normalSum));
    memset(speSum, 0, sizeof(speSum));

    for(i = startPhase; i <= endPhase; i++)
    {
        for(j = 0; j < (NORMAL_NUM+SPE_NUM); j++)
        {
            if(j < NORMAL_NUM)
                normalSum[srcDbData[COMBINE_NUM*i+j]]++;
            else
                speSum[srcDbData[COMBINE_NUM*i+j]]++;
        }
    }

    return analysisData;
}


uint8_t* GetWeight(uint8_t * sumData)
{
    uint16_t i, j;
    uint8_t weightSum[NUM_MAX];
    memset(weightSum, 0, NUM_MAX);
    for(i = WEIGHT_SUM/2; i < NUM_MAX-(WEIGHT_SUM/2))
    {
        for(j = i-(WEIGHT_SUM/2); i < WEIGHT_SUM; i++)
        {
            weightSum[i] += sumData[j];
        }
    }
}

void AnalysisWeight(uint16_t analysisPhaseTimes)
{
    uint8_t normalTemp[NUM_MAX], specTemp[NUM_MAX];
    GetDataSum(0, ANALYSIS_PHASE, normalTemp, specTemp);
    for()
}





int main()
{
    uint32_t maxPhase;
    uint8_t *srcDate, *dstData;

    printf("**************Congratulations, make a big asset!**************\n");

    for(i = ANALYSIS_PHASE-1; i < maxPhase; i++)
    {
        srcDate = 
    }

    return 0;
}
