/**
 *   TRABALHO DE C�LCULO NUM�RICO - ENGENHARIA DE COMPUTA��O - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cl�udia Mariana Costa Maia
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
/* ########## SE��O 01: CONVERS�O DE BASES NUM�RICAS ##########
 *
 *  FUN��ES:
 *     I   - converteParteInteira(): converte a parte inteira de um n�mero decimal;
 *     II  - converteParteFracionaria(): converte a parte fracion�ria de um n�mero decimal;
 *     III - converteBase(): recebe o n�mero decimal digitado pelo usu�rio e utiliza as fun��es I e II
 *                           para convert�-lo em Bin�rio, Octal e Hexadecimal.
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
    /** Recebe 'parteInteira', que � a parte inteira de um n�mero real decimal qualquer.
     *   Se essa parte for igual a zero, imprime zero e o programa finaliza.
     *   Caso contr�rio, converte essa parte inteira para a base num�rica passada como par�metro.
     */

    /* Vari�veis */
    int i = 0;
    int j = 0;
    int *resto; //Armazenar� os restos das sucessivas divis�es da parte inteira pela base num�rica;

    resto = malloc(sizeof(resto)*20); //Aloca o vetor (Obs.: o tamanho � um valor arbitr�rio);

    if(resto == NULL){ /* Falta de mem�ria no sistema */
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
            /* Imprime o vetor 'resto' de tr�s para frente */
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
    /**  Recebe 'fracao', que � a parte fracion�ria de um n�mero real decimal qualquer.
     *   Converte a parte fracion�ria para a base num�rica passada como par�metro.
     */

    /* Vari�veis */
    int i = 0;
    int parteInteira = 0;
    double mult = 0.0;

    /* Calcula e imprime as partes inteiras das sucessivas multiplica��es das partes fracion�rias pela base num�rica */
    do{
        mult = fracao * baseNumerica;
        parteInteira = floor(mult);   //Separa a parte inteira;
        fracao = mult - (double)parteInteira; //Separa a parte fracion�ria;

        printf("%d",parteInteira); //Imprime a parte inteira;

        mult = 0.0;
        parteInteira = 0;
        i++;
    } while (fracao != 0.0 && i<=19); /* P�ra quando a parte fracion�ria � nula ou quando atinge 20 casas decimais (0<= i <=19) */

    return;
} /* Fim converteParteFracionaria */

