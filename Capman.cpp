#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "game.h"

/* 
para que o manual de jogo seja apresentado, este jogo deve ser iniciado atrav�s 
da execu��o do programa launchCapman.exe presente na mesma pasta. 
*/

int main()
{
	SetConsoleTitle("*** C A P M A N ***");
	char cenario[25][25];	
	HWND hwnd = GetConsoleWindow();					
	if(hwnd != NULL) 
		MoveWindow(hwnd ,130,50 ,590, 600, TRUE); 
	agente jogador, inimigo;
	uchar espera = 40;
	char direcao;
	uchar qtdPontos;
	uchar fase = 3;
	bool continuarJogo = true;
	strcpy(jogador.categoria, "jogador");
	strcpy(inimigo.categoria, "inimigo");
	
	do
	{
		direcao = 'z';				
		jogador = resetarPosicoes(jogador, fase);
		inimigo = resetarPosicoes(inimigo, fase);
		montarCenario(fase, cenario, jogador);		
		qtdPontos = gerarPontos(cenario, fase);
		do
		{	
			system("cls");
			if(cenario[jogador.linha][jogador.coluna] == 'm')	// Retirar as moedas ap�s captura
			{
				cenario[jogador.linha][jogador.coluna] = '0';
				qtdPontos--;
			}
			if(cenario[jogador.linha][jogador.coluna] == 't')	// movimenta��o ap�s teletransporte. v�lido apenas para fase 3
			{
				if(jogador.linha < 5)							// identificar qual a porta de teletransporte
					direcao = 'w';
				else
					direcao = 'a';	
			}
			printf("\n\tFase %d", fase);
			printf("\t\t\t\tMoedas restantes: %d",qtdPontos);
			mostrarJogo(cenario, jogador, inimigo);
			if(kbhit())												
				direcao = getch();									// pegar tecla digitada do usu�rio
			jogador = acaoJogador(direcao, jogador, cenario);		// atualizar posi��o do jogador
			Sleep(espera);
		}while(!wasTouched(jogador, inimigo) && qtdPontos > 0);
		putchar('\a');
		if(qtdPontos > 0)
		{
			animacaoDerrota();
			fase = 1;	
		}
		else
		{
			animacaoVitoria(fase);
			fase++;	
			espera -= 10; 
		}
		printf("Deseja continuar jogando? (S/N): ");
		do
		{
			while(!kbhit());									// la�o inifinito at� usu�rio digitar alguma tecla
			direcao = getch();   								// aproveitamento de variaveis 	
		}while(direcao != 's' && direcao != 'n' && direcao != 'S' && direcao != 'N');   // s� sai do la�o se usu�rio digitar op��es validas
		switch(direcao)
		{
			case 'S':
				continuarJogo = true;
				break;
			case 's':
				continuarJogo = true;
				break;
			case 'N':
				continuarJogo = false;
				break;
			case 'n':
				continuarJogo = false;
		}
	}while(continuarJogo);
	system("cls");
	printf("Obigado por jogar :)\nDesenvolvido por Yure Matias\n\n");
	Sleep(500);
	system("taskkill /f /fi \"windowtitle eq Manual\"");		// fechar o manual ap�s termino do jogo
	return 0;
}
