/*
Actividad 3.4 - Actividad Integral estructura de datos no lineales (Evidencia Competencia).
- Actividad integral donde regresamos un árbol max heap de acuerdo las ocurrencias de una IP.
Autores:
- Jeshua Nava Avila | A01639282
- Barbara Nicole Vidal Sandoval | A01635233
- Renet de Jesus Perez Gomez | A01640555 
Fecha de creación y última modificación:
- 22/10/2021
- 22/10/2021 
*/

// Librerías
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

//Clase para crear nodos
class Node{
    public:
        string IP;
        int ocurrencia;

        // Constructor.
        Node(string ip, int ocurrencia_n = 0){
            this->IP = ip;
            this->ocurrencia = ocurrencia_n;
        }
};

//Clase para crear el Tree Heap
class priority_queue{
    private:
        int _size{}; //Contador de la cantidad de valores del vector
        vector<Node> heapTree = {Node("string",-1)}; //Vector que contendra los datos de nuestra "priority_queue"

        /**
         *Metodo que nos ayuda balancear el arbol (en este caso baja el "nodo" en el arbol)  
         *Complejidad: O(Log2N)
         * @param i //Índice de referencia
        **/
        void shiftDown(int i){
            if(i > this->_size) return; //Llegamos a la ultima posición

            int swapId = i; //Asignamose el index actual a una variable auxiliar

            if (left(i) <= this->_size && this->heapTree[i].ocurrencia < this->heapTree[left(i)].ocurrencia)
                swapId = left(i); //Significa que el hijo izquierdo es menor al indice de la recursion actual

            if (right(i) <= this->_size && this->heapTree[swapId].ocurrencia < this->heapTree[right(i)].ocurrencia)
                swapId = right(i); //Significa que el hijo izquierdo es menor al indice de la recursion actual

            if (swapId != i){ //En caso de que aun haya nodos hijo
                swap(this->heapTree[i], this->heapTree[swapId]); //Cambiamos el nodo de la recursion actual, por el nodo hijo que fue mayor
                shiftDown(swapId); //Aplicamos nuevamente la recursion
            }
            return;
        }

        /**
         *Metodo que nos ayuda balancear el arbol (en este caso sube en el arbol "nodo") 
         *Complejidad: O(Log2N)
         * @param i //Índice de referencia
        **/
        void shiftUp(int i){
            if(i > _size) return; //Significa que llegamos al ultimo valor
            if(i == 1) return; //Significa que llegamos al valor mas relevante
            if(this->heapTree[i].ocurrencia > this->heapTree[parent(i)].ocurrencia){//Si el nodo hijo es mas grande que el padre, lo cambiamos
                swap(this->heapTree[parent(i)], this->heapTree[i]);
            }
            shiftUp(parent(i));//Llamada a función
        }

        /**
         *Metodo para calcular el indice del nodo padre, tomando un indice como referencia  
         *Complejidad: O(1)
         *@param i //Indice de referencia para calcular el nodo padre 
        **/
        int parent(int i) { return floor(i / 2); }

        /**
         *Metodo para calcular el índice del nodo hijo izquierdo, tomando un índice como referencia  
         *Complejidad: O(1)
         *@param i //Índice de referencia para calcular su nodo hijo izquierdo 
        **/
        int left(int i) { return 2 * i; }

        /**
         *Metodo para calcular el índice del nodo hijo derecho, tomando un índice como referencia    
         *Complejidad: O(1)
         *@param i //Índice de referencia para calcular su nodo hijo derecho 
        **/
        int right(int i) { return 2 * i + 1; }

    public:
        priority_queue() {}
        ~priority_queue() {}

        /**
         * Metodo que agrega un nuevo dato a la fila de prioridad
         * Complegidad: O(Log2N)
        **/
        void push(string IP, int ocurrencia) {
            Node nodo(IP, ocurrencia); // Creamos al nodo a insertar.
            this->heapTree.push_back(nodo);
            _size++;
            shiftUp(_size); //Llamamos a función para acomodar el valor correctamente 
            return;
        }

        /**
         * Metodo que agrega un nuevo dato a la fila de prioridad
         * Complegidad: O(Log2N)
        **/
        void pop(){
            if (!empty()){//Verificar que arbol heap no este vacio
                if(size() == 1){//Si el arbol heap solo tiene 1 elemnto
                    this->heapTree.pop_back(); //Eliminamos dicho elemento de la priority_queue
                }
                Node root = this->heapTree[1]; // Guardamos el valor mas relevante
                // this->heapTree[0] = 0; //El valor mas relevante le asignamos un 0
                swap(this->heapTree[1], this->heapTree[this->_size--]); 
                shiftDown(1); //Balanceamos el priority_queue
                this->heapTree.pop_back();
            }
        }

        /**
         * Metodo para obtener el dato de mayor prioridad de la priority_queue
         * Complegidad: O(1)
        **/
        Node top(){
            if(!empty()) return this->heapTree[1]; //Si la lista tiene datos, regresaremos el dato mas relevante
            else return Node("-1", -1); //Si esta vacia retornaremos un -1
        }

        /**
         * Metodo para saber si la priority_queue esta vacio
         * Complegidad: O(1)
        **/
        bool empty(){ return !(this->heapTree.size() > 0); } //Si esta vacío retornara "1", caso contrario "0"

