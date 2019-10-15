/**
 *   TRABALHO DE CÁLCULO NUMÉRICO - ENGENHARIA DE COMPUTAÇÃO - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cláudia Mariana Costa Maia
 *       - Cristiano Oliveira Lopes
 *       - Eduardo Maia Santos
 *       - Michael Alves Ribeiro
 *       - Ulric Marques Ferreira
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

/* ############################################################ */
/* ########## SEÇÃO 01: CONVERSÃO DE BASES NUMÉRICAS ##########
 *
 *  FUNÇÕES:
 *     I   - converteParteInteira(): converte a parte inteira de um número decimal;
 *     II  - converteParteFracionaria(): converte a parte fracionária de um número decimal;
 *     III - converteBase(): recebe o número decimal digitado pelo usuário e utiliza as funções I e II
 *                           para convertê-lo em Binário, Octal e Hexadecimal.
 */

void limpaTela(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int converteParteInteira(int parteInteira, int baseNumerica){
    /** Recebe 'parteInteira', que é a parte inteira de um número real decimal qualquer.
     *   Se essa parte for igual a zero, imprime zero e o programa finaliza.
     *   Caso contrário, converte essa parte inteira para a base numérica passada como parâmetro.
     */

    /* Variáveis */
    int i = 0;
    int j = 0;
    int *resto; //Armazenará os restos das sucessivas divisões da parte inteira pela base numérica;

    resto = malloc(sizeof(resto)*20); //Aloca o vetor (Obs.: o tamanho é um valor arbitrário);

    if(resto == NULL){ /* Falta de memória no sistema */
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        free(resto);
        return 1;

    } else{
        if(parteInteira == 0){
            printf("0");
        } else{
            while(parteInteira >= (baseNumerica-1)){
                resto[i] = parteInteira % baseNumerica;
                parteInteira = parteInteira / baseNumerica;
                i++;
            }
            resto[i] = parteInteira % baseNumerica;

            j = i;
            /* Imprime o vetor 'resto' de trás para frente */
            while(j >= 0){
                if(resto[j] == 10) printf("A");
                else if(resto[j] == 11) printf("B");
                else if(resto[j] == 12) printf("C");
                else if(resto[j] == 13) printf("D");
                else if(resto[j] == 14) printf("E");
                else if(resto[j] == 15) printf("F");
                else printf("%d", resto[j]);

                j--;
            }
        }
    }
    return 0;
} /* Fim converteParteInteira */

void converteParteFracionaria(double fracao, int baseNumerica) {
    /**  Recebe 'fracao', que é a parte fracionária de um número real decimal qualquer.
     *   Converte a parte fracionária para a base numérica passada como parâmetro.
     */

    /* Variáveis */
    int i = 0;
    int parteInteira = 0;
    double mult = 0.0;

    /* Calcula e imprime as partes inteiras das sucessivas multiplicações das partes fracionárias pela base numérica */
    do{
        mult = fracao * baseNumerica;
        parteInteira = floor(mult);   //Separa a parte inteira;
        fracao = mult - (double)parteInteira; //Separa a parte fracionária;

        printf("%d",parteInteira); //Imprime a parte inteira;

        mult = 0.0;
        parteInteira = 0;
        i++;
    } while (fracao != 0.0 && i<=19); /* Pára quando a parte fracionária é nula ou quando atinge 20 casas decimais (0<= i <=19) */

    return;
} /* Fim converteParteFracionaria */

void converteBase(){
    /** Lê um número real decimal qualquer e o converte para as bases binária, octal e hexadecimal. */

    /* Cabeçalho */
    limpaTela();
    printf("### CONVERSAO DE BASE ###\n\n");
    printf("### Converte da base DECIMAL para BINARIO, OCTAL e HEXADECIMAL ###\n\n");

    /* Variáveis */
    double numeroDecimal;
    int parteInteira;
    double parteFracionaria;
    int aux;    //Variável auxiliar para receber o retorno da função 'converteParteInteira';

    setbuf(stdin,NULL);
    printf("Digite um numero decimal: ");
    scanf("%lf",&numeroDecimal);    // Lê o número real decimal;

    parteInteira = floor(numeroDecimal);             //Separa a parte inteira;
    parteFracionaria = numeroDecimal - (double)parteInteira; //Separa a parte fracionária;

    /* Converte em Binário */
    printf("\n\t- BINARIO: ");
    aux = converteParteInteira(parteInteira,2);
    if(parteFracionaria != 0.0 && aux!= 1){
        printf(".");
        converteParteFracionaria(parteFracionaria,2);
    }

    /* Converte em Octal */
    printf("\n\n\t- OCTAL: ");
    aux = converteParteInteira(parteInteira,8);
    if(parteFracionaria != 0.0 && aux!=1){
        printf(".");
        converteParteFracionaria(parteFracionaria,8);
    }

    /* Converte em Hexadecimal */
    printf("\n\n\t- HEXADECIMAL: ");
    aux = converteParteInteira(parteInteira,16);
    if(parteFracionaria != 0.0 && aux!=1){
        printf(".");
        converteParteFracionaria(parteFracionaria,16);
    }

    /* Espera o usuario pressionar uma tecla para voltar ao menu principal */
    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
    setbuf(stdin,NULL);
    getchar();

return;
} /* Fim converteBase() */

/* ===================== FIM SEÇÃO 01 ===================== */

/* ############################################################################ */
/* ### SEÇÃO 02: RESOLUÇÃO DE SISTEMAS LINEARES ATRAVÉS DO MÉTODO DE JORDAN ###
 *
 *  FUNÇÕES:
 *     I   - alocaMatriz(): aloca espaço na memória para uma matriz com l linhas e c colunas;
 *     II  - imprimeMatriz(): imprime uma matriz passada como parâmetro;
 *     III - jordan(): diagonaliza uma matriz passada como parâmetro;
 *     IV  - resolveJordan(): resolve a matriz diagonal após a função III.
 *     V   - sistemaLinear(): recebe o nome do arquivo, digitado pelo usuário, lê o conteúdo desse arquivo
 *                            e utiliza as funções III e IV para manipular o Sistema Linear e resolvê-lo
 *                            pelo método de Jordan.
 */

 double **alocaMatriz(int l, int c){
 	/*  Se houver memória disponível, aloca dinamicamente uma matriz de double com l linhas e c colunas
     *  e devolve um ponteiro para essa matriz, caso contrário, devolve um ponteiro nulo.
     */
     
	int i, j;
	double **M;

	
	M = malloc(sizeof(M)*l);
	if (M == NULL){
		return NULL;
    }
	for (i=0; i<l; i++){
		M[i] = malloc(sizeof(double)*c);
		if (M[i]==NULL){
			for (j=0;j<i;j++){
				free(M[j]);
				}
			free(M);
			return NULL;
			}
		}
	return M;
} /* Fim alocaMatriz() */

void imprimeMatriz(double **M, int l, int c){
	/*Imprime o conteúdo de uma matriz de double alocada
	dinamicamente com l linhas e c colunas*/
	int i, j;
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%10.3lf ", M[i][j]);
        }
		printf("\n");
    }
} /* Fim imprimeMatriz() */

