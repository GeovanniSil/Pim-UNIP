import csv
import os
from collections import deque

# ----------------------------------------------
# CLASSE DE MODELAGEM DO ALUNO
# ----------------------------------------------
class Aluno:
    def __init__(self, nome, ra, turma, disciplina, notas=None):
        self.nome = nome
        self.ra = ra
        self.turma = turma
        self.disciplina = disciplina
        # self.notas agora deve conter no máximo 3 floats: [P1, P2, Trabalho]
        self.notas = notas if notas is not None else []
        # VARIÁVEL RENOMEADA: de self.media para self.media_semestral
        self.media_semestral = 0.0

    def calcular_media(self):
        """
        Calcula a Média Semestral (Soma das 3 notas / 3).
        """
        NUMERO_NOTAS_FIXO = 3
        
        if len(self.notas) != NUMERO_NOTAS_FIXO:
            self.media_semestral = 0.0
            if len(self.notas) > 0:
                 # Esta mensagem de alerta só aparece se houver notas, mas não 3
                 print(f"Alerta: O cálculo da média requer exatamente {NUMERO_NOTAS_FIXO} notas. Média Semestral definida como 0.0.")
            return self.media_semestral

        # Cálculo da Média Semestral
        soma_notas = sum(self.notas)
        self.media_semestral = soma_notas / NUMERO_NOTAS_FIXO
        return self.media_semestral

    def to_csv_row(self):
        self.calcular_media()
        
        # Assume que self.notas[0], [1], [2] existem devido à função de cadastro
        p1 = f"{self.notas[0]:.2f}"
        p2 = f"{self.notas[1]:.2f}"
        trab = f"{self.notas[2]:.2f}"
        
        # VARIÁVEL RENOMEADA: self.media_semestral
        # Retorna a linha: [..., Disciplina, P1, P2, Trabalho, Média Semestral]
        return [self.nome, self.ra, self.turma, self.disciplina, p1, p2, trab, f"{self.media_semestral:.2f}"]

# ----------------------------------------------
# FUNÇÕES DE LÓGICA DO SISTEMA
# ----------------------------------------------

def carregar_disciplinas():
    return {
        '1': "Algoritmos e Estruturas de Dados em Python",
        '2': "Análise e Projeto de Sistemas",
        '3': "Engenharia de Software Agil",  'Tirei o acento do "Ágil" para nao der erro'
        '4': "Programação Estruturada em C"
    }

def selecionar_disciplina_para_aluno():
    disciplinas = carregar_disciplinas()
    while True:
        print("\n--- SELEÇÃO DE DISCIPLINA ---")
        for key, value in disciplinas.items():
            print(f"[{key}] - {value}")
        escolha = input("Selecione a disciplina para o aluno: ")
        if escolha in disciplinas:
            return disciplinas[escolha]
        else:
            print("Opção inválida. Tente novamente.")

def obter_nota(nome_nota):
    """Função auxiliar para solicitar e validar uma única nota."""
    while True:
        try:
            nota = input(f"Digite a nota para {nome_nota} (0 a 10): ")
            nota_float = float(nota.replace(',', '.'))
            if 0 <= nota_float <= 10:
                return nota_float
            else:
                print("Nota inválida. Digite um valor entre 0 e 10.")
        except ValueError:
            print("Entrada inválida. Digite um número.")

def cadastrar_aluno_e_notas_em_disciplina():
    print("\n--- Cadastro Básico do Aluno ---")
    nome = input("Nome do Aluno: ").strip()
    ra = input("RA do Aluno: ").strip()
    turma = input("Turma (Ex: ADS-A): ").strip()
    nome_disciplina = selecionar_disciplina_para_aluno()
    
    nomes_notas = [
        "Prova 1º Bimestre", 
        "Prova 2º Bimestre", 
        "Trabalho"
    ]
    
    notas = []
    print(f"\n--- Cadastro de Notas para {nome_disciplina} ---")
    
    for nome_nota in nomes_notas:
        nota = obter_nota(nome_nota)
        notas.append(nota)
        
    print("\nCadastro de 3 notas completo.")
    return Aluno(nome, ra, turma, nome_disciplina, notas)

def formatar_nome_arquivo(nome_disciplina):
    return nome_disciplina.replace(" ", "_").replace("ê", "e").replace("á", "a") + ".csv"

def salvar_dados_csv(filas_por_disciplina):
    salvos_count = 0
    for disciplina, alunos_fila in filas_por_disciplina.items():
        if not alunos_fila:
            continue

        arquivo_csv = formatar_nome_arquivo(disciplina)
        arquivo_existe = os.path.exists(arquivo_csv)
        
        try:
            with open(arquivo_csv, mode='a', newline='', encoding='utf-8') as file:
                writer = csv.writer(file, delimiter=';')
                
                # ALTERAÇÃO: Cabeçalho com "Média Semestral"
                if not arquivo_existe:
                    writer.writerow(["Nome", "RA", "Turma", "Disciplina", "Prova 1", "Prova 2", "Trabalho", "Média Semestral"])

                print(f"\n--- Processando Fila de {disciplina} (FIFO) ---")
                while alunos_fila:
                    aluno = alunos_fila.popleft()
                    writer.writerow(aluno.to_csv_row())
                    # VARIÁVEL RENOMEADA: aluno.media_semestral
                    print(f"SALVO: {aluno.nome} (Média Semestral: {aluno.media_semestral:.2f})")
                    salvos_count += 1
                    
        except Exception as e:
            print(f" Erro ao salvar os dados da disciplina {disciplina}: {e}")
            
    if salvos_count > 0:
        print(f"\n Total de {salvos_count} cadastros salvos com sucesso em seus respectivos arquivos.")
    else:
        print("\nNenhum novo cadastro para salvar nesta sessão.")

