/*
Actividad 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia).
- Actividad integral donde regresamos un archivo conteniendo registros ordenados y limitados de una bitácora.
Autores:
- Jeshua Nava Avila | A01639282
- Barbara Nicole Vidal Sandoval | A01635233
- Renet de Jesus Perez Gomez | A01640555 
Fecha de creación y última modificación:
- 12/10/2021
- 22/10/2021 
*/

// Librerías
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>

using namespace std;

//Clases ---
//Esta clase nos ayudara a organizar la información
class Node{
    public:
      int ip; //Guarda la codificación de la IP
      int ocurrencia; //Cuantas veces aparece una IP 
      string formatoOriginal; //Guarda la linea de la bitacora correspondiente a la IP

      //Contructor
      Node(){
          this->ip = 0;
          this->ocurrencia = 0;
          this->formatoOriginal = " ";
      }

      //Constructor
      Node(int ip, int ocurrencia, string formatoOriginal){
          this->ip = ip;
          this->ocurrencia = ocurrencia;
          this->formatoOriginal = formatoOriginal;
      }

      /**
       * Retorna el dia de la IP
       * Complejidad computacional: O(1)
       * @return //Retorna el dia en el que esta la IP
       **/
      string getDay(){
        return this->formatoOriginal.substr(0, 6);
      }

      /**
       * Retorna la IP
       * Complejidad computacional: O(1)
       * @return //Retorna la IP de la lina
       **/
      string getIP(){
        string temp = ""; // Variable que nos ayduara a guardar posiciones de la linea de la bitacora
        string IP = ""; //Variable donde se guardara la IP
        int pos = 0; //Variable auxiliar para las posiciones

        temp = this->formatoOriginal[14]; // Asignamos la posicion 14
        
        if(temp == " "){ // Si es verdadero significa que comienza en la linea 15
          pos = 15;
          temp = this->formatoOriginal[pos];
        }else{ // Si es falso significa que comienza en la linea 15
          pos = 16;
          temp = this->formatoOriginal[pos];
        }

        //Comenzamos a obtener la IP
        while(temp != " "){
          IP += temp;
          pos++;
          temp = this->formatoOriginal[pos];
        }

        return IP;
      }

};

//Funciones de conversion y calculo ---
/**
 * Función que convierte un mes en un valor int, para poder comparar meses.
 * Complejidad computacional: O(1).
 * Como trabajamos con un unordered_map, que es implementado con un Hash Table, estos tienen un costo de búsqueda, insersión
 * y borrado de O(1).
 * 
 * @param mes String que contiene el mes que se quiere encontrar su equivalencia en int.
 * @return El int equivalente del mes, que es buscado en el unordered_map.
 */