void trocaColunas(double **M, int n, int c1, int c2, int *vetorIndices){
	/* Recebe M, a matriz aumentada de um SL com n variáveis
	 * e n equações e troca a posição das colunas c1 e c2 de M. 
	 * Após isso, faz a mesma troca no vetorIndices, que é o vetor
	 * que associa cada coluna da matriz a sua respectiva variável do SL.
	 */
	int i,aux;
	for(i=0; i<n; i++){
		aux = M[i][c1];
		M[i][c1] = M[i][c2];
		M[i][c2] = aux;
	}
	aux = vetorIndices[c1];
	vetorIndices[c1] = vetorIndices[c2];
	vetorIndices[c2] = aux;
}

void jordan(double **M, int n, int *vetorIndices){
    /* Recebe M, a matriz aumentada de um SL com n variáveis
	 * e n equações e tranforma M na matriz aumentada de um SL diagonal
	 * equivalente, atualizando o vetor de índices quando necessário.
	 */
	int i,j,k;
	double fator;
	for(i=0; i<n; i++){
    	if (M[i][i] == 0){
			j = i+1;
			while(j < n && M[i][j] == 0){
				j++;
			}
			if(j < n){
				trocaColunas(M, n, i, j, vetorIndices);
			}
			else{
                for(k=0; k<n; k++){
                	//enche a coluna de zeros
                    M[k][i] = 0;
                }
			}
		}
		
		if(M[i][i] != 0){
			for(j=0; j<n; j++){
		        if(j!=i){
		            fator = M[j][i] / M[i][i];
		            for(k=0; k<n+1; k++){
		                M[j][k]= M[j][k] - (fator * M[i][k]);
		            }
		        }
       		}
		}
		
    }

} /* Fim jordan() */