# ----------------------------------------------
# RECURSO: VISUALIZAR DADOS SALVOS
# ----------------------------------------------
def visualizar_alunos_salvos():
    """Permite ao usuário selecionar uma disciplina e visualizar todos os alunos no CSV."""
    
    disciplinas = carregar_disciplinas()
    
    print("\n--- VISUALIZAR DADOS SALVOS ---")
    for key, value in disciplinas.items():
        print(f"[{key}] - {value}")
    
    escolha = input("Selecione a disciplina para visualizar: ")
    
    if escolha not in disciplinas:
        print("Opção inválida.")
        return

    nome_disciplina = disciplinas[escolha]
    arquivo_csv = formatar_nome_arquivo(nome_disciplina)

    if not os.path.exists(arquivo_csv):
        print(f"\n O arquivo de dados para '{nome_disciplina}' ainda não existe. Cadastre e salve alunos primeiro.")
        return

    try:
        print(f"\n=== Alunos Cadastrados em {nome_disciplina} ===")
        with open(arquivo_csv, mode='r', newline='', encoding='utf-8') as file:
            reader = csv.reader(file, delimiter=';')
            
            # Pula o cabeçalho (que agora tem "Média Semestral")
            next(reader) 
            
            tem_alunos = False
            for row in reader:
                # Estrutura do CSV: [0:Nome, 1:RA, 2:Turma, 3:Disciplina, 4:P1, 5:P2, 6:Trabalho, 7:Média Semestral]
                if len(row) < 8: continue
                
                nome, ra, turma, _, p1, p2, trab, media_semestral = row
                # MUDANÇA NA EXIBIÇÃO
                print(f"Nome: {nome} | RA: {ra} | Turma: {turma} | P1: {p1} | P2: {p2} | Trabalho: {trab} | Média Semestral: {media_semestral}")
                tem_alunos = True
            
            if not tem_alunos:
                print("Nenhum aluno encontrado neste arquivo.")
                
    except Exception as e:
        print(f" Erro ao ler o arquivo {arquivo_csv}: {e}")


# ----------------------------------------------
# FUNÇÃO PRINCIPAL
# ----------------------------------------------
def main():
    """Função principal que executa o sistema."""
    
    disciplinas_disponiveis = carregar_disciplinas()
    filas_por_disciplina = {
        nome: deque() 
        for nome in disciplinas_disponiveis.values()
    }
    
    print("\n==============================================")
    print("      SISTEMA ACADÊMICO - INÍCIO")
    print("==============================================")
    
    while True:
        print("\n--- MENU PRINCIPAL ---")
        print("[1] - Cadastrar Novo Aluno, Disciplina e Notas")
        print("[2] - SALVAR E PERSISTIR dados da Fila (no CSV)")
        print("[3] - Visualizar Alunos Salvos (do CSV)")
        print("[0] - Sair do Sistema")
        
        acao = input("Escolha uma ação: ")
        
        if acao == '1':
            aluno_completo = cadastrar_aluno_e_notas_em_disciplina()
            disciplina_do_aluno = aluno_completo.disciplina
            filas_por_disciplina[disciplina_do_aluno].append(aluno_completo)
            # VARIÁVEL RENOMEADA: media_final agora é aluno_completo.calcular_media()
            media_final = aluno_completo.calcular_media()
            print(f"\n--> Aluno {aluno_completo.nome} adicionado à Fila da disciplina {disciplina_do_aluno}.")
            # MUDANÇA NA EXIBIÇÃO
            print(f"--> Média Semestral calculada: {media_final:.2f}")
            
        elif acao == '2':
            salvar_dados_csv(filas_por_disciplina)
            
        elif acao == '3':
            visualizar_alunos_salvos()

        elif acao == '0':
            total_nao_salvo = sum(len(fila) for fila in filas_por_disciplina.values())
            if total_nao_salvo > 0:
                print(f"\nATENÇÃO: Há {total_nao_salvo} cadastros na Fila que não foram salvos!")
                confirm = input("Deseja descartar estes cadastros e sair? (s/n): ").lower()
                if confirm == 's':
                    print("Encerrando o sistema. Dados não salvos descartados.")
                    break
                else:
                    continue
            
            print("\nEncerrando o sistema. Até logo!")
            break
            
        else:
            print("Opção inválida.")

if __name__ == "__main__":
    main()