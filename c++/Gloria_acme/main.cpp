#include <iostream>
#include <string>
using namespace std;

//DECLARACIO DE VARIABLES

//conte les posicions del arrays comarques i pobles amb els que estem treballant
int posicio_poble;
int posicio_comarca;
const int numero_incidencies_max=50;
const int numero_pobles_max=200;
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
    int n_incidencies=0;
    
};

//structura amb les dades de la comarca
struct comarca
{
    string nom_comarca;
    poble pobles[numero_pobles_max];
    
};

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
    //Pre:	0<=v.n<=MAX,	v.t[0..v.n-1]	ordenat	creixentment	
    //Post:	retorna	la	posició	on	s’ha	trobat		x	a		v.t[0..v.n-1],	o	-1	si	no	existeix.	
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
      comarques[posicio_comarca].pobles[esq-1]={};
      comarques[posicio_comarca].pobles[esq-1].nom_poble=temp_poble;      
      posicio_poble=esq-1;
      menu_afegir_dades();
      }  
      
    }
};

int guardar_comarca_ordenadament(string temp_poble,string temp_comarca){
    //Pre:	0<=v.n<=MAX,	v.t[0..v.n-1]	ordenat	creixentment	
    //Post:	retorna	la	posició	on	s’ha	trobat		x	a		v.t[0..v.n-1],	o	-1	si	no	existeix.	
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
      comarques[esq-1]={};
      comarques[esq-1].nom_comarca=temp_comarca;
      posicio_comarca=esq-1;
      guardar_poble_ordenadament(temp_poble);  
      }
      
         

    }
  };
  
  

void introduccio_poblacio(){
  string temp_poble="";
  string temp_comarca="";
  while (temp_poble!="FI")
  {
    cout << "Entra registres:" << endl;
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
            cout << comarques[i].nom_comarca << " ";
            for (int x = 0; x < numero_pobles_max; x++)
            {
              if (comarques[i].pobles[x].nom_poble!="")
              {
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
                  cout << comarques[i].pobles[x].vent << " km/h ";
                  cout << comarques[i].pobles[x].dia_vent << " - ";
                  cout << comarques[i].pobles[x].hora_vent << " ";
                }
                if (comarques[i].pobles[x].incidencies[0]!="")
                {
                  cout << "--";   
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
              }            
          }    
          cout << endl;    
          }          
        }
      }
      else
      {
        cout << "No hi ha incidents registrats" << endl;
      }      
};



int main()
{
    //variables usades dins el main
    char lletra_menu='i';
    

  cout << "REGISTRES TEMPORAL GLORIA" << endl << endl ;

  while (lletra_menu!='s'){ //lletra 's' per sortir del menu

    cout << "Opcio	[a/m/c/r/s]:" << endl;
    cin >> lletra_menu;

    switch(lletra_menu) {
      case 'a': case 'A':
        introduccio_poblacio();
        break;
      case 'm': case 'M':
        mostrar_dades();        
        break;
      //case 'c': case 'C':
    
        //break;
      //case 'r': case 'R':
    
        //break;    
  
}
}   
	
  return 0;
}

