#include <iostream>
#include <string>
using namespace std;

//DECLARACIO DE VARIABLES

//conte les posicions del arrays comarques i pobles amb els que estem treballant
int posicio_poble;
int posicio_comarca;
const int numero_incidencies_max=50;

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
    poble pobles[200];
    
};

comarca comarques[50];


//FUNCIONS
void guardar_pluja_neu(bool poble_nou,char lletra,int dada){
  if (lletra=='p' || lletra=='P')
  {
    if (poble_nou)
    {
      comarques[posicio_comarca].pobles[posicio_poble].pluja=dada;
    }
    else
    {
      comarques[posicio_comarca].pobles[posicio_poble].pluja+=dada;
    }    
  }
  if (lletra=='n' || lletra=='N')
  {
    if (poble_nou)
    {
      comarques[posicio_comarca].pobles[posicio_poble].neu=dada;
    }
    else
    {
      comarques[posicio_comarca].pobles[posicio_poble].neu+=dada;
    }   
  }
};

void guardar_vent(int dada,string dia,string hora){
  if (comarques[posicio_comarca].pobles[posicio_poble].vent<dada)
  {
    comarques[posicio_comarca].pobles[posicio_poble].vent=dada;
    comarques[posicio_comarca].pobles[posicio_poble].dia_vent=dia;
    comarques[posicio_comarca].pobles[posicio_poble].hora_vent=hora;
  }
  
};

void guardar_incidencia(string dada){
    comarques[posicio_comarca].pobles[posicio_poble].incidencies[comarques[posicio_comarca].pobles[posicio_poble].n_incidencies]=dada;
    comarques[posicio_comarca].pobles[posicio_poble].n_incidencies++;
};

void menu_afegir_dades(bool poble_nou){
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
      guardar_pluja_neu(poble_nou,lletra_menu,dada);
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
    bool poble_nou;
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
      posicio_poble=mig-1;
      menu_afegir_dades(false);      
    }
    else {
      int i = (sizeof(comarques[posicio_comarca].pobles)/sizeof(comarques[posicio_comarca].pobles[0]))-1;
      while (i>esq-1)
      {
        comarques[posicio_comarca].pobles[i]=comarques[posicio_comarca].pobles[i-1];
        i--;
      }
      comarques[posicio_comarca].pobles[esq-1].nom_poble=temp_poble;
      
      posicio_poble=esq-1;
      menu_afegir_dades(true);
    }
};

int guardar_comarca_ordenadament(string temp_poble,string temp_comarca){
    //Pre:	0<=v.n<=MAX,	v.t[0..v.n-1]	ordenat	creixentment	
    //Post:	retorna	la	posició	on	s’ha	trobat		x	a		v.t[0..v.n-1],	o	-1	si	no	existeix.	

    int posicio_poble;
    int posicio_comarca;
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
      int i = (sizeof(comarques)/sizeof(comarques[0]))-1;
      while (i>esq-1)
      {
        comarques[i]=comarques[i-1];
        i--;
      }
      comarques[esq-1].nom_comarca=temp_comarca;
      posicio_comarca=esq-1;
      guardar_poble_ordenadament(temp_poble);

      

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
        int count=50;
        int count2=200;
        int count3=50;
        for (int i = 0; i < count; i++)
        {
          cout << "comarca:" << comarques[i].nom_comarca << endl;
          for (int x = 0; x < count2; x++)
          {
            
            cout << "   pobles:" << comarques[i].pobles[x].nom_poble << endl;
            cout << "       pluja:" << comarques[i].pobles[x].pluja << endl;
            cout << "       neu:" << comarques[i].pobles[x].neu << endl;
            cout << "       vent:" << comarques[i].pobles[x].vent << endl;
            cout << "          dia:" << comarques[i].pobles[x].dia_vent << endl;
            cout << "          hora:" << comarques[i].pobles[x].hora_vent << endl;
            for (int z = 0; z < count3; z++)
            {
              cout << "     incidencia:" << comarques[i].pobles[x].incidencies[z] << endl;
            }
            
          }
          
        }
        
        break;
      case 'c': case 'C':
    
        break;
      case 'r': case 'R':
    
        break;    
  
}
}   
	
  return 0;
}

