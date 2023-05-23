#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct com os parâmetros definidos para cada venda -> Palavra-Chave "venda"
typedef struct Venda {
	float peso;
	float valor;
}venda;

// Struct para armazenar os dados de um dia de vendas
typedef struct Relatorio_Diario {
	float total_vendas;
	venda vendas[2];
	int id;
}rD;

// Struct para armazenar os dados de um mês de venda
typedef struct Relatorio_Mensal {
	float total_vendas;
	rD dia[4];
	char nome[16];
}rM;

// Função para limpar o buffer de leitura
void clearBuffer(void) {
	while (getchar() != '\n');
}

// Função para calcular o valor com base no peso
float pesoValor(float peso){
    return (peso * 55);
}

// Função para criar o valor de um dia de vendas, assumindo 10 vendas por dia
rD um_dia (void) {
	int i, n, bebida;
	rD dia;
	printf("\n---Insira as vendas---\n\n");
	
	dia.total_vendas = 0;
	
	for (i=0;i<2;i++) {
		printf("Digite 1 para quentinha.\nDigite 2 para peso.\n-> ");
		scanf("%d", &n);	
		clearBuffer();
		
		if (n == 1) {
			dia.vendas[i].peso = 0;
			dia.vendas[i].valor = 20.5;
		} else if (n == 2) {
			printf("Digite e o peso do prato: ");
			scanf("%f", &dia.vendas[i].peso);
			clearBuffer();
			
			dia.vendas[i].valor = pesoValor(dia.vendas[i].peso);
		}
		
		printf("\nAcompanha bebida por R$ 6.50?\n[1-Sim/2-Nao]-> ");
		scanf("%d", &bebida);
		
		if (bebida == 1) {
			dia.vendas[i].valor += 6.50;
		} else if (bebida == 2) {
			dia.vendas[i].valor += 0;
		}
		dia.total_vendas += dia.vendas[i].valor;
	}
	
	printf("\n--- Relatorio Diario --- \n\n");
	
	for (i=0;i<2;i++) {
		printf("Venda %d:\n%.3f Kg\n%.2f reais\n", i+1, dia.vendas[i].peso, dia.vendas[i].valor);
	}
	return dia;
}

// Função para calcular o valor de um mês de vendas, assumindo 28 dias por mês
rM um_mes (void) {
	int j;
	rM mes;
	
	mes.total_vendas = 0;
	
	for (j=0;j<4;j++) {
		mes.dia[j] = um_dia();
		mes.total_vendas += mes.dia[j].total_vendas;
		mes.dia[j].id = j+1;
	}
	
	printf("\n---Dados do Mes---\n");
	for (j=0;j<4;j++) {
		printf("Dia %d: %.2f reais.\n", mes.dia[j].id, mes.dia[j].total_vendas);
	}
	
	return mes;

}

// Função Principal
int main (void) {
	int i, j;
	
	rM meses[4];
	rM temp;
	
	// Enumeração de 4 meses do ano
	enum meses {Janeiro = 0, Fevereiro, Marco, Abril};
	
	for (i=0;i<4;i++) {
		if (i == Janeiro) {
			meses[0] = um_mes();
			strcpy(meses[0].nome, "Janeiro");
		} else if (i == Fevereiro) {
			meses[1] = um_mes();
			strcpy(meses[1].nome, "Fevereiro");
		} else if (i == Marco) {
			meses[2] = um_mes();
			strcpy(meses[2].nome, "Marco");
		} else if (i == Abril) {
			meses[3] = um_mes();
			strcpy(meses[3].nome, "Abril");
		}
	}
	
	// Bubble sorting para colocar os meses em ordem decrescente
	for (i=0;i<3;i++) {
		for (j=0;j<4;j++) {
			if (meses[j].total_vendas < meses[j+1].total_vendas) {
				temp = meses[j];
				meses[j] = meses[j+1];
				meses[j+1] = temp;
			}
		}
	}
	
	printf("\n--- Relatorio Anual ---\n\n");
	
	for (i=0;i<4;i++) {
		printf("%s: %.2f reais.\n", meses[i].nome, meses[i].total_vendas);
	}
	
	// Para testar o código de forma eficiente, os valor usados foram
	// 2 - para vendas por dia
	// 4 - para dias por mes
	
 }
