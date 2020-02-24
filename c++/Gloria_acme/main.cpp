#include <iostream>
#include <string>
using namespace std;

//DECLARACIO DE VARIABLES

//conte les posicions del arrays comarques i pobles amb els que estem treballant
int posicio_poble;
int posicio_comarca;
const int numero_incidencies_max=50;
const int numero_pobles_maxim=200;
const int numero_comarques_maxim=50;

//structura que conte les dades d'una poblacio
struct poble 
{
    string nom_poble; 
    int pluja;
    int neu;
    int vent;
    string dia_vent;
    string hora_vent;
    string incidencies[numero_incidencies_max];
    int n_incidencies;
    
};

//structura amb les dades de la comarca
struct comarca
{
    string nom_comarca;
    poble pobles[numero_pobles_maxim];
    
};

poble netejar_posicions_poble;
comarca netejar_posicions_comarca;
comarca comarques[numero_comarques_maxim];


//FUNCIONS
void guardar_pluja_neu(char lletra,int dada){
  //Pre: lletra introduida i dada
  //Pos: suma el valor de neu o pluja al poble corresponent
  if (lletra=='p' || lletra=='P')
  {
      comarques[posicio_comarca].pobles[posicio_poble].pluja+=dada;
  }
  else if (lletra=='n' || lletra=='N')
  {
      comarques[posicio_comarca].pobles[posicio_poble].neu+=dada;
  }
};

void guardar_vent(int dada,string dia,string hora){
  //Pre: cantitat de vent,dia i hora del vent
  //Pos: si la dada es superior es guardar si no s'ignora
    if (comarques[posicio_comarca].pobles[posicio_poble].vent<dada)
  {
    comarques[posicio_comarca].pobles[posicio_poble].vent=dada;
    comarques[posicio_comarca].pobles[posicio_poble].dia_vent=dia;
    comarques[posicio_comarca].pobles[posicio_poble].hora_vent=hora;
  }   
  
};

void guardar_incidencia(string dada){
  //Pre:incidencia
  //Pos: gurada la incidencia en el primer lloc buit de l'array incidencies
  if (comarques[posicio_comarca].pobles[posicio_poble].n_incidencies<numero_incidencies_max)
  {
    comarques[posicio_comarca].pobles[posicio_poble].incidencies[comarques[posicio_comarca].pobles[posicio_poble].n_incidencies]=dada;
    comarques[posicio_comarca].pobles[posicio_poble].n_incidencies++;
  }
  else
  {
    cout << "la taula incidencies esta plena, no es poden afegir mes registres" << endl;
  }  
  
};

void menu_afegir_dades(){
  //Pre: posicions de pobla i comarca actualitzades
  //Pos: dades guardades al poble corresponent
  char lletra_menu;
  int dada;
  string dia;
  string hora;
  string incidencia;

  cout << "[p/n/v/i]:" << endl;
  cin >> lletra_menu;
  

    if (lletra_menu=='p' || lletra_menu=='P' || lletra_menu=='n' || lletra_menu=='N')
    {
      cout << "Dada:" << endl;
      cin >> dada;
      guardar_pluja_neu(lletra_menu,dada);
    }
    else if (lletra_menu=='v' || lletra_menu=='V')
    {
      cout << "Dada:" << endl;
      cin >> dada;
      cout << "Dia i hora:" << endl;
      cin >> dia;
      cin >> hora;
      guardar_vent(dada,dia,hora);
    }
    else if (lletra_menu=='i' || lletra_menu=='I')
    {
      cout << "Dada:" << endl;
      cin >> incidencia;
      guardar_incidencia(incidencia);
    }
    
    
    
}

void guardar_poble_ordenadament(string temp_poble){
    //Pre:nom del poble a guradar/actualiitzar	
    //Post:	guarda el poble de forma ordenada i actualitza el valor de posicio del poble	
    int mig, esq=0, dreta=(sizeof(comarques[posicio_comarca].pobles)/sizeof(comarques[posicio_comarca].pobles[0]))-1;
    bool trobat=false;
    while(not trobat and esq<=dreta){
      mig = (esq+dreta)/2;
      if(temp_poble<comarques[posicio_comarca].pobles[mig].nom_poble) dreta=mig-1;
      else if(temp_poble>comarques[posicio_comarca].pobles[mig].nom_poble) esq=mig+1;
      else trobat=true;
    }
    if (trobat) {
      //retornem la posicio on l'hem trobat
      posicio_poble=mig;
      menu_afegir_dades();      
    }
    else {
      int i = 0;
      if (comarques[posicio_comarca].pobles[0].nom_poble!="")
      {
        cout << "El Registre de pobles esta ple, no es poden afegir nous pobles en aquesta comarca" << endl;
      }
      else
      {
        while (i<esq-1)
      {
        comarques[posicio_comarca].pobles[i]=comarques[posicio_comarca].pobles[i+1];
        i++;
      }
      comarques[posicio_comarca].pobles[esq-1]=netejar_posicions_poble;
      comarques[posicio_comarca].pobles[esq-1].nom_poble=temp_poble;      
      posicio_poble=esq-1;
      menu_afegir_dades();
      }  
      
    }
};

