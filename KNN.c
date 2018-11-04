#include <stdio.h>
#include <stdlib.h>

#define ROWS 74
#define TESTROWS 26
#define COLS 4
#define K 5

typedef struct _tab {
   double *x;   //Stores Xi
   int y;    //Stores y
} tab;

typedef struct _dist {
   double e;    //Stores distance
   int index;   //Stores original index
} dist;

void bubbleSort(dist *d)  //Function to implement stable sort

{

   dist temp;

   for (int i=1; i<ROWS; i++) {

      for (int j=0; j<ROWS-i; j++) {

         if(d[j].e > d[j+1].e) {
            temp = d[j];
            d[j] = d[j+1];
            d[j+1] = temp;
         }

      }

   }

}

int KNN(tab *table, double *instance)

{

   int count=0;
   dist *d = (dist *) malloc(ROWS*sizeof(dist));

   for (int i=0; i<ROWS; i++) {

      d[i].index = i;  //Initializes original index of every distance structure
      d[i].e = 0;   //Initializes distance to 0
      
      for(int j=0; j<COLS; j++) {

         d[i].e += (instance[j]-table[i].x[j])*(instance[j]-table[i].x[j]);

         //Calculates square of Euclidean distance between instance point and every set Xi, and stores it in corresponding d[i]

      }

   }

   bubbleSort(d);  //Sorted in ascending order

   for(int i=0; i<K; i++)
      if(table[d[i].index].y == 1) count++;
      //Counts number of cases with y=1 among nearest K neighbours
   
   return (count > (K/2));  //If count>K/2 returns 1, else 0

}

int main()

{

   FILE *fp, *fp2, *fpw;
   tab *table = (tab *) malloc(ROWS*sizeof(tab));
   double **instance = (double **) malloc(TESTROWS*sizeof(double *));

   fp = fopen("data4.csv", "r");

   if(fp==NULL) {
      printf("data4.csv not found\n");
      return 1;
   }

   for(int i=0; i<ROWS; i++) {
 
      table[i].x = (double *) malloc(COLS*sizeof(double));

      for (int j=0; j<COLS; j++) {

         fscanf(fp, " %lf,", &table[i].x[j]);

      }

      fscanf(fp, " %d,", &table[i].y);

   }

   fclose(fp);

   fp2 = fopen("test4.csv", "r");

   if(fp2 == NULL) {
      printf("test4.csv not found\n");
      return 1;
   }

   for (int i=0; i<TESTROWS; i++) {

      instance[i] = (double *) malloc(COLS*sizeof(double));

      for (int j=0; j<COLS; j++) {

         fscanf(fp2, " %lf,", &instance[i][j]);

      }

   }

   fclose(fp2);

   fpw = fopen("KNN.out", "w");

   if(fp2 == NULL) {
      printf("Failed to create output file\n");

      for (int i=0; i<TESTROWS; i++) 
         printf("%d ", KNN(table, instance[i]));

      printf("\n");
      
      return 1;

   } 

   for (int i=0; i<TESTROWS; i++) {
      fprintf(fpw, "%d ", KNN(table, instance[i]));
      printf("%d ", KNN(table, instance[i]));
   }

   printf("\n");

   return 0;

} 
