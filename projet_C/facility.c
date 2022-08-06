#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "facility.h"

/*creation d'un facilitie*/
 facility_t *facility_create() 
 {
   facility_t * facility;
   facility=malloc(sizeof(facility_t));
   if (facility==NULL)      
   {
     fprintf(stderr,"allocution echouee \n");
     return NULL;
   }
   facility->area=0;
   facility->cost=0;
   facility->name=malloc(2*sizeof(char*));
   return facility;
 }

 void facility_free(facility_t *facility){
   free(facility->name);
   free(facility);
 }
  /*affichage des facilities*/
   void facility_handle_f(facility_t facility)
   {
     printf("%s, %d m2, %.2f USD\n",facility.name,facility.area,facility.cost);
   }

/*Fonction qui affiche une installation avec le prix correspondant*/
void facility_handle_fc(facility_t facility, double cost){
  if(facility.cost == cost)
  {
    facility_handle_f(facility);
  }
}

/*Fonction qui affiche une installation avec le prix supérieur ou égal correspondant*/
void facility_handle_fcge(facility_t facility, double cost){
  if(facility.cost >= cost)
  {
    facility_handle_f(facility);
  }
}
/*Fonction qui affiche une installation avec le prix supérieur correspondant*/
void facility_handle_fcgt(facility_t facility, double cost){
  if(facility.cost > cost)
  {
    facility_handle_f(facility);
  }
}

/*Fonction qui affiche une installation avec le prix inférieur ou égal correspondant*/
void facility_handle_fcle(facility_t facility, double cost){
  if(facility.cost <= cost)
  {
    facility_handle_f(facility);
  }
}

/*Fonction qui affiche une installation avec le prix inférieur correspondant*/
void facility_handle_fclt(facility_t facility, double cost){
  if(facility.cost < cost)
  {
    facility_handle_f(facility);
  }
}

/*Fonction qui affiche une base ayant NAME dans son nom de famille*/
void facility_handle_fn(facility_t facility, const char *last_name){
  if(strstr(facility.name,(char *)last_name)!=NULL)
  {
    facility_handle_f(facility);
  }
}
