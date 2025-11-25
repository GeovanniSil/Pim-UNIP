import csv
import os
from collections import deque
from colorama import init, Fore, Style 

# Inicializa o Colorama para que as cores funcionem em diferentes terminais
init(autoreset=True)

# Definição de constantes de cor para melhor legibilidade
# Cores de feedback
COR_ERRO = Fore.RED + Style.BRIGHT # Vermelho Brilhante para erros
COR_SUCESSO = Fore.GREEN + Style.BRIGHT # Verde Brilhante para sucesso
COR_ALERTA = Fore.RED + Style.BRIGHT # Vermelho Brilhante para alertas críticos (dados não salvos)

# Cores de interface (ATUALIZADAS CONFORME SUA REVISÃO)
COR_TITULO = Fore.WHITE + Style.BRIGHT # Branco Brilhante para títulos (ex: "MENU PRINCIPAL")
COR_OPCAO = Fore.CYAN # Ciano/Azul Claro para as opções ([1], [2], [3])
COR_INPUT = Fore.YELLOW # Amarelo para textos de input
COR_RESET = Style.RESET_ALL # Reseta a cor após a mensagem

# CONSTANTE PARA O LIMITE DE CARACTERES DO NOME 
LIMITE_NOME = 50 # Limite de 50 caracteres para o nome (NOVO)
# CONSTANTE PARA O LIMITE DE CARACTERES DO RA
LIMITE_RA = 8
# CONSTANTE PARA O LIMITE DE CARACTERES DA TURMA
LIMITE_TURMA = 8

# ----------------------------------------------
# CLASSE DE MODELAGEM DO ALUNO
# Objetivo: Representar um aluno e calcular sua média.
# ----------------------------------------------
class Aluno:
    def __init__(self, nome, ra, turma, disciplina, notas=None):
        self.nome = nome # Nome do aluno
        # Armazena o RA como digitado, mas checa de forma case-insensitive
        self.ra = ra 
        self.turma = turma
        self.disciplina = disciplina
        # Lista para armazenar as 3 notas (P1, P2, Trabalho)
        self.notas = notas if notas is not None else []
        self.media_semestral = 0.0 # Média calculada das 3 notas

    def calcular_media(self):
        """Calcula a Média Semestral (Soma das 3 notas / 3)."""
        NUMERO_NOTAS_FIXO = 3
        
        # Verifica se há o número correto de notas para o cálculo
        if len(self.notas) != NUMERO_NOTAS_FIXO:
            self.media_semestral = 0.0
            if len(self.notas) > 0:
                # Mensagem de alerta se as notas estiverem incompletas (Vermelho)
                print(f"{COR_ERRO}Alerta: O cálculo da média requer exatamente {NUMERO_NOTAS_FIXO} notas. Média Semestral definida como 0.0.{COR_RESET}")
            return self.media_semestral

        # Realiza o cálculo da Média Semestral
        soma_notas = sum(self.notas)
        self.media_semestral = soma_notas / NUMERO_NOTAS_FIXO
        return self.media_semestral

    def to_csv_row(self):
        """Formata os dados do aluno em uma lista para gravação no CSV."""
        self.calcular_media()
        
        # Formata as 3 notas com 2 casas decimais
        # Assume que self.notas[0], [1], [2] existem devido à função de cadastro
        p1 = f"{self.notas[0]:.2f}"
        p2 = f"{self.notas[1]:.2f}"
        trab = f"{self.notas[2]:.2f}"
        
        # Retorna a linha completa, incluindo a Média Semestral
        return [self.nome, self.ra, self.turma, self.disciplina, p1, p2, trab, f"{self.media_semestral:.2f}"]

# ----------------------------------------------
# FUNÇÕES DE LÓGICA DO SISTEMA
# ----------------------------------------------

def carregar_disciplinas():
    """Retorna um dicionário com as disciplinas disponíveis no sistema."""
    return {
        '1': "Algoritmos e Estruturas de Dados em Python",
        '2': "Analise e Projeto de Sistemas",
        '3': "Engenharia de Software Agil",
        '4': "Programacao Estruturada em C"
    }

def formatar_nome_arquivo(nome_disciplina):
    """Cria um nome de arquivo CSV limpo a partir do nome da disciplina."""
    return nome_disciplina.replace(" ", "_").replace("ê", "e").replace("á", "a") + ".csv"

