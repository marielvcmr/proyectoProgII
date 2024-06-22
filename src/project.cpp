/*********************************Sistema Administrativo de una biblioteca**********************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 

struct user{    // Estructura que contiene los datos de un usuario existente de el sistema de la biblioteca
    string name; 
    string surname; 
    string id; 
    string username; 
    string password;
    string accState; 
    string role; 
}; 

void arrayCreation(user usersList[]){ 
    // arreglo existente, lo hace un arreglo que contenga los datos de los usuarios 
    string usuarioDatos;     // cadena que tiene los datos de un usuario en una linea 
    string nombre;
    string apellido; 
    string cedula; 
    string clave; 
    string estatus; 
    string rol; 
    
    fstream inUsersList;   // creacion del filehand
    inUsersList.open("C:/Users/maria/OneDrive/Desktop/projectP2/assets/dataProject.csv", ios:: in);     // abrimos el file

    if(!inUsersList.is_open()){
        cout<<"No se encontro el archivo solicitado"<<endl;
    }

    getline(inUsersList, usuarioDatos);   // leemos la primera linea, que tiene los caracteristicas de los datos de la estructura
    int line = 0;    // indice del nro de linea de datos a ingresar en el arreglo

    while(!inUsersList.eof() && line<98 ){
        getline(inUsersList, usuarioDatos);   // del archivo inUsersList tomo una linea para usuarioDatos
        stringstream s(usuarioDatos);     
        getline(s, nombre, ',');
        getline(s, apellido, ',');
        getline(s, cedula, ',');
        getline(s, clave, ',');
        getline(s, estatus, ',');
        getline(s, rol, ',');

        usersList[line] = {nombre, apellido, cedula, clave, estatus, rol};
        line += 1;
       
    }

    inUsersList.close();   
}


void signIn(string inUsername, string inPassword, int& userIndex, user usersList[]){

    // Mensaje de bienvenida 
    cout<<". ";
    for(int i = 0; i<40; i ++){
        cout<<"_"; 
    }
    cout<<" ."<<endl;          // cabecera

    cout<<"| ";
    for (int i = 0; i<6; i++){
        cout<<" "; 
    }
    cout<<"¡Bienvenido a la Biblioteca!";
    for (int i = 0; i<6; i++){
        cout<<" "; 
    }
    cout<<" |"<<endl;         // texto del mensaje

    cout<<". ";
    for(int i = 0; i<40; i ++){
        cout<<"-"; 
    }
    cout<<" ."<<endl<<endl;    // parte inferior de la caja del  mensaje 
    

    // Ingreso de los datos de un usuario 
    cout<<"Por favor, ingrese sus datos: "<<endl;
    cout<<"Nombre de usuario: ";
    cin>>inUsername; 
    cout<<endl<<"Clave: ";
    cin>>inPassword; 
    cout<<endl; 


    /*Autenticar si los datos de esos usuarios verdaderamente estan en el libro
    con la informacion acerca de todos los usuarios registrados*/
    cout<<"Autenticando..."<<endl;
    userIndex = -1;
    int i = 0; 
    while(usersList[i].username != ""){

        if(inUsername == usersList[i].username){
            if(inPassword == usersList[i].password){
                userIndex = i;
                break;
            }else{
                i += 1;
            }
        }else{
            i += 1;
        }
    }
    // Dependiendo de si el index anterior es mayor a -1 o es -1, sabemos si los datos anteriores se autenticaron o no
    if(userIndex>=0){
        cout<<"Hola, "<<usersList[userIndex].name<<"!"<<endl;

        if(usersList[userIndex].accState == "suspendida"){
            cout<<"Lo sentimos, esta cuenta esta suspendida."<<endl;
            userIndex = -1;
        }else{
            cout<<"Ahora puedes disfrutar de todo lo que te ofrece la Biblioteca"<<endl;
        }
    }
    else{
        cout<<"Sus datos son incorrectos"<<endl;
    }
    cout<<"____________________________________________"<<endl;
}


int main(){

    // Arreglo para trabajar durante el programa
    user usersList[100];
    arrayCreation(usersList); 

    //for (int i = 0;i <100; i++){                      /*this was just to verify that arrayCreation worked as it was*/
        //cout<<usersList[i].name<<", "<<usersList[i].surname<<endl;          /*supposed to work in the program*/
    //}   // Now that we know that it works we can continue the program having the array done by starting with the login

    // SignIn 
    string varUsuario; 
    string varClave; 
    int intentoError;
    int indiceUsuario = -1; 
    
    signIn(varUsuario, varClave, indiceUsuario, usersList);

    if(indiceUsuario == -1){   // datos invalidos o cuenta suspendida

        do{         // ciclo para ingresar datos de nuevo o no
            cout<<"¿Desea ingresar nuevos datos?"<<endl;
            cout<<"Use 1 para indicar si, y 2 para indicar no: ";
            cin>>intentoError;
            switch (intentoError){ 
                case 1: 
                    signIn(varUsuario, varClave, indiceUsuario, usersList);
                    break;
                case 2: 
                    return -1;
                default: 
                    cout<<"Opcion invalida"<<endl;
            }
        }while(indiceUsuario == -1);
    } // final del  signIn 


    // A partir del indice anterior, ver tipo de usuario y estado de cuenta, y presentar opciones
    /*code*/


    
}