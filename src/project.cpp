#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

struct user { 
    string name; 
    string last_name; 
    string id; 
    string username; 
    string password;
    string accState; 
    string role; 
}; 

struct book {
    string title;
    string author;
    int year;
    string genre;
    float rentprice;
    float purchaseprice;
    int code;
    string status;
    string yearStr = to_string(year);
    string rpriceStr = to_string(rentprice);
    string ppriceStr = to_string(purchaseprice);
    string codeStr = to_string(code);  
};


void arrayCreation(user usersList[]) {
    string usuarioDatos;
    string nombre, apellido, cedula, usuario, clave, estatus, rol;
    
    fstream inUsersList;
    inUsersList.open("./assets/dataProject.csv", ios::in);

    getline(inUsersList, usuarioDatos);
    int line = 0;

    while(!inUsersList.eof() && line < 98) {
        getline(inUsersList, usuarioDatos);
        stringstream s(usuarioDatos);
        getline(s, nombre, ',');
        getline(s, apellido, ',');
        getline(s, cedula, ',');
        getline(s, usuario, ',');
        getline(s, clave, ',');
        getline(s, estatus, ',');
        getline(s, rol, ',');

        usersList[line] = {nombre, apellido, cedula, usuario, clave, estatus, rol};
        line += 1;
    }

    inUsersList.close();
}

void arrayCreationBooks(book booksList[]) {
    string bookData;
    string title, author, year, genre, rprice, pprice, code, status;
    
    fstream inBooksList;
    inBooksList.open("./assets/books.csv", ios::in);

    getline(inBooksList, bookData); // Leer la cabecera
    int line = 0;

    while(getline(inBooksList, bookData) && line < 98) {
        stringstream s(bookData);
        getline(s, title, ',');
        getline(s, author, ',');
        getline(s, year, ',');
        getline(s, genre, ',');
        getline(s, rprice, ',');
        getline(s, pprice, ',');
        getline(s, code, ',');
        getline(s, status, ',');

        booksList[line] = {title, author, stoi(year), genre, stof(rprice), stof(pprice), stoi(code), status};
        line += 1;
    }

    inBooksList.close();
}

void signIn(string &inUsername, string &inPassword, int &userIndex, user usersList[]) {
    cout<<". ";
    for(int i = 0; i<40; i++) {
        cout<<"_"; 
    }
    cout<<" ."<<endl;         

    cout<<"| ";
    for (int i = 0; i<6; i++) {
        cout<<" "; 
    }
    cout<<"Bienvenido a la Biblioteca!";
    for (int i = 0; i<6; i++) {
        cout<<" "; 
    }
    cout<<"|"<<endl;         

    cout<<". ";
    for(int i = 0; i<40; i++) {
        cout<<"-"; 
    }
    cout<<" ."<<endl<<endl;    

    cout<<"Por favor, ingrese sus datos: "<<endl;
    cout<<"Nombre de usuario: ";
    cin>>inUsername; 
    cout<<endl<<"Clave: ";
    cin>>inPassword; 
    cout<<endl; 

    cout<<"Autenticando..."<<endl;
    userIndex = -1;
    int i = 0;
while(usersList[i].username != "") {
    if(inUsername == usersList[i].username && inPassword == usersList[i].password) {
        userIndex = i;
        break;
    } else {
        i += 1;
    }
}

    if(userIndex>=0) {
        cout<<"Hola, "<<usersList[userIndex].name<<"!\nAhora puedes disfrutar de todo lo que te ofrece la Biblioteca"<<endl;
    } else {
        cout<<"Sus datos son incorrectos"<<endl;
    }
    cout<<"____________________________________________"<<endl;
}

void saveUsers(user usersList[]) {
    ofstream outUsersList("./assets/dataProject.csv", ios::out);
    if (!outUsersList.is_open()) {
        cout << "No se pudo abrir el archivo para guardar los usuarios.\n";
        return;
    }

    outUsersList << "nombre,apellido,cedula,usuario,clave,estatus,rol" << endl;

    for(int i = 0; i < 200; i++) {
        if (!usersList[i].username.empty()) { // Verificar usuarios válidos
            outUsersList << usersList[i].name << ',' << usersList[i].last_name << ','
                         << usersList[i].id << ',' << usersList[i].username << ','
                         << usersList[i].password << ',' << usersList[i].accState << ','
                         << usersList[i].role << endl;
        }
    }

    outUsersList.close();
    cout << "Usuarios guardados correctamente.\n"; // Mensaje de confirmación
}

