#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../ArrayList/ArrayList.h"
#include "Propietario.h"

ePropietario* ePropietario_nuevo(void)
{
    ePropietario* unPropietario;
    unPropietario = (ePropietario*)malloc(sizeof(ePropietario));
    return unPropietario;
}

ePropietario* ePropietario_nuevoPedirDatos(ArrayList* lista)
{
    int huboError = 0;
    int id;
    ePropietario* unPropietario = ePropietario_nuevo();

    if(lista != NULL && unPropietario != NULL)
    {
        id = ePropietario_nuevoId(lista, unPropietario);
        if(id > 0)
        {
            if(ePropietario_setId(unPropietario, id) == 0)
            {
                if(ePropietario_pedirNombre(unPropietario) < 0)
                {
                    huboError = 1;
                }
                else if(huboError == 0 && ePropietario_pedirDireccion(unPropietario) < 0)
                {
                    huboError = 1;
                }
                else if(huboError == 0 && ePropietario_pedirNumeroTarjeta(unPropietario) < 0)
                {
                    huboError = 1;
                }

                if(huboError == 1)
                {
                    ePropietario_borrar(unPropietario);
                    unPropietario = NULL;
                }
            }
        }
    }

    return unPropietario;
}

void ePropietario_borrar(ePropietario* elemento)
{
    if(elemento != NULL)
    {
        free(elemento);
    }
}

int ePropietario_confirmaOperacion(ePropietario* elemento, const char* mensaje)
{
    int retorno = -1;
    char confirma;

    if(elemento != NULL)
    {
        do
        {
            printf("%s", mensaje);
            ePropietario_imprimir(elemento);
            printf("Esta seguro? (S/N): ");
            fflush(stdin);
            scanf("%c", &confirma);
            if(toupper(confirma) != 'S' && toupper(confirma) != 'N')
            {
                printf("Respuesta no valida. Debe ingresar S o N\n");
            }
        } while(toupper(confirma) != 'S' && toupper(confirma) != 'N');

        if(toupper(confirma) == 'S')
        {
            retorno = 0;
        }
    }

    return retorno;
}

int ePropietario_cargarDesdeArchivo(ArrayList* lista, const char* nombreArchivo)
{
    int retorno = -1;
    FILE* archivo;
    int cantidadLeida;
    int huboError = 0;
    ePropietario* unPropietario = NULL;

    if(lista != NULL && nombreArchivo != NULL)
    {
        archivo = fopen(nombreArchivo, "rb");
        if(archivo != NULL)
        {
            while(!feof(archivo))
            {
                unPropietario = ePropietario_nuevo();
                if(unPropietario != NULL)
                {
                    cantidadLeida = fread(unPropietario, sizeof(ePropietario), 1, archivo);

                    if(feof(archivo))
                    {
                        ePropietario_borrar(unPropietario);
                        break;
                    }

                    if(cantidadLeida == 1)
                    {
                        if(ePropietario_agregar(lista, unPropietario) < 0)
                        {
                            huboError = 1; //Error al guardar en ArrayList
                            ePropietario_borrar(unPropietario);
                            break;
                        }
                    }
                    else
                    {
                        huboError = 1; //Error de lectura
                        ePropietario_borrar(unPropietario);
                        break;
                    }
                }
                else
                {
                    huboError = 1; //Error por falta de memoria
                    break;
                }
            }
            fclose(archivo);

            if(huboError == 0)
            {
                retorno = 0;
            }
        }
        else
        {
            retorno = 0; //No existe el archivo
        }
    }

    return retorno;
}

int ePropietario_agregar(ArrayList* lista, ePropietario* elemento)
{
    int retorno = -1;

    if(lista != NULL && elemento != NULL)
    {
        retorno = al_add(lista, elemento);
        if(retorno < 0)
        {
            printf("Hubo un error al dar de alta el Propietario en la Lista\n");
        }
    }

    return retorno;
}

