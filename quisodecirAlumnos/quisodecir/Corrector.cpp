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
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	int longi, posic = 0;
	int a, b, c, bPalabra = 0, ptr, bPtr, cont = 0;
	int posicion2 = 0;

	char alfabeto[] = { "abcdefghijklmnopqrstuvwxyz" };
	char letrasAcc[] = { "ñáéíóú" };

	char palabraLeidaCopia[TAMTOKEN];
	char palabraLeidaCopia2[TAMTOKEN];
	char finPal[TAMTOKEN];
	char tempPalab[TAMTOKEN];
	char tempPalab2[TAMTOKEN];

	longi = strlen(szPalabraLeida);

	for (a = 0; a < longi; a++)
	{
		for (b = 0; b < strlen(alfabeto); b++)
		{
			if (szPalabraLeida[a] == alfabeto[b])
			{
				cont++;
			}
			else if (szPalabraLeida[a] == letrasAcc[0] || szPalabraLeida[a] == letrasAcc[1] || szPalabraLeida[a] == letrasAcc[2] || szPalabraLeida[a] == letrasAcc[3] || szPalabraLeida[a] == letrasAcc[4] || szPalabraLeida[a] == letrasAcc[5])
			{
				posic = a;
			}
		}
	}
	if (posic != 0)
	{
		ptr = 0;
		for (a = 0; a < longi; a++)
		{
			if (szPalabraLeida[a] != letrasAcc[1])
			{
				finPal[ptr] = szPalabraLeida[a];
				ptr++;
			}
		}
		strcpy(szPalabraLeida, finPal);
		longi--;
	}
	//inicio eliminacion							
	for (a = 0; a < longi; a++)
	{
		ptr = 0;
		memset(finPal, 0, 50);

		for (b = 0; b < longi; b++)
		{
			if (a != b)
			{
				finPal[ptr] = szPalabraLeida[b];
				ptr++;
			}
		}
		bPalabra = Revertir(posic, finPal, szPalabrasSugeridas, bPalabra, longi);
	}
	//aqui termina la eliminaci n!!!

	//ahora el intercambio							
	for (b = 1; b < longi; b++)
	{

		strcpy(palabraLeidaCopia2, szPalabraLeida);
		strcpy(palabraLeidaCopia, szPalabraLeida);

		for (a = 0; a < longi - b; a++)
		{
			palabraLeidaCopia2[a + b] = palabraLeidaCopia2[a + (b - 1)];
			palabraLeidaCopia2[a + (b - 1)] = palabraLeidaCopia[a + b];

			bPalabra = Revertir(posic, palabraLeidaCopia2, szPalabrasSugeridas, bPalabra, longi);
		}
	}
	//aqui termina el intercambio!!!

	//intercambio de car cteres					O
	for (a = 0; a < longi; a++)
	{
		strcpy(palabraLeidaCopia, szPalabraLeida);

		for (b = 0; b < strlen(alfabeto); b++)
		{
			palabraLeidaCopia[a] = alfabeto[b];
			bPalabra = Revertir(posic, palabraLeidaCopia, szPalabrasSugeridas, bPalabra, longi);
		}
	}

	for (a = 0; a < longi; a++)
	{
		strcpy(palabraLeidaCopia, szPalabraLeida);
		for (b = 0; b < 6; b++)
		{
			for (int k = 0; k < 50; k++)			//memset?
			{
				tempPalab[k] = 0;
				tempPalab2[k] = 0;
			}
			ptr = 0;
			for (c = 0; c < a; c++)
			{
				tempPalab[ptr] = palabraLeidaCopia[c];
				ptr++;
			}
			ptr = 0;
			for (c = a + 1; c < longi; c++)
			{
				tempPalab2[ptr] = palabraLeidaCopia[c];
				ptr++;
			}
			switch (b)								//para acentos
			{
			case 0:
				strcat(tempPalab, "ñ");
				strcat(tempPalab, tempPalab2);
				break;
			case 1:
				strcat(tempPalab, "á");
				strcat(tempPalab, tempPalab2);
				break;
			case 2:
				strcat(tempPalab, "é");
				strcat(tempPalab, tempPalab2);
				break;
			case 3:
				strcat(tempPalab, "í");
				strcat(tempPalab, tempPalab2);
				break;
			case 4:
				strcat(tempPalab, "ó");
				strcat(tempPalab, tempPalab2);
				break;
			case 5:
				strcat(tempPalab, "ú");
				strcat(tempPalab, tempPalab2);
				break;
			}
			bPalabra = Revertir(posic, tempPalab, szPalabrasSugeridas, bPalabra, longi);
		}
	}
	//aqui acaba el cambio de caracteres!!!

	//poner caracteres entre caracteres							OK!
	for (a = 0; a < longi + 1; a++)
	{
		strcpy(palabraLeidaCopia, szPalabraLeida);
		for (b = 0; b < strlen(alfabeto); b++)
		{
			for (int k = 0; k < 50; k++)
			{
				tempPalab[k] = 0;
				tempPalab2[k] = 0;
			}
			ptr = 0;
			for (c = 0; c < a; c++)
			{
				tempPalab[ptr] = palabraLeidaCopia[c];
				ptr++;
			}
			tempPalab[ptr] = alfabeto[b];

			ptr = 0;
			for (c = a; c < longi; c++)
			{
				tempPalab2[ptr] = palabraLeidaCopia[c];
				ptr++;
			}
			strcat(tempPalab, tempPalab2);
			bPalabra = Revertir(posic, tempPalab, szPalabrasSugeridas, bPalabra, longi);
		}
	}
	//aqui termina poner caracteres en caracteres

	iNumSugeridas = bPalabra + 1;
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
