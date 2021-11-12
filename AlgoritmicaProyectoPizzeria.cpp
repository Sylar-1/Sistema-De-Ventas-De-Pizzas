/*  CONTRASEÑA DE ADMINISTRADOR "7516".
********************************************
*
*	Descripción del programa :
*	Tenemos un programa que se encarga de registrar en el inventario, pizzas con su nombre, codigo, la cantidad que se tiene,
*	el precio unitario, tambien operaciones como mostrar, borrar, borrar todo; todo eso en el menu de administrador.
*	Tambien tenemos una opcion para vender pizzas, que se encarga de mostrar las pizzas disponibles , el codigo, el nombre,
*   la cantidad, el precio unitario; otra opcion para vender, el usuario escoge la pizza que desea comprar mediante su codigo
*   de la pizza, conforme se van comprando pizza tras pizza, la cantidad va disminuyendo.
*	Incluimos un sistema de seguridad para que en la opcion administrador solo personal autorizado pueda modificar el archivo
*/
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<ctime>     // fecha y hora del sistema
#include<vector>
#include<locale.h>  // librería para mostrar la ñ y vocales acentuadas
#include<string.h>	// funciones de cadena
#include<iomanip>	// setw()

using namespace std;

FILE *P;

struct productos{
	int cod;
	char nombre[20];
	int cantidad;
	float precio;
}pizza;

void raya1();
void menu();
void fechaActual();
void administrador();
void comprador();
void ingresarPizzas();
void mostrarPizzas();
void borrarPizzas();
void borrarTodo();
void venderPizzas();



int main(){
	menu();
	system("pause");
	return(0);
}

void menu(){
	int op;

	setlocale(LC_ALL,"spanish");  // letra ñ y vocales acentuadas
	system("color c0");
	fechaActual();

	do{
	system("cls");
	cout<<"\n\t\t\t*********************************\n";
	cout<<"\t\t\t        PIZZAS RAULLLLLLL  \n";
	cout<<"\t\t\t*********************************\n";
	cout<<"\t\t\t[1] : Administrador\n";
	cout<<"\t\t\t[2] : Comprador\n";
	cout<<"\t\t\t[3] : Salir\n";
	cout<<"\n\t\t\tIngrese una opción: ";
	cin>>op;

	switch(op){
		case 1: administrador();break;
		case 2: comprador();break;
	}

	}while(op!=3);
	system("cls");
	cout<<"Hasta luego...\n";
}

void fechaActual(){
   time_t now=time(0);
   tm *time=localtime(&now);
   vector<string> dia_semana;
   dia_semana.push_back("Domingo");
   dia_semana.push_back("Lunes");
   dia_semana.push_back("Martes");
   dia_semana.push_back("Miercoles");
   dia_semana.push_back("Jueves");
   dia_semana.push_back("Viernes");
   dia_semana.push_back("Sabado");

   vector<string> mes;
   mes.push_back("Enero");
   mes.push_back("Febrero");
   mes.push_back("Marzo");
   mes.push_back("Abril");
   mes.push_back("Mayo");
   mes.push_back("Junio");
   mes.push_back("Julio");
   mes.push_back("Agosto");
   mes.push_back("Setiembre");
   mes.push_back("Octubre");
   mes.push_back("Noviembre");
   mes.push_back("Diciembre");

   int year=1900+time->tm_year;

   cout<<dia_semana[time->tm_wday]<<" ";
   cout<<time->tm_mday<<" de "<<mes[time->tm_mon]<<" del "<<year<<endl;
   cout<<time->tm_hour<<":"<<time->tm_min<<":"<<time->tm_sec<<endl;
   cout<<"-------------------------------------------------------\n";
}