void resolveJordan(double **M, int n, double x[], int *vetorIndices){
    /* Recebe M, que é uma matriz diagonal (de dimensão n) de um Sistema Linear após diagonalização,
     * e a resolve, colocando suas soluções no vetor x, passado como parâmetro, usando o vetor de índices
	 * para mostrar o valor correto de cada variavél do SL.
	 */
    int i;
    int tipo = 0; //classificação do SL: 0 para determinado; 1 para indeterminado
	for(i=0; i<n; i++){
		if(M[i][i] == 0){
			if(M[i][n] != 0){
				printf("\nO sistema linear é incompatível.\n");
    			return;
			}
			else{
				tipo = 1;
    			x[i] = 0;
			}
    	}
		else{
    		x[i]= M[i][n] / M[i][i];
		}
	}
	if(tipo){
		printf("\nO sistema é compatível e indeterminado.\nUma solução é:\n");
	}else{
		printf("\nO sistema é compatível e determinado.\nSua solução é:\n");
	}
    for(i=0; i<n; i++){
        printf("\n x%d = %10.3lf\n", vetorIndices[i],x[i]);
    }



} /* Fim resolveJordan() */

void sistemaLinear(){
    /**   Lê o nome do arquivo e, ao localizá-lo, lê o Sistema Linear contido no mesmo,
     *    bem como sua respectiva dimensao, e o resolve através do método de Jordan.
     */

    /* Cabeçalho */
    limpaTela();
    printf("### SISTEMA LINEAR ###\n\n");
    printf("### Resolve um Sistema Linear pelo Metodo de JORDAN ###\n\n");

    /* Variáveis para manipulação do arquivo */
    char *nomeArquivo;
    FILE *file;

    /* Variáveis para leitura e manipulação dos dados contidos no arquivo */
    int n;
    int coeficiente=0;
    double **matriz;
    double *vetorSolucao;

    /* Variáveis auxiliares */
    int i=0, j=0;
    int aux=0; //Variável auxiliar, para ler a primeira linha do arquivo (dimensao do sistema)
    int *vetorIndices; //Vetor utilizado para associar cada coluna da matriz a sua respectiva variável do sistema 


    nomeArquivo = malloc(sizeof(char)*35); /* Aloca string com até 35 caracteres (valor arbitrário) */

    if(nomeArquivo == NULL){
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        free(nomeArquivo);
        return;
    }
    setbuf(stdin,NULL);
    printf("Digite o nome do arquivo de texto (SEM SUA EXTENSAO): ");
    gets(nomeArquivo);   //Lê o nome do arquivo;

    strcat(nomeArquivo,".txt\0"); //Adiciona a extensão '.txt' mais caractere '\0' (final da string) ao nome do arquivo;

    file = fopen(nomeArquivo,"r"); //Abre arquivo no modo de leitura;

    if(file == NULL){ /* Arquivo não encontrado */
        free(nomeArquivo);
        printf("\n\n[!] Arquivo nao localizado");
        printf("\n[i] Verifique se o arquivo existe ou se voce digitou o nome corretamente");
        printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
        setbuf(stdin,NULL);
        getchar();

        return;
    }
    else{
        printf("\n\tArquivo: %s\t",nomeArquivo);

        while(!feof(file)){ /* Lê os dados do arquivo enquanto não chega no final do mesmo */
            if(aux==0){
                fscanf(file,"%d",&n); //Lê dimensao da matriz (primeira linha do arquivo);
                matriz = alocaMatriz(n,n+1);
                vetorSolucao = malloc(sizeof(double)*n);

                printf("Dimensao do sistema: %dx%d\n",n,n);

                if(matriz == NULL || vetorSolucao == NULL){ /* Falta de memória */
                    printf("\n[x] Falha! Nao ha memoria disponivel no sistema");
                    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
                    setbuf(stdin,NULL);
                    getchar();
                    return;
                }
                aux++; //Atualiza 'aux', para que este laço não seja mais executado nas próximas iterações.

            } else{
                /* Lê a matriz contida arquivo */
                fscanf(file,"%d",&coeficiente);
                matriz[i][j] = coeficiente;

                coeficiente = 0; //Reinicialização da variável, para receber novo valor na próxima iteração.
                setbuf(stdin,NULL);

                /* Atualiza i e j para atribuir os valores às posições corretas na matriz */
                j++;
                if(j>n){
                    i++;
                    j = 0;
                }
            }
        }
        fclose(file); //Fecha o arquivo
        
        vetorIndices = malloc(sizeof(int)*n); 
		for(i=0; i<n; i++){
			vetorIndices[i] = i+1; //o vetor de índices inicia normalmente na ordem crescente (1,2...,n)
		}

        printf("\nSistema Linear (Matriz Original)\n\n");
        imprimeMatriz(matriz,n,n+1);

        printf("\nSistema Linear (Matriz Diagonal)\n\n");
        jordan(matriz,n, vetorIndices);
        imprimeMatriz(matriz,n,n+1);

        resolveJordan(matriz,n,vetorSolucao, vetorIndices);
    }

	free(vetorIndices);
	free(vetorSolucao);
    /* Espera o usuario pressionar uma tecla para voltar ao menu principal */
    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
    setbuf(stdin,NULL);
    getchar();

    return;
} /* Fim sistemaLinear() */

 /* ===================== FIM SEÇÃO 02 ===================== */