def check_ra_uniqueness(ra_input, filas_por_disciplina):
    """
    Verifica se o RA já está cadastrado (CASE-INSENSITIVE).
    Retorna o NOME (em UPPER) associado ao RA se encontrado, ou None caso contrário.
    """
    # Normaliza o RA de entrada para maiúsculas para checagem case-insensitive
    ra_input_upper = ra_input.strip().upper()
    
    # 1. Checa RAs na fila (não salvos)
    for disciplina, alunos_fila in filas_por_disciplina.items():
        for aluno in alunos_fila:
            # Compara o RA da fila normalizado com o RA de entrada normalizado
            if aluno.ra.strip().upper() == ra_input_upper:
                return aluno.nome.strip().upper() # Retorna o nome do aluno na fila (em UPPER)

    # 2. Checa RAs nos arquivos CSV (salvos)
    disciplinas = carregar_disciplinas()
    for nome_disciplina in disciplinas.values():
        arquivo_csv = formatar_nome_arquivo(nome_disciplina)
        
        if os.path.exists(arquivo_csv):
            try:
                with open(arquivo_csv, mode='r', newline='', encoding='utf-8') as file:
                    reader = csv.reader(file, delimiter=';')
                    next(reader) # Pula o cabeçalho
                    
                    for row in reader:
                        # row[0] é o Nome e row[1] é o RA
                        # Compara o RA do CSV normalizado com o RA de entrada normalizado
                        if len(row) > 1 and row[1].strip().upper() == ra_input_upper:
                            return row[0].strip().upper() # Retorna o nome do aluno no arquivo CSV (em UPPER)
            except Exception:
                pass 
                
    return None # RA é novo e único

def selecionar_disciplina_para_aluno():
    """Exibe as disciplinas e solicita ao usuário que escolha uma válida."""
    disciplinas = carregar_disciplinas()
    while True:
        print(f"\n{COR_TITULO}--- SELEÇÃO DE DISCIPLINA ---{COR_RESET}") # Título em Branco
        # Opções em Azul Claro/Ciano
        for key, value in disciplinas.items():
            print(f"{COR_OPCAO}[{key}] - {value}{COR_RESET}") 
        
        # Input em Amarelo
        escolha = input(f"{COR_INPUT}Selecione a disciplina para o aluno: {COR_RESET}").strip()
        
        # Valida se a opção escolhida está no dicionário de disciplinas
        if escolha in disciplinas:
            return disciplinas[escolha]
        else:
            # Erro em Vermelho
            print(f"{COR_ERRO}Opção inválida. Tente novamente.{COR_RESET}")

def obter_nota(nome_nota):
    """Função auxiliar para solicitar e validar uma única nota (entre 0 e 10)."""
    while True:
        try:
            # Input em Amarelo
            nota = input(f"{COR_INPUT}Digite a nota para {nome_nota} (0 a 10): {COR_RESET}")
            # Converte a entrada para float (aceita vírgula ou ponto)
            nota_float = float(nota.replace(',', '.'))
            if 0 <= nota_float <= 10:
                return nota_float
            else:
                # Erro em Vermelho
                print(f"{COR_ERRO}Nota inválida. Digite um valor entre 0 e 10.{COR_RESET}")
        except ValueError:
            # Erro em Vermelho
            print(f"{COR_ERRO}Entrada inválida. Digite um número.{COR_RESET}")

