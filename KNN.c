#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SAMPLE_CNT 150
#define ATTR_CNT 4
#define K 23

struct Iris{
 double attr[ATTR_CNT];
  int label;
};

char pr[20]; //用于存放类别
struct Iris Iris[SAMPLE_CNT];
double loca[SAMPLE_CNT-1]; //记录样本排序前的位置
double attr[ATTR_CNT];
//Iris-setosa=1
//Iris-versicolor=2
//Iris-virginica=3
void ReadFile()
{
  FILE *fp;
  int i=0;
fp=fopen("Iris.txt","rb");
 
if(!feof(fp)) 
    //printf("s!");

  while(!feof(fp))
  {
   fscanf(fp,"%lf,%lf,%lf,%lf,%s",&(Iris[i].attr[0]),&(Iris[i].attr[1]),&(Iris[i].attr[2]),&(Iris[i].attr[3]),pr);
    
    if(!strcmp(pr,"Iris-setosa"))
		Iris[i].label=1;

    if(!strcmp(pr,"Iris-versicolor"))
   		Iris[i].label=2;

    if(!strcmp(pr,"Iris-virginica"))
		Iris[i].label=3;
    i++;
  }
  fclose(fp);
}


void swap(double *a,double *b)
{
  double tmp;
  tmp=*a;
   *a=*b;
  *b=tmp;
}

int  Paration(double *w,int p,int r)
{//p,r表示下标
  int i=p,j;
  int val=w[p];

  for(j=p+1;j<=r;j++)
  {
	  if(val>=w[j])
	  {
		 i++;
         swap(&w[i],&w[j]);
		 swap(&loca[i],&loca[j]);
	  }
  }
	swap(&w[i],&w[p]);
	swap(&loca[i],&loca[p]);

   return i;
}


void QuickSort(double *w,int p,int r)
{
  int q=Paration(w,p,r);
  if(p<r)
  {
	  QuickSort(w,p,q-1);
      QuickSort(w,q+1,r);
  }
}


void Bubblesort(double a[], int n)
{
    int i, j, temp;
  
    for (j = 0; j < n - 1; j++)
    for (i = 0; i < n - 1 - j; i++)
      if(a[i] > a[i + 1])
         {
         swap(&a[i],&a[i+1]);
         swap(&loca[i],&loca[i+1]);
         }
}


//KNN
void predict()
{
   int i,j,k;
   int label;
   int plabel;
   int predT=0;
   int h,maxscore;
   int classNum[3];
   
   double dis[SAMPLE_CNT];

   ReadFile();

  for(i=0;i<SAMPLE_CNT;i++)
  {
       h=0;

	//测试样本 (使用留一法)
	label = Iris[i].label;
    
   //测试样本属
    for(j=0;j<ATTR_CNT;j++)
      attr[j]=Iris[i].attr[j];
 
   //以便下一个测试样本使用
    for(j=0;j<SAMPLE_CNT-1;j++)
      dis[j]=0;
  
    for(j=0;j<ATTR_CNT;j++)
      classNum[j]=0;      

    //训练样本中和测试样本的距离?
	 for(j=0;j<SAMPLE_CNT;j++)
	  {
         if(j!=i) 
       {                    
		for(k=0;k<ATTR_CNT;k++)
		{
		   dis[h]+=(attr[k]-Iris[j].attr[k])*(attr[k]-Iris[j].attr[k]);
		   
		   loca[h]=Iris[j].label;
		}
          h++;
       }
	  }

      //QuickSort(dis,0,h-1);
        Bubblesort(dis,h); 
         
	  //K邻域中各类的数量\E3\80?
	  for(j=0;j<K;j++)
	    classNum[(int)loca[j]-1]++;

	  printf("��%d������,ʵ������Ϊ%d\n",i,label);
	  printf("%d   %d��%d\n",classNum[0],classNum[1],classNum[2]);

     maxscore=(classNum[0]>classNum[1]?classNum[0]:classNum[1])>classNum[2]?(classNum[0]>classNum[1]?classNum[0]:classNum[1]):classNum[2]; //最大\E5\80?

	  if(classNum[0]==maxscore)
        plabel=1;
    if(classNum[1]==maxscore)
        plabel=2;
    if(classNum[2]==maxscore)
        plabel=3;

      if(label==plabel)
		  predT++;
  }

   printf("true %lf\n",(double)predT/SAMPLE_CNT);

}


int main()
{
  	predict();
  	getch();
    return 1;
}



