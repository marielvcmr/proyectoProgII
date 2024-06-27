#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

struct user
{
    string name;
    string last_name;
    string id;
    string username;
    string password;
    string accState;
    string role;
    float balance; // Nuevo campo de saldo
    string balanceStr = to_string(balance);
};

struct book
{
    string title;
    string author;
    int year;
    string genre;
    float rentprice;
    float purchaseprice;
    int code;
    string status;
    string rentedBy; // Nuevo campo que indica el usuario que ha retirado el libro
    string yearStr = to_string(year);
    string rpriceStr = to_string(rentprice);
    string ppriceStr = to_string(purchaseprice);
    string codeStr = to_string(code);
};

void arrayCreation(user usersList[])
{
    string usuarioDatos;
    string nombre, apellido, cedula, usuario, clave, estatus, rol, balance;

    fstream inUsersList;
    inUsersList.open("./assets/dataProject.csv", ios::in);

    getline(inUsersList, usuarioDatos); // Leer la cabecera
    int line = 0;

    while (getline(inUsersList, usuarioDatos) && line<200)
    {
        stringstream s(usuarioDatos);
        getline(s, nombre, ',');
        getline(s, apellido, ',');
        getline(s, cedula, ',');
        getline(s, usuario, ',');
        getline(s, clave, ',');
        getline(s, estatus, ',');
        getline(s, rol, ',');
        getline(s, balance, ',');

        float saldoUsuario = 0.0; // Valor predeterminado en caso de error
        try
        {
            saldoUsuario = stof(balance);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Error al convertir balance a float: " << e.what() << endl;
            // Manejo del error, como asignar un valor predeterminado o registrar el problema
        }

        usersList[line] = {nombre, apellido, cedula, usuario, clave, estatus, rol, saldoUsuario};
        line += 1;
    }

    inUsersList.close();
}

void arrayCreationBooks(book booksList[])
{
    string bookData;
    string title, author, year, genre, rprice, pprice, code, status, rentedBy;

    fstream inBooksList;
    inBooksList.open("./assets/books.csv", ios::in);

    getline(inBooksList, bookData); // Leer la cabecera
    int line = 0;

    while (getline(inBooksList, bookData) && line<200)
    {
        stringstream s(bookData);
        getline(s, title, ',');
        getline(s, author, ',');
        getline(s, year, ',');
        getline(s, genre, ',');
        getline(s, rprice, ',');
        getline(s, pprice, ',');
        getline(s, code, ',');
        getline(s, status, ',');
        getline(s, rentedBy, ',');

        booksList[line] = {title, author, stoi(year), genre, stof(rprice), stof(pprice), stoi(code), status, rentedBy};
        line += 1;
    }

    inBooksList.close();
}

void signIn(string inUsername, string inPassword, int& userIndex, user usersList[])
{  //Mensaje de bienvenida
    cout << ". ";
    for (int i = 0; i < 40; i++)
    {
        cout << "_";
    }
    cout << " ." << endl;

    cout << "| ";
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    cout << "Bienvenido a la Biblioteca!";
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    cout << "  |" << endl;

    cout << ". ";
    for (int i = 0; i < 40; i++)
    {
        cout << "-";
    }
    cout << " ." << endl
         << endl;
    //Ingreso de datos
    cout << "Por favor, ingrese sus datos: " << endl;
    cout << "Nombre de usuario: ";
    cin >> inUsername;
    cout << endl
         << "Clave: ";
    cin >> inPassword;
    cout << endl;

    cout << "Autenticando..." << endl;
    userIndex = -1;
    int i = 0;
    while (usersList[i].username != "")
    {
        if (inUsername == usersList[i].username && inPassword == usersList[i].password)
        {
            userIndex = i;
            break;
        }
        else
        {
            i += 1;
        }
    }

    if (userIndex >= 0)
    {
        cout << "Hola, " << usersList[userIndex].name << "!" << endl;
        if(usersList[userIndex].accState == "suspendida")
        {
            cout<<"Lo sentimos, esta cuenta esta suspendida."<<endl;
            userIndex = -1;
        }
        else
        {
            cout<<"Ahora puedes disfrutar de todo lo que te ofrece la Biblioteca"<<endl;
            cout<<"Tipo de usuario: "<<usersList[userIndex].role<<endl;
        }
    }
    else
    {
        cout << "Sus datos son incorrectos" << endl;
    }
    cout << "____________________________________________" << endl;
}

