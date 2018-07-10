#ifndef PROPIETARIO_H_INCLUDED
#define PROPIETARIO_H_INCLUDED

#define TAM_NOMBRE_APELLIDO 100
#define TAM_DIRECCION 50
#define TAM_TARJETA 50
#define CHAR_BUFFER 512
#define ARCHIVO_PROPIETARIOS "Propietarios.dat"

typedef struct
{
    int id;
    char nombre[TAM_NOMBRE_APELLIDO];
    char direccion[TAM_DIRECCION];
    char numeroTarjeta[TAM_TARJETA];
} ePropietario;

//Constructores y Destructores*******
ePropietario* ePropietario_nuevo(void);
ePropietario* ePropietario_nuevoPedirDatos(ArrayList* lista);
ePropietario* ePropietario_nuevoModificar(ePropietario* elemento);
//***********************************

void ePropietario_borrar(ePropietario* elemento);
int ePropietario_confirmaOperacion(void);
int ePropietario_cargarDesdeArchivo(ArrayList* lista, const char* nombreArchivo);
int ePropietario_agregar(ArrayList* lista, ePropietario* elemento);
int ePropietario_agregarEnArchivo(const char* nombreArchivo, ePropietario* elemento);
int ePropietario_modificar(ArrayList* lista, ePropietario* elemento, int indice);
int ePropietario_modificarEnArchivo(const char* nombreArchivo, ePropietario* elemento);
int ePropietario_buscar(ArrayList* lista, int id);
int ePropietario_nuevoId(ArrayList* lista);
int ePropietario_pedirNombre(ePropietario* elemento);
int ePropietario_pedirDireccion(ePropietario* elemento);
int ePropietario_pedirNumeroTarjeta(ePropietario* elemento);
void ePropietario_imprimir(ePropietario* elemento);
int ePropietario_listar(ArrayList* lista);
void ePropietario_limpiarMemoria(ArrayList* lista);

//Seters y Getters*******************
int ePropietario_setId(ePropietario* this, int id);
int ePropietario_getId(ePropietario* this);
int ePropietario_setNombre(ePropietario* this, const char* nombre);
char* ePropietario_getNombre(ePropietario* this);
int ePropietario_setDireccion(ePropietario* this, const char* direccion);
char* ePropietario_getDireccion(ePropietario* this);
int ePropietario_setNumeroTarjeta(ePropietario* this, const char* numeroTarjeta);
char* ePropietario_getNumeroTarjeta(ePropietario* this);
//***********************************

#endif // PROPIETARIO_H_INCLUDED
