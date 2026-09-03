// // Autor: Dany Zhou
//
// #include <iostream>
// #include <iomanip>
// #include <climits>
// #define COL 6
// using namespace std;
//
// int robot(int x,int y,int n,int m,int tablero[][COL]) {
//     // Determinamos la cantidad máxima de anillos completos.
//
// }
// int main() {
//
//     int n=6;
//     int m=6;
//     int tablero[][COL] {
//         {0,0,0,1,0,1},
//         {0,0,1,0,0,0},
//         {1,0,0,0,0,0},
//         {0,1,0,0,1,0},
//         {0,0,0,0,1,0},
//     };
//
//     cout<<"Unidades encontradas: "<<robot(0,0,n,m,tablero)<<endl;
//
//     return 0;
// }
#include <iostream>
#define N 6
#define M 6
using namespace std;
int buscarUnidades(int fila,int columna,int filasMatriz,int columnasMatriz,int terrenoBusqueda[N][M],int k) {
    int contador=0;
    if (fila-k < 0  or fila+k>=filasMatriz or columna-k<0 or columna+k>=columnasMatriz ) {
        return 0;
    }
    if (k==0) {
        if (terrenoBusqueda[fila][columna]==1) {
            contador++;
        }
    }else {
        for (int i = -k ; i <= k; i++) {
            if (terrenoBusqueda[fila-k][columna+i] == 1) {
                contador++;
                terrenoBusqueda[fila-k][columna+i] = 0;
            }
            if (terrenoBusqueda[fila+k][columna+i] == 1) {
                contador++;
                terrenoBusqueda[fila+k][columna+i] = 0;
            }
            if (terrenoBusqueda[fila+i][columna+k] == 1) {
                contador++;
                terrenoBusqueda[fila+i][columna+k] =0;
            }
            if (terrenoBusqueda[fila+i][columna-k] == 1) {
                contador++;
                terrenoBusqueda[fila+i][columna-k] = 0;
            }
        }
    }
    return contador + buscarUnidades(fila,columna,N,M,terrenoBusqueda,k+1);
}
int main() {
    int fila=3,columna=2;
    int terrenoBusqueda[N][M] = {
        {0,0,0,1,0,1},
        {0,0,1,0,0,0},
        {0,1,0,0,0,1},
        {1,0,0,0,0,0},
        {0,1,0,0,1,0},
        {0,0,0,0,1,0}
    };

    cout<< buscarUnidades(fila,columna,N,M,terrenoBusqueda,0) <<endl;
    return 0;
}
