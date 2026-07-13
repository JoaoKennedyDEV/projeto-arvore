typedef struct NO_DEC {
    int id;
    char pergunta[200];
    int ehFolha;
    char solucao[400];
    char referencia[100];
    struct NO_DEC *sim;
    struct NO_DEC *nao;
} NO_DEC;

typedef struct { NO_DEC *no; int profundidade; } Estado;

NO_DEC* criarNoDecisao(int id, char *pergunta, int folha);

void inserirFilho(NO_DEC *pai, NO_DEC *filho, int respSim);
void navegarDiagnostico(NO_DEC *raiz);
void exibirArvoreCompleta(NO_DEC *raiz, int nivel);
int contarDiagnosticos(NO_DEC *raiz);
int contarPerguntas(NO_DEC *raiz);
void salvarArvoreArquivo(NO_DEC *raiz, FILE *f);
NO_DEC* carregarArvoreArquivo(FILE *f);
void registrarSessao(int idDiagnostico, char *data, FILE *f);