void administrador(){
	int contra; // contraseña -> 7516
	int op;

	do{
		system("cls");
		cout<<"Ingrese la contraseña: ";
		cin>>contra;
		if(contra!=7516){
		puts("Contraseña incorrecta...\n");
		system("pause");
		}
	}while(contra!=7516);

	do{
	system("cls");
	fechaActual();
	cout<<"\t\t\t***************************************\n";
	cout<<"\t\t\t      MENU DE ADMINISTRADOR\n";
	cout<<"\t\t\t***************************************\n";
	cout<<"\t\t\t[1] : Ingresar pizzas\n";
	cout<<"\t\t\t[2] : Mostrar pizzas\n";
	cout<<"\t\t\t[3] : Borrar pizzaa\n";
	cout<<"\t\t\t[4] : Borrar todo\n";
	cout<<"\t\t\t[5] : Regresar\n";
	cout<<"\n\t\t\tIngrese una opción: ";
	cin>>op;

	switch(op){
		case 1: ingresarPizzas();break;
		case 2: mostrarPizzas();break;
		case 3: borrarPizzas();break;
		case 4: borrarTodo();break;
	}

	}while(op!=5);
}

void ingresarPizzas(){
	int codigo;
	system("cls");
	P = fopen("pizzas.txt", "ab+");
	if( P == NULL ) {
		cout << "\n\t*~----------Error a la hora de crear/abrir el archivo----------~*\n";
		getch();
		exit(1);
	}
	cout << "\n\tIngrese los datos de la pizza:\n";

	do{
		cout<<"\t\tCodigo de la pizza: ";
		cin>>codigo;
	}while(codigo <= 0);
	while(!feof(P)) {
		fread(&pizza,sizeof(pizza),1,P);
		if(pizza.cod == codigo) {
			cout<<"\n\t*~----------Codigo de la pizza ya registrada----------~*\n";
			fclose(P);
			getch();
			return;
		}
	}
	pizza.cod = codigo;

	getc(stdin); // limpieza de buffer
	cout<<"\n\t\tNombre de la pizza: "; gets(pizza.nombre);
	strupr(pizza.nombre);

	do{
		cout<<"\t\tUnidades: ";
		cin>>pizza.cantidad;
	}while(pizza.cantidad <= 0);

	do{
		cout<<"\t\tPrecio de la pizza (S/.): ";
		cin>>pizza.precio;
	}while(pizza.precio <= 0);

	fwrite(&pizza,sizeof(pizza),1,P);
	fclose(P);
	system("cls");
}

void mostrarPizzas(){
	system("cls");
	P = fopen("pizzas.txt","r+");
	if(P == NULL){
		cout << "\n\t*----------Archivo inexistente----------*\n";
		system("pause");
		return;
	}
	fechaActual();
	cout<<"\n\t\t\t********************************\n";
	cout<<"\t\t\t        P.I.Z.Z.A.S             \n";
	cout<<"\t\t\t********************************\n\n";
	fread(&pizza,sizeof(pizza),1,P);
	raya1();
	cout<<"\t\t"<<setw(6)<<"CODIGO"<<setw(15)<<"NOMBRE"<<setw(15)<<"UNIDADES"<<setw(15)<<"PRECIO(S/)"<<endl;
	raya1();

	while(!feof(P)){
		if(pizza.cod != 0){
			cout<<"\t\t"<<setw(6)<<pizza.cod<<setw(15)<<pizza.nombre<<setw(15)<<pizza.cantidad<<setw(15)<<pizza.precio<<endl;
		}
		fread(&pizza,sizeof(pizza),1,P);
	}
	cout << endl;
	fclose(P);
    system("pause");
    return;
}