int ePropietario_agregarEnArchivo(const char* nombreArchivo, ePropietario* elemento)
{
    int retorno = -1;
    FILE* archivo;
    int cantidadEscrita;

    if(nombreArchivo != NULL && elemento != NULL)
    {
        archivo = fopen(nombreArchivo, "ab");
        if(archivo != NULL)
        {
            cantidadEscrita = fwrite(elemento, sizeof(ePropietario), 1, archivo);
            if(cantidadEscrita == 1)
            {
                retorno = 0;
            }
            fclose(archivo);
        }
    }

    return retorno;
}

ePropietario* ePropietario_buscar(ArrayList* lista, int id)
{
    ePropietario* unPropietario = NULL;
    int i;
    int elementoHallado = 0;

    if(lista != NULL && id > 0)
    {
        if(al_isEmpty(lista) == 0)
        {
            for(i = 0; i < al_len(lista); i++)
            {
                unPropietario = (ePropietario*)al_get(lista, i);
                if(unPropietario != NULL)
                {
                    if(ePropietario_getId(unPropietario) == id)
                    {
                        elementoHallado = 1;
                        break;
                    }
                }
            }

            if(elementoHallado == 0)
            {
                unPropietario = NULL;
            }
        }
    }

    return unPropietario;
}

int ePropietario_nuevoId(ArrayList* lista, ePropietario* elemento)
{
    int nuevoId = 0;
    int listaVacia;
    int ultimoElemento;

    if(lista != NULL)
    {
        listaVacia = al_isEmpty(lista);
        if(listaVacia == 1)
        {
            nuevoId = 1;
        }
        else if(listaVacia == 0)
        {
            if(elemento != NULL)
            {
                ultimoElemento = al_len(lista) - 1;
                elemento = (ePropietario*)al_get(lista, ultimoElemento);
                nuevoId = elemento->id + 1;
            }
        }
    }

    return nuevoId;
}

int ePropietario_pedirId(ePropietario* elemento)
{
    int retorno = -1;
    int id;

    if(elemento != NULL)
    {
        printf("\nIngrese id del Propietario: ");
        scanf("%d", &id);
        retorno = ePropietario_setId(elemento, id);
    }

    return retorno;
}

int ePropietario_pedirNombre(ePropietario* elemento)
{
    int retorno = -1;
    char nombreAux[CHAR_BUFFER];
    char nombre[TAM_NOMBRE_APELLIDO];
    int longitud;

    if(elemento != NULL)
    {
        printf("\nIngrese nombre y apellido: ");
        fflush(stdin);
        gets(nombreAux);
        longitud = strlen(nombreAux);
        if(longitud == 0)
        {
            printf("Debe ingresar un nombre y apellido\n");
        }
        else if(longitud > TAM_NOMBRE_APELLIDO)
        {
            printf("El nombre y apellido debe tener como maximo %d caracteres\n", TAM_NOMBRE_APELLIDO);
        }
        else
        {
            strcpy(nombre, nombreAux);
            retorno = ePropietario_setNombre(elemento, nombre);
        }
    }

    return retorno;
}

int ePropietario_pedirDireccion(ePropietario* elemento)
{
    int retorno = -1;
    char direccionAux[CHAR_BUFFER];
    char direccion[TAM_DIRECCION];
    int longitud;

    if(elemento != NULL)
    {
        printf("\nIngrese direccion: ");
        fflush(stdin);
        gets(direccionAux);
        longitud = strlen(direccionAux);
        if(longitud == 0)
        {
            printf("Debe ingresar una direccion\n");
        }
        else if(longitud > TAM_DIRECCION)
        {
            printf("La direccion debe tener como maximo %d caracteres\n", TAM_DIRECCION);
        }
        else
        {
            strcpy(direccion, direccionAux);
            retorno = ePropietario_setDireccion(elemento, direccion);
        }
    }

    return retorno;
}