def cadastrar_aluno_e_notas_em_disciplina(filas_por_disciplina):
    """Solicita os dados do aluno (com validação de nome, RA e Turma) e suas 3 notas."""
    print(f"\n{COR_TITULO}--- Cadastro Básico do Aluno ---{COR_RESET}") # Título em Branco
    
    # Validação do nome: aceita apenas letras e espaços e tem limite de tamanho (NOVO)
    while True:
        # Input em Amarelo
        nome = input(f"{COR_INPUT}Nome do Aluno: {COR_RESET}").strip()
        
        # 1. Checa se o nome não está vazio
        if not nome:
            print(f"{COR_ERRO}Nome não pode ser vazio.{COR_RESET}")
            continue

        # 2. Checa o limite de caracteres
        if len(nome) > LIMITE_NOME:
            print(f"{COR_ERRO}Nome inválido. O nome deve ter no máximo {LIMITE_NOME} caracteres. ({len(nome)} digitados){COR_RESET}")
            continue
            
        # 3. Verifica se contém apenas letras e espaços
        if all(c.isalpha() or c.isspace() for c in nome):
            break
        else:
            # Erro em Vermelho
            print(f"{COR_ERRO}Nome inválido. Por favor, utilize apenas letras.{COR_RESET}")
    
    # Coleta e validação do RA: limite de 8 caracteres e unicidade
    while True:
        ra = input(f"{COR_INPUT}RA do Aluno: {COR_RESET}").strip()
        
        if not ra:
            print(f"{COR_ERRO}RA não pode ser vazio.{COR_RESET}")
            continue

        if len(ra) > LIMITE_RA:
            print(f"{COR_ERRO}RA inválido. O RA deve ter no máximo {LIMITE_RA} caracteres. ({len(ra)} digitados){COR_RESET}")
            continue
            
        # V A L I D A Ç Ã O   D E   U N I C I D A D E   C O N J U N T A (CASE-INSENSITIVE)
        # nome_existente será o nome do aluno já cadastrado com aquele RA, em UPPER
        nome_existente = check_ra_uniqueness(ra, filas_por_disciplina)
        
        if nome_existente is not None:
            # Compara o nome digitado (em UPPER) com o nome já cadastrado (em UPPER)
            if nome.strip().upper() != nome_existente:
                 # Se os nomes NÃO baterem (mas os RAs são iguais de forma case-insensitive), dá erro!
                 print(f"{COR_ERRO}RA '{ra}' (ou sua variação maiúscula/minúscula) já está cadastrado para o aluno '{nome_existente}'.{COR_RESET}")
                 print(f"{COR_ERRO}Você não pode cadastrar um aluno diferente com o mesmo RA. Tente novamente.{COR_RESET}")
                 continue
            else:
                # Se o RA existe E o nome digitado É o mesmo (RA pode ser reutilizado pelo mesmo aluno)
                print(f"{Fore.GREEN}RA '{ra}' pertence ao aluno '{nome_existente}'. Cadastro autorizado para outra disciplina/notas.{COR_RESET}")
                break
        
        break # RA é novo e válido
    
    # Coleta e validação da Turma: limite de 8 caracteres
    while True:
        turma = input(f"{COR_INPUT}Turma: {COR_RESET}").strip()
        
        if not turma:
            print(f"{COR_ERRO}Turma não pode ser vazia.{COR_RESET}")
            continue

        if len(turma) > LIMITE_TURMA:
            print(f"{COR_ERRO}Turma inválida. O campo Turma deve ter no máximo {LIMITE_TURMA} caracteres. ({len(turma)} digitados){COR_RESET}")
            continue
        
        break # Turma válida
    
    nome_disciplina = selecionar_disciplina_para_aluno()
    
    # Define os nomes das notas a serem solicitadas
    nomes_notas = [
        "Prova 1º Bimestre", 
        "Prova 2º Bimestre", 
        "Trabalho"
    ]
    
    notas = []
    print(f"\n{COR_TITULO}--- Cadastro de Notas para {nome_disciplina} ---{COR_RESET}") # Título em Branco
    
    # Coleta as 3 notas usando a função de validação
    for nome_nota in nomes_notas:
        nota = obter_nota(nome_nota)
        notas.append(nota)
        
    # Mensagem de Sucesso em Verde
    print(f"{COR_SUCESSO}\nCadastro de 3 notas completo. Retornando ao menu principal para salvar.{COR_RESET}")
    # Retorna o objeto Aluno preenchido
    return Aluno(nome, ra, turma, nome_disciplina, notas)