void saveBooks(book booksList[]) {
    ofstream outBooksList("./assets/books.csv", ios::out);
    outBooksList << "titulo,autor,año,genero,precio_renta,precio_compra,code,estado" << endl;

    for(int i = 0; i < 200; i++) {
        if (!booksList[i].title.empty()) {
            outBooksList << booksList[i].title << ',' << booksList[i].author << ','
                         << booksList[i].year << ','  << booksList[i].genre << ','
                         << booksList[i].rentprice << ',' << booksList[i].purchaseprice << ','
                         << booksList[i].code << ',' << booksList[i].status << endl;
        }
    }

    outBooksList.close();
}


void addUser(user usersList[]) {
    for(int i = 0; i < 200; i++) {
        if(usersList[i].username == "") {
            cout << "Ingrese nombre: ";
            cin >> usersList[i].name;
            cout << "Ingrese apellido: ";
            cin >> usersList[i].last_name;
            cout << "Ingrese cedula: ";
            cin >> usersList[i].id;
            cout << "Ingrese nombre de usuario: ";
            cin >> usersList[i].username;
            cout << "Ingrese clave: ";
            cin >> usersList[i].password;
            usersList[i].accState = "activo";
            cout << "Ingrese rol: ";
            cin >> usersList[i].role;
            saveUsers(usersList);
            break;
        }
    }
}

void deleteUser(user usersList[]) {
    string username;
    cout << "Ingrese el nombre de usuario a eliminar: ";
    cin >> username;
    bool userFound = false;
    
    for(int i = 0; i < 200; i++) {
        if(usersList[i].username == username) {
            usersList[i].username = ""; // Marca el usuario como eliminado
            userFound = true;
            break; // Rompe el ciclo después de encontrar y marcar el usuario
        }
    }
    
    if(userFound) {
        saveUsers(usersList); // Guarda la lista actualizada
        cout << "Usuario eliminado con exito.\n";
    } else {
        cout << "Usuario no encontrado.\n";
    }
}

void suspendUser(user usersList[]) {
    string username;
    cout << "Ingrese el nombre de usuario a suspender: ";
    cin >> username;

    for(int i = 0; i < 200; i++) {
        if(usersList[i].username == username) {
            usersList[i].accState = "suspendida"; // Actualizar solo el estado a suspendida
            break;
        }
    }

    saveUsers(usersList); // Guardar los cambios en el archivo
}

void activateUser(user usersList[]) {
    string username;
    cout << "Ingrese el nombre de usuario a reactivar: ";
    cin >> username;

    for(int i = 0; i < 200; i++) {
        if(usersList[i].username == username) {
            usersList[i].accState = "activa"; // Actualizar solo el estado a activa
            break;
        }
    }

    saveUsers(usersList); // Guardar los cambios en el archivo
}

void addBook(book booksList[]) {
    for(int i = 0; i < 200; i++) {
        if(booksList[i].codeStr == "") {
            cout << "Ingrese titulo: ";
            cin.ignore();
            getline(cin, booksList[i].title);
            cout << "Ingrese autor: ";
            getline(cin, booksList[i].author);
            cout << "Ingrese año: ";
            getline(cin, booksList[i].yearStr);
            cout << "Ingrese genero: ";
            getline(cin, booksList[i].genre);
            cout << "Ingrese precio de renta: ";
            getline(cin, booksList[i].rpriceStr);
            cout <<"Ingrese precio de compra: ";
            getline(cin, booksList[i].ppriceStr);
            cout <<"Ingrese el codigo del libro: ";
            getline(cin, booksList[i].codeStr);
            cout <<"Ingrese el estado del libro: ";
            getline(cin, booksList[i].status);
            booksList[i].code = stoi(booksList[i].codeStr);
            saveBooks(booksList);
            break;
        }
    }
}

void deleteBook(book booksList[]) {
    int code;
    cout << "Ingrese el codigo del libro a eliminar: ";
    cin >> code;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Limite de entrada
    for(int i = 0; i < 200; i++) {
        if(booksList[i].code == code) {
            booksList[i].codeStr = ""; //Marca el libro como eliminado
            saveBooks(booksList);
            break;
        }
    }
}

void modifyBook(book booksList[]) {
    int code;
    cout << "Ingrese el codigo del libro a modificar: ";
    cin >> code;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Limite de entrada

    for(int i = 0; i < 200; i++) {
        if(booksList[i].code == code) {
            string input;

            cout << "Ingrese nuevo titulo (deje en blanco para mantener " << booksList[i].title << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].title = input;
            }

            cout << "Ingrese nuevo autor (deje en blanco para mantener " << booksList[i].author << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].author = input;
            }

            cout << "Ingrese nuevo año (deje en blanco para mantener " << booksList[i].year << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].year = stoi(input);
            }

            cout << "Ingrese nuevo genero (deje en blanco para mantener " << booksList[i].genre << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].genre = input;
            }

            cout << "Ingrese nuevo precio de renta (deje en blanco para mantener " << booksList[i].rentprice << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].rentprice = stof(input);
            }

            cout << "Ingrese nuevo precio de compra (deje en blanco para mantener " << booksList[i].purchaseprice << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].purchaseprice = stof(input);
            }

            cout << "Ingrese nuevo estado del libro (deje en blanco para mantener " << booksList[i].status << "): ";
            getline(cin, input);
            if (!input.empty()) {
                booksList[i].status = input;
            }

            saveBooks(booksList);
            break;
        }
    }
}