/* ############################################################# */
 /* ### SEÇÃO 03: TEOREMA DE LAGRANGE EM EQUAÇÕES ALGÉBRICAS ###
 *
 *  FUNÇÕES:
 *      I    - verificaAn(): verifica se o coeficiente da variável de grau n de um polinômio é negativo. Se sim, multiplica o polinômio por -1.
 *      II   - calculaP1():  calcula P1(x), obtido invertendo-se as posições dos coeficientes do polinômio P(x) recebido como parâmetro. 
 *      III  - calculaP2();	 calcula P2(x), obtido invertendo-se o sinal dos coeficientes das variáveis de grau ímpar do polinômio P(x) recebido.
 *      IV   - calculaP3();  calcula P3(x), obtido aplicando-se ambas as operações realizadas em II e III sobre o polinômio P(x) recebido como parâmetro.
 *      V    - calculaK();	 retorna K, o maior índice dentre os índices dos coeficientes negativos de um polinômio recebido como parâmetro.
 *      VI   - calculaB();	 retorna B, o módulo do coeficiente mais negativo de um polinômio recebido como parâmetro.
 *      VII  - calculaL();   retorna L, obtido aplicando-se a fórmula do Teorema de Lagrange a um polinômio recebido como parãmetro.
 *      VIII - teoremaDeLagrange(); calcula os intervalos que contém as raízes reais positivas e negativas de um polinômio, utilizando as funções de II a VII.
 *      IX   - resolvePolinomio();  resolve o polinômio P(x), substituindo o valor de x recebido como parâmetro.
 *      X    - bissecao(): calcula uma aproximação para a raíz de um polinômio contida no intervalo recebido como parâmetro, utilizando a função IX
 *      XI   - teoremaDeBolzano(): recebe um polinômio f(x) e aplica o Teorema de Bolzano a um intervalo[a,b], mostrando uma aproximação da raíz contida
 								   nesse intervalo caso f(a) * f(b) seja menor que 0, ou informa que o intervalo contém uma quantidade par de raízes 
								   caso contrário. Utiliza a função X.
 *      XII  - equacaoAlgebrica(): lê o grau e os coeficientes do polinômio, e os utilizam nas funções VIII e XI;
 *
 */

 void verificaAn(int grau, int *coeficientes){
 	/* Recebe o grau de um polinômio e um vetor com seus coeficientes.
     * Verifica se o coeficiente da variável com o grau recebido é negativo.
     * Em caso afirmativo, multiplica o polinômio por -1.
     */
	int i;

	if (coeficientes[grau] < 0){
		for(i=0; i <= grau; i++){
			coeficientes[i] = coeficientes[i] * (-1);
		}
	}
} /* Fim verificaAn() */

