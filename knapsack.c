#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
  int weight;
  int value;
  char name[32];
} item;

int
max (int a, int b)
{
  return (a > b) ? a : b;
}

void
findknapSack (int W, int wt[], int val[], int n, int indexList[], int ValueWeight[])
{
  int i, w;
 // int K[n + 1][W + 1];      // variable length array change this
  int K[256][256];    

  for (i = 0; i <= n; i++) // table 
    {                                  
      for (w = 0; w <= W; w++)          
	{
	  if (i == 0 || w == 0)             // double check this part
	    K[i][w] = 0;
	  else if (wt[i - 1] <= w)
	    K[i][w] = max (val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
	  else
	    K[i][w] = K[i - 1][w];
	}
    }

  // store res of Knapsack

  int res = K[n][W];
  int totalValue = K[n][W];
  int totalWeight = 0;

  w = W;
  for (i = n; i > 0 && res > 0; i--)
    {
      if (res == K[i - 1][w])
	continue;
      else
	{

	  // This item is included.

	  // If an index of a return item is included, assign 2.
	  indexList[i - 1]=2 ;
	  
	  totalWeight = wt[i - 1] + totalWeight;
	  res = res - val[i - 1];
	  w = w - wt[i - 1];
	}
    }

  ValueWeight[0] = totalValue;
  ValueWeight[1] = totalWeight;
  return;

}

void
callKnapSack (item *i, int itemcount, int weight_limit)
{				// make struct into int[]


  int *weights = (int *) malloc (sizeof (int *) * itemcount);
  int *values = (int *) malloc (sizeof (int *) * itemcount);
  int *indexList = (int *) malloc (sizeof (int *) * itemcount);
  int *ValueWeight = (int *) malloc (sizeof (int *) * 2);


  int j;
  for (j = 0; j < itemcount; j++)
    {
  //  printf("%d\n", i[j].weight)   ; 
      weights[j] = i[j].weight;
      values[j] = i[j].value;
    }
    //printf("itemcount:%d, weight_limit:%d", itemcount, weight_limit);

 //   for(j=0;j<itemcount;j++){
 //   printf("weight %d,value  %d \n", weights[j], values[j]);
 //   }
 
  
  findknapSack (weight_limit, weights, values, itemcount, indexList, ValueWeight);
  
  for (j = 0; j < itemcount; j++)
  {
      if(indexList[j]==2){
      	printf("%s\n", i[j].name);
      }
  }
  printf ("%d / %d\n", ValueWeight[0], ValueWeight[1]);

  free(weights);
  free(values);
  free(indexList);      // double check frees, pls no memory leak
  free(ValueWeight);

  return;
}

void
READvalueWeight (FILE * fp, int *weights, int *values, int itemcount)
{
 // int j, i;


  struct item itemList[256];
  int itemsIndex = 0;


  char temp[250];
  while (NULL != fgets (temp, 120, fp))
    {
      sscanf (temp, "%s %d %d", itemList[itemsIndex].name,
	      &itemList[itemsIndex].value, &itemList[itemsIndex].weight);
      itemsIndex++;		// ad degistir belki
    }
  /*
     for (i = 0; i < itemsIndex; i++)
     {
     printf(" %s %d %d\n", itemList[i].name, itemList[i].weight, itemList[i].value);
     }
   */
  return;
}

FILE *
ReadFile (char **argv, int argc)
{
  FILE *fp;
  if (argc == 3)
    {				//argc2 = weight limit, argc3 = filename.txt
      fp = fopen (argv[2], "r");
    }
  return fp;
}

// Driver Code

int
main (int argc, char **argv)
{



  int weight_limit;
  sscanf (argv[1], "%d", &weight_limit);

  FILE *fp = ReadFile (argv, argc);
  int itemcount;
  fscanf (fp, "%d\n", &itemcount);




//  int j, i;
  struct item itemList[128];
  int itemsIndex = 0;


  char temp[250];
  while (NULL != fgets (temp, 120, fp))
    {
      sscanf (temp, "%31s %d %d", itemList[itemsIndex].name,
	      &itemList[itemsIndex].weight, &itemList[itemsIndex].value);
      itemsIndex++;		
    }

    //printf("limit: %d \n", weight_limit);
  /*
     for (i = 0; i < itemsIndex; i++)
     {
     printf(" %s %d %d\n", itemList[i].name, itemList[i].weight, itemList[i].value);
     } */

 callKnapSack (itemList, itemcount, weight_limit);



  return 0;
}

                                                         
