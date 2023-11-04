#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>      
#include <locale.h>     
#define TAM 100 

typedef struct Agenda{
	
	char nome[50];
	char fone[17];
	char email[80];
	
}

contatos;

void Incluir(void);
void Listar(void);
void Orgnizar(void);
void Pesquisar(void);
char AddMais();
void Formato(void);

static int qtd = 0;
contatos max [TAM];
FILE *arq;

void Incluir(void){
	
	int cont = 0;
	int retorno;
	char op = 's';
	
	arq = fopen("agenda.txt", "a");
	if(arq == NULL){
		printf("Erro!\no arquivo da lista nao pode ser aberto!\n");
		getch();
		exit(1);
	}
	
	while((cont < TAM) && (op == 's')){
		
		printf (" Digite o nome: ");
           gets(max[cont].nome);
           printf (" Digite o numero: ");
           gets(max[cont].fone);
           printf (" Digite o E-mail: ");
           gets(max[cont].email);
           
           retorno = fwrite (&max[cont], sizeof (contatos), 1, arq  );
           if (retorno == 1){
           	printf("\n Gravacao ok!");
		   }
		
		cont++;
		op = AddMais();
		qtd++;
	}
	fclose(arq);
	
}

char AddMais(){
	char op;
	do{
	printf("\n Deseja inserir novos dados? [S ou N]? " );
      op = getch();
      printf("\n" );
   } while (op != 's' && op != 'n');
   return op;	
		
		}



void Formato(){
	arq = fopen("agenda.txt", "w+");
	printf("\n\tLista limpa!\n ");
	fclose(arq);
	 getch();
}

void Organizar(void){
	contatos vet;
	int aux, i, j,k ,retorno;
	char *str, *str2, *straux;
	aux = qtd;
	
	for(i = 0; i < aux; i++){
		
		str = max[i].nome;
		for(j = i+1; j < aux; j++){
		 str2 = max[j].nome;
		 if(strcmp(str, str2) > 0){
		 	
		 	vet = max[i];
                 max[i] = max[j];
                 max[j] = vet;
		 	
		 	}	
		}
		
	}
	
	remove("agenda.txt");
     arq = fopen("agenda.txt", "w+");
     if (arq == NULL){
        printf (" ERRO!\n ");
        getch();
        exit(1);
     }
     for (k = 0 ; k < aux ; k++){
           retorno = fwrite (&max[k], sizeof(contatos) ,1,arq);
           if (retorno != 1) { 
               printf("\n ERRO! ");
           }
     }
     fclose(arq);
     printf("\n Lista Ordenada!\n ");
     getch();
}	 
	
	
void Pesquisar(void){
     int i=0, retorno=1, cont=0;//
     char nome[50],op;

     arq = fopen("agenda.txt", "r");
     if (arq == NULL){
         printf (" Erro!\nO arquivo da lista não pode ser aberto! \n");
         getch();
         exit(1);
     }
     printf (" Digite o nome: ");
     gets(nome);
     retorno = fread(&max[i], sizeof(contatos), 1, arq);
     while (retorno == 1){
         if (strcmp(nome, max[i].nome) == 0 ){
            printf("\n Nome....: %s",max[i].nome);
            printf("\n Fone....: %s",max[i].fone);
            printf("\n E-mail..: %s\n ",max[i].email);
            cont++;
         }
     i++;
     retorno = fread(&max[i], sizeof(contatos), 1, arq);
     }
     if(cont == 0){
        printf("Nao ha contatos com este nome!\n ");
     }
     getch();
     fclose(arq);
}



void Listar(void){
    int i = 0, retorno;

    arq = fopen("agenda.txt", "r");//fopen abre o arquivo no modo leitura "r"
    if (arq == NULL){//caso o SO não consiga abrir o arquivo
       printf ("Erro!\nO arquivo da lista não pode ser aberto!\n");//sera mostrada esta mensagens
       getch();//espera que o usuário pressione uma tecla
       exit(1);//caso esse erro ocorra este comando encerra o programa
    }
    retorno = fread(&max[i], sizeof(contatos), 1, arq);//fread le apenas 1 contato do arquivo
    while (retorno == 1){ //o retorno recebe a quantidade de contatos lidos no fread
      printf("\n Nome....: %s",max[i].nome);
      printf("\n Fone....: %s",max[i].fone);
      printf("\n E-mail..: %s\n",max[i].email);
      i++;
      retorno = fread(&max[i], sizeof(contatos), 1, arq);//fread vai ler o proximo contato
    }
    printf(" \n\n %d Contatos salvos!\n ", i);
    getch();//espera que o usuário pressione uma tecla
    fclose(arq);//fecha o arquivo agenda.txt
}
	
void Sobre(void){
    printf("\n\n\t\tAGENDA EM LINGUAGUEM C\n\n");
    printf("\tTrabalho para obtenção de nota Parcial\n\tNa Disciplina de Algoritmos e Estrutura de Dados\n");
    printf("\tIntegrantes da Equipe:\n\t\tRodrigo Alves\n\t\tAdailton\n\t\tEduardo Ramos\n\t\tRoseane Brito");
    getch();
}

void menu(void){
    char op;
    do{
        system("cls");
        printf("\n\n\t\tAGENDA EM LINGUAGUEM C\n");
        printf("\n 1 = Incluir\n 2 = Listar\n 3 = Organizar por ordem alfabetica\n 4 = Pesquisar por nome\n");
        printf(" 5 = Formatar lista\n 6 = Sobre\n 7 = Voltar\n\n");
        op = getch();
        switch(op){
            case '1':
                Incluir();
                break;
            case '2':
                Listar();
                break;
            case '3':
                Organizar();
                break;
            case '4':
                Pesquisar();
                break;
            case '5':
                Formato();
                break;
            case '6':
                system("cls");
                Sobre();
                break;
            case '7':
                system("cls");
                main();
                break;
            default:
                printf("\a Digite uma opção valida\n");
                getch();
        }
    }
    while (op);
}

int main(int argc, char *argv[]) {
int var;
    system("title AGENDA");
    system("color 1f");// Define a o plano de Fundo Azul Marinho e o texto em Branco
    setlocale(LC_ALL, "Portuguese");//Define no console o idioma Portugues
    printf("\n\n\t\tAGENDA EM LINGUAGUEM C\n\n");
    printf("\tVeja todas as funções disponiveis no menu.\n");
    printf("\tUse os numeros para selecionar a opção desejada.\n");
    printf("\tPressione qualquer tecla para continuar ou\n\tEspaço para sair do programa agora.\n\t");
    var=getch();
    if(var == 32){ exit(0);}// 32 corresponde a espaço no teclado conforme Tabela ASCII
menu();// chamando a funçao menu para a main
system("pause");
}