void calculaP1(int grau, int *coeficientes, int *resultado){
	/* Recebe o grau de um polinômio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polinômio obtido
	 * invertendo-se os coeficientes do polinômio original.
     */
	int i;
	for(i=0;i <= grau; i++){
		resultado[i] = coeficientes[grau-i];
	}

	verificaAn(grau, resultado);

} /* Fim calculaP1() */

void calculaP2(int grau, int *coeficientes, int *resultado){
	/* Recebe o grau de um polinômio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polinômio obtido
	 * invertendo-se o sinal dos coeficientes das variáveis com grau ímpar
	 * do polinômio original.
     */
	
	int i;
	for(i = 0;i <= grau; i++){
		if(i % 2 != 0){
			resultado[i] = coeficientes[i]*(-1);
		}
		else{
			resultado[i] = coeficientes[i];
		}
	}

	verificaAn(grau, resultado);

} /* Fim calculaP2() */

void calculaP3(int grau, int *coeficientes, int *resultado){
	/* Recebe o grau de um polinômio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polinômio obtido
	 * invertendo-se os coeficientes do polinômio original e também 
	 * trocando o sinal dos coeficientes das variáveis com grau ímpar.
     */
     
	int i, *aux;
	aux = malloc(sizeof(int)*(grau+1));

	for(i=0;i <= grau; i++){
		resultado[i] = coeficientes[grau-i];
		aux[i] = coeficientes[grau-i];
	}

	for(i = 0;i <= grau; i++){
		if(i % 2 !=0){
			resultado[i] = aux[i]*(-1);
		}
		else{
			resultado[i] = aux[i];
		}
	}

	free(aux);
	verificaAn(grau, resultado);

} /* Fim calculaP3() */

int calculaK(int grau, int *coeficientes){
	/* Recebe o grau de um polinômio e o vetor com seus coeficientes.
     * Retorna o valor do maior índice dentre os índices dos coeficientes
	 * negativos do polinômio.
     */
	int i;
	for(i = grau; i >=0; i--){
		if(coeficientes[i] < 0)
			return i;
	}
	return -1;
} /* Fim calculaK() */


int calculaB(int grau, int *coeficientes){
	/* Recebe o grau de um polinômio e o vetor com seus coeficientes.
     * Retorna o valor do módulo do coeficiente mais negativo do polinômio.
     */
	int b = 0;
	int i;

	for(i = grau; i >= 0; i--){
		if(coeficientes[i] < b)
			b = coeficientes[i];
	}
	return abs(b);
} /* Fim calculaB() */

double calculaL(int grau, int k, int b, int an){
	/* Recebe o grau, o valor do maior índice dentre os índices 
	 * dos coeficientes negativos, o valor do módulo do coeficiente
     * mais negativo e o coeficiente da variável com o grau recebido
	 * de um polinômio. Retorna o limite superior para as raízes reais
	 * positivas desse polinômio. 
     */
     
	return 1.0 + pow((b * 1.0)/an, 1.0/(grau-k));
	
} /* Fim calculaL() */


