#ifndef PROPIETARIO_H_INCLUDED
#define PROPIETARIO_H_INCLUDED

#define TAM_NOMBRE_APELLIDO 100
#define TAM_DIRECCION 50
#define TAM_TARJETA 50
#define CHAR_BUFFER 512

typedef struct
{
    int id;
    char* nombre;
    char* direccion;
    char* numeroTarjeta;
} ePropietario;

ePropietario* ePropietario_nuevo(void);
ePropietario* ePropietario_nuevoPedirDatos(ArrayList* lista);
void ePropietario_borrar(ePropietario* elemento);
char* char_nuevo(int longitud);
void char_borrar(char* elemento);
int ePropietario_agregar(ArrayList* lista, ePropietario* elemento);
int ePropietario_nuevoId(ArrayList* lista, ePropietario* elemento);
int ePropietario_pedirId(ePropietario* elemento);
int ePropietario_pedirNombre(ePropietario* elemento);
int ePropietario_pedirDireccion(ePropietario* elemento);
int ePropietario_pedirNumeroTarjeta(ePropietario* elemento);
void ePropietario_imprimir(ePropietario* elemento);
int ePropietario_listar(ArrayList* lista);
void ePropietario_limpiarMemoria(ArrayList* lista);

//Seters y Getters*******************
int ePropietario_setId(ePropietario* this, int id);
int ePropietario_getId(ePropietario* this);
int ePropietario_setNombre(ePropietario* this, char* nombre);
char* ePropietario_getNombre(ePropietario* this);
int ePropietario_setDireccion(ePropietario* this, char* direccion);
char* ePropietario_getDireccion(ePropietario* this);
int ePropietario_setNumeroTarjeta(ePropietario* this, char* numeroTarjeta);
char* ePropietario_getNumeroTarjeta(ePropietario* this);
//***********************************

#endif // PROPIETARIO_H_INCLUDED
