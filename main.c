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

uint8_t norNumDb[4096][NORMAL_NUM];
uint8_t specNumDb[4096][SPE_NUM];


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
    uint32_t  i;

    printf("**************Congratulations, make a big asset!**************\n");


    char filename[] = "D:\\ssq.csv"; //文件名
    char *ptr;
    FILE *fp;
    char StrLine[1024];             //每行最大读取的字符数
    if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
    {
        printf("error!");
        return -1;
    }

    i = 0;
    feof(fp);
    fgets(StrLine,1024,fp);  //读取一行
    while (!feof(fp))
    {
        memset(StrLine, 0, 1024);
        fgets(StrLine,1024,fp);  //读取一行

        ptr = strstr(StrLine, ",");
        if(ptr == NULL)
            break;
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
        i++;
        if(i>=4095)
            break;
    }

    return 0;
}
