/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fp;
	char palabra[TAMTOKEN];
	iNumElementos = 0;
	int i;

	//open file											//OK
	fp = fopen(szNombre, "r");

	while (feof(fp) == 0)
	{
		fscanf(fp, "%s", palabra);
		elimCaract(palabra);
		strcpy(szPalabras[iNumElementos], palabra);
		iNumElementos++;
	}

	iNumElementos--;
	Supr(szPalabras, iNumElementos, iEstadisticas);
	Ordenar(szPalabras, iNumElementos, iEstadisticas, 1);
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}



//funciones utiles

void elimCaract(char* palabra)					//elimina s mbolos y convierte a min sculas.

{
	char simbolos[] = ". ,;()";
	int i, j, apuntador = 0;

	for (i = 0; i < strlen(palabra); i++)
	{
		int anadir = 1;
		for (j = 0; j < strlen(simbolos); j++)
		{
			if (palabra[i] == simbolos[j])
			{
				anadir = 0;
			}
		}
		if (anadir == 1)
		{
			palabra[apuntador] = palabra[i];
			apuntador++;
		}
	}
	palabra[apuntador] = 0;

	for (i = 0; palabra[i] != '\0'; i++)
	{
		palabra[i] = tolower(palabra[i]);
	}
}

void Supr(char szPalabras[][TAMTOKEN], int& elementos, int iEstadisticas[])	//elimina duplicados.
{
	int i, j, k;
	for (i = 0; i < elementos; i++)
	{
		iEstadisticas[i]++;
	}

	for (i = 0; i < elementos; i++)
	{
		for (j = i + 1; j < elementos; j++)
		{
			if (strcmp(szPalabras[i], szPalabras[j]) == 0)
			{
				iEstadisticas[i] += 1;
				for (k = j; k < elementos; k++)
				{
					strcpy(szPalabras[k], szPalabras[k + 1]);
				}
				elementos--;
				j--;
			}
		}
	}
}

void Ordenar(char szPalabras[][TAMTOKEN], int elementos, int iEstadisticas[], int opcion)
{
	int i, j;
	char aux[TAMTOKEN];
	int auxNum;

	if (opcion == 0)
	{
		for (i = 0; i < elementos; i++)
		{
			for (j = 0; j < elementos - 1; j++)
			{
				if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0)
				{
					strcpy(aux, szPalabras[j]);
					strcpy(szPalabras[j], szPalabras[j + 1]);
					strcpy(szPalabras[j + 1], aux);

					auxNum = iEstadisticas[j];
					iEstadisticas[j] = iEstadisticas[j + 1];
					iEstadisticas[j + 1] = auxNum;
				}
			}
		}
	}
	else if (opcion == 1)
	{
		for (i = 0; i < elementos; i++)
		{
			for (j = 0; j < elementos - 1; j++)
			{
				if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0)
				{
					strcpy(aux, szPalabras[j]);
					strcpy(szPalabras[j], szPalabras[j + 1]);
					strcpy(szPalabras[j + 1], aux);

					auxNum = iEstadisticas[j];
					iEstadisticas[j] = iEstadisticas[j + 1];
					iEstadisticas[j + 1] = auxNum;
				}
				else if (strcmp(szPalabras[j], szPalabras[j + 1]) == 0 && iEstadisticas[j] > iEstadisticas[j + 1])
				{
					auxNum = iEstadisticas[j];
					iEstadisticas[j] = iEstadisticas[j + 1];
					iEstadisticas[j + 1] = auxNum;
				}
			}
		}
	}
}
