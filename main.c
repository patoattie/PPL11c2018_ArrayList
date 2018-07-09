#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../ArrayList/ArrayList.h"
#include "Propietario.h"

int main()
{
    char seguir = 's';
    int opcion = 0;
    int puntoMenu;
    ArrayList* listaPropietarios = al_newArrayList();
    ePropietario* unPropietario = NULL;

    if(ePropietario_cargarDesdeArchivo(listaPropietarios, ARCHIVO_PROPIETARIOS) == 0)
    {
        while(seguir == 's')
        {
            system("cls");

            printf(" 1- Alta de propietario\n");
            printf(" 2- Modificacion de propietario\n");
            printf(" 3- Baja de propietario\n");
            printf(" 4- Listado de propietarios\n");
            printf(" 5- Ingreso de automovil\n");
            printf(" 6- Egreso de automovil\n");
            printf(" 7- Listado de automoviles\n");
            printf(" 8- Recaudacion Total\n");
            printf(" 9- Recaudacion Total por Marca\n");
            printf("10- Listado de automoviles estacionados por propietario\n");
            printf("11- Listado de propietarios con automoviles Audi estacionados\n");
            printf("12- Listado de automoviles estacionados\n\n");
            printf("13- Salir\n");

            scanf("%d", &opcion);

            switch(opcion)
            {
                case 1:
                    unPropietario = ePropietario_nuevoPedirDatos(listaPropietarios);
                    if(unPropietario != NULL)
                    {
                        if(ePropietario_confirmaOperacion(unPropietario, "Se va a dar de alta el Propietario:\n") == 0)
                        {
                            puntoMenu = ePropietario_agregar(listaPropietarios, unPropietario);
                            if(puntoMenu == 0)
                            {
                                puntoMenu = ePropietario_agregarEnArchivo(ARCHIVO_PROPIETARIOS, unPropietario);
                                if(puntoMenu == 0)
                                {
                                    printf("Alta de Propietario OK\n");
                                }
                                else
                                {
                                    //ePropietario_borrar
                                    ePropietario_borrar(unPropietario);
                                    unPropietario = NULL;
                                }
                            }
                            else
                            {
                                ePropietario_borrar(unPropietario);
                                unPropietario = NULL;
                            }
                        }
                        else
                        {
                            printf("Accion cancelada\n");
                            ePropietario_borrar(unPropietario);
                            unPropietario = NULL;
                        }
                    }
                    else
                    {
                        printf("Error al dar de alta Propietario\n");
                    }
                    break;

                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    puntoMenu = ePropietario_listar(listaPropietarios);
                    if(puntoMenu < 0)
                    {
                        printf("No hay Propietarios ingresados\n");
                    }
                    break;

                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    seguir = 'n';
                    ePropietario_limpiarMemoria(listaPropietarios);
                    break;
                default:
                    printf("\nOpcion no contemplada, por favor vuelva a elegir");
            }

            if(seguir == 's')
            {
                printf("\n");
                system("pause");
            }
        }
    }
    else
    {
        printf("\nError al leer archivo de Propietarios");
        ePropietario_limpiarMemoria(listaPropietarios);
    }

    return 0;
}