int ePropietario_pedirNumeroTarjeta(ePropietario* elemento)
{
    int retorno = -1;
    char numeroTarjetaAux[CHAR_BUFFER];
    char numeroTarjeta[TAM_TARJETA];
    int longitud;

    if(elemento != NULL)
    {
        printf("\nIngrese numero de tarjeta de credito: ");
        fflush(stdin);
        gets(numeroTarjetaAux);
        longitud = strlen(numeroTarjetaAux);
        if(longitud == 0)
        {
            printf("Debe ingresar un numero de tarjeta de credito\n");
        }
        else if(longitud > TAM_TARJETA)
        {
            printf("El numero de tarjeta de credito debe tener como maximo %d caracteres\n", TAM_TARJETA);
        }
        else
        {
            strcpy(numeroTarjeta, numeroTarjetaAux);
            retorno = ePropietario_setNumeroTarjeta(elemento, numeroTarjeta);
        }
    }

    return retorno;
}

void ePropietario_imprimir(ePropietario* elemento)
{
    printf("%d - %s - %s - %s\n", ePropietario_getId(elemento), ePropietario_getNombre(elemento), ePropietario_getDireccion(elemento), ePropietario_getNumeroTarjeta(elemento));
}

int ePropietario_listar(ArrayList* lista)
{
    int i;
    int retorno = -1;
    ePropietario* unPropietario = NULL;

    if(lista != NULL)
    {
        if(al_isEmpty(lista) == 0)
        {
            for(i = 0; i < al_len(lista); i++)
            {
                unPropietario = (ePropietario*)al_get(lista, i);
                if(unPropietario != NULL)
                {
                    ePropietario_imprimir(unPropietario);
                    retorno = 0;
                }
            }
        }
    }

    return retorno;
}

void ePropietario_limpiarMemoria(ArrayList* lista)
{
    int i;
    ePropietario* unPropietario = NULL;

    if(lista != NULL)
    {
        if(al_isEmpty(lista) == 0)
        {
            for(i = 0; i < al_len(lista); i++)
            {
                unPropietario = (ePropietario*)al_get(lista, i);
                ePropietario_borrar(unPropietario);
            }
        }
        al_deleteArrayList(lista);
    }
}

//Seters y Getters*******************
int ePropietario_setId(ePropietario* this, int id)
{
    int retorno = -1;

    if(this != NULL && id > 0)
    {
        this->id = id;
        retorno = 0;
    }

    return retorno;
}

int ePropietario_getId(ePropietario* this)
{
    int retorno = -1;

    if(this != NULL)
    {
        retorno = this->id;
    }

    return retorno;
}

int ePropietario_setNombre(ePropietario* this, const char* nombre)
{
    int retorno = -1;

    if(this != NULL && nombre != NULL)
    {
        strcpy(this->nombre, nombre);
        retorno = 0;
    }

    return retorno;
}

char* ePropietario_getNombre(ePropietario* this)
{
    char* retorno = NULL;

    if(this != NULL)
    {
        retorno = this->nombre;
    }

    return retorno;
}

int ePropietario_setDireccion(ePropietario* this, const char* direccion)
{
    int retorno = -1;

    if(this != NULL && direccion != NULL)
    {
        strcpy(this->direccion, direccion);
        retorno = 0;
    }

    return retorno;
}

char* ePropietario_getDireccion(ePropietario* this)
{
    char* retorno = NULL;

    if(this != NULL)
    {
        retorno = this->direccion;
    }

    return retorno;
}

int ePropietario_setNumeroTarjeta(ePropietario* this, const char* numeroTarjeta)
{
    int retorno = -1;

    if(this != NULL && numeroTarjeta != NULL)
    {
        strcpy(this->numeroTarjeta, numeroTarjeta);
        retorno = 0;
    }

    return retorno;
}

char* ePropietario_getNumeroTarjeta(ePropietario* this)
{
    char* retorno = NULL;

    if(this != NULL)
    {
        retorno = this->numeroTarjeta;
    }

    return retorno;
}
//***********************************