int mesNum(string mes){
  unordered_map<string, int> meses({
    {"Ene", 1}, {"Feb", 2}, {"Mar", 3}, {"Abr", 4}, {"May", 5}, {"Jun", 6}, 
    {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dic", 12}
    });
    
    return meses[mes];
}

/**
 * Convierte el mes, día, hora, minuto y segundo en un número decimal.
 * Ejemplo: Oct 9 10:32:24  -> 1009103224.
 * Ejemplo: Oct 9 00:00:00  -> 1009000000.
 * Ejemplo: Oct 9 23:59:59  -> 1009235959.
 * 235959
 * F1 - F2 = x
 * x > 235959 
 * Ejemplo: Nov 20 01:00:59 -> 1120010059.
 * Complejidad: O(1).
 * Como el input siempre es una línea de n carácteres, siempre realiza una serie determinada de pasos.
 * 
 * Orden de meses: Ene = 1 - Dec = 12.
 * Orden de los días: 1-31.
 * Orden de horas: 0 - 23.
 * Orden de minutos: 0 - 59.
 * Orden de segundos: 0 - 59.
 * @param linea Un string que contiene el registro (fecha).
 * @return Número equivalente a la fecha de registro.
 */
int tiempoDecimal(string linea){
    string mes, dia, hor, min, seg, temp;
    // Obtenemos mes en número y lo cambiamos a string.
    mes = to_string(mesNum(linea.substr(0, 3))); // mesNum no afecta complejidad, ya que también es O(1).
    // Obtenemos día, hora, minuto y segundos en strings.
    temp = linea[5];
    if(temp == " "){
      dia = "0"; // En la posicion 5 aveces sera un espacio, para conservar el formato agregamos 0 al inicio.
      dia += linea.substr(4, 1);
      hor = linea.substr(6, 2);
      min = linea.substr(9, 2);
      seg = linea.substr(12, 2);
    } else {
      dia = linea.substr(4, 2); 
      hor = linea.substr(7, 2);
      min = linea.substr(10, 2);
      seg = linea.substr(13, 2);
    }
    // Juntamos variables en un string y los convertimos en un int.
    return stoi(mes + dia + hor + min + seg); 
}

/**
 * Esta funcion obtiene de la linea la IP, para formar un codigo unico y retnorarla como resultado...
 * El codigo se compone  de 2 partes:
 * 1 - La suma de los numeros que componen la IP
 * 2 - Concatenacion directa de los primeros 6 numeros de conforman la IP
 * 
 * Complejidad computacional: O(n)
 * 
 * de los numeros que componente la IP concatenado con los primeros
 * @param lineal //Seria la linea de la bitacora a la que queremos codificar la IP
 * @return //Retorna la codificación de la IP 
 */
int ipDecimal(string linea){ //obtener el decimal de cada IP
  
  string temp = "", ip = ""; //Variables auxiliares para limpiar y guardar los numeros de la IP
  
  int pos = 0; //Variable que nos indicara la posición de donde empezaremos en la linea 
  int resultado = 0; // Variable que retornara la codificacion de la IP

  temp = linea[14];
  if(temp == " "){//Ip comienza en 15
    pos = 15;
    temp = linea[pos];
  }else{//Ip comienza en 16
    pos = 16;
    temp = linea[pos];
  }

  string security = ""; //Nos ayudara a guardar los numeros de la IP a guardar para agregar seguridad a la IP
  int cont = 0; //Con esta variable decidimos cuantos numeros de la IP guardamos

  //Limpiamos el string de "." y ":"
  while(temp != " "){
    if (temp != "." && temp != ":"){
      ip += temp;
      if(cont < 6) security += temp; //En caso de que se cumpla, salvara el numero en la variable "security"
    }
    pos++;
    cont++;
    temp = linea[pos];
  }

  // Sumamos los numeros que conforman la IP
  for(int i = 0; i < ip.length(); i++){
    temp = ip[i];
    resultado += stoi(temp);
  }
  
  //Como media de seguridad le agregmos los primeros digitos de la IP
  string sumaTemp = "";
  sumaTemp = to_string(resultado); //Convertimos la primera parte de la codificacion en string
  sumaTemp += security; //Concatenamos primera parte con segunda parte
  resultado += stoi(sumaTemp); //Lo convertimos a int

  return resultado;
}


//Funciones de ordenamiento ---
/**
 * Función que compara elementos de un vector y los ordena (parte del función Merge Sort).
 * Complejidad computacional: O(n).
 * Aunque tenga varios for loops y whiles, ninguno está anidado (en total n pasos para completar merge).
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio del vector.
 * @param m Int index del punto medio del vector.
 * @param r Int index del final de un vector.
 */
void merge(vector<string>& V, int l, int m, int r){
    vector<string> L, R; // Subarreglos temporales
    int n1 = m - l + 1, n2 = r - m, i = 0, j = 0, k = l;
    for (int i = 0; i < n1; i++){
        L.push_back(V[l+i]);
    }

    for (int j = 0; j < n2; j++){
        R.push_back(V[m+j+1]);
    }

    i = j = 0;

    while (i < n1 && j < n2){
        if (tiempoDecimal(L[i]) <= tiempoDecimal(R[j])){
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        V[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        V[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Ordena un vector con el algoritmo MergeSort.
 * Complejidad computacional (promedio): O(nLog n).
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio de un vector.
 * @param r Int index del final de un vector (size - 1).
 */
void ordenaMerge(vector<string>& V, int l, int r){
    int m = 0;
    if (l < r){
        m = floor(((l + r) / 2));
        ordenaMerge(V, l, m);
        ordenaMerge(V, m + 1, r);
        merge(V, l, m, r);
    }
}

/**
 * Algoritmo Merge que pertenece a "ordenaMergeIP"
 * Complejidad computacional O(n)
 * @param V Vector de nodos que se deseamos ordenar (el nodo contiene la informacion de la IP).
 * @param l Int index del inicio del vector.
 * @param m Int index del punto medio del vector.
 * @param r Int index del final de un vector.
 **/
void mergeIP(vector<Node>& V, int l, int m, int r){
    vector<Node> L, R; // Subarreglos temporales
    int n1 = m - l + 1, n2 = r - m, i = 0, j = 0, k = l;
    for (int i = 0; i < n1; i++){
      L.push_back(Node(V[l + i].ip, V[l + i].ocurrencia, V[l + i].formatoOriginal));
    }
    
    for (int j = 0; j < n2; j++){
        R.push_back(Node(V[m + j + 1].ip, V[m + j + 1].ocurrencia, V[m + j + 1].formatoOriginal));
    }

    i = j = 0;
    
    while (i < n1 && j < n2){
        if (L[i].ip <= R[j].ip){
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        V[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        V[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Ordena un vector con el algoritmo MergeSort... Este merge-sort ordena por la codificacion de la IP.
 * Complejidad computacional (promedio): O(nLog n).
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 *
 * @param V VVector de nodos que se deseamos ordenar (el nodo contiene la informacion de la IP).
 * @param l Int index del inicio de un vector.
 * @param r Int index del final de un vector (size - 1).
 */
void ordenaMergeIP(vector<Node>& V, int l, int r){
    int m = 0;
    if (l < r){
        m = floor(((l + r) / 2));
        ordenaMergeIP(V, l, m);
        ordenaMergeIP(V, m + 1, r);
        mergeIP(V, l, m, r);
    }
}

/**
 * Algoritmo Merge que pertenece a "ordenaMergeIP"
 * Complejidad computacional O(n)
 * @param V Vector de nodos que se deseamos ordenar (el nodo contiene la informacion de la IP).
 * @param l Int index del inicio del vector.
 * @param m Int index del punto medio del vector.
 * @param r Int index del final de un vector.
 **/
void mergeIPOcurrencia(vector<Node>& V, int l, int m, int r){
    vector<Node> L, R; // Subarreglos temporales
    int n1 = m - l + 1, n2 = r - m, i = 0, j = 0, k = l;
    for (int i = 0; i < n1; i++){
        L.push_back(Node(V[l + i].ip, V[l + i].ocurrencia, V[l + i].formatoOriginal));
    }

    for (int j = 0; j < n2; j++){
        R.push_back(Node(V[m + j + 1].ip, V[m + j + 1].ocurrencia, V[m + j + 1].formatoOriginal));
    }
    
    i = j = 0;
    
    while (i < n1 && j < n2){
        if (L[i].ocurrencia >= R[j].ocurrencia){
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        V[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        V[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Ordena un vector con el algoritmo MergeSort... Este merge-sort ordena por la ocurrencia de IP.
 * Complejidad computacional (promedio): O(nLog n).
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 *
 * @param V VVector de nodos que se deseamos ordenar (el nodo contiene la informacion de la IP).
 * @param l Int index del inicio de un vector.
 * @param r Int index del final de un vector (size - 1).
 */
void ordenaMergeIPOcurrencia(vector<Node>& V, int l, int r){
    int m = 0;
    if (l < r){
        m = floor(((l + r) / 2));
        ordenaMergeIPOcurrencia(V, l, m);
        ordenaMergeIPOcurrencia(V, m + 1, r);
        mergeIPOcurrencia(V, l, m, r);
    }
}

//Funciones de busquedas  ---

/**
 * Función que regresa el index de un elemento dentro de un vector, o regresa el índice mas cercano al key,
 * con el algoritmo Binary Search.
 * Complejidad computacional: O(Logn)
 * Dividimos al arreglo de tamaño n en dos hasta llegar a un tamaño 1 (o un lugar en donde se encuentra el elemento).
 * 
 * @param V vector tipo int em donde se busca el elemento.
 * @param key elemento que se desea encontrar su index dentro del vector (si existe).
 * @return El índice en donde se encuentra el elemento o el índice más cercano.
 */
int busqBinaria(vector<string> V, int key){
    int l = 0, r = V.size() - 1, index = 0, temp;
    while (r >= l){
        index = floor((l + r) / 2);
        temp = tiempoDecimal(V[index]);
        if (temp == key){
            return index;
        } else if (temp > key){
            r = index - 1;
        } else {
            l = index + 1 ;
        }
    }
    return index; // Retorna el índice más cercano al key. 
}

/**
 * Función que regresa el index de un elemento dentro de un vector, o regresa el índice mas cercano al key,
 * con el algoritmo Binary Search.
 * Complejidad computacional: O(Logn)
 * Dividimos al arreglo de tamaño n en dos hasta llegar a un tamaño 1 (o un lugar en donde se encuentra el elemento).
 *
 * @param V vector tipo Node (el nodo que contiene toda la información de la ip)  en donde se busca el elemento.
 * @param key elemento que se desea encontrar su index dentro del vector (si existe).
 * @return El índice en donde se encuentra el elemento o el índice más cercano.
 */
int busqBinariaIP(vector<Node> V, int key){
    int l = 0, r = V.size() - 1, index = 0;
    while (l <= r){
        index = floor((l + r) / 2);
        if (V[index].ip == key){
            return index;
        } else if (V[index].ip > key){
            r = index - 1;
        } else {
            l = index + 1 ;
        }
    }
    return -1; // Retorna -1 si no lo encuentra.
}

//Funciones de operación ---

/**
 * Lee un archivo, y cada línea de texto lo guarda dentro de un vector.
 * Complejidad computacional: O(n).
 * Tiene que leer cada línea que viene dentro del archivo.
 * 
 * @param nombreArchivo El nombre del archivo en string.
 * @return Un vector que contiene las líneas del archivo.
 */
vector<string> leerVectorizarArchivo(string nombreArchivo) {
    vector<string> bitacora;
    string linea;

    ifstream archivo(nombreArchivo.c_str()); // Abrir archivo.
    
    // Obtener línea de archivo, y almacenar contenido en "linea".
    while (getline(archivo, linea)) {
       bitacora.push_back(linea);
    }

    archivo.close();
    return bitacora;
}


/**
 * Función que pide el rango de fechas a consultar.
 * Complejidad computacional: O(n).
 * Depende de lo que ingrese el usuario.
 * 
 * @param indiceConsulta Número de consulta.
 * @return Un vector string con las fechas de rango.
 */
vector<string> consulta(int indiceConsulta){
  int mesIni = 0, diaIni = 0, mesFin = 0, diaFin = 0;
  string fechaIni = "", fechaFin = "";
  vector<string> fechasBusqueda;
  
  cout << endl << "-=-= Consulta " << indiceConsulta << " -=-=-=-=" << endl;
  cout << "Por favor ingrese el rango de meses que quiera consultar: " << endl;
  cout << "Meses: [1=Ene, 2=Feb, 3=Mar, 4=Abr, 5=May, 6=Jun, 7=Jul, 8=Aug, 9=Sep, 10=Oct, 11=Nov, 12=Dic]" << endl;
  cout << "Dias: [Del 1 al 31]" << endl;

  // Verificamos que ingrese un mes correcto.
  while(mesIni <= 0 || mesIni > 11){ 
    cout << "Mes de inicio: [Ingrese el numero de mes de inicio (1-11)] " << endl << "-> ";
    cin >> mesIni;
    if(mesIni <= 0 || mesIni > 11){
      cout << "Por favor, el mes de inicio debe ser mayor a 0 y menor que 11 :)" << endl;
    } else {
      fechaIni += to_string(mesIni); // Guardamos el valor del mes.
    }
  }

  //Verificamos que ingrese un dia correcto
  while(diaIni <= 0 || diaIni > 31){
    cout << "Dia del mes de inicio: [Ingrese el numero del dia del mes de inicio]" << endl << "-> "; 
    cin >> diaIni;
    if(diaIni <= 0 || diaIni > 31){
      cout << "El dia debe ser entre un numero del 1 al 31 :)" << endl;
    } else if (diaIni < 10) { // Guardamos el valor del día.
      fechaIni += "0" + to_string(diaIni); // Agregamos un cero para mantener formato.
    } else {
      fechaIni += to_string(diaIni); // Guardamos el valor del día.
    }
  }

  // Verificamos que ingrese un mes correcto. Cuidando que no ingrese un mes menor al del mes inicial.
  while(mesFin <= 0 || mesFin > 12 || mesFin < mesIni){
    cout << "Mes final: [Ingrese el numero de mes final]" << endl << "-> ";
    cin >> mesFin;
    if(mesFin <= 0 || mesFin > 12 || mesFin < mesIni){
      cout << "El mes final debe de estar entre el mes " << mesIni << " y el mes 12 :)" << endl;
    } else {
      fechaFin += to_string(mesFin); // Guardamos el valor del mes.
    }
  }

  //Verificamos que ingrese un dia correcto. Cuidando que si es el mismo mes no sea un día menor.
  while(diaFin <= 0 || diaFin > 31 || diaFin < diaIni && mesFin == mesIni){
    cout << "Dia del mes final: [Ingrese el numero del dia del mes final]" << endl << "-> ";
    cin >> diaFin;
    if(diaFin <= 0 || diaFin > 31){
      cout << "Recuerda que el dia es numero entre el 1 y el 31 :)";
    } else if (diaFin < diaIni && mesFin == mesIni){
      cout << "El dia final no puede ser menor al dia de inicio en el mismo mes :)" << endl; 
    } else if (diaFin < 10) {
      fechaFin += "0" + to_string(diaFin); // Agregamos 0 para mantener formato.
    } else {
      fechaFin += to_string(diaFin);
    } 
  }
  // // Terminamos de completar nuestras fechas de busqueda.
  fechaIni += "000000"; // Inicio del día.
  fechaFin += "235959"; // Final del día. 
  // cout<<"Imprimiendo fechas"<<endl;
  // cout<<fechaIni<<endl;
  // cout<<fechaFin<<endl;
  fechasBusqueda.push_back(fechaIni);
  fechasBusqueda.push_back(fechaFin);

  return fechasBusqueda;
}


/**
 * Función que despliega los registros en el rango de fechas, y los guarda en un archivo.
 * Complejidad computacional: O(n^2).
 * Dependiendo del rango de las fechas, será la cantidad de regsitros.
 
 * @param fechas El rango de fechas de consulta.
 * @param bitacora Todas las lineas de la bitacora.
 * @param numConsulta Números de consulta que se realizarán.
 */
void guardaArchivo(vector<string> fechas, vector<string> bitacora, int numConsulta){
  int inicio = 0; //Guardara el indice del inicio de la busqueda (índice es fecha)
  int fin = 0;  //Guardara el indice del fin de la busqueda (índice es fecha)
  int key = 0; //Guarda el ID de la fecha fin

  string consulta = "Consulta" + to_string(numConsulta+1) + ".txt"; //Variable auxiliar para nombrar el documento que contendra los datos
  
  // Consultar las fechas. Ver de donde empieza y donde termina para guardar estos registros en un vector.
  // Buscamos el índice "start" (fecha de inicio) más cercano en bitacora
  key = stoi(fechas[0]); // ID de la fecha inicio.
  inicio = busqBinaria(bitacora, key); // Indice más cercano a la fecha inico.
  key = stoi(fechas[1]); // ID de la fecha fin.
  fin = busqBinaria(bitacora, key); //Indice más cercano a la fecha fin.
  
  // Verificar que los índices no sean los mismos.
  if(inicio-fin==0){
    cout << endl << "-=-= Consulta " << numConsulta + 1 << " -=-=-=-=" << endl;
    cout << "No se encontro ningun registro en el intervalo de fecha solicitado." << endl;
  }else{
    // Recorrer bitacora por estos indices, para guardar los registros en un vector.
    vector<Node> vectorIPs; //Vector para guardar las IP y sus ocurrencias de un dia
    vector<vector<Node>> vectorIPsDay; //Vector que guarda los dias (cada dia es un: vectorIPs)

    //Ciclamos for para recorrer todos los registros de la consulta
    int baseTiempo = tiempoDecimal(bitacora[0]); //Variable que nos ayudara a saber cuando paso un dia
    for(int i = inicio; i < fin+1; i++){ 
      //cout<<"Turno de: "<< bitacora[i] <<endl;
      /*Ejemplo: Oct 9 10:32:24  -> 1009103224.
      * Ejemplo: Oct 9 00:00:00  -> 1009000000.
      * Ejemplo: Oct 9 23:59:59  -> 1009235959.*/

      int temp = baseTiempo - tiempoDecimal(bitacora[i]); //Diferecia para comprobar si estamos en un mismo dia o no.

      if (temp < -235959){//Significa que estamos en un nuevo dia
        vectorIPsDay.push_back(vectorIPs); //Agregamos el dia actual al vecto de dias.
        vectorIPs.clear(); //Limpiamos el vector actual
        baseTiempo = tiempoDecimal(bitacora[i]); //Actualizamos variable para saber si ya paso un dia 
      }

      int IP = busqBinariaIP(vectorIPs, ipDecimal(bitacora[i])); //Buscamos la IP actual en vector "vectorIps"
      
      //Verificacion si es una IP nueva o repertida
      if(IP == -1){//Si no encontramos la IP actual  en el vector "vectorIPs", significa que tenemos que agregar esa IP
        vectorIPs.push_back(Node(ipDecimal(bitacora[i]), 1, bitacora[i]));
      }else{//Significa que esa IP ya tenemos en el vector IPs, por lo que se agrega "+1" en ocurrencia
        vectorIPs[IP].ocurrencia += 1;
      }

      ordenaMergeIP(vectorIPs, 0, vectorIPs.size() - 1); //Ordenamos el vector para la siguiente iteracion
      
      //Este es para el ultimo dia 
      if(i == bitacora.size()-1){
        vectorIPsDay.push_back(vectorIPs);
      }
    }
    

    //Ciclamos for para poder ordenar de mayor a menor las ocurrencias (cada celda es un dia).
    for(int i = 0; i < vectorIPsDay.size(); i++){
        ordenaMergeIPOcurrencia(vectorIPsDay[i], 0, vectorIPsDay[i].size() - 1);
    }

    // Imprimimos toda la información
    cout << endl << "-=-= Consulta " << numConsulta + 1 << " -=-=-=-=" << endl;
    //Se elige la opcion para imprecion previa a "creacion de consulta"
    int inicio = 0; //Primer dia al que vamos a imprimir
    int fin = 0; //Ultimo dia al que vamos a imprimir

    if(vectorIPsDay.size()>10){
      int op=0;
      cout<<"1 - Imprimir todo"<<endl;
      cout<<"2 - Imprimir los primeros 10 dias"<<endl;
      cout<<"3 - Imprimir los ultimos 10 dias"<<endl;
      cin >> op;
      
      if(op == 1){//Imprimir todo el arreglo
        inicio = 0;
        fin = vectorIPsDay.size();
      }else if(op == 2){ //Imprimir solo los primeros 10
        inicio = 0; 
        fin = 10;
      }else if(op == 3){ //Imprimir los ultimos 10
        inicio = vectorIPsDay.size() - 10;
        fin = vectorIPsDay.size();
      }
    }else{//Imprime todo el arreglo
      inicio = 0;
      fin = vectorIPsDay.size();
    }

    //Dependiendo de la opcion se imprimira el arreglo
    for(int i = inicio; i < fin; i++){
      for(int j = 0; j < vectorIPsDay[i].size(); j++){
      if(j == 0){
        cout << endl;
        cout << "Dia: " << vectorIPsDay[i][j].getDay()<< endl;
      }  
        cout << "IP: " << vectorIPsDay[i][j].getIP() << " Ocurrencia: " << vectorIPsDay[i][j].ocurrencia << endl;
      }
    }
 
    // Guarda un archivo .txt con los registros.
    cout << endl;
    cout << "Guardando los registros en el archivo: " << consulta << endl; 
    ofstream archivoTxt(consulta); //Abrimos el archivo
    for(int i=0; i < vectorIPsDay.size(); i++){
      for(int j=0; j < vectorIPsDay[i].size(); j++){
        //Guardamos información
        archivoTxt << "Dia: " << vectorIPsDay[i][j].getDay() << " - IP: " << vectorIPsDay[i][j].getIP() << " - Ocurrencia: " << vectorIPsDay[i][j].ocurrencia << endl; //<< " Ocurrencia: " << vectorIPsDay[i][j].ocurrencia + "\n";
      } 
    }  
    archivoTxt.close(); // Cerramos archivo
  }
}


//Funciones auxiliares ---
/**
 * Imprime por línea un archivo.
 * Complijidad computacinoal: O(n).
 * Esto es debido a que tenemos un ciclo iterativo while, que lee cada línea del archivo.
 * @param nombreArchivo Archivo que imprimimos en consola.
 */
void ImprimeArchivo(string nombreArchivo){
  ifstream archivo(nombreArchivo); //Abrimos archivo.
  string linea;
  //Leemos el archivo
  while (getline(archivo, linea)){
    cout << linea << endl; // Imprimos la línea.
  }
  archivo.close(); // Cerramos archivo.
}


int main(){
  int numConsultas = 0, opc=1;
  cout << "Leyendo archivo de registros, cargando..." << endl;
  vector<string> bitacora, temp;
  vector<vector<string>> fechasConsultas;

  // Leer archivo bitacora.txt y ordenarlo en un vector.
  bitacora = leerVectorizarArchivo("bitacora.txt");
  ordenaMerge(bitacora, 0, bitacora.size()-1);

  // La verdad no creo que vamos a ocupar el while, amenos que implementos un menú o algo.
  ImprimeArchivo("portada.txt");
  cout << endl << "Bienvenido a los registros de ingreso de Data TC :)" << endl;
  //Aqui pedimos el numero de consultas*******************************
  while(numConsultas == 0 || numConsultas > 10){ // Revisar que el usuario ingrese un número válido.
    cout << "Cuantas consultas va a realizar? [Ingrese un numero entero]" << endl << "-> ";
    cin >> numConsultas;
    if (numConsultas <= 0){
      cout << endl << "Por favor, un numero mayor que cero :)" << endl;
    } else if (numConsultas > 10){
      cout << endl << "Nada mas es permitido hacer hasta 9 consultas, gracias por su comprension :)" << endl;
    }
  }

  //Ciclo for para solicitar las fechas de la cantidad del numero de consultas   
  for(int i=1; i<numConsultas+1; i++){
    temp = consulta(i); // Guarda el rango de fechas.
    fechasConsultas.push_back(temp);
  }
  //Ciclo for para guardar e imprimir los datos (la cantidad del numero de consultas)
  for(int i=0; i<fechasConsultas.size(); i++){
    temp = fechasConsultas[i]; // temp = rango que consultar.
    guardaArchivo(temp, bitacora, i);
  }

  cout << endl << "Gracias por usar el programa, si quiere hacer otra consulta, reinicie el programa :)." << endl;
  return 0;
}