#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if(lista != NULL && unPropietario != NULL)
    {
        id = ePropietario_nuevoId(lista);
        if(id > 0)
        {
            if(ePropietario_setId(unPropietario, id) == 0)
            {

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
    strcpy(retorno, this->nombre);
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
    strcpy(retorno, this->direccion);
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
    strcpy(retorno, this->numeroTarjeta);
    return retorno;
}
//***********************************
