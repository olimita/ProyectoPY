#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 

#define KCLUSTERS 8
#define ITERATIONS 10


using namespace std;

class Registro {       // The class
  public:             // Access specifier
    vector<string> atributos;        // Attribute (int variable)
    //string Estrato;  // Attribute (string variable)
    Registro(){

    };
    Registro (vector<string> x) {
      for(int i = 0;i<x.size(); i++){
          atributos.push_back(x[i]);
      }
    };

    void set(vector<string> x) {
      for(int i = 0;i<x.size(); i++){
          atributos[i] = x[i];
      }
    };
    void clean(){
      atributos.clear();
    }
};

class Cluster{
  public:
    vector<Registro> partes;
    Registro mode;
    Registro oldMode;
    Cluster (){
      mode = Registro();
    };

    void asignar(Registro r){
      partes.push_back(r);
    }

    void setMode(Registro r){
      mode = r;
    }
    void setOldMode(Registro r){
      oldMode = r;
    }

    void newMode(){
      vector<string> opciones[mode.atributos.size()];
      vector<int> cantidades[mode.atributos.size()];
      vector<string> nuevaModa;
      for(int i =0; i<mode.atributos.size();i++){
        for(int j =0; j < partes.size();j++){
          string actual = partes[j].atributos[i];
          vector<string>::iterator itr = find(opciones[i].begin(), opciones[i].end(), actual);
	        if (itr != opciones[i].end()) {
            int lugar = distance(opciones[i].begin(), itr);
            cantidades[i][lugar] +=1;
	        }
	        else {           
		        cantidades[i].push_back(1);
            opciones[i].push_back(actual);
	        }
        }
      }
      for(int i =0; i<mode.atributos.size();i++){
        int selected = *max_element(cantidades[i].begin(), cantidades[i].end());
        vector<int>::iterator selected2 = find(cantidades[i].begin(),cantidades[i].end(),selected);
        int selected3 = distance(cantidades[i].begin(), selected2);
        nuevaModa.push_back(opciones[i].at(selected3));
      }
      oldMode = mode;
      mode.set(nuevaModa);
    };

};

double distancia(Registro primero, Registro segundo){
  double coincidencias = 0; 
  for(int i = 0; i<primero.atributos.size();i++ ){
    if(primero.atributos[i] == segundo.atributos[i]){
      coincidencias += 1;
    }
  }
  return coincidencias/primero.atributos.size();
}

class Universo{
  public:
    vector<Cluster> grupos;
    int unidades;

    Universo(){
      unidades = 0;
    }
    
    void addCluster(Cluster c){
      grupos.push_back(c);
    }

    int size(){
      return grupos.size();
    }

    void test(){
      for(int i =0 ; i < grupos.size();i++){
        for(int j =0; j < grupos[i].partes.size();j++){
          for(int k =0; k < grupos.size();k++){
            double coind =distancia(grupos[i].partes[j], grupos[k].mode);
            cout << coind ;
            cout << "   " << "Cluster ";
            cout << i;
            cout << " Registro ";
            cout << j;
            cout << " comparado con mode del Cluster ";
            cout << k << "\n";
          };
        };
      };
    };

};

//se separan los elementos por coma y se guardan en un vector que se retorna
vector<string> splitItems(string str){
    string tmp = "";
    bool inString = false;
    vector<string> elements;
    
    for(int i=0; i< str.size();i++){
        if(str[i] == '\"' && !inString){
            tmp+=str[i];
            inString = true;
        
        }else if(str[i] != '\"' && inString){
            tmp+=str[i];
        }else if(str[i] == '\"' && inString){
            inString =false;
            tmp+=str[i];
            elements.push_back(tmp);
            tmp = "";
        }
        else if(str[i] != ',' && !inString){
            tmp+=str[i];
        }else{
            if(tmp !=""){
                elements.push_back(tmp);
                tmp = "";
            }
        }
    }
    elements.push_back(tmp);

    return elements;
}

Universo inicializar(vector<string> inputData, int k){
  Universo resultado;
  Cluster aux;
  vector<string> elements;
  vector<double> diferencias;
  int iSecret;
  for(int i = 0; i<k;i++){
    resultado.addCluster(aux);
  }
  
  for(int i =0;i<31;i++){
    elements.push_back("10010");
  }

  Registro aux2(elements);
  Registro aux3(elements);

  for(int i = 0; i < k;i++){
    iSecret = (rand() % inputData.size()) + 1;
    //cout<<iSecret<<endl;
    elements = splitItems(inputData[iSecret]);
    aux2.set(elements);
    resultado.grupos[i].setMode(aux2);
    resultado.grupos[i].setOldMode(aux3);
  }

  for(int i = 1;i < inputData.size();i++){
    elements = splitItems(inputData[i]);
    aux2.set(elements);
    for(int j = 0; j<k;j++){
      double diff = distancia(aux2, resultado.grupos[j].mode);
      diferencias.push_back(diff);
    }
    double selected = *min_element(diferencias.begin(), diferencias.end());
    vector<double>::iterator selected2 = find(diferencias.begin(),diferencias.end(),selected);
    int selected3 = distance(diferencias.begin(), selected2);
    //cout<<selected<<endl<<selected3<<endl;
    resultado.grupos[selected3].asignar(aux2);
    resultado.unidades += 1;
    diferencias.clear();
  }

  return resultado;
}

bool isFinished(Universo u){
  for(int i =0 ;i<u.grupos.size();i++){
    if(distancia(u.grupos[i].mode, u.grupos[i].oldMode) != 0) return false;
  }
  return true;
}

Universo procesar(Universo u){
  Universo temp;
  vector<string> elements;
  vector<double> diferencias;
  Cluster aux;
  for(int i =0;i<31;i++){
    elements.push_back("1");
  }
  Registro aux2(elements);
  for(int i = 0; i<u.grupos.size();i++){
    temp.addCluster(aux);
    temp.grupos[i].setMode(aux2);
    temp.grupos[i].setOldMode(aux2);
  }
  cout<<"creo temporal"<<endl;
  for(int i=0;i<u.grupos.size();i++){
    for(int j=0; j<u.grupos[i].partes.size();j++){
      for(int k = 0; k<u.grupos.size();k++){
        double diff = distancia(u.grupos[k].mode, u.grupos[i].partes[j]);
        diferencias.push_back(diff);
      }
      double selected = *min_element(diferencias.begin(), diferencias.end());
      vector<double>::iterator selected2 = find(diferencias.begin(),diferencias.end(),selected);
      int selected3 = distance(diferencias.begin(), selected2);
      temp.grupos[selected3].asignar(u.grupos[i].partes[j]);
      temp.unidades += 1;
      diferencias.clear();
    }
  }

  return temp;
}

int main() {
  int kModes = 8;
  vector<string> elements;
  vector<string> inputData;
  string line;
  string tmp;
  Cluster aux;
  srand (time(NULL));

  for(int i =0;i<31;i++){
    elements.push_back("10010");
  }
  Registro reg (elements);

  ifstream myfile ("Saber_prueba.csv");
  if(myfile.is_open()){
      while (getline(myfile,line))
      {
          inputData.push_back(line);
      }
      myfile.close();
  }

  Universo prueba;

  prueba = inicializar(inputData, KCLUSTERS);

  for(int i =0;i<ITERATIONS;i++){
    for(int j = 0;j<prueba.grupos.size();j++){
      prueba.grupos[j].newMode();
    }
    prueba = procesar(prueba);
  }
}