        /**
         * Metodo para saber el tamaño de la priority_queue
         * Complegidad: O(1)
        **/
        int size(){ return this->heapTree.size(); }

        //Funciones auxiliares
        /**
         * Metodo imprimir toda la priority_queue
         * Complegidad: O(n)
        **/
        void imprimir() {
            for (int i = 1; i < this->heapTree.size(); i++) {
                string ip = this->heapTree[i].IP;
                int ocurrencia = this->heapTree[i].ocurrencia; 
                cout << "IP: " << ip << " - Ocurrencia: " << ocurrencia << " -> ";
            } 
            cout << endl;
        }
};

/** 
 * Obtiene el IP de una línea de una consulta.
 * Complejidad Computacional: O(1).
 * Las IP tienen un tamaño similar, y solamente se selecionnan algunos carácteres.
 * 
 * @param linea Línea de la bitacora al cual se quiere obtener su IP.
 * @return El IP de una línea de bitacora.
 */
string ipFromLine(string linea){ //obtener el decimal de cada IP
  string carac = "", ip = ""; 
  int pos = 18; // La IP empieza en el index 18 de cada línea en consulta.
  carac = linea[pos];
  
  //Ciclamos while para obtener la IP (el while funcionara desde el primer caracter hasta que haiga un espacio)
  while(carac != " "){
    ip += linea[pos];
    pos++;
    carac = linea[pos];
  }  
  return ip;
}

/** 
 * Obtiene la ocurrencia de una línea de consulta.
 * Complejidad Computacional: O(1).
 * La ocurrencia siempre aparece en la parte final de un renglón en una consulta. Por lo tanto, para obtenerlo seguimos unos pasos determinados.
 * 
 * @param linea Línea de la bitacora al cual se quiere obtener el valor de ocurrencia.
 * @return La ocurrencia en 
 */
int ocurrenciaFromLine(string linea){ //obtener el decimal de cada IP
  string carac = "", ocurrenciaInv = "", ocurrencia = "";
  int pos = linea.length() - 1, temp = 0;
  carac = linea[pos]; 
  //Rescatamos la ocurrencia (solo que en orden inverso)
  while(carac != " "){
    ocurrenciaInv+= linea[pos];
    pos--;
    carac = linea[pos];
  }
  // Ahora que tenemos la ocurrencia en inverso, lo volvemos a inversar para obtener la cantidad de ocurrencias.
  pos = ocurrenciaInv.length() -1; // La última posición.
  while(pos>=0){
    ocurrencia+=ocurrenciaInv[pos];
    pos--;
  }
  return stoi(ocurrencia);
}


/**
 * Lee un archivo, y cada línea de texto lo guarda dentro de un vector.
 * Complejidad computacional: O(n).
 * Tiene que leer cada línea que viene dentro del archivo.
 * 
 * @param nombreArchivo El nombre del archivo en string.
 * @return Un vector que contiene las líneas del archivo.
 * 
 */
vector<string> leerVectorizarArchivo(string nombreArchivo) {
    vector<string> bitacora;
    ifstream archivo(nombreArchivo.c_str()); // Abrir archivo.
    string linea;
    
    // Obtener línea de archivo, y almacenar contenido en "linea".
    while (getline(archivo, linea)) {
       bitacora.push_back(linea);
    }
    archivo.close();
    return bitacora;
}

int main(){
    priority_queue valoresMaximos;
    vector<string> registros, unicosIP;
    unordered_map<string, int> IPS;
    string temp;
    
    registros = leerVectorizarArchivo("Consulta1.txt"); // Guardar cada línea.
    // Actualizamos el unordered_map con IPs y ocurrencias.
    // Encontrar y definir las veces que se encuentra un IP en el vector.
    for(int i=0; i < registros.size(); i++){
      // Si encuentra la IP dentro del unorder map, le suma uno. Si no, lo agrega.
      if(IPS.count(ipFromLine(registros[i])) == 0){
        IPS[ipFromLine(registros[i])] = ocurrenciaFromLine(registros[i]);
      } else {
        IPS[ipFromLine(registros[i])] += ocurrenciaFromLine(registros[i]);
      }
    }
    // Recorremos de nuevo por los registros, para agregarlos al árbol heap max.
    for(int i = 0; i < registros.size(); i++){
        // Revisar si no repetimos IP.
        if(find(unicosIP.begin(), unicosIP.end(), ipFromLine(registros[i])) != unicosIP.end()){
            ; // No hacer nada si ya se encuentra el IP dentro de unicosIP, para no repetir.
          } else {
            unicosIP.push_back(ipFromLine(registros[i]));
            temp = ipFromLine(registros[i]); // Obtenemos IP.
            int ocurrencia = IPS[ipFromLine(registros[i])]; // Obtenemos ocurrencias de IP. 
            valoresMaximos.push(ipFromLine(registros[i]), ocurrencia);
          }
    }
    cout << "Las IP con mas acceso en la consulta: " << endl;
    for(int i = 0; i < 5; i++){
        Node node = valoresMaximos.top();
        cout << i+1 << ".- " << "IP: " <<  node.IP << " - Ocurrencia: " << node.ocurrencia <<endl;
        valoresMaximos.pop();
    }
    return 0;
}