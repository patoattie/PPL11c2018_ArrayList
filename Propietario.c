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

int ePropietario_agregar(ArrayList* lista)
{
    int retorno = -1;
    int huboError = 0;
    int id;
    ePropietario* unPropietario = ePropietario_nuevo();
    char confirma;

    if(lista != NULL && unPropietario != NULL)
    {
        id = ePropietario_nuevoId(lista, unPropietario);
        if(id > 0)
        {
            if(ePropietario_setId(unPropietario, id) == 0)
            {
                if(ePropietario_pedirNombre(unPropietario) < 0)
                {
                    printf("Debe ingresar un nombre y apellido\n");
                    huboError = 1;
                }
                else if(huboError == 0 && ePropietario_pedirDireccion(unPropietario) < 0)
                {
                    printf("Debe ingresar una direccion\n");
                    huboError = 1;
                }
                else if(huboError == 0 && ePropietario_pedirNumeroTarjeta(unPropietario) < 0)
                {
                    printf("Debe ingresar un numero de tarjeta\n");
                    huboError = 1;
                }

                if(huboError == 0)
                {
                    do
                    {
                        printf("Se va a dar de alta el Propietario:\n");
                        ePropietario_imprimir(unPropietario);
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
                        retorno = al_add(lista, unPropietario);
                        if(retorno < 0)
                        {
                            free(unPropietario);
                            printf("Hubo un error al dar de alta el Propietario en la Lista\n");
                        }
                    }
                    else
                    {
                        free(unPropietario);
                        printf("La accion fue cancelada\n");
                    }
                }
                else
                {
                    free(unPropietario);
                }
            }
        }
    }

    return retorno;
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
    char* nombre;

    if(elemento != NULL)
    {
        nombre = (char*)malloc(sizeof(char) * TAM_NOMBRE_APELLIDO);
        if(nombre != NULL)
        {
            printf("\nIngrese nombre y apellido: ");
            fflush(stdin);
            gets(nombre);
            if(strcmp(nombre, "") == 0)
            {
                free(nombre);
            }
            else
            {
                retorno = ePropietario_setNombre(elemento, nombre);
                if(retorno < 0)
                {
                    free(nombre);
                }
            }
        }
    }

    return retorno;
}

int ePropietario_pedirDireccion(ePropietario* elemento)
{
    int retorno = -1;
    char* direccion;

    if(elemento != NULL)
    {
        direccion = (char*)malloc(sizeof(char) * TAM_DIRECCION);
        if(direccion != NULL)
        {
            printf("\nIngrese direccion: ");
            fflush(stdin);
            gets(direccion);
            if(strcmp(direccion, "") == 0)
            {
                free(direccion);
            }
            else
            {
                retorno = ePropietario_setDireccion(elemento, direccion);
                if(retorno < 0)
                {
                    free(direccion);
                }
            }
        }
    }

    return retorno;
}

int ePropietario_pedirNumeroTarjeta(ePropietario* elemento)
{
    int retorno = -1;
    char* numeroTarjeta;

    if(elemento != NULL)
    {
        numeroTarjeta = (char*)malloc(sizeof(char) * TAM_TARJETA);
        if(numeroTarjeta != NULL)
        {
            printf("\nIngrese numero de tarjeta: ");
            fflush(stdin);
            gets(numeroTarjeta);
            if(strcmp(numeroTarjeta, "") == 0)
            {
                free(numeroTarjeta);
            }
            else
            {
                retorno = ePropietario_setNumeroTarjeta(elemento, numeroTarjeta);
                if(retorno < 0)
                {
                    free(numeroTarjeta);
                }
            }
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

int ePropietario_setNombre(ePropietario* this, char* nombre)
{
    int retorno = -1;

    if(this != NULL && nombre != NULL)
    {
        //strcpy(this->nombre, nombre);
        this->nombre = nombre;
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

int ePropietario_setDireccion(ePropietario* this, char* direccion)
{
    int retorno = -1;

    if(this != NULL && direccion != NULL)
    {
        //strcpy(this->direccion, direccion);
        this->direccion = direccion;
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

int ePropietario_setNumeroTarjeta(ePropietario* this, char* numeroTarjeta)
{
    int retorno = -1;

    if(this != NULL && numeroTarjeta != NULL)
    {
        //strcpy(this->numeroTarjeta, numeroTarjeta);
        this->numeroTarjeta = numeroTarjeta;
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
