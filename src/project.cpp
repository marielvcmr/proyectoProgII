#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
    string isbn;
    int quantity;
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
    string title, author, isbn, quantityStr;
    
    fstream inBooksList;
    inBooksList.open("./assets/books.csv", ios::in);

    getline(inBooksList, bookData);
    int line = 0;

    while(!inBooksList.eof() && line < 98) {
        getline(inBooksList, bookData);
        stringstream s(bookData);
        getline(s, title, ',');
        getline(s, author, ',');
        getline(s, isbn, ',');
        getline(s, quantityStr, ',');


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
    cout<<"¡Bienvenido a la Biblioteca!";
    for (int i = 0; i<6; i++) {
        cout<<" "; 
    }
    cout<<" |"<<endl;         

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
    outUsersList << "nombre,apellido,cedula,clave,estatus,rol" << endl;
    for(int i = 0; i < 100 && usersList[i].username != ""; i++) {
        outUsersList << usersList[i].name << ',' << usersList[i].last_name << ',' 
                     << usersList[i].id << ',' << usersList[i].password << ',' 
                     << usersList[i].accState << ',' << usersList[i].role << endl;
    }
    outUsersList.close();
}

void saveBooks(book booksList[]) {
    ofstream outBooksList("./assets/books.csv", ios::out);
    outBooksList << "titulo,autor,isbn,cantidad" << endl;
    for(int i = 0; i < 100 && booksList[i].isbn != ""; i++) {
        outBooksList << booksList[i].title << ',' << booksList[i].author << ',' 
                     << booksList[i].isbn << ',' << booksList[i].quantity << endl;
    }
    outBooksList.close();
}

void addUser(user usersList[]) {
    for(int i = 0; i < 100; i++) {
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
    for(int i = 0; i < 100; i++) {
        if(usersList[i].username == username) {
            usersList[i].username = "";
            saveUsers(usersList);
            break;
        }
    }
}

void suspendUser(user usersList[]) {
    string username;
    cout << "Ingrese el nombre de usuario a suspender: ";
    cin >> username;
    for(int i = 0; i < 100; i++) {
        if(usersList[i].username == username) {
            usersList[i].accState = "suspendido";
            saveUsers(usersList);
            break;
        }
    }
}

void addBook(book booksList[]) {
    for(int i = 0; i < 100; i++) {
        if(booksList[i].isbn == "") {
            cout << "Ingrese titulo: ";
            cin.ignore();
            getline(cin, booksList[i].title);
            cout << "Ingrese autor: ";
            getline(cin, booksList[i].author);
            cout << "Ingrese ISBN: ";
            cin >> booksList[i].isbn;
            cout << "Ingrese cantidad: ";
            cin >> booksList[i].quantity;
            saveBooks(booksList);
            break;
        }
    }
}

void deleteBook(book booksList[]) {
    string isbn;
    cout << "Ingrese el ISBN del libro a eliminar: ";
    cin >> isbn;
    for(int i = 0; i < 100; i++) {
        if(booksList[i].isbn == isbn) {
            booksList[i].isbn = "";
            saveBooks(booksList);
            break;
        }
    }
}

void modifyBook(book booksList[]) {
    string isbn;
    cout << "Ingrese el ISBN del libro a modificar: ";
    cin >> isbn;
    for(int i = 0; i < 100; i++) {
        if(booksList[i].isbn == isbn) {
            cout << "Ingrese nuevo titulo: ";
            cin.ignore();
            getline(cin, booksList[i].title);
            cout << "Ingrese nuevo autor: ";
            getline(cin, booksList[i].author);
            cout << "Ingrese nueva cantidad: ";
            cin >> booksList[i].quantity;
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
            string isbn;
            cout << "Ingrese el ISBN del libro a comprar: ";
            cin >> isbn;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].isbn == isbn) {
                    if(booksList[i].quantity > 0) {
                        booksList[i].quantity--;
                        cout << "Libro comprado con éxito.\n";
                    } else {
                        cout << "No hay suficientes copias disponibles.\n";
                    }
                    saveBooks(booksList);
                    break;
                }
            }
        } else if(option == 2) {
            string isbn;
            cout << "Ingrese el ISBN del libro a retirar: ";
            cin >> isbn;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].isbn == isbn) {
                    if(booksList[i].quantity > 0) {
                        booksList[i].quantity--;
                        currentUser.accState = "suspendido";  // Simulación de no devolución
                        cout << "Libro retirado. Recuerde devolverlo a tiempo.\n";
                    } else {
                        cout << "No hay suficientes copias disponibles.\n";
                    }
                    saveBooks(booksList);
                    break;
                }
            }
        } else if(option == 3) {
            string isbn;
            cout << "Ingrese el ISBN del libro a devolver: ";
            cin >> isbn;
            for(int i = 0; i < 100; i++) {
                if(booksList[i].isbn == isbn) {
                    booksList[i].quantity++;
                    currentUser.accState = "activo";
                    cout << "Libro devuelto con éxito.\n";
                    saveBooks(booksList);
                    break;
                }
            }
        }
        
    } while(option != 4);

}

void employeeOptions(book booksList[]) {
    int option;
    do {
        cout << "Seleccione una opción: \n1. Agregar libro\n2. Eliminar libro\n3. Modificar libro\n4. Salir\n";
        cin >> option;
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
        cout << "Seleccione una opción: \n1. Agregar usuario\n2. Eliminar usuario\n3. Suspender usuario\n4. Agregar libro\n5. Eliminar libro\n6. Modificar libro\n7. Salir\n";
        cin >> option;
        if(option == 1) {
            addUser(usersList);
        } else if(option == 2) {
            deleteUser(usersList);
        } else if(option == 3) {
            suspendUser(usersList);
        } else if(option == 4) {
            addBook(booksList);
        } else if(option == 5) {
            deleteBook(booksList);
        } else if(option == 6) {
            modifyBook(booksList);
        }
    } while(option != 7);
}

int main() {
    user usersList[100] = {};
    book booksList[100] = {};
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