void saveUsers(user usersList[]) // Guarda un arreglo de usuarios en el archivo
{
    ofstream outUsersList("./assets/dataProject.csv", ios::out);

    if (!outUsersList.is_open())
    {
        cout << "No se pudo abrir el archivo para guardar los usuarios.\n";
        return;
    }

    outUsersList << "name,last_name,id,username,password,accState,role,balance\n";

    for (int i = 0; i < 200; ++i)
    {
        if (usersList[i].username != "") // Guardar solo usuarios válidos
        {
            outUsersList << usersList[i].name << ',' << usersList[i].last_name << ','
                         << usersList[i].id << ',' << usersList[i].username << ','
                         << usersList[i].password << ',' << usersList[i].accState << ','
                         << usersList[i].role << ',' << usersList[i].balance << '\n';
        }
    }

    outUsersList.close();
    cout << "Usuarios guardados correctamente.\n";
}

void saveBooks(book booksList[]) { //Guarda un arreglo de libros en el archivo
    ofstream outBooksList("./assets/books.csv", ios::out);

    if (!outBooksList.is_open()) {
        cout << "No se pudo abrir el archivo para guardar los libros.\n";
        return;
    }

    outBooksList << "titulo,autor,año,genero,precio_renta,precio_compra,code,estado,rentedBy\n";

    for (int i = 0; i < 200; ++i) {
        if (!booksList[i].title.empty()) { // Guardar solo libros válidos
            outBooksList << booksList[i].title << ',' << booksList[i].author << ','
                         << booksList[i].year << ',' << booksList[i].genre << ','
                         << booksList[i].rentprice << ',' << booksList[i].purchaseprice << ','
                         << booksList[i].code << ',' << booksList[i].status << ','
                         << booksList[i].rentedBy << '\n';
        }
    }

    outBooksList.close();
    cout << "Libros guardados correctamente.\n";
}
void addUser(user usersList[])  // registro de un nuevo usuario
{
    for (int i = 0; i < 200; i++)
    {
        if (usersList[i].username == "")
        {
            cout << "Ingrese el nombre del nuevo usuario: ";
            cin >> usersList[i].name;
            cout << "Ingrese el apellido del nuevo usuario: ";
            cin >> usersList[i].last_name;
            cout << "Ingrese la cedula del nuevo usuario: ";
            cin >> usersList[i].id;
            cout << "Ingrese el nombre de usuario para esta cuenta: ";
            cin >> usersList[i].username;
            cout << "Ingrese la clave a utilizar por esta cuenta: ";
            cin >> usersList[i].password;
            usersList[i].accState = "activo";
            cout << "Ingrese el tipo de usuario a ser registrado: ";
            cin >> usersList[i].role;
            cout << "Ingrese saldo del usuario: ";
            cin >> usersList[i].balance;
            saveUsers(usersList);
            break;
        }
    }
}

void deleteUser(user usersList[])
{
    string username;
    cout << "Ingrese el nombre de usuario a eliminar: ";
    cin >> username;
    bool userFound = false;

    for (int i = 0; i < 200; i++)
    {
        if (usersList[i].username == username)
        {
            usersList[i].username = ""; // Marca el usuario como eliminado
            userFound = true;
            break; // Rompe el ciclo después de encontrar y marcar el usuario
        }
    }

    if (userFound)
    {
        saveUsers(usersList); // Guarda la lista actualizada en el archivo
        cout << "Usuario eliminado con exito.\n";
    }
    else
    {
        cout << "Usuario no encontrado.\n";
    }
    arrayCreation(usersList); // actualiza el arreglo para no tener como elemento el usuario eliminado
}

void suspendUser(user usersList[])
{
    string username;
    cout << "Ingrese el nombre de usuario a suspender: ";
    cin >> username;

    for (int i = 0; i < 200; i++)
    {
        if (usersList[i].username == username)
        {
            usersList[i].accState = "suspendida"; // Actualizar solo el estado a suspendida
            break;
        }
    }

    saveUsers(usersList); // Guardar los cambios en el archivo
}

void activateUser(user usersList[])
{
    string username;
    cout << "Ingrese el nombre de usuario a reactivar: ";
    cin >> username;

    for (int i = 0; i < 200; i++)
    {
        if (usersList[i].username == username)
        {
            usersList[i].accState = "activa"; // Actualizar solo el estado a activa
            break;
        }
    }

    saveUsers(usersList); // Guardar los cambios en el archivo
}

void changeBalance(user usersList[])
{
    string username;
    float newBalance;
    cout << "Ingrese el nombre de usuario del usuario cuyo saldo desea cambiar: ";
    cin >> username;

    bool userFound = false;
    for (int i = 0; i < 200; i++)
    {
        if (usersList[i].username == username)
        {
            userFound = true;
            cout << "El saldo actual de " << username << " es: " << usersList[i].balance << endl;
            cout << "Ingrese el nuevo saldo: ";
            cin >> newBalance;
            usersList[i].balance = newBalance;
            saveUsers(usersList); // Guardar los cambios en el archivo
            cout << "Se ha cambiado el saldo de " << username << " correctamente.\n";
            break;
        }
    }

    if (!userFound)
    {
        cout << "Usuario no encontrado.\n";
    }
}