void converteBase(){
    /** L� um n�mero real decimal qualquer e o converte para as bases bin�ria, octal e hexadecimal. */

    /* Cabe�alho */
    limpaTela();
    printf("### CONVERSAO DE BASE ###\n\n");
    printf("### Converte da base DECIMAL para BINARIO, OCTAL e HEXADECIMAL ###\n\n");

    /* Vari�veis */
    double numeroDecimal;
    int parteInteira;
    double parteFracionaria;
    int aux;    //Vari�vel auxiliar para receber o retorno da fun��o 'converteParteInteira';

    setbuf(stdin,NULL);
    printf("Digite um numero decimal: ");
    scanf("%lf",&numeroDecimal);    // L� o n�mero real decimal;

    parteInteira = floor(numeroDecimal);             //Separa a parte inteira;
    parteFracionaria = numeroDecimal - (double)parteInteira; //Separa a parte fracion�ria;

    /* Converte em Bin�rio */
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

/* ===================== FIM SE��O 01 ===================== */

/* ############################################################################ */
/* ### SE��O 02: RESOLU��O DE SISTEMAS LINEARES ATRAV�S DO M�TODO DE JORDAN ###
 *
 *  FUN��ES:
 *     I   - alocaMatriz(): aloca espa�o na mem�ria para uma matriz com l linhas e c colunas;
 *     II  - imprimeMatriz(): imprime uma matriz passada como par�metro;
 *     III - jordan(): diagonaliza uma matriz passada como par�metro;
 *     IV  - resolveJordan(): resolve a matriz diagonal ap�s a fun��o III.
 *     V   - sistemaLinear(): recebe o nome do arquivo, digitado pelo usu�rio, l� o conte�do desse arquivo
 *                            e utiliza as fun��es III e IV para manipular o Sistema Linear e resolv�-lo
 *                            pelo m�todo de Jordan.
 */

 double **alocaMatriz(int l, int c){
 	/*  Se houver mem�ria dispon�vel, aloca dinamicamente uma matriz de double com l linhas e c colunas
     *  e devolve um ponteiro para essa matriz, caso contr�rio, devolve um ponteiro nulo.
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
	/*Imprime o conte�do de uma matriz de double alocada
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
	/* Recebe M, a matriz aumentada de um SL com n vari�veis
	 * e n equa��es e troca a posi��o das colunas c1 e c2 de M. 
	 * Ap�s isso, faz a mesma troca no vetorIndices, que � o vetor
	 * que associa cada coluna da matriz a sua respectiva vari�vel do SL.
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
    /* Recebe M, a matriz aumentada de um SL com n vari�veis
	 * e n equa��es e tranforma M na matriz aumentada de um SL diagonal
	 * equivalente, atualizando o vetor de �ndices quando necess�rio.
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
    /* Recebe M, que � uma matriz diagonal (de dimens�o n) de um Sistema Linear ap�s diagonaliza��o,
     * e a resolve, colocando suas solu��es no vetor x, passado como par�metro, usando o vetor de �ndices
	 * para mostrar o valor correto de cada variav�l do SL.
	 */
    int i;
    int tipo = 0; //classifica��o do SL: 0 para determinado; 1 para indeterminado
	for(i=0; i<n; i++){
		if(M[i][i] == 0){
			if(M[i][n] != 0){
				printf("\nO sistema linear � incompat�vel.\n");
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
		printf("\nO sistema � compat�vel e indeterminado.\nUma solu��o �:\n");
	}else{
		printf("\nO sistema � compat�vel e determinado.\nSua solu��o �:\n");
	}
    for(i=0; i<n; i++){
        printf("\n x%d = %10.3lf\n", vetorIndices[i],x[i]);
    }



} /* Fim resolveJordan() */

void sistemaLinear(){
    /**   L� o nome do arquivo e, ao localiz�-lo, l� o Sistema Linear contido no mesmo,
     *    bem como sua respectiva dimensao, e o resolve atrav�s do m�todo de Jordan.
     */

    /* Cabe�alho */
    limpaTela();
    printf("### SISTEMA LINEAR ###\n\n");
    printf("### Resolve um Sistema Linear pelo Metodo de JORDAN ###\n\n");

    /* Vari�veis para manipula��o do arquivo */
    char *nomeArquivo;
    FILE *file;

    /* Vari�veis para leitura e manipula��o dos dados contidos no arquivo */
    int n;
    int coeficiente=0;
    double **matriz;
    double *vetorSolucao;

    /* Vari�veis auxiliares */
    int i=0, j=0;
    int aux=0; //Vari�vel auxiliar, para ler a primeira linha do arquivo (dimensao do sistema)
    int *vetorIndices; //Vetor utilizado para associar cada coluna da matriz a sua respectiva vari�vel do sistema 


    nomeArquivo = malloc(sizeof(char)*35); /* Aloca string com at� 35 caracteres (valor arbitr�rio) */

    if(nomeArquivo == NULL){
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        free(nomeArquivo);
        return;
    }
    setbuf(stdin,NULL);
    printf("Digite o nome do arquivo de texto (SEM SUA EXTENSAO): ");
    gets(nomeArquivo);   //L� o nome do arquivo;

    strcat(nomeArquivo,".txt\0"); //Adiciona a extens�o '.txt' mais caractere '\0' (final da string) ao nome do arquivo;

    file = fopen(nomeArquivo,"r"); //Abre arquivo no modo de leitura;

    if(file == NULL){ /* Arquivo n�o encontrado */
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

        while(!feof(file)){ /* L� os dados do arquivo enquanto n�o chega no final do mesmo */
            if(aux==0){
                fscanf(file,"%d",&n); //L� dimensao da matriz (primeira linha do arquivo);
                matriz = alocaMatriz(n,n+1);
                vetorSolucao = malloc(sizeof(double)*n);

                printf("Dimensao do sistema: %dx%d\n",n,n);

                if(matriz == NULL || vetorSolucao == NULL){ /* Falta de mem�ria */
                    printf("\n[x] Falha! Nao ha memoria disponivel no sistema");
                    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
                    setbuf(stdin,NULL);
                    getchar();
                    return;
                }
                aux++; //Atualiza 'aux', para que este la�o n�o seja mais executado nas pr�ximas itera��es.

            } else{
                /* L� a matriz contida arquivo */
                fscanf(file,"%d",&coeficiente);
                matriz[i][j] = coeficiente;

                coeficiente = 0; //Reinicializa��o da vari�vel, para receber novo valor na pr�xima itera��o.
                setbuf(stdin,NULL);

                /* Atualiza i e j para atribuir os valores �s posi��es corretas na matriz */
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
			vetorIndices[i] = i+1; //o vetor de �ndices inicia normalmente na ordem crescente (1,2...,n)
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

 /* ===================== FIM SE��O 02 ===================== */

/* ############################################################# */
 /* ### SE��O 03: TEOREMA DE LAGRANGE EM EQUA��ES ALG�BRICAS ###
 *
 *  FUN��ES:
 *      I    - verificaAn(): verifica se o coeficiente da vari�vel de grau n de um polin�mio � negativo. Se sim, multiplica o polin�mio por -1.
 *      II   - calculaP1():  calcula P1(x), obtido invertendo-se as posi��es dos coeficientes do polin�mio P(x) recebido como par�metro. 
 *      III  - calculaP2();	 calcula P2(x), obtido invertendo-se o sinal dos coeficientes das vari�veis de grau �mpar do polin�mio P(x) recebido.
 *      IV   - calculaP3();  calcula P3(x), obtido aplicando-se ambas as opera��es realizadas em II e III sobre o polin�mio P(x) recebido como par�metro.
 *      V    - calculaK();	 retorna K, o maior �ndice dentre os �ndices dos coeficientes negativos de um polin�mio recebido como par�metro.
 *      VI   - calculaB();	 retorna B, o m�dulo do coeficiente mais negativo de um polin�mio recebido como par�metro.
 *      VII  - calculaL();   retorna L, obtido aplicando-se a f�rmula do Teorema de Lagrange a um polin�mio recebido como par�metro.
 *      VIII - teoremaDeLagrange(); calcula os intervalos que cont�m as ra�zes reais positivas e negativas de um polin�mio, utilizando as fun��es de II a VII.
 *      IX   - resolvePolinomio();  resolve o polin�mio P(x), substituindo o valor de x recebido como par�metro.
 *      X    - bissecao(): calcula uma aproxima��o para a ra�z de um polin�mio contida no intervalo recebido como par�metro, utilizando a fun��o IX
 *      XI   - teoremaDeBolzano(): recebe um polin�mio f(x) e aplica o Teorema de Bolzano a um intervalo[a,b], mostrando uma aproxima��o da ra�z contida
 								   nesse intervalo caso f(a) * f(b) seja menor que 0, ou informa que o intervalo cont�m uma quantidade par de ra�zes 
								   caso contr�rio. Utiliza a fun��o X.
 *      XII  - equacaoAlgebrica(): l� o grau e os coeficientes do polin�mio, e os utilizam nas fun��es VIII e XI;
 *
 */

 void verificaAn(int grau, int *coeficientes){
 	/* Recebe o grau de um polin�mio e um vetor com seus coeficientes.
     * Verifica se o coeficiente da vari�vel com o grau recebido � negativo.
     * Em caso afirmativo, multiplica o polin�mio por -1.
     */
	int i;

	if (coeficientes[grau] < 0){
		for(i=0; i <= grau; i++){
			coeficientes[i] = coeficientes[i] * (-1);
		}
	}
} /* Fim verificaAn() */

void calculaP1(int grau, int *coeficientes, int *resultado){
	/* Recebe o grau de um polin�mio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polin�mio obtido
	 * invertendo-se os coeficientes do polin�mio original.
     */
	int i;
	for(i=0;i <= grau; i++){
		resultado[i] = coeficientes[grau-i];
	}

	verificaAn(grau, resultado);

} /* Fim calculaP1() */

void calculaP2(int grau, int *coeficientes, int *resultado){
	/* Recebe o grau de um polin�mio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polin�mio obtido
	 * invertendo-se o sinal dos coeficientes das vari�veis com grau �mpar
	 * do polin�mio original.
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
	/* Recebe o grau de um polin�mio e um vetor com seus coeficientes.
     * Guarda no vetor resultado os coeficientes de um polin�mio obtido
	 * invertendo-se os coeficientes do polin�mio original e tamb�m 
	 * trocando o sinal dos coeficientes das vari�veis com grau �mpar.
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
	/* Recebe o grau de um polin�mio e o vetor com seus coeficientes.
     * Retorna o valor do maior �ndice dentre os �ndices dos coeficientes
	 * negativos do polin�mio.
     */
	int i;
	for(i = grau; i >=0; i--){
		if(coeficientes[i] < 0)
			return i;
	}
	return -1;
} /* Fim calculaK() */


int calculaB(int grau, int *coeficientes){
	/* Recebe o grau de um polin�mio e o vetor com seus coeficientes.
     * Retorna o valor do m�dulo do coeficiente mais negativo do polin�mio.
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
	/* Recebe o grau, o valor do maior �ndice dentre os �ndices 
	 * dos coeficientes negativos, o valor do m�dulo do coeficiente
     * mais negativo e o coeficiente da vari�vel com o grau recebido
	 * de um polin�mio. Retorna o limite superior para as ra�zes reais
	 * positivas desse polin�mio. 
     */
     
	return 1.0 + pow((b * 1.0)/an, 1.0/(grau-k));
	
} /* Fim calculaL() */


void teoremaDeLagrange(int grau, int *coeficientes){
    /* Recebe o grau do polin�mio e o vetor com seus coeficientes.
     * Calcula os limites superiores e inferiores de suas ra�zes reais
	 * positivas e negativas usando o Teorema de Lagrange.
     */

    /* Vari�veis */
	int i;
	int an[4], b[4], k[4];
	double l[4], limSupP, limInfP, limSupN, limInfN;
	int **p; //matriz utilizada para armazenar os polin�mios P, P1, P2 e P3
	
	p = malloc(sizeof(p)*4);
	p[0] = coeficientes; // salva o vetor dos coeficientes do polin�mio original em p[0]
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
		
	printf("\nOs limites das raizes reais positivas do polin�mio s�o:\n\n%lf <= x <= %lf \n\n", limInfP, limSupP);
	printf("\nOs limites das raizes reais negativas do polin�mio s�o:\n\n%lf <= x <= %lf \n", limInfN, limSupN);
	
	free(p);
} /* Fim teoremaDeLagrange() */

double resolvePolinomio(int grau, int *coeficientes, double x){
	/* Recebe um vetor com os coeficientes de um polin�mio e seu respectivo grau e
     * calcula o resultado do polin�mio em fun��o do valor x recebido como par�metro.
     */
     
	int i;
	double resultado = 0;
	for(i = grau; i >= 0 ; i--){
		resultado = resultado + (coeficientes[i] * pow(x, i));
	}
	return resultado;
} /* Fim resolvePolinomio() */


double bissecao(int grau, int *coeficientes, double a, double b){
    /* Recebe um vetor com os coeficientes de um polin�mio e seu respectivo grau.
     * Calcula a aproxima��o de uma raiz desse polin�mio dentro do intervalo [a, b]
     * atrav�s do m�todo da bisse��o.
     */

    /* Vari�veis */
	int i;
	double erro, fa, fb, m, fm;
	
	 //calcula o erro
	erro = (b-a)/2;
	
	i = 0; //inicia o contador de itera��es
	
	// continua iterando at� que o erro seja menor que 10^-8 ou tenham passado 1000 itera��es
	while(erro > 0,00000001 && i < 1000){
		m = (a+b)/2; //calcula o valor m�dio do intervalo
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
	/* Recebe um vetor com os coeficientes de um polin�mio e seu respectivo grau.
     * Aplica o Teorema de Bolzano no intervalo [a,b]. Caso a f(a) * f(b) seja menor
	 * que 0, mostra uma aproxima��o da ra�z contida no intervalo. Se f(a) * f(b) for
	 * igual a 0, mostra um dos extremos do intervalo que � uma ra�z do polin�mio.
	 * Finalmente, caso f(a) * f(b) seja maior que 0, diz ao usu�rio que o intervalo
	 * cont�m uma quantidade par de ra�zes. 
     */
     
	double fa, fb, resultado;

	fa = resolvePolinomio(grau, coeficientes, a); //salva o resultado do polin�mio em fun��o do valor a
	fb = resolvePolinomio(grau, coeficientes, b); // salva o resultado do polin�mio em fun��o do valor b
	resultado = fa * fb;

	if(resultado < 0){
		printf("\nUma aproxima��o para a ra�z contida nesse intervalo �: %lf\n", bissecao(grau, coeficientes, a, b));
	}
	else{
		if(resultado > 0){
			printf("\nO intervalo cont�m uma quantidade par de ra�zes.\n");
		}
		else{
			if(fa == 0)
				printf("\nUma ra�z contida nesse intervalo �: %lf\n", a);
			else
				printf("\nUma ra�z contida nesse intervalo �: %lf\n", b);
				
		}	
	}
}  /* Fim teoremaDeBolzano() */


void equacaoAlgebrica(){
    /**  L� o grau e os coeficientes de um polin�mio, exibe os intervalos onde se encontram
     *   as ra�zes reais positivas e negativas desse polin�mio. Em seguida, l� um intervalo
	 *   aplica o Teorema de Bolzano para verificar se ele cont�m uma quantidade �mpar de 
	 *   ra�zes. Em caso afirmativo, exibe uma aproxima��o da ra�z contida no intervalo
	 *	 utilizando o m�todo da bisse��o. Caso contr�rio, exibe uma mensagem informando que
	 * 	 o intervalo cont�m uma quantidade par de ra�zes.
     */

    /* Cabe�alho */
    limpaTela();
    printf("### EQUACAO ALGEBRICA ###\n\n");
    printf("### Calcula os limites das raizes pelo Teorema de LAGRANGE ###\n\n");

    /* Vari�veis */
    int grau;
    int *coeficientes;
    int i = 0;
    double a,b;

    setbuf(stdin,NULL);
    printf("Digite o grau da equacao: ");
    scanf("%d",&grau);  //L� o grau da equa��o

    coeficientes = malloc(sizeof(int)*(grau+1));

    if(coeficientes == NULL){ /* Falta de mem�ria */
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
           /* La�o 'for' para ler os coeficientes da equa��o.
            * OBS.: a(n) corresponde � posi��o i=grau, a(n-1) � posi��o i=grau-1, ..., a(1) � posi��o i=1 e a(0) � posi��o i=0;
            * Para isso ser poss�vel, o vetor � lido de tr�s para frente.
            */
            setbuf(stdin,NULL);
            if(i==grau){
                /* Verifica se a(n)>=0. O la�o finaliza somente quando essa condi��o for satisfeita */
                do{
                    printf("a[%d]: ",i);
                    scanf("%d",&coeficientes[grau]);

                    if(coeficientes[grau]<=0){
                        printf("[!] Invalido! a[%d] deve ser MAIOR QUE 0. Tente novamente.\n\n",i);
                        coeficientes[grau] = 0; //Reinicializa a vari�vel;
                    }
                } while(coeficientes[grau]<=0);

            } else if(i==0){
                /* Verifica se a(0)!=0. O la�o finaliza somente quando essa condi��o for satisfeita */
                do{
                    printf("a[%d]: ",i);
                    scanf("%d",&coeficientes[0]);
                    if(coeficientes[0]==0){
                        printf("[!] Invalido! a[%d] deve ser DIFERENTE DE 0. Tente novamente.\n\n",i);
                        coeficientes[0] = 0; //Reinicializa vari�vel;
                    }
                } while(coeficientes[0]==0);

            } else{
                /* L� os demais coeficientes da equa��o, que n�o sejam o a(n), nem o a(0),
                 * que merecem tratamentos especiais.
                 */
                printf("a[%d]: ",i);
                scanf("%d",&coeficientes[i]);
            }
        }

        printf("\n");
        teoremaDeLagrange(grau, coeficientes);

        printf("\n\nInforme o in�cio e o fim de um intervalo:\n");
        setbuf(stdin, NULL);
        printf("\nIn�cio: ");
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

 /* ===================== FIM SE��O 03 ===================== */


 /* ######################################################## */
 /* ############### SE��O 04: MENU DE OP��ES ###############
 *
 *  FUN��O:
 *      - menudeopcoes(): exibe o menu de op��es para que o usu�rio escolha a funcionalidade
 *                        do programa que deseja utilizar.
 */

 char menuDeOpcoes(){
    /** Exibe o menu de op��es, l� a op��o escolhida pelo usu�rio e retorna essa op��o */

    char opcao;

    //Mostra o menu de op��es. Repete o processo enquanto a op��o escolhida pelo usu�rio n�o for v�lida.
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
        opcao = toupper(getchar()); //L� a op��o digitada pelo usu�rio e a transforma em letra mai�scula.

        /* Exibe aviso de advert�ncia, caso a op��o escolhida pelo usu�rio seja inv�lida */
        if((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F')){
            printf("#");
            printf("\n\n[!] Opcao invalida\n");
            printf("[i] Pressione <ENTER> e tente novamente...");
            setbuf(stdin,NULL);
            getchar();
        }
    //Testa validade. Se a op��o escolhida for v�lida, o la�o termina. Caso contr�rio, mostra o menu novamente.
    } while((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F'));

    return opcao;
} /* Fim menuDeOpcoes() */

 /* ===================== FIM SE��O 04 ===================== */


/** FUN��O PRINCIPAL */
int main(){
    setlocale(LC_ALL, "portuguese");
    int finalizarPrograma = 0; //Flag para quando o usu�rio desejar finalizar o programa.

    /* La�o do-while: Chama a fun��o 'menuDeOp��es' e abre a fun��o correspondente � escolha do usu�rio.
     * Repete o processo enquanto o mesmo n�o desejar finalizar o programa.
     */
    do{
        switch(menuDeOpcoes()){
            //Op��o 'CONVERS�O'
            case 'C':
                converteBase();
                break;

            //Op��o 'SISTEMA LINEAR'
            case 'S':
                sistemaLinear();
                break;

            //Op��o 'EQUA��O ALG�BRICA'
            case 'E':
                equacaoAlgebrica();
                break;

            //Op��o 'FINALIZAR'
            case 'F':
                printf("Finalizar\n");
                finalizarPrograma = 1;
                break;
        }
    //Testa validade para saber se o usu�rio deseja finalizar o programa.
    } while(!finalizarPrograma);

return 0;
} /* Fim main() */