def salvar_dados_csv(filas_por_disciplina):
    """Persiste os dados dos alunos da fila (FIFO) em arquivos CSV separados por disciplina."""
    salvos_count = 0
    # Itera sobre as filas de alunos pendentes por disciplina
    for disciplina, alunos_fila in filas_por_disciplina.items():
        if not alunos_fila:
            continue

        arquivo_csv = formatar_nome_arquivo(disciplina)
        arquivo_existe = os.path.exists(arquivo_csv)
        
        try:
            # Abre o arquivo em modo append ('a')
            with open(arquivo_csv, mode='a', newline='', encoding='utf-8') as file:
                writer = csv.writer(file, delimiter=';')
                
                # Escreve o cabeçalho apenas se o arquivo for novo
                if not arquivo_existe:
                    writer.writerow(["Nome", "RA", "Turma", "Disciplina", "Prova 1", "Prova 2", "Trabalho", "Média Semestral"])

                print(f"{COR_TITULO}\n--- Processando Fila de {disciplina} (FIFO) ---{COR_RESET}") # Título em Branco
                # Remove e processa cada aluno da fila
                while alunos_fila:
                    aluno = alunos_fila.popleft() # Usa FIFO (First-In, First-Out)
                    writer.writerow(aluno.to_csv_row()) # Grava a linha formatada
                    # Mensagem de sucesso (salvo) em Verde
                    print(f"{Fore.GREEN}SALVO: {aluno.nome} (Média Semestral: {aluno.media_semestral:.2f}){COR_RESET}")
                    salvos_count += 1
                    
        except Exception as e:
            # Erro em Vermelho
            print(f"{COR_ERRO} Erro ao salvar os dados da disciplina {disciplina}: {e}{COR_RESET}")
            
    if salvos_count > 0:
        # Sucesso em Verde
        print(f"\n{COR_SUCESSO} Total de {salvos_count} cadastros salvos com sucesso em seus respectivos arquivos.{COR_RESET}")
    else:
        # Alerta (se tentou salvar sem dados) em Vermelho
        print(f"\n{COR_ALERTA}Nenhum novo cadastro para salvar nesta sessão.{COR_RESET}")

# ----------------------------------------------
# RECURSO: VISUALIZAR DADOS SALVOS
# ----------------------------------------------
def visualizar_alunos_salvos():
    """Permite ao usuário selecionar uma disciplina e visualizar os alunos do CSV."""
    
    disciplinas = carregar_disciplinas()
    
    print(f"\n{COR_TITULO}--- VISUALIZAR DADOS SALVOS ---{COR_RESET}") # Título em Branco
    # Opções em Azul Claro/Ciano
    for key, value in disciplinas.items():
        print(f"{COR_OPCAO}[{key}] - {value}{COR_RESET}")
    
    # Input em Amarelo
    escolha = input(f"{COR_INPUT}Selecione a disciplina para visualizar: {COR_RESET}").strip()
    
    if escolha not in disciplinas:
        # Erro em Vermelho
        print(f"{COR_ERRO}Opção inválida.{COR_RESET}")
        return

    nome_disciplina = disciplinas[escolha]
    arquivo_csv = formatar_nome_arquivo(nome_disciplina)

    # Verifica se o arquivo existe
    if not os.path.exists(arquivo_csv):
        # Alerta em Vermelho
        print(f"\n{COR_ALERTA} O arquivo de dados para '{nome_disciplina}' ainda não existe. Cadastre e salve alunos primeiro.{COR_RESET}")
        return

    try:
        print(f"\n{COR_TITULO}=== Alunos Cadastrados em {nome_disciplina} ==={COR_RESET}") # Título em Branco
        # Abre o arquivo CSV para leitura
        with open(arquivo_csv, mode='r', newline='', encoding='utf-8') as file:
            reader = csv.reader(file, delimiter=';')
            
            next(reader) # Pula o cabeçalho
            
            tem_alunos = False
            # Imprime os dados de cada linha
            for row in reader:
                if len(row) < 8: continue
                
                nome, ra, turma, _, p1, p2, trab, media_semestral = row
                # Usa cor Verde se a média for maior ou igual a 6.0, e Vermelho caso contrário
                cor_media = Fore.GREEN if float(media_semestral) >= 6.0 else Fore.RED
                
                # Exibe a linha, destacando a média
                print(f"Nome: {nome} | RA: {ra} | Turma: {turma} | P1: {p1} | P2: {p2} | Trabalho: {trab} | Média Semestral: {cor_media}{media_semestral}{COR_RESET}")
                tem_alunos = True
            
            if not tem_alunos:
                # Alerta em Vermelho
                print(f"{COR_ALERTA}Nenhum aluno encontrado neste arquivo.{COR_RESET}")
                
    except Exception as e:
        # Erro em Vermelho
        print(f"{COR_ERRO} Erro ao ler o arquivo {arquivo_csv}: {e}{COR_RESET}")


