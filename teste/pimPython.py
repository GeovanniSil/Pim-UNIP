import csv
import os
from collections import deque 

# ... (CLASSES E FUNÇÕES AUXILIARES MANTIDAS: Aluno, carregar_disciplinas, selecionar_disciplina_para_aluno, cadastrar_aluno_e_notas_em_disciplina, formatar_nome_arquivo)
# Para economizar espaço, mantenho o código da classe Aluno e das funções de cadastro. 
# A única mudança é a nova função 'visualizar_alunos_salvos'.

# ----------------------------------------------
# CLASSE DE MODELAGEM DO ALUNO (Mantida)
# ----------------------------------------------
class Aluno:
    def __init__(self, nome, ra, turma, disciplina, notas=None):
        self.nome = nome
        self.ra = ra
        self.turma = turma
        self.disciplina = disciplina
        self.notas = notas if notas is not None else []
        self.media = 0.0

    def calcular_media(self):
        if not self.notas:
            self.media = 0.0
            return self.media
        numero_de_notas = len(self.notas)
        soma_notas = sum(self.notas)
        self.media = soma_notas / numero_de_notas
        return self.media

    def to_csv_row(self):
        self.calcular_media() 
        notas_str = ";".join(map(str, self.notas))
        return [self.nome, self.ra, self.turma, self.disciplina, notas_str, f"{self.media:.2f}"]

# ----------------------------------------------
# FUNÇÕES DE LÓGICA DO SISTEMA (Mantidas ou Adaptadas)
# ----------------------------------------------

# As funções carregar_disciplinas, selecionar_disciplina_para_aluno, 
# cadastrar_aluno_e_notas_em_disciplina e formatar_nome_arquivo permanecem as mesmas.

# A função salvar_dados_csv também permanece a mesma (usando 'a' para append).

def carregar_disciplinas():
    return {
        '1': "Algoritmos e Estruturas de Dados",
        '2': "Engenharia de Software",
        '3': "Banco de Dados"
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

def cadastrar_aluno_e_notas_em_disciplina():
    print("\n--- Cadastro Básico do Aluno ---")
    nome = input("Nome do Aluno: ").strip()
    ra = input("RA do Aluno: ").strip()
    turma = input("Turma (Ex: ADS-A): ").strip()
    nome_disciplina = selecionar_disciplina_para_aluno()
    
    notas = []
    print(f"\n--- Cadastro de Notas para {nome_disciplina} ---")
    while True:
        try:
            nota = input("Digite uma nota (0 a 10, ou 'f' para finalizar): ")
            if nota.lower() == 'f':
                break
            nota_float = float(nota.replace(',', '.'))
            if 0 <= nota_float <= 10:
                notas.append(nota_float)
            else:
                print("Nota inválida. Digite um valor entre 0 e 10.")
        except ValueError:
            print("Entrada inválida. Digite um número ou 'f'.")
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
                
                if not arquivo_existe:
                    writer.writerow(["Nome", "RA", "Turma", "Disciplina", "Notas (separadas por ';')", "Média"])

                print(f"\n--- Processando Fila de {disciplina} (FIFO) ---")
                while alunos_fila:
                    aluno = alunos_fila.popleft()
                    writer.writerow(aluno.to_csv_row())
                    print(f"SALVO: {aluno.nome} (Média: {aluno.media:.2f})")
                    salvos_count += 1
                    
        except Exception as e:
            print(f"❌ Erro ao salvar os dados da disciplina {disciplina}: {e}")
            
    if salvos_count > 0:
        print(f"\n✅ Total de {salvos_count} cadastros salvos com sucesso em seus respectivos arquivos.")
    else:
        print("\nNenhum novo cadastro para salvar nesta sessão.")

# ----------------------------------------------
# NOVO RECURSO: VISUALIZAR DADOS SALVOS
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
        print(f"\n⚠️ O arquivo de dados para '{nome_disciplina}' ainda não existe. Cadastre e salve alunos primeiro.")
        return

    try:
        print(f"\n=== Alunos Cadastrados em {nome_disciplina} ===")
        with open(arquivo_csv, mode='r', newline='', encoding='utf-8') as file:
            reader = csv.reader(file, delimiter=';')
            
            # Pula o cabeçalho
            header = next(reader) 
            
            tem_alunos = False
            for row in reader:
                # Formato: [Nome, RA, Turma, Disciplina, Notas, Média]
                nome, ra, turma, _, _, media = row
                print(f"Nome: {nome} | RA: {ra} | Turma: {turma} | Média: {media}")
                tem_alunos = True
            
            if not tem_alunos:
                print("Nenhum aluno encontrado neste arquivo.")
                
    except Exception as e:
        print(f"❌ Erro ao ler o arquivo {arquivo_csv}: {e}")


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
        print("[3] - Visualizar Alunos Salvos (do CSV)") # NOVO!
        print("[0] - Sair do Sistema")
        
        acao = input("Escolha uma ação: ")
        
        if acao == '1':
            aluno_completo = cadastrar_aluno_e_notas_em_disciplina()
            disciplina_do_aluno = aluno_completo.disciplina
            filas_por_disciplina[disciplina_do_aluno].append(aluno_completo)
            media_final = aluno_completo.calcular_media()
            print(f"\n--> Aluno {aluno_completo.nome} adicionado à Fila da disciplina {disciplina_do_aluno}.")
            print(f"--> Média final calculada: {media_final:.2f}")
            
        elif acao == '2':
            # Salva os novos dados, ANEXANDO ao que já existe no CSV
            salvar_dados_csv(filas_por_disciplina)
            
        elif acao == '3':
            # Visualiza os dados persistidos no CSV
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