void teoremaDeLagrange(int grau, int *coeficientes){
    /* Recebe o grau do polinômio e o vetor com seus coeficientes.
     * Calcula os limites superiores e inferiores de suas raízes reais
	 * positivas e negativas usando o Teorema de Lagrange.
     */

    /* Variáveis */
	int i;
	int an[4], b[4], k[4];
	double l[4], limSupP, limInfP, limSupN, limInfN;
	int **p; //matriz utilizada para armazenar os polinômios P, P1, P2 e P3
	
	p = malloc(sizeof(p)*4);
	p[0] = coeficientes; // salva o vetor dos coeficientes do polinômio original em p[0]
	for(i=1; i<4; i++){
		p[i] = malloc(sizeof(int)*(grau+1)); /*aloca dinamicamente os vetores correspondentes
											   aos coeficientes de P1, P2 e P3 */
	}
	
	calculaP1(grau, coeficientes, p[1]);
	calculaP2(grau, coeficientes, p[2]);
	calculaP3(grau, coeficientes, p[3]);

	for(i=0; i<4; i++){
		an[i] = p[i][grau];
		b[i]=calculaB(grau, p[i]);
		k[i]=calculaK(grau, p[i]);
		l[i] = calculaL(grau, k[i], b[i], an[i]);
	}

	limSupP = l[0];		//calcula o limite superior das raizes reais positivas
	limInfP = 1/l[1];  	//calcula o limite inferior das raizes reais positivas
	limSupN = -1/l[3];	//calcula o limite supeior das raizes reais negativas
	limInfN = -l[2];	//calcula o limite inferior das raizes reais negativas
		
	printf("\nOs limites das raizes reais positivas do polinômio são:\n\n%lf <= x <= %lf \n\n", limInfP, limSupP);
	printf("\nOs limites das raizes reais negativas do polinômio são:\n\n%lf <= x <= %lf \n", limInfN, limSupN);
	
	free(p);
} /* Fim teoremaDeLagrange() */

double resolvePolinomio(int grau, int *coeficientes, double x){
	/* Recebe um vetor com os coeficientes de um polinômio e seu respectivo grau e
     * calcula o resultado do polinômio em função do valor x recebido como parâmetro.
     */
     
	int i;
	double resultado = 0;
	for(i = grau; i >= 0 ; i--){
		resultado = resultado + (coeficientes[i] * pow(x, i));
	}
	return resultado;
} /* Fim resolvePolinomio() */


double bissecao(int grau, int *coeficientes, double a, double b){
    /* Recebe um vetor com os coeficientes de um polinômio e seu respectivo grau.
     * Calcula a aproximação de uma raiz desse polinômio dentro do intervalo [a, b]
     * através do método da bisseção.
     */

    /* Variáveis */
	int i;
	double erro, fa, fb, m, fm;
	
	 //calcula o erro
	erro = (b-a)/2;
	
	i = 0; //inicia o contador de iterações
	
	// continua iterando até que o erro seja menor que 10^-8 ou tenham passado 1000 iterações
	while(erro > 0,00000001 && i < 1000){
		m = (a+b)/2; //calcula o valor médio do intervalo
		fa = resolvePolinomio(grau, coeficientes, a);
		fb = resolvePolinomio(grau, coeficientes, b);
		fm = resolvePolinomio(grau, coeficientes, m);
		//compara o sinal do polinomio de m com o sinal dos extremos e substitui o de mesmo sinal
		if(fm == 0)
			return m;
		
		if(fa * fm < 0){
			b = m;
		}
		else{
			a = m;
		}
		//calcula novo erro
		erro = (b-a)/2;
		i++;
	}
	
	return m;
} /* Fim bissecao() */


