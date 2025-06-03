#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadratic_solver.h"

int quadratic_solver(double a, double b, double c, double eps, double **roots){

   if(fabs(a)<eps) {
      if(roots) *roots = NULL;
	  return NOT_QUADRATIC_EQUATION; //Íå ÿâëÿåòñÿ êâàäðàòè÷íûì óðàâíåíèåì
   }

   //Êàæäûé êîýôôèöèåíò äåëèì äëÿ ëåãêîñòè âû÷èñëåíèÿ
   b = b / a;
   c = c / a;

   double disc = b * b - 4 * c; //Äèñêðèìèíàíò
   if(disc < -eps) {
	  *roots = NULL;
	  return NO_ROOTS; //Íåò êîðíåé
   } else if(fabs(disc) <= eps) { //Äèñêðèìèíàíò ðàâåí(ïî÷òè) íóëþ
	  *roots = (double *)malloc(1  *sizeof(double)); //Êîðåíü 1, âûäåëÿåì ïàìÿòü íà 1
	  (*roots)[0] = -b / 2; //Îäèí êîðåíü
	  return ONE_ROOT;
   } else {
	  *roots = (double *)malloc(2 * sizeof(double)); //Êîðíÿ 2, âûäåëÿåì ïàìÿòü íà 2

	  (*roots)[0] = (-b - sqrt(disc)) / 2; //Ïåðâûé êîðåíü
	  (*roots)[1] = (-b + sqrt(disc)) / 2; //Âòîðîé êîðåíü
	  //Êîðíè ïî âîçðàñòàíèþ
	  return TWO_ROOTS;
   }
}
