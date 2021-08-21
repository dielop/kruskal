#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,pair<int,int>> arista;

class grafo{

        int V,E;
        vector<arista> aristas;
        vector<arista> arbol_minimo;
public:
        grafo(){};
        ~grafo(){};
        void insertar_arista(int ,int ,int); //prototipo de la funcion de insertar las aristas
        int kruskal(); //prototipo funcion kruskal
        void mostrar();  //prototipo funcion que muestra el arbol_minimo     
};

void grafo::insertar_arista(int u,int v,int costo){
    aristas.push_back({costo,{u,v}});
}

void grafo::mostrar(){
    vector<arista>::iterator it;

    for(it = arbol_minimo.begin();it!=arbol_minimo.end();it++){
        char v1 = '@' + it->second.first;
        char v2 = '@' + it->second.second;

        cout << v1 << " - " << v2 << " = " << it->first << endl;
    }
}

//variables globales
int *nombre_conjunto,*conjunto_encabezado, *primer_elem, *siguiente_elem;
int n=6;


typedef struct combina_encuentra{ //asigno espacio e inicializo cuenta, nombre, primer elemento y siguiente.       
    combina_encuentra(int n){ 
        conjunto_encabezado = new int[n+1];       
        nombre_conjunto = new int[n+1];
        primer_elem = new int[n+1];
        siguiente_elem = new int[n+1];        
        

        for(int i=1;i<=n;i++){
            conjunto_encabezado[i] = 1; //cuenta
            nombre_conjunto[i] = i; //nombre
            primer_elem[i] = i;    //primer elemento
            siguiente_elem[i] = 0;//siguiente elemento 
        }        
    }
       
    int encuentra(int); //prototipo funcion encuentra
    void combina(int, int);  //prototipo funcion combina
    
}CE;

//funcion encuentra
int CE::encuentra(int u){
        if(u == nombre_conjunto[u]) return nombre_conjunto[u]; //Si u es miembro de el nombre_conjunto, devuelve el nombre_conjunto
        else return encuentra(nombre_conjunto[u]); //Vuelvo a buscar
}

//funcion combina
void CE::combina(int x,int y){        
         
        if(x != y){
            if(conjunto_encabezado[x] <= conjunto_encabezado[y]){  //si conjunto_encabezado[x] <= conjunto_encabezado[y]
                conjunto_encabezado[y] += conjunto_encabezado[x]; //suma las cantidades y luego combina el conjunto x en y
                conjunto_encabezado[x] = 0; //pone cuenta en 0
                primer_elem[x] = 0; //pone primer elemento en 0
                nombre_conjunto[x] = y; 
                siguiente_elem[y] = x; 
            }
            else{
                conjunto_encabezado[x] += conjunto_encabezado[y];  // en el caso que sea mas grande x que y
                conjunto_encabezado[y] = 0; //pone cuenta en 0
                primer_elem[y] = 0; //pone primer elemento en 0
                nombre_conjunto[y] = x; 
                siguiente_elem[x] = y;
            }
        }
}



int grafo::kruskal(){
    int arbol_minimopeso = 0; //suma todos los pesos de los vertices
    sort(aristas.begin(),aristas.end());   //aplico un sort para acomodar las aristas por pesos  
    
    CE ca(this->V);//ca = conjunto 

    vector<arista>::iterator it;
    
    //bucle donde va a buscar las aristas y luego combina
    for(it = aristas.begin(); it!=aristas.end();it++){
        int u = it->second.first;
        int v = it->second.second;

        int Uencontrada = ca.encuentra(u); //busco primer componente
        int Vencontrada = ca.encuentra(v); //busco segunda componente


        if(Uencontrada != Vencontrada){
            int costo = it->first;
            arbol_minimo.push_back({costo,{u,v}});
            arbol_minimopeso += it->first;

            ca.combina(Uencontrada,Vencontrada); //combina
        }
    }
    return arbol_minimopeso;
}

int main(){

    grafo G;
    int u,v,costo;
    
    //inserto las aristas con sus pesos
    G.insertar_arista(1,2,6);
    G.insertar_arista(1,4,5);
    G.insertar_arista(1,3,1);
    G.insertar_arista(2,3,5);
    G.insertar_arista(2,5,3);
    G.insertar_arista(3,5,6);
    G.insertar_arista(3,6,4);
    G.insertar_arista(3,4,5);
    G.insertar_arista(5,6,6);
    G.insertar_arista(4,6,2);   

    int peso = G.kruskal();
    cout << "Vertices con pesos del arbol minimo: " << endl;
    G.mostrar();
    cout << "El peso del arbol minimo es: " << peso;

    return 0;
}