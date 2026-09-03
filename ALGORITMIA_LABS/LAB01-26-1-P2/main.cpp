// Autor: Dany Zhou

#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <cmath>
using namespace std;
void calcularDuracionYGanancia(int *tipo,int *caries,int cantUbicaciones,int cantTipos,
        int *ganancia,int *duracion,int *duracionDeCadaUbicacion,int *gananciaDeCadaUbicacion) {
    //Aca se calculara la ganancia y duracion por atender cada ubicacion
    for (int i=0;i<cantUbicaciones;i++) {
        for (int j=0;j<cantTipos;j++) {
            if (tipo[i]==j+1) {
                duracionDeCadaUbicacion[i]=caries[i]*duracion[j];
                gananciaDeCadaUbicacion[i]=caries[i]*ganancia[j];
            }
        }
    }
}
void convertirBase(int num,int base,int *combinacion,int cantUbicaciones) {
    int j=0;
    for (int i=0;i<cantUbicaciones;i++) {//nos aseguramos que la combinacion empiece en 0
        combinacion[i]=0;
    }
    while (num>0) { //comvertimos la conbinacion actual a la base
        combinacion[j]=num%base;
        num=num/base;
        j++;
    }
}
// void cargabin(int num,int n,int *cromosoma) {
//     int resto,i=0;
//     for (int j=0;j<n;j++) cromosoma[j]=0;
//     while(num>0) {
//         resto=num%2;
//         num=num/2;
//         cromosoma[i]=resto;
//         i++;
//     }
// }
void evaluarCombinacion(int *combinacion,int cantUbicaciones,int *duracion,int *ganancia,int *cita,
        int &gananciaMaxima,int *mejorCombinacion) {
    int tiempocita1=0,tiempocita2=0,tiempocita3=0,gananciacita1=0,gananciacita2=0,gananciacita3=0,gananciatotal=0;
    bool cumple=true;
    for (int i=0;i<cantUbicaciones;i++) {//Cuando combinacion[i]=0 es porquen no se atendera esa ubcacion
        if (combinacion[i]==1) {
            tiempocita1+=duracion[i];
            gananciacita1+=ganancia[i];
        }
        if (combinacion[i]==2) {
            tiempocita2+=duracion[i];
            gananciacita2+=ganancia[i];
        }
        if (combinacion[i]==3) {
            tiempocita3+=duracion[i];
            gananciacita3+=ganancia[i];
        }
        if (tiempocita1>cita[0] or tiempocita2>cita[1] or tiempocita3>cita[2]) {
            //si alguno de los tiempo de citra de la actual combinacion supera al tiempo de cita maximo
            //declarado esa combinacion sera incorrecta
            cumple=false;
        }
    }
    if (cumple) {//Si cumple procedemos a comprar si la actual combinacion es mejor que la que teniamos guardada anteriormente
        gananciatotal = gananciacita1 + gananciacita2 + gananciacita3;
        if (gananciatotal>gananciaMaxima) {
            gananciaMaxima=gananciatotal;
            for (int i=0;i<cantUbicaciones;i++) {
                mejorCombinacion[i]=combinacion[i];
            }
        }
    }
}
int main() {

    int tipo[]={1,1,2,3,3,4,4,4};
    int caries[]={3,1,0,1,2,1,2,3};

    int duracion[]={5,7,10,12};
    int ganancia[]={20,30,35,42};
    int cita[]={60,45,50};

    int gananciaMaxima=INT_MIN;

    //Para ubicación de las caries habrá 4 opciones:   Cita 1, cita 2 , cita 3 , no entender
    //La cantidad de combinaciones posibles será 4^8
    int base=4,cantUbicaciones=8,cantTipos=4;
    int combinaciones = pow(base,cantUbicaciones);

    int duracionDeCadaUbicacion[cantUbicaciones];
    int gananciaDeCadaUbicacion[cantUbicaciones];
    int mejorCombinacion[cantUbicaciones];

    calcularDuracionYGanancia(tipo,caries,cantUbicaciones,cantTipos,ganancia,duracion,duracionDeCadaUbicacion,
        gananciaDeCadaUbicacion);

    int combinacion[cantUbicaciones];
    for (int i=0;i<combinaciones;i++) {
        convertirBase(i,base,combinacion,cantUbicaciones);
        evaluarCombinacion(combinacion,cantUbicaciones,duracionDeCadaUbicacion,gananciaDeCadaUbicacion,
            cita,gananciaMaxima,mejorCombinacion);
    }

    for (int i=0;i<cantUbicaciones;i++) {
        if (mejorCombinacion[i]!=0) {
            cout<<"Cita "<<mejorCombinacion[i]<<": "<< "diente "<<i+1<<endl;
        }
    }
    cout<<"Ganancia Maxima = "<<gananciaMaxima<<" "<<endl;
    return 0;
}