int guardar_comarca_ordenadament(string temp_poble,string temp_comarca){
    //Pre:	nom del poble i la comarca a introduir o actualitzar	
    //Post:	guarde el poble/comarca de forma ordenada si ja esta creat no actualitza les variables de posicio
    int mig, esq=0, dreta=(sizeof(comarques)/sizeof(comarques[0]))-1;
    bool trobat=false;
    while(not trobat and esq<=dreta){
      mig = (esq+dreta)/2; 
      if(temp_comarca<comarques[mig].nom_comarca) dreta=mig-1;
      else if(temp_comarca>comarques[mig].nom_comarca) esq=mig+1;
      else trobat=true;
    }
    if (trobat) {
      //la comarca ja esta creada, guardem el poble dins seu
      posicio_comarca=mig;
      guardar_poble_ordenadament(temp_poble);      
    }
    else {
      int i = 0;
      if (comarques[0].nom_comarca!="")
        {
          cout << "El Registre de Comarques esta ple, no es poden afegir noves comarques" << endl;
        }
      else
      {
        while (i<esq-1)
      {
          comarques[i]=comarques[i+1];
          i++;
      }
      comarques[esq-1]=netejar_posicions_comarca;
      comarques[esq-1].nom_comarca=temp_comarca;
      posicio_comarca=esq-1;
      guardar_poble_ordenadament(temp_poble);  
      }
      
         

    }
  };
  
  

void introduccio_poblacio(){
  //demana les dades per introduir un nou poble/comarca al sistema
  //variables usades dins la funcio
  string temp_poble="";
  string temp_comarca="";


  cout << "Entra registres:" << endl;
  while (temp_poble!="FI")
  {
    cout << "Poblacio:" << endl;
    cin >> temp_poble;
    if (temp_poble=="FI")
    {
      break;
    }  
    cout << "Comarca:" << endl;
    cin >> temp_comarca;
    guardar_comarca_ordenadament(temp_poble,temp_comarca);
  } 
  
};

void mostrar_dades(){
      if (comarques[numero_comarques_maxim-1].nom_comarca!="")
      {
        for (int i = 0; i < numero_comarques_maxim; i++)
        {
          if (comarques[i].nom_comarca!="")
          {            
            for (int x = 0; x < numero_pobles_maxim; x++)
            {
              if (comarques[i].pobles[x].nom_poble!="")
              {
                cout << comarques[i].nom_comarca << " ";
                cout << comarques[i].pobles[x].nom_poble << ": ";
                if (comarques[i].pobles[x].pluja!=0)
                {
                  cout << comarques[i].pobles[x].pluja << " l/m2 ";
                }
                if (comarques[i].pobles[x].neu!=0)
                {
                  cout << comarques[i].pobles[x].neu << " cm ";
                }
                if (comarques[i].pobles[x].vent!=0)
                {
                  cout << comarques[i].pobles[x].vent << "km/h ";
                  cout << comarques[i].pobles[x].dia_vent << " - ";
                  cout << comarques[i].pobles[x].hora_vent << " ";
                }
                if (comarques[i].pobles[x].incidencies[0]!="")
                {
                  cout << "-- ";   
                  for (int z =0; z < numero_incidencies_max; z++)
                  {
                    if (comarques[i].pobles[x].incidencies[z]!="")
                    {
                      cout << comarques[i].pobles[x].incidencies[z];
                    }
                    else
                    {
                      break;
                    }                 
                  }
                }
                cout << endl;               
              }            
            }    
              
          }          
        }
      }
      else
      {
        cout << "No tenim dades" << endl;
      }      
};

void poblacio_mes_incidents(){
  //Pre:
  //Pos: mostre el poble amb mes incidents
  int posicio_comarca_max=0;
  int posicio_poble_max=0;
  int maxim_incidencies=0;
  for (int i = 0; i < numero_comarques_maxim; i++)
  {
    for (int x = 0; x < numero_pobles_maxim; x++)
    {
      if (comarques[i].pobles[x].n_incidencies>maxim_incidencies)
      {
        maxim_incidencies=comarques[i].pobles[x].n_incidencies;
        posicio_comarca_max=i;
        posicio_poble_max=x;
      }      
    }    
  }
  if (posicio_comarca_max==0)
  {
    cout << "No hi ha incidents registrats" << endl;
  }
  else
  {
    cout << comarques[posicio_comarca_max].nom_comarca << " " ;
    cout << comarques[posicio_comarca_max].pobles[posicio_poble_max].nom_poble << ": -- ";
    for (int z = 0; z < comarques[posicio_comarca_max].pobles[posicio_poble_max].n_incidencies; z++)
    {
     cout << comarques[posicio_comarca_max].pobles[posicio_poble_max].incidencies[z] << " ";
    } 
    cout << endl;
  }
  
  
  
};