void addBook(book booksList[]) {
    for (int i = 0; i < 200; i++) {
        if (booksList[i].code == 0) {
            cout << "Ingrese el título del nuevo libro: ";
            getline(cin, booksList[i].title);
            cout << "Ingrese el autor del nuevo libro: ";
            getline(cin, booksList[i].author);
            cout << "Ingrese el año de publicación del nuevo libro: ";
            cin >> booksList[i].year;
            cout << "Ingrese el género del nuevo libro: ";
            cin.ignore();
            getline(cin, booksList[i].genre);
            cout << "Ingrese el precio de renta del nuevo libro: ";
            cin >> booksList[i].rentprice;
            cout << "Ingrese el precio de compra del nuevo libro: ";
            cin >> booksList[i].purchaseprice;
            cout << "Ingrese el código del nuevo libro: ";
            cin >> booksList[i].code;
            booksList[i].status = "disponible";
            booksList[i].rentedBy = "";

            saveBooks(booksList);
            break;
        }
    }
}

void deleteBook(book booksList[]) {
    int code;
    cout << "Ingrese el código del libro a eliminar: ";
    cin >> code;

    for (int i = 0; i < 200; ++i) {
        if (booksList[i].code == code) {
            booksList[i] = {}; // Reiniciar la estructura
            saveBooks(booksList);
            cout << "Libro eliminado correctamente.\n";
            return;
        }
    }

    cout << "Libro no encontrado.\n";
}

void modifyBook(book booksList[]) {
    int code;
    cout << "Ingrese el codigo del libro a modificar: ";
    cin >> code;
    cin.ignore(); // Limpiar el buffer de entrada

    for (int i = 0; i < 200; i++) {
        if (booksList[i].code == code) {
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

            // Actualizar las variables de cadena
            booksList[i].yearStr = to_string(booksList[i].year);
            booksList[i].rpriceStr = to_string(booksList[i].rentprice);
            booksList[i].ppriceStr = to_string(booksList[i].purchaseprice);
            booksList[i].codeStr = to_string(booksList[i].code);

            saveBooks(booksList);
            break;
        }
    }
}


void buy_book(user &currentUser, book booksList[], user usersList[]){

    string code;
    cout << "Ingrese el codigo del libro a comprar: ";
    cin >> code;
    for (int i = 0; i < 200; i++)
    {
        if (booksList[i].codeStr == code)
        {
            if (booksList[i].status == "disponible")
            {
                if (currentUser.balance >= booksList[i].purchaseprice)
                {
                    currentUser.balance -= booksList[i].purchaseprice;
                    booksList[i].status = "no disponible - VENDIDO";
                    booksList[i].codeStr = ""; // Marca el libro como eliminado
                    cout << "Libro comprado exitosamente.\n";
                    saveBooks(booksList); // Guarda los cambios en books.csv
                    arrayCreationBooks(booksList); //Guarda los cambios en el arreglo de libros
                    saveUsers(usersList); // Guarda los cambios en dataProject.csv
                }
                else
                {
                    cout << "Saldo insuficiente para comprar el libro.\n";
                }
            }
            else
            {
            cout << "El libro no está disponible para la compra.\n";
            }
            break;
        }
    }
        
}

void withdraw_book(user &currentUser, book booksList[], user usersList[])
{
    string code;
    cout << "Ingrese el codigo del libro a retirar: ";
    cin >> code;
    for (int i = 0; i < 200; i++)
    {
        if (booksList[i].codeStr == code)
        {
            if (booksList[i].status == "disponible")
            {
                if (currentUser.balance >= booksList[i].rentprice)
                {
                    currentUser.balance -= booksList[i].rentprice;
                    booksList[i].status = "no disponible";
                    booksList[i].rentedBy = currentUser.id;
                    cout << "Libro retirado. Recuerde devolverlo a tiempo.\n";
                    saveBooks(booksList); // Guarda los cambios en books.csv
                    saveUsers(usersList); // Guarda los cambios en dataProject.csv
                }
                else
                {
                    cout << "Saldo insuficiente para retirar el libro.\n";
                }
            }
            else
            {
                cout << "El libro no se encuentra disponible ahora mismo.\n";
            }
            break;
        }
    }
}

