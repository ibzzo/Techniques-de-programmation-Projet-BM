#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "base.h"
#include <libxml/parser.h>

void bm_handle_v(){
  printf("BM (Base Manager) 20211129 \n");
  printf("\nCopyright (C) 2021 Ibrahima Diao and Younes Addi.\n");
  printf("\nWritten by Ibrahima Diao <ibrahima.diao@univ-pau.fr> and Younes Addi <younes.addi@univ-pau.fr>\n");

}

void bm_handle_h(){
    printf("b: Prints the base\n");
    printf("c: Prints the base country\n");
    printf("d: Prints the base date\n");
    printf("f: Prints the base facilities\n");
    printf("fc COST: Prints the base facilities with the cost equal to COST\n");
    printf("fcge COST: Prints the base facilities with the cost greater than or equal to COST\n");
    printf("fcgt COST: Prints the base facilities with the cost greater than COST\n");
    printf("fcle COST: Prints the base facilities with the cost less than or equal to COST\n");
    printf("fclt COST: Prints the base facilities with the cost less than COST\n");
    printf("fn NAME: Prints the base facilities with the name containing NAME\n");
    printf("h: Prints this help\n");
    printf("n: Prints the base name\n");
    printf("t: Prints the base total cost\n");
    printf("v: Prints the BM version\n");
    printf("q: Quits BM\n"); 
}

void getDateToBase(xmlDocPtr doc,base_t * base,xmlNodePtr n)
{
    n=n->children;
   while (n!=NULL)
   {
        n=n->next;
        if (n!=NULL)
        { 
           if(!xmlStrcmp(n->name, (const xmlChar*) "day"))
           {
              base->day=strtod((char*)xmlNodeListGetString(doc, n->xmlChildrenNode, 1),NULL);
           }
           if(!xmlStrcmp(n->name, (const xmlChar*) "month"))
           {
               base->month=strtod((char*)xmlNodeListGetString(doc, n->xmlChildrenNode, 1),NULL);
           }
           if(!xmlStrcmp(n->name, (const xmlChar*) "year"))
           {
        
               base->year=strtod((char*)xmlNodeListGetString(doc, n->xmlChildrenNode, 1),NULL);
           }
           
            n=n->next;  
        }
   }
   
}

void getCountryToBase(xmlDocPtr doc,base_t * base,xmlNodePtr n)
{
    base->country=(char*)xmlNodeListGetString(doc, n->xmlChildrenNode, 1);
}

int getNumberFacilities(xmlNodePtr n)
{
    int i=0;
    n=n->children;
     n=n->next;
     while (n!=NULL)
     {
         n=n->next;
         if(!xmlStrcmp(n->name, (const xmlChar*) "facilities"))
         {
             n=n->children;
             n=n->next;
             while (n!=NULL)
             {
                 n=n->next;
                 i++;
                 if (n!=NULL)
                 {
                     n=n->next;
                 }
                 
             }
             
         }

     }
     return i;
     
}

void getFacilitiesToBase(xmlDocPtr doc,base_t * base,xmlNodePtr n)
{
    int i=0;
     xmlNodePtr n1; 
    n=n->children;
   while (n!=NULL)
   {
        n=n->next;
        if (n!=NULL)
        {
            n1=n->children;
            while (n1!=NULL)
            {
                n1=n1->next;
                if (n1!=NULL)
              {
                if(!xmlStrcmp(n1->name, (const xmlChar*) "area"))
                {
                  base->facilities[i]->name=(char*)xmlGetProp(n,(xmlChar*)"name");
                  base->facilities[i]->area=strtod((char*)xmlNodeListGetString(doc, n1->xmlChildrenNode, 1),NULL);
                
                }
                if(!xmlStrcmp(n1->name, (const xmlChar*) "cost"))
                {
                  base->facilities[i]->cost=strtod((char*)xmlNodeListGetString(doc, n1->xmlChildrenNode, 1),NULL);
                }
                n1=n1->next;  
            } 
            }
            n=n->next;
            i++;
        }
   }
   
}


void setBase(base_t * base,xmlDocPtr doc,xmlNodePtr racine)
{
    xmlChar* name;
   xmlNodePtr n;   
      name=xmlGetProp(racine,(xmlChar*)"name");
      base->name=(char*)name;
      racine=racine->children;
      n=racine;
  while(n!=NULL)
  {
      if(!xmlStrcmp(n->name, (const xmlChar*) "date"))
      {
         getDateToBase(doc,base,n);
      }
     if(!xmlStrcmp(n->name, (const xmlChar*) "country"))
      {
         getCountryToBase(doc,base,n);
      }
     if(!xmlStrcmp(n->name, (const xmlChar*) "facilities"))
      {
          getFacilitiesToBase(doc,base,n);
      }
      n=n->next;
  }
}

