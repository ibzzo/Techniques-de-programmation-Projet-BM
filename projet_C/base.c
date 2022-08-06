#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

/*operation de creation la base*/
 base_t *base_create()
 {
   base_t *base;
     base=malloc(sizeof(base_t));
     if (base==NULL)      
     {
       fprintf(stderr,"allocution impossible ! \n");
       return NULL;
     }
     base->country=malloc(sizeof(char*));
     base->day=0;
     base->facilities=malloc(sizeof(facility_t));
     base->month=0;
     base->name=malloc(sizeof(char*));
     base->nfacilities=0;
     base->year=0;

     return base;
 }
  void base_free(base_t *base){
    int i;
        for(i=0;i<base->nfacilities;i++)
        {
          facility_free(base->facilities[i]);
        }
        free(base->name);
        free( base->country);
       free(base);
  }
 /*operation permettant d'ajouter une facilities */
  int base_add_facility(base_t *base, facility_t *facility)
  {
    base->facilities=realloc(base->facilities,2*sizeof(facility_t));
    if(base->facilities==NULL)
    {
      fprintf(stderr,"reallocution echouee \n");
      return -1;
    }
    base->facilities[base->nfacilities]=facility;
    return 0;
  }
  /*affichage de la base*/
   void base_handle_b(base_t base){
     printf("%s  (",base.name);
     printf("%d-0%d-0%d",base.year,base.month,base.day);
    printf(", %s)\n",base.country);
   }
/*Fonction qui affiche le pays de la base constituée d’installations*/
void base_handle_c(base_t base){
  printf("%s\n", base.country);
}                                       

/*Fonction qui affiche la date de la base*/
void base_handle_d(base_t base){
  printf("%d-0%d-0%d \n",base.year,base.month,base.day);
}

/*Fonction qui affiche le nom de la base*/
void base_handle_n(base_t base){
  printf("%s\n", base.name);
}


/*Fonction qui affiche une installation de la base*/
void base_handle_f(base_t base){
  int i;
  for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_f(*base.facilities[i]);
  }
}

/*Fonction qui affiche une installation avec le prix correspondant*/
void base_handle_fc(base_t base, double cost){
   int i;
  for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_fc(*base.facilities[i],cost);
  }
}

/*Fonction qui affiche une installation avec le prix supérieur ou égal correspondant*/
void base_handle_fcge(base_t base, double cost){
   int i;
 for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_fcge(*base.facilities[i], cost);
  }
}

/*Fonction qui affiche une installation avec le prix supérieur correspondant*/
void base_handle_fcgt(base_t base, double cost){
   int i;
  for (i = 0 ; i <= base.nfacilities; i++){
    facility_handle_fcgt(*base.facilities[i], cost);
  }
}

/*Fonction qui affiche une installation avec le prix inférieur ou égal correspondant*/
void base_handle_fcle(base_t base, double cost){
   int i;
  for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_fcle(*base.facilities[i], cost);
  }
}

/*Fonction qui affiche une installation avec le prix supérieur correspondant*/
void base_handle_fclt(base_t base, double cost){
   int i;
  for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_fclt(*base.facilities[i], cost);
  }
}

/*Fonction qui affiche une installation(base) ayant NAME dans leur nom de famille*/
void base_handle_fn(base_t base, const char *last_name){
 
   int i;
  for (i = 0 ; i < base.nfacilities; i++){
    facility_handle_fn(*base.facilities[i], last_name);
  }
}

/*Fonction qui affiche le cout total de la base*/
void base_handle_t(base_t base){
   int i;
  double cost=0;
  for (i = 0 ; i < base.nfacilities; i++){
    cost += base.facilities[i]->cost;
  }
  printf("%.2f USD \n", cost);
}