void returnBook(user &currentUser, book booksList[], user usersList[])
{
    string code;
    cout << "Ingrese el codigo del libro a devolver: ";
    cin >> code;
    for (int i = 0; i < 200; i++)
    {
        if (booksList[i].codeStr == code)
        {
            if (booksList[i].status == "no disponible" && booksList[i].rentedBy == currentUser.id)
            {
                booksList[i].status = "disponible";
                booksList[i].rentedBy = "";
                cout << "Libro devuelto con éxito.\n";
                saveBooks(booksList);
                break;
            }
            else
            {
                cout << "No puede devolver este libro.\n";
            }
        }
    }
}

void clientOptions(user &currentUser, book booksList[], user usersList[])
{
    int option;
    do
    {  
        cout<<"Seleccione una opcion: \n1. Comprar libro\n2. Retirar libro\n3. Devolver libros\n4. Salir\n";
        cin>>option;
        if(option == 1){
            buy_book(currentUser, booksList, usersList);
        }
        else if (option == 2)
        {
            withdraw_book(currentUser, booksList, usersList);
        }
        else if (option == 3)
        {
            returnBook(currentUser, booksList, usersList);
        }
        cout<<endl;
    } 
    while (option != 4);
}

void employeeOptions(user &currentUser, book booksList[], user usersList[])
{
    int option;
    do
    {
        cout << "Seleccione una opcion: \n1. Agregar libro\n2. Eliminar libro\n3. Modificar libro\n4. Comprar libro\n5. Retirar libro\n6. Devolver libro\n7. Salir\n";
        cin >> option;
        cin.ignore();
        if (option == 1)
        {
            addBook(booksList);
        }
        else if (option == 2)
        {
            deleteBook(booksList);
        }
        else if (option == 3)
        {
            modifyBook(booksList);
        }
        else if(option == 4)
        {
            buy_book(currentUser, booksList, usersList);
        }
        else if (option == 5)
        {
            withdraw_book(currentUser, booksList, usersList);
        }
        else if (option == 6)
        {
            returnBook(currentUser, booksList, usersList);

        }
    } while (option != 7);
}

void adminOptions(user &currentUser, book booksList[], user usersList[])
{
    int option;
    do
    {
        cout << "Seleccione una opcion: \n1. Agregar nuevo usuario\n2. Eliminar usuario\n3. Suspender usuario\n4. Reactivar usuario\n5. Agregar libro\n6. Eliminar libro\n7. Modificar libro\n8. Comprar un libro\n9. Retirar un libro\n10. Devolver un libro\n11. Cambiar saldo de usuario\n12. Salir\n";
        cin >> option;
        cin.ignore();
        if (option == 1)
        {
            addUser(usersList);
        }
        else if (option == 2)
        {
            deleteUser(usersList);
        }
        else if (option == 3)
        {
            suspendUser(usersList);
        }
        else if (option == 4)
        {
            activateUser(usersList);
        }
        else if (option == 5)
        {
            addBook(booksList);
        }
        else if (option == 6)
        {
            deleteBook(booksList);
        }
        else if (option == 7)
        {
            modifyBook(booksList);
        }
        else if (option == 8)
        {
            buy_book(currentUser, booksList, usersList);
        }
        else if(option == 9)
        {
            withdraw_book(currentUser, booksList, usersList);
        }
        else if(option == 10)
        {
            returnBook(currentUser, booksList, usersList);
        }
        else if(option == 11)
        {
            changeBalance(usersList);
        }

    } while (option != 12);
}

int main()
{
    user usersList[200];
    book booksList[200] ;
    arrayCreation(usersList);
    arrayCreationBooks(booksList);

    string varUsuario;
    string varClave;
    int intentoError;
    int indiceUsuario = -1;

    signIn(varUsuario, varClave, indiceUsuario, usersList);

    if (indiceUsuario == -1)  // datos invalidos o cuenta suspendida
    {
        do
        {      // ciclo para ingresar datos de nuevo o no
            cout << "¿Desea ingresar sus datos de nuevo?" << endl;
            cout << "Use 1 para indicar si, y 2 para indicar no: ";
            cin >> intentoError;
            switch (intentoError)
            {
            case 1:
                signIn(varUsuario, varClave, indiceUsuario, usersList);
                break;
            case 2:
                return -1;
            default:
                cout << "Opcion invalida" << endl;
            }
        } while (indiceUsuario == -1);
    }

    if (indiceUsuario != -1)
    {
        // Aquí se ejecutan las opciones según el rol del usuario
        if (usersList[indiceUsuario].role == "administrador")
        {
            adminOptions(usersList[indiceUsuario], booksList, usersList);
        }
        else if (usersList[indiceUsuario].role == "empleado")
        {
            employeeOptions(usersList[indiceUsuario], booksList, usersList);
        }
        else if (usersList[indiceUsuario].role == "cliente")
        {
            clientOptions(usersList[indiceUsuario], booksList, usersList);
        }
    }
    

}