# ----------------------------------------------
# FUNÇÃO PRINCIPAL
# Objetivo: Lógica de menu e controle do fluxo do sistema.
# ----------------------------------------------
def main():
    """Função principal que executa o sistema e o menu de opções."""
    
    disciplinas_disponiveis = carregar_disciplinas()
    # Inicializa um dicionário de filas (deque) para armazenar alunos por disciplina
    filas_por_disciplina = {
        nome: deque() 
        for nome in disciplinas_disponiveis.values()
    }
    
    # Título principal em Branco
    print(f"\n{COR_TITULO}==============================================")
    print("      SISTEMA ACADÊMICO - INÍCIO")
    print("==============================================" + COR_RESET)
    
    # Loop principal do menu
    while True:
        print(f"\n{COR_TITULO}--- MENU PRINCIPAL ---{COR_RESET}") # Título em Branco
        # Opções em Azul Claro/Ciano
        print(f"{COR_OPCAO}[1] - Cadastrar Novo Aluno, Disciplina e Notas{COR_RESET}")
        print(f"{COR_OPCAO}[2] - SALVAR E PERSISTIR dados da Fila{COR_RESET}")
        print(f"{COR_OPCAO}[3] - Visualizar Alunos Salvos{COR_RESET}")
        # Opção Sair com aviso em Vermelho
        print(f"{COR_OPCAO}[0] - Sair do Sistema{COR_RESET}")
        
        # Input em Amarelo
        acao = input(f"{COR_INPUT}Escolha uma ação: {COR_RESET}").strip()
        
        if acao == '1':
            # Passa o dicionário de filas para que a função de cadastro possa checar o RA
            aluno_completo = cadastrar_aluno_e_notas_em_disciplina(filas_por_disciplina)
            
            # Se a função cadastrar_aluno_e_notas_em_disciplina não retornar nada, volta ao menu
            if aluno_completo:
                disciplina_do_aluno = aluno_completo.disciplina
                filas_por_disciplina[disciplina_do_aluno].append(aluno_completo)
                media_final = aluno_completo.calcular_media()
            
                # Mensagem de sucesso (adicionado à fila) em Verde
                print(f"\n{COR_SUCESSO}--> Aluno {aluno_completo.nome} adicionado à Fila da disciplina {disciplina_do_aluno}.{COR_RESET}")
                
                # Colore a média final calculada (Verde se >= 6.0, Vermelho se < 6.0)
                cor_media = Fore.GREEN if media_final >= 6.0 else Fore.RED
                print(f"--> Média Semestral calculada: {cor_media}{media_final:.2f}{COR_RESET}")
            
        elif acao == '2':
            # Salva os alunos em fila nos respectivos arquivos CSV
            salvar_dados_csv(filas_por_disciplina)
            
        elif acao == '3':
            # Exibe o conteúdo de um arquivo CSV de disciplina
            visualizar_alunos_salvos()

        elif acao == '0':
            # Verifica se há dados não salvos antes de sair
            total_nao_salvo = sum(len(fila) for fila in filas_por_disciplina.values())
            if total_nao_salvo > 0:
                # Alerta em Vermelho
                print(f"\n{COR_ALERTA}ATENÇÃO: Há {total_nao_salvo} cadastros na Fila que não foram salvos!{COR_RESET}")
                # Input de confirmação em Amarelo
                confirm = input(f"{COR_INPUT}Deseja descartar estes cadastros e sair? (s/n): {COR_RESET}").lower().strip()
                if confirm == 's':
                    # Mensagem de saída forçada em Vermelho
                    print(f"{COR_ERRO}Encerrando o sistema. Dados não salvos descartados.{COR_RESET}")
                    break
                else:
                    continue
            
            # Mensagem de saída normal em Branco
            print(f"\n{COR_TITULO}Encerrando o sistema. Até logo!{COR_RESET}")
            break
            
        else:
            # Erro de opção inválida em Vermelho
            print(f"{COR_ERRO}Opção inválida. Tente novamente.{COR_RESET}")

if __name__ == "__main__":
    main()