void teoremaDeBolzano(int grau, int *coeficientes, double a, double b){
	/* Recebe um vetor com os coeficientes de um polinômio e seu respectivo grau.
     * Aplica o Teorema de Bolzano no intervalo [a,b]. Caso a f(a) * f(b) seja menor
	 * que 0, mostra uma aproximação da raíz contida no intervalo. Se f(a) * f(b) for
	 * igual a 0, mostra um dos extremos do intervalo que é uma raíz do polinômio.
	 * Finalmente, caso f(a) * f(b) seja maior que 0, diz ao usuário que o intervalo
	 * contém uma quantidade par de raízes. 
     */
     
	double fa, fb, resultado;

	fa = resolvePolinomio(grau, coeficientes, a); //salva o resultado do polinômio em função do valor a
	fb = resolvePolinomio(grau, coeficientes, b); // salva o resultado do polinômio em função do valor b
	resultado = fa * fb;

	if(resultado < 0){
		printf("\nUma aproximação para a raíz contida nesse intervalo é: %lf\n", bissecao(grau, coeficientes, a, b));
	}
	else{
		if(resultado > 0){
			printf("\nO intervalo contém uma quantidade par de raízes.\n");
		}
		else{
			if(fa == 0)
				printf("\nUma raíz contida nesse intervalo é: %lf\n", a);
			else
				printf("\nUma raíz contida nesse intervalo é: %lf\n", b);
				
		}	
	}
}  /* Fim teoremaDeBolzano() */