double convert(char *s)
{
    char *endp;
    double d;
    double l;


    d = strtod(s, &endp);
    if (s != endp && *endp == '\n')
        return d;
    else
    {
        l = strtol(s, &endp, 0);
        if (s != endp && *endp == '\n')
           return l;
        else
        {
          return 1;
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    char action[20]="";
    char name[20]="";
    char* ptr;
    double cost;
    int i,j;
    xmlDocPtr doc;
    xmlNodePtr racine;
    base_t * base;
       if (argc!=2)
       {
           fprintf(stderr,"./bm.out: Invalid number of arguments \n");
           exit(EXIT_FAILURE);
       }
      doc=xmlParseFile(argv[1]);
       if (doc==NULL)
       {
           fprintf(stderr,"./bm.out: Unable to parse the document \n");
           exit(EXIT_FAILURE);
       }
       racine = xmlDocGetRootElement(doc);
       base=malloc(sizeof(base_t));
       if (base==NULL)      
       {
           fprintf(stderr,"allocution impossible \n");
           exit(EXIT_FAILURE);
       }
        base=base_create();
        base->nfacilities=getNumberFacilities(racine);
        for(i=0;i< base->nfacilities;i++)
        {
            base->facilities[i]=facility_create();
        }
        setBase(base,doc,racine);
          printf("BM> ");
        fgets(action,20,stdin);
        while (action[0]!='q' || action[1]!='\n')
        {
         i=0;
          i=strlen(action); 
         if (i>18)
         {
             fprintf(stderr,"./bm.out: Too many characters for the command\n");
         }
         
         else if (strcmp(action,"h\n")==0)
         {
             bm_handle_h();
         }
        else if (strcmp(action,"b\n")==0)
        {
            base_handle_b(*base);
        }
        else if (strcmp(action,"c\n")==0)
        {
            base_handle_c(*base);
        }
        else if (strcmp(action,"d\n")==0)
        {
               base_handle_d(*base);
        }   
        else if (strcmp(action,"f\n")==0)
        {
           base_handle_f(*base);
        }
        else if (strcmp(action,"n\n")==0)
        {
            base_handle_n(*base);
        }
        else if (strcmp(action,"t\n")==0)
        {
            base_handle_t(*base);
        }
        else if (strcmp(action,"v\n")==0)
        {
           bm_handle_v();
        }
         else if (strstr(action,"fcge")!=NULL)
         {
             if (action[4]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fcge command\n");
             }
             else
             {
             ptr=&action[5];
            if (convert(ptr)==-1)
            {
                printf("Invalid parameter for the fcge command\n");
            }
            else
            {
            cost=convert(ptr);
             base_handle_fcge(*base,cost);
            }
             }
         }
         else if (strstr(action,"fcgt")!=NULL)
         {
             if (action[4]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fcgt command\n");
             }
             else
             {
             ptr=&action[5];
            if (convert(ptr)==1)
            {
                printf("./bm.out: Invalid parameter for the fcgt command\n");
            }
            else
            {
            cost=convert(ptr);
             base_handle_fcgt(*base,cost);
            }
             }             

            
         }
        else if (strstr(action,"fcle")!=NULL)
         {
             if (action[4]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fcle command\n");
             }
             else
             {
             ptr=&action[5];
            if (convert(ptr)==1)
            {
                printf("./bm.out: Invalid parameter for the fcle command\n");
            }
            else
            {
            cost=convert(ptr);
             base_handle_fcle(*base,cost);
            }
             }             
         }
        else if (strstr(action,"fclt")!=NULL)
         {
             if (action[4]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fclt command\n");
             }
             else
             {
             ptr=&action[5];
            if (convert(ptr)==1)
            {
                printf("./bm.out: Invalid parameter for the fclt command\n");
            }
            else
            {
            cost=convert(ptr);
             base_handle_fclt(*base,cost);
            }
             }             

         }
        else if (strstr(action,"fn")!=NULL)
         {
             if (action[2]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fn command\n");
             }
             else
             {
             i=3;
             j=0;
             while (action[i]!='\n')
             {
                 name[j]=action[i];
                 i++;
                 j++;//Ne pas oublier d'ajouter le caractere de fin de la chaine:'\0'
             }
             base_handle_fn(*base,name);
             }             

         }
         else if (strstr(action,"fc")!=NULL)
         {
             if (action[2]!=' ')
             {
                 fprintf(stderr,"./bm.out: Missing parameter for the fc command\n");
             }
             else
             {
            ptr=&action[3];
            if (convert(ptr)==1)
            {
                printf("./bm.out: Invalid parameter for the fc command\n");
            }
            else
            {
            cost=convert(ptr);
             base_handle_fc(*base,cost);
            }  

             }           
         }
         else 
         {
             fprintf(stderr,"./bm.out: Invalid command\n");
         }
         if (i>=19)/*le vidage du flux d'entrer standart est declencher si la taille  d'entree de l'utilisateur depasse 18 caractere*/
         {
                      while (getchar()!='\n')
         {
             /* code */
         }
         }
         
         printf("BM> ");
          fgets(action,20,stdin);   
        }
        printf("Goodbye!\n");
        base_free(base);
        xmlCleanupParser();
        xmlFreeDoc(doc);
    return 0;
}