void registres_superiors(){
  //Pre: 
  //Pos: mostra els pobles amb valors superiors a "valor_llindar" en pluja neu o vent

  //variables
  char lectura_teclat;
  int valor_llindar;
  int numero_superiors=0;
  struct adresa_pobles
  {
    int comarca,poble;
  };  
  adresa_pobles llista_pobles[numero_comarques_maxim*numero_pobles_maxim];


  cout << "[p/v/n]:" << endl;
  cin >> lectura_teclat;
  cout << "Llindar:" << endl;
  cin >> valor_llindar;

  //recorre les posicions del pobles comparant els valor amb el "valor_llindar", si es superior es guardn les posicions del poble dins "llista_pobles" de forma ordenada
  for (int y = 0; y < numero_comarques_maxim; y++)
  {
    for (int x = 0; x < numero_pobles_maxim; x++)
    {
      if (lectura_teclat=='p')
      {
        if (valor_llindar<comarques[y].pobles[x].pluja)
        { 
          if (numero_superiors==0)
          {
            llista_pobles[0].comarca=y;
            llista_pobles[0].poble=x;
          }
          else
          {
            int i;
            for ( i = numero_superiors - 1; (i >= 0 &&comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].pluja > valor_llindar); i--){
              llista_pobles[i + 1] =llista_pobles[i];
            }
            llista_pobles[i + 1].comarca =y;
            llista_pobles[i + 1].poble=x;
          }
          numero_superiors+=1;
        } 
      }
      if (lectura_teclat=='v')
      {
        if (valor_llindar<comarques[y].pobles[x].vent)
        { 
          if (numero_superiors==0)
          {
            llista_pobles[0].comarca =y;
            llista_pobles[0].poble =x;
          }          
          else
          {
            int i;
            for (i =numero_superiors-1; (i >= 0 &&comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].vent > valor_llindar); i--){
              llista_pobles[i + 1] =llista_pobles[i];
            }
            llista_pobles[i + 1].comarca=y;
            llista_pobles[i + 1].poble=x;
          };
          numero_superiors+=1;
        };
      if (lectura_teclat=='n')
      {
        if (valor_llindar<comarques[y].pobles[x].neu)
        { 
          if (numero_superiors==0)
          {
            llista_pobles[0].comarca=y;
            llista_pobles[0].poble=x;
          }
          else
          {
            int i;
            for (i = numero_superiors - 1; (i >= 0 &&comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].neu > valor_llindar); i--){
              llista_pobles[i + 1] =llista_pobles[i];
            }
            llista_pobles[i+1].comarca=y;
            llista_pobles[i+1].poble=x;
          }
          numero_superiors+=1;
      }      
      }      
      }
    
    }
  }
  //mostre els pobles que superen el llindar
  if (numero_superiors==0)
  {
    cout << "Llindar no superat" << endl;
  }
  else
  {
    for (int i = 0; i < (numero_superiors); i++)
    {
      cout << comarques[llista_pobles[i].comarca].nom_comarca << " ";
      cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].nom_poble << ": ";
      if (comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].pluja!=0)
      {
        cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].pluja << " l/m2 ";
      }
      if (comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].neu!=0)
      {
        cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].neu << " cm ";
      }
      if (comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].vent!=0)
      {
        cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].vent << " km/h ";
        cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].dia_vent << " - ";
        cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].hora_vent << " ";
      }
      if (comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].incidencies[0]!="")
      {
        cout << "--";   
        for (int z =0; z < numero_incidencies_max; z++)
        {
          if (comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].incidencies[z]!="")
          {
            cout << comarques[llista_pobles[i].comarca].pobles[llista_pobles[i].poble].incidencies[z];
          }
          else
          {
            break;
          }                 
        }
      }
      cout << endl;        
    }
  }
  
};


int main()
{
    //variables usades dins el main
    char lletra_menu='i';
    

  cout << "REGISTRES TEMPORAL GLORIA" << endl ;

  while (lletra_menu!='s'){ //lletra 's' per sortir del menu
    cout << endl;
    cout << "Opcio	[a/m/c/r/s]:" << endl;
    cin >> lletra_menu;

    switch(lletra_menu) {
      case 'a': case 'A':
        introduccio_poblacio();
        break;
      case 'm': case 'M':
        mostrar_dades();        
        break;
      case 'c': case 'C':
        poblacio_mes_incidents();
        break;
      case 'r': case 'R':
        registres_superiors();
        break;    
  
}
}   
	
  return 0;
}