void clientOptions(user &currentUser, book booksList[]) {
    int option;
    do {
        cout << "Seleccione una opcion: \n1. Comprar libro\n2. Retirar libro\n3. Devolver libro\n4. Salir\n";
        cin >> option;
        if(option == 1) {
            string code;
            cout << "Ingrese el codigo del libro a comprar: ";
            cin >> code;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].codeStr == code) {
                    if(booksList[i].status == "disponible") {
                        booksList[i].status = "no disponible";
                        cout << "Libro comprado con exito.\n";
                    } else {
                        cout << "El libro no esta disponible.\n";
                    }
                    saveBooks(booksList);
                    break;
                }
            }
        } else if(option == 2) {
            string code;
            cout << "Ingrese el codigo del libro a retirar: ";
            cin >> code;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].codeStr == code) {
                    if(booksList[i].status == "disponible") {
                        booksList[i].status = "no disponible";
                        cout << "Libro retirado. Recuerde devolverlo a tiempo.\n";
                    } else {
                        cout << "El libro no se encuentra disponible ahora mismo....\n";
                    }
                    saveBooks(booksList);
                    break;
                }
            }
        } else if(option == 3) {
            string code;
            cout << "Ingrese el codigo del libro a devolver: ";
            cin >> code;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].codeStr == code) {
                    if(booksList[i].status == "no disponible"){
                    booksList[i].status = "disponible";
                    cout << "Libro devuelto con éxito.\n";
                    saveBooks(booksList);
                    break;
                    }
                }
            }
        }
        
    } while(option != 4);

}

void employeeOptions(book booksList[]) {
    int option;
    do {
        cout << "Seleccione una opcion: \n1. Agregar libro\n2. Eliminar libro\n3. Modificar libro\n4. Salir\n";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(option == 1) {
            addBook(booksList);
        } else if(option == 2) {
            deleteBook(booksList);
        } else if(option == 3) {
            modifyBook(booksList);
        }
    } while(option != 4);
}

void adminOptions(user usersList[], book booksList[]) {
    int option;
    do {
        cout << "Seleccione una opcion: \n1. Agregar usuario\n2. Eliminar usuario\n3. Suspender usuario\n4. Reactivar usuario\n5. Agregar libro\n6. Eliminar libro\n7. Modificar libro\n8. Salir\n";
        cin >> option;
        if(option == 1) {
            addUser(usersList);
        } else if(option == 2) {
            deleteUser(usersList);
        } else if(option == 3) {
            suspendUser(usersList);
        } else if(option == 4) {
            activateUser(usersList);
        } else if(option == 5) {
            addBook(booksList);
        } else if(option == 6) {
            deleteBook(booksList);
        } else if(option == 7) {
            modifyBook(booksList);
        }
    } while(option != 8);
}

int main() {
    user usersList[200] = {};
    book booksList[200] = {};
    arrayCreation(usersList);
    arrayCreationBooks(booksList);

    string varUsuario; 
    string varClave; 
    int intentoError;
    int indiceUsuario = -1; 
    
    signIn(varUsuario, varClave, indiceUsuario, usersList);

    if(indiceUsuario == -1) {
        do {
            cout<<"¿Desea ingresar sus datos de nuevo?"<<endl;
            cout<<"Use 1 para indicar si, y 2 para indicar no: ";
            cin>>intentoError;
            switch (intentoError) { 
                case 1: 
                    signIn(varUsuario, varClave, indiceUsuario, usersList);
                    break;
                case 2: 
                    return -1;
                default: 
                    cout<<"Opcion invalida"<<endl;
            }
        } while(indiceUsuario == -1);
    }

    if(indiceUsuario != -1) {
    // Aquí se ejecutan las opciones según el rol del usuario
    if(usersList[indiceUsuario].role == "admin") {
        adminOptions(usersList, booksList);
    } else if(usersList[indiceUsuario].role == "empleado") {
        employeeOptions(booksList);
    } else if(usersList[indiceUsuario].role == "cliente") {
        clientOptions(usersList[indiceUsuario], booksList);
    }
} else {
    cout << "Autenticación fallida. Sus datos son incorrectos." << endl;
}

    return 0;
}
