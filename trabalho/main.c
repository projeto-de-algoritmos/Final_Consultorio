/* Alunos:
Gabriel Alves Hussein   17/0103200
Victor Amaral Cerqueira 17/0164411
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definicoes Gerais
typedef int item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A,B) {item t=A; A=B, B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Paciente{
    char nome[100];
    int horarioInicio;
    int horarioFim;
    int visitado;
    int urgencia;
}PACIENTE;

// Chamada das Funcoes
void mostraMenu(int totalPacientes);
void exibePacientes(PACIENTE *paciente, int totalPacientes);
void ordena(PACIENTE *paciente, int relacoes[100][100], int l, int r, int totalPacientes);
void merge(PACIENTE *paciente, int relacoes[100][100], int l, int r1, int r2, int totalPacientes);
void cadastroPaciente (PACIENTE *paciente, int totalPacientes, int relacoes[100][100]);
void organizarGrade(PACIENTE *paciente, int totalPacientes, int relacoes[100][100]);
int criaPacientes (PACIENTE *Paciente, int totalPacientes, int relacoes[100][100]);

int main(){
    PACIENTE paciente[100];
    int relacoes[100][100] = {0};
    int totalPacientes = 0, opcao;
    
    totalPacientes = criaPacientes(paciente, totalPacientes, relacoes);

    do{
        mostraMenu(totalPacientes);
        scanf("%d",&opcao);
        system("clear");
        switch(opcao){
        case 1:
            cadastroPaciente(paciente, totalPacientes, relacoes);
            totalPacientes++;
            getc(stdin);
            printf("Aperte enter para voltar ao menu.");
            break;
        case 2:
            exibePacientes(paciente, totalPacientes);
            getc(stdin);
            break;
        case 3:
            ordena(paciente, relacoes, 0, totalPacientes-1, totalPacientes);
            organizarGrade(paciente, totalPacientes, relacoes);
            break;
        }
  }while(opcao != 0);

    return 0;
}

// Desenvolvimento das funcoes 
void mostraMenu(int totalPacientes){
  printf("\n");
  printf(" ====================================================\n");
  printf("|             >>>>>>>>> Menu <<<<<<<<<               |\n");
  printf("| 1 - Adicionar paciente (%d pacientes cadastrados)  |\n", totalPacientes);
  printf("| 2 - Exibir Pacientes disponiveis                   |\n");
  printf("| 3 - Calcular melhor grade de atendimento           |\n");
  printf("| 0 - Sair                                           |\n");
  printf(" ====================================================\n");
  printf("Sua opcao: ");
}

void exibePacientes(PACIENTE *paciente, int totalPacientes){
     for(int j = 0; j < totalPacientes; j++){
        printf("Codigo: %d\nNome: %s\nHorario: %d - %d\nGrau de urgencia: %d\n\n", j+1, paciente[j].nome, paciente[j].horarioInicio, paciente[j].horarioFim, paciente[j].urgencia);
    }
}

void ordena(PACIENTE *paciente, int relacoes[100][100], int l, int r, int totalPacientes){
    if(l>=r) return;
    int meio = (r+l)/2;
    ordena(paciente, relacoes, l, meio, totalPacientes);
    ordena(paciente, relacoes, meio+1, r, totalPacientes);
    merge(paciente, relacoes, l, meio, r, totalPacientes);
}

void merge(PACIENTE *paciente, int relacoes[100][100], int l, int r1, int r2, int totalPacientes){
    PACIENTE v2[100];
    int k = 0;
    int i = l;
    int j = r1 + 1;

    while (i <= r1 && j <= r2)
    {
        if (less(paciente[i].horarioFim, paciente[j].horarioFim))
            v2[k++] = paciente[i++];
        else
            v2[k++] = paciente[j++];
        
    }

    while (i <= r1)
        v2[k++] = paciente[i++];
    
    while (j <= r2)           
        v2[k++] = paciente[j++];
    

    k = 0;

    for (int i = l; i <= r2; i++)
        paciente[i] = v2[k++];
    

    return;
}

void cadastroPaciente (PACIENTE *paciente, int totalPacientes, int relacoes[100][100]) {
    int opcaoRelacionamento = 0, codigoRelacionamento = 0, novoPaciente = 0;

    printf("Digite o nome do paciente a ser cadastrado: \n");
    scanf(" %[^\n]s", paciente[totalPacientes].nome);
    
    printf("Digite o Horario de inicio do atendimento do paciente: \n");
    scanf("%d", &paciente[totalPacientes].horarioInicio);

    paciente[totalPacientes].horarioFim = paciente[totalPacientes].horarioInicio + 1;
    
    printf("Digite o grau de urgencia do atendimento do paciente(entre 1 a 5): \n");
    scanf("%d", &paciente[totalPacientes].urgencia);

    printf("O paciente possui relacao com algum outro paciente com consulta ja marcada?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &opcaoRelacionamento);
	
	paciente[totalPacientes].visitado = 0;

    if(opcaoRelacionamento==1){
        printf("Digite o codigo do paciente que se relaciona com o paciente atual\n");
        exibePacientes(paciente, totalPacientes);
        scanf("%d", &codigoRelacionamento);
        relacoes[codigoRelacionamento][totalPacientes+1];
        relacoes[totalPacientes+1][codigoRelacionamento];
    }
}

void organizarGrade(PACIENTE *paciente, int totalPacientes, int relacoes[100][100])
{
	PACIENTE grade[totalPacientes], pacienteAtendido;
    int urgenciaGeral = 0, diaConsulta = 0, urgenciaParcial = 0, visitados = 0, printGrade = 0;

	while(visitados < totalPacientes){
		for (int i=1; i<=totalPacientes; i++)
		{
			urgenciaParcial = paciente[i-1].urgencia;
			for (int j=1; j<=totalPacientes; j++){
				if(relacoes[i-1][j-1]==1 && paciente[i-1].visitado==0){
					urgenciaParcial = urgenciaParcial + paciente[j-1].urgencia;
				}
				if(j == totalPacientes && urgenciaGeral<urgenciaParcial && paciente[i-1].visitado==0){
					urgenciaGeral = urgenciaParcial;
					grade[diaConsulta] = paciente[i-1];
					pacienteAtendido = paciente[i-1];
				}
			}
			if(i==totalPacientes){
				for(int x=0; x<totalPacientes; x++){
					if(strcmp(pacienteAtendido.nome, paciente[x].nome)==0){
						paciente[x].visitado = 1;
						visitados++;
						for(int y=0; y<totalPacientes; y++){
							if(relacoes[x][y]==1){
                                if(paciente[y].visitado==0){
								    paciente[y].visitado = 1;
								    visitados++;
                                }
							}
						}
					}
				}
				diaConsulta++;
                urgenciaGeral = 0;
                i = 0;
                if(visitados>=totalPacientes){
                    break;
                }
			}
		}
	}

    printf("A grade de consultas ficou da seguinte forma:\n\n");
    for(int i = 0; i<diaConsulta; i++){
        printf("Dia %d\nCodigo: %d\nNome: %s\nHorario: %d - %d\nGrau de urgencia: %d\n\n", i+1, printGrade, grade[printGrade].nome, grade[printGrade].horarioInicio, grade[printGrade].horarioFim, grade[printGrade].urgencia);
        printGrade++;
        for(int j = 0; j<totalPacientes; j++){
            if(relacoes[printGrade-1][j]==1){
				printf("Codigo: %d\nNome: %s\nHorario: %d - %d\nGrau de urgencia: %d\n\n", printGrade, paciente[j].nome, paciente[j].horarioInicio, paciente[j].horarioFim, paciente[j].urgencia);
                printGrade++;
            }
        }
    }

}

int criaPacientes (PACIENTE *paciente, int totalPacientes, int relacoes[100][100]){
    strcpy(paciente[0].nome, "Jair");
    paciente[0].horarioInicio = 8;
    paciente[0].horarioFim = 9;
    paciente[0].urgencia = 1;
	paciente[0].visitado = 0;
    totalPacientes++;

    strcpy(paciente[1].nome, "Laura");
    paciente[1].horarioInicio = 15;
    paciente[1].horarioFim = 16;
    paciente[1].urgencia = 2;
	paciente[1].visitado = 0;
    totalPacientes++;

    strcpy(paciente[2].nome, "Juninho");
    paciente[2].horarioInicio = 14;
    paciente[2].horarioFim = 15;
    paciente[2].urgencia = 3;
	paciente[2].visitado = 0;
    totalPacientes++;

    strcpy(paciente[3].nome, "Kalil");
    paciente[3].horarioInicio = 10;
    paciente[3].horarioFim = 11;
    paciente[3].urgencia = 3;
	paciente[3].visitado = 0;
    totalPacientes++;

    strcpy(paciente[4].nome, "Brian");
    paciente[4].horarioInicio = 10;
    paciente[4].horarioFim = 11;
    paciente[4].urgencia = 5;
	paciente[4].visitado = 0;
    totalPacientes++;
    
    return totalPacientes;
}