void equacaoAlgebrica(){
    /**  Lê o grau e os coeficientes de um polinômio, exibe os intervalos onde se encontram
     *   as raízes reais positivas e negativas desse polinômio. Em seguida, lê um intervalo
	 *   aplica o Teorema de Bolzano para verificar se ele contém uma quantidade ímpar de 
	 *   raízes. Em caso afirmativo, exibe uma aproximação da raíz contida no intervalo
	 *	 utilizando o método da bisseção. Caso contrário, exibe uma mensagem informando que
	 * 	 o intervalo contém uma quantidade par de raízes.
     */

    /* Cabeçalho */
    limpaTela();
    printf("### EQUACAO ALGEBRICA ###\n\n");
    printf("### Calcula os limites das raizes pelo Teorema de LAGRANGE ###\n\n");

    /* Variáveis */
    int grau;
    int *coeficientes;
    int i = 0;
    double a,b;

    setbuf(stdin,NULL);
    printf("Digite o grau da equacao: ");
    scanf("%d",&grau);  //Lê o grau da equação

    coeficientes = malloc(sizeof(int)*(grau+1));

    if(coeficientes == NULL){ /* Falta de memória */
        free(coeficientes);
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
        setbuf(stdin,NULL);
        getchar();
        return;

    } else{
        printf("\n");

        printf("Digite os coeficientes:\n\n");
        for(i=grau;i>=0;i--){
           /* Laço 'for' para ler os coeficientes da equação.
            * OBS.: a(n) corresponde à posição i=grau, a(n-1) à posição i=grau-1, ..., a(1) à posição i=1 e a(0) à posição i=0;
            * Para isso ser possível, o vetor é lido de trás para frente.
            */
            setbuf(stdin,NULL);
            if(i==grau){
                /* Verifica se a(n)>=0. O laço finaliza somente quando essa condição for satisfeita */
                do{
                    printf("a[%d]: ",i);
                    scanf("%d",&coeficientes[grau]);

                    if(coeficientes[grau]<=0){
                        printf("[!] Invalido! a[%d] deve ser MAIOR QUE 0. Tente novamente.\n\n",i);
                        coeficientes[grau] = 0; //Reinicializa a variável;
                    }
                } while(coeficientes[grau]<=0);

            } else if(i==0){
                /* Verifica se a(0)!=0. O laço finaliza somente quando essa condição for satisfeita */
                do{
                    printf("a[%d]: ",i);
                    scanf("%d",&coeficientes[0]);
                    if(coeficientes[0]==0){
                        printf("[!] Invalido! a[%d] deve ser DIFERENTE DE 0. Tente novamente.\n\n",i);
                        coeficientes[0] = 0; //Reinicializa variável;
                    }
                } while(coeficientes[0]==0);

            } else{
                /* Lê os demais coeficientes da equação, que não sejam o a(n), nem o a(0),
                 * que merecem tratamentos especiais.
                 */
                printf("a[%d]: ",i);
                scanf("%d",&coeficientes[i]);
            }
        }

        printf("\n");
        teoremaDeLagrange(grau, coeficientes);

        printf("\n\nInforme o início e o fim de um intervalo:\n");
        setbuf(stdin, NULL);
        printf("\nInício: ");
        scanf("%lf", &a);

        setbuf(stdin,NULL);
        printf("\nFim: ");
        scanf("%lf", &b);
        printf("\n");
        
        teoremaDeBolzano(grau, coeficientes, a, b);
       
    }
	
	free(coeficientes);
	
    /* Espera o usuario pressionar uma tecla para voltar ao menu principal */
    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
    setbuf(stdin,NULL);
    getchar();

    return;
} /* Fim equacaoAlgebrica() */

 /* ===================== FIM SEÇÃO 03 ===================== */


 /* ######################################################## */
 /* ############### SEÇÃO 04: MENU DE OPÇÕES ###############
 *
 *  FUNÇÃO:
 *      - menudeopcoes(): exibe o menu de opções para que o usuário escolha a funcionalidade
 *                        do programa que deseja utilizar.
 */

 char menuDeOpcoes(){
    /** Exibe o menu de opções, lê a opção escolhida pelo usuário e retorna essa opção */

    char opcao;

    //Mostra o menu de opções. Repete o processo enquanto a opção escolhida pelo usuário não for válida.
    do{
        //Monta menu.
        limpaTela();
        printf("### CALCULO NUMERICO ###\n\n");
        printf("### MENU DE OPCOES ###\n\n");
        printf("C - Conversao\n");
        printf("S - Sistema Linear\n");
        printf("E - Equacao Algebrica\n");
        printf("F - Finalizar\n");
        printf("\n[i] Escolha uma opcao acima e pressione <ENTER>: ");

        setbuf(stdin,NULL);
        opcao = toupper(getchar()); //Lê a opção digitada pelo usuário e a transforma em letra maiúscula.

        /* Exibe aviso de advertência, caso a opção escolhida pelo usuário seja inválida */
        if((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F')){
            printf("#");
            printf("\n\n[!] Opcao invalida\n");
            printf("[i] Pressione <ENTER> e tente novamente...");
            setbuf(stdin,NULL);
            getchar();
        }
    //Testa validade. Se a opção escolhida for válida, o laço termina. Caso contrário, mostra o menu novamente.
    } while((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F'));

    return opcao;
} /* Fim menuDeOpcoes() */

 /* ===================== FIM SEÇÃO 04 ===================== */


/** FUNÇÃO PRINCIPAL */
int main(){
    setlocale(LC_ALL, "portuguese");
    int finalizarPrograma = 0; //Flag para quando o usuário desejar finalizar o programa.

    /* Laço do-while: Chama a função 'menuDeOpções' e abre a função correspondente à escolha do usuário.
     * Repete o processo enquanto o mesmo não desejar finalizar o programa.
     */
    do{
        switch(menuDeOpcoes()){
            //Opção 'CONVERSÃO'
            case 'C':
                converteBase();
                break;

            //Opção 'SISTEMA LINEAR'
            case 'S':
                sistemaLinear();
                break;

            //Opção 'EQUAÇÃO ALGÉBRICA'
            case 'E':
                equacaoAlgebrica();
                break;

            //Opção 'FINALIZAR'
            case 'F':
                printf("Finalizar\n");
                finalizarPrograma = 1;
                break;
        }
    //Testa validade para saber se o usuário deseja finalizar o programa.
    } while(!finalizarPrograma);

return 0;
} /* Fim main() */
