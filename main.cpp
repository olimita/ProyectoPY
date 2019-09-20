#include <iostream>
#include <vector>

using namespace std;

class Registro {       // The class
  public:             // Access specifier
    string atributos[2];        // Attribute (int variable)
    //string Estrato;  // Attribute (string variable)
    int Puntaje;
    Registro(){

    };
    Registro (string x, string y, int z) {
      atributos[0] = x;
      atributos[1] = y;
      Puntaje = z;
    };
};

class Cluster{
  public:
    vector<Registro> partes;
    Registro mode;
    Cluster (){
      mode = Registro();
    };

    void asignar(Registro r){
      partes.push_back(r);
    }

    void newMode(Registro r){
      mode = r;
    };

};

double distance(Registro primero, Registro segundo){
  double coincidencias = 0; 
  for(int i = 0; i<2;i++ ){
    if(primero.atributos[i] == segundo.atributos[i]){
      coincidencias += 1;
    }
  }
  return coincidencias/2;
}

class Universo{
  public:
    vector<Cluster> grupos;

    Universo(){
    }
    
    void addCluster(Cluster c){
      grupos.push_back(c);
    }

    void test(){
      for(int i =0 ; i < grupos.size();i++){
        for(int j =0; j < grupos[i].partes.size();j++){
          for(int k =0; k < grupos.size();k++){
            double coind =distance(grupos[i].partes[j], grupos[k].mode);
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

int main() {
  Registro reg1 ("M", "Estrato 1", 70);
  Registro reg2 ("M", "Estrato 2", 70);
  Cluster clus1;
  clus1.asignar(reg1);
  clus1.asignar(reg2);
  clus1.newMode(reg1);
  Registro reg3 ("M", "Estrato 1", 70);
  Registro reg4 ("F", "Estrato 1", 70);
  Cluster clus2;
  clus2.asignar(reg3);
  clus2.asignar(reg4);
  clus2.newMode(reg3);
  Registro reg5 ("F", "Estrato 2", 70);
  Registro reg6 ("F", "Estrato 1", 70);
  Cluster clus3;
  clus3.asignar(reg5);
  clus3.asignar(reg6);
  clus3.newMode(reg5);

  Universo prueba;
  prueba.addCluster(clus1);
  prueba.addCluster(clus2);
  prueba.addCluster(clus3);
  prueba.test();

  //double distancia = distance(prueba.grupos[0].partes[1], prueba.grupos[0].mode);
  //printf("%.7lf\n",distance(prueba.grupos[0].partes[0], prueba.grupos[0].mode));
  //printf("%.7lf\n",distancia);
  cout << "Hello World!\n";
}