void borrarPizzas(){
	system("cls");
	P = fopen("pizzas.txt", "r+");
	if(P == NULL){
		cout << "\n\t*~----------Archivo inexistente----------~*\n";
		system("pause");
		return;
	}

	int code;
	cout<<"\n\tIngrese el codigo de la pizza que desea eliminar: "; cin>>code;
	char seguro;
	while(!feof(P)){
		fread( &pizza, sizeof(pizza),1,P);
		if(pizza.cod == code) {
			raya1();
			cout<<"\n\t\tCodigo de la pizza          : "<<pizza.cod;
			cout<<"\n\t\tNombre de la pizza          : "<<pizza.nombre;
			cout<<"\n\t\tUnidades de esta pizza      : "<<pizza.cantidad;
			cout<<"\n\t\tPrecio unitario de la pizza : "<<pizza.precio;
			raya1();
			pizza.cod = 0;
			strcpy(pizza.nombre, "");
			pizza.cantidad = 0;
			pizza.precio = 0;
			do{
				cout<<"\n\n\nSeguro que quiere eliminar esta pizza? (S/N) ---> ";
				cin>>seguro;
				seguro = toupper(seguro);
			}while( seguro != 'S' && seguro != 'N' );
			if( seguro == 'S' ) {
				fseek(P,ftell(P) - sizeof(pizza), SEEK_SET );
				fwrite( &pizza,sizeof(pizza),1,P);
				cout << "\n\n*~----------Pizza borrada----------~*\n";
			}
			fclose(P);
			system("pause");
			return;
		}
	}
	cout << "\n\t*~----------Codigo de pizza no encontrada----------~*\n";
	fclose(P);
	system("pause");
}

void borrarTodo(){
	system("cls");
	char s;
	do{
		cout<<"\n\tSeguro que quiere eliminar el archivo? (S/N) ---> ";
		cin>>s;
		s = toupper(s);
	}while(s != 'S' && s != 'N');
	if(s == 'S'){
		remove("pizzas.txt");
		system("cls");
		cout<<"Archivo eliminado\n";
	}
	system("pause");
}

void comprador(){
	int op;
	do{
	system("cls");
	cout<<"\t\t\t***************************************\n";
	cout<<"\t\t\t      MENU DE COMPRADOR\n";
	cout<<"\t\t\t***************************************\n";
	cout<<"\t\t\t[1] : Ver pizzas\n";
	cout<<"\t\t\t[2] : Vender pizzas\n";
	cout<<"\t\t\t[3] : Regresar\n";
	cout<<"\n\t\t\tIngrese una opción: ";
	cin>>op;

	switch(op){
		case 1: mostrarPizzas();break;
		case 2: venderPizzas();break;
	}
	}while(op!=3);
}

void venderPizzas(){
	system("cls");
	P = fopen("pizzas.txt","r+");
	if(P == NULL){
		cout<<"\n\t----------Archivo inexistente----------\n";
		system("pause");
		return;
	}
	int code;
	cout<<"Ingrese el codigo de la pizza: ";
	cin>>code;
	char s;
	while(!feof(P)){
		fread( &pizza, sizeof(pizza),1,P);
		if(pizza.cod == code){
			cout << "\n----------------------------------------";
			//cout << "\nCodigo del partido        :"<< Partidos_CM.codigo_partido;
			//cout << "\nNombre del estadio        : "<< Partidos_CM.nombre_estadio;
			cout << "\nNombre de la pizza              : "<<pizza.nombre;
			cout << "\nCantidad disponible             : "<<pizza.cantidad;
			cout << "\nPrecio unitaria de la pizza (S/): "<<pizza.precio;
			if( pizza.cantidad == 0 ) {
				cout << "\n\nYa no quedan más pizzas\n";
				fclose(P);
				getch();
				return;
			}
			do{
				cout<<"\n\nSeguro que desea comprar una pizza? (S/N) ---> ";
				cin>>s;
				s = toupper(s);
			}while(s != 'S' && s != 'N');
			if(s == 'S'){
				pizza.cantidad --;
				fseek(P, ftell(P) - sizeof(pizza), SEEK_SET );
				fwrite( &pizza, sizeof(pizza),1,P);
			}
			fclose(P);
			system("pause");
			return;
		}
	}
	cout<<"\nCodigo no encontrado\n";
	fclose(P);
	system("pause");
	return;
}

void raya1(){
    printf("\n\t\t============================================================